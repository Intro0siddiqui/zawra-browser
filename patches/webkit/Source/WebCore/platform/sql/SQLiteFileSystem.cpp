#include "config.h"
#include "SQLiteFileSystem.h"
#include <wtf/FileSystem.h>

namespace WebCore {

String SQLiteFileSystem::computeHashForFileName(StringView filePath)
{
    return FileSystem::encodeForFileName(filePath.toString());
}

String SQLiteFileSystem::appendDatabaseFileNameToPath(StringView path, StringView fileName)
{
    return FileSystem::pathByAppendingComponent(path, fileName);
}

bool SQLiteFileSystem::moveDatabaseFile(const String& oldPath, const String& newPath)
{
    return FileSystem::moveFile(oldPath, newPath);
}

bool SQLiteFileSystem::deleteDatabaseFile(const String& fileName)
{
    return FileSystem::deleteFile(fileName);
}

uint64_t SQLiteFileSystem::databaseFileSize(const String& fileName)
{
    auto fileSize = FileSystem::fileSize(fileName);
    return fileSize ? *fileSize : 0;
}

} // namespace WebCore
