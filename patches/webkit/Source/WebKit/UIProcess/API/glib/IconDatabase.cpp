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

// Zawra: SQLite removed from IconDatabase (N/A in Zawra).

#include "config.h"
#include "IconDatabase.h"

#include <wtf/RunLoop.h>

namespace WebKit {

IconDatabase::IconDatabase(const String&, AllowDatabaseWrite allowDatabaseWrite)
    : m_workQueue(WorkQueue::create("org.webkit.IconDatabase"_s))
    , m_allowDatabaseWrite(allowDatabaseWrite)
{
}

IconDatabase::~IconDatabase() = default;

void IconDatabase::invalidate()
{
}

void IconDatabase::checkIconURLAndSetPageURLIfNeeded(const String&, const String&, AllowDatabaseWrite, CompletionHandler<void(bool, bool)>&& completionHandler)
{
    RunLoop::mainSingleton().dispatch([completionHandler = WTF::move(completionHandler)]() mutable {
        completionHandler(false, false);
    });
}

void IconDatabase::loadIconsForPageURL(const String&, AllowDatabaseWrite, CompletionHandler<void(Vector<WebCore::PlatformImagePtr>&&)>&& completionHandler)
{
    RunLoop::mainSingleton().dispatch([completionHandler = WTF::move(completionHandler)]() mutable {
        completionHandler({ });
    });
}

ListHashSet<String> IconDatabase::iconURLsForPageURL(const String&)
{
    return { };
}

void IconDatabase::setIconForPageURL(const String&, std::span<const uint8_t>, const String&, AllowDatabaseWrite, CompletionHandler<void(bool)>&& completionHandler)
{
    RunLoop::mainSingleton().dispatch([completionHandler = WTF::move(completionHandler)]() mutable {
        completionHandler(false);
    });
}

void IconDatabase::clear(CompletionHandler<void()>&& completionHandler)
{
    RunLoop::mainSingleton().dispatch([completionHandler = WTF::move(completionHandler)]() mutable {
        completionHandler();
    });
}

} // namespace WebKit
