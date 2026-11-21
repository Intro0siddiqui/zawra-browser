#include "config.h"
#include "SQLResultSetRowList.h"

namespace WebCore {

unsigned SQLResultSetRowList::length() const
{
    return 0;
}

ExceptionOr<Vector<KeyValuePair<String, SQLValue>>> SQLResultSetRowList::item(unsigned index) const
{
    return Vector<KeyValuePair<String, SQLValue>> { };
}

} // namespace WebCore
