// Zawra no-op: WebSQL replaced by BrowserDB. All methods are stubs.

#include "config.h"
#include "ChangeVersionWrapper.h"

#include "SQLError.h"
#include <utility>

namespace WebCore {

ChangeVersionWrapper::ChangeVersionWrapper(String&& oldVersion, String&& newVersion)
    : m_oldVersion(std::move(oldVersion))
    , m_newVersion(std::move(newVersion))
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
