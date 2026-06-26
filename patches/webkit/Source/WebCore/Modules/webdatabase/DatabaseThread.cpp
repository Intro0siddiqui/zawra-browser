// Zawra no-op: WebSQL replaced by BrowserDB. All methods are stubs.

#include "config.h"
#include "DatabaseThread.h"

#include "Database.h"
#include "DatabaseTask.h"
#include "SQLTransactionCoordinator.h"

namespace WebCore {

DatabaseThread::DatabaseThread()
    : m_transactionCoordinator(makeUnique<SQLTransactionCoordinator>())
{
}

DatabaseThread::~DatabaseThread()
{
    requestTermination(nullptr);
}

void DatabaseThread::start()
{
}

void DatabaseThread::requestTermination(DatabaseTaskSynchronizer* cleanupSync)
{
    m_cleanupSync = cleanupSync;
    if (m_thread) {
        m_thread->waitForCompletion();
        m_thread = nullptr;
    }
}

bool DatabaseThread::terminationRequested(DatabaseTaskSynchronizer*) const
{
    return !m_thread;
}

void DatabaseThread::scheduleTask(std::unique_ptr<DatabaseTask>&&)
{
}

void DatabaseThread::scheduleImmediateTask(std::unique_ptr<DatabaseTask>&&)
{
}

void DatabaseThread::unscheduleDatabaseTasks(Database&)
{
}

bool DatabaseThread::hasPendingDatabaseActivity() const
{
    return false;
}

void DatabaseThread::recordDatabaseOpen(Database& database)
{
    Locker locker { m_openDatabaseSetLock };
    m_openDatabaseSet.add(&database);
}

void DatabaseThread::recordDatabaseClosed(Database& database)
{
    Locker locker { m_openDatabaseSetLock };
    m_openDatabaseSet.remove(&database);
}

void DatabaseThread::databaseThread()
{
}

} // namespace WebCore
