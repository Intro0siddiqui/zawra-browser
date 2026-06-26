// Zawra no-op: WebSQL replaced by BrowserDB. All methods are stubs.

#include "config.h"
#include "SQLTransactionBackend.h"

#include "Database.h"
#include "SQLError.h"
#include "SQLTransaction.h"

namespace WebCore {

SQLTransactionBackend::SQLTransactionBackend(SQLTransaction& transaction)
    : m_frontend(transaction)
{
}

SQLTransactionBackend::~SQLTransactionBackend()
{
}

void SQLTransactionBackend::notifyDatabaseThreadIsShuttingDown()
{
}

void SQLTransactionBackend::requestTransitToState(SQLTransactionState)
{
}

void SQLTransactionBackend::doCleanup()
{
}

SQLTransactionBackend::StateFunction SQLTransactionBackend::stateFunctionFor(SQLTransactionState state)
{
    switch (state) {
    case SQLTransactionState::AcquireLock:
        return &SQLTransactionBackend::acquireLock;
    case SQLTransactionState::OpenTransactionAndPreflight:
        return &SQLTransactionBackend::openTransactionAndPreflight;
    case SQLTransactionState::RunStatements:
        return &SQLTransactionBackend::runStatements;
    case SQLTransactionState::CleanupAndTerminate:
        return &SQLTransactionBackend::cleanupAndTerminate;
    case SQLTransactionState::CleanupAfterTransactionErrorCallback:
        return &SQLTransactionBackend::cleanupAfterTransactionErrorCallback;
    default:
        return nullptr;
    }
}

void SQLTransactionBackend::computeNextStateAndCleanupIfNeeded()
{
}

void SQLTransactionBackend::acquireLock()
{
}

void SQLTransactionBackend::openTransactionAndPreflight()
{
}

void SQLTransactionBackend::runStatements()
{
}

void SQLTransactionBackend::cleanupAndTerminate()
{
}

void SQLTransactionBackend::cleanupAfterTransactionErrorCallback()
{
}

void SQLTransactionBackend::unreachableState()
{
    ASSERT_NOT_REACHED();
}

} // namespace WebCore
