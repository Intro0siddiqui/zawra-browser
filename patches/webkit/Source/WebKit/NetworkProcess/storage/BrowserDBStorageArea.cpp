/*
 * Copyright (C) 2008-2021 Apple Inc. All rights reserved.
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
#include "BrowserDBStorageArea.h"

#include "Logging.h"
#include <WebCore/ZawraStorageBridge.h>

namespace WebKit {

constexpr unsigned maximumSizeForValuesKeptInMemory { 1 * KB };

BrowserDBStorageArea::BrowserDBStorageArea(unsigned quota, const WebCore::ClientOrigin& origin, Ref<WorkQueue>&& workQueue)
    : StorageAreaBase(quota, origin)
    , m_queue(WTFMove(workQueue))
{
    ASSERT(!isMainRunLoop());
    WebCore::ZSB::hashString(origin.clientOrigin.databaseIdentifier(), m_originHashHi, m_originHashLo);
}

void BrowserDBStorageArea::close()
{
    m_cache = std::nullopt;
    m_cacheSize = std::nullopt;
}

bool BrowserDBStorageArea::isEmpty()
{
    if (m_cache)
        return m_cache->isEmpty();
    auto items = allItems();
    return items.isEmpty();
}

void BrowserDBStorageArea::clear()
{
    ASSERT(!isMainRunLoop());

    close();
    WebCore::ZSB::clearData(m_originHashHi, m_originHashLo);
    notifyListenersAboutClear();
}

Expected<String, StorageError> BrowserDBStorageArea::getItem(const String& key)
{
    if (m_cache) {
        auto iterator = m_cache->find(key);
        if (iterator == m_cache->end())
            return makeUnexpected(StorageError::ItemNotFound);

        if (auto* valueString = std::get_if<String>(&iterator->value)) {
            ASSERT(!valueString->isNull());
            return *valueString;
        }
    }

    return getItemFromDatabase(key);
}

Expected<String, StorageError> BrowserDBStorageArea::getItemFromDatabase(const String& key)
{
    return WebCore::ZSB::getData(m_originHashHi, m_originHashLo, key);
}

HashMap<String, String> BrowserDBStorageArea::allItems()
{
    ASSERT(!isMainRunLoop());

    HashMap<String, String> items = WebCore::ZSB::getAllData(m_originHashHi, m_originHashLo);

    m_cache = HashMap<String, Value> { };
    m_cacheSize = 0;

    for (auto& item : items) {
        updateCacheIfNeeded(item.key, item.value);
    }

    return items;
}

Expected<void, StorageError> BrowserDBStorageArea::setItem(IPC::Connection::UniqueID connection, StorageAreaImplIdentifier storageAreaImplID, String&& key, String&& value, const String& urlString)
{
    ASSERT(!isMainRunLoop());

    if (!requestSpace(key, value))
        return makeUnexpected(StorageError::QuotaExceeded);

    String oldValue;
    if (auto valueOrError = getItem(key))
        oldValue = valueOrError.value();

    WebCore::ZSB::storeDataWithTTL(m_originHashHi, m_originHashLo, key, value, 0);

    dispatchEvents(connection, storageAreaImplID, key, oldValue, value, urlString);
    updateCacheIfNeeded(key, value);

    return { };
}

Expected<void, StorageError> BrowserDBStorageArea::removeItem(IPC::Connection::UniqueID connection, StorageAreaImplIdentifier storageAreaImplID, const String& key, const String& urlString)
{
    ASSERT(!isMainRunLoop());

    String oldValue;
    if (auto valueOrError = getItem(key))
        oldValue = valueOrError.value();
    else
        return makeUnexpected(StorageError::ItemNotFound);

    WebCore::ZSB::removeData(m_originHashHi, m_originHashLo, key);

    dispatchEvents(connection, storageAreaImplID, key, oldValue, String(), urlString);
    updateCacheIfNeeded(key, { });

    return { };
}

Expected<void, StorageError> BrowserDBStorageArea::clear(IPC::Connection::UniqueID connection, StorageAreaImplIdentifier storageAreaImplID, const String& urlString)
{
    ASSERT(!isMainRunLoop());

    if (m_cache && m_cache->isEmpty())
        return makeUnexpected(StorageError::ItemNotFound);

    if (m_cache) {
        m_cache->clear();
        m_cacheSize = 0;
    }

    WebCore::ZSB::clearData(m_originHashHi, m_originHashLo);

    dispatchEvents(connection, storageAreaImplID, String(), String(), String(), urlString);

    return { };
}

void BrowserDBStorageArea::commitTransactionIfNecessary()
{
}

void BrowserDBStorageArea::handleLowMemoryWarning()
{
    m_cache = std::nullopt;
    m_cacheSize = std::nullopt;
}

void BrowserDBStorageArea::updateCacheIfNeeded(const String& key, const String& value)
{
    if (!m_cache)
        return;

    ASSERT(m_cacheSize);
    auto iter = m_cache->find(key);
    bool itemExists = iter != m_cache->end();
    unsigned oldKeySize = 0;
    unsigned oldValueSize = 0;
    unsigned keySize = key.sizeInBytes();
    unsigned valueSize = value.sizeInBytes();
    if (itemExists) {
        oldKeySize = iter->key.sizeInBytes();
        WTF::switchOn(iter->value, [&](unsigned valueSize) {
            oldValueSize = valueSize;
        }, [&](const String& value) {
            oldValueSize = value.sizeInBytes();
        });
    }

    CheckedUint32 newCacheSize = *m_cacheSize;
    if (value.isNull()) {
        m_cache->remove(key);
        newCacheSize -= oldKeySize;
        newCacheSize -= oldValueSize;
    } else {
        if (valueSize > maximumSizeForValuesKeptInMemory)
            m_cache->set(key, valueSize);
        else
            m_cache->set(key, value);
        newCacheSize -= oldKeySize;
        newCacheSize -= oldValueSize;
        newCacheSize += itemExists ? oldKeySize : keySize;
        newCacheSize += valueSize;
    }

    if (newCacheSize.hasOverflowed()) {
        RELEASE_LOG_ERROR(Storage, "BrowserDBStorageArea::updateCacheIfNeeded newCacheSize has overflowed: cacheSize - %u, oldKeySize - %u, oldValueSize - %u, keySize - %u, valueSize - %u, will recompute", *m_cacheSize, oldKeySize, oldValueSize, keySize, valueSize);
        newCacheSize = 0;
        for (auto& value : m_cache->values()) {
            WTF::switchOn(value, [&](unsigned size) {
                newCacheSize += size;
            }, [&](const String& value) {
                newCacheSize += value.sizeInBytes();
            });
        }
    }

    m_cacheSize = newCacheSize;
}

bool BrowserDBStorageArea::requestSpace(const String& key, const String& value)
{
    if (!m_cache)
        return key.sizeInBytes() + value.sizeInBytes() <= quota();
    if (value.isNull())
        return true;
    CheckedUint32 newCacheSize = *m_cacheSize;
    auto iter = m_cache->find(key);
    if (iter == m_cache->end())
        newCacheSize += key.sizeInBytes();
    else {
        auto oldValueSize = WTF::switchOn(iter->value, [](unsigned valueSize) {
            return valueSize;
        }, [](const String& value) {
            return value.sizeInBytes();
        });
        newCacheSize -= oldValueSize;
    }
    newCacheSize += value.sizeInBytes();
    if (newCacheSize.hasOverflowed())
        return false;
    return newCacheSize <= quota();
}

} // namespace WebKit
