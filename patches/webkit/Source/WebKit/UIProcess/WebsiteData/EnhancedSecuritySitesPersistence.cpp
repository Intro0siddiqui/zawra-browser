/*
 * Copyright (C) 2024 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "EnhancedSecuritySitesPersistence.h"

#include "Logging.h"
#include <wtf/MainThread.h>
#include <wtf/text/MakeString.h>

namespace WebKit {

EnhancedSecuritySitesPersistence::EnhancedSecuritySitesPersistence(const String&)
    : m_isOpen(true)
{
}

EnhancedSecuritySitesPersistence::~EnhancedSecuritySitesPersistence()
{
    closeDatabase();
}

bool EnhancedSecuritySitesPersistence::openDatabase(const String&)
{
    m_isOpen = true;
    return true;
}

void EnhancedSecuritySitesPersistence::deleteSites(const Vector<WebCore::RegistrableDomain>& sites)
{
    for (const auto& site : sites)
        deleteSite(site);
}

void EnhancedSecuritySitesPersistence::deleteSite(const WebCore::RegistrableDomain& site)
{
    m_enhancedSecurityOnlyDomains.remove(site);
    m_allEnhancedSecuritySites.remove(site);
}

void EnhancedSecuritySitesPersistence::deleteAllSites()
{
    m_enhancedSecurityOnlyDomains.clear();
    m_allEnhancedSecuritySites.clear();
}

HashSet<WebCore::RegistrableDomain> EnhancedSecuritySitesPersistence::enhancedSecurityOnlyDomains()
{
    return m_enhancedSecurityOnlyDomains;
}

HashSet<WebCore::RegistrableDomain> EnhancedSecuritySitesPersistence::allEnhancedSecuritySites()
{
    return m_allEnhancedSecuritySites;
}

void EnhancedSecuritySitesPersistence::trackEnhancedSecurityForDomain(WebCore::RegistrableDomain&& site, EnhancedSecurity reason)
{
    if (isEnhancedSecurityEnabledForState(reason))
        m_enhancedSecurityOnlyDomains.add(site);
    m_allEnhancedSecuritySites.add(WTF::move(site));
}

void EnhancedSecuritySitesPersistence::closeDatabase()
{
    m_isOpen = false;
}

} // namespace WebKit
