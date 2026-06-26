// Zawra no-op: WebSQL replaced by BrowserDB. All methods are stubs.

#include "config.h"
#include "SQLTransactionCoordinator.h"

#include "SQLTransaction.h"

namespace WebCore {

SQLTransactionCoordinator::SQLTransactionCoordinator()
    : m_isShuttingDown(false)
{
}

void SQLTransactionCoordinator::acquireLock(SQLTransaction&)
{
}

void SQLTransactionCoordinator::releaseLock(SQLTransaction&)
{
}

void SQLTransactionCoordinator::shutdown()
{
    m_isShuttingDown = true;
}

void SQLTransactionCoordinator::processPendingTransactions(CoordinationInfo&)
{
}

} // namespace WebCore
