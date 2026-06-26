/*
 * Copyright (C) 2022 Apple Inc. All rights reserved.
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
#include "PushDatabase.h"

#if ENABLE(SERVICE_WORKER)

#include "Logging.h"
#include "SecurityOrigin.h"
#include "ZPushBridge.h"
#include <iterator>
#include <wtf/CrossThreadCopier.h>
#include <wtf/Expected.h>
#include <wtf/FileSystem.h>
#include <wtf/RunLoop.h>
#include <wtf/Scope.h>
#include <wtf/UniqueRef.h>
#include <wtf/text/StringConcatenateNumbers.h>

#if 0
#include "SQLValue.h"
#include "SQLiteFileSystem.h"
#include "SQLiteTransaction.h"
#endif

#define PUSHDB_RELEASE_LOG(fmt, ...) RELEASE_LOG(Push, "%p - PushDatabase::" fmt, this, ##__VA_ARGS__)
#define PUSHDB_RELEASE_LOG_ERROR(fmt, ...) RELEASE_LOG_ERROR(Push, "%p - PushDatabase::" fmt, this, ##__VA_ARGS__)

#if 0
#define kPushRecordColumns " sub.rowID, ss.bundleID, ss.pushPartition, ss.dataStoreUUID, ss.securityOrigin, sub.scope, sub.endpoint, sub.topic, sub.serverVAPIDPublicKey, sub.clientPublicKey, sub.clientPrivateKey, sub.sharedAuthSecret, sub.expirationTime "

#define bindSubscriptionSetParameters(ss) \
    !(ss).bundleIdentifier.isNull() ? (ss).bundleIdentifier : emptyString(), \
    !(ss).pushPartition.isNull() ? (ss).pushPartition : emptyString(), \
    uuidToSpan((ss).dataStoreIdentifier)
#endif

namespace WebCore {

#if 0
static constexpr ASCIILiteral pushDatabaseSchemaV1Statements[] = {
    "PRAGMA auto_vacuum=INCREMENTAL"_s,
};

static constexpr ASCIILiteral pushDatabaseSchemaV2Statements[] = {
    "CREATE TABLE SubscriptionSets("
    "  rowID INTEGER PRIMARY KEY AUTOINCREMENT,"
    "  creationTime INT NOT NULL,"
    "  bundleID TEXT NOT NULL,"
    "  securityOrigin TEXT NOT NULL,"
    "  silentPushCount INT NOT NULL,"
    "  UNIQUE(bundleID, securityOrigin))"_s,
    "CREATE TABLE Subscriptions("
    "  rowID INTEGER PRIMARY KEY AUTOINCREMENT,"
    "  creationTime INT NOT NULL,"
    "  subscriptionSetID INT NOT NULL,"
    "  scope TEXT NOT NULL,"
    "  endpoint TEXT NOT NULL,"
    "  topic TEXT NOT NULL UNIQUE,"
    "  serverVAPIDPublicKey BLOB NOT NULL,"
    "  clientPublicKey BLOB NOT NULL,"
    "  clientPrivateKey BLOB NOT NULL,"
    "  sharedAuthSecret BLOB NOT NULL,"
    "  expirationTime INT,"
    "  UNIQUE(scope, subscriptionSetID))"_s,
    "CREATE INDEX Subscriptions_SubscriptionSetID_Index ON Subscriptions(subscriptionSetID)"_s,
};

static constexpr ASCIILiteral pushDatabaseSchemaV3Statements[] = {
    "CREATE TABLE Metadata(key TEXT, value, UNIQUE(key))"_s,
};

static constexpr ASCIILiteral pushDatabaseSchemaV4Statements[] = {
    "ALTER TABLE SubscriptionSets ADD COLUMN state INT NOT NULL DEFAULT 0"_s,
};

static constexpr ASCIILiteral pushDatabaseSchemaV5Statements[] = {
    "ALTER TABLE SubscriptionSets RENAME TO SubscriptionSetsOld"_s,
    "CREATE TABLE SubscriptionSets("
    "  rowID INTEGER PRIMARY KEY AUTOINCREMENT,"
    "  creationTime INT NOT NULL,"
    "  bundleID TEXT NOT NULL,"
    "  pushPartition TEXT NOT NULL,"
    "  dataStoreUUID BLOB NOT NULL,"
    "  securityOrigin TEXT NOT NULL,"
    "  silentPushCount INT NOT NULL,"
    "  state INT NOT NULL DEFAULT 0,"
    "  UNIQUE(bundleID, pushPartition, dataStoreUUID, securityOrigin))"_s,
    "INSERT INTO SubscriptionSets SELECT rowID, creationTime, bundleID, '', X'', securityOrigin, silentPushCount, state FROM SubscriptionSetsOld"_s,
    "DROP TABLE SubscriptionSetsOld"_s,
};

static constexpr std::span<const ASCIILiteral> pushDatabaseSchemaStatements[] = {
    { pushDatabaseSchemaV1Statements },
    { pushDatabaseSchemaV2Statements },
    { pushDatabaseSchemaV3Statements },
    { pushDatabaseSchemaV4Statements },
    { pushDatabaseSchemaV5Statements },
};

static constexpr int currentPushDatabaseVersion = std::size(pushDatabaseSchemaStatements);

static constexpr ASCIILiteral publicTokenKey = "publicToken"_s;
#endif

PushRecord PushRecord::isolatedCopy() const &
{
    return {
        identifier,
        subscriptionSetIdentifier.isolatedCopy(),
        securityOrigin.isolatedCopy(),
        scope.isolatedCopy(),
        endpoint.isolatedCopy(),
        topic.isolatedCopy(),
        serverVAPIDPublicKey,
        clientPublicKey,
        clientPrivateKey,
        sharedAuthSecret,
        expirationTime
    };
}

PushRecord PushRecord::isolatedCopy() &&
{
    return {
        identifier,
        WTFMove(subscriptionSetIdentifier).isolatedCopy(),
        WTFMove(securityOrigin).isolatedCopy(),
        WTFMove(scope).isolatedCopy(),
        WTFMove(endpoint).isolatedCopy(),
        WTFMove(topic).isolatedCopy(),
        WTFMove(serverVAPIDPublicKey),
        WTFMove(clientPublicKey),
        WTFMove(clientPrivateKey),
        WTFMove(sharedAuthSecret),
        expirationTime
    };
}

RemovedPushRecord RemovedPushRecord::isolatedCopy() const &
{
    return { identifier, topic.isolatedCopy(), serverVAPIDPublicKey };
}

RemovedPushRecord RemovedPushRecord::isolatedCopy() &&
{
    return { identifier, WTFMove(topic).isolatedCopy(), WTFMove(serverVAPIDPublicKey) };
}

PushTopics PushTopics::isolatedCopy() const &
{
    return { crossThreadCopy(enabledTopics), crossThreadCopy(ignoredTopics) };
}

PushTopics PushTopics::isolatedCopy() &&
{
    return { crossThreadCopy(WTFMove(enabledTopics)), crossThreadCopy(WTFMove(ignoredTopics)) };
}

#if 0
enum class ShouldDeleteAndRetry : bool { No, Yes };

static Expected<UniqueRef<SQLiteDatabase>, ShouldDeleteAndRetry> openAndMigrateDatabaseImpl(const String& path)
{
    ASSERT(!RunLoop::isMain());

    if (path != ":memory:"_s && !FileSystem::fileExists(path) && !FileSystem::makeAllDirectories(FileSystem::parentPath(path))) {
        RELEASE_LOG_ERROR(Push, "Couldn't create PushDatabase parent directories for path %s", path.utf8().data());
        return makeUnexpected(ShouldDeleteAndRetry::No);
    }

    auto db = WTF::makeUniqueRef<SQLiteDatabase>();
    db->disableThreadingChecks();

    if (!db->open(path)) {
        RELEASE_LOG_ERROR(Push, "Couldn't open PushDatabase at path %s", path.utf8().data());
        return makeUnexpected(ShouldDeleteAndRetry::Yes);
    }

    int version = 0;
    {
        auto sql = db->prepareStatement("PRAGMA user_version"_s);
        if (!sql || sql->step() != SQLITE_ROW) {
            RELEASE_LOG_ERROR(Push, "Couldn't get PushDatabase version at path %s", path.utf8().data());
            return makeUnexpected(ShouldDeleteAndRetry::Yes);
        }
        version = sql->columnInt(0);
    }

    if (version < 0 || version > currentPushDatabaseVersion) {
        RELEASE_LOG_ERROR(Push, "Found unexpected PushDatabase version: %d (expected: %d) at path: %s", version, currentPushDatabaseVersion, path.utf8().data());
        return makeUnexpected(ShouldDeleteAndRetry::Yes);
    }

    if (version < currentPushDatabaseVersion) {
        FileSystem::setExcludedFromBackup(FileSystem::parentPath(path), true);

        SQLiteTransaction transaction(db);
        transaction.begin();

        for (auto i = version; i < currentPushDatabaseVersion; i++) {
            for (auto statement : pushDatabaseSchemaStatements[i]) {
                if (!db->executeCommand(statement)) {
                    RELEASE_LOG_ERROR(Push, "Error executing PushDatabase DDL statement %s at path %s: %d", statement.characters(), path.utf8().data(), db->lastError());
                    return makeUnexpected(ShouldDeleteAndRetry::Yes);
                }
            }
        }

        if (!db->executeCommandSlow(makeString("PRAGMA user_version = ", currentPushDatabaseVersion)))
            RELEASE_LOG_ERROR(Push, "Error setting user version for PushDatabase at path %s: %d", path.utf8().data(), db->lastError());

        transaction.commit();
    }

    return db;
}

static std::unique_ptr<SQLiteDatabase> openAndMigrateDatabase(const String& path)
{
    ASSERT(!RunLoop::isMain());

    auto result = openAndMigrateDatabaseImpl(path);
    if (!result && result.error() == ShouldDeleteAndRetry::Yes) {
        if (path == SQLiteDatabase::inMemoryPath() || !SQLiteFileSystem::deleteDatabaseFile(path)) {
            RELEASE_LOG_ERROR(Push, "Failed to delete PushDatabase at path %s; bailing on recreating from scratch", path.utf8().data());
            return nullptr;
        }

        RELEASE_LOG_ERROR(Push, "Deleted PushDatabase at path %s and recreating from scratch", path.utf8().data());
        result = openAndMigrateDatabaseImpl(path);
    }

    if (!result)
        return nullptr;

    auto database = WTFMove(*result);
    return database.moveToUniquePtr();
}
#endif

void PushDatabase::create(const String& path, CreationHandler&& completionHandler)
{
    ASSERT(RunLoop::isMain());

    auto queue = WorkQueue::create("PushDatabase I/O Thread");
    queue->dispatch([queue, path = crossThreadCopy(path), completionHandler = WTFMove(completionHandler)]() mutable {
        UNUSED_PARAM(path);
#if 0
        auto database = openAndMigrateDatabase(path);
#endif
        WorkQueue::main().dispatch([queue = WTFMove(queue), completionHandler = WTFMove(completionHandler)]() mutable {
#if 0
            if (!database) {
                completionHandler(nullptr);
                return;
            }

            completionHandler(std::unique_ptr<PushDatabase>(new PushDatabase(WTFMove(queue), makeUniqueRefFromNonNullUniquePtr(WTFMove(database)))));
#else
            UNUSED_PARAM(queue);
            completionHandler(nullptr);
#endif
        });
    });
}

#if 0
PushDatabase::PushDatabase(Ref<WorkQueue>&& queue, UniqueRef<SQLiteDatabase>&& db)
    : m_queue(WTFMove(queue))
    , m_db(WTFMove(db))
{
}
#endif

PushDatabase::~PushDatabase()
{
    ASSERT(RunLoop::isMain());

    m_queue->dispatchSync([]() { });

#if 0
    m_queue->dispatchSync([db = WTFMove(m_db), statements = WTFMove(m_statements)]() mutable {
        statements.clear();
        db->close();
    });
#else
    m_queue->dispatchSync([]() { });
#endif
}

void PushDatabase::dispatchOnWorkQueue(Function<void()>&& function)
{
    RELEASE_ASSERT(RunLoop::isMain());
    m_queue->dispatch(WTFMove(function));
}

#if 0
SQLiteStatementAutoResetScope PushDatabase::cachedStatementOnQueue(ASCIILiteral query)
{
    ASSERT(!RunLoop::isMain());

    auto it = m_statements.find(query);
    if (it != m_statements.end())
        return SQLiteStatementAutoResetScope(it->value.ptr());

    auto result = m_db->prepareHeapStatement(query);
    if (!result) {
        PUSHDB_RELEASE_LOG_ERROR("Failed with %d preparing statement: %" PUBLIC_LOG_STRING, result.error(), query.characters());
        return SQLiteStatementAutoResetScope(nullptr);
    }

    auto ref = WTFMove(*result);
    auto statement = ref.ptr();
    m_statements.add(query, WTFMove(ref));
    return SQLiteStatementAutoResetScope(statement);
}

template<typename... Args>
WebCore::SQLiteStatementAutoResetScope PushDatabase::bindStatementOnQueue(ASCIILiteral query, Args&&... args)
{
    auto sql = cachedStatementOnQueue(query);
    if (!sql || !sql->bind(std::forward<Args>(args)...)) {
        PUSHDB_RELEASE_LOG_ERROR("Failed with %d (%" PUBLIC_LOG_STRING ") while binding statement: %" PUBLIC_LOG_STRING, m_db->lastError(), m_db->lastErrorMsg(), query.characters());
        return SQLiteStatementAutoResetScope(nullptr);
    }

    return sql;
}
#endif

static std::span<const uint8_t> uuidToSpan(const std::optional<WTF::UUID>& uuid)
{
    if (!uuid) {
        static const uint8_t junk = 0;
        return std::span(&junk, static_cast<size_t>(0));
    }

    return uuid->toSpan();
}

#if 0
static std::optional<WTF::UUID> uuidFromSpan(std::span<const uint8_t> span)
{
    if (span.size() != 16)
        return std::nullopt;

    return WTF::UUID(span.first<16>());
}

static SQLValue expirationTimeToValue(std::optional<EpochTimeStamp> timestamp)
{
    if (!timestamp)
        return nullptr;

    return convertEpochTimeStampToSeconds(*timestamp);
}

static std::optional<EpochTimeStamp> expirationTimeFromValue(SQLValue value)
{
    if (std::holds_alternative<double>(value))
        return convertSecondsToEpochTimeStamp(std::get<double>(value));

    return std::nullopt;
}
#endif

template <class T, class U>
static void completeOnMainQueue(CompletionHandler<void(T)>&& completionHandler, U&& result)
{
    ASSERT(!RunLoop::isMain());
    WorkQueue::main().dispatch([completionHandler = WTFMove(completionHandler), result = crossThreadCopy(std::forward<U>(result))]() mutable {
        completionHandler(WTFMove(result));
    });
}

static void computeOriginHash(const String& securityOrigin, uint64_t& hi, uint64_t& lo)
{
    auto utf8 = securityOrigin.utf8();
    uint64_t h = 0xcbf29ce484222325ULL;
    for (unsigned i = 0; i < utf8.length(); i++) {
        h ^= static_cast<uint8_t>(utf8.data()[i]);
        h *= 0x100000001b3ULL;
    }
    hi = h;
    lo = h ^ 0xdeadbeef;
}

void PushDatabase::updatePublicToken(std::span<const uint8_t> publicToken, CompletionHandler<void(PublicTokenChanged)>&& completionHandler)
{
    dispatchOnWorkQueue([this, newPublicToken = Vector<uint8_t> { publicToken }, completionHandler = WTFMove(completionHandler)]() mutable {
        UNUSED_PARAM(this);

        auto result = PublicTokenChanged::No;

#if 0
        SQLiteTransaction transaction(m_db);
        transaction.begin();

        Vector<uint8_t> currentPublicToken;
        auto scope = makeScopeExit([&completionHandler, &result] {
            completeOnMainQueue(WTFMove(completionHandler), result);
        });

        {
            auto sql = bindStatementOnQueue("SELECT value FROM Metadata WHERE key = ?"_s, publicTokenKey);
            if (!sql)
                return;

            if (sql->step() == SQLITE_ROW)
                currentPublicToken = sql->columnBlob(0);
        }

        if (currentPublicToken == newPublicToken)
            return;

        {
            auto sql = bindStatementOnQueue("REPLACE INTO Metadata(key, value) VALUES(?, ?)"_s, publicTokenKey, newPublicToken);
            if (!sql || sql->step() != SQLITE_DONE)
                return;
        }

        if (!currentPublicToken.isEmpty()) {
            auto deleteSubscriptionSets = cachedStatementOnQueue("DELETE FROM SubscriptionSets"_s);
            auto deleteSubscriptions = cachedStatementOnQueue("DELETE FROM Subscriptions"_s);

            if (!deleteSubscriptionSets || !deleteSubscriptions || deleteSubscriptionSets->step() != SQLITE_DONE || deleteSubscriptions->step() != SQLITE_DONE)
                return;

            ZPushBridge::deleteAll();

            result = PublicTokenChanged::Yes;
        }

        scope.release();
        transaction.commit();
        completeOnMainQueue(WTFMove(completionHandler), result);
#else
        UNUSED_PARAM(newPublicToken);
        ZPushBridge::deleteAll();
        result = PublicTokenChanged::Yes;
        completeOnMainQueue(WTFMove(completionHandler), result);
#endif
    });
}

void PushDatabase::getPublicToken(CompletionHandler<void(Vector<uint8_t>&&)>&& completionHandler)
{
    dispatchOnWorkQueue([this, completionHandler = WTFMove(completionHandler)]() mutable {
        UNUSED_PARAM(this);
#if 0
        SQLiteTransaction transaction(m_db);
        transaction.begin();

        auto sql = bindStatementOnQueue("SELECT value FROM Metadata WHERE key = ?"_s, publicTokenKey);
        if (!sql)
            return completeOnMainQueue(WTFMove(completionHandler), Vector<uint8_t> { });

        Vector<uint8_t> result;
        if (sql->step() == SQLITE_ROW)
            result = sql->columnBlob(0);

        transaction.commit();
        completeOnMainQueue(WTFMove(completionHandler), WTFMove(result));
#else
        completeOnMainQueue(WTFMove(completionHandler), Vector<uint8_t> { });
#endif
    });
}

void PushDatabase::insertRecord(const PushRecord& record, CompletionHandler<void(std::optional<PushRecord>&&)>&& completionHandler)
{
    dispatchOnWorkQueue([this, record = crossThreadCopy(record), completionHandler = WTFMove(completionHandler)]() mutable {
        UNUSED_PARAM(this);

#if 0
        SQLiteTransaction transaction(m_db);
        transaction.begin();

        int64_t subscriptionSetID = 0;

        {
            auto sql = bindStatementOnQueue(
                "SELECT rowID FROM SubscriptionSets WHERE bundleID = ? AND pushPartition = ? AND dataStoreUUID = ? AND securityOrigin = ?"_s,
                bindSubscriptionSetParameters(record.subscriptionSetIdentifier),
                record.securityOrigin);
            if (!sql)
                return completeOnMainQueue(WTFMove(completionHandler), std::optional<PushRecord> { });

            if (sql->step() == SQLITE_ROW)
                subscriptionSetID = sql->columnInt64(0);
        }

        if (!subscriptionSetID) {
            auto sql = bindStatementOnQueue(
                "INSERT INTO SubscriptionSets VALUES(NULL, ?, ?, ?, ?, ?, 0, 0)"_s,
                time(nullptr),
                bindSubscriptionSetParameters(record.subscriptionSetIdentifier),
                record.securityOrigin);
            if (!sql || sql->step() != SQLITE_DONE)
                return completeOnMainQueue(WTFMove(completionHandler), std::optional<PushRecord> { });

            subscriptionSetID = m_db->lastInsertRowID();
        }

        {
            auto sql = bindStatementOnQueue(
                "INSERT INTO Subscriptions VALUES(NULL, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"_s,
                time(nullptr),
                subscriptionSetID,
                record.scope,
                record.endpoint,
                record.topic,
                record.serverVAPIDPublicKey,
                record.clientPublicKey,
                record.clientPrivateKey,
                record.sharedAuthSecret,
                expirationTimeToValue(record.expirationTime));
            if (!sql || sql->step() != SQLITE_DONE)
                return completeOnMainQueue(WTFMove(completionHandler), std::optional<PushRecord> { });

            record.identifier = ObjectIdentifier<PushSubscriptionIdentifierType>(m_db->lastInsertRowID());
        }

        transaction.commit();
#endif

        uint64_t originHi = 0, originLo = 0;
        computeOriginHash(record.securityOrigin, originHi, originLo);
        auto endpointUtf8 = record.endpoint.utf8();
        ZPushBridge::storeSubscription(originHi, originLo,
            reinterpret_cast<const uint8_t*>(endpointUtf8.data()), endpointUtf8.length(),
            record.clientPublicKey.data(), record.clientPublicKey.size(),
            record.sharedAuthSecret.data(), record.sharedAuthSecret.size());

        completeOnMainQueue(WTFMove(completionHandler), WTFMove(record));
    });
}

void PushDatabase::removeRecordByIdentifier(PushSubscriptionIdentifier identifier, CompletionHandler<void(bool)>&& completionHandler)
{
    dispatchOnWorkQueue([this, rowIdentifier = identifier.toUInt64(), completionHandler = WTFMove(completionHandler)]() mutable {
        UNUSED_PARAM(this);
        UNUSED_PARAM(rowIdentifier);
#if 0
        SQLiteTransaction transaction(m_db);
        transaction.begin();

        bool isLastSubscriptionInSet = false;
        int64_t subscriptionSetID = 0;

        {
            auto sql = bindStatementOnQueue("SELECT subscriptionSetID FROM Subscriptions WHERE rowid = ?"_s, rowIdentifier);
            if (!sql || sql->step() != SQLITE_ROW)
                return completeOnMainQueue(WTFMove(completionHandler), false);

            subscriptionSetID = sql->columnInt(0);
        }

        {
            auto sql = bindStatementOnQueue("DELETE FROM Subscriptions WHERE rowid = ?"_s, rowIdentifier);
            if (!sql || sql->step() != SQLITE_DONE)
                return completeOnMainQueue(WTFMove(completionHandler), false);
        }

        {
            auto sql = bindStatementOnQueue("SELECT rowid FROM Subscriptions WHERE subscriptionSetID = ?"_s, subscriptionSetID);
            if (!sql)
                return completeOnMainQueue(WTFMove(completionHandler), false);

            isLastSubscriptionInSet = (sql->step() == SQLITE_DONE);
        }

        if (isLastSubscriptionInSet) {
            auto sql = bindStatementOnQueue("DELETE FROM SubscriptionSets WHERE rowid = ?"_s, subscriptionSetID);
            if (!sql || sql->step() != SQLITE_DONE)
                return completeOnMainQueue(WTFMove(completionHandler), false);
        }

        transaction.commit();

        completeOnMainQueue(WTFMove(completionHandler), true);
#else
        completeOnMainQueue(WTFMove(completionHandler), true);
#endif
    });
}

#if 0
static PushRecord makePushRecordFromRow(SQLiteStatementAutoResetScope& sql, int columnIndex)
{
    return PushRecord {
        .identifier = ObjectIdentifier<PushSubscriptionIdentifierType>(sql->columnInt64(columnIndex)),
        .subscriptionSetIdentifier = {
            .bundleIdentifier = sql->columnText(columnIndex + 1),
            .pushPartition = sql->columnText(columnIndex + 2),
            .dataStoreIdentifier = uuidFromSpan(sql->columnBlobAsSpan(columnIndex + 3))
        },
        .securityOrigin = sql->columnText(columnIndex + 4),
        .scope = sql->columnText(columnIndex + 5),
        .endpoint = sql->columnText(columnIndex + 6),
        .topic = sql->columnText(columnIndex + 7),
        .serverVAPIDPublicKey = sql->columnBlob(columnIndex + 8),
        .clientPublicKey = sql->columnBlob(columnIndex + 9),
        .clientPrivateKey = sql->columnBlob(columnIndex + 10),
        .sharedAuthSecret = sql->columnBlob(columnIndex + 11),
        .expirationTime = expirationTimeFromValue(sql->columnValue(columnIndex + 12))
    };
}
#endif

void PushDatabase::getRecordByTopic(const String& topic, CompletionHandler<void(std::optional<PushRecord>&&)>&& completionHandler)
{
    dispatchOnWorkQueue([this, topic = crossThreadCopy(topic), completionHandler = WTFMove(completionHandler)]() mutable {
        UNUSED_PARAM(this);
        UNUSED_PARAM(topic);
#if 0
        auto sql = bindStatementOnQueue(
            "SELECT " kPushRecordColumns
            "FROM Subscriptions sub "
            "CROSS JOIN SubscriptionSets ss "
            "ON sub.subscriptionSetID = ss.rowid "
            "WHERE sub.topic = ?"_s, topic);
        if (!sql || sql->step() != SQLITE_ROW)
            return completeOnMainQueue(WTFMove(completionHandler), std::optional<PushRecord> { });

        completeOnMainQueue(WTFMove(completionHandler), makePushRecordFromRow(sql, 0));
#else
        completeOnMainQueue(WTFMove(completionHandler), std::optional<PushRecord> { });
#endif
    });
}

void PushDatabase::getRecordBySubscriptionSetAndScope(const PushSubscriptionSetIdentifier& subscriptionSetIdentifier, const String& scope, CompletionHandler<void(std::optional<PushRecord>&&)>&& completionHandler)
{
    dispatchOnWorkQueue([this, subscriptionSetIdentifier = crossThreadCopy(subscriptionSetIdentifier), scope = crossThreadCopy(scope), completionHandler = WTFMove(completionHandler)]() mutable {
        UNUSED_PARAM(this);
        UNUSED_PARAM(subscriptionSetIdentifier);
        UNUSED_PARAM(scope);
#if 0
        auto sql = bindStatementOnQueue(
            "SELECT " kPushRecordColumns
            "FROM Subscriptions sub "
            "CROSS JOIN SubscriptionSets ss "
            "ON sub.subscriptionSetID = ss.rowid "
            "WHERE sub.scope = ? AND ss.bundleID = ? AND ss.pushPartition = ? AND ss.dataStoreUUID = ?"_s,
            scope,
            bindSubscriptionSetParameters(subscriptionSetIdentifier));
        if (!sql || sql->step() != SQLITE_ROW)
            return completeOnMainQueue(WTFMove(completionHandler), std::optional<PushRecord> { });

        completeOnMainQueue(WTFMove(completionHandler), makePushRecordFromRow(sql, 0));
#else
        completeOnMainQueue(WTFMove(completionHandler), std::optional<PushRecord> { });
#endif
    });
}

void PushDatabase::getIdentifiers(CompletionHandler<void(HashSet<PushSubscriptionIdentifier>&&)>&& completionHandler)
{
    dispatchOnWorkQueue([this, completionHandler = WTFMove(completionHandler)]() mutable {
        UNUSED_PARAM(this);
#if 0
        HashSet<PushSubscriptionIdentifier> result;
        auto sql = cachedStatementOnQueue("SELECT rowid FROM Subscriptions"_s);
        while (sql && sql->step() == SQLITE_ROW)
            result.add(ObjectIdentifier<PushSubscriptionIdentifierType>(sql->columnInt64(0)));

        completeOnMainQueue(WTFMove(completionHandler), WTFMove(result));
#else
        HashSet<PushSubscriptionIdentifier> result;
        completeOnMainQueue(WTFMove(completionHandler), WTFMove(result));
#endif
    });
}

void PushDatabase::getTopics(CompletionHandler<void(PushTopics&&)>&& completionHandler)
{
    dispatchOnWorkQueue([this, completionHandler = WTFMove(completionHandler)]() mutable {
        UNUSED_PARAM(this);
#if 0
        PushTopics topics;

        auto sql = cachedStatementOnQueue(
            "SELECT sub.topic, ss.state "
            "FROM Subscriptions sub "
            "JOIN SubscriptionSets ss "
            "ON sub.subscriptionSetID = ss.rowid"_s);
        if (!sql)
            return completeOnMainQueue(WTFMove(completionHandler), topics);

        while (sql->step() == SQLITE_ROW) {
            switch (static_cast<SubscriptionSetState>(sql->columnInt(1))) {
            case SubscriptionSetState::Enabled:
                topics.enabledTopics.append(sql->columnText(0));
                break;
            case SubscriptionSetState::Ignored:
                topics.ignoredTopics.append(sql->columnText(0));
                break;
            }
        }

        completeOnMainQueue(WTFMove(completionHandler), WTFMove(topics));
#else
        PushTopics topics;
        completeOnMainQueue(WTFMove(completionHandler), WTFMove(topics));
#endif
    });
}

void PushDatabase::incrementSilentPushCount(const PushSubscriptionSetIdentifier& subscriptionSetIdentifier, const String& securityOrigin, CompletionHandler<void(unsigned)>&& completionHandler)
{
    dispatchOnWorkQueue([this, subscriptionSetIdentifier = crossThreadCopy(subscriptionSetIdentifier), securityOrigin = crossThreadCopy(securityOrigin), completionHandler = WTFMove(completionHandler)]() mutable {
        UNUSED_PARAM(this);
        UNUSED_PARAM(subscriptionSetIdentifier);
        UNUSED_PARAM(securityOrigin);
#if 0
        int silentPushCount = 0;
        SQLiteTransaction transaction(m_db);
        transaction.begin();

        {
            auto sql = bindStatementOnQueue(
                "UPDATE SubscriptionSets "
                "SET silentPushCount = silentPushCount + 1 "
                "WHERE bundleID = ? AND pushPartition = ? AND dataStoreUUID = ? AND securityOrigin = ?"_s,
                bindSubscriptionSetParameters(subscriptionSetIdentifier),
                securityOrigin);
            if (!sql || sql->step() != SQLITE_DONE)
                return completeOnMainQueue(WTFMove(completionHandler), 0u);
        }

        {
            auto sql = bindStatementOnQueue(
                "SELECT silentPushCount "
                "FROM SubscriptionSets "
                "WHERE bundleID = ? AND pushPartition = ? AND dataStoreUUID = ? AND securityOrigin = ?"_s,
                bindSubscriptionSetParameters(subscriptionSetIdentifier),
                securityOrigin);
            if (!sql || sql->step() != SQLITE_ROW)
                return completeOnMainQueue(WTFMove(completionHandler), 0u);

            silentPushCount = sql->columnInt(0);
        }

        transaction.commit();

        completeOnMainQueue(WTFMove(completionHandler), silentPushCount);
#else
        completeOnMainQueue(WTFMove(completionHandler), 0u);
#endif
    });
}

void PushDatabase::removeRecordsBySubscriptionSet(const PushSubscriptionSetIdentifier& subscriptionSetIdentifier, CompletionHandler<void(Vector<RemovedPushRecord>&&)>&& completionHandler)
{
    dispatchOnWorkQueue([this, subscriptionSetIdentifier = crossThreadCopy(subscriptionSetIdentifier), completionHandler = WTFMove(completionHandler)]() mutable {
        UNUSED_PARAM(this);

        auto scope = makeScopeExit([&completionHandler] {
            completeOnMainQueue(WTFMove(completionHandler), Vector<RemovedPushRecord> { });
        });

        Vector<RemovedPushRecord> removedPushRecords;
        Vector<String> securityOriginsToDelete;

#if 0
        SQLiteTransaction transaction(m_db);
        transaction.begin();

        {
            auto sql = bindStatementOnQueue(
                "SELECT DISTINCT ss.securityOrigin "
                "FROM SubscriptionSets ss "
                "WHERE ss.bundleID = ? AND ss.pushPartition = ? AND ss.dataStoreUUID = ?"_s,
                bindSubscriptionSetParameters(subscriptionSetIdentifier));
            if (sql) {
                while (sql->step() == SQLITE_ROW)
                    securityOriginsToDelete.append(sql->columnText(0));
            }
        }

        {
            auto sql = bindStatementOnQueue(
                "SELECT sub.subscriptionSetID, sub.rowid, sub.topic, sub.serverVAPIDPublicKey "
                "FROM SubscriptionSets ss "
                "JOIN Subscriptions sub "
                "ON ss.rowid = sub.subscriptionSetID "
                "WHERE ss.bundleID = ? AND ss.pushPartition = ? AND ss.dataStoreUUID = ?"_s,
                bindSubscriptionSetParameters(subscriptionSetIdentifier));
            if (!sql)
                return;

            while (sql->step() == SQLITE_ROW) {
                auto identifier = ObjectIdentifier<PushSubscriptionIdentifierType>(sql->columnInt(1));
                auto topic = sql->columnText(2);
                auto serverVAPIDPublicKey = sql->columnBlob(3);
                removedPushRecords.append({ identifier, WTFMove(topic), WTFMove(serverVAPIDPublicKey) });
            }
        }

        {
            auto sql = bindStatementOnQueue(
                "DELETE FROM Subscriptions "
                "WHERE subscriptionSetID IN ("
                "    SELECT rowid FROM SubscriptionSets "
                "    WHERE bundleID = ? AND pushPartition = ? AND dataStoreUUID = ? "
                ")"_s,
                bindSubscriptionSetParameters(subscriptionSetIdentifier));
            if (!sql || sql->step() != SQLITE_DONE)
                return;
        }

        {
            auto sql = bindStatementOnQueue(
                "DELETE FROM SubscriptionSets "
                "WHERE bundleID = ? AND pushPartition = ? AND dataStoreUUID = ?"_s,
                bindSubscriptionSetParameters(subscriptionSetIdentifier));
            if (!sql || sql->step() != SQLITE_DONE)
                return;
        }

        transaction.commit();
#endif

        for (const auto& securityOrigin : securityOriginsToDelete) {
            uint64_t originHi = 0, originLo = 0;
            computeOriginHash(securityOrigin, originHi, originLo);
            ZPushBridge::deleteSubscription(originHi, originLo);
        }

        if (securityOriginsToDelete.isEmpty())
            ZPushBridge::deleteAll();

        scope.release();
        completeOnMainQueue(WTFMove(completionHandler), WTFMove(removedPushRecords));
    });
}


void PushDatabase::removeRecordsBySubscriptionSetAndSecurityOrigin(const PushSubscriptionSetIdentifier& subscriptionSetIdentifier, const String& securityOrigin, CompletionHandler<void(Vector<RemovedPushRecord>&&)>&& completionHandler)
{
    dispatchOnWorkQueue([this, subscriptionSetIdentifier = crossThreadCopy(subscriptionSetIdentifier), securityOrigin = crossThreadCopy(securityOrigin), completionHandler = WTFMove(completionHandler)]() mutable {
        UNUSED_PARAM(this);

        auto scope = makeScopeExit([&completionHandler] {
            completeOnMainQueue(WTFMove(completionHandler), Vector<RemovedPushRecord> { });
        });

        Vector<RemovedPushRecord> removedPushRecords;

#if 0
        SQLiteTransaction transaction(m_db);
        transaction.begin();

        int64_t subscriptionSetID = 0;

        {
            auto sql = bindStatementOnQueue(
                "SELECT sub.subscriptionSetID, sub.rowid, sub.topic, sub.serverVAPIDPublicKey "
                "FROM SubscriptionSets ss "
                "JOIN Subscriptions sub "
                "ON ss.rowid = sub.subscriptionSetID "
                "WHERE ss.bundleID = ? AND ss.pushPartition = ? AND ss.dataStoreUUID = ? AND ss.securityOrigin = ?"_s,
                bindSubscriptionSetParameters(subscriptionSetIdentifier),
                securityOrigin);
            if (!sql)
                return;

            while (sql->step() == SQLITE_ROW) {
                subscriptionSetID = sql->columnInt(0);
                auto identifier = ObjectIdentifier<PushSubscriptionIdentifierType>(sql->columnInt(1));
                auto topic = sql->columnText(2);
                auto serverVAPIDPublicKey = sql->columnBlob(3);
                removedPushRecords.append({ identifier, WTFMove(topic), WTFMove(serverVAPIDPublicKey) });
            }
        }

        {
            auto sql = bindStatementOnQueue("DELETE FROM Subscriptions WHERE subscriptionSetID = ?"_s, subscriptionSetID);
            if (!sql || sql->step() != SQLITE_DONE)
                return;
        }

        {
            auto sql = bindStatementOnQueue("DELETE FROM SubscriptionSets WHERE rowid = ?"_s, subscriptionSetID);
            if (!sql || sql->step() != SQLITE_DONE)
                return;
        }

        transaction.commit();
#endif

        {
            uint64_t originHi = 0, originLo = 0;
            computeOriginHash(securityOrigin, originHi, originLo);
            ZPushBridge::deleteSubscription(originHi, originLo);
        }

        scope.release();
        completeOnMainQueue(WTFMove(completionHandler), WTFMove(removedPushRecords));
    });
}

void PushDatabase::setPushesEnabledForOrigin(const PushSubscriptionSetIdentifier& subscriptionSetIdentifier, const String& securityOrigin, bool enabled, CompletionHandler<void(bool recordsChanged)>&& completionHandler)
{
    dispatchOnWorkQueue([this, subscriptionSetIdentifier = crossThreadCopy(subscriptionSetIdentifier), securityOrigin = crossThreadCopy(securityOrigin), enabled, completionHandler = WTFMove(completionHandler)]() mutable {
        UNUSED_PARAM(this);
        UNUSED_PARAM(subscriptionSetIdentifier);
        UNUSED_PARAM(securityOrigin);
        UNUSED_PARAM(enabled);

        auto scope = makeScopeExit([&completionHandler] {
            completeOnMainQueue(WTFMove(completionHandler), false);
        });

#if 0
        SQLiteTransaction transaction(m_db);
        transaction.begin();

        int64_t subscriptionSetID = 0;
        auto newState = enabled ? SubscriptionSetState::Enabled : SubscriptionSetState::Ignored;

        {
            auto sql = bindStatementOnQueue(
                "SELECT rowid, state "
                "FROM SubscriptionSets "
                "WHERE bundleID = ? AND pushPartition = ? AND dataStoreUUID = ? AND securityOrigin = ?"_s,
                bindSubscriptionSetParameters(subscriptionSetIdentifier),
                securityOrigin);
            if (!sql || sql->step() != SQLITE_ROW || static_cast<SubscriptionSetState>(sql->columnInt(1)) == newState)
                return;

            subscriptionSetID = sql->columnInt64(0);
        }

        {
            auto sql = bindStatementOnQueue("UPDATE SubscriptionSets SET state = ? WHERE rowid = ?"_s, static_cast<int>(newState), subscriptionSetID);
            if (!sql || sql->step() != SQLITE_DONE)
                return;
        }

        transaction.commit();
#endif

        scope.release();
        completeOnMainQueue(WTFMove(completionHandler), true);
    });
}

} // namespace WebCore

#endif // ENABLE(SERVICE_WORKER)
