#include "config.h"
#include "DatabaseTracker.h"

#include "Database.h"

namespace WebCore {

std::unique_ptr<DatabaseTracker> DatabaseTracker::trackerWithDatabasePath(const String& databasePath)
{
    return std::unique_ptr<DatabaseTracker>(new DatabaseTracker(databasePath));
}

void DatabaseTracker::initializeTracker(const String&)
{
}

DatabaseTracker& DatabaseTracker::singleton()
{
    static DatabaseTracker instance(String { });
    return instance;
}

bool DatabaseTracker::isInitialized()
{
    return true;
}

ExceptionOr<void> DatabaseTracker::canEstablishDatabase(DatabaseContext&, const String&, uint64_t)
{
    return { };
}

ExceptionOr<void> DatabaseTracker::retryCanEstablishDatabase(DatabaseContext&, const String&, uint64_t)
{
    return { };
}

void DatabaseTracker::setDatabaseDetails(const SecurityOriginData&, const String&, const String&, uint64_t)
{
}

String DatabaseTracker::fullPathForDatabase(const SecurityOriginData&, const String& name, bool)
{
    return name;
}

Vector<Ref<Database>> DatabaseTracker::openDatabases()
{
    return { };
}

void DatabaseTracker::addOpenDatabase(Database&)
{
}

void DatabaseTracker::removeOpenDatabase(Database&)
{
}

uint64_t DatabaseTracker::maximumSize(Database&)
{
    return 0;
}

void DatabaseTracker::closeAllDatabases(CurrentQueryBehavior)
{
}

Vector<SecurityOriginData> DatabaseTracker::origins()
{
    return { };
}

Vector<String> DatabaseTracker::databaseNames(const SecurityOriginData&)
{
    return { };
}

DatabaseDetails DatabaseTracker::detailsForNameAndOrigin(const String&, const SecurityOriginData&)
{
    return DatabaseDetails();
}

uint64_t DatabaseTracker::usage(const SecurityOriginData&)
{
    return 0;
}

uint64_t DatabaseTracker::quota(const SecurityOriginData&)
{
    return 0;
}

void DatabaseTracker::setQuota(const SecurityOriginData&, uint64_t)
{
}

Ref<OriginLock> DatabaseTracker::originLockFor(const SecurityOriginData&)
{
    RELEASE_ASSERT_NOT_REACHED();
}

void DatabaseTracker::deleteAllDatabasesImmediately()
{
}

void DatabaseTracker::deleteDatabasesModifiedSince(WallTime)
{
}

bool DatabaseTracker::deleteOrigin(const SecurityOriginData&)
{
    return true;
}

bool DatabaseTracker::deleteDatabase(const SecurityOriginData&, const String&)
{
    return true;
}

#if PLATFORM(IOS_FAMILY)
void DatabaseTracker::removeDeletedOpenedDatabases()
{
}

bool DatabaseTracker::deleteDatabaseFileIfEmpty(const String&)
{
    return true;
}

Lock& DatabaseTracker::openDatabaseMutex()
{
    static Lock mutex;
    return mutex;
}

void DatabaseTracker::emptyDatabaseFilesRemovalTaskWillBeScheduled()
{
}

void DatabaseTracker::emptyDatabaseFilesRemovalTaskDidFinish()
{
}
#endif

void DatabaseTracker::setClient(DatabaseManagerClient*)
{
}

void DatabaseTracker::scheduleNotifyDatabaseChanged(const SecurityOriginData&, const String&)
{
}

void DatabaseTracker::doneCreatingDatabase(Database&)
{
}

DatabaseTracker::DatabaseTracker(const String& databasePath)
    : m_databaseDirectoryPath(databasePath)
{
}

ExceptionOr<void> DatabaseTracker::hasAdequateQuotaForOrigin(const SecurityOriginData&, uint64_t)
{
    return { };
}

bool DatabaseTracker::hasEntryForOriginNoLock(const SecurityOriginData&)
{
    return false;
}

String DatabaseTracker::fullPathForDatabaseNoLock(const SecurityOriginData&, const String& name, bool)
{
    return name;
}

Vector<String> DatabaseTracker::databaseNamesNoLock(const SecurityOriginData&)
{
    return { };
}

uint64_t DatabaseTracker::quotaNoLock(const SecurityOriginData&)
{
    return 0;
}

String DatabaseTracker::trackerDatabasePath() const
{
    return m_databaseDirectoryPath;
}

void DatabaseTracker::openTrackerDatabase(TrackerCreationAction)
{
}

String DatabaseTracker::originPath(const SecurityOriginData&) const
{
    return m_databaseDirectoryPath;
}

bool DatabaseTracker::hasEntryForDatabase(const SecurityOriginData&, const String&)
{
    return false;
}

bool DatabaseTracker::addDatabase(const SecurityOriginData&, const String&, const String&)
{
    return true;
}

bool DatabaseTracker::deleteOrigin(const SecurityOriginData&, DeletionMode)
{
    return true;
}

bool DatabaseTracker::deleteDatabaseFile(const SecurityOriginData&, const String&, DeletionMode)
{
    return true;
}

void DatabaseTracker::deleteOriginLockFor(const SecurityOriginData&)
{
}

bool DatabaseTracker::isDeletingDatabaseOrOriginFor(const SecurityOriginData&, const String&)
{
    return false;
}

void DatabaseTracker::recordCreatingDatabase(const SecurityOriginData&, const String&)
{
}

void DatabaseTracker::doneCreatingDatabase(const SecurityOriginData&, const String&)
{
}

bool DatabaseTracker::creatingDatabase(const SecurityOriginData&, const String&)
{
    return false;
}

bool DatabaseTracker::canDeleteDatabase(const SecurityOriginData&, const String&)
{
    return true;
}

void DatabaseTracker::recordDeletingDatabase(const SecurityOriginData&, const String&)
{
}

void DatabaseTracker::doneDeletingDatabase(const SecurityOriginData&, const String&)
{
}

bool DatabaseTracker::isDeletingDatabase(const SecurityOriginData&, const String&)
{
    return false;
}

bool DatabaseTracker::canDeleteOrigin(const SecurityOriginData&)
{
    return true;
}

bool DatabaseTracker::isDeletingOrigin(const SecurityOriginData&)
{
    return false;
}

void DatabaseTracker::recordDeletingOrigin(const SecurityOriginData&)
{
}

void DatabaseTracker::doneDeletingOrigin(const SecurityOriginData&)
{
}

void DatabaseTracker::scheduleForNotification()
{
}

void DatabaseTracker::notifyDatabasesChanged()
{
}

} // namespace WebCore
