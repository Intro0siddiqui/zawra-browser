/*
 * Copyright (C) 2021 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "PrivateClickMeasurementDatabase.h"

#include "Logging.h"
#include "PrivateClickMeasurementDebugInfo.h"
#include "PrivateClickMeasurementManager.h"
#include "ZPCMBridge.h"
#include <WebCore/RegistrableDomain.h>
#include <wtf/NeverDestroyed.h>
#include <wtf/TZoneMallocInlines.h>
#include <wtf/text/MakeString.h>
#include <wtf/text/StringBuilder.h>

namespace WebKit::PCM {

static WeakHashSet<Database>& NODELETE allDatabases()
{
    ASSERT(!RunLoop::isMain());
    static NeverDestroyed<WeakHashSet<Database>> set;
    return set;
}

WTF_MAKE_TZONE_ALLOCATED_IMPL(Database);

Ref<Database> Database::create(const String& storageDirectory)
{
    return adoptRef(*new Database(storageDirectory));
}

Database::Database(const String& storageDirectory)
    : DatabaseUtilities(FileSystem::pathByAppendingComponent(storageDirectory, "pcm.db"_s))
{
    ASSERT(!RunLoop::isMain());
    allDatabases().add(*this);
}

Database::~Database()
{
    ASSERT(!RunLoop::isMain());
    allDatabases().remove(*this);
}

void Database::interruptAllDatabases()
{
    ASSERT(!RunLoop::isMain());
    for (auto& database : allDatabases())
        database.interrupt();
}

void Database::insertPrivateClickMeasurement(WebCore::PrivateClickMeasurement&& attribution, PrivateClickMeasurementAttributionType attributionType)
{
    ASSERT(!RunLoop::isMain());

    // Route through BrowserDB via ZPCMBridge
    if (attributionType == PrivateClickMeasurementAttributionType::Attributed) {
        auto utf8 = attribution.sourceApplicationBundleID().utf8();
        ZPCMBridge::storeAttributed(utf8.data(), utf8.length());
    } else {
        auto utf8 = attribution.sourceApplicationBundleID().utf8();
        ZPCMBridge::storeUnattributed(utf8.data(), utf8.length());
    }
}

void Database::markAllUnattributedPrivateClickMeasurementAsExpiredForTesting()
{
    ASSERT(!RunLoop::isMain());
}

std::pair<std::optional<Database::UnattributedPrivateClickMeasurement>, std::optional<Database::AttributedPrivateClickMeasurement>> Database::findPrivateClickMeasurement(const WebCore::PCM::SourceSite&, const WebCore::PCM::AttributionDestinationSite&, const ApplicationBundleIdentifier&)
{
    ASSERT(!RunLoop::isMain());
    return std::make_pair(std::nullopt, std::nullopt);
}

std::pair<std::optional<WebCore::PCM::AttributionSecondsUntilSendData>, DebugInfo> Database::attributePrivateClickMeasurement(const WebCore::PCM::SourceSite& sourceSite, const WebCore::PCM::AttributionDestinationSite& destinationSite, const ApplicationBundleIdentifier& applicationBundleIdentifier, WebCore::PCM::AttributionTriggerData&& attributionTriggerData, WebCore::PrivateClickMeasurement::IsRunningLayoutTest isRunningTest)
{
    ASSERT(!RunLoop::isMain());

    clearExpiredPrivateClickMeasurement();
    if (!attributionTriggerData.isValid()) {
        RELEASE_LOG_INFO(PrivateClickMeasurement, "Got an invalid attribution.");
        return { std::nullopt, {{{ MessageLevel::Error, "[Private Click Measurement] Got an invalid attribution."_s }}} };
    }

    DebugInfo debugInfo;
    auto data = attributionTriggerData.data;
    auto priority = attributionTriggerData.priority;
    RELEASE_LOG_INFO(PrivateClickMeasurement, "Got an attribution with attribution trigger data: %u and priority: %u.", data, priority);
    debugInfo.messages.append({ MessageLevel::Info, makeString("[Private Click Measurement] Got an attribution with attribution trigger data: '"_s, data, "' and priority: '"_s, priority, "'."_s) });

    WebCore::PCM::AttributionSecondsUntilSendData secondsUntilSend { std::nullopt, std::nullopt };

    auto attribution = findPrivateClickMeasurement(sourceSite, destinationSite, applicationBundleIdentifier);
    auto& previouslyUnattributed = attribution.first;
    auto& previouslyAttributed = attribution.second;

    if (previouslyUnattributed) {
        removeUnattributed(*previouslyUnattributed);
        secondsUntilSend = previouslyUnattributed.value().attributeAndGetEarliestTimeToSend(WTF::move(attributionTriggerData), isRunningTest);

        if (!secondsUntilSend.hasValidSecondsUntilSendValues()) {
            ASSERT_NOT_REACHED();
            return { std::nullopt, WTF::move(debugInfo) };
        }

        RELEASE_LOG_INFO(PrivateClickMeasurement, "Converted a stored ad click with attribution trigger data: %u and priority: %u.", data, priority);
        debugInfo.messages.append({ MessageLevel::Info, makeString("[Private Click Measurement] Converted a stored ad click with attribution trigger data: '"_s, data, "' and priority: '"_s, priority, "'."_s) });

        if (!previouslyAttributed || previouslyUnattributed.value().hasHigherPriorityThan(*previouslyAttributed)) {
            insertPrivateClickMeasurement(WTF::move(*previouslyUnattributed), PrivateClickMeasurementAttributionType::Attributed);

            RELEASE_LOG_INFO(PrivateClickMeasurement, "Replaced a previously converted ad click with a new one with attribution data: %u and priority: %u because it had higher priority.", data, priority);
            debugInfo.messages.append({ MessageLevel::Info, makeString("[Private Click Measurement] Replaced a previously converted ad click with a new one with attribution trigger data: '"_s, data, "' and priority: '"_s, priority, "' because it had higher priority."_s) });
        }
    } else if (previouslyAttributed) {
        if (!previouslyAttributed.value().hasPreviouslyBeenReported()) {
            auto secondsUntilSend = previouslyAttributed.value().attributeAndGetEarliestTimeToSend(WTF::move(attributionTriggerData), isRunningTest);
            if (!secondsUntilSend.hasValidSecondsUntilSendValues())
                return { std::nullopt, WTF::move(debugInfo) };

            insertPrivateClickMeasurement(WTF::move(*previouslyAttributed), PrivateClickMeasurementAttributionType::Attributed);

            RELEASE_LOG_INFO(PrivateClickMeasurement, "Re-converted an ad click with a new one with attribution trigger data: %u and priority: %u because it had higher priority.", data, priority);
            debugInfo.messages.append({ MessageLevel::Info, makeString("[Private Click Measurement] Re-converted an ad click with a new one with attribution trigger data: '"_s, data, "' and priority: '"_s, priority, "'' because it had higher priority."_s) });
        }
    }

    if (!secondsUntilSend.hasValidSecondsUntilSendValues())
        return { std::nullopt, WTF::move(debugInfo) };

    return { secondsUntilSend, WTF::move(debugInfo) };
}

void Database::removeUnattributed(WebCore::PrivateClickMeasurement& attribution)
{
    ASSERT(!RunLoop::isMain());
    // Route removal through BrowserDB via ZPCMBridge
    ZPCMBridge::deleteMeasurement(0, static_cast<uint64_t>(attribution.sourceID()));
}

Vector<WebCore::PrivateClickMeasurement> Database::allAttributedPrivateClickMeasurement()
{
    ASSERT(!RunLoop::isMain());

    // Retrieve attributed PCM from BrowserDB via ZPCMBridge
    Vector<WebCore::PrivateClickMeasurement> attributions;
    {
        char buf[4096];
        uint32_t written = 0;
        if (ZPCMBridge::getAttributed(buf, sizeof(buf), &written) == 0 && written > 2) {
            // BrowserDB data is available; currently retained for future merge
        }
    }

    return attributions;
}

String Database::privateClickMeasurementToStringForTesting() const
{
    ASSERT(!RunLoop::isMain());
    return "\nNo stored Private Click Measurement data.\n"_s;
}

String Database::attributionToStringForTesting(const WebCore::PrivateClickMeasurement&) const
{
    ASSERT(!RunLoop::isMain());
    return emptyString();
}

void Database::markAttributedPrivateClickMeasurementsAsExpiredForTesting()
{
    ASSERT(!RunLoop::isMain());
}

void Database::clearPrivateClickMeasurement(std::optional<WebCore::RegistrableDomain>)
{
    ASSERT(!RunLoop::isMain());
}

void Database::clearExpiredPrivateClickMeasurement()
{
    ASSERT(!RunLoop::isMain());
}

void Database::clearSentAttribution(WebCore::PrivateClickMeasurement&&, WebCore::PCM::AttributionReportEndpoint)
{
    ASSERT(!RunLoop::isMain());
}

void Database::markReportAsSentToDestination(SourceDomainID, DestinationDomainID, const ApplicationBundleIdentifier&)
{
    ASSERT(!RunLoop::isMain());
}

void Database::markReportAsSentToSource(SourceDomainID, DestinationDomainID, const ApplicationBundleIdentifier&)
{
    ASSERT(!RunLoop::isMain());
}

std::pair<std::optional<Database::SourceEarliestTimeToSend>, std::optional<Database::DestinationEarliestTimeToSend>> Database::earliestTimesToSend(const WebCore::PrivateClickMeasurement&)
{
    ASSERT(!RunLoop::isMain());
    return std::make_pair(std::nullopt, std::nullopt);
}

std::optional<Database::DomainID> Database::domainID(const WebCore::RegistrableDomain&)
{
    ASSERT(!RunLoop::isMain());
    return std::nullopt;
}

String Database::getDomainStringFromDomainID(DomainID) const
{
    ASSERT(!RunLoop::isMain());
    return emptyString();
}

std::optional<Database::DomainID> Database::ensureDomainID(const WebCore::RegistrableDomain&)
{
    ASSERT(!RunLoop::isMain());
    return std::nullopt;
}

void Database::addDestinationTokenColumnsIfNecessary()
{
}

const MemoryCompactLookupOnlyRobinHoodHashMap<String, TableAndIndexPair>& Database::expectedTableAndIndexQueries()
{
    static NeverDestroyed<MemoryCompactLookupOnlyRobinHoodHashMap<String, TableAndIndexPair>> emptyMap;
    return emptyMap;
}

bool Database::createSchema()
{
    return true;
}

void Database::destroyStatements()
{
}

bool Database::createUniqueIndices()
{
    return true;
}

std::span<const ASCIILiteral> Database::sortedTables()
{
    return { };
}

Vector<WebCore::RegistrableDomain> Database::fetchRegistrableDomains() const
{
    return { };
}

} // namespace WebKit::PCM
