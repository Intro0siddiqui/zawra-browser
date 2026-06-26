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
#if 0
#include <WebCore/SQLiteStatement.h>
#include <WebCore/SQLiteStatementAutoResetScope.h>
#include <WebCore/SQLiteTransaction.h>
#endif

namespace WebKit::PCM {

// SQL query constants retained for reference (unused when SQLite is disabled).
#if 0
constexpr auto setUnattributedPrivateClickMeasurementAsExpiredQuery = "UPDATE UnattributedPrivateClickMeasurement SET timeOfAdClick = -1.0"_s;
constexpr auto insertUnattributedPrivateClickMeasurementQuery = "INSERT OR REPLACE INTO UnattributedPrivateClickMeasurement (sourceSiteDomainID, destinationSiteDomainID, "
    "sourceID, timeOfAdClick, token, signature, keyID, sourceApplicationBundleID) VALUES (?, ?, ?, ?, ?, ?, ?, ?)"_s;
constexpr auto insertAttributedPrivateClickMeasurementQuery = "INSERT OR REPLACE INTO AttributedPrivateClickMeasurement (sourceSiteDomainID, destinationSiteDomainID, "
    "sourceID, attributionTriggerData, priority, timeOfAdClick, earliestTimeToSendToSource, token, signature, keyID, earliestTimeToSendToDestination, sourceApplicationBundleID, destinationToken, destinationSignature, destinationKeyID) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"_s;
constexpr auto findUnattributedQuery = "SELECT * FROM UnattributedPrivateClickMeasurement WHERE sourceSiteDomainID = ? AND destinationSiteDomainID = ? AND sourceApplicationBundleID = ?"_s;
constexpr auto findAttributedQuery = "SELECT * FROM AttributedPrivateClickMeasurement WHERE sourceSiteDomainID = ? AND destinationSiteDomainID = ? AND sourceApplicationBundleID = ?"_s;
constexpr auto removeUnattributedQuery = "DELETE FROM UnattributedPrivateClickMeasurement WHERE sourceSiteDomainID = ? AND destinationSiteDomainID = ? AND sourceApplicationBundleID = ?"_s;
constexpr auto allAttributedPrivateClickMeasurementQuery = "SELECT *, MIN(earliestTimeToSendToSource, earliestTimeToSendToDestination) as minVal "
    "FROM AttributedPrivateClickMeasurement WHERE earliestTimeToSendToSource IS NOT NULL AND earliestTimeToSendToDestination IS NOT NULL "
    "UNION ALL SELECT *, earliestTimeToSendToSource as minVal FROM AttributedPrivateClickMeasurement WHERE earliestTimeToSendToDestination IS NULL "
    "UNION ALL SELECT *, earliestTimeToSendToDestination as minVal FROM AttributedPrivateClickMeasurement WHERE earliestTimeToSendToSource IS NULL ORDER BY minVal"_s;
constexpr auto allUnattributedPrivateClickMeasurementAttributionsQuery = "SELECT * FROM UnattributedPrivateClickMeasurement"_s;
constexpr auto clearExpiredPrivateClickMeasurementQuery = "DELETE FROM UnattributedPrivateClickMeasurement WHERE ? > timeOfAdClick"_s;
constexpr auto markReportAsSentToSourceQuery = "UPDATE AttributedPrivateClickMeasurement SET earliestTimeToSendToSource = null WHERE sourceSiteDomainID = ? AND destinationSiteDomainID = ? AND sourceApplicationBundleID = ?"_s;
constexpr auto markReportAsSentToDestinationQuery = "UPDATE AttributedPrivateClickMeasurement SET earliestTimeToSendToDestination = null WHERE sourceSiteDomainID = ? AND destinationSiteDomainID = ? AND sourceApplicationBundleID = ?"_s;
constexpr auto earliestTimesToSendQuery = "SELECT earliestTimeToSendToSource, earliestTimeToSendToDestination FROM AttributedPrivateClickMeasurement WHERE sourceSiteDomainID = ? AND destinationSiteDomainID = ? AND sourceApplicationBundleID = ?"_s;
constexpr auto domainIDFromStringQuery = "SELECT domainID FROM PCMObservedDomains WHERE registrableDomain = ?"_s;
constexpr auto domainStringFromDomainIDQuery = "SELECT registrableDomain FROM PCMObservedDomains WHERE domainID = ?"_s;
constexpr auto createUnattributedPrivateClickMeasurement = "CREATE TABLE UnattributedPrivateClickMeasurement ("
    "sourceSiteDomainID INTEGER NOT NULL, destinationSiteDomainID INTEGER NOT NULL, sourceID INTEGER NOT NULL, "
    "timeOfAdClick REAL NOT NULL, token TEXT, signature TEXT, keyID TEXT, sourceApplicationBundleID TEXT, FOREIGN KEY(sourceSiteDomainID) "
    "REFERENCES PCMObservedDomains(domainID) ON DELETE CASCADE, FOREIGN KEY(destinationSiteDomainID) REFERENCES "
    "PCMObservedDomains(domainID) ON DELETE CASCADE)"_s;
constexpr auto createAttributedPrivateClickMeasurement = "CREATE TABLE AttributedPrivateClickMeasurement ("
    "sourceSiteDomainID INTEGER NOT NULL, destinationSiteDomainID INTEGER NOT NULL, sourceID INTEGER NOT NULL, "
    "attributionTriggerData INTEGER NOT NULL, priority INTEGER NOT NULL, timeOfAdClick REAL NOT NULL, "
    "earliestTimeToSendToSource REAL, token TEXT, signature TEXT, keyID TEXT, earliestTimeToSendToDestination REAL, sourceApplicationBundleID TEXT, "
    "destinationToken TEXT, destinationSignature TEXT, destinationKeyID TEXT, "
    "FOREIGN KEY(sourceSiteDomainID) REFERENCES PCMObservedDomains(domainID) ON DELETE CASCADE, FOREIGN KEY(destinationSiteDomainID) REFERENCES "
    "PCMObservedDomains(domainID) ON DELETE CASCADE)"_s;
constexpr auto createUniqueIndexUnattributedPrivateClickMeasurement = "CREATE UNIQUE INDEX IF NOT EXISTS UnattributedPrivateClickMeasurement_sourceSiteDomainID_destinationSiteDomainID_sourceApplicationBundleID on UnattributedPrivateClickMeasurement ( sourceSiteDomainID, destinationSiteDomainID, sourceApplicationBundleID )"_s;
constexpr auto createUniqueIndexAttributedPrivateClickMeasurement = "CREATE UNIQUE INDEX IF NOT EXISTS AttributedPrivateClickMeasurement_sourceSiteDomainID_destinationSiteDomainID_sourceApplicationBundleID on AttributedPrivateClickMeasurement ( sourceSiteDomainID, destinationSiteDomainID, sourceApplicationBundleID )"_s;
constexpr auto createPCMObservedDomain = "CREATE TABLE PCMObservedDomains ("
    "domainID INTEGER PRIMARY KEY, registrableDomain TEXT NOT NULL UNIQUE ON CONFLICT FAIL)"_s;
constexpr auto insertObservedDomainQuery = "INSERT INTO PCMObservedDomains (registrableDomain) VALUES (?)"_s;
constexpr auto clearAllPrivateClickMeasurementQuery = "DELETE FROM PCMObservedDomains WHERE domainID LIKE ?"_s;
#endif

static HashSet<Database*>& allDatabases()
{
    ASSERT(!RunLoop::isMain());
    static NeverDestroyed<HashSet<Database*>> set;
    return set;
}

Database::Database(const String& storageDirectory)
    : DatabaseUtilities(FileSystem::pathByAppendingComponent(storageDirectory, "pcm.db"_s))
{
    ASSERT(!RunLoop::isMain());
#if 0
    openDatabaseAndCreateSchemaIfNecessary();
    enableForeignKeys();
    addDestinationTokenColumnsIfNecessary();
#endif
    allDatabases().add(this);
}

Database::~Database()
{
    ASSERT(!RunLoop::isMain());
#if 0
    close();
#endif
    allDatabases().remove(this);
}

#if 0
const MemoryCompactLookupOnlyRobinHoodHashMap<String, TableAndIndexPair>& Database::expectedTableAndIndexQueries()
{
    static NeverDestroyed expectedTableAndIndexQueries = MemoryCompactLookupOnlyRobinHoodHashMap<String, TableAndIndexPair> {
        { "PCMObservedDomains"_s, std::make_pair<String, std::optional<String>>(createPCMObservedDomain, std::nullopt) },
        { "UnattributedPrivateClickMeasurement"_s, std::make_pair<String, std::optional<String>>(createUnattributedPrivateClickMeasurement, stripIndexQueryToMatchStoredValue(createUniqueIndexUnattributedPrivateClickMeasurement)) },
        { "AttributedPrivateClickMeasurement"_s, std::make_pair<String, std::optional<String>>(createAttributedPrivateClickMeasurement, stripIndexQueryToMatchStoredValue(createUniqueIndexAttributedPrivateClickMeasurement)) },
    };

    return expectedTableAndIndexQueries;
}
#endif

#if 0
std::span<const ASCIILiteral> Database::sortedTables()
{
    static std::array sortedTables {
        "PCMObservedDomains"_s,
        "UnattributedPrivateClickMeasurement"_s,
        "AttributedPrivateClickMeasurement"_s
    };

    return { sortedTables.data(), sortedTables.size() };
}
#endif

void Database::interruptAllDatabases()
{
    ASSERT(!RunLoop::isMain());
    for (auto database : allDatabases())
        database->interrupt();
}

#if 0
bool Database::createUniqueIndices()
{
    if (!m_database.executeCommand(createUniqueIndexUnattributedPrivateClickMeasurement)
        || !m_database.executeCommand(createUniqueIndexAttributedPrivateClickMeasurement)) {
        LOG_ERROR("Error creating indexes");
        return false;
    }
    return true;
}
#endif

#if 0
bool Database::createSchema()
{
    ASSERT(!RunLoop::isMain());

    if (!m_database.executeCommand(createPCMObservedDomain)) {
        LOG_ERROR("Could not create PCMObservedDomains table in database (%i) - %s", m_database.lastError(), m_database.lastErrorMsg());
        return false;
    }

    if (!m_database.executeCommand(createUnattributedPrivateClickMeasurement)) {
        LOG_ERROR("Could not create UnattributedPrivateClickMeasurement table in database (%i) - %s", m_database.lastError(), m_database.lastErrorMsg());
        return false;
    }

    if (!m_database.executeCommand(createAttributedPrivateClickMeasurement)) {
        LOG_ERROR("Could not create AttributedPrivateClickMeasurement table in database (%i) - %s", m_database.lastError(), m_database.lastErrorMsg());
        return false;
    }

    if (!m_database.executeCommand(createUniqueIndexUnattributedPrivateClickMeasurement)
        || !m_database.executeCommand(createUniqueIndexAttributedPrivateClickMeasurement)) {
        LOG_ERROR("Error creating indexes");
        return false;
    }
    return true;
}
#endif

void Database::insertPrivateClickMeasurement(WebCore::PrivateClickMeasurement&& attribution, PrivateClickMeasurementAttributionType attributionType)
{
    ASSERT(!RunLoop::isMain());

#if 0
    auto transactionScope = beginTransactionIfNecessary();

    auto sourceID = ensureDomainID(attribution.sourceSite().registrableDomain);
    auto attributionDestinationID = ensureDomainID(attribution.destinationSite().registrableDomain);
    if (!sourceID || !attributionDestinationID)
        return;

    auto& sourceSecretToken = attribution.sourceSecretToken();
    if (attributionType == PrivateClickMeasurementAttributionType::Attributed) {
        auto attributionTriggerData = attribution.attributionTriggerData() ? attribution.attributionTriggerData().value().data : -1;
        auto priority = attribution.attributionTriggerData() ? attribution.attributionTriggerData().value().priority : -1;
        auto sourceEarliestTimeToSend = attribution.timesToSend().sourceEarliestTimeToSend ? attribution.timesToSend().sourceEarliestTimeToSend.value().secondsSinceEpoch().value() : -1;
        auto destinationSecretToken = attribution.attributionTriggerData() ? attribution.attributionTriggerData().value().destinationSecretToken : std::nullopt;
        auto destinationEarliestTimeToSend = attribution.timesToSend().destinationEarliestTimeToSend ? attribution.timesToSend().destinationEarliestTimeToSend.value().secondsSinceEpoch().value() : -1;

        // We should never be inserting an attributed private click measurement value into the database without valid report times.
        ASSERT(sourceEarliestTimeToSend != -1 || destinationEarliestTimeToSend != -1);

        auto statement = m_database.prepareStatement(insertAttributedPrivateClickMeasurementQuery);
        if (!statement
            || statement->bindInt(1, *sourceID) != SQLITE_OK
            || statement->bindInt(2, *attributionDestinationID) != SQLITE_OK
            || statement->bindInt(3, attribution.sourceID()) != SQLITE_OK
            || statement->bindInt(4, attributionTriggerData) != SQLITE_OK
            || statement->bindInt(5, priority) != SQLITE_OK
            || statement->bindDouble(6, attribution.timeOfAdClick().secondsSinceEpoch().value()) != SQLITE_OK
            || statement->bindDouble(7, sourceEarliestTimeToSend) != SQLITE_OK
            || statement->bindText(8, sourceSecretToken ? sourceSecretToken->tokenBase64URL : emptyString()) != SQLITE_OK
            || statement->bindText(9, sourceSecretToken ? sourceSecretToken->signatureBase64URL : emptyString()) != SQLITE_OK
            || statement->bindText(10, sourceSecretToken ? sourceSecretToken->keyIDBase64URL : emptyString()) != SQLITE_OK
            || statement->bindDouble(11, destinationEarliestTimeToSend) != SQLITE_OK
            || statement->bindText(12, attribution.sourceApplicationBundleID()) != SQLITE_OK
            || statement->bindText(13, destinationSecretToken ? destinationSecretToken->tokenBase64URL : emptyString()) != SQLITE_OK
            || statement->bindText(14, destinationSecretToken ? destinationSecretToken->signatureBase64URL : emptyString()) != SQLITE_OK
            || statement->bindText(15, destinationSecretToken ? destinationSecretToken->keyIDBase64URL : emptyString()) != SQLITE_OK
            || statement->step() != SQLITE_DONE) {
            RELEASE_LOG_ERROR(PrivateClickMeasurement, "%p - Database::insertPrivateClickMeasurement insertAttributedPrivateClickMeasurementQuery, error message: %" PRIVATE_LOG_STRING, this, m_database.lastErrorMsg());
            ASSERT_NOT_REACHED();
        }
        return;
    }

    ASSERT(attributionType == PrivateClickMeasurementAttributionType::Unattributed);

    auto statement = m_database.prepareStatement(insertUnattributedPrivateClickMeasurementQuery);
    if (!statement
        || statement->bindInt(1, *sourceID) != SQLITE_OK
        || statement->bindInt(2, *attributionDestinationID) != SQLITE_OK
        || statement->bindInt(3, attribution.sourceID()) != SQLITE_OK
        || statement->bindDouble(4, attribution.timeOfAdClick().secondsSinceEpoch().value()) != SQLITE_OK
        || statement->bindText(5, sourceSecretToken ? sourceSecretToken->tokenBase64URL : emptyString()) != SQLITE_OK
        || statement->bindText(6, sourceSecretToken ? sourceSecretToken->signatureBase64URL : emptyString()) != SQLITE_OK
        || statement->bindText(7, sourceSecretToken ? sourceSecretToken->keyIDBase64URL : emptyString()) != SQLITE_OK
        || statement->bindText(8, attribution.sourceApplicationBundleID()) != SQLITE_OK
        || statement->step() != SQLITE_DONE) {
        RELEASE_LOG_ERROR(PrivateClickMeasurement, "%p - Database::insertPrivateClickMeasurement insertUnattributedPrivateClickMeasurementQuery, error message: %" PRIVATE_LOG_STRING, this, m_database.lastErrorMsg());
        ASSERT_NOT_REACHED();
    }
#endif

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

std::pair<std::optional<Database::UnattributedPrivateClickMeasurement>, std::optional<Database::AttributedPrivateClickMeasurement>> Database::findPrivateClickMeasurement(const WebCore::PCM::SourceSite& sourceSite, const WebCore::PCM::AttributionDestinationSite& destinationSite, const ApplicationBundleIdentifier& applicationBundleIdentifier)
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
        secondsUntilSend = previouslyUnattributed.value().attributeAndGetEarliestTimeToSend(WTFMove(attributionTriggerData), isRunningTest);

        if (!secondsUntilSend.hasValidSecondsUntilSendValues()) {
            ASSERT_NOT_REACHED();
            return { std::nullopt, WTFMove(debugInfo) };
        }

        RELEASE_LOG_INFO(PrivateClickMeasurement, "Converted a stored ad click with attribution trigger data: %u and priority: %u.", data, priority);
        debugInfo.messages.append({ MessageLevel::Info, makeString("[Private Click Measurement] Converted a stored ad click with attribution trigger data: '"_s, data, "' and priority: '"_s, priority, "'."_s) });

        if (!previouslyAttributed || previouslyUnattributed.value().hasHigherPriorityThan(*previouslyAttributed)) {
            insertPrivateClickMeasurement(WTFMove(*previouslyUnattributed), PrivateClickMeasurementAttributionType::Attributed);

            RELEASE_LOG_INFO(PrivateClickMeasurement, "Replaced a previously converted ad click with a new one with attribution data: %u and priority: %u because it had higher priority.", data, priority);
            debugInfo.messages.append({ MessageLevel::Info, makeString("[Private Click Measurement] Replaced a previously converted ad click with a new one with attribution trigger data: '"_s, data, "' and priority: '"_s, priority, "' because it had higher priority."_s) });
        }
    } else if (previouslyAttributed) {
        if (!previouslyAttributed.value().hasPreviouslyBeenReported()) {
            auto secondsUntilSend = previouslyAttributed.value().attributeAndGetEarliestTimeToSend(WTFMove(attributionTriggerData), isRunningTest);
            if (!secondsUntilSend.hasValidSecondsUntilSendValues())
                return { std::nullopt, WTFMove(debugInfo) };

            insertPrivateClickMeasurement(WTFMove(*previouslyAttributed), PrivateClickMeasurementAttributionType::Attributed);

            RELEASE_LOG_INFO(PrivateClickMeasurement, "Re-converted an ad click with a new one with attribution trigger data: %u and priority: %u because it had higher priority.", data, priority);
            debugInfo.messages.append({ MessageLevel::Info, makeString("[Private Click Measurement] Re-converted an ad click with a new one with attribution trigger data: '"_s, data, "' and priority: '"_s, priority, "'' because it had higher priority."_s) });
        }
    }

    if (!secondsUntilSend.hasValidSecondsUntilSendValues())
        return { std::nullopt, WTFMove(debugInfo) };

    return { secondsUntilSend, WTFMove(debugInfo) };
}

void Database::removeUnattributed(WebCore::PrivateClickMeasurement& attribution)
{
    ASSERT(!RunLoop::isMain());

#if 0
    auto sourceSiteDomainID = domainID(attribution.sourceSite().registrableDomain);
    auto destinationSiteDomainID = domainID(attribution.destinationSite().registrableDomain);
    if (!sourceSiteDomainID || !destinationSiteDomainID)
        return;

    auto scopedStatement = this->scopedStatement(m_removeUnattributedStatement, removeUnattributedQuery, "removeUnattributed"_s);

    if (!scopedStatement
        || scopedStatement->bindInt(1, *sourceSiteDomainID) != SQLITE_OK
        || scopedStatement->bindInt(2, *destinationSiteDomainID) != SQLITE_OK
        || scopedStatement->bindText(3, attribution.sourceApplicationBundleID()) != SQLITE_OK
        || scopedStatement->step() != SQLITE_DONE) {
        RELEASE_LOG_ERROR(PrivateClickMeasurement, "%p - Database::removeUnattributed, error message: %" PRIVATE_LOG_STRING, this, m_database.lastErrorMsg());
        ASSERT_NOT_REACHED();
    }
#endif

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

String Database::attributionToStringForTesting(const WebCore::PrivateClickMeasurement& pcm) const
{
    ASSERT(!RunLoop::isMain());
    auto sourceSiteDomain = pcm.sourceSite().registrableDomain;
    auto destinationSiteDomain = pcm.destinationSite().registrableDomain;
    auto sourceID = pcm.sourceID();

    StringBuilder builder;
    builder.append("Source site: ", sourceSiteDomain, "\nAttribute on site: ", destinationSiteDomain, "\nSource ID: ", sourceID);

    if (auto& triggerData = pcm.attributionTriggerData()) {
        auto attributionTriggerData = triggerData->data;
        auto priority = triggerData->priority;
        auto earliestTimeToSend = pcm.timesToSend().sourceEarliestTimeToSend;

        builder.append("\nAttribution trigger data: ", attributionTriggerData, "\nAttribution priority: ", priority, "\nAttribution earliest time to send: ");
        if (!earliestTimeToSend)
            builder.append("Not set");
        else {
            auto secondsUntilSend = *earliestTimeToSend - WallTime::now();
            builder.append((secondsUntilSend >= 24_h && secondsUntilSend <= 48_h) ? "Within 24-48 hours" : "Outside 24-48 hours");
        }

        builder.append("\nDestination token: ");
        if (!triggerData->destinationSecretToken)
            builder.append("Not set");
        else
            builder.append("\ntoken: ", triggerData->destinationSecretToken->tokenBase64URL, "\nsignature: ", triggerData->destinationSecretToken->signatureBase64URL, "\nkey: ", triggerData->destinationSecretToken->keyIDBase64URL);
    } else
        builder.append("\nNo attribution trigger data.");
    builder.append("\nApplication bundle identifier: ", pcm.sourceApplicationBundleID(), '\n');

    return builder.toString();
}

void Database::markAttributedPrivateClickMeasurementsAsExpiredForTesting()
{
    ASSERT(!RunLoop::isMain());
}

void Database::clearPrivateClickMeasurement(std::optional<WebCore::RegistrableDomain> domain)
{
    ASSERT(!RunLoop::isMain());
}

void Database::clearExpiredPrivateClickMeasurement()
{
    ASSERT(!RunLoop::isMain());
}

void Database::clearSentAttribution(WebCore::PrivateClickMeasurement&& attribution, WebCore::PCM::AttributionReportEndpoint attributionReportEndpoint)
{
    ASSERT(!RunLoop::isMain());
}

void Database::markReportAsSentToDestination(SourceDomainID sourceSiteDomainID, DestinationDomainID destinationSiteDomainID, const ApplicationBundleIdentifier& sourceApplicationBundleID)
{
    ASSERT(!RunLoop::isMain());
}

void Database::markReportAsSentToSource(SourceDomainID sourceSiteDomainID, DestinationDomainID destinationSiteDomainID, const ApplicationBundleIdentifier& sourceApplicationBundleID)
{
    ASSERT(!RunLoop::isMain());
}

std::pair<std::optional<Database::SourceEarliestTimeToSend>, std::optional<Database::DestinationEarliestTimeToSend>> Database::earliestTimesToSend(const WebCore::PrivateClickMeasurement& attribution)
{
    ASSERT(!RunLoop::isMain());
    return std::make_pair(std::nullopt, std::nullopt);
}

std::optional<Database::DomainID> Database::domainID(const WebCore::RegistrableDomain& domain)
{
    ASSERT(!RunLoop::isMain());
    return std::nullopt;
}

String Database::getDomainStringFromDomainID(DomainID domainID) const
{
    ASSERT(!RunLoop::isMain());
    return emptyString();
}

std::optional<Database::DomainID> Database::ensureDomainID(const WebCore::RegistrableDomain& domain)
{
    ASSERT(!RunLoop::isMain());
    return std::nullopt;
}

#if 0
void Database::destroyStatements()
{
    m_setUnattributedPrivateClickMeasurementAsExpiredStatement = nullptr;
    m_findUnattributedStatement = nullptr;
    m_findAttributedStatement = nullptr;
    m_removeUnattributedStatement = nullptr;
    m_allAttributedPrivateClickMeasurementStatement = nullptr;
    m_allUnattributedPrivateClickMeasurementAttributionsStatement = nullptr;
    m_clearAllPrivateClickMeasurementStatement = nullptr;
    m_clearExpiredPrivateClickMeasurementStatement = nullptr;
    m_earliestTimesToSendStatement = nullptr;
    m_markReportAsSentToSourceStatement = nullptr;
    m_markReportAsSentToDestinationStatement = nullptr;
    m_domainIDFromStringStatement = nullptr;
    m_domainStringFromDomainIDStatement = nullptr;
    m_insertObservedDomainStatement = nullptr;
}
#endif

#if 0
void Database::addDestinationTokenColumnsIfNecessary()
{
    constexpr auto attributedTableName = "AttributedPrivateClickMeasurement"_s;
    String destinationKeyIDColumnName("destinationKeyID"_s);
    auto columns = columnsForTable(attributedTableName);
    if (!columns.size() || columns.last() != destinationKeyIDColumnName) {
        addMissingColumnToTable(attributedTableName, "destinationToken TEXT"_s);
        addMissingColumnToTable(attributedTableName, "destinationSignature TEXT"_s);
        addMissingColumnToTable(attributedTableName, "destinationKeyID TEXT"_s);
    }
}
#endif

// Zawra stubs: SQLite code disabled
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

} // namespace WebKit::PCM
