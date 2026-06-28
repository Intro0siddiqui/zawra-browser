#include "config.h"
#include "DatabaseManager.h"

#include "Database.h"
#include "DatabaseContext.h"
#include "Exception.h"
#include <wtf/NeverDestroyed.h>

namespace WebCore {

DatabaseManager& DatabaseManager::singleton()
{
    static NeverDestroyed<DatabaseManager> instance;
    return instance;
}

void DatabaseManager::initialize(const String& databasePath)
{
    UNUSED_PARAM(databasePath);
}

void DatabaseManager::setClient(DatabaseManagerClient* client)
{
    m_client = client;
}

bool DatabaseManager::isAvailable()
{
    return m_databaseIsAvailable;
}

void DatabaseManager::setIsAvailable(bool available)
{
    m_databaseIsAvailable = available;
}

Ref<DatabaseContext> DatabaseManager::databaseContext(Document& document)
{
    return adoptRef(*new DatabaseContext(document));
}

ExceptionOr<Ref<Database>> DatabaseManager::openDatabase(Document& document, const String& name, const String& expectedVersion, const String& displayName, unsigned estimatedSize, RefPtr<DatabaseCallback>&& creationCallback)
{
    UNUSED_PARAM(document);
    UNUSED_PARAM(name);
    UNUSED_PARAM(expectedVersion);
    UNUSED_PARAM(displayName);
    UNUSED_PARAM(estimatedSize);
    UNUSED_PARAM(creationCallback);
    return Exception { InvalidStateError };
}

bool DatabaseManager::hasOpenDatabases(Document& document)
{
    UNUSED_PARAM(document);
    return false;
}

void DatabaseManager::stopDatabases(Document& document, DatabaseTaskSynchronizer* synchronizer)
{
    UNUSED_PARAM(document);
    UNUSED_PARAM(synchronizer);
}

String DatabaseManager::fullPathForDatabase(SecurityOrigin& origin, const String& name, bool createIfDoesNotExist)
{
    UNUSED_PARAM(origin);
    UNUSED_PARAM(name);
    UNUSED_PARAM(createIfDoesNotExist);
    return String();
}

DatabaseDetails DatabaseManager::detailsForNameAndOrigin(const String& name, SecurityOrigin& origin)
{
    UNUSED_PARAM(name);
    UNUSED_PARAM(origin);
    return DatabaseDetails { };
}

void DatabaseManager::platformInitialize(const String& databasePath)
{
    UNUSED_PARAM(databasePath);
}

ExceptionOr<Ref<Database>> DatabaseManager::openDatabaseBackend(Document& document, const String& name, const String& expectedVersion, const String& displayName, unsigned estimatedSize, bool setVersionInNewDatabase)
{
    UNUSED_PARAM(document);
    UNUSED_PARAM(name);
    UNUSED_PARAM(expectedVersion);
    UNUSED_PARAM(displayName);
    UNUSED_PARAM(estimatedSize);
    UNUSED_PARAM(setVersionInNewDatabase);
    return Exception { InvalidStateError };
}

ExceptionOr<Ref<Database>> DatabaseManager::tryToOpenDatabaseBackend(Document& document, const String& name, const String& expectedVersion, const String& displayName, unsigned estimatedSize, bool setVersionInNewDatabase, OpenAttempt attempt)
{
    UNUSED_PARAM(document);
    UNUSED_PARAM(name);
    UNUSED_PARAM(expectedVersion);
    UNUSED_PARAM(displayName);
    UNUSED_PARAM(estimatedSize);
    UNUSED_PARAM(setVersionInNewDatabase);
    UNUSED_PARAM(attempt);
    return Exception { InvalidStateError };
}

void DatabaseManager::addProposedDatabase(ProposedDatabase& proposedDatabase)
{
    UNUSED_PARAM(proposedDatabase);
}

void DatabaseManager::removeProposedDatabase(ProposedDatabase& proposedDatabase)
{
    UNUSED_PARAM(proposedDatabase);
}

void DatabaseManager::logErrorMessage(Document& document, const String& message)
{
    UNUSED_PARAM(document);
    UNUSED_PARAM(message);
}

} // namespace WebCore
