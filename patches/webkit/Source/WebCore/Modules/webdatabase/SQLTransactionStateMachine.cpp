// Zawra no-op: WebSQL replaced by BrowserDB. All methods are stubs.

#include "config.h"
#include "SQLTransactionStateMachine.h"

namespace WebCore {

#if !LOG_DISABLED
const char* nameForSQLTransactionState(SQLTransactionState state)
{
    switch (state) {
    case SQLTransactionState::End:
        return "End";
    case SQLTransactionState::Idle:
        return "Idle";
    case SQLTransactionState::AcquireLock:
        return "AcquireLock";
    case SQLTransactionState::OpenTransactionAndPreflight:
        return "OpenTransactionAndPreflight";
    case SQLTransactionState::RunStatements:
        return "RunStatements";
    case SQLTransactionState::PostflightAndCommit:
        return "PostflightAndCommit";
    case SQLTransactionState::CleanupAndTerminate:
        return "CleanupAndTerminate";
    case SQLTransactionState::CleanupAfterTransactionErrorCallback:
        return "CleanupAfterTransactionErrorCallback";
    case SQLTransactionState::DeliverTransactionCallback:
        return "DeliverTransactionCallback";
    case SQLTransactionState::DeliverTransactionErrorCallback:
        return "DeliverTransactionErrorCallback";
    case SQLTransactionState::DeliverStatementCallback:
        return "DeliverStatementCallback";
    case SQLTransactionState::DeliverQuotaIncreaseCallback:
        return "DeliverQuotaIncreaseCallback";
    case SQLTransactionState::DeliverSuccessCallback:
        return "DeliverSuccessCallback";
    case SQLTransactionState::NumberOfStates:
        return "NumberOfStates";
    }
    return "<unknown>";
}
#endif

} // namespace WebCore
