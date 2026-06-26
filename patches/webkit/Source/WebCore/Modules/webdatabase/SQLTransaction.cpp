#include "config.h"
#include "SQLTransaction.h"

#include "SQLStatementCallback.h"
#include "SQLStatementErrorCallback.h"

namespace WebCore {

ExceptionOr<void> SQLTransaction::executeSql(const String&, std::optional<Vector<SQLValue>>&&, RefPtr<SQLStatementCallback>&&, RefPtr<SQLStatementErrorCallback>&&)
{
    return { };
}

} // namespace WebCore
