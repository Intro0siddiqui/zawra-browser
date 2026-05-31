/*
 * Copyright (C) 2007-2017 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include <wtf/FileSystem.h>

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fnmatch.h>
#include <libgen.h>
#include <stdio.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <sys/types.h>
#include <unistd.h>
#include <wtf/EnumTraits.h>
#include <wtf/SafeStrerror.h>
#include <wtf/text/CString.h>
#include <wtf/text/StringBuilder.h>
#include <wtf/text/WTFString.h>

#if USE(GLIB)
#include <glib.h>
#endif

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

extern "C" {
    struct ZawraFileInfo { uint64_t size; uint64_t modified; bool isDirectory; };
    uint64_t Zawra_File_Seek(int handle, int64_t offset, int origin);
    int Zawra_File_Stat(const char* path, ZawraFileInfo* info);
    int Zawra_File_StatFD(int handle, ZawraFileInfo* info);
    int Zawra_File_Mkdir(const char* path);
    int Zawra_File_Unlink(const char* path);
}

namespace WTF {
namespace FileSystemImpl {


PlatformFileHandle openFile(const String& path, FileOpenMode mode, FileAccessPermission permission, bool failIfFileExists)
{
    CString fsRep = fileSystemRepresentation(path);

    if (fsRep.isNull())
        return invalidPlatformFileHandle;

    int platformFlag = 0;
    switch (mode) {
    case FileOpenMode::Read:
        platformFlag |= O_RDONLY;
        break;
    case FileOpenMode::Truncate:
        platformFlag |= (O_WRONLY | O_CREAT | O_TRUNC);
        break;
    case FileOpenMode::ReadWrite:
        platformFlag |= (O_RDWR | O_CREAT);
        break;
#if OS(DARWIN)
    case FileOpenMode::EventsOnly:
        platformFlag |= O_EVTONLY;
        break;
#endif
    }

    if (failIfFileExists)
        platformFlag |= (O_CREAT | O_EXCL);

    int permissionFlag = 0;
    if (permission == FileAccessPermission::User)
        permissionFlag |= (S_IRUSR | S_IWUSR);
    else if (permission == FileAccessPermission::All)
        permissionFlag |= (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

    return open(fsRep.data(), platformFlag, permissionFlag);
}

void closeFile(PlatformFileHandle& handle)
{
    if (isHandleValid(handle)) {
        close(handle);
        handle = invalidPlatformFileHandle;
    }
}

int posixFileDescriptor(PlatformFileHandle handle)
{
    return handle;
}

long long seekFile(PlatformFileHandle handle, long long offset, FileSeekOrigin origin)
{
    return static_cast<long long>(Zawra_File_Seek(handle, offset, static_cast<int>(origin)));
}

bool truncateFile(PlatformFileHandle handle, long long offset)
{
    // ftruncate returns 0 to indicate the success.
    return !ftruncate(handle, offset);
}

bool flushFile(PlatformFileHandle handle)
{
    return !fsync(handle);
}

int writeToFile(PlatformFileHandle handle, const void* data, int length)
{
    do {
        int bytesWritten = write(handle, data, static_cast<size_t>(length));
        if (bytesWritten >= 0)
            return bytesWritten;
    } while (errno == EINTR);
    return -1;
}

int readFromFile(PlatformFileHandle handle, void* data, int length)
{
    do {
        int bytesRead = read(handle, data, static_cast<size_t>(length));
        if (bytesRead >= 0)
            return bytesRead;
    } while (errno == EINTR);
    return -1;
}

#if USE(FILE_LOCK)
bool lockFile(PlatformFileHandle handle, OptionSet<FileLockMode> lockMode)
{
    static_assert(LOCK_SH == WTF::enumToUnderlyingType(FileLockMode::Shared), "LockSharedEncoding is as expected");
    static_assert(LOCK_EX == WTF::enumToUnderlyingType(FileLockMode::Exclusive), "LockExclusiveEncoding is as expected");
    static_assert(LOCK_NB == WTF::enumToUnderlyingType(FileLockMode::Nonblocking), "LockNonblockingEncoding is as expected");
    int result = flock(handle, lockMode.toRaw());
    return (result != -1);
}

bool unlockFile(PlatformFileHandle handle)
{
    int result = flock(handle, LOCK_UN);
    return (result != -1);
}
#endif

std::optional<uint64_t> fileSize(PlatformFileHandle handle)
{
    ZawraFileInfo info;
    if (Zawra_File_StatFD(handle, &info))
        return std::nullopt;

    return info.size;
}

std::optional<WallTime> fileCreationTime(const String& path)
{
#if (OS(LINUX) && HAVE(STATX)) || OS(DARWIN) || OS(OPENBSD) || OS(NETBSD) || OS(FREEBSD)
    CString fsRep = fileSystemRepresentation(path);
    if (!fsRep.data() || fsRep.data()[0] == '\0')
        return std::nullopt;

#if OS(LINUX) && HAVE(STATX)
    struct statx fileInfo;

    if (statx(-1, fsRep.data(), 0, STATX_BTIME, &fileInfo) == -1)
        return std::nullopt;

    return WallTime::fromRawSeconds(fileInfo.stx_btime.tv_sec);
#elif OS(DARWIN) || OS(OPENBSD) || OS(NETBSD) || OS(FREEBSD)
    struct stat fileInfo;

    if (stat(fsRep.data(), &fileInfo) == -1)
        return std::nullopt;

    return WallTime::fromRawSeconds(fileInfo.st_birthtime);
#endif
#endif

    UNUSED_PARAM(path);
    return std::nullopt;
}

std::optional<PlatformFileID> fileID(PlatformFileHandle handle)
{
    struct stat fileInfo;
    if (fstat(handle, &fileInfo))
        return std::nullopt;

    return fileInfo.st_ino;
}

bool fileIDsAreEqual(std::optional<PlatformFileID> a, std::optional<PlatformFileID> b)
{
    return a == b;
}

std::optional<uint32_t> volumeFileBlockSize(const String& path)
{
    struct statvfs fileStat;
    if (!statvfs(fileSystemRepresentation(path).data(), &fileStat))
        return fileStat.f_frsize;

    return std::nullopt;
}

#if !USE(CF)
String stringFromFileSystemRepresentation(const char* path)
{
    if (!path)
        return String();

    return String::fromUTF8(path);
}

CString fileSystemRepresentation(const String& path)
{
    return path.utf8();
}
#endif

#if !PLATFORM(COCOA)
static const char* temporaryFileDirectory()
{
#if USE(GLIB)
    return g_get_tmp_dir();
#else
    if (auto* tmpDir = getenv("TMPDIR"))
        return tmpDir;

    return "/tmp";
#endif
}

String openTemporaryFile(StringView prefix, PlatformFileHandle& handle, StringView suffix)
{
    // Suffix is not supported because that's incompatible with mkstemp.
    // This is OK for now since the code using it is built on macOS only.
    ASSERT_UNUSED(suffix, suffix.isEmpty());

    char buffer[PATH_MAX];
    if (snprintf(buffer, PATH_MAX, "%s/%sXXXXXX", temporaryFileDirectory(), prefix.utf8().data()) >= PATH_MAX)
        goto end;

    handle = mkstemp(buffer);
    if (handle < 0)
        goto end;

    return String::fromUTF8(buffer);

end:
    handle = invalidPlatformFileHandle;
    return String();
}
#endif // !PLATFORM(COCOA)

std::optional<int32_t> getFileDeviceId(const String& path)
{
    auto fsFile = fileSystemRepresentation(path);
    if (fsFile.isNull())
        return std::nullopt;

    struct stat fileStat;
    if (stat(fsFile.data(), &fileStat) == -1)
        return std::nullopt;

    return fileStat.st_dev;
}

// On macOS, stat() used by std::filesystem is much slower than access() when sandboxed.
// This fast path exists to avoid calls to stat(). It's not needed on other platforms.
#if ENABLE(FILESYSTEM_POSIX_FAST_PATH)

bool fileExists(const String& path)
{
    return access(fileSystemRepresentation(path).data(), F_OK) != -1;
}

bool deleteFile(const String& path)
{
    return Zawra_File_Unlink(fileSystemRepresentation(path).data()) == 0;
}

bool makeAllDirectories(const String& path)
{
    return Zawra_File_Mkdir(fileSystemRepresentation(path).data()) == 0;
}

String pathByAppendingComponent(StringView path, StringView component)
{
    if (path.endsWith('/'))
        return makeString(path, component);
    return makeString(path, '/', component);
}

String pathByAppendingComponents(StringView path, const Vector<StringView>& components)
{
    StringBuilder builder;
    builder.append(path);
    bool isFirstComponent = true;
    for (auto& component : components) {
        if (isFirstComponent) {
            isFirstComponent = false;
            if (path.endsWith('/')) {
                builder.append(component);
                continue;
            }
        }
        builder.append('/', component);
    }
    return builder.toString();
}

#endif

} // namespace FileSystemImpl
} // namespace WTF
