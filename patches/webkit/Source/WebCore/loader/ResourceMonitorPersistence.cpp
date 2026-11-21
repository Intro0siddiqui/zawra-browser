/*
 * Zawra stub: ResourceMonitorPersistence SQLite backend removed.
 * Resource monitoring storage is handled by BrowserDB / in-memory structures.
 */

#include "config.h"
#include "ResourceMonitorPersistence.h"

#if ENABLE(CONTENT_EXTENSIONS)

namespace WebCore {

ResourceMonitorPersistence::ResourceMonitorPersistence() = default;
ResourceMonitorPersistence::~ResourceMonitorPersistence() = default;

void ResourceMonitorPersistence::reportSQLError(ASCIILiteral, ASCIILiteral) { }

bool ResourceMonitorPersistence::openDatabase(String&&)
{
    return false;
}

void ResourceMonitorPersistence::deleteAllRecords() { }

void ResourceMonitorPersistence::deleteExpiredRecords(ContinuousApproximateTime, Seconds) { }

Vector<ResourceMonitorPersistence::Record> ResourceMonitorPersistence::importRecords()
{
    return { };
}

void ResourceMonitorPersistence::recordAccess(const String&, ContinuousApproximateTime) { }

void ResourceMonitorPersistence::closeDatabase() { }

} // namespace WebCore

#endif
