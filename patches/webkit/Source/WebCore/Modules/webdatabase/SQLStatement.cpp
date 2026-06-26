// Zawra no-op: WebSQL replaced by BrowserDB. All methods are stubs.

#include "config.h"
#include "SQLStatement.h"

#include "Database.h"
#include "SQLError.h"
#include "SQLResultSet.h"
#include "SQLStatementCallback.h"
#include "SQLStatementErrorCallback.h"
#include "SQLTransaction.h"

namespace WebCore {

SQLStatement::SQLStatement(Database&, const String& statement, Vector<SQLValue>&& arguments, RefPtr<SQLStatementCallback>&& callback, RefPtr<SQLStatementErrorCallback>&& errorCallback, int permissions)
    : m_statement(statement)
    , m_arguments(WTFMove(arguments))
    , m_statementCallbackWrapper(WTFMove(callback), nullptr)
    , m_statementErrorCallbackWrapper(WTFMove(errorCallback), nullptr)
    , m_permissions(permissions)
{
}

SQLStatement::~SQLStatement()
{
}

bool SQLStatement::execute(Database&)
{
    return true;
}

bool SQLStatement::lastExecutionFailedDueToQuota() const
{
    return false;
}

bool SQLStatement::performCallback(SQLTransaction&)
{
    return true;
}

void SQLStatement::setDatabaseDeletedError()
{
    m_error = SQLError::create(SQLError::DATABASE_ERR, "Database has been deleted"_s);
}

void SQLStatement::setVersionMismatchedError()
{
    m_error = SQLError::create(SQLError::VERSION_ERR, "Database version mismatch"_s);
}

SQLError* SQLStatement::sqlError() const
{
    return m_error.get();
}

SQLResultSet* SQLStatement::sqlResultSet() const
{
    return m_resultSet.get();
}

void SQLStatement::setFailureDueToQuota()
{
}

void SQLStatement::clearFailureDueToQuota()
{
}

} // namespace WebCore
