/*
 * Copyright (C) 2019 Igalia S.L.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#pragma once

// Zawra: SQLite removed from IconDatabase (N/A in Zawra).

#include <WebCore/NativeImage.h>
#include <wtf/CompletionHandler.h>
#include <wtf/HashMap.h>
#include <wtf/ListHashSet.h>
#include <wtf/Lock.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/WorkQueue.h>

namespace WebKit {

class IconDatabase : public ThreadSafeRefCountedAndCanMakeThreadSafeWeakPtr<IconDatabase> {
public:
    enum class AllowDatabaseWrite : bool { No, Yes };

    static Ref<IconDatabase> create(const String& path, AllowDatabaseWrite allowDatabaseWrite)
    {
        return adoptRef(*new IconDatabase(path, allowDatabaseWrite));
    }

    ~IconDatabase();

    void invalidate();

    void checkIconURLAndSetPageURLIfNeeded(const String& iconURL, const String& pageURL, AllowDatabaseWrite, CompletionHandler<void(bool, bool)>&&);
    void loadIconsForPageURL(const String&, AllowDatabaseWrite, CompletionHandler<void(Vector<WebCore::PlatformImagePtr>&&)>&&);
    ListHashSet<String> iconURLsForPageURL(const String&);
    void setIconForPageURL(const String& iconURL, std::span<const uint8_t>, const String& pageURL, AllowDatabaseWrite, CompletionHandler<void(bool)>&&);
    void clear(CompletionHandler<void()>&&);

private:
    IconDatabase(const String&, AllowDatabaseWrite);

    Ref<WorkQueue> m_workQueue;
    AllowDatabaseWrite m_allowDatabaseWrite { AllowDatabaseWrite::Yes };
};

} // namespace WebKit
