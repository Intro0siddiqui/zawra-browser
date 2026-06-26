#include "config.h"
#include "DatabaseContext.h"

#include "DatabaseDetails.h"
#include "DatabaseManager.h"
#include "DatabaseTask.h"
#include "DatabaseThread.h"
#include "Document.h"
#include "SecurityOrigin.h"
#include "SecurityOriginData.h"

namespace WebCore {

DatabaseContext::DatabaseContext(Document& document)
    : ThreadSafeRefCounted<DatabaseContext>()
    , ActiveDOMObject(document)
{
}

DatabaseContext::~DatabaseContext()
{
    stopDatabases();
}

DatabaseThread* DatabaseContext::databaseThread()
{
    if (!m_databaseThread) {
        m_databaseThread = DatabaseThread::create();
        m_databaseThread->start();
    }
    return m_databaseThread.get();
}

bool DatabaseContext::stopDatabases(DatabaseTaskSynchronizer* synchronizer)
{
    if (!m_databaseThread)
        return false;

    if (m_hasRequestedTermination)
        return true;

    m_hasRequestedTermination = true;
    m_databaseThread->requestTermination(synchronizer);
    m_databaseThread = nullptr;
    return true;
}

bool DatabaseContext::allowDatabaseAccess() const
{
    return true;
}

void DatabaseContext::databaseExceededQuota(const String& name, DatabaseDetails details)
{
    DatabaseManager::singleton().setIsAvailable(false);
}

const SecurityOriginData& DatabaseContext::securityOrigin() const
{
    return document()->securityOrigin().data();
}

bool DatabaseContext::isContextThread() const
{
    return scriptExecutionContext()->isContextThread();
}

void DatabaseContext::contextDestroyed()
{
    stopDatabases();
}

void DatabaseContext::stop()
{
    stopDatabases();
}

} // namespace WebCore
