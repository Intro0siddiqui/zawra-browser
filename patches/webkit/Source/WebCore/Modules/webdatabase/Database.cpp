/*
 * Copyright (C) 2007, 2008, 2013, 2015 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// Zawra no-op: WebSQL replaced by BrowserDB. All methods are stubs.

#include "config.h"
#include "Database.h"

#include "DatabaseAuthorizer.h"
#include "DatabaseContext.h"
#include "DatabaseManager.h"
#include "DatabaseTask.h"
#include "DatabaseThread.h"
#include "Document.h"
#include "SecurityOrigin.h"
#include "SecurityOriginData.h"
#include "SQLTransaction.h"
#include "SQLTransactionCallback.h"
#include "SQLTransactionErrorCallback.h"
#include "VoidCallback.h"

namespace WebCore {


Database::Database(DatabaseContext& context, const String& name, const String& expectedVersion, const String& displayName, unsigned long long estimatedSize)
    : m_document(*context.document())
    , m_contextThreadSecurityOrigin(context.document()->securityOrigin())
    , m_databaseThreadSecurityOrigin(context.document()->securityOrigin())
    , m_databaseContext(context)
    , m_name(name)
    , m_expectedVersion(expectedVersion)
    , m_displayName(displayName)
    , m_estimatedSize(estimatedSize)
    , m_guid(0)
    , m_databaseAuthorizer(DatabaseAuthorizer::create("ZawraStub"_s))
{
}

Database::~Database() = default;

ExceptionOr<void> Database::openAndVerifyVersion(bool)
{
    return { };
}

void Database::close()
{
}

void Database::interrupt()
{
}

unsigned long long Database::maximumSize()
{
    return 0;
}

void Database::scheduleTransactionStep(SQLTransaction&)
{
}

void Database::inProgressTransactionCompleted()
{
}

bool Database::hasPendingTransaction()
{
    return false;
}

void Database::didCommitWriteTransaction()
{
}

bool Database::didExceedQuota()
{
    return false;
}

SQLTransactionCoordinator* Database::transactionCoordinator()
{
    return nullptr;
}

String Database::version() const
{
    return emptyString();
}

void Database::changeVersion(String&&, String&&, RefPtr<SQLTransactionCallback>&&, RefPtr<SQLTransactionErrorCallback>&&, RefPtr<VoidCallback>&& successCallback)
{
    if (successCallback)
        successCallback->handleEvent();
}

void Database::transaction(RefPtr<SQLTransactionCallback>&&, RefPtr<SQLTransactionErrorCallback>&&, RefPtr<VoidCallback>&& successCallback)
{
    if (successCallback)
        successCallback->handleEvent();
}

void Database::readTransaction(RefPtr<SQLTransactionCallback>&&, RefPtr<SQLTransactionErrorCallback>&&, RefPtr<VoidCallback>&& successCallback)
{
    if (successCallback)
        successCallback->handleEvent();
}

String Database::stringIdentifierIsolatedCopy() const
{
    return m_name.isolatedCopy();
}

String Database::displayNameIsolatedCopy() const
{
    return m_displayName.isolatedCopy();
}

String Database::expectedVersionIsolatedCopy() const
{
    return m_expectedVersion.isolatedCopy();
}

unsigned long long Database::estimatedSize() const
{
    return m_estimatedSize;
}

String Database::fileNameIsolatedCopy() const
{
    return m_filename.isolatedCopy();
}

DatabaseDetails Database::details() const
{
    return DatabaseDetails();
}

void Database::disableAuthorizer()
{
    m_databaseAuthorizer->disable();
}

void Database::enableAuthorizer()
{
    m_databaseAuthorizer->enable();
}

void Database::setAuthorizerPermissions(int permissions)
{
    m_databaseAuthorizer->setPermissions(permissions);
}

bool Database::lastActionChangedDatabase()
{
    return m_databaseAuthorizer->lastActionChangedDatabase();
}

bool Database::lastActionWasInsert()
{
    return m_databaseAuthorizer->lastActionWasInsert();
}

void Database::resetDeletes()
{
    m_databaseAuthorizer->resetDeletes();
}

bool Database::hadDeletes()
{
    return m_databaseAuthorizer->hadDeletes();
}

void Database::resetAuthorizer()
{
    m_databaseAuthorizer->reset();
}

DatabaseThread& Database::databaseThread()
{
    if (auto* thread = m_databaseContext->existingDatabaseThread())
        return *thread;
    static auto thread = DatabaseThread::create();
    return thread.get();
}

void Database::logErrorMessage(const String&)
{
}

Vector<String> Database::tableNames()
{
    return { };
}

SecurityOriginData Database::securityOrigin()
{
    return { };
}

void Database::markAsDeletedAndClose()
{
    m_deleted = true;
}

void Database::scheduleTransactionCallback(SQLTransaction*)
{
}

void Database::incrementalVacuumIfNeeded()
{
}

ExceptionOr<void> Database::performOpenAndVerify(bool)
{
    m_opened = true;
    return { };
}

Vector<String> Database::performGetTableNames()
{
    return { };
}

void Database::performClose()
{
    m_opened = false;
}

// Private methods

void Database::closeDatabase()
{
}

bool Database::getVersionFromDatabase(String& version, bool)
{
    version = m_expectedVersion;
    return true;
}

bool Database::setVersionInDatabase(const String& version, bool)
{
    m_expectedVersion = version;
    return true;
}

void Database::setExpectedVersion(const String& version)
{
    m_expectedVersion = version;
}

String Database::getCachedVersion() const
{
    return m_expectedVersion;
}

void Database::setCachedVersion(const String& version)
{
    m_expectedVersion = version;
}

bool Database::getActualVersionForTransaction(String& version)
{
    version = m_expectedVersion;
    return true;
}

void Database::setEstimatedSize(unsigned long long size)
{
    m_estimatedSize = size;
}

void Database::scheduleTransaction()
{
}

void Database::runTransaction(RefPtr<SQLTransactionCallback>&&, RefPtr<SQLTransactionErrorCallback>&&, RefPtr<VoidCallback>&&, RefPtr<SQLTransactionWrapper>&&, bool)
{
}

#if !LOG_DISABLED || !ERROR_DISABLED
String Database::databaseDebugName() const
{
    return m_name;
}
#endif

} // namespace WebCore

