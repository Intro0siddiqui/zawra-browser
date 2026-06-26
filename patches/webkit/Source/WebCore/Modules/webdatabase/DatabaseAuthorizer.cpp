// Zawra no-op: WebSQL replaced by BrowserDB. All methods are stubs.

#include "config.h"
#include "DatabaseAuthorizer.h"

#include <wtf/text/WTFString.h>

namespace WebCore {

const int SQLAuthAllow = 1;
const int SQLAuthIgnore = 2;
const int SQLAuthDeny = 3;

Ref<DatabaseAuthorizer> DatabaseAuthorizer::create(const String& databaseInfoTableName)
{
    return adoptRef(*new DatabaseAuthorizer(databaseInfoTableName));
}

DatabaseAuthorizer::DatabaseAuthorizer(const String& databaseInfoTableName)
    : m_permissions(ReadWriteMask)
    , m_securityEnabled(true)
    , m_lastActionWasInsert(false)
    , m_lastActionChangedDatabase(false)
    , m_hadDeletes(false)
    , m_databaseInfoTableName(databaseInfoTableName)
{
}

int DatabaseAuthorizer::createTable(const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::createTempTable(const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::dropTable(const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::dropTempTable(const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::allowAlterTable(const String&, const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::createIndex(const String&, const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::createTempIndex(const String&, const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::dropIndex(const String&, const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::dropTempIndex(const String&, const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::createTrigger(const String&, const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::createTempTrigger(const String&, const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::dropTrigger(const String&, const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::dropTempTrigger(const String&, const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::createView(const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::createTempView(const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::dropView(const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::dropTempView(const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::createVTable(const String&, const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::dropVTable(const String&, const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::allowDelete(const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::allowInsert(const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::allowUpdate(const String&, const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::allowTransaction()
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::allowRead(const String&, const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::allowReindex(const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::allowAnalyze(const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::allowFunction(const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::allowPragma(const String&, const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::allowAttach(const String&)
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::allowDetach(const String&)
{
    return SQLAuthAllow;
}

void DatabaseAuthorizer::disable()
{
    m_securityEnabled = false;
}

void DatabaseAuthorizer::enable()
{
    m_securityEnabled = true;
}

void DatabaseAuthorizer::setPermissions(int permissions)
{
    m_permissions = permissions;
}

void DatabaseAuthorizer::reset()
{
    m_lastActionWasInsert = false;
    m_lastActionChangedDatabase = false;
    m_hadDeletes = false;
}

void DatabaseAuthorizer::resetDeletes()
{
    m_hadDeletes = false;
}

void DatabaseAuthorizer::addAllowedFunctions()
{
}

int DatabaseAuthorizer::denyBasedOnTableName(const String&) const
{
    return SQLAuthAllow;
}

int DatabaseAuthorizer::updateDeletesBasedOnTableName(const String&)
{
    return SQLAuthAllow;
}

bool DatabaseAuthorizer::allowWrite()
{
    return true;
}

} // namespace WebCore
