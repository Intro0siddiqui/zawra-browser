// Zawra no-op: WebSQL replaced by BrowserDB. All methods are stubs.

#include "config.h"
#include "ChangeVersionWrapper.h"

#include "SQLError.h"

namespace WebCore {

ChangeVersionWrapper::ChangeVersionWrapper(String&& oldVersion, String&& newVersion)
    : m_oldVersion(WTFMove(oldVersion))
    , m_newVersion(WTFMove(newVersion))
{
}

bool ChangeVersionWrapper::performPreflight(SQLTransaction&)
{
    return true;
}

bool ChangeVersionWrapper::performPostflight(SQLTransaction&)
{
    return true;
}

void ChangeVersionWrapper::handleCommitFailedAfterPostflight(SQLTransaction&)
{
}

} // namespace WebCore
