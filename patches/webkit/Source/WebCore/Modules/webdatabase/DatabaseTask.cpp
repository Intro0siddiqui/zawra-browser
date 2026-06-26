// Zawra no-op: WebSQL replaced by BrowserDB. All methods are stubs.

#include "config.h"
#include "DatabaseTask.h"

#include "Database.h"
#include "SQLTransaction.h"

namespace WebCore {

// DatabaseTaskSynchronizer

DatabaseTaskSynchronizer::DatabaseTaskSynchronizer()
{
}

void DatabaseTaskSynchronizer::waitForTaskCompletion()
{
    Locker locker { m_synchronousLock };
    m_synchronousCondition.wait(m_synchronousLock, [this] {
        return m_taskCompleted;
    });
}

void DatabaseTaskSynchronizer::taskCompleted()
{
    Locker locker { m_synchronousLock };
    m_taskCompleted = true;
    m_synchronousCondition.notifyAll();
}

// DatabaseTask

DatabaseTask::DatabaseTask(Database& database, DatabaseTaskSynchronizer* synchronizer)
    : m_database(database)
    , m_synchronizer(synchronizer)
{
}

DatabaseTask::~DatabaseTask()
{
}

void DatabaseTask::performTask()
{
    doPerformTask();

#if ASSERT_ENABLED
    if (m_synchronizer)
        m_synchronizer->setHasCheckedForTermination();
#endif

    if (m_synchronizer)
        m_synchronizer->taskCompleted();
}

// DatabaseOpenTask

DatabaseOpenTask::DatabaseOpenTask(Database& database, bool setVersionInNewDatabase, DatabaseTaskSynchronizer& synchronizer, ExceptionOr<void>& result)
    : DatabaseTask(database, &synchronizer)
    , m_setVersionInNewDatabase(setVersionInNewDatabase)
    , m_result(result)
{
}

void DatabaseOpenTask::doPerformTask()
{
    m_result = database().performOpenAndVerify(m_setVersionInNewDatabase);
}

#if !LOG_DISABLED
const char* DatabaseOpenTask::debugTaskName() const
{
    return "DatabaseOpenTask";
}
#endif

// DatabaseCloseTask

DatabaseCloseTask::DatabaseCloseTask(Database& database, DatabaseTaskSynchronizer& synchronizer)
    : DatabaseTask(database, &synchronizer)
{
}

void DatabaseCloseTask::doPerformTask()
{
    database().performClose();
}

#if !LOG_DISABLED
const char* DatabaseCloseTask::debugTaskName() const
{
    return "DatabaseCloseTask";
}
#endif

// DatabaseTransactionTask

DatabaseTransactionTask::DatabaseTransactionTask(RefPtr<SQLTransaction>&& transaction)
    : DatabaseTask(transaction->database(), nullptr)
    , m_transaction(WTFMove(transaction))
    , m_didPerformTask(false)
{
}

DatabaseTransactionTask::~DatabaseTransactionTask()
{
}

void DatabaseTransactionTask::doPerformTask()
{
    m_didPerformTask = true;
}

#if !LOG_DISABLED
const char* DatabaseTransactionTask::debugTaskName() const
{
    return "DatabaseTransactionTask";
}
#endif

// DatabaseTableNamesTask

DatabaseTableNamesTask::DatabaseTableNamesTask(Database& database, DatabaseTaskSynchronizer& synchronizer, Vector<String>& result)
    : DatabaseTask(database, &synchronizer)
    , m_result(result)
{
}

void DatabaseTableNamesTask::doPerformTask()
{
    m_result = database().performGetTableNames();
}

#if !LOG_DISABLED
const char* DatabaseTableNamesTask::debugTaskName() const
{
    return "DatabaseTableNamesTask";
}
#endif

} // namespace WebCore
