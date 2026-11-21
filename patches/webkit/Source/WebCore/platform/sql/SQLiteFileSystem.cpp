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

bool SQLiteFileSystem::ensureDatabaseDirectoryExists(const String& path)
{
    return FileSystem::makeAllDirectories(path);
}

bool SQLiteFileSystem::ensureDatabaseFileExists(const String& fileName, bool checkPathOnly)
{
    if (checkPathOnly)
        return ensureDatabaseDirectoryExists(FileSystem::parentPath(fileName));
    return FileSystem::fileExists(fileName);
}

bool SQLiteFileSystem::deleteEmptyDatabaseDirectory(const String& path)
{
    return FileSystem::deleteEmptyDirectory(path);
}

std::optional<WallTime> SQLiteFileSystem::databaseCreationTime(const String& fileName)
{
    return FileSystem::fileCreationTime(fileName);
}

std::optional<WallTime> SQLiteFileSystem::databaseModificationTime(const String& fileName)
{
    return FileSystem::fileModificationTime(fileName);
}

} // namespace WebCore
