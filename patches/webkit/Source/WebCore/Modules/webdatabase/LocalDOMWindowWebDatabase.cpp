#include "config.h"
#include "LocalDOMWindowWebDatabase.h"

#include "Database.h"

namespace WebCore {

ExceptionOr<RefPtr<Database>> LocalDOMWindowWebDatabase::openDatabase(LocalDOMWindow&, const String&, const String&, const String&, unsigned, RefPtr<DatabaseCallback>&&)
{
    return nullptr;
}

} // namespace WebCore
