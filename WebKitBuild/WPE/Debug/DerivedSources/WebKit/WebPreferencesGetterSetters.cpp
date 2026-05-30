/*
* THIS FILE WAS AUTOMATICALLY GENERATED, DO NOT EDIT.
*
* Copyright (C) 2020 Apple Inc. All rights reserved.
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
#include "WebPreferences.h"

#include "WebPreferencesKeys.h"

namespace WebKit {

void WebPreferences::setAcceleratedCompositingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::acceleratedCompositingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::acceleratedCompositingEnabledKey(), value, false);
}

bool WebPreferences::acceleratedCompositingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::acceleratedCompositingEnabledKey());
}

void WebPreferences::deleteAcceleratedCompositingEnabled()
{
    deleteKey(WebPreferencesKey::acceleratedCompositingEnabledKey());
}

void WebPreferences::setAcceleratedCompositingForFixedPositionEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::acceleratedCompositingForFixedPositionEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::acceleratedCompositingForFixedPositionEnabledKey(), value, false);
}

bool WebPreferences::acceleratedCompositingForFixedPositionEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::acceleratedCompositingForFixedPositionEnabledKey());
}

void WebPreferences::deleteAcceleratedCompositingForFixedPositionEnabled()
{
    deleteKey(WebPreferencesKey::acceleratedCompositingForFixedPositionEnabledKey());
}

void WebPreferences::setAggressiveTileRetentionEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::aggressiveTileRetentionEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::aggressiveTileRetentionEnabledKey(), value, false);
}

bool WebPreferences::aggressiveTileRetentionEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::aggressiveTileRetentionEnabledKey());
}

void WebPreferences::deleteAggressiveTileRetentionEnabled()
{
    deleteKey(WebPreferencesKey::aggressiveTileRetentionEnabledKey());
}

void WebPreferences::setAllowContentSecurityPolicySourceStarToMatchAnyProtocol(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::allowContentSecurityPolicySourceStarToMatchAnyProtocolKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::allowContentSecurityPolicySourceStarToMatchAnyProtocolKey(), value, false);
}

bool WebPreferences::allowContentSecurityPolicySourceStarToMatchAnyProtocol() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::allowContentSecurityPolicySourceStarToMatchAnyProtocolKey());
}

void WebPreferences::deleteAllowContentSecurityPolicySourceStarToMatchAnyProtocol()
{
    deleteKey(WebPreferencesKey::allowContentSecurityPolicySourceStarToMatchAnyProtocolKey());
}

void WebPreferences::setAllowCrossOriginSubresourcesToAskForCredentials(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::allowCrossOriginSubresourcesToAskForCredentialsKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::allowCrossOriginSubresourcesToAskForCredentialsKey(), value, false);
}

bool WebPreferences::allowCrossOriginSubresourcesToAskForCredentials() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::allowCrossOriginSubresourcesToAskForCredentialsKey());
}

void WebPreferences::deleteAllowCrossOriginSubresourcesToAskForCredentials()
{
    deleteKey(WebPreferencesKey::allowCrossOriginSubresourcesToAskForCredentialsKey());
}

void WebPreferences::setAllowDisplayOfInsecureContent(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::allowDisplayOfInsecureContentKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::allowDisplayOfInsecureContentKey(), value, false);
}

bool WebPreferences::allowDisplayOfInsecureContent() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::allowDisplayOfInsecureContentKey());
}

void WebPreferences::deleteAllowDisplayOfInsecureContent()
{
    deleteKey(WebPreferencesKey::allowDisplayOfInsecureContentKey());
}

void WebPreferences::setAllowFileAccessFromFileURLs(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::allowFileAccessFromFileURLsKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::allowFileAccessFromFileURLsKey(), value, false);
}

bool WebPreferences::allowFileAccessFromFileURLs() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::allowFileAccessFromFileURLsKey());
}

void WebPreferences::deleteAllowFileAccessFromFileURLs()
{
    deleteKey(WebPreferencesKey::allowFileAccessFromFileURLsKey());
}

void WebPreferences::setAllowMultiElementImplicitSubmission(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::allowMultiElementImplicitSubmissionKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::allowMultiElementImplicitSubmissionKey(), value, false);
}

bool WebPreferences::allowMultiElementImplicitSubmission() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::allowMultiElementImplicitSubmissionKey());
}

void WebPreferences::deleteAllowMultiElementImplicitSubmission()
{
    deleteKey(WebPreferencesKey::allowMultiElementImplicitSubmissionKey());
}

void WebPreferences::setAllowRunningOfInsecureContent(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::allowRunningOfInsecureContentKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::allowRunningOfInsecureContentKey(), value, false);
}

bool WebPreferences::allowRunningOfInsecureContent() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::allowRunningOfInsecureContentKey());
}

void WebPreferences::deleteAllowRunningOfInsecureContent()
{
    deleteKey(WebPreferencesKey::allowRunningOfInsecureContentKey());
}

void WebPreferences::setAllowSettingAnyXHRHeaderFromFileURLs(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::allowSettingAnyXHRHeaderFromFileURLsKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::allowSettingAnyXHRHeaderFromFileURLsKey(), value, false);
}

bool WebPreferences::allowSettingAnyXHRHeaderFromFileURLs() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::allowSettingAnyXHRHeaderFromFileURLsKey());
}

void WebPreferences::deleteAllowSettingAnyXHRHeaderFromFileURLs()
{
    deleteKey(WebPreferencesKey::allowSettingAnyXHRHeaderFromFileURLsKey());
}

void WebPreferences::setAllowsAirPlayForMediaPlayback(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::allowsAirPlayForMediaPlaybackKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::allowsAirPlayForMediaPlaybackKey(), value, false);
}

bool WebPreferences::allowsAirPlayForMediaPlayback() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::allowsAirPlayForMediaPlaybackKey());
}

void WebPreferences::deleteAllowsAirPlayForMediaPlayback()
{
    deleteKey(WebPreferencesKey::allowsAirPlayForMediaPlaybackKey());
}

void WebPreferences::setAllowsInlineMediaPlayback(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::allowsInlineMediaPlaybackKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::allowsInlineMediaPlaybackKey(), value, false);
}

bool WebPreferences::allowsInlineMediaPlayback() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::allowsInlineMediaPlaybackKey());
}

void WebPreferences::deleteAllowsInlineMediaPlayback()
{
    deleteKey(WebPreferencesKey::allowsInlineMediaPlaybackKey());
}

void WebPreferences::setAllowsInlineMediaPlaybackAfterFullscreen(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::allowsInlineMediaPlaybackAfterFullscreenKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::allowsInlineMediaPlaybackAfterFullscreenKey(), value, false);
}

bool WebPreferences::allowsInlineMediaPlaybackAfterFullscreen() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::allowsInlineMediaPlaybackAfterFullscreenKey());
}

void WebPreferences::deleteAllowsInlineMediaPlaybackAfterFullscreen()
{
    deleteKey(WebPreferencesKey::allowsInlineMediaPlaybackAfterFullscreenKey());
}

void WebPreferences::setAllowsPictureInPictureMediaPlayback(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::allowsPictureInPictureMediaPlaybackKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::allowsPictureInPictureMediaPlaybackKey(), value, false);
}

bool WebPreferences::allowsPictureInPictureMediaPlayback() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::allowsPictureInPictureMediaPlaybackKey());
}

void WebPreferences::deleteAllowsPictureInPictureMediaPlayback()
{
    deleteKey(WebPreferencesKey::allowsPictureInPictureMediaPlaybackKey());
}

void WebPreferences::setAlternateFormControlDesignEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::alternateFormControlDesignEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::alternateFormControlDesignEnabledKey(), value, false);
}

bool WebPreferences::alternateFormControlDesignEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::alternateFormControlDesignEnabledKey());
}

void WebPreferences::deleteAlternateFormControlDesignEnabled()
{
    deleteKey(WebPreferencesKey::alternateFormControlDesignEnabledKey());
}

void WebPreferences::setAlternateFullScreenControlDesignEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::alternateFullScreenControlDesignEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::alternateFullScreenControlDesignEnabledKey(), value, false);
}

bool WebPreferences::alternateFullScreenControlDesignEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::alternateFullScreenControlDesignEnabledKey());
}

void WebPreferences::deleteAlternateFullScreenControlDesignEnabled()
{
    deleteKey(WebPreferencesKey::alternateFullScreenControlDesignEnabledKey());
}

void WebPreferences::setAnimatedImageAsyncDecodingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::animatedImageAsyncDecodingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::animatedImageAsyncDecodingEnabledKey(), value, false);
}

bool WebPreferences::animatedImageAsyncDecodingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::animatedImageAsyncDecodingEnabledKey());
}

void WebPreferences::deleteAnimatedImageAsyncDecodingEnabled()
{
    deleteKey(WebPreferencesKey::animatedImageAsyncDecodingEnabledKey());
}

void WebPreferences::setAppleMailPaginationQuirkEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::appleMailPaginationQuirkEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::appleMailPaginationQuirkEnabledKey(), value, false);
}

bool WebPreferences::appleMailPaginationQuirkEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::appleMailPaginationQuirkEnabledKey());
}

void WebPreferences::deleteAppleMailPaginationQuirkEnabled()
{
    deleteKey(WebPreferencesKey::appleMailPaginationQuirkEnabledKey());
}

void WebPreferences::setApplePayCapabilityDisclosureAllowed(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::applePayCapabilityDisclosureAllowedKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::applePayCapabilityDisclosureAllowedKey(), value, false);
}

bool WebPreferences::applePayCapabilityDisclosureAllowed() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::applePayCapabilityDisclosureAllowedKey());
}

void WebPreferences::deleteApplePayCapabilityDisclosureAllowed()
{
    deleteKey(WebPreferencesKey::applePayCapabilityDisclosureAllowedKey());
}

void WebPreferences::setApplePayEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::applePayEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::applePayEnabledKey(), value, false);
}

bool WebPreferences::applePayEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::applePayEnabledKey());
}

void WebPreferences::deleteApplePayEnabled()
{
    deleteKey(WebPreferencesKey::applePayEnabledKey());
}

void WebPreferences::setAsynchronousSpellCheckingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::asynchronousSpellCheckingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::asynchronousSpellCheckingEnabledKey(), value, false);
}

bool WebPreferences::asynchronousSpellCheckingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::asynchronousSpellCheckingEnabledKey());
}

void WebPreferences::deleteAsynchronousSpellCheckingEnabled()
{
    deleteKey(WebPreferencesKey::asynchronousSpellCheckingEnabledKey());
}

void WebPreferences::setAudioControlsScaleWithPageZoom(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::audioControlsScaleWithPageZoomKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::audioControlsScaleWithPageZoomKey(), value, false);
}

bool WebPreferences::audioControlsScaleWithPageZoom() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::audioControlsScaleWithPageZoomKey());
}

void WebPreferences::deleteAudioControlsScaleWithPageZoom()
{
    deleteKey(WebPreferencesKey::audioControlsScaleWithPageZoomKey());
}

void WebPreferences::setAuthorAndUserStylesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::authorAndUserStylesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::authorAndUserStylesEnabledKey(), value, false);
}

bool WebPreferences::authorAndUserStylesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::authorAndUserStylesEnabledKey());
}

void WebPreferences::deleteAuthorAndUserStylesEnabled()
{
    deleteKey(WebPreferencesKey::authorAndUserStylesEnabledKey());
}

void WebPreferences::setBackspaceKeyNavigationEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::backspaceKeyNavigationEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::backspaceKeyNavigationEnabledKey(), value, false);
}

bool WebPreferences::backspaceKeyNavigationEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::backspaceKeyNavigationEnabledKey());
}

void WebPreferences::deleteBackspaceKeyNavigationEnabled()
{
    deleteKey(WebPreferencesKey::backspaceKeyNavigationEnabledKey());
}

void WebPreferences::setCaretBrowsingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::caretBrowsingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::caretBrowsingEnabledKey(), value, false);
}

bool WebPreferences::caretBrowsingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::caretBrowsingEnabledKey());
}

void WebPreferences::deleteCaretBrowsingEnabled()
{
    deleteKey(WebPreferencesKey::caretBrowsingEnabledKey());
}

void WebPreferences::setColorFilterEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::colorFilterEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::colorFilterEnabledKey(), value, false);
}

bool WebPreferences::colorFilterEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::colorFilterEnabledKey());
}

void WebPreferences::deleteColorFilterEnabled()
{
    deleteKey(WebPreferencesKey::colorFilterEnabledKey());
}

void WebPreferences::setConstantPropertiesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::constantPropertiesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::constantPropertiesEnabledKey(), value, false);
}

bool WebPreferences::constantPropertiesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::constantPropertiesEnabledKey());
}

void WebPreferences::deleteConstantPropertiesEnabled()
{
    deleteKey(WebPreferencesKey::constantPropertiesEnabledKey());
}

void WebPreferences::setContentChangeObserverEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::contentChangeObserverEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::contentChangeObserverEnabledKey(), value, false);
}

bool WebPreferences::contentChangeObserverEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::contentChangeObserverEnabledKey());
}

void WebPreferences::deleteContentChangeObserverEnabled()
{
    deleteKey(WebPreferencesKey::contentChangeObserverEnabledKey());
}

void WebPreferences::setContentDispositionAttachmentSandboxEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::contentDispositionAttachmentSandboxEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::contentDispositionAttachmentSandboxEnabledKey(), value, false);
}

bool WebPreferences::contentDispositionAttachmentSandboxEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::contentDispositionAttachmentSandboxEnabledKey());
}

void WebPreferences::deleteContentDispositionAttachmentSandboxEnabled()
{
    deleteKey(WebPreferencesKey::contentDispositionAttachmentSandboxEnabledKey());
}

void WebPreferences::setContextMenuQRCodeDetectionEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::contextMenuQRCodeDetectionEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::contextMenuQRCodeDetectionEnabledKey(), value, false);
}

bool WebPreferences::contextMenuQRCodeDetectionEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::contextMenuQRCodeDetectionEnabledKey());
}

void WebPreferences::deleteContextMenuQRCodeDetectionEnabled()
{
    deleteKey(WebPreferencesKey::contextMenuQRCodeDetectionEnabledKey());
}

void WebPreferences::setCursiveFontFamily(const String& value)
{
    if (!m_store.setStringValueForKey(WebPreferencesKey::cursiveFontFamilyKey(), value))
        return;
    updateStringValueForKey(WebPreferencesKey::cursiveFontFamilyKey(), value, false);
}

String WebPreferences::cursiveFontFamily() const
{
    return m_store.getStringValueForKey(WebPreferencesKey::cursiveFontFamilyKey());
}

void WebPreferences::deleteCursiveFontFamily()
{
    deleteKey(WebPreferencesKey::cursiveFontFamilyKey());
}

void WebPreferences::setDNSPrefetchingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::dnsPrefetchingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::dnsPrefetchingEnabledKey(), value, false);
}

bool WebPreferences::dnsPrefetchingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::dnsPrefetchingEnabledKey());
}

void WebPreferences::deleteDNSPrefetchingEnabled()
{
    deleteKey(WebPreferencesKey::dnsPrefetchingEnabledKey());
}

void WebPreferences::setDOMPasteAllowed(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::domPasteAllowedKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::domPasteAllowedKey(), value, false);
}

bool WebPreferences::domPasteAllowed() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::domPasteAllowedKey());
}

void WebPreferences::deleteDOMPasteAllowed()
{
    deleteKey(WebPreferencesKey::domPasteAllowedKey());
}

void WebPreferences::setDataDetectorTypes(const uint32_t& value)
{
    if (!m_store.setUInt32ValueForKey(WebPreferencesKey::dataDetectorTypesKey(), value))
        return;
    updateUInt32ValueForKey(WebPreferencesKey::dataDetectorTypesKey(), value, false);
}

uint32_t WebPreferences::dataDetectorTypes() const
{
    return m_store.getUInt32ValueForKey(WebPreferencesKey::dataDetectorTypesKey());
}

void WebPreferences::deleteDataDetectorTypes()
{
    deleteKey(WebPreferencesKey::dataDetectorTypesKey());
}

void WebPreferences::setDatabasesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::databasesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::databasesEnabledKey(), value, false);
}

bool WebPreferences::databasesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::databasesEnabledKey());
}

void WebPreferences::deleteDatabasesEnabled()
{
    deleteKey(WebPreferencesKey::databasesEnabledKey());
}

void WebPreferences::setDefaultFixedFontSize(const double& value)
{
    if (!m_store.setDoubleValueForKey(WebPreferencesKey::defaultFixedFontSizeKey(), value))
        return;
    updateDoubleValueForKey(WebPreferencesKey::defaultFixedFontSizeKey(), value, false);
}

double WebPreferences::defaultFixedFontSize() const
{
    return m_store.getDoubleValueForKey(WebPreferencesKey::defaultFixedFontSizeKey());
}

void WebPreferences::deleteDefaultFixedFontSize()
{
    deleteKey(WebPreferencesKey::defaultFixedFontSizeKey());
}

void WebPreferences::setDefaultFontSize(const double& value)
{
    if (!m_store.setDoubleValueForKey(WebPreferencesKey::defaultFontSizeKey(), value))
        return;
    updateDoubleValueForKey(WebPreferencesKey::defaultFontSizeKey(), value, false);
}

double WebPreferences::defaultFontSize() const
{
    return m_store.getDoubleValueForKey(WebPreferencesKey::defaultFontSizeKey());
}

void WebPreferences::deleteDefaultFontSize()
{
    deleteKey(WebPreferencesKey::defaultFontSizeKey());
}

void WebPreferences::setDefaultTextEncodingName(const String& value)
{
    if (!m_store.setStringValueForKey(WebPreferencesKey::defaultTextEncodingNameKey(), value))
        return;
    updateStringValueForKey(WebPreferencesKey::defaultTextEncodingNameKey(), value, false);
}

String WebPreferences::defaultTextEncodingName() const
{
    return m_store.getStringValueForKey(WebPreferencesKey::defaultTextEncodingNameKey());
}

void WebPreferences::deleteDefaultTextEncodingName()
{
    deleteKey(WebPreferencesKey::defaultTextEncodingNameKey());
}

void WebPreferences::setDeveloperExtrasEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::developerExtrasEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::developerExtrasEnabledKey(), value, false);
}

bool WebPreferences::developerExtrasEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::developerExtrasEnabledKey());
}

void WebPreferences::deleteDeveloperExtrasEnabled()
{
    deleteKey(WebPreferencesKey::developerExtrasEnabledKey());
}

void WebPreferences::setDeviceHeight(const uint32_t& value)
{
    if (!m_store.setUInt32ValueForKey(WebPreferencesKey::deviceHeightKey(), value))
        return;
    updateUInt32ValueForKey(WebPreferencesKey::deviceHeightKey(), value, false);
}

uint32_t WebPreferences::deviceHeight() const
{
    return m_store.getUInt32ValueForKey(WebPreferencesKey::deviceHeightKey());
}

void WebPreferences::deleteDeviceHeight()
{
    deleteKey(WebPreferencesKey::deviceHeightKey());
}

void WebPreferences::setDeviceOrientationEventEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::deviceOrientationEventEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::deviceOrientationEventEnabledKey(), value, false);
}

bool WebPreferences::deviceOrientationEventEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::deviceOrientationEventEnabledKey());
}

void WebPreferences::deleteDeviceOrientationEventEnabled()
{
    deleteKey(WebPreferencesKey::deviceOrientationEventEnabledKey());
}

void WebPreferences::setDeviceOrientationPermissionAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::deviceOrientationPermissionAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::deviceOrientationPermissionAPIEnabledKey(), value, false);
}

bool WebPreferences::deviceOrientationPermissionAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::deviceOrientationPermissionAPIEnabledKey());
}

void WebPreferences::deleteDeviceOrientationPermissionAPIEnabled()
{
    deleteKey(WebPreferencesKey::deviceOrientationPermissionAPIEnabledKey());
}

void WebPreferences::setDeviceWidth(const uint32_t& value)
{
    if (!m_store.setUInt32ValueForKey(WebPreferencesKey::deviceWidthKey(), value))
        return;
    updateUInt32ValueForKey(WebPreferencesKey::deviceWidthKey(), value, false);
}

uint32_t WebPreferences::deviceWidth() const
{
    return m_store.getUInt32ValueForKey(WebPreferencesKey::deviceWidthKey());
}

void WebPreferences::deleteDeviceWidth()
{
    deleteKey(WebPreferencesKey::deviceWidthKey());
}

void WebPreferences::setDisabledAdaptationsMetaTagEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::disabledAdaptationsMetaTagEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::disabledAdaptationsMetaTagEnabledKey(), value, false);
}

bool WebPreferences::disabledAdaptationsMetaTagEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::disabledAdaptationsMetaTagEnabledKey());
}

void WebPreferences::deleteDisabledAdaptationsMetaTagEnabled()
{
    deleteKey(WebPreferencesKey::disabledAdaptationsMetaTagEnabledKey());
}

void WebPreferences::setDownloadAttributeEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::downloadAttributeEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::downloadAttributeEnabledKey(), value, false);
}

bool WebPreferences::downloadAttributeEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::downloadAttributeEnabledKey());
}

void WebPreferences::deleteDownloadAttributeEnabled()
{
    deleteKey(WebPreferencesKey::downloadAttributeEnabledKey());
}

void WebPreferences::setEditableLinkBehavior(const uint32_t& value)
{
    if (!m_store.setUInt32ValueForKey(WebPreferencesKey::editableLinkBehaviorKey(), value))
        return;
    updateUInt32ValueForKey(WebPreferencesKey::editableLinkBehaviorKey(), value, false);
}

uint32_t WebPreferences::editableLinkBehavior() const
{
    return m_store.getUInt32ValueForKey(WebPreferencesKey::editableLinkBehaviorKey());
}

void WebPreferences::deleteEditableLinkBehavior()
{
    deleteKey(WebPreferencesKey::editableLinkBehaviorKey());
}

void WebPreferences::setEnableInheritURIQueryComponent(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::enableInheritURIQueryComponentKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::enableInheritURIQueryComponentKey(), value, false);
}

bool WebPreferences::enableInheritURIQueryComponent() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::enableInheritURIQueryComponentKey());
}

void WebPreferences::deleteEnableInheritURIQueryComponent()
{
    deleteKey(WebPreferencesKey::enableInheritURIQueryComponentKey());
}

void WebPreferences::setEncryptedMediaAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::encryptedMediaAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::encryptedMediaAPIEnabledKey(), value, false);
}

bool WebPreferences::encryptedMediaAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::encryptedMediaAPIEnabledKey());
}

void WebPreferences::deleteEncryptedMediaAPIEnabled()
{
    deleteKey(WebPreferencesKey::encryptedMediaAPIEnabledKey());
}

void WebPreferences::setExtensibleSSOEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::isExtensibleSSOEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::isExtensibleSSOEnabledKey(), value, false);
}

bool WebPreferences::isExtensibleSSOEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::isExtensibleSSOEnabledKey());
}

void WebPreferences::deleteExtensibleSSOEnabled()
{
    deleteKey(WebPreferencesKey::isExtensibleSSOEnabledKey());
}

void WebPreferences::setFTPDirectoryTemplatePath(const String& value)
{
    if (!m_store.setStringValueForKey(WebPreferencesKey::ftpDirectoryTemplatePathKey(), value))
        return;
    updateStringValueForKey(WebPreferencesKey::ftpDirectoryTemplatePathKey(), value, false);
}

String WebPreferences::ftpDirectoryTemplatePath() const
{
    return m_store.getStringValueForKey(WebPreferencesKey::ftpDirectoryTemplatePathKey());
}

void WebPreferences::deleteFTPDirectoryTemplatePath()
{
    deleteKey(WebPreferencesKey::ftpDirectoryTemplatePathKey());
}

void WebPreferences::setFantasyFontFamily(const String& value)
{
    if (!m_store.setStringValueForKey(WebPreferencesKey::fantasyFontFamilyKey(), value))
        return;
    updateStringValueForKey(WebPreferencesKey::fantasyFontFamilyKey(), value, false);
}

String WebPreferences::fantasyFontFamily() const
{
    return m_store.getStringValueForKey(WebPreferencesKey::fantasyFontFamilyKey());
}

void WebPreferences::deleteFantasyFontFamily()
{
    deleteKey(WebPreferencesKey::fantasyFontFamilyKey());
}

void WebPreferences::setFixedFontFamily(const String& value)
{
    if (!m_store.setStringValueForKey(WebPreferencesKey::fixedFontFamilyKey(), value))
        return;
    updateStringValueForKey(WebPreferencesKey::fixedFontFamilyKey(), value, false);
}

String WebPreferences::fixedFontFamily() const
{
    return m_store.getStringValueForKey(WebPreferencesKey::fixedFontFamilyKey());
}

void WebPreferences::deleteFixedFontFamily()
{
    deleteKey(WebPreferencesKey::fixedFontFamilyKey());
}

void WebPreferences::setForceCompositingMode(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::forceCompositingModeKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::forceCompositingModeKey(), value, false);
}

bool WebPreferences::forceCompositingMode() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::forceCompositingModeKey());
}

void WebPreferences::deleteForceCompositingMode()
{
    deleteKey(WebPreferencesKey::forceCompositingModeKey());
}

void WebPreferences::setForceFTPDirectoryListings(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::forceFTPDirectoryListingsKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::forceFTPDirectoryListingsKey(), value, false);
}

bool WebPreferences::forceFTPDirectoryListings() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::forceFTPDirectoryListingsKey());
}

void WebPreferences::deleteForceFTPDirectoryListings()
{
    deleteKey(WebPreferencesKey::forceFTPDirectoryListingsKey());
}

void WebPreferences::setForceWebGLUsesLowPower(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::forceWebGLUsesLowPowerKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::forceWebGLUsesLowPowerKey(), value, false);
}

bool WebPreferences::forceWebGLUsesLowPower() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::forceWebGLUsesLowPowerKey());
}

void WebPreferences::deleteForceWebGLUsesLowPower()
{
    deleteKey(WebPreferencesKey::forceWebGLUsesLowPowerKey());
}

void WebPreferences::setGStreamerEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::isGStreamerEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::isGStreamerEnabledKey(), value, false);
}

bool WebPreferences::isGStreamerEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::isGStreamerEnabledKey());
}

void WebPreferences::deleteGStreamerEnabled()
{
    deleteKey(WebPreferencesKey::isGStreamerEnabledKey());
}

void WebPreferences::setHiddenPageCSSAnimationSuspensionEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::hiddenPageCSSAnimationSuspensionEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::hiddenPageCSSAnimationSuspensionEnabledKey(), value, false);
}

bool WebPreferences::hiddenPageCSSAnimationSuspensionEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::hiddenPageCSSAnimationSuspensionEnabledKey());
}

void WebPreferences::deleteHiddenPageCSSAnimationSuspensionEnabled()
{
    deleteKey(WebPreferencesKey::hiddenPageCSSAnimationSuspensionEnabledKey());
}

void WebPreferences::setInactiveMediaCaptureSteamRepromptIntervalInMinutes(const double& value)
{
    if (!m_store.setDoubleValueForKey(WebPreferencesKey::inactiveMediaCaptureSteamRepromptIntervalInMinutesKey(), value))
        return;
    updateDoubleValueForKey(WebPreferencesKey::inactiveMediaCaptureSteamRepromptIntervalInMinutesKey(), value, false);
}

double WebPreferences::inactiveMediaCaptureSteamRepromptIntervalInMinutes() const
{
    return m_store.getDoubleValueForKey(WebPreferencesKey::inactiveMediaCaptureSteamRepromptIntervalInMinutesKey());
}

void WebPreferences::deleteInactiveMediaCaptureSteamRepromptIntervalInMinutes()
{
    deleteKey(WebPreferencesKey::inactiveMediaCaptureSteamRepromptIntervalInMinutesKey());
}

void WebPreferences::setIncompleteImageBorderEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::incompleteImageBorderEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::incompleteImageBorderEnabledKey(), value, false);
}

bool WebPreferences::incompleteImageBorderEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::incompleteImageBorderEnabledKey());
}

void WebPreferences::deleteIncompleteImageBorderEnabled()
{
    deleteKey(WebPreferencesKey::incompleteImageBorderEnabledKey());
}

void WebPreferences::setIncrementalPDFLoadingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::incrementalPDFLoadingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::incrementalPDFLoadingEnabledKey(), value, false);
}

bool WebPreferences::incrementalPDFLoadingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::incrementalPDFLoadingEnabledKey());
}

void WebPreferences::deleteIncrementalPDFLoadingEnabled()
{
    deleteKey(WebPreferencesKey::incrementalPDFLoadingEnabledKey());
}

void WebPreferences::setIncrementalRenderingSuppressionTimeout(const double& value)
{
    if (!m_store.setDoubleValueForKey(WebPreferencesKey::incrementalRenderingSuppressionTimeoutKey(), value))
        return;
    updateDoubleValueForKey(WebPreferencesKey::incrementalRenderingSuppressionTimeoutKey(), value, false);
}

double WebPreferences::incrementalRenderingSuppressionTimeout() const
{
    return m_store.getDoubleValueForKey(WebPreferencesKey::incrementalRenderingSuppressionTimeoutKey());
}

void WebPreferences::deleteIncrementalRenderingSuppressionTimeout()
{
    deleteKey(WebPreferencesKey::incrementalRenderingSuppressionTimeoutKey());
}

void WebPreferences::setInlineMediaPlaybackRequiresPlaysInlineAttribute(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::inlineMediaPlaybackRequiresPlaysInlineAttributeKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::inlineMediaPlaybackRequiresPlaysInlineAttributeKey(), value, false);
}

bool WebPreferences::inlineMediaPlaybackRequiresPlaysInlineAttribute() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::inlineMediaPlaybackRequiresPlaysInlineAttributeKey());
}

void WebPreferences::deleteInlineMediaPlaybackRequiresPlaysInlineAttribute()
{
    deleteKey(WebPreferencesKey::inlineMediaPlaybackRequiresPlaysInlineAttributeKey());
}

void WebPreferences::setInspectorAttachedHeight(const uint32_t& value)
{
    if (!m_store.setUInt32ValueForKey(WebPreferencesKey::inspectorAttachedHeightKey(), value))
        return;
    updateUInt32ValueForKey(WebPreferencesKey::inspectorAttachedHeightKey(), value, false);
}

uint32_t WebPreferences::inspectorAttachedHeight() const
{
    return m_store.getUInt32ValueForKey(WebPreferencesKey::inspectorAttachedHeightKey());
}

void WebPreferences::deleteInspectorAttachedHeight()
{
    deleteKey(WebPreferencesKey::inspectorAttachedHeightKey());
}

void WebPreferences::setInspectorAttachedWidth(const uint32_t& value)
{
    if (!m_store.setUInt32ValueForKey(WebPreferencesKey::inspectorAttachedWidthKey(), value))
        return;
    updateUInt32ValueForKey(WebPreferencesKey::inspectorAttachedWidthKey(), value, false);
}

uint32_t WebPreferences::inspectorAttachedWidth() const
{
    return m_store.getUInt32ValueForKey(WebPreferencesKey::inspectorAttachedWidthKey());
}

void WebPreferences::deleteInspectorAttachedWidth()
{
    deleteKey(WebPreferencesKey::inspectorAttachedWidthKey());
}

void WebPreferences::setInspectorAttachmentSide(const uint32_t& value)
{
    if (!m_store.setUInt32ValueForKey(WebPreferencesKey::inspectorAttachmentSideKey(), value))
        return;
    updateUInt32ValueForKey(WebPreferencesKey::inspectorAttachmentSideKey(), value, false);
}

uint32_t WebPreferences::inspectorAttachmentSide() const
{
    return m_store.getUInt32ValueForKey(WebPreferencesKey::inspectorAttachmentSideKey());
}

void WebPreferences::deleteInspectorAttachmentSide()
{
    deleteKey(WebPreferencesKey::inspectorAttachmentSideKey());
}

void WebPreferences::setInspectorStartsAttached(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::inspectorStartsAttachedKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::inspectorStartsAttachedKey(), value, false);
}

bool WebPreferences::inspectorStartsAttached() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::inspectorStartsAttachedKey());
}

void WebPreferences::deleteInspectorStartsAttached()
{
    deleteKey(WebPreferencesKey::inspectorStartsAttachedKey());
}

void WebPreferences::setInspectorWindowFrame(const String& value)
{
    if (!m_store.setStringValueForKey(WebPreferencesKey::inspectorWindowFrameKey(), value))
        return;
    updateStringValueForKey(WebPreferencesKey::inspectorWindowFrameKey(), value, false);
}

String WebPreferences::inspectorWindowFrame() const
{
    return m_store.getStringValueForKey(WebPreferencesKey::inspectorWindowFrameKey());
}

void WebPreferences::deleteInspectorWindowFrame()
{
    deleteKey(WebPreferencesKey::inspectorWindowFrameKey());
}

void WebPreferences::setInteractionRegionInlinePadding(const double& value)
{
    if (!m_store.setDoubleValueForKey(WebPreferencesKey::interactionRegionInlinePaddingKey(), value))
        return;
    updateDoubleValueForKey(WebPreferencesKey::interactionRegionInlinePaddingKey(), value, false);
}

double WebPreferences::interactionRegionInlinePadding() const
{
    return m_store.getDoubleValueForKey(WebPreferencesKey::interactionRegionInlinePaddingKey());
}

void WebPreferences::deleteInteractionRegionInlinePadding()
{
    deleteKey(WebPreferencesKey::interactionRegionInlinePaddingKey());
}

void WebPreferences::setInteractionRegionMinimumCornerRadius(const double& value)
{
    if (!m_store.setDoubleValueForKey(WebPreferencesKey::interactionRegionMinimumCornerRadiusKey(), value))
        return;
    updateDoubleValueForKey(WebPreferencesKey::interactionRegionMinimumCornerRadiusKey(), value, false);
}

double WebPreferences::interactionRegionMinimumCornerRadius() const
{
    return m_store.getDoubleValueForKey(WebPreferencesKey::interactionRegionMinimumCornerRadiusKey());
}

void WebPreferences::deleteInteractionRegionMinimumCornerRadius()
{
    deleteKey(WebPreferencesKey::interactionRegionMinimumCornerRadiusKey());
}

void WebPreferences::setInterruptAudioOnPageVisibilityChangeEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::interruptAudioOnPageVisibilityChangeEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::interruptAudioOnPageVisibilityChangeEnabledKey(), value, false);
}

bool WebPreferences::interruptAudioOnPageVisibilityChangeEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::interruptAudioOnPageVisibilityChangeEnabledKey());
}

void WebPreferences::deleteInterruptAudioOnPageVisibilityChangeEnabled()
{
    deleteKey(WebPreferencesKey::interruptAudioOnPageVisibilityChangeEnabledKey());
}

void WebPreferences::setInterruptVideoOnPageVisibilityChangeEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::interruptVideoOnPageVisibilityChangeEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::interruptVideoOnPageVisibilityChangeEnabledKey(), value, false);
}

bool WebPreferences::interruptVideoOnPageVisibilityChangeEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::interruptVideoOnPageVisibilityChangeEnabledKey());
}

void WebPreferences::deleteInterruptVideoOnPageVisibilityChangeEnabled()
{
    deleteKey(WebPreferencesKey::interruptVideoOnPageVisibilityChangeEnabledKey());
}

void WebPreferences::setInvisibleAutoplayNotPermitted(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::invisibleAutoplayNotPermittedKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::invisibleAutoplayNotPermittedKey(), value, false);
}

bool WebPreferences::invisibleAutoplayNotPermitted() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::invisibleAutoplayNotPermittedKey());
}

void WebPreferences::deleteInvisibleAutoplayNotPermitted()
{
    deleteKey(WebPreferencesKey::invisibleAutoplayNotPermittedKey());
}

void WebPreferences::setJavaScriptCanAccessClipboard(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::javaScriptCanAccessClipboardKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::javaScriptCanAccessClipboardKey(), value, false);
}

bool WebPreferences::javaScriptCanAccessClipboard() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::javaScriptCanAccessClipboardKey());
}

void WebPreferences::deleteJavaScriptCanAccessClipboard()
{
    deleteKey(WebPreferencesKey::javaScriptCanAccessClipboardKey());
}

void WebPreferences::setJavaScriptCanOpenWindowsAutomatically(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::javaScriptCanOpenWindowsAutomaticallyKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::javaScriptCanOpenWindowsAutomaticallyKey(), value, false);
}

bool WebPreferences::javaScriptCanOpenWindowsAutomatically() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::javaScriptCanOpenWindowsAutomaticallyKey());
}

void WebPreferences::deleteJavaScriptCanOpenWindowsAutomatically()
{
    deleteKey(WebPreferencesKey::javaScriptCanOpenWindowsAutomaticallyKey());
}

void WebPreferences::setJavaScriptMarkupEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::javaScriptMarkupEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::javaScriptMarkupEnabledKey(), value, false);
}

bool WebPreferences::javaScriptMarkupEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::javaScriptMarkupEnabledKey());
}

void WebPreferences::deleteJavaScriptMarkupEnabled()
{
    deleteKey(WebPreferencesKey::javaScriptMarkupEnabledKey());
}

void WebPreferences::setJavaScriptRuntimeFlags(const uint32_t& value)
{
    if (!m_store.setUInt32ValueForKey(WebPreferencesKey::javaScriptRuntimeFlagsKey(), value))
        return;
    updateUInt32ValueForKey(WebPreferencesKey::javaScriptRuntimeFlagsKey(), value, false);
}

uint32_t WebPreferences::javaScriptRuntimeFlags() const
{
    return m_store.getUInt32ValueForKey(WebPreferencesKey::javaScriptRuntimeFlagsKey());
}

void WebPreferences::deleteJavaScriptRuntimeFlags()
{
    deleteKey(WebPreferencesKey::javaScriptRuntimeFlagsKey());
}

void WebPreferences::setLargeImageAsyncDecodingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::largeImageAsyncDecodingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::largeImageAsyncDecodingEnabledKey(), value, false);
}

bool WebPreferences::largeImageAsyncDecodingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::largeImageAsyncDecodingEnabledKey());
}

void WebPreferences::deleteLargeImageAsyncDecodingEnabled()
{
    deleteKey(WebPreferencesKey::largeImageAsyncDecodingEnabledKey());
}

void WebPreferences::setLayoutFallbackWidth(const uint32_t& value)
{
    if (!m_store.setUInt32ValueForKey(WebPreferencesKey::layoutFallbackWidthKey(), value))
        return;
    updateUInt32ValueForKey(WebPreferencesKey::layoutFallbackWidthKey(), value, false);
}

uint32_t WebPreferences::layoutFallbackWidth() const
{
    return m_store.getUInt32ValueForKey(WebPreferencesKey::layoutFallbackWidthKey());
}

void WebPreferences::deleteLayoutFallbackWidth()
{
    deleteKey(WebPreferencesKey::layoutFallbackWidthKey());
}

void WebPreferences::setLayoutViewportHeightExpansionFactor(const double& value)
{
    if (!m_store.setDoubleValueForKey(WebPreferencesKey::layoutViewportHeightExpansionFactorKey(), value))
        return;
    updateDoubleValueForKey(WebPreferencesKey::layoutViewportHeightExpansionFactorKey(), value, false);
}

double WebPreferences::layoutViewportHeightExpansionFactor() const
{
    return m_store.getDoubleValueForKey(WebPreferencesKey::layoutViewportHeightExpansionFactorKey());
}

void WebPreferences::deleteLayoutViewportHeightExpansionFactor()
{
    deleteKey(WebPreferencesKey::layoutViewportHeightExpansionFactorKey());
}

void WebPreferences::setLinkPreconnect(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::linkPreconnectKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::linkPreconnectKey(), value, false);
}

bool WebPreferences::linkPreconnect() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::linkPreconnectKey());
}

void WebPreferences::deleteLinkPreconnect()
{
    deleteKey(WebPreferencesKey::linkPreconnectKey());
}

void WebPreferences::setLinkPreloadEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::linkPreloadEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::linkPreloadEnabledKey(), value, false);
}

bool WebPreferences::linkPreloadEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::linkPreloadEnabledKey());
}

void WebPreferences::deleteLinkPreloadEnabled()
{
    deleteKey(WebPreferencesKey::linkPreloadEnabledKey());
}

void WebPreferences::setLoadDeferringEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::loadDeferringEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::loadDeferringEnabledKey(), value, false);
}

bool WebPreferences::loadDeferringEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::loadDeferringEnabledKey());
}

void WebPreferences::deleteLoadDeferringEnabled()
{
    deleteKey(WebPreferencesKey::loadDeferringEnabledKey());
}

void WebPreferences::setLoadsImagesAutomatically(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::loadsImagesAutomaticallyKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::loadsImagesAutomaticallyKey(), value, false);
}

bool WebPreferences::loadsImagesAutomatically() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::loadsImagesAutomaticallyKey());
}

void WebPreferences::deleteLoadsImagesAutomatically()
{
    deleteKey(WebPreferencesKey::loadsImagesAutomaticallyKey());
}

void WebPreferences::setLongRunningMediaCaptureStreamRepromptIntervalInHours(const double& value)
{
    if (!m_store.setDoubleValueForKey(WebPreferencesKey::longRunningMediaCaptureStreamRepromptIntervalInHoursKey(), value))
        return;
    updateDoubleValueForKey(WebPreferencesKey::longRunningMediaCaptureStreamRepromptIntervalInHoursKey(), value, false);
}

double WebPreferences::longRunningMediaCaptureStreamRepromptIntervalInHours() const
{
    return m_store.getDoubleValueForKey(WebPreferencesKey::longRunningMediaCaptureStreamRepromptIntervalInHoursKey());
}

void WebPreferences::deleteLongRunningMediaCaptureStreamRepromptIntervalInHours()
{
    deleteKey(WebPreferencesKey::longRunningMediaCaptureStreamRepromptIntervalInHoursKey());
}

void WebPreferences::setLowPowerVideoAudioBufferSizeEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::lowPowerVideoAudioBufferSizeEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::lowPowerVideoAudioBufferSizeEnabledKey(), value, false);
}

bool WebPreferences::lowPowerVideoAudioBufferSizeEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::lowPowerVideoAudioBufferSizeEnabledKey());
}

void WebPreferences::deleteLowPowerVideoAudioBufferSizeEnabled()
{
    deleteKey(WebPreferencesKey::lowPowerVideoAudioBufferSizeEnabledKey());
}

void WebPreferences::setManagedMediaSourceHighThreshold(const double& value)
{
    if (!m_store.setDoubleValueForKey(WebPreferencesKey::managedMediaSourceHighThresholdKey(), value))
        return;
    updateDoubleValueForKey(WebPreferencesKey::managedMediaSourceHighThresholdKey(), value, false);
}

double WebPreferences::managedMediaSourceHighThreshold() const
{
    return m_store.getDoubleValueForKey(WebPreferencesKey::managedMediaSourceHighThresholdKey());
}

void WebPreferences::deleteManagedMediaSourceHighThreshold()
{
    deleteKey(WebPreferencesKey::managedMediaSourceHighThresholdKey());
}

void WebPreferences::setManagedMediaSourceLowThreshold(const double& value)
{
    if (!m_store.setDoubleValueForKey(WebPreferencesKey::managedMediaSourceLowThresholdKey(), value))
        return;
    updateDoubleValueForKey(WebPreferencesKey::managedMediaSourceLowThresholdKey(), value, false);
}

double WebPreferences::managedMediaSourceLowThreshold() const
{
    return m_store.getDoubleValueForKey(WebPreferencesKey::managedMediaSourceLowThresholdKey());
}

void WebPreferences::deleteManagedMediaSourceLowThreshold()
{
    deleteKey(WebPreferencesKey::managedMediaSourceLowThresholdKey());
}

void WebPreferences::setMathMLEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mathMLEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mathMLEnabledKey(), value, false);
}

bool WebPreferences::mathMLEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mathMLEnabledKey());
}

void WebPreferences::deleteMathMLEnabled()
{
    deleteKey(WebPreferencesKey::mathMLEnabledKey());
}

void WebPreferences::setMaxParseDuration(const double& value)
{
    if (!m_store.setDoubleValueForKey(WebPreferencesKey::maxParseDurationKey(), value))
        return;
    updateDoubleValueForKey(WebPreferencesKey::maxParseDurationKey(), value, false);
}

double WebPreferences::maxParseDuration() const
{
    return m_store.getDoubleValueForKey(WebPreferencesKey::maxParseDurationKey());
}

void WebPreferences::deleteMaxParseDuration()
{
    deleteKey(WebPreferencesKey::maxParseDurationKey());
}

void WebPreferences::setMediaAudioCodecIDsAllowedInLockdownMode(const String& value)
{
    if (!m_store.setStringValueForKey(WebPreferencesKey::mediaAudioCodecIDsAllowedInLockdownModeKey(), value))
        return;
    updateStringValueForKey(WebPreferencesKey::mediaAudioCodecIDsAllowedInLockdownModeKey(), value, false);
}

String WebPreferences::mediaAudioCodecIDsAllowedInLockdownMode() const
{
    return m_store.getStringValueForKey(WebPreferencesKey::mediaAudioCodecIDsAllowedInLockdownModeKey());
}

void WebPreferences::deleteMediaAudioCodecIDsAllowedInLockdownMode()
{
    deleteKey(WebPreferencesKey::mediaAudioCodecIDsAllowedInLockdownModeKey());
}

void WebPreferences::setMediaCapabilitiesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mediaCapabilitiesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mediaCapabilitiesEnabledKey(), value, false);
}

bool WebPreferences::mediaCapabilitiesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mediaCapabilitiesEnabledKey());
}

void WebPreferences::deleteMediaCapabilitiesEnabled()
{
    deleteKey(WebPreferencesKey::mediaCapabilitiesEnabledKey());
}

void WebPreferences::setMediaCaptionFormatTypesAllowedInLockdownMode(const String& value)
{
    if (!m_store.setStringValueForKey(WebPreferencesKey::mediaCaptionFormatTypesAllowedInLockdownModeKey(), value))
        return;
    updateStringValueForKey(WebPreferencesKey::mediaCaptionFormatTypesAllowedInLockdownModeKey(), value, false);
}

String WebPreferences::mediaCaptionFormatTypesAllowedInLockdownMode() const
{
    return m_store.getStringValueForKey(WebPreferencesKey::mediaCaptionFormatTypesAllowedInLockdownModeKey());
}

void WebPreferences::deleteMediaCaptionFormatTypesAllowedInLockdownMode()
{
    deleteKey(WebPreferencesKey::mediaCaptionFormatTypesAllowedInLockdownModeKey());
}

void WebPreferences::setMediaCodecTypesAllowedInLockdownMode(const String& value)
{
    if (!m_store.setStringValueForKey(WebPreferencesKey::mediaCodecTypesAllowedInLockdownModeKey(), value))
        return;
    updateStringValueForKey(WebPreferencesKey::mediaCodecTypesAllowedInLockdownModeKey(), value, false);
}

String WebPreferences::mediaCodecTypesAllowedInLockdownMode() const
{
    return m_store.getStringValueForKey(WebPreferencesKey::mediaCodecTypesAllowedInLockdownModeKey());
}

void WebPreferences::deleteMediaCodecTypesAllowedInLockdownMode()
{
    deleteKey(WebPreferencesKey::mediaCodecTypesAllowedInLockdownModeKey());
}

void WebPreferences::setMediaContainerTypesAllowedInLockdownMode(const String& value)
{
    if (!m_store.setStringValueForKey(WebPreferencesKey::mediaContainerTypesAllowedInLockdownModeKey(), value))
        return;
    updateStringValueForKey(WebPreferencesKey::mediaContainerTypesAllowedInLockdownModeKey(), value, false);
}

String WebPreferences::mediaContainerTypesAllowedInLockdownMode() const
{
    return m_store.getStringValueForKey(WebPreferencesKey::mediaContainerTypesAllowedInLockdownModeKey());
}

void WebPreferences::deleteMediaContainerTypesAllowedInLockdownMode()
{
    deleteKey(WebPreferencesKey::mediaContainerTypesAllowedInLockdownModeKey());
}

void WebPreferences::setMediaContentTypesRequiringHardwareSupport(const String& value)
{
    if (!m_store.setStringValueForKey(WebPreferencesKey::mediaContentTypesRequiringHardwareSupportKey(), value))
        return;
    updateStringValueForKey(WebPreferencesKey::mediaContentTypesRequiringHardwareSupportKey(), value, false);
}

String WebPreferences::mediaContentTypesRequiringHardwareSupport() const
{
    return m_store.getStringValueForKey(WebPreferencesKey::mediaContentTypesRequiringHardwareSupportKey());
}

void WebPreferences::deleteMediaContentTypesRequiringHardwareSupport()
{
    deleteKey(WebPreferencesKey::mediaContentTypesRequiringHardwareSupportKey());
}

void WebPreferences::setMediaControlsContextMenusEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mediaControlsContextMenusEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mediaControlsContextMenusEnabledKey(), value, false);
}

bool WebPreferences::mediaControlsContextMenusEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mediaControlsContextMenusEnabledKey());
}

void WebPreferences::deleteMediaControlsContextMenusEnabled()
{
    deleteKey(WebPreferencesKey::mediaControlsContextMenusEnabledKey());
}

void WebPreferences::setMediaControlsScaleWithPageZoom(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mediaControlsScaleWithPageZoomKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mediaControlsScaleWithPageZoomKey(), value, false);
}

bool WebPreferences::mediaControlsScaleWithPageZoom() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mediaControlsScaleWithPageZoomKey());
}

void WebPreferences::deleteMediaControlsScaleWithPageZoom()
{
    deleteKey(WebPreferencesKey::mediaControlsScaleWithPageZoomKey());
}

void WebPreferences::setMediaDataLoadsAutomatically(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mediaDataLoadsAutomaticallyKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mediaDataLoadsAutomaticallyKey(), value, false);
}

bool WebPreferences::mediaDataLoadsAutomatically() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mediaDataLoadsAutomaticallyKey());
}

void WebPreferences::deleteMediaDataLoadsAutomatically()
{
    deleteKey(WebPreferencesKey::mediaDataLoadsAutomaticallyKey());
}

void WebPreferences::setMediaEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mediaEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mediaEnabledKey(), value, false);
}

bool WebPreferences::mediaEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mediaEnabledKey());
}

void WebPreferences::deleteMediaEnabled()
{
    deleteKey(WebPreferencesKey::mediaEnabledKey());
}

void WebPreferences::setMediaPreferredFullscreenWidth(const double& value)
{
    if (!m_store.setDoubleValueForKey(WebPreferencesKey::mediaPreferredFullscreenWidthKey(), value))
        return;
    updateDoubleValueForKey(WebPreferencesKey::mediaPreferredFullscreenWidthKey(), value, false);
}

double WebPreferences::mediaPreferredFullscreenWidth() const
{
    return m_store.getDoubleValueForKey(WebPreferencesKey::mediaPreferredFullscreenWidthKey());
}

void WebPreferences::deleteMediaPreferredFullscreenWidth()
{
    deleteKey(WebPreferencesKey::mediaPreferredFullscreenWidthKey());
}

void WebPreferences::setMediaPreloadingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mediaPreloadingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mediaPreloadingEnabledKey(), value, false);
}

bool WebPreferences::mediaPreloadingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mediaPreloadingEnabledKey());
}

void WebPreferences::deleteMediaPreloadingEnabled()
{
    deleteKey(WebPreferencesKey::mediaPreloadingEnabledKey());
}

void WebPreferences::setMediaStreamEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mediaStreamEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mediaStreamEnabledKey(), value, false);
}

bool WebPreferences::mediaStreamEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mediaStreamEnabledKey());
}

void WebPreferences::deleteMediaStreamEnabled()
{
    deleteKey(WebPreferencesKey::mediaStreamEnabledKey());
}

void WebPreferences::setMediaUserGestureInheritsFromDocument(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mediaUserGestureInheritsFromDocumentKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mediaUserGestureInheritsFromDocumentKey(), value, false);
}

bool WebPreferences::mediaUserGestureInheritsFromDocument() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mediaUserGestureInheritsFromDocumentKey());
}

void WebPreferences::deleteMediaUserGestureInheritsFromDocument()
{
    deleteKey(WebPreferencesKey::mediaUserGestureInheritsFromDocumentKey());
}

void WebPreferences::setMediaVideoCodecIDsAllowedInLockdownMode(const String& value)
{
    if (!m_store.setStringValueForKey(WebPreferencesKey::mediaVideoCodecIDsAllowedInLockdownModeKey(), value))
        return;
    updateStringValueForKey(WebPreferencesKey::mediaVideoCodecIDsAllowedInLockdownModeKey(), value, false);
}

String WebPreferences::mediaVideoCodecIDsAllowedInLockdownMode() const
{
    return m_store.getStringValueForKey(WebPreferencesKey::mediaVideoCodecIDsAllowedInLockdownModeKey());
}

void WebPreferences::deleteMediaVideoCodecIDsAllowedInLockdownMode()
{
    deleteKey(WebPreferencesKey::mediaVideoCodecIDsAllowedInLockdownModeKey());
}

void WebPreferences::setMenuItemElementEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::menuItemElementEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::menuItemElementEnabledKey(), value, false);
}

bool WebPreferences::menuItemElementEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::menuItemElementEnabledKey());
}

void WebPreferences::deleteMenuItemElementEnabled()
{
    deleteKey(WebPreferencesKey::menuItemElementEnabledKey());
}

void WebPreferences::setMinimumFontSize(const double& value)
{
    if (!m_store.setDoubleValueForKey(WebPreferencesKey::minimumFontSizeKey(), value))
        return;
    updateDoubleValueForKey(WebPreferencesKey::minimumFontSizeKey(), value, false);
}

double WebPreferences::minimumFontSize() const
{
    return m_store.getDoubleValueForKey(WebPreferencesKey::minimumFontSizeKey());
}

void WebPreferences::deleteMinimumFontSize()
{
    deleteKey(WebPreferencesKey::minimumFontSizeKey());
}

void WebPreferences::setMinimumLogicalFontSize(const double& value)
{
    if (!m_store.setDoubleValueForKey(WebPreferencesKey::minimumLogicalFontSizeKey(), value))
        return;
    updateDoubleValueForKey(WebPreferencesKey::minimumLogicalFontSizeKey(), value, false);
}

double WebPreferences::minimumLogicalFontSize() const
{
    return m_store.getDoubleValueForKey(WebPreferencesKey::minimumLogicalFontSizeKey());
}

void WebPreferences::deleteMinimumLogicalFontSize()
{
    deleteKey(WebPreferencesKey::minimumLogicalFontSizeKey());
}

void WebPreferences::setMinimumZoomFontSize(const double& value)
{
    if (!m_store.setDoubleValueForKey(WebPreferencesKey::minimumZoomFontSizeKey(), value))
        return;
    updateDoubleValueForKey(WebPreferencesKey::minimumZoomFontSizeKey(), value, false);
}

double WebPreferences::minimumZoomFontSize() const
{
    return m_store.getDoubleValueForKey(WebPreferencesKey::minimumZoomFontSizeKey());
}

void WebPreferences::deleteMinimumZoomFontSize()
{
    deleteKey(WebPreferencesKey::minimumZoomFontSizeKey());
}

void WebPreferences::setMockCaptureDevicesPromptEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mockCaptureDevicesPromptEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mockCaptureDevicesPromptEnabledKey(), value, false);
}

bool WebPreferences::mockCaptureDevicesPromptEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mockCaptureDevicesPromptEnabledKey());
}

void WebPreferences::deleteMockCaptureDevicesPromptEnabled()
{
    deleteKey(WebPreferencesKey::mockCaptureDevicesPromptEnabledKey());
}

void WebPreferences::setMockScrollbarsControllerEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mockScrollbarsControllerEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mockScrollbarsControllerEnabledKey(), value, false);
}

bool WebPreferences::mockScrollbarsControllerEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mockScrollbarsControllerEnabledKey());
}

void WebPreferences::deleteMockScrollbarsControllerEnabled()
{
    deleteKey(WebPreferencesKey::mockScrollbarsControllerEnabledKey());
}

void WebPreferences::setMockScrollbarsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mockScrollbarsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mockScrollbarsEnabledKey(), value, false);
}

bool WebPreferences::mockScrollbarsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mockScrollbarsEnabledKey());
}

void WebPreferences::deleteMockScrollbarsEnabled()
{
    deleteKey(WebPreferencesKey::mockScrollbarsEnabledKey());
}

void WebPreferences::setNeedsAdobeFrameReloadingQuirk(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::needsAdobeFrameReloadingQuirkKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::needsAdobeFrameReloadingQuirkKey(), value, false);
}

bool WebPreferences::needsAdobeFrameReloadingQuirk() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::needsAdobeFrameReloadingQuirkKey());
}

void WebPreferences::deleteNeedsAdobeFrameReloadingQuirk()
{
    deleteKey(WebPreferencesKey::needsAdobeFrameReloadingQuirkKey());
}

void WebPreferences::setNeedsFrameNameFallbackToIdQuirk(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::needsFrameNameFallbackToIdQuirkKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::needsFrameNameFallbackToIdQuirkKey(), value, false);
}

bool WebPreferences::needsFrameNameFallbackToIdQuirk() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::needsFrameNameFallbackToIdQuirkKey());
}

void WebPreferences::deleteNeedsFrameNameFallbackToIdQuirk()
{
    deleteKey(WebPreferencesKey::needsFrameNameFallbackToIdQuirkKey());
}

void WebPreferences::setNeedsKeyboardEventDisambiguationQuirks(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::needsKeyboardEventDisambiguationQuirksKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::needsKeyboardEventDisambiguationQuirksKey(), value, false);
}

bool WebPreferences::needsKeyboardEventDisambiguationQuirks() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::needsKeyboardEventDisambiguationQuirksKey());
}

void WebPreferences::deleteNeedsKeyboardEventDisambiguationQuirks()
{
    deleteKey(WebPreferencesKey::needsKeyboardEventDisambiguationQuirksKey());
}

void WebPreferences::setOfflineWebApplicationCacheEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::offlineWebApplicationCacheEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::offlineWebApplicationCacheEnabledKey(), value, false);
}

bool WebPreferences::offlineWebApplicationCacheEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::offlineWebApplicationCacheEnabledKey());
}

void WebPreferences::deleteOfflineWebApplicationCacheEnabled()
{
    deleteKey(WebPreferencesKey::offlineWebApplicationCacheEnabledKey());
}

void WebPreferences::setPDFPluginEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::pdfPluginEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::pdfPluginEnabledKey(), value, false);
}

bool WebPreferences::pdfPluginEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::pdfPluginEnabledKey());
}

void WebPreferences::deletePDFPluginEnabled()
{
    deleteKey(WebPreferencesKey::pdfPluginEnabledKey());
}

void WebPreferences::setPassiveTouchListenersAsDefaultOnDocument(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::passiveTouchListenersAsDefaultOnDocumentKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::passiveTouchListenersAsDefaultOnDocumentKey(), value, false);
}

bool WebPreferences::passiveTouchListenersAsDefaultOnDocument() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::passiveTouchListenersAsDefaultOnDocumentKey());
}

void WebPreferences::deletePassiveTouchListenersAsDefaultOnDocument()
{
    deleteKey(WebPreferencesKey::passiveTouchListenersAsDefaultOnDocumentKey());
}

void WebPreferences::setPasswordEchoDuration(const double& value)
{
    if (!m_store.setDoubleValueForKey(WebPreferencesKey::passwordEchoDurationKey(), value))
        return;
    updateDoubleValueForKey(WebPreferencesKey::passwordEchoDurationKey(), value, false);
}

double WebPreferences::passwordEchoDuration() const
{
    return m_store.getDoubleValueForKey(WebPreferencesKey::passwordEchoDurationKey());
}

void WebPreferences::deletePasswordEchoDuration()
{
    deleteKey(WebPreferencesKey::passwordEchoDurationKey());
}

void WebPreferences::setPasswordEchoEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::passwordEchoEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::passwordEchoEnabledKey(), value, false);
}

bool WebPreferences::passwordEchoEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::passwordEchoEnabledKey());
}

void WebPreferences::deletePasswordEchoEnabled()
{
    deleteKey(WebPreferencesKey::passwordEchoEnabledKey());
}

void WebPreferences::setPictographFontFamily(const String& value)
{
    if (!m_store.setStringValueForKey(WebPreferencesKey::pictographFontFamilyKey(), value))
        return;
    updateStringValueForKey(WebPreferencesKey::pictographFontFamilyKey(), value, false);
}

String WebPreferences::pictographFontFamily() const
{
    return m_store.getStringValueForKey(WebPreferencesKey::pictographFontFamilyKey());
}

void WebPreferences::deletePictographFontFamily()
{
    deleteKey(WebPreferencesKey::pictographFontFamilyKey());
}

void WebPreferences::setPictureInPictureAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::pictureInPictureAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::pictureInPictureAPIEnabledKey(), value, false);
}

bool WebPreferences::pictureInPictureAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::pictureInPictureAPIEnabledKey());
}

void WebPreferences::deletePictureInPictureAPIEnabled()
{
    deleteKey(WebPreferencesKey::pictureInPictureAPIEnabledKey());
}

void WebPreferences::setPitchCorrectionAlgorithm(const uint32_t& value)
{
    if (!m_store.setUInt32ValueForKey(WebPreferencesKey::pitchCorrectionAlgorithmKey(), value))
        return;
    updateUInt32ValueForKey(WebPreferencesKey::pitchCorrectionAlgorithmKey(), value, false);
}

uint32_t WebPreferences::pitchCorrectionAlgorithm() const
{
    return m_store.getUInt32ValueForKey(WebPreferencesKey::pitchCorrectionAlgorithmKey());
}

void WebPreferences::deletePitchCorrectionAlgorithm()
{
    deleteKey(WebPreferencesKey::pitchCorrectionAlgorithmKey());
}

void WebPreferences::setPluginsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::pluginsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::pluginsEnabledKey(), value, false);
}

bool WebPreferences::pluginsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::pluginsEnabledKey());
}

void WebPreferences::deletePluginsEnabled()
{
    deleteKey(WebPreferencesKey::pluginsEnabledKey());
}

void WebPreferences::setPunchOutWhiteBackgroundsInDarkMode(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::punchOutWhiteBackgroundsInDarkModeKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::punchOutWhiteBackgroundsInDarkModeKey(), value, false);
}

bool WebPreferences::punchOutWhiteBackgroundsInDarkMode() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::punchOutWhiteBackgroundsInDarkModeKey());
}

void WebPreferences::deletePunchOutWhiteBackgroundsInDarkMode()
{
    deleteKey(WebPreferencesKey::punchOutWhiteBackgroundsInDarkModeKey());
}

void WebPreferences::setRequiresPageVisibilityToPlayAudio(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::requiresPageVisibilityToPlayAudioKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::requiresPageVisibilityToPlayAudioKey(), value, false);
}

bool WebPreferences::requiresPageVisibilityToPlayAudio() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::requiresPageVisibilityToPlayAudioKey());
}

void WebPreferences::deleteRequiresPageVisibilityToPlayAudio()
{
    deleteKey(WebPreferencesKey::requiresPageVisibilityToPlayAudioKey());
}

void WebPreferences::setRequiresUserGestureForAudioPlayback(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::requiresUserGestureForAudioPlaybackKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::requiresUserGestureForAudioPlaybackKey(), value, false);
}

bool WebPreferences::requiresUserGestureForAudioPlayback() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::requiresUserGestureForAudioPlaybackKey());
}

void WebPreferences::deleteRequiresUserGestureForAudioPlayback()
{
    deleteKey(WebPreferencesKey::requiresUserGestureForAudioPlaybackKey());
}

void WebPreferences::setRequiresUserGestureForMediaPlayback(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::requiresUserGestureForMediaPlaybackKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::requiresUserGestureForMediaPlaybackKey(), value, false);
}

bool WebPreferences::requiresUserGestureForMediaPlayback() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::requiresUserGestureForMediaPlaybackKey());
}

void WebPreferences::deleteRequiresUserGestureForMediaPlayback()
{
    deleteKey(WebPreferencesKey::requiresUserGestureForMediaPlaybackKey());
}

void WebPreferences::setRequiresUserGestureForVideoPlayback(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::requiresUserGestureForVideoPlaybackKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::requiresUserGestureForVideoPlaybackKey(), value, false);
}

bool WebPreferences::requiresUserGestureForVideoPlayback() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::requiresUserGestureForVideoPlaybackKey());
}

void WebPreferences::deleteRequiresUserGestureForVideoPlayback()
{
    deleteKey(WebPreferencesKey::requiresUserGestureForVideoPlaybackKey());
}

void WebPreferences::setRequiresUserGestureToLoadVideo(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::requiresUserGestureToLoadVideoKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::requiresUserGestureToLoadVideoKey(), value, false);
}

bool WebPreferences::requiresUserGestureToLoadVideo() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::requiresUserGestureToLoadVideoKey());
}

void WebPreferences::deleteRequiresUserGestureToLoadVideo()
{
    deleteKey(WebPreferencesKey::requiresUserGestureToLoadVideoKey());
}

void WebPreferences::setRubberBandingForSubScrollableRegionsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::rubberBandingForSubScrollableRegionsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::rubberBandingForSubScrollableRegionsEnabledKey(), value, false);
}

bool WebPreferences::rubberBandingForSubScrollableRegionsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::rubberBandingForSubScrollableRegionsEnabledKey());
}

void WebPreferences::deleteRubberBandingForSubScrollableRegionsEnabled()
{
    deleteKey(WebPreferencesKey::rubberBandingForSubScrollableRegionsEnabledKey());
}

void WebPreferences::setSampledPageTopColorMaxDifference(const double& value)
{
    if (!m_store.setDoubleValueForKey(WebPreferencesKey::sampledPageTopColorMaxDifferenceKey(), value))
        return;
    updateDoubleValueForKey(WebPreferencesKey::sampledPageTopColorMaxDifferenceKey(), value, false);
}

double WebPreferences::sampledPageTopColorMaxDifference() const
{
    return m_store.getDoubleValueForKey(WebPreferencesKey::sampledPageTopColorMaxDifferenceKey());
}

void WebPreferences::deleteSampledPageTopColorMaxDifference()
{
    deleteKey(WebPreferencesKey::sampledPageTopColorMaxDifferenceKey());
}

void WebPreferences::setSampledPageTopColorMinHeight(const double& value)
{
    if (!m_store.setDoubleValueForKey(WebPreferencesKey::sampledPageTopColorMinHeightKey(), value))
        return;
    updateDoubleValueForKey(WebPreferencesKey::sampledPageTopColorMinHeightKey(), value, false);
}

double WebPreferences::sampledPageTopColorMinHeight() const
{
    return m_store.getDoubleValueForKey(WebPreferencesKey::sampledPageTopColorMinHeightKey());
}

void WebPreferences::deleteSampledPageTopColorMinHeight()
{
    deleteKey(WebPreferencesKey::sampledPageTopColorMinHeightKey());
}

void WebPreferences::setSansSerifFontFamily(const String& value)
{
    if (!m_store.setStringValueForKey(WebPreferencesKey::sansSerifFontFamilyKey(), value))
        return;
    updateStringValueForKey(WebPreferencesKey::sansSerifFontFamilyKey(), value, false);
}

String WebPreferences::sansSerifFontFamily() const
{
    return m_store.getStringValueForKey(WebPreferencesKey::sansSerifFontFamilyKey());
}

void WebPreferences::deleteSansSerifFontFamily()
{
    deleteKey(WebPreferencesKey::sansSerifFontFamilyKey());
}

void WebPreferences::setSelectTrailingWhitespaceEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::selectTrailingWhitespaceEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::selectTrailingWhitespaceEnabledKey(), value, false);
}

bool WebPreferences::selectTrailingWhitespaceEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::selectTrailingWhitespaceEnabledKey());
}

void WebPreferences::deleteSelectTrailingWhitespaceEnabled()
{
    deleteKey(WebPreferencesKey::selectTrailingWhitespaceEnabledKey());
}

void WebPreferences::setSerifFontFamily(const String& value)
{
    if (!m_store.setStringValueForKey(WebPreferencesKey::serifFontFamilyKey(), value))
        return;
    updateStringValueForKey(WebPreferencesKey::serifFontFamilyKey(), value, false);
}

String WebPreferences::serifFontFamily() const
{
    return m_store.getStringValueForKey(WebPreferencesKey::serifFontFamilyKey());
}

void WebPreferences::deleteSerifFontFamily()
{
    deleteKey(WebPreferencesKey::serifFontFamilyKey());
}

void WebPreferences::setServiceControlsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::serviceControlsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::serviceControlsEnabledKey(), value, false);
}

bool WebPreferences::serviceControlsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::serviceControlsEnabledKey());
}

void WebPreferences::deleteServiceControlsEnabled()
{
    deleteKey(WebPreferencesKey::serviceControlsEnabledKey());
}

void WebPreferences::setServiceWorkerEntitlementDisabledForTesting(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::serviceWorkerEntitlementDisabledForTestingKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::serviceWorkerEntitlementDisabledForTestingKey(), value, false);
}

bool WebPreferences::serviceWorkerEntitlementDisabledForTesting() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::serviceWorkerEntitlementDisabledForTestingKey());
}

void WebPreferences::deleteServiceWorkerEntitlementDisabledForTesting()
{
    deleteKey(WebPreferencesKey::serviceWorkerEntitlementDisabledForTestingKey());
}

void WebPreferences::setShouldAllowUserInstalledFonts(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::shouldAllowUserInstalledFontsKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::shouldAllowUserInstalledFontsKey(), value, false);
}

bool WebPreferences::shouldAllowUserInstalledFonts() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::shouldAllowUserInstalledFontsKey());
}

void WebPreferences::deleteShouldAllowUserInstalledFonts()
{
    deleteKey(WebPreferencesKey::shouldAllowUserInstalledFontsKey());
}

void WebPreferences::setShouldConvertInvalidURLsToBlank(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::shouldConvertInvalidURLsToBlankKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::shouldConvertInvalidURLsToBlankKey(), value, false);
}

bool WebPreferences::shouldConvertInvalidURLsToBlank() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::shouldConvertInvalidURLsToBlankKey());
}

void WebPreferences::deleteShouldConvertInvalidURLsToBlank()
{
    deleteKey(WebPreferencesKey::shouldConvertInvalidURLsToBlankKey());
}

void WebPreferences::setShouldConvertPositionStyleOnCopy(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::shouldConvertPositionStyleOnCopyKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::shouldConvertPositionStyleOnCopyKey(), value, false);
}

bool WebPreferences::shouldConvertPositionStyleOnCopy() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::shouldConvertPositionStyleOnCopyKey());
}

void WebPreferences::deleteShouldConvertPositionStyleOnCopy()
{
    deleteKey(WebPreferencesKey::shouldConvertPositionStyleOnCopyKey());
}

void WebPreferences::setShouldDecidePolicyBeforeLoadingQuickLookPreview(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::shouldDecidePolicyBeforeLoadingQuickLookPreviewKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::shouldDecidePolicyBeforeLoadingQuickLookPreviewKey(), value, false);
}

bool WebPreferences::shouldDecidePolicyBeforeLoadingQuickLookPreview() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::shouldDecidePolicyBeforeLoadingQuickLookPreviewKey());
}

void WebPreferences::deleteShouldDecidePolicyBeforeLoadingQuickLookPreview()
{
    deleteKey(WebPreferencesKey::shouldDecidePolicyBeforeLoadingQuickLookPreviewKey());
}

void WebPreferences::setShouldDisplayCaptions(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::shouldDisplayCaptionsKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::shouldDisplayCaptionsKey(), value, false);
}

bool WebPreferences::shouldDisplayCaptions() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::shouldDisplayCaptionsKey());
}

void WebPreferences::deleteShouldDisplayCaptions()
{
    deleteKey(WebPreferencesKey::shouldDisplayCaptionsKey());
}

void WebPreferences::setShouldDisplaySubtitles(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::shouldDisplaySubtitlesKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::shouldDisplaySubtitlesKey(), value, false);
}

bool WebPreferences::shouldDisplaySubtitles() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::shouldDisplaySubtitlesKey());
}

void WebPreferences::deleteShouldDisplaySubtitles()
{
    deleteKey(WebPreferencesKey::shouldDisplaySubtitlesKey());
}

void WebPreferences::setShouldDisplayTextDescriptions(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::shouldDisplayTextDescriptionsKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::shouldDisplayTextDescriptionsKey(), value, false);
}

bool WebPreferences::shouldDisplayTextDescriptions() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::shouldDisplayTextDescriptionsKey());
}

void WebPreferences::deleteShouldDisplayTextDescriptions()
{
    deleteKey(WebPreferencesKey::shouldDisplayTextDescriptionsKey());
}

void WebPreferences::setShouldEnableTextAutosizingBoost(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::shouldEnableTextAutosizingBoostKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::shouldEnableTextAutosizingBoostKey(), value, false);
}

bool WebPreferences::shouldEnableTextAutosizingBoost() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::shouldEnableTextAutosizingBoostKey());
}

void WebPreferences::deleteShouldEnableTextAutosizingBoost()
{
    deleteKey(WebPreferencesKey::shouldEnableTextAutosizingBoostKey());
}

void WebPreferences::setShouldIgnoreMetaViewport(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::shouldIgnoreMetaViewportKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::shouldIgnoreMetaViewportKey(), value, false);
}

bool WebPreferences::shouldIgnoreMetaViewport() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::shouldIgnoreMetaViewportKey());
}

void WebPreferences::deleteShouldIgnoreMetaViewport()
{
    deleteKey(WebPreferencesKey::shouldIgnoreMetaViewportKey());
}

void WebPreferences::setShouldPrintBackgrounds(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::shouldPrintBackgroundsKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::shouldPrintBackgroundsKey(), value, false);
}

bool WebPreferences::shouldPrintBackgrounds() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::shouldPrintBackgroundsKey());
}

void WebPreferences::deleteShouldPrintBackgrounds()
{
    deleteKey(WebPreferencesKey::shouldPrintBackgroundsKey());
}

void WebPreferences::setShouldRespectImageOrientation(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::shouldRespectImageOrientationKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::shouldRespectImageOrientationKey(), value, false);
}

bool WebPreferences::shouldRespectImageOrientation() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::shouldRespectImageOrientationKey());
}

void WebPreferences::deleteShouldRespectImageOrientation()
{
    deleteKey(WebPreferencesKey::shouldRespectImageOrientationKey());
}

void WebPreferences::setShouldRestrictBaseURLSchemes(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::shouldRestrictBaseURLSchemesKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::shouldRestrictBaseURLSchemesKey(), value, false);
}

bool WebPreferences::shouldRestrictBaseURLSchemes() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::shouldRestrictBaseURLSchemesKey());
}

void WebPreferences::deleteShouldRestrictBaseURLSchemes()
{
    deleteKey(WebPreferencesKey::shouldRestrictBaseURLSchemesKey());
}

void WebPreferences::setShouldSuppressTextInputFromEditingDuringProvisionalNavigation(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::shouldSuppressTextInputFromEditingDuringProvisionalNavigationKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::shouldSuppressTextInputFromEditingDuringProvisionalNavigationKey(), value, false);
}

bool WebPreferences::shouldSuppressTextInputFromEditingDuringProvisionalNavigation() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::shouldSuppressTextInputFromEditingDuringProvisionalNavigationKey());
}

void WebPreferences::deleteShouldSuppressTextInputFromEditingDuringProvisionalNavigation()
{
    deleteKey(WebPreferencesKey::shouldSuppressTextInputFromEditingDuringProvisionalNavigationKey());
}

void WebPreferences::setShouldUseServiceWorkerShortTimeout(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::shouldUseServiceWorkerShortTimeoutKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::shouldUseServiceWorkerShortTimeoutKey(), value, false);
}

bool WebPreferences::shouldUseServiceWorkerShortTimeout() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::shouldUseServiceWorkerShortTimeoutKey());
}

void WebPreferences::deleteShouldUseServiceWorkerShortTimeout()
{
    deleteKey(WebPreferencesKey::shouldUseServiceWorkerShortTimeoutKey());
}

void WebPreferences::setShowsToolTipOverTruncatedText(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::showsToolTipOverTruncatedTextKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::showsToolTipOverTruncatedTextKey(), value, false);
}

bool WebPreferences::showsToolTipOverTruncatedText() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::showsToolTipOverTruncatedTextKey());
}

void WebPreferences::deleteShowsToolTipOverTruncatedText()
{
    deleteKey(WebPreferencesKey::showsToolTipOverTruncatedTextKey());
}

void WebPreferences::setShowsURLsInToolTipsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::showsURLsInToolTipsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::showsURLsInToolTipsEnabledKey(), value, false);
}

bool WebPreferences::showsURLsInToolTipsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::showsURLsInToolTipsEnabledKey());
}

void WebPreferences::deleteShowsURLsInToolTipsEnabled()
{
    deleteKey(WebPreferencesKey::showsURLsInToolTipsEnabledKey());
}

void WebPreferences::setShrinksStandaloneImagesToFit(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::shrinksStandaloneImagesToFitKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::shrinksStandaloneImagesToFitKey(), value, false);
}

bool WebPreferences::shrinksStandaloneImagesToFit() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::shrinksStandaloneImagesToFitKey());
}

void WebPreferences::deleteShrinksStandaloneImagesToFit()
{
    deleteKey(WebPreferencesKey::shrinksStandaloneImagesToFitKey());
}

void WebPreferences::setSmartInsertDeleteEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::smartInsertDeleteEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::smartInsertDeleteEnabledKey(), value, false);
}

bool WebPreferences::smartInsertDeleteEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::smartInsertDeleteEnabledKey());
}

void WebPreferences::deleteSmartInsertDeleteEnabled()
{
    deleteKey(WebPreferencesKey::smartInsertDeleteEnabledKey());
}

void WebPreferences::setSourceBufferChangeTypeEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::sourceBufferChangeTypeEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::sourceBufferChangeTypeEnabledKey(), value, false);
}

bool WebPreferences::sourceBufferChangeTypeEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::sourceBufferChangeTypeEnabledKey());
}

void WebPreferences::deleteSourceBufferChangeTypeEnabled()
{
    deleteKey(WebPreferencesKey::sourceBufferChangeTypeEnabledKey());
}

void WebPreferences::setSpatialNavigationEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::spatialNavigationEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::spatialNavigationEnabledKey(), value, false);
}

bool WebPreferences::spatialNavigationEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::spatialNavigationEnabledKey());
}

void WebPreferences::deleteSpatialNavigationEnabled()
{
    deleteKey(WebPreferencesKey::spatialNavigationEnabledKey());
}

void WebPreferences::setStandalone(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::standaloneKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::standaloneKey(), value, false);
}

bool WebPreferences::standalone() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::standaloneKey());
}

void WebPreferences::deleteStandalone()
{
    deleteKey(WebPreferencesKey::standaloneKey());
}

void WebPreferences::setStandardFontFamily(const String& value)
{
    if (!m_store.setStringValueForKey(WebPreferencesKey::standardFontFamilyKey(), value))
        return;
    updateStringValueForKey(WebPreferencesKey::standardFontFamilyKey(), value, false);
}

String WebPreferences::standardFontFamily() const
{
    return m_store.getStringValueForKey(WebPreferencesKey::standardFontFamilyKey());
}

void WebPreferences::deleteStandardFontFamily()
{
    deleteKey(WebPreferencesKey::standardFontFamilyKey());
}

void WebPreferences::setSuppressesIncrementalRendering(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::suppressesIncrementalRenderingKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::suppressesIncrementalRenderingKey(), value, false);
}

bool WebPreferences::suppressesIncrementalRendering() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::suppressesIncrementalRenderingKey());
}

void WebPreferences::deleteSuppressesIncrementalRendering()
{
    deleteKey(WebPreferencesKey::suppressesIncrementalRenderingKey());
}

void WebPreferences::setSystemLayoutDirection(const uint32_t& value)
{
    if (!m_store.setUInt32ValueForKey(WebPreferencesKey::systemLayoutDirectionKey(), value))
        return;
    updateUInt32ValueForKey(WebPreferencesKey::systemLayoutDirectionKey(), value, false);
}

uint32_t WebPreferences::systemLayoutDirection() const
{
    return m_store.getUInt32ValueForKey(WebPreferencesKey::systemLayoutDirectionKey());
}

void WebPreferences::deleteSystemLayoutDirection()
{
    deleteKey(WebPreferencesKey::systemLayoutDirectionKey());
}

void WebPreferences::setSystemPreviewEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::systemPreviewEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::systemPreviewEnabledKey(), value, false);
}

bool WebPreferences::systemPreviewEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::systemPreviewEnabledKey());
}

void WebPreferences::deleteSystemPreviewEnabled()
{
    deleteKey(WebPreferencesKey::systemPreviewEnabledKey());
}

void WebPreferences::setTabsToLinks(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::tabsToLinksKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::tabsToLinksKey(), value, false);
}

bool WebPreferences::tabsToLinks() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::tabsToLinksKey());
}

void WebPreferences::deleteTabsToLinks()
{
    deleteKey(WebPreferencesKey::tabsToLinksKey());
}

void WebPreferences::setTelephoneNumberParsingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::telephoneNumberParsingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::telephoneNumberParsingEnabledKey(), value, false);
}

bool WebPreferences::telephoneNumberParsingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::telephoneNumberParsingEnabledKey());
}

void WebPreferences::deleteTelephoneNumberParsingEnabled()
{
    deleteKey(WebPreferencesKey::telephoneNumberParsingEnabledKey());
}

void WebPreferences::setTemporaryTileCohortRetentionEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::temporaryTileCohortRetentionEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::temporaryTileCohortRetentionEnabledKey(), value, false);
}

bool WebPreferences::temporaryTileCohortRetentionEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::temporaryTileCohortRetentionEnabledKey());
}

void WebPreferences::deleteTemporaryTileCohortRetentionEnabled()
{
    deleteKey(WebPreferencesKey::temporaryTileCohortRetentionEnabledKey());
}

void WebPreferences::setTextAreasAreResizable(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::textAreasAreResizableKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::textAreasAreResizableKey(), value, false);
}

bool WebPreferences::textAreasAreResizable() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::textAreasAreResizableKey());
}

void WebPreferences::deleteTextAreasAreResizable()
{
    deleteKey(WebPreferencesKey::textAreasAreResizableKey());
}

void WebPreferences::setTextAutosizingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::textAutosizingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::textAutosizingEnabledKey(), value, false);
}

bool WebPreferences::textAutosizingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::textAutosizingEnabledKey());
}

void WebPreferences::deleteTextAutosizingEnabled()
{
    deleteKey(WebPreferencesKey::textAutosizingEnabledKey());
}

void WebPreferences::setTextInteractionEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::textInteractionEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::textInteractionEnabledKey(), value, false);
}

bool WebPreferences::textInteractionEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::textInteractionEnabledKey());
}

void WebPreferences::deleteTextInteractionEnabled()
{
    deleteKey(WebPreferencesKey::textInteractionEnabledKey());
}

void WebPreferences::setThreadedScrollingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::threadedScrollingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::threadedScrollingEnabledKey(), value, false);
}

bool WebPreferences::threadedScrollingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::threadedScrollingEnabledKey());
}

void WebPreferences::deleteThreadedScrollingEnabled()
{
    deleteKey(WebPreferencesKey::threadedScrollingEnabledKey());
}

void WebPreferences::setTreatsAnyTextCSSLinkAsStylesheet(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::treatsAnyTextCSSLinkAsStylesheetKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::treatsAnyTextCSSLinkAsStylesheetKey(), value, false);
}

bool WebPreferences::treatsAnyTextCSSLinkAsStylesheet() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::treatsAnyTextCSSLinkAsStylesheetKey());
}

void WebPreferences::deleteTreatsAnyTextCSSLinkAsStylesheet()
{
    deleteKey(WebPreferencesKey::treatsAnyTextCSSLinkAsStylesheetKey());
}

void WebPreferences::setUseImageDocumentForSubframePDF(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::useImageDocumentForSubframePDFKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::useImageDocumentForSubframePDFKey(), value, false);
}

bool WebPreferences::useImageDocumentForSubframePDF() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::useImageDocumentForSubframePDFKey());
}

void WebPreferences::deleteUseImageDocumentForSubframePDF()
{
    deleteKey(WebPreferencesKey::useImageDocumentForSubframePDFKey());
}

void WebPreferences::setUseLegacyBackgroundSizeShorthandBehavior(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::useLegacyBackgroundSizeShorthandBehaviorKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::useLegacyBackgroundSizeShorthandBehaviorKey(), value, false);
}

bool WebPreferences::useLegacyBackgroundSizeShorthandBehavior() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::useLegacyBackgroundSizeShorthandBehaviorKey());
}

void WebPreferences::deleteUseLegacyBackgroundSizeShorthandBehavior()
{
    deleteKey(WebPreferencesKey::useLegacyBackgroundSizeShorthandBehaviorKey());
}

void WebPreferences::setUsePreHTML5ParserQuirks(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::usePreHTML5ParserQuirksKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::usePreHTML5ParserQuirksKey(), value, false);
}

bool WebPreferences::usePreHTML5ParserQuirks() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::usePreHTML5ParserQuirksKey());
}

void WebPreferences::deleteUsePreHTML5ParserQuirks()
{
    deleteKey(WebPreferencesKey::usePreHTML5ParserQuirksKey());
}

void WebPreferences::setUserInterfaceDirectionPolicy(const uint32_t& value)
{
    if (!m_store.setUInt32ValueForKey(WebPreferencesKey::userInterfaceDirectionPolicyKey(), value))
        return;
    updateUInt32ValueForKey(WebPreferencesKey::userInterfaceDirectionPolicyKey(), value, false);
}

uint32_t WebPreferences::userInterfaceDirectionPolicy() const
{
    return m_store.getUInt32ValueForKey(WebPreferencesKey::userInterfaceDirectionPolicyKey());
}

void WebPreferences::deleteUserInterfaceDirectionPolicy()
{
    deleteKey(WebPreferencesKey::userInterfaceDirectionPolicyKey());
}

void WebPreferences::setUsesBackForwardCache(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::usesBackForwardCacheKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::usesBackForwardCacheKey(), value, false);
}

bool WebPreferences::usesBackForwardCache() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::usesBackForwardCacheKey());
}

void WebPreferences::deleteUsesBackForwardCache()
{
    deleteKey(WebPreferencesKey::usesBackForwardCacheKey());
}

void WebPreferences::setUsesEncodingDetector(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::usesEncodingDetectorKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::usesEncodingDetectorKey(), value, false);
}

bool WebPreferences::usesEncodingDetector() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::usesEncodingDetectorKey());
}

void WebPreferences::deleteUsesEncodingDetector()
{
    deleteKey(WebPreferencesKey::usesEncodingDetectorKey());
}

void WebPreferences::setVP8DecoderEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::vp8DecoderEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::vp8DecoderEnabledKey(), value, false);
}

bool WebPreferences::vp8DecoderEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::vp8DecoderEnabledKey());
}

void WebPreferences::deleteVP8DecoderEnabled()
{
    deleteKey(WebPreferencesKey::vp8DecoderEnabledKey());
}

void WebPreferences::setVP9DecoderEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::vp9DecoderEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::vp9DecoderEnabledKey(), value, false);
}

bool WebPreferences::vp9DecoderEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::vp9DecoderEnabledKey());
}

void WebPreferences::deleteVP9DecoderEnabled()
{
    deleteKey(WebPreferencesKey::vp9DecoderEnabledKey());
}

void WebPreferences::setVideoFullscreenRequiresElementFullscreen(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::videoFullscreenRequiresElementFullscreenKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::videoFullscreenRequiresElementFullscreenKey(), value, false);
}

bool WebPreferences::videoFullscreenRequiresElementFullscreen() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::videoFullscreenRequiresElementFullscreenKey());
}

void WebPreferences::deleteVideoFullscreenRequiresElementFullscreen()
{
    deleteKey(WebPreferencesKey::videoFullscreenRequiresElementFullscreenKey());
}

void WebPreferences::setVideoPresentationModeAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::videoPresentationModeAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::videoPresentationModeAPIEnabledKey(), value, false);
}

bool WebPreferences::videoPresentationModeAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::videoPresentationModeAPIEnabledKey());
}

void WebPreferences::deleteVideoPresentationModeAPIEnabled()
{
    deleteKey(WebPreferencesKey::videoPresentationModeAPIEnabledKey());
}

void WebPreferences::setVideoQualityIncludesDisplayCompositingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::videoQualityIncludesDisplayCompositingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::videoQualityIncludesDisplayCompositingEnabledKey(), value, false);
}

bool WebPreferences::videoQualityIncludesDisplayCompositingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::videoQualityIncludesDisplayCompositingEnabledKey());
}

void WebPreferences::deleteVideoQualityIncludesDisplayCompositingEnabled()
{
    deleteKey(WebPreferencesKey::videoQualityIncludesDisplayCompositingEnabledKey());
}

void WebPreferences::setVisibleDebugOverlayRegions(const uint32_t& value)
{
    if (!m_store.setUInt32ValueForKey(WebPreferencesKey::visibleDebugOverlayRegionsKey(), value))
        return;
    updateUInt32ValueForKey(WebPreferencesKey::visibleDebugOverlayRegionsKey(), value, false);
}

uint32_t WebPreferences::visibleDebugOverlayRegions() const
{
    return m_store.getUInt32ValueForKey(WebPreferencesKey::visibleDebugOverlayRegionsKey());
}

void WebPreferences::deleteVisibleDebugOverlayRegions()
{
    deleteKey(WebPreferencesKey::visibleDebugOverlayRegionsKey());
}

void WebPreferences::setVisualViewportEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::visualViewportEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::visualViewportEnabledKey(), value, false);
}

bool WebPreferences::visualViewportEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::visualViewportEnabledKey());
}

void WebPreferences::deleteVisualViewportEnabled()
{
    deleteKey(WebPreferencesKey::visualViewportEnabledKey());
}

void WebPreferences::setWantsBalancedSetDefersLoadingBehavior(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::wantsBalancedSetDefersLoadingBehaviorKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::wantsBalancedSetDefersLoadingBehaviorKey(), value, false);
}

bool WebPreferences::wantsBalancedSetDefersLoadingBehavior() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::wantsBalancedSetDefersLoadingBehaviorKey());
}

void WebPreferences::deleteWantsBalancedSetDefersLoadingBehavior()
{
    deleteKey(WebPreferencesKey::wantsBalancedSetDefersLoadingBehaviorKey());
}

void WebPreferences::setWebAudioEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webAudioEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webAudioEnabledKey(), value, false);
}

bool WebPreferences::webAudioEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webAudioEnabledKey());
}

void WebPreferences::deleteWebAudioEnabled()
{
    deleteKey(WebPreferencesKey::webAudioEnabledKey());
}

void WebPreferences::setWebMFormatReaderEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webMFormatReaderEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webMFormatReaderEnabledKey(), value, false);
}

bool WebPreferences::webMFormatReaderEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webMFormatReaderEnabledKey());
}

void WebPreferences::deleteWebMFormatReaderEnabled()
{
    deleteKey(WebPreferencesKey::webMFormatReaderEnabledKey());
}

void WebPreferences::setWebMParserEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webMParserEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webMParserEnabledKey(), value, false);
}

bool WebPreferences::webMParserEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webMParserEnabledKey());
}

void WebPreferences::deleteWebMParserEnabled()
{
    deleteKey(WebPreferencesKey::webMParserEnabledKey());
}

void WebPreferences::setWebSecurityEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webSecurityEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webSecurityEnabledKey(), value, false);
}

bool WebPreferences::webSecurityEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webSecurityEnabledKey());
}

void WebPreferences::deleteWebSecurityEnabled()
{
    deleteKey(WebPreferencesKey::webSecurityEnabledKey());
}

void WebPreferences::setWebSocketEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webSocketEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webSocketEnabledKey(), value, false);
}

bool WebPreferences::webSocketEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webSocketEnabledKey());
}

void WebPreferences::deleteWebSocketEnabled()
{
    deleteKey(WebPreferencesKey::webSocketEnabledKey());
}

void WebPreferences::setWindowFocusRestricted(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::windowFocusRestrictedKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::windowFocusRestrictedKey(), value, false);
}

bool WebPreferences::windowFocusRestricted() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::windowFocusRestrictedKey());
}

void WebPreferences::deleteWindowFocusRestricted()
{
    deleteKey(WebPreferencesKey::windowFocusRestrictedKey());
}

void WebPreferences::setWirelessPlaybackTargetAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::wirelessPlaybackTargetAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::wirelessPlaybackTargetAPIEnabledKey(), value, false);
}

bool WebPreferences::wirelessPlaybackTargetAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::wirelessPlaybackTargetAPIEnabledKey());
}

void WebPreferences::deleteWirelessPlaybackTargetAPIEnabled()
{
    deleteKey(WebPreferencesKey::wirelessPlaybackTargetAPIEnabledKey());
}

void WebPreferences::setDirPseudoEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::dirPseudoEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::dirPseudoEnabledKey(), value, false);
}

bool WebPreferences::dirPseudoEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::dirPseudoEnabledKey());
}

void WebPreferences::deleteDirPseudoEnabled()
{
    deleteKey(WebPreferencesKey::dirPseudoEnabledKey());
}

void WebPreferences::setFocusVisibleEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::focusVisibleEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::focusVisibleEnabledKey(), value, false);
}

bool WebPreferences::focusVisibleEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::focusVisibleEnabledKey());
}

void WebPreferences::deleteFocusVisibleEnabled()
{
    deleteKey(WebPreferencesKey::focusVisibleEnabledKey());
}

void WebPreferences::setHasPseudoClassEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::hasPseudoClassEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::hasPseudoClassEnabledKey(), value, false);
}

bool WebPreferences::hasPseudoClassEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::hasPseudoClassEnabledKey());
}

void WebPreferences::deleteHasPseudoClassEnabled()
{
    deleteKey(WebPreferencesKey::hasPseudoClassEnabledKey());
}

void WebPreferences::setPageAtRuleSupportEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::pageAtRuleSupportEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::pageAtRuleSupportEnabledKey(), value, true);
}

bool WebPreferences::pageAtRuleSupportEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::pageAtRuleSupportEnabledKey());
}

void WebPreferences::deletePageAtRuleSupportEnabled()
{
    deleteKey(WebPreferencesKey::pageAtRuleSupportEnabledKey());
}

void WebPreferences::setAriaReflectionForElementReferencesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::ariaReflectionForElementReferencesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::ariaReflectionForElementReferencesEnabledKey(), value, false);
}

bool WebPreferences::ariaReflectionForElementReferencesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::ariaReflectionForElementReferencesEnabledKey());
}

void WebPreferences::deleteAriaReflectionForElementReferencesEnabled()
{
    deleteKey(WebPreferencesKey::ariaReflectionForElementReferencesEnabledKey());
}

void WebPreferences::setAVFoundationEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::isAVFoundationEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::isAVFoundationEnabledKey(), value, false);
}

bool WebPreferences::isAVFoundationEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::isAVFoundationEnabledKey());
}

void WebPreferences::deleteAVFoundationEnabled()
{
    deleteKey(WebPreferencesKey::isAVFoundationEnabledKey());
}

void WebPreferences::setAbortSignalAnyOperationEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::abortSignalAnyOperationEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::abortSignalAnyOperationEnabledKey(), value, false);
}

bool WebPreferences::abortSignalAnyOperationEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::abortSignalAnyOperationEnabledKey());
}

void WebPreferences::deleteAbortSignalAnyOperationEnabled()
{
    deleteKey(WebPreferencesKey::abortSignalAnyOperationEnabledKey());
}

void WebPreferences::setAcceleratedFiltersEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::acceleratedFiltersEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::acceleratedFiltersEnabledKey(), value, true);
}

bool WebPreferences::acceleratedFiltersEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::acceleratedFiltersEnabledKey());
}

void WebPreferences::deleteAcceleratedFiltersEnabled()
{
    deleteKey(WebPreferencesKey::acceleratedFiltersEnabledKey());
}

void WebPreferences::setAccessHandleEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::accessHandleEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::accessHandleEnabledKey(), value, false);
}

bool WebPreferences::accessHandleEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::accessHandleEnabledKey());
}

void WebPreferences::deleteAccessHandleEnabled()
{
    deleteKey(WebPreferencesKey::accessHandleEnabledKey());
}

void WebPreferences::setDOMTestingAPIsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::domTestingAPIsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::domTestingAPIsEnabledKey(), value, true);
}

bool WebPreferences::domTestingAPIsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::domTestingAPIsEnabledKey());
}

void WebPreferences::deleteDOMTestingAPIsEnabled()
{
    deleteKey(WebPreferencesKey::domTestingAPIsEnabledKey());
}

void WebPreferences::setAllowMediaContentTypesRequiringHardwareSupportAsFallback(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::allowMediaContentTypesRequiringHardwareSupportAsFallbackKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::allowMediaContentTypesRequiringHardwareSupportAsFallbackKey(), value, false);
}

bool WebPreferences::allowMediaContentTypesRequiringHardwareSupportAsFallback() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::allowMediaContentTypesRequiringHardwareSupportAsFallbackKey());
}

void WebPreferences::deleteAllowMediaContentTypesRequiringHardwareSupportAsFallback()
{
    deleteKey(WebPreferencesKey::allowMediaContentTypesRequiringHardwareSupportAsFallbackKey());
}

void WebPreferences::setAllowViewportShrinkToFitContent(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::allowViewportShrinkToFitContentKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::allowViewportShrinkToFitContentKey(), value, true);
}

bool WebPreferences::allowViewportShrinkToFitContent() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::allowViewportShrinkToFitContentKey());
}

void WebPreferences::deleteAllowViewportShrinkToFitContent()
{
    deleteKey(WebPreferencesKey::allowViewportShrinkToFitContentKey());
}

void WebPreferences::setAllowWebGLInWorkers(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::allowWebGLInWorkersKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::allowWebGLInWorkersKey(), value, false);
}

bool WebPreferences::allowWebGLInWorkers() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::allowWebGLInWorkersKey());
}

void WebPreferences::deleteAllowWebGLInWorkers()
{
    deleteKey(WebPreferencesKey::allowWebGLInWorkersKey());
}

void WebPreferences::setPerElementSpeakerSelectionEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::perElementSpeakerSelectionEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::perElementSpeakerSelectionEnabledKey(), value, true);
}

bool WebPreferences::perElementSpeakerSelectionEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::perElementSpeakerSelectionEnabledKey());
}

void WebPreferences::deletePerElementSpeakerSelectionEnabled()
{
    deleteKey(WebPreferencesKey::perElementSpeakerSelectionEnabledKey());
}

void WebPreferences::setExposeSpeakersEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::exposeSpeakersEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::exposeSpeakersEnabledKey(), value, true);
}

bool WebPreferences::exposeSpeakersEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::exposeSpeakersEnabledKey());
}

void WebPreferences::deleteExposeSpeakersEnabled()
{
    deleteKey(WebPreferencesKey::exposeSpeakersEnabledKey());
}

void WebPreferences::setAllowTopNavigationToDataURLs(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::allowTopNavigationToDataURLsKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::allowTopNavigationToDataURLsKey(), value, false);
}

bool WebPreferences::allowTopNavigationToDataURLs() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::allowTopNavigationToDataURLsKey());
}

void WebPreferences::deleteAllowTopNavigationToDataURLs()
{
    deleteKey(WebPreferencesKey::allowTopNavigationToDataURLsKey());
}

void WebPreferences::setAllowUniversalAccessFromFileURLs(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::allowUniversalAccessFromFileURLsKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::allowUniversalAccessFromFileURLsKey(), value, false);
}

bool WebPreferences::allowUniversalAccessFromFileURLs() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::allowUniversalAccessFromFileURLsKey());
}

void WebPreferences::deleteAllowUniversalAccessFromFileURLs()
{
    deleteKey(WebPreferencesKey::allowUniversalAccessFromFileURLsKey());
}

void WebPreferences::setAlternateWebMPlayerEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::alternateWebMPlayerEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::alternateWebMPlayerEnabledKey(), value, true);
}

bool WebPreferences::alternateWebMPlayerEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::alternateWebMPlayerEnabledKey());
}

void WebPreferences::deleteAlternateWebMPlayerEnabled()
{
    deleteKey(WebPreferencesKey::alternateWebMPlayerEnabledKey());
}

void WebPreferences::setAppBadgeEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::appBadgeEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::appBadgeEnabledKey(), value, true);
}

bool WebPreferences::appBadgeEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::appBadgeEnabledKey());
}

void WebPreferences::deleteAppBadgeEnabled()
{
    deleteKey(WebPreferencesKey::appBadgeEnabledKey());
}

void WebPreferences::setAppHighlightsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::appHighlightsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::appHighlightsEnabledKey(), value, true);
}

bool WebPreferences::appHighlightsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::appHighlightsEnabledKey());
}

void WebPreferences::deleteAppHighlightsEnabled()
{
    deleteKey(WebPreferencesKey::appHighlightsEnabledKey());
}

void WebPreferences::setAspectRatioOfImgFromWidthAndHeightEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::aspectRatioOfImgFromWidthAndHeightEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::aspectRatioOfImgFromWidthAndHeightEnabledKey(), value, false);
}

bool WebPreferences::aspectRatioOfImgFromWidthAndHeightEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::aspectRatioOfImgFromWidthAndHeightEnabledKey());
}

void WebPreferences::deleteAspectRatioOfImgFromWidthAndHeightEnabled()
{
    deleteKey(WebPreferencesKey::aspectRatioOfImgFromWidthAndHeightEnabledKey());
}

void WebPreferences::setAsyncFrameScrollingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::asyncFrameScrollingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::asyncFrameScrollingEnabledKey(), value, true);
}

bool WebPreferences::asyncFrameScrollingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::asyncFrameScrollingEnabledKey());
}

void WebPreferences::deleteAsyncFrameScrollingEnabled()
{
    deleteKey(WebPreferencesKey::asyncFrameScrollingEnabledKey());
}

void WebPreferences::setAsyncOverflowScrollingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::asyncOverflowScrollingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::asyncOverflowScrollingEnabledKey(), value, true);
}

bool WebPreferences::asyncOverflowScrollingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::asyncOverflowScrollingEnabledKey());
}

void WebPreferences::deleteAsyncOverflowScrollingEnabled()
{
    deleteKey(WebPreferencesKey::asyncOverflowScrollingEnabledKey());
}

void WebPreferences::setAsyncClipboardAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::asyncClipboardAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::asyncClipboardAPIEnabledKey(), value, false);
}

bool WebPreferences::asyncClipboardAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::asyncClipboardAPIEnabledKey());
}

void WebPreferences::deleteAsyncClipboardAPIEnabled()
{
    deleteKey(WebPreferencesKey::asyncClipboardAPIEnabledKey());
}

void WebPreferences::setAttachmentElementEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::attachmentElementEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::attachmentElementEnabledKey(), value, false);
}

bool WebPreferences::attachmentElementEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::attachmentElementEnabledKey());
}

void WebPreferences::deleteAttachmentElementEnabled()
{
    deleteKey(WebPreferencesKey::attachmentElementEnabledKey());
}

void WebPreferences::setAttachmentWideLayoutEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::attachmentWideLayoutEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::attachmentWideLayoutEnabledKey(), value, false);
}

bool WebPreferences::attachmentWideLayoutEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::attachmentWideLayoutEnabledKey());
}

void WebPreferences::deleteAttachmentWideLayoutEnabled()
{
    deleteKey(WebPreferencesKey::attachmentWideLayoutEnabledKey());
}

void WebPreferences::setExtendedAudioDescriptionsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::extendedAudioDescriptionsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::extendedAudioDescriptionsEnabledKey(), value, false);
}

bool WebPreferences::extendedAudioDescriptionsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::extendedAudioDescriptionsEnabledKey());
}

void WebPreferences::deleteExtendedAudioDescriptionsEnabled()
{
    deleteKey(WebPreferencesKey::extendedAudioDescriptionsEnabledKey());
}

void WebPreferences::setAudioDescriptionsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::audioDescriptionsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::audioDescriptionsEnabledKey(), value, false);
}

bool WebPreferences::audioDescriptionsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::audioDescriptionsEnabledKey());
}

void WebPreferences::deleteAudioDescriptionsEnabled()
{
    deleteKey(WebPreferencesKey::audioDescriptionsEnabledKey());
}

void WebPreferences::setDOMAudioSessionEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::domAudioSessionEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::domAudioSessionEnabledKey(), value, false);
}

bool WebPreferences::domAudioSessionEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::domAudioSessionEnabledKey());
}

void WebPreferences::deleteDOMAudioSessionEnabled()
{
    deleteKey(WebPreferencesKey::domAudioSessionEnabledKey());
}

void WebPreferences::setDOMAudioSessionFullEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::domAudioSessionFullEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::domAudioSessionFullEnabledKey(), value, true);
}

bool WebPreferences::domAudioSessionFullEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::domAudioSessionFullEnabledKey());
}

void WebPreferences::deleteDOMAudioSessionFullEnabled()
{
    deleteKey(WebPreferencesKey::domAudioSessionFullEnabledKey());
}

void WebPreferences::setBeaconAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::beaconAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::beaconAPIEnabledKey(), value, false);
}

bool WebPreferences::beaconAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::beaconAPIEnabledKey());
}

void WebPreferences::deleteBeaconAPIEnabled()
{
    deleteKey(WebPreferencesKey::beaconAPIEnabledKey());
}

void WebPreferences::setThirdPartyIframeRedirectBlockingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::thirdPartyIframeRedirectBlockingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::thirdPartyIframeRedirectBlockingEnabledKey(), value, false);
}

bool WebPreferences::thirdPartyIframeRedirectBlockingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::thirdPartyIframeRedirectBlockingEnabledKey());
}

void WebPreferences::deleteThirdPartyIframeRedirectBlockingEnabled()
{
    deleteKey(WebPreferencesKey::thirdPartyIframeRedirectBlockingEnabledKey());
}

void WebPreferences::setBroadcastChannelEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::broadcastChannelEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::broadcastChannelEnabledKey(), value, false);
}

bool WebPreferences::broadcastChannelEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::broadcastChannelEnabledKey());
}

void WebPreferences::deleteBroadcastChannelEnabled()
{
    deleteKey(WebPreferencesKey::broadcastChannelEnabledKey());
}

void WebPreferences::setBroadcastChannelOriginPartitioningEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::broadcastChannelOriginPartitioningEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::broadcastChannelOriginPartitioningEnabledKey(), value, false);
}

bool WebPreferences::broadcastChannelOriginPartitioningEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::broadcastChannelOriginPartitioningEnabledKey());
}

void WebPreferences::deleteBroadcastChannelOriginPartitioningEnabled()
{
    deleteKey(WebPreferencesKey::broadcastChannelOriginPartitioningEnabledKey());
}

void WebPreferences::setBuiltInNotificationsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::builtInNotificationsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::builtInNotificationsEnabledKey(), value, true);
}

bool WebPreferences::builtInNotificationsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::builtInNotificationsEnabledKey());
}

void WebPreferences::deleteBuiltInNotificationsEnabled()
{
    deleteKey(WebPreferencesKey::builtInNotificationsEnabledKey());
}

void WebPreferences::setUseCGDisplayListsForDOMRendering(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::useCGDisplayListsForDOMRenderingKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::useCGDisplayListsForDOMRenderingKey(), value, true);
}

bool WebPreferences::useCGDisplayListsForDOMRendering() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::useCGDisplayListsForDOMRenderingKey());
}

void WebPreferences::deleteUseCGDisplayListsForDOMRendering()
{
    deleteKey(WebPreferencesKey::useCGDisplayListsForDOMRenderingKey());
}

void WebPreferences::setUseCGDisplayListImageCache(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::useCGDisplayListImageCacheKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::useCGDisplayListImageCacheKey(), value, true);
}

bool WebPreferences::useCGDisplayListImageCache() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::useCGDisplayListImageCacheKey());
}

void WebPreferences::deleteUseCGDisplayListImageCache()
{
    deleteKey(WebPreferencesKey::useCGDisplayListImageCacheKey());
}

void WebPreferences::setReplayCGDisplayListsIntoBackingStore(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::replayCGDisplayListsIntoBackingStoreKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::replayCGDisplayListsIntoBackingStoreKey(), value, true);
}

bool WebPreferences::replayCGDisplayListsIntoBackingStore() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::replayCGDisplayListsIntoBackingStoreKey());
}

void WebPreferences::deleteReplayCGDisplayListsIntoBackingStore()
{
    deleteKey(WebPreferencesKey::replayCGDisplayListsIntoBackingStoreKey());
}

void WebPreferences::setCSS3DTransformInteroperabilityEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::css3DTransformInteroperabilityEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::css3DTransformInteroperabilityEnabledKey(), value, false);
}

bool WebPreferences::css3DTransformInteroperabilityEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::css3DTransformInteroperabilityEnabledKey());
}

void WebPreferences::deleteCSS3DTransformInteroperabilityEnabled()
{
    deleteKey(WebPreferencesKey::css3DTransformInteroperabilityEnabledKey());
}

void WebPreferences::setCSSCounterStyleAtRuleImageSymbolsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssCounterStyleAtRuleImageSymbolsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssCounterStyleAtRuleImageSymbolsEnabledKey(), value, true);
}

bool WebPreferences::cssCounterStyleAtRuleImageSymbolsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssCounterStyleAtRuleImageSymbolsEnabledKey());
}

void WebPreferences::deleteCSSCounterStyleAtRuleImageSymbolsEnabled()
{
    deleteKey(WebPreferencesKey::cssCounterStyleAtRuleImageSymbolsEnabledKey());
}

void WebPreferences::setCSSCounterStyleAtRulesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssCounterStyleAtRulesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssCounterStyleAtRulesEnabledKey(), value, false);
}

bool WebPreferences::cssCounterStyleAtRulesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssCounterStyleAtRulesEnabledKey());
}

void WebPreferences::deleteCSSCounterStyleAtRulesEnabled()
{
    deleteKey(WebPreferencesKey::cssCounterStyleAtRulesEnabledKey());
}

void WebPreferences::setCSSFontFaceSizeAdjustEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssFontFaceSizeAdjustEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssFontFaceSizeAdjustEnabledKey(), value, false);
}

bool WebPreferences::cssFontFaceSizeAdjustEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssFontFaceSizeAdjustEnabledKey());
}

void WebPreferences::deleteCSSFontFaceSizeAdjustEnabled()
{
    deleteKey(WebPreferencesKey::cssFontFaceSizeAdjustEnabledKey());
}

void WebPreferences::setAccentColorEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::accentColorEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::accentColorEnabledKey(), value, false);
}

bool WebPreferences::accentColorEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::accentColorEnabledKey());
}

void WebPreferences::deleteAccentColorEnabled()
{
    deleteKey(WebPreferencesKey::accentColorEnabledKey());
}

void WebPreferences::setAspectRatioEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::aspectRatioEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::aspectRatioEnabledKey(), value, false);
}

bool WebPreferences::aspectRatioEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::aspectRatioEnabledKey());
}

void WebPreferences::deleteAspectRatioEnabled()
{
    deleteKey(WebPreferencesKey::aspectRatioEnabledKey());
}

void WebPreferences::setCSSCascadeLayersEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssCascadeLayersEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssCascadeLayersEnabledKey(), value, false);
}

bool WebPreferences::cssCascadeLayersEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssCascadeLayersEnabledKey());
}

void WebPreferences::deleteCSSCascadeLayersEnabled()
{
    deleteKey(WebPreferencesKey::cssCascadeLayersEnabledKey());
}

void WebPreferences::setCSSColor4(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssColor4Key(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssColor4Key(), value, false);
}

bool WebPreferences::cssColor4() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssColor4Key());
}

void WebPreferences::deleteCSSColor4()
{
    deleteKey(WebPreferencesKey::cssColor4Key());
}

void WebPreferences::setCSSContainIntrinsicSizeEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssContainIntrinsicSizeEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssContainIntrinsicSizeEnabledKey(), value, false);
}

bool WebPreferences::cssContainIntrinsicSizeEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssContainIntrinsicSizeEnabledKey());
}

void WebPreferences::deleteCSSContainIntrinsicSizeEnabled()
{
    deleteKey(WebPreferencesKey::cssContainIntrinsicSizeEnabledKey());
}

void WebPreferences::setCSSContainerQueriesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssContainerQueriesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssContainerQueriesEnabledKey(), value, false);
}

bool WebPreferences::cssContainerQueriesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssContainerQueriesEnabledKey());
}

void WebPreferences::deleteCSSContainerQueriesEnabled()
{
    deleteKey(WebPreferencesKey::cssContainerQueriesEnabledKey());
}

void WebPreferences::setCSSContainmentEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssContainmentEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssContainmentEnabledKey(), value, false);
}

bool WebPreferences::cssContainmentEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssContainmentEnabledKey());
}

void WebPreferences::deleteCSSContainmentEnabled()
{
    deleteKey(WebPreferencesKey::cssContainmentEnabledKey());
}

void WebPreferences::setCSSContentVisibilityEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssContentVisibilityEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssContentVisibilityEnabledKey(), value, true);
}

bool WebPreferences::cssContentVisibilityEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssContentVisibilityEnabledKey());
}

void WebPreferences::deleteCSSContentVisibilityEnabled()
{
    deleteKey(WebPreferencesKey::cssContentVisibilityEnabledKey());
}

void WebPreferences::setCSSCustomPropertiesAndValuesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssCustomPropertiesAndValuesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssCustomPropertiesAndValuesEnabledKey(), value, false);
}

bool WebPreferences::cssCustomPropertiesAndValuesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssCustomPropertiesAndValuesEnabledKey());
}

void WebPreferences::deleteCSSCustomPropertiesAndValuesEnabled()
{
    deleteKey(WebPreferencesKey::cssCustomPropertiesAndValuesEnabledKey());
}

void WebPreferences::setCSSGradientInterpolationColorSpacesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssGradientInterpolationColorSpacesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssGradientInterpolationColorSpacesEnabledKey(), value, false);
}

bool WebPreferences::cssGradientInterpolationColorSpacesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssGradientInterpolationColorSpacesEnabledKey());
}

void WebPreferences::deleteCSSGradientInterpolationColorSpacesEnabled()
{
    deleteKey(WebPreferencesKey::cssGradientInterpolationColorSpacesEnabledKey());
}

void WebPreferences::setCSSGradientPremultipliedAlphaInterpolationEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssGradientPremultipliedAlphaInterpolationEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssGradientPremultipliedAlphaInterpolationEnabledKey(), value, false);
}

bool WebPreferences::cssGradientPremultipliedAlphaInterpolationEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssGradientPremultipliedAlphaInterpolationEnabledKey());
}

void WebPreferences::deleteCSSGradientPremultipliedAlphaInterpolationEnabled()
{
    deleteKey(WebPreferencesKey::cssGradientPremultipliedAlphaInterpolationEnabledKey());
}

void WebPreferences::setCSSIndividualTransformPropertiesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssIndividualTransformPropertiesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssIndividualTransformPropertiesEnabledKey(), value, false);
}

bool WebPreferences::cssIndividualTransformPropertiesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssIndividualTransformPropertiesEnabledKey());
}

void WebPreferences::deleteCSSIndividualTransformPropertiesEnabled()
{
    deleteKey(WebPreferencesKey::cssIndividualTransformPropertiesEnabledKey());
}

void WebPreferences::setCSSInputSecurityEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssInputSecurityEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssInputSecurityEnabledKey(), value, true);
}

bool WebPreferences::cssInputSecurityEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssInputSecurityEnabledKey());
}

void WebPreferences::deleteCSSInputSecurityEnabled()
{
    deleteKey(WebPreferencesKey::cssInputSecurityEnabledKey());
}

void WebPreferences::setMasonryEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::masonryEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::masonryEnabledKey(), value, false);
}

bool WebPreferences::masonryEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::masonryEnabledKey());
}

void WebPreferences::deleteMasonryEnabled()
{
    deleteKey(WebPreferencesKey::masonryEnabledKey());
}

void WebPreferences::setCSSMotionPathEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssMotionPathEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssMotionPathEnabledKey(), value, false);
}

bool WebPreferences::cssMotionPathEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssMotionPathEnabledKey());
}

void WebPreferences::deleteCSSMotionPathEnabled()
{
    deleteKey(WebPreferencesKey::cssMotionPathEnabledKey());
}

void WebPreferences::setCSSNestingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssNestingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssNestingEnabledKey(), value, false);
}

bool WebPreferences::cssNestingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssNestingEnabledKey());
}

void WebPreferences::deleteCSSNestingEnabled()
{
    deleteKey(WebPreferencesKey::cssNestingEnabledKey());
}

void WebPreferences::setOverscrollBehaviorEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::overscrollBehaviorEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::overscrollBehaviorEnabledKey(), value, false);
}

bool WebPreferences::overscrollBehaviorEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::overscrollBehaviorEnabledKey());
}

void WebPreferences::deleteOverscrollBehaviorEnabled()
{
    deleteKey(WebPreferencesKey::overscrollBehaviorEnabledKey());
}

void WebPreferences::setCSSPaintingAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssPaintingAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssPaintingAPIEnabledKey(), value, true);
}

bool WebPreferences::cssPaintingAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssPaintingAPIEnabledKey());
}

void WebPreferences::deleteCSSPaintingAPIEnabled()
{
    deleteKey(WebPreferencesKey::cssPaintingAPIEnabledKey());
}

void WebPreferences::setCSSRelativeColorSyntaxEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssRelativeColorSyntaxEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssRelativeColorSyntaxEnabledKey(), value, false);
}

bool WebPreferences::cssRelativeColorSyntaxEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssRelativeColorSyntaxEnabledKey());
}

void WebPreferences::deleteCSSRelativeColorSyntaxEnabled()
{
    deleteKey(WebPreferencesKey::cssRelativeColorSyntaxEnabledKey());
}

void WebPreferences::setCSSRhythmicSizingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssRhythmicSizingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssRhythmicSizingEnabledKey(), value, true);
}

bool WebPreferences::cssRhythmicSizingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssRhythmicSizingEnabledKey());
}

void WebPreferences::deleteCSSRhythmicSizingEnabled()
{
    deleteKey(WebPreferencesKey::cssRhythmicSizingEnabledKey());
}

void WebPreferences::setCSSScrollAnchoringEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssScrollAnchoringEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssScrollAnchoringEnabledKey(), value, true);
}

bool WebPreferences::cssScrollAnchoringEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssScrollAnchoringEnabledKey());
}

void WebPreferences::deleteCSSScrollAnchoringEnabled()
{
    deleteKey(WebPreferencesKey::cssScrollAnchoringEnabledKey());
}

void WebPreferences::setSpringTimingFunctionEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::springTimingFunctionEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::springTimingFunctionEnabledKey(), value, true);
}

bool WebPreferences::springTimingFunctionEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::springTimingFunctionEnabledKey());
}

void WebPreferences::deleteSpringTimingFunctionEnabled()
{
    deleteKey(WebPreferencesKey::springTimingFunctionEnabledKey());
}

void WebPreferences::setCSSTypedOMEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssTypedOMEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssTypedOMEnabledKey(), value, false);
}

bool WebPreferences::cssTypedOMEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssTypedOMEnabledKey());
}

void WebPreferences::deleteCSSTypedOMEnabled()
{
    deleteKey(WebPreferencesKey::cssTypedOMEnabledKey());
}

void WebPreferences::setCSSTypedOMColorEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssTypedOMColorEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssTypedOMColorEnabledKey(), value, true);
}

bool WebPreferences::cssTypedOMColorEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssTypedOMColorEnabledKey());
}

void WebPreferences::deleteCSSTypedOMColorEnabled()
{
    deleteKey(WebPreferencesKey::cssTypedOMColorEnabledKey());
}

void WebPreferences::setMasonryTrackAlignmentEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::masonryTrackAlignmentEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::masonryTrackAlignmentEnabledKey(), value, true);
}

bool WebPreferences::masonryTrackAlignmentEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::masonryTrackAlignmentEnabledKey());
}

void WebPreferences::deleteMasonryTrackAlignmentEnabled()
{
    deleteKey(WebPreferencesKey::masonryTrackAlignmentEnabledKey());
}

void WebPreferences::setCSSColorContrastEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssColorContrastEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssColorContrastEnabledKey(), value, true);
}

bool WebPreferences::cssColorContrastEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssColorContrastEnabledKey());
}

void WebPreferences::deleteCSSColorContrastEnabled()
{
    deleteKey(WebPreferencesKey::cssColorContrastEnabledKey());
}

void WebPreferences::setCSSColorMixEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssColorMixEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssColorMixEnabledKey(), value, false);
}

bool WebPreferences::cssColorMixEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssColorMixEnabledKey());
}

void WebPreferences::deleteCSSColorMixEnabled()
{
    deleteKey(WebPreferencesKey::cssColorMixEnabledKey());
}

void WebPreferences::setCSSMarginTrimEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssMarginTrimEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssMarginTrimEnabledKey(), value, false);
}

bool WebPreferences::cssMarginTrimEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssMarginTrimEnabledKey());
}

void WebPreferences::deleteCSSMarginTrimEnabled()
{
    deleteKey(WebPreferencesKey::cssMarginTrimEnabledKey());
}

void WebPreferences::setOverflowClipEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::overflowClipEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::overflowClipEnabledKey(), value, false);
}

bool WebPreferences::overflowClipEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::overflowClipEnabledKey());
}

void WebPreferences::deleteOverflowClipEnabled()
{
    deleteKey(WebPreferencesKey::overflowClipEnabledKey());
}

void WebPreferences::setCSSScrollbarColorEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssScrollbarColorEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssScrollbarColorEnabledKey(), value, true);
}

bool WebPreferences::cssScrollbarColorEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssScrollbarColorEnabledKey());
}

void WebPreferences::deleteCSSScrollbarColorEnabled()
{
    deleteKey(WebPreferencesKey::cssScrollbarColorEnabledKey());
}

void WebPreferences::setCSSScrollbarGutterEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssScrollbarGutterEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssScrollbarGutterEnabledKey(), value, true);
}

bool WebPreferences::cssScrollbarGutterEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssScrollbarGutterEnabledKey());
}

void WebPreferences::deleteCSSScrollbarGutterEnabled()
{
    deleteKey(WebPreferencesKey::cssScrollbarGutterEnabledKey());
}

void WebPreferences::setCSSScrollbarWidthEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssScrollbarWidthEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssScrollbarWidthEnabledKey(), value, true);
}

bool WebPreferences::cssScrollbarWidthEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssScrollbarWidthEnabledKey());
}

void WebPreferences::deleteCSSScrollbarWidthEnabled()
{
    deleteKey(WebPreferencesKey::cssScrollbarWidthEnabledKey());
}

void WebPreferences::setSubgridEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::subgridEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::subgridEnabledKey(), value, false);
}

bool WebPreferences::subgridEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::subgridEnabledKey());
}

void WebPreferences::deleteSubgridEnabled()
{
    deleteKey(WebPreferencesKey::subgridEnabledKey());
}

void WebPreferences::setCSSTextAlignLastEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssTextAlignLastEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssTextAlignLastEnabledKey(), value, false);
}

bool WebPreferences::cssTextAlignLastEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssTextAlignLastEnabledKey());
}

void WebPreferences::deleteCSSTextAlignLastEnabled()
{
    deleteKey(WebPreferencesKey::cssTextAlignLastEnabledKey());
}

void WebPreferences::setCSSTextBoxTrimEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssTextBoxTrimEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssTextBoxTrimEnabledKey(), value, false);
}

bool WebPreferences::cssTextBoxTrimEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssTextBoxTrimEnabledKey());
}

void WebPreferences::deleteCSSTextBoxTrimEnabled()
{
    deleteKey(WebPreferencesKey::cssTextBoxTrimEnabledKey());
}

void WebPreferences::setCSSTextGroupAlignEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssTextGroupAlignEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssTextGroupAlignEnabledKey(), value, true);
}

bool WebPreferences::cssTextGroupAlignEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssTextGroupAlignEnabledKey());
}

void WebPreferences::deleteCSSTextGroupAlignEnabled()
{
    deleteKey(WebPreferencesKey::cssTextGroupAlignEnabledKey());
}

void WebPreferences::setCSSTextJustifyEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssTextJustifyEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssTextJustifyEnabledKey(), value, true);
}

bool WebPreferences::cssTextJustifyEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssTextJustifyEnabledKey());
}

void WebPreferences::deleteCSSTextJustifyEnabled()
{
    deleteKey(WebPreferencesKey::cssTextJustifyEnabledKey());
}

void WebPreferences::setCSSTextSpacingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssTextSpacingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssTextSpacingEnabledKey(), value, true);
}

bool WebPreferences::cssTextSpacingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssTextSpacingEnabledKey());
}

void WebPreferences::deleteCSSTextSpacingEnabled()
{
    deleteKey(WebPreferencesKey::cssTextSpacingEnabledKey());
}

void WebPreferences::setCSSTextUnderlinePositionLeftRightEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssTextUnderlinePositionLeftRightEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssTextUnderlinePositionLeftRightEnabledKey(), value, true);
}

bool WebPreferences::cssTextUnderlinePositionLeftRightEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssTextUnderlinePositionLeftRightEnabledKey());
}

void WebPreferences::deleteCSSTextUnderlinePositionLeftRightEnabled()
{
    deleteKey(WebPreferencesKey::cssTextUnderlinePositionLeftRightEnabledKey());
}

void WebPreferences::setCSSWhiteSpaceLonghandsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssWhiteSpaceLonghandsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssWhiteSpaceLonghandsEnabledKey(), value, true);
}

bool WebPreferences::cssWhiteSpaceLonghandsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssWhiteSpaceLonghandsEnabledKey());
}

void WebPreferences::deleteCSSWhiteSpaceLonghandsEnabled()
{
    deleteKey(WebPreferencesKey::cssWhiteSpaceLonghandsEnabledKey());
}

void WebPreferences::setCSSTextWrapNewValuesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssTextWrapNewValuesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssTextWrapNewValuesEnabledKey(), value, true);
}

bool WebPreferences::cssTextWrapNewValuesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssTextWrapNewValuesEnabledKey());
}

void WebPreferences::deleteCSSTextWrapNewValuesEnabled()
{
    deleteKey(WebPreferencesKey::cssTextWrapNewValuesEnabledKey());
}

void WebPreferences::setCSSTransformStyleOptimized3DEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssTransformStyleOptimized3DEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssTransformStyleOptimized3DEnabledKey(), value, true);
}

bool WebPreferences::cssTransformStyleOptimized3DEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssTransformStyleOptimized3DEnabledKey());
}

void WebPreferences::deleteCSSTransformStyleOptimized3DEnabled()
{
    deleteKey(WebPreferencesKey::cssTransformStyleOptimized3DEnabledKey());
}

void WebPreferences::setCSSOMViewScrollingAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssOMViewScrollingAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssOMViewScrollingAPIEnabledKey(), value, false);
}

bool WebPreferences::cssOMViewScrollingAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssOMViewScrollingAPIEnabledKey());
}

void WebPreferences::deleteCSSOMViewScrollingAPIEnabled()
{
    deleteKey(WebPreferencesKey::cssOMViewScrollingAPIEnabledKey());
}

void WebPreferences::setCSSOMViewSmoothScrollingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssOMViewSmoothScrollingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssOMViewSmoothScrollingEnabledKey(), value, false);
}

bool WebPreferences::cssOMViewSmoothScrollingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssOMViewSmoothScrollingEnabledKey());
}

void WebPreferences::deleteCSSOMViewSmoothScrollingEnabled()
{
    deleteKey(WebPreferencesKey::cssOMViewSmoothScrollingEnabledKey());
}

void WebPreferences::setCacheAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cacheAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cacheAPIEnabledKey(), value, false);
}

bool WebPreferences::cacheAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cacheAPIEnabledKey());
}

void WebPreferences::deleteCacheAPIEnabled()
{
    deleteKey(WebPreferencesKey::cacheAPIEnabledKey());
}

void WebPreferences::setCanvasColorSpaceEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::canvasColorSpaceEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::canvasColorSpaceEnabledKey(), value, false);
}

bool WebPreferences::canvasColorSpaceEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::canvasColorSpaceEnabledKey());
}

void WebPreferences::deleteCanvasColorSpaceEnabled()
{
    deleteKey(WebPreferencesKey::canvasColorSpaceEnabledKey());
}

void WebPreferences::setCanvasFiltersEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::canvasFiltersEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::canvasFiltersEnabledKey(), value, true);
}

bool WebPreferences::canvasFiltersEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::canvasFiltersEnabledKey());
}

void WebPreferences::deleteCanvasFiltersEnabled()
{
    deleteKey(WebPreferencesKey::canvasFiltersEnabledKey());
}

void WebPreferences::setCanvasUsesAcceleratedDrawing(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::canvasUsesAcceleratedDrawingKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::canvasUsesAcceleratedDrawingKey(), value, false);
}

bool WebPreferences::canvasUsesAcceleratedDrawing() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::canvasUsesAcceleratedDrawingKey());
}

void WebPreferences::deleteCanvasUsesAcceleratedDrawing()
{
    deleteKey(WebPreferencesKey::canvasUsesAcceleratedDrawingKey());
}

void WebPreferences::setCaptureAudioInUIProcessEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::captureAudioInUIProcessEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::captureAudioInUIProcessEnabledKey(), value, true);
}

bool WebPreferences::captureAudioInUIProcessEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::captureAudioInUIProcessEnabledKey());
}

void WebPreferences::deleteCaptureAudioInUIProcessEnabled()
{
    deleteKey(WebPreferencesKey::captureAudioInUIProcessEnabledKey());
}

void WebPreferences::setCaptureVideoInUIProcessEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::captureVideoInUIProcessEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::captureVideoInUIProcessEnabledKey(), value, true);
}

bool WebPreferences::captureVideoInUIProcessEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::captureVideoInUIProcessEnabledKey());
}

void WebPreferences::deleteCaptureVideoInUIProcessEnabled()
{
    deleteKey(WebPreferencesKey::captureVideoInUIProcessEnabledKey());
}

void WebPreferences::setClearSiteDataHTTPHeaderEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::clearSiteDataHTTPHeaderEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::clearSiteDataHTTPHeaderEnabledKey(), value, false);
}

bool WebPreferences::clearSiteDataHTTPHeaderEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::clearSiteDataHTTPHeaderEnabledKey());
}

void WebPreferences::deleteClearSiteDataHTTPHeaderEnabled()
{
    deleteKey(WebPreferencesKey::clearSiteDataHTTPHeaderEnabledKey());
}

void WebPreferences::setClientBadgeEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::clientBadgeEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::clientBadgeEnabledKey(), value, true);
}

bool WebPreferences::clientBadgeEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::clientBadgeEnabledKey());
}

void WebPreferences::deleteClientBadgeEnabled()
{
    deleteKey(WebPreferencesKey::clientBadgeEnabledKey());
}

void WebPreferences::setInputTypeColorEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::inputTypeColorEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::inputTypeColorEnabledKey(), value, false);
}

bool WebPreferences::inputTypeColorEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::inputTypeColorEnabledKey());
}

void WebPreferences::deleteInputTypeColorEnabled()
{
    deleteKey(WebPreferencesKey::inputTypeColorEnabledKey());
}

void WebPreferences::setCompositingBordersVisible(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::compositingBordersVisibleKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::compositingBordersVisibleKey(), value, true);
}

bool WebPreferences::compositingBordersVisible() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::compositingBordersVisibleKey());
}

void WebPreferences::deleteCompositingBordersVisible()
{
    deleteKey(WebPreferencesKey::compositingBordersVisibleKey());
}

void WebPreferences::setCompositingRepaintCountersVisible(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::compositingRepaintCountersVisibleKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::compositingRepaintCountersVisibleKey(), value, true);
}

bool WebPreferences::compositingRepaintCountersVisible() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::compositingRepaintCountersVisibleKey());
}

void WebPreferences::deleteCompositingRepaintCountersVisible()
{
    deleteKey(WebPreferencesKey::compositingRepaintCountersVisibleKey());
}

void WebPreferences::setCompressionStreamEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::compressionStreamEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::compressionStreamEnabledKey(), value, false);
}

bool WebPreferences::compressionStreamEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::compressionStreamEnabledKey());
}

void WebPreferences::deleteCompressionStreamEnabled()
{
    deleteKey(WebPreferencesKey::compressionStreamEnabledKey());
}

void WebPreferences::setConstructableStylesheetsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::constructableStylesheetsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::constructableStylesheetsEnabledKey(), value, false);
}

bool WebPreferences::constructableStylesheetsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::constructableStylesheetsEnabledKey());
}

void WebPreferences::deleteConstructableStylesheetsEnabled()
{
    deleteKey(WebPreferencesKey::constructableStylesheetsEnabledKey());
}

void WebPreferences::setContactPickerAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::contactPickerAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::contactPickerAPIEnabledKey(), value, true);
}

bool WebPreferences::contactPickerAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::contactPickerAPIEnabledKey());
}

void WebPreferences::deleteContactPickerAPIEnabled()
{
    deleteKey(WebPreferencesKey::contactPickerAPIEnabledKey());
}

void WebPreferences::setSampleBufferContentKeySessionSupportEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::sampleBufferContentKeySessionSupportEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::sampleBufferContentKeySessionSupportEnabledKey(), value, true);
}

bool WebPreferences::sampleBufferContentKeySessionSupportEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::sampleBufferContentKeySessionSupportEnabledKey());
}

void WebPreferences::deleteSampleBufferContentKeySessionSupportEnabled()
{
    deleteKey(WebPreferencesKey::sampleBufferContentKeySessionSupportEnabledKey());
}

void WebPreferences::setCookieConsentAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cookieConsentAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cookieConsentAPIEnabledKey(), value, true);
}

bool WebPreferences::cookieConsentAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cookieConsentAPIEnabledKey());
}

void WebPreferences::deleteCookieConsentAPIEnabled()
{
    deleteKey(WebPreferencesKey::cookieConsentAPIEnabledKey());
}

void WebPreferences::setCookieStoreAPIExtendedAttributesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cookieStoreAPIExtendedAttributesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cookieStoreAPIExtendedAttributesEnabledKey(), value, true);
}

bool WebPreferences::cookieStoreAPIExtendedAttributesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cookieStoreAPIExtendedAttributesEnabledKey());
}

void WebPreferences::deleteCookieStoreAPIExtendedAttributesEnabled()
{
    deleteKey(WebPreferencesKey::cookieStoreAPIExtendedAttributesEnabledKey());
}

void WebPreferences::setCookieStoreAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cookieStoreAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cookieStoreAPIEnabledKey(), value, true);
}

bool WebPreferences::cookieStoreAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cookieStoreAPIEnabledKey());
}

void WebPreferences::deleteCookieStoreAPIEnabled()
{
    deleteKey(WebPreferencesKey::cookieStoreAPIEnabledKey());
}

void WebPreferences::setCookieEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cookieEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cookieEnabledKey(), value, false);
}

bool WebPreferences::cookieEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cookieEnabledKey());
}

void WebPreferences::deleteCookieEnabled()
{
    deleteKey(WebPreferencesKey::cookieEnabledKey());
}

void WebPreferences::setCrossOriginEmbedderPolicyEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::crossOriginEmbedderPolicyEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::crossOriginEmbedderPolicyEnabledKey(), value, false);
}

bool WebPreferences::crossOriginEmbedderPolicyEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::crossOriginEmbedderPolicyEnabledKey());
}

void WebPreferences::deleteCrossOriginEmbedderPolicyEnabled()
{
    deleteKey(WebPreferencesKey::crossOriginEmbedderPolicyEnabledKey());
}

void WebPreferences::setCrossOriginOpenerPolicyEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::crossOriginOpenerPolicyEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::crossOriginOpenerPolicyEnabledKey(), value, false);
}

bool WebPreferences::crossOriginOpenerPolicyEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::crossOriginOpenerPolicyEnabledKey());
}

void WebPreferences::deleteCrossOriginOpenerPolicyEnabled()
{
    deleteKey(WebPreferencesKey::crossOriginOpenerPolicyEnabledKey());
}

void WebPreferences::setCustomPasteboardDataEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::customPasteboardDataEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::customPasteboardDataEnabledKey(), value, false);
}

bool WebPreferences::customPasteboardDataEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::customPasteboardDataEnabledKey());
}

void WebPreferences::deleteCustomPasteboardDataEnabled()
{
    deleteKey(WebPreferencesKey::customPasteboardDataEnabledKey());
}

void WebPreferences::setDOMPasteAccessRequestsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::domPasteAccessRequestsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::domPasteAccessRequestsEnabledKey(), value, true);
}

bool WebPreferences::domPasteAccessRequestsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::domPasteAccessRequestsEnabledKey());
}

void WebPreferences::deleteDOMPasteAccessRequestsEnabled()
{
    deleteKey(WebPreferencesKey::domPasteAccessRequestsEnabledKey());
}

void WebPreferences::setDOMTimersThrottlingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::domTimersThrottlingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::domTimersThrottlingEnabledKey(), value, false);
}

bool WebPreferences::domTimersThrottlingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::domTimersThrottlingEnabledKey());
}

void WebPreferences::deleteDOMTimersThrottlingEnabled()
{
    deleteKey(WebPreferencesKey::domTimersThrottlingEnabledKey());
}

void WebPreferences::setDeclarativeShadowDOMInDOMParserEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::declarativeShadowDOMInDOMParserEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::declarativeShadowDOMInDOMParserEnabledKey(), value, true);
}

bool WebPreferences::declarativeShadowDOMInDOMParserEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::declarativeShadowDOMInDOMParserEnabledKey());
}

void WebPreferences::deleteDeclarativeShadowDOMInDOMParserEnabled()
{
    deleteKey(WebPreferencesKey::declarativeShadowDOMInDOMParserEnabledKey());
}

void WebPreferences::setZoomOnDoubleTapWhenRoot(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::zoomOnDoubleTapWhenRootKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::zoomOnDoubleTapWhenRootKey(), value, true);
}

bool WebPreferences::zoomOnDoubleTapWhenRoot() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::zoomOnDoubleTapWhenRootKey());
}

void WebPreferences::deleteZoomOnDoubleTapWhenRoot()
{
    deleteKey(WebPreferencesKey::zoomOnDoubleTapWhenRootKey());
}

void WebPreferences::setAlwaysZoomOnDoubleTap(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::alwaysZoomOnDoubleTapKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::alwaysZoomOnDoubleTapKey(), value, true);
}

bool WebPreferences::alwaysZoomOnDoubleTap() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::alwaysZoomOnDoubleTapKey());
}

void WebPreferences::deleteAlwaysZoomOnDoubleTap()
{
    deleteKey(WebPreferencesKey::alwaysZoomOnDoubleTapKey());
}

void WebPreferences::setDataTransferItemsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::dataTransferItemsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::dataTransferItemsEnabledKey(), value, false);
}

bool WebPreferences::dataTransferItemsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::dataTransferItemsEnabledKey());
}

void WebPreferences::deleteDataTransferItemsEnabled()
{
    deleteKey(WebPreferencesKey::dataTransferItemsEnabledKey());
}

void WebPreferences::setDataListElementEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::dataListElementEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::dataListElementEnabledKey(), value, false);
}

bool WebPreferences::dataListElementEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::dataListElementEnabledKey());
}

void WebPreferences::deleteDataListElementEnabled()
{
    deleteKey(WebPreferencesKey::dataListElementEnabledKey());
}

void WebPreferences::setInputTypeDateEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::inputTypeDateEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::inputTypeDateEnabledKey(), value, false);
}

bool WebPreferences::inputTypeDateEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::inputTypeDateEnabledKey());
}

void WebPreferences::deleteInputTypeDateEnabled()
{
    deleteKey(WebPreferencesKey::inputTypeDateEnabledKey());
}

void WebPreferences::setDateTimeInputsEditableComponentsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::dateTimeInputsEditableComponentsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::dateTimeInputsEditableComponentsEnabledKey(), value, false);
}

bool WebPreferences::dateTimeInputsEditableComponentsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::dateTimeInputsEditableComponentsEnabledKey());
}

void WebPreferences::deleteDateTimeInputsEditableComponentsEnabled()
{
    deleteKey(WebPreferencesKey::dateTimeInputsEditableComponentsEnabledKey());
}

void WebPreferences::setDeclarativeShadowDOMEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::declarativeShadowDOMEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::declarativeShadowDOMEnabledKey(), value, false);
}

bool WebPreferences::declarativeShadowDOMEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::declarativeShadowDOMEnabledKey());
}

void WebPreferences::deleteDeclarativeShadowDOMEnabled()
{
    deleteKey(WebPreferencesKey::declarativeShadowDOMEnabledKey());
}

void WebPreferences::setDefaultARIAForCustomElementsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::defaultARIAForCustomElementsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::defaultARIAForCustomElementsEnabledKey(), value, false);
}

bool WebPreferences::defaultARIAForCustomElementsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::defaultARIAForCustomElementsEnabledKey());
}

void WebPreferences::deleteDefaultARIAForCustomElementsEnabled()
{
    deleteKey(WebPreferencesKey::defaultARIAForCustomElementsEnabledKey());
}

void WebPreferences::setShouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::shouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaintKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::shouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaintKey(), value, false);
}

bool WebPreferences::shouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::shouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaintKey());
}

void WebPreferences::deleteShouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint()
{
    deleteKey(WebPreferencesKey::shouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaintKey());
}

void WebPreferences::setDeprecateRSAESPKCSWebCryptoEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::deprecateRSAESPKCSWebCryptoEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::deprecateRSAESPKCSWebCryptoEnabledKey(), value, false);
}

bool WebPreferences::deprecateRSAESPKCSWebCryptoEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::deprecateRSAESPKCSWebCryptoEnabledKey());
}

void WebPreferences::deleteDeprecateRSAESPKCSWebCryptoEnabled()
{
    deleteKey(WebPreferencesKey::deprecateRSAESPKCSWebCryptoEnabledKey());
}

void WebPreferences::setDeprecationReportingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::deprecationReportingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::deprecationReportingEnabledKey(), value, true);
}

bool WebPreferences::deprecationReportingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::deprecationReportingEnabledKey());
}

void WebPreferences::deleteDeprecationReportingEnabled()
{
    deleteKey(WebPreferencesKey::deprecationReportingEnabledKey());
}

void WebPreferences::setDiagnosticLoggingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::diagnosticLoggingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::diagnosticLoggingEnabledKey(), value, false);
}

bool WebPreferences::diagnosticLoggingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::diagnosticLoggingEnabledKey());
}

void WebPreferences::deleteDiagnosticLoggingEnabled()
{
    deleteKey(WebPreferencesKey::diagnosticLoggingEnabledKey());
}

void WebPreferences::setDirectoryUploadEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::directoryUploadEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::directoryUploadEnabledKey(), value, false);
}

bool WebPreferences::directoryUploadEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::directoryUploadEnabledKey());
}

void WebPreferences::deleteDirectoryUploadEnabled()
{
    deleteKey(WebPreferencesKey::directoryUploadEnabledKey());
}

void WebPreferences::setIsThirdPartyCookieBlockingDisabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::isThirdPartyCookieBlockingDisabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::isThirdPartyCookieBlockingDisabledKey(), value, false);
}

bool WebPreferences::isThirdPartyCookieBlockingDisabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::isThirdPartyCookieBlockingDisabledKey());
}

void WebPreferences::deleteIsThirdPartyCookieBlockingDisabled()
{
    deleteKey(WebPreferencesKey::isThirdPartyCookieBlockingDisabledKey());
}

void WebPreferences::setIsFirstPartyWebsiteDataRemovalDisabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::isFirstPartyWebsiteDataRemovalDisabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::isFirstPartyWebsiteDataRemovalDisabledKey(), value, false);
}

bool WebPreferences::isFirstPartyWebsiteDataRemovalDisabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::isFirstPartyWebsiteDataRemovalDisabledKey());
}

void WebPreferences::deleteIsFirstPartyWebsiteDataRemovalDisabled()
{
    deleteKey(WebPreferencesKey::isFirstPartyWebsiteDataRemovalDisabledKey());
}

void WebPreferences::setDisableScreenSizeOverride(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::disableScreenSizeOverrideKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::disableScreenSizeOverrideKey(), value, true);
}

bool WebPreferences::disableScreenSizeOverride() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::disableScreenSizeOverrideKey());
}

void WebPreferences::deleteDisableScreenSizeOverride()
{
    deleteKey(WebPreferencesKey::disableScreenSizeOverrideKey());
}

void WebPreferences::setDisallowSyncXHRDuringPageDismissalEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::disallowSyncXHRDuringPageDismissalEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::disallowSyncXHRDuringPageDismissalEnabledKey(), value, false);
}

bool WebPreferences::disallowSyncXHRDuringPageDismissalEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::disallowSyncXHRDuringPageDismissalEnabledKey());
}

void WebPreferences::deleteDisallowSyncXHRDuringPageDismissalEnabled()
{
    deleteKey(WebPreferencesKey::disallowSyncXHRDuringPageDismissalEnabledKey());
}

void WebPreferences::setDisplayListDrawingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::displayListDrawingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::displayListDrawingEnabledKey(), value, true);
}

bool WebPreferences::displayListDrawingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::displayListDrawingEnabledKey());
}

void WebPreferences::deleteDisplayListDrawingEnabled()
{
    deleteKey(WebPreferencesKey::displayListDrawingEnabledKey());
}

void WebPreferences::setShouldDropNearSuspendedAssertionAfterDelay(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::shouldDropNearSuspendedAssertionAfterDelayKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::shouldDropNearSuspendedAssertionAfterDelayKey(), value, true);
}

bool WebPreferences::shouldDropNearSuspendedAssertionAfterDelay() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::shouldDropNearSuspendedAssertionAfterDelayKey());
}

void WebPreferences::deleteShouldDropNearSuspendedAssertionAfterDelay()
{
    deleteKey(WebPreferencesKey::shouldDropNearSuspendedAssertionAfterDelayKey());
}

void WebPreferences::setEmbedElementEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::embedElementEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::embedElementEnabledKey(), value, false);
}

bool WebPreferences::embedElementEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::embedElementEnabledKey());
}

void WebPreferences::deleteEmbedElementEnabled()
{
    deleteKey(WebPreferencesKey::embedElementEnabledKey());
}

void WebPreferences::setAutomaticLiveResizeEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::automaticLiveResizeEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::automaticLiveResizeEnabledKey(), value, true);
}

bool WebPreferences::automaticLiveResizeEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::automaticLiveResizeEnabledKey());
}

void WebPreferences::deleteAutomaticLiveResizeEnabled()
{
    deleteKey(WebPreferencesKey::automaticLiveResizeEnabledKey());
}

void WebPreferences::setCanvasFingerprintingQuirkEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::canvasFingerprintingQuirkEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::canvasFingerprintingQuirkEnabledKey(), value, false);
}

bool WebPreferences::canvasFingerprintingQuirkEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::canvasFingerprintingQuirkEnabledKey());
}

void WebPreferences::deleteCanvasFingerprintingQuirkEnabled()
{
    deleteKey(WebPreferencesKey::canvasFingerprintingQuirkEnabledKey());
}

void WebPreferences::setEnumeratingAllNetworkInterfacesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::enumeratingAllNetworkInterfacesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::enumeratingAllNetworkInterfacesEnabledKey(), value, true);
}

bool WebPreferences::enumeratingAllNetworkInterfacesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::enumeratingAllNetworkInterfacesEnabledKey());
}

void WebPreferences::deleteEnumeratingAllNetworkInterfacesEnabled()
{
    deleteKey(WebPreferencesKey::enumeratingAllNetworkInterfacesEnabledKey());
}

void WebPreferences::setEnumeratingVisibleNetworkInterfacesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::enumeratingVisibleNetworkInterfacesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::enumeratingVisibleNetworkInterfacesEnabledKey(), value, true);
}

bool WebPreferences::enumeratingVisibleNetworkInterfacesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::enumeratingVisibleNetworkInterfacesEnabledKey());
}

void WebPreferences::deleteEnumeratingVisibleNetworkInterfacesEnabled()
{
    deleteKey(WebPreferencesKey::enumeratingVisibleNetworkInterfacesEnabledKey());
}

void WebPreferences::setICECandidateFilteringEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::iceCandidateFilteringEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::iceCandidateFilteringEnabledKey(), value, true);
}

bool WebPreferences::iceCandidateFilteringEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::iceCandidateFilteringEnabledKey());
}

void WebPreferences::deleteICECandidateFilteringEnabled()
{
    deleteKey(WebPreferencesKey::iceCandidateFilteringEnabledKey());
}

void WebPreferences::setLegacyEncryptedMediaAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::legacyEncryptedMediaAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::legacyEncryptedMediaAPIEnabledKey(), value, false);
}

bool WebPreferences::legacyEncryptedMediaAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::legacyEncryptedMediaAPIEnabledKey());
}

void WebPreferences::deleteLegacyEncryptedMediaAPIEnabled()
{
    deleteKey(WebPreferencesKey::legacyEncryptedMediaAPIEnabledKey());
}

void WebPreferences::setMockCaptureDevicesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mockCaptureDevicesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mockCaptureDevicesEnabledKey(), value, true);
}

bool WebPreferences::mockCaptureDevicesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mockCaptureDevicesEnabledKey());
}

void WebPreferences::deleteMockCaptureDevicesEnabled()
{
    deleteKey(WebPreferencesKey::mockCaptureDevicesEnabledKey());
}

void WebPreferences::setPdfJSViewerEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::pdfJSViewerEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::pdfJSViewerEnabledKey(), value, true);
}

bool WebPreferences::pdfJSViewerEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::pdfJSViewerEnabledKey());
}

void WebPreferences::deletePdfJSViewerEnabled()
{
    deleteKey(WebPreferencesKey::pdfJSViewerEnabledKey());
}

void WebPreferences::setBackgroundWebContentRunningBoardThrottlingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::backgroundWebContentRunningBoardThrottlingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::backgroundWebContentRunningBoardThrottlingEnabledKey(), value, true);
}

bool WebPreferences::backgroundWebContentRunningBoardThrottlingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::backgroundWebContentRunningBoardThrottlingEnabledKey());
}

void WebPreferences::deleteBackgroundWebContentRunningBoardThrottlingEnabled()
{
    deleteKey(WebPreferencesKey::backgroundWebContentRunningBoardThrottlingEnabledKey());
}

void WebPreferences::setBackgroundFetchAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::backgroundFetchAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::backgroundFetchAPIEnabledKey(), value, true);
}

bool WebPreferences::backgroundFetchAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::backgroundFetchAPIEnabledKey());
}

void WebPreferences::deleteBackgroundFetchAPIEnabled()
{
    deleteKey(WebPreferencesKey::backgroundFetchAPIEnabledKey());
}

void WebPreferences::setExperimentalSandboxEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::experimentalSandboxEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::experimentalSandboxEnabledKey(), value, true);
}

bool WebPreferences::experimentalSandboxEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::experimentalSandboxEnabledKey());
}

void WebPreferences::deleteExperimentalSandboxEnabled()
{
    deleteKey(WebPreferencesKey::experimentalSandboxEnabledKey());
}

void WebPreferences::setStrictSecureDecodingForAllObjC(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::strictSecureDecodingForAllObjCKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::strictSecureDecodingForAllObjCKey(), value, true);
}

bool WebPreferences::strictSecureDecodingForAllObjC() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::strictSecureDecodingForAllObjCKey());
}

void WebPreferences::deleteStrictSecureDecodingForAllObjC()
{
    deleteKey(WebPreferencesKey::strictSecureDecodingForAllObjCKey());
}

void WebPreferences::setEnterKeyHintEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::enterKeyHintEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::enterKeyHintEnabledKey(), value, true);
}

bool WebPreferences::enterKeyHintEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::enterKeyHintEnabledKey());
}

void WebPreferences::deleteEnterKeyHintEnabled()
{
    deleteKey(WebPreferencesKey::enterKeyHintEnabledKey());
}

void WebPreferences::setEventHandlerDrivenSmoothKeyboardScrollingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::eventHandlerDrivenSmoothKeyboardScrollingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::eventHandlerDrivenSmoothKeyboardScrollingEnabledKey(), value, true);
}

bool WebPreferences::eventHandlerDrivenSmoothKeyboardScrollingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::eventHandlerDrivenSmoothKeyboardScrollingEnabledKey());
}

void WebPreferences::deleteEventHandlerDrivenSmoothKeyboardScrollingEnabled()
{
    deleteKey(WebPreferencesKey::eventHandlerDrivenSmoothKeyboardScrollingEnabledKey());
}

void WebPreferences::setMediaSessionCoordinatorEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mediaSessionCoordinatorEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mediaSessionCoordinatorEnabledKey(), value, false);
}

bool WebPreferences::mediaSessionCoordinatorEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mediaSessionCoordinatorEnabledKey());
}

void WebPreferences::deleteMediaSessionCoordinatorEnabled()
{
    deleteKey(WebPreferencesKey::mediaSessionCoordinatorEnabledKey());
}

void WebPreferences::setMediaSessionPlaylistEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mediaSessionPlaylistEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mediaSessionPlaylistEnabledKey(), value, false);
}

bool WebPreferences::mediaSessionPlaylistEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mediaSessionPlaylistEnabledKey());
}

void WebPreferences::deleteMediaSessionPlaylistEnabled()
{
    deleteKey(WebPreferencesKey::mediaSessionPlaylistEnabledKey());
}

void WebPreferences::setMediaSourceInlinePaintingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mediaSourceInlinePaintingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mediaSourceInlinePaintingEnabledKey(), value, true);
}

bool WebPreferences::mediaSourceInlinePaintingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mediaSourceInlinePaintingEnabledKey());
}

void WebPreferences::deleteMediaSourceInlinePaintingEnabled()
{
    deleteKey(WebPreferencesKey::mediaSourceInlinePaintingEnabledKey());
}

void WebPreferences::setCFNetworkNetworkLoaderEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cFNetworkNetworkLoaderEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cFNetworkNetworkLoaderEnabledKey(), value, true);
}

bool WebPreferences::cFNetworkNetworkLoaderEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cFNetworkNetworkLoaderEnabledKey());
}

void WebPreferences::deleteCFNetworkNetworkLoaderEnabled()
{
    deleteKey(WebPreferencesKey::cFNetworkNetworkLoaderEnabledKey());
}

void WebPreferences::setFTPEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::ftpEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::ftpEnabledKey(), value, false);
}

bool WebPreferences::ftpEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::ftpEnabledKey());
}

void WebPreferences::deleteFTPEnabled()
{
    deleteKey(WebPreferencesKey::ftpEnabledKey());
}

void WebPreferences::setPreferFasterClickOverDoubleTap(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::preferFasterClickOverDoubleTapKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::preferFasterClickOverDoubleTapKey(), value, true);
}

bool WebPreferences::preferFasterClickOverDoubleTap() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::preferFasterClickOverDoubleTapKey());
}

void WebPreferences::deletePreferFasterClickOverDoubleTap()
{
    deleteKey(WebPreferencesKey::preferFasterClickOverDoubleTapKey());
}

void WebPreferences::setFasterClicksEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::fasterClicksEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::fasterClicksEnabledKey(), value, true);
}

bool WebPreferences::fasterClicksEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::fasterClicksEnabledKey());
}

void WebPreferences::deleteFasterClicksEnabled()
{
    deleteKey(WebPreferencesKey::fasterClicksEnabledKey());
}

void WebPreferences::setFetchAPIKeepAliveEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::fetchAPIKeepAliveEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::fetchAPIKeepAliveEnabledKey(), value, false);
}

bool WebPreferences::fetchAPIKeepAliveEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::fetchAPIKeepAliveEnabledKey());
}

void WebPreferences::deleteFetchAPIKeepAliveEnabled()
{
    deleteKey(WebPreferencesKey::fetchAPIKeepAliveEnabledKey());
}

void WebPreferences::setFetchAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::fetchAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::fetchAPIEnabledKey(), value, false);
}

bool WebPreferences::fetchAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::fetchAPIEnabledKey());
}

void WebPreferences::deleteFetchAPIEnabled()
{
    deleteKey(WebPreferencesKey::fetchAPIEnabledKey());
}

void WebPreferences::setFetchMetadataEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::fetchMetadataEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::fetchMetadataEnabledKey(), value, false);
}

bool WebPreferences::fetchMetadataEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::fetchMetadataEnabledKey());
}

void WebPreferences::deleteFetchMetadataEnabled()
{
    deleteKey(WebPreferencesKey::fetchMetadataEnabledKey());
}

void WebPreferences::setFetchPriorityEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::fetchPriorityEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::fetchPriorityEnabledKey(), value, true);
}

bool WebPreferences::fetchPriorityEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::fetchPriorityEnabledKey());
}

void WebPreferences::deleteFetchPriorityEnabled()
{
    deleteKey(WebPreferencesKey::fetchPriorityEnabledKey());
}

void WebPreferences::setFileSystemAccessEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::fileSystemAccessEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::fileSystemAccessEnabledKey(), value, false);
}

bool WebPreferences::fileSystemAccessEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::fileSystemAccessEnabledKey());
}

void WebPreferences::deleteFileSystemAccessEnabled()
{
    deleteKey(WebPreferencesKey::fileSystemAccessEnabledKey());
}

void WebPreferences::setFileReaderAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::fileReaderAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::fileReaderAPIEnabledKey(), value, false);
}

bool WebPreferences::fileReaderAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::fileReaderAPIEnabledKey());
}

void WebPreferences::deleteFileReaderAPIEnabled()
{
    deleteKey(WebPreferencesKey::fileReaderAPIEnabledKey());
}

void WebPreferences::setRestrictedHTTPResponseAccess(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::restrictedHTTPResponseAccessKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::restrictedHTTPResponseAccessKey(), value, true);
}

bool WebPreferences::restrictedHTTPResponseAccess() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::restrictedHTTPResponseAccessKey());
}

void WebPreferences::deleteRestrictedHTTPResponseAccess()
{
    deleteKey(WebPreferencesKey::restrictedHTTPResponseAccessKey());
}

void WebPreferences::setForceAlwaysUserScalable(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::forceAlwaysUserScalableKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::forceAlwaysUserScalableKey(), value, true);
}

bool WebPreferences::forceAlwaysUserScalable() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::forceAlwaysUserScalableKey());
}

void WebPreferences::deleteForceAlwaysUserScalable()
{
    deleteKey(WebPreferencesKey::forceAlwaysUserScalableKey());
}

void WebPreferences::setRequestSubmitEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::requestSubmitEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::requestSubmitEnabledKey(), value, false);
}

bool WebPreferences::requestSubmitEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::requestSubmitEnabledKey());
}

void WebPreferences::deleteRequestSubmitEnabled()
{
    deleteKey(WebPreferencesKey::requestSubmitEnabledKey());
}

void WebPreferences::setFormAssociatedCustomElementsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::formAssociatedCustomElementsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::formAssociatedCustomElementsEnabledKey(), value, false);
}

bool WebPreferences::formAssociatedCustomElementsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::formAssociatedCustomElementsEnabledKey());
}

void WebPreferences::deleteFormAssociatedCustomElementsEnabled()
{
    deleteKey(WebPreferencesKey::formAssociatedCustomElementsEnabledKey());
}

void WebPreferences::setFrameFlatteningEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::frameFlatteningEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::frameFlatteningEnabledKey(), value, false);
}

bool WebPreferences::frameFlatteningEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::frameFlatteningEnabledKey());
}

void WebPreferences::deleteFrameFlatteningEnabled()
{
    deleteKey(WebPreferencesKey::frameFlatteningEnabledKey());
}

void WebPreferences::setLayoutFormattingContextEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::layoutFormattingContextEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::layoutFormattingContextEnabledKey(), value, true);
}

bool WebPreferences::layoutFormattingContextEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::layoutFormattingContextEnabledKey());
}

void WebPreferences::deleteLayoutFormattingContextEnabled()
{
    deleteKey(WebPreferencesKey::layoutFormattingContextEnabledKey());
}

void WebPreferences::setFullScreenEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::fullScreenEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::fullScreenEnabledKey(), value, false);
}

bool WebPreferences::fullScreenEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::fullScreenEnabledKey());
}

void WebPreferences::deleteFullScreenEnabled()
{
    deleteKey(WebPreferencesKey::fullScreenEnabledKey());
}

void WebPreferences::setFullscreenSceneAspectRatioLockingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::fullscreenSceneAspectRatioLockingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::fullscreenSceneAspectRatioLockingEnabledKey(), value, true);
}

bool WebPreferences::fullscreenSceneAspectRatioLockingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::fullscreenSceneAspectRatioLockingEnabledKey());
}

void WebPreferences::deleteFullscreenSceneAspectRatioLockingEnabled()
{
    deleteKey(WebPreferencesKey::fullscreenSceneAspectRatioLockingEnabledKey());
}

void WebPreferences::setFullscreenSceneDimmingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::fullscreenSceneDimmingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::fullscreenSceneDimmingEnabledKey(), value, true);
}

bool WebPreferences::fullscreenSceneDimmingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::fullscreenSceneDimmingEnabledKey());
}

void WebPreferences::deleteFullscreenSceneDimmingEnabled()
{
    deleteKey(WebPreferencesKey::fullscreenSceneDimmingEnabledKey());
}

void WebPreferences::setCaptureAudioInGPUProcessEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::captureAudioInGPUProcessEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::captureAudioInGPUProcessEnabledKey(), value, true);
}

bool WebPreferences::captureAudioInGPUProcessEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::captureAudioInGPUProcessEnabledKey());
}

void WebPreferences::deleteCaptureAudioInGPUProcessEnabled()
{
    deleteKey(WebPreferencesKey::captureAudioInGPUProcessEnabledKey());
}

void WebPreferences::setBlockMediaLayerRehostingInWebContentProcess(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::blockMediaLayerRehostingInWebContentProcessKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::blockMediaLayerRehostingInWebContentProcessKey(), value, true);
}

bool WebPreferences::blockMediaLayerRehostingInWebContentProcess() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::blockMediaLayerRehostingInWebContentProcessKey());
}

void WebPreferences::deleteBlockMediaLayerRehostingInWebContentProcess()
{
    deleteKey(WebPreferencesKey::blockMediaLayerRehostingInWebContentProcessKey());
}

void WebPreferences::setUseGPUProcessForCanvasRenderingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::useGPUProcessForCanvasRenderingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::useGPUProcessForCanvasRenderingEnabledKey(), value, false);
}

bool WebPreferences::useGPUProcessForCanvasRenderingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::useGPUProcessForCanvasRenderingEnabledKey());
}

void WebPreferences::deleteUseGPUProcessForCanvasRenderingEnabled()
{
    deleteKey(WebPreferencesKey::useGPUProcessForCanvasRenderingEnabledKey());
}

void WebPreferences::setManageCaptureStatusBarInGPUProcessEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::manageCaptureStatusBarInGPUProcessEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::manageCaptureStatusBarInGPUProcessEnabledKey(), value, true);
}

bool WebPreferences::manageCaptureStatusBarInGPUProcessEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::manageCaptureStatusBarInGPUProcessEnabledKey());
}

void WebPreferences::deleteManageCaptureStatusBarInGPUProcessEnabled()
{
    deleteKey(WebPreferencesKey::manageCaptureStatusBarInGPUProcessEnabledKey());
}

void WebPreferences::setUseGPUProcessForDOMRenderingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::useGPUProcessForDOMRenderingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::useGPUProcessForDOMRenderingEnabledKey(), value, false);
}

bool WebPreferences::useGPUProcessForDOMRenderingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::useGPUProcessForDOMRenderingEnabledKey());
}

void WebPreferences::deleteUseGPUProcessForDOMRenderingEnabled()
{
    deleteKey(WebPreferencesKey::useGPUProcessForDOMRenderingEnabledKey());
}

void WebPreferences::setUseGPUProcessForMediaEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::useGPUProcessForMediaEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::useGPUProcessForMediaEnabledKey(), value, false);
}

bool WebPreferences::useGPUProcessForMediaEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::useGPUProcessForMediaEnabledKey());
}

void WebPreferences::deleteUseGPUProcessForMediaEnabled()
{
    deleteKey(WebPreferencesKey::useGPUProcessForMediaEnabledKey());
}

void WebPreferences::setUseGPUProcessForDisplayCapture(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::useGPUProcessForDisplayCaptureKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::useGPUProcessForDisplayCaptureKey(), value, false);
}

bool WebPreferences::useGPUProcessForDisplayCapture() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::useGPUProcessForDisplayCaptureKey());
}

void WebPreferences::deleteUseGPUProcessForDisplayCapture()
{
    deleteKey(WebPreferencesKey::useGPUProcessForDisplayCaptureKey());
}

void WebPreferences::setCaptureVideoInGPUProcessEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::captureVideoInGPUProcessEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::captureVideoInGPUProcessEnabledKey(), value, true);
}

bool WebPreferences::captureVideoInGPUProcessEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::captureVideoInGPUProcessEnabledKey());
}

void WebPreferences::deleteCaptureVideoInGPUProcessEnabled()
{
    deleteKey(WebPreferencesKey::captureVideoInGPUProcessEnabledKey());
}

void WebPreferences::setUseGPUProcessForWebGLEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::useGPUProcessForWebGLEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::useGPUProcessForWebGLEnabledKey(), value, true);
}

bool WebPreferences::useGPUProcessForWebGLEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::useGPUProcessForWebGLEnabledKey());
}

void WebPreferences::deleteUseGPUProcessForWebGLEnabled()
{
    deleteKey(WebPreferencesKey::useGPUProcessForWebGLEnabledKey());
}

void WebPreferences::setWebRTCPlatformCodecsInGPUProcessEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webRTCPlatformCodecsInGPUProcessEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webRTCPlatformCodecsInGPUProcessEnabledKey(), value, false);
}

bool WebPreferences::webRTCPlatformCodecsInGPUProcessEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webRTCPlatformCodecsInGPUProcessEnabledKey());
}

void WebPreferences::deleteWebRTCPlatformCodecsInGPUProcessEnabled()
{
    deleteKey(WebPreferencesKey::webRTCPlatformCodecsInGPUProcessEnabledKey());
}

void WebPreferences::setGamepadTriggerRumbleEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::gamepadTriggerRumbleEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::gamepadTriggerRumbleEnabledKey(), value, true);
}

bool WebPreferences::gamepadTriggerRumbleEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::gamepadTriggerRumbleEnabledKey());
}

void WebPreferences::deleteGamepadTriggerRumbleEnabled()
{
    deleteKey(WebPreferencesKey::gamepadTriggerRumbleEnabledKey());
}

void WebPreferences::setGamepadVibrationActuatorEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::gamepadVibrationActuatorEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::gamepadVibrationActuatorEnabledKey(), value, false);
}

bool WebPreferences::gamepadVibrationActuatorEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::gamepadVibrationActuatorEnabledKey());
}

void WebPreferences::deleteGamepadVibrationActuatorEnabled()
{
    deleteKey(WebPreferencesKey::gamepadVibrationActuatorEnabledKey());
}

void WebPreferences::setGamepadsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::gamepadsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::gamepadsEnabledKey(), value, false);
}

bool WebPreferences::gamepadsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::gamepadsEnabledKey());
}

void WebPreferences::deleteGamepadsEnabled()
{
    deleteKey(WebPreferencesKey::gamepadsEnabledKey());
}

void WebPreferences::setGenericCueAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::genericCueAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::genericCueAPIEnabledKey(), value, false);
}

bool WebPreferences::genericCueAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::genericCueAPIEnabledKey());
}

void WebPreferences::deleteGenericCueAPIEnabled()
{
    deleteKey(WebPreferencesKey::genericCueAPIEnabledKey());
}

void WebPreferences::setGraphicsContextFiltersEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::graphicsContextFiltersEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::graphicsContextFiltersEnabledKey(), value, true);
}

bool WebPreferences::graphicsContextFiltersEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::graphicsContextFiltersEnabledKey());
}

void WebPreferences::deleteGraphicsContextFiltersEnabled()
{
    deleteKey(WebPreferencesKey::graphicsContextFiltersEnabledKey());
}

void WebPreferences::setAcceleratedDrawingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::acceleratedDrawingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::acceleratedDrawingEnabledKey(), value, true);
}

bool WebPreferences::acceleratedDrawingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::acceleratedDrawingEnabledKey());
}

void WebPreferences::deleteAcceleratedDrawingEnabled()
{
    deleteKey(WebPreferencesKey::acceleratedDrawingEnabledKey());
}

void WebPreferences::setDialogElementEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::dialogElementEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::dialogElementEnabledKey(), value, false);
}

bool WebPreferences::dialogElementEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::dialogElementEnabledKey());
}

void WebPreferences::deleteDialogElementEnabled()
{
    deleteKey(WebPreferencesKey::dialogElementEnabledKey());
}

void WebPreferences::setModelElementEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::modelElementEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::modelElementEnabledKey(), value, true);
}

bool WebPreferences::modelElementEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::modelElementEnabledKey());
}

void WebPreferences::deleteModelElementEnabled()
{
    deleteKey(WebPreferencesKey::modelElementEnabledKey());
}

void WebPreferences::setModelDocumentEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::modelDocumentEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::modelDocumentEnabledKey(), value, true);
}

bool WebPreferences::modelDocumentEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::modelDocumentEnabledKey());
}

void WebPreferences::deleteModelDocumentEnabled()
{
    deleteKey(WebPreferencesKey::modelDocumentEnabledKey());
}

void WebPreferences::setInteractiveFormValidationEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::interactiveFormValidationEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::interactiveFormValidationEnabledKey(), value, false);
}

bool WebPreferences::interactiveFormValidationEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::interactiveFormValidationEnabledKey());
}

void WebPreferences::deleteInteractiveFormValidationEnabled()
{
    deleteKey(WebPreferencesKey::interactiveFormValidationEnabledKey());
}

void WebPreferences::setInertAttributeEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::inertAttributeEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::inertAttributeEnabledKey(), value, false);
}

bool WebPreferences::inertAttributeEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::inertAttributeEnabledKey());
}

void WebPreferences::deleteInertAttributeEnabled()
{
    deleteKey(WebPreferencesKey::inertAttributeEnabledKey());
}

void WebPreferences::setPopoverAttributeEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::popoverAttributeEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::popoverAttributeEnabledKey(), value, false);
}

bool WebPreferences::popoverAttributeEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::popoverAttributeEnabledKey());
}

void WebPreferences::deletePopoverAttributeEnabled()
{
    deleteKey(WebPreferencesKey::popoverAttributeEnabledKey());
}

void WebPreferences::setHiddenPageDOMTimerThrottlingAutoIncreases(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::hiddenPageDOMTimerThrottlingAutoIncreasesKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::hiddenPageDOMTimerThrottlingAutoIncreasesKey(), value, false);
}

bool WebPreferences::hiddenPageDOMTimerThrottlingAutoIncreases() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::hiddenPageDOMTimerThrottlingAutoIncreasesKey());
}

void WebPreferences::deleteHiddenPageDOMTimerThrottlingAutoIncreases()
{
    deleteKey(WebPreferencesKey::hiddenPageDOMTimerThrottlingAutoIncreasesKey());
}

void WebPreferences::setHiddenPageDOMTimerThrottlingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::hiddenPageDOMTimerThrottlingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::hiddenPageDOMTimerThrottlingEnabledKey(), value, false);
}

bool WebPreferences::hiddenPageDOMTimerThrottlingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::hiddenPageDOMTimerThrottlingEnabledKey());
}

void WebPreferences::deleteHiddenPageDOMTimerThrottlingEnabled()
{
    deleteKey(WebPreferencesKey::hiddenPageDOMTimerThrottlingEnabledKey());
}

void WebPreferences::setHighlightAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::highlightAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::highlightAPIEnabledKey(), value, true);
}

bool WebPreferences::highlightAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::highlightAPIEnabledKey());
}

void WebPreferences::deleteHighlightAPIEnabled()
{
    deleteKey(WebPreferencesKey::highlightAPIEnabledKey());
}

void WebPreferences::setHyperlinkAuditingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::hyperlinkAuditingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::hyperlinkAuditingEnabledKey(), value, false);
}

bool WebPreferences::hyperlinkAuditingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::hyperlinkAuditingEnabledKey());
}

void WebPreferences::deleteHyperlinkAuditingEnabled()
{
    deleteKey(WebPreferencesKey::hyperlinkAuditingEnabledKey());
}

void WebPreferences::setBlockIOKitInWebContentSandbox(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::blockIOKitInWebContentSandboxKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::blockIOKitInWebContentSandboxKey(), value, true);
}

bool WebPreferences::blockIOKitInWebContentSandbox() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::blockIOKitInWebContentSandboxKey());
}

void WebPreferences::deleteBlockIOKitInWebContentSandbox()
{
    deleteKey(WebPreferencesKey::blockIOKitInWebContentSandboxKey());
}

void WebPreferences::setIPCTestingAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::ipcTestingAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::ipcTestingAPIEnabledKey(), value, true);
}

bool WebPreferences::ipcTestingAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::ipcTestingAPIEnabledKey());
}

void WebPreferences::deleteIPCTestingAPIEnabled()
{
    deleteKey(WebPreferencesKey::ipcTestingAPIEnabledKey());
}

void WebPreferences::setItpDebugModeEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::itpDebugModeEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::itpDebugModeEnabledKey(), value, false);
}

bool WebPreferences::itpDebugModeEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::itpDebugModeEnabledKey());
}

void WebPreferences::deleteItpDebugModeEnabled()
{
    deleteKey(WebPreferencesKey::itpDebugModeEnabledKey());
}

void WebPreferences::setTextAutosizingUsesIdempotentMode(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::textAutosizingUsesIdempotentModeKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::textAutosizingUsesIdempotentModeKey(), value, false);
}

bool WebPreferences::textAutosizingUsesIdempotentMode() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::textAutosizingUsesIdempotentModeKey());
}

void WebPreferences::deleteTextAutosizingUsesIdempotentMode()
{
    deleteKey(WebPreferencesKey::textAutosizingUsesIdempotentModeKey());
}

void WebPreferences::setImageAnalysisDuringFindInPageEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::imageAnalysisDuringFindInPageEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::imageAnalysisDuringFindInPageEnabledKey(), value, true);
}

bool WebPreferences::imageAnalysisDuringFindInPageEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::imageAnalysisDuringFindInPageEnabledKey());
}

void WebPreferences::deleteImageAnalysisDuringFindInPageEnabled()
{
    deleteKey(WebPreferencesKey::imageAnalysisDuringFindInPageEnabledKey());
}

void WebPreferences::setImageAnimationControlEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::imageAnimationControlEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::imageAnimationControlEnabledKey(), value, false);
}

bool WebPreferences::imageAnimationControlEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::imageAnimationControlEnabledKey());
}

void WebPreferences::deleteImageAnimationControlEnabled()
{
    deleteKey(WebPreferencesKey::imageAnimationControlEnabledKey());
}

void WebPreferences::setImageControlsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::imageControlsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::imageControlsEnabledKey(), value, true);
}

bool WebPreferences::imageControlsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::imageControlsEnabledKey());
}

void WebPreferences::deleteImageControlsEnabled()
{
    deleteKey(WebPreferencesKey::imageControlsEnabledKey());
}

void WebPreferences::setImperativeSlotAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::imperativeSlotAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::imperativeSlotAPIEnabledKey(), value, false);
}

bool WebPreferences::imperativeSlotAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::imperativeSlotAPIEnabledKey());
}

void WebPreferences::deleteImperativeSlotAPIEnabled()
{
    deleteKey(WebPreferencesKey::imperativeSlotAPIEnabledKey());
}

void WebPreferences::setIndexedDBAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::indexedDBAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::indexedDBAPIEnabledKey(), value, false);
}

bool WebPreferences::indexedDBAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::indexedDBAPIEnabledKey());
}

void WebPreferences::deleteIndexedDBAPIEnabled()
{
    deleteKey(WebPreferencesKey::indexedDBAPIEnabledKey());
}

void WebPreferences::setInlinePredictionsInAllEditableElementsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::inlinePredictionsInAllEditableElementsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::inlinePredictionsInAllEditableElementsEnabledKey(), value, true);
}

bool WebPreferences::inlinePredictionsInAllEditableElementsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::inlinePredictionsInAllEditableElementsEnabledKey());
}

void WebPreferences::deleteInlinePredictionsInAllEditableElementsEnabled()
{
    deleteKey(WebPreferencesKey::inlinePredictionsInAllEditableElementsEnabledKey());
}

void WebPreferences::setInteractionRegionsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::interactionRegionsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::interactionRegionsEnabledKey(), value, true);
}

bool WebPreferences::interactionRegionsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::interactionRegionsEnabledKey());
}

void WebPreferences::deleteInteractionRegionsEnabled()
{
    deleteKey(WebPreferencesKey::interactionRegionsEnabledKey());
}

void WebPreferences::setIntersectionObserverEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::intersectionObserverEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::intersectionObserverEnabledKey(), value, false);
}

bool WebPreferences::intersectionObserverEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::intersectionObserverEnabledKey());
}

void WebPreferences::deleteIntersectionObserverEnabled()
{
    deleteKey(WebPreferencesKey::intersectionObserverEnabledKey());
}

void WebPreferences::setIsLoggedInAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::isLoggedInAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::isLoggedInAPIEnabledKey(), value, true);
}

bool WebPreferences::isLoggedInAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::isLoggedInAPIEnabledKey());
}

void WebPreferences::deleteIsLoggedInAPIEnabled()
{
    deleteKey(WebPreferencesKey::isLoggedInAPIEnabledKey());
}

void WebPreferences::setIsAccessibilityIsolatedTreeEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::isAccessibilityIsolatedTreeEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::isAccessibilityIsolatedTreeEnabledKey(), value, false);
}

bool WebPreferences::isAccessibilityIsolatedTreeEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::isAccessibilityIsolatedTreeEnabledKey());
}

void WebPreferences::deleteIsAccessibilityIsolatedTreeEnabled()
{
    deleteKey(WebPreferencesKey::isAccessibilityIsolatedTreeEnabledKey());
}

void WebPreferences::setJavaScriptEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::javaScriptEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::javaScriptEnabledKey(), value, false);
}

bool WebPreferences::javaScriptEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::javaScriptEnabledKey());
}

void WebPreferences::deleteJavaScriptEnabled()
{
    deleteKey(WebPreferencesKey::javaScriptEnabledKey());
}

void WebPreferences::setLayerBasedSVGEngineEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::layerBasedSVGEngineEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::layerBasedSVGEngineEnabledKey(), value, true);
}

bool WebPreferences::layerBasedSVGEngineEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::layerBasedSVGEngineEnabledKey());
}

void WebPreferences::deleteLayerBasedSVGEngineEnabled()
{
    deleteKey(WebPreferencesKey::layerBasedSVGEngineEnabledKey());
}

void WebPreferences::setLazyIframeLoadingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::lazyIframeLoadingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::lazyIframeLoadingEnabledKey(), value, false);
}

bool WebPreferences::lazyIframeLoadingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::lazyIframeLoadingEnabledKey());
}

void WebPreferences::deleteLazyIframeLoadingEnabled()
{
    deleteKey(WebPreferencesKey::lazyIframeLoadingEnabledKey());
}

void WebPreferences::setLazyImageLoadingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::lazyImageLoadingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::lazyImageLoadingEnabledKey(), value, false);
}

bool WebPreferences::lazyImageLoadingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::lazyImageLoadingEnabledKey());
}

void WebPreferences::deleteLazyImageLoadingEnabled()
{
    deleteKey(WebPreferencesKey::lazyImageLoadingEnabledKey());
}

void WebPreferences::setLegacyOverflowScrollingTouchEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::legacyOverflowScrollingTouchEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::legacyOverflowScrollingTouchEnabledKey(), value, true);
}

bool WebPreferences::legacyOverflowScrollingTouchEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::legacyOverflowScrollingTouchEnabledKey());
}

void WebPreferences::deleteLegacyOverflowScrollingTouchEnabled()
{
    deleteKey(WebPreferencesKey::legacyOverflowScrollingTouchEnabledKey());
}

void WebPreferences::setLegacyLineLayoutVisualCoverageEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::legacyLineLayoutVisualCoverageEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::legacyLineLayoutVisualCoverageEnabledKey(), value, true);
}

bool WebPreferences::legacyLineLayoutVisualCoverageEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::legacyLineLayoutVisualCoverageEnabledKey());
}

void WebPreferences::deleteLegacyLineLayoutVisualCoverageEnabled()
{
    deleteKey(WebPreferencesKey::legacyLineLayoutVisualCoverageEnabledKey());
}

void WebPreferences::setShowModalDialogEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::showModalDialogEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::showModalDialogEnabledKey(), value, false);
}

bool WebPreferences::showModalDialogEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::showModalDialogEnabledKey());
}

void WebPreferences::deleteShowModalDialogEnabled()
{
    deleteKey(WebPreferencesKey::showModalDialogEnabledKey());
}

void WebPreferences::setMediaCaptureRequiresSecureConnection(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mediaCaptureRequiresSecureConnectionKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mediaCaptureRequiresSecureConnectionKey(), value, true);
}

bool WebPreferences::mediaCaptureRequiresSecureConnection() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mediaCaptureRequiresSecureConnectionKey());
}

void WebPreferences::deleteMediaCaptureRequiresSecureConnection()
{
    deleteKey(WebPreferencesKey::mediaCaptureRequiresSecureConnectionKey());
}

void WebPreferences::setLinkSanitizerEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::linkSanitizerEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::linkSanitizerEnabledKey(), value, true);
}

bool WebPreferences::linkSanitizerEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::linkSanitizerEnabledKey());
}

void WebPreferences::deleteLinkSanitizerEnabled()
{
    deleteKey(WebPreferencesKey::linkSanitizerEnabledKey());
}

void WebPreferences::setLinkPreloadResponsiveImagesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::linkPreloadResponsiveImagesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::linkPreloadResponsiveImagesEnabledKey(), value, true);
}

bool WebPreferences::linkPreloadResponsiveImagesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::linkPreloadResponsiveImagesEnabledKey());
}

void WebPreferences::deleteLinkPreloadResponsiveImagesEnabled()
{
    deleteKey(WebPreferencesKey::linkPreloadResponsiveImagesEnabledKey());
}

void WebPreferences::setLinkModulePreloadEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::linkModulePreloadEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::linkModulePreloadEnabledKey(), value, false);
}

bool WebPreferences::linkModulePreloadEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::linkModulePreloadEnabledKey());
}

void WebPreferences::deleteLinkModulePreloadEnabled()
{
    deleteKey(WebPreferencesKey::linkModulePreloadEnabledKey());
}

void WebPreferences::setLinkPreconnectEarlyHintsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::linkPreconnectEarlyHintsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::linkPreconnectEarlyHintsEnabledKey(), value, false);
}

bool WebPreferences::linkPreconnectEarlyHintsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::linkPreconnectEarlyHintsEnabledKey());
}

void WebPreferences::deleteLinkPreconnectEarlyHintsEnabled()
{
    deleteKey(WebPreferencesKey::linkPreconnectEarlyHintsEnabledKey());
}

void WebPreferences::setLinkPrefetchEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::linkPrefetchEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::linkPrefetchEnabledKey(), value, true);
}

bool WebPreferences::linkPrefetchEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::linkPrefetchEnabledKey());
}

void WebPreferences::deleteLinkPrefetchEnabled()
{
    deleteKey(WebPreferencesKey::linkPrefetchEnabledKey());
}

void WebPreferences::setLiveRangeSelectionEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::liveRangeSelectionEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::liveRangeSelectionEnabledKey(), value, false);
}

bool WebPreferences::liveRangeSelectionEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::liveRangeSelectionEnabledKey());
}

void WebPreferences::deleteLiveRangeSelectionEnabled()
{
    deleteKey(WebPreferencesKey::liveRangeSelectionEnabledKey());
}

void WebPreferences::setLocalFileContentSniffingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::localFileContentSniffingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::localFileContentSniffingEnabledKey(), value, true);
}

bool WebPreferences::localFileContentSniffingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::localFileContentSniffingEnabledKey());
}

void WebPreferences::deleteLocalFileContentSniffingEnabled()
{
    deleteKey(WebPreferencesKey::localFileContentSniffingEnabledKey());
}

void WebPreferences::setLocalStorageEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::localStorageEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::localStorageEnabledKey(), value, false);
}

bool WebPreferences::localStorageEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::localStorageEnabledKey());
}

void WebPreferences::deleteLocalStorageEnabled()
{
    deleteKey(WebPreferencesKey::localStorageEnabledKey());
}

void WebPreferences::setLogsPageMessagesToSystemConsoleEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::logsPageMessagesToSystemConsoleEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::logsPageMessagesToSystemConsoleEnabledKey(), value, true);
}

bool WebPreferences::logsPageMessagesToSystemConsoleEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::logsPageMessagesToSystemConsoleEnabledKey());
}

void WebPreferences::deleteLogsPageMessagesToSystemConsoleEnabled()
{
    deleteKey(WebPreferencesKey::logsPageMessagesToSystemConsoleEnabledKey());
}

void WebPreferences::setMainContentUserGestureOverrideEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mainContentUserGestureOverrideEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mainContentUserGestureOverrideEnabledKey(), value, false);
}

bool WebPreferences::mainContentUserGestureOverrideEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mainContentUserGestureOverrideEnabledKey());
}

void WebPreferences::deleteMainContentUserGestureOverrideEnabled()
{
    deleteKey(WebPreferencesKey::mainContentUserGestureOverrideEnabledKey());
}

void WebPreferences::setManagedMediaSourceEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::managedMediaSourceEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::managedMediaSourceEnabledKey(), value, false);
}

bool WebPreferences::managedMediaSourceEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::managedMediaSourceEnabledKey());
}

void WebPreferences::deleteManagedMediaSourceEnabled()
{
    deleteKey(WebPreferencesKey::managedMediaSourceEnabledKey());
}

void WebPreferences::setManagedMediaSourceNeedsAirPlay(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::managedMediaSourceNeedsAirPlayKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::managedMediaSourceNeedsAirPlayKey(), value, false);
}

bool WebPreferences::managedMediaSourceNeedsAirPlay() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::managedMediaSourceNeedsAirPlayKey());
}

void WebPreferences::deleteManagedMediaSourceNeedsAirPlay()
{
    deleteKey(WebPreferencesKey::managedMediaSourceNeedsAirPlayKey());
}

void WebPreferences::setMaskWebGLStringsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::maskWebGLStringsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::maskWebGLStringsEnabledKey(), value, false);
}

bool WebPreferences::maskWebGLStringsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::maskWebGLStringsEnabledKey());
}

void WebPreferences::deleteMaskWebGLStringsEnabled()
{
    deleteKey(WebPreferencesKey::maskWebGLStringsEnabledKey());
}

void WebPreferences::setCoreMathMLEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::coreMathMLEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::coreMathMLEnabledKey(), value, true);
}

bool WebPreferences::coreMathMLEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::coreMathMLEnabledKey());
}

void WebPreferences::deleteCoreMathMLEnabled()
{
    deleteKey(WebPreferencesKey::coreMathMLEnabledKey());
}

void WebPreferences::setMediaCapabilitiesExtensionsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mediaCapabilitiesExtensionsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mediaCapabilitiesExtensionsEnabledKey(), value, false);
}

bool WebPreferences::mediaCapabilitiesExtensionsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mediaCapabilitiesExtensionsEnabledKey());
}

void WebPreferences::deleteMediaCapabilitiesExtensionsEnabled()
{
    deleteKey(WebPreferencesKey::mediaCapabilitiesExtensionsEnabledKey());
}

void WebPreferences::setMediaSessionEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mediaSessionEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mediaSessionEnabledKey(), value, false);
}

bool WebPreferences::mediaSessionEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mediaSessionEnabledKey());
}

void WebPreferences::deleteMediaSessionEnabled()
{
    deleteKey(WebPreferencesKey::mediaSessionEnabledKey());
}

void WebPreferences::setMediaSourceEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mediaSourceEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mediaSourceEnabledKey(), value, false);
}

bool WebPreferences::mediaSourceEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mediaSourceEnabledKey());
}

void WebPreferences::deleteMediaSourceEnabled()
{
    deleteKey(WebPreferencesKey::mediaSourceEnabledKey());
}

void WebPreferences::setMediaDevicesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mediaDevicesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mediaDevicesEnabledKey(), value, false);
}

bool WebPreferences::mediaDevicesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mediaDevicesEnabledKey());
}

void WebPreferences::deleteMediaDevicesEnabled()
{
    deleteKey(WebPreferencesKey::mediaDevicesEnabledKey());
}

void WebPreferences::setMediaRecorderEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mediaRecorderEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mediaRecorderEnabledKey(), value, false);
}

bool WebPreferences::mediaRecorderEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mediaRecorderEnabledKey());
}

void WebPreferences::deleteMediaRecorderEnabled()
{
    deleteKey(WebPreferencesKey::mediaRecorderEnabledKey());
}

void WebPreferences::setMomentumScrollingAnimatorEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::momentumScrollingAnimatorEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::momentumScrollingAnimatorEnabledKey(), value, true);
}

bool WebPreferences::momentumScrollingAnimatorEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::momentumScrollingAnimatorEnabledKey());
}

void WebPreferences::deleteMomentumScrollingAnimatorEnabled()
{
    deleteKey(WebPreferencesKey::momentumScrollingAnimatorEnabledKey());
}

void WebPreferences::setInputTypeMonthEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::inputTypeMonthEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::inputTypeMonthEnabledKey(), value, false);
}

bool WebPreferences::inputTypeMonthEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::inputTypeMonthEnabledKey());
}

void WebPreferences::deleteInputTypeMonthEnabled()
{
    deleteKey(WebPreferencesKey::inputTypeMonthEnabledKey());
}

void WebPreferences::setMouseEventsSimulationEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::mouseEventsSimulationEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::mouseEventsSimulationEnabledKey(), value, true);
}

bool WebPreferences::mouseEventsSimulationEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::mouseEventsSimulationEnabledKey());
}

void WebPreferences::deleteMouseEventsSimulationEnabled()
{
    deleteKey(WebPreferencesKey::mouseEventsSimulationEnabledKey());
}

void WebPreferences::setMuteCameraOnMicrophoneInterruptionEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::muteCameraOnMicrophoneInterruptionEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::muteCameraOnMicrophoneInterruptionEnabledKey(), value, true);
}

bool WebPreferences::muteCameraOnMicrophoneInterruptionEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::muteCameraOnMicrophoneInterruptionEnabledKey());
}

void WebPreferences::deleteMuteCameraOnMicrophoneInterruptionEnabled()
{
    deleteKey(WebPreferencesKey::muteCameraOnMicrophoneInterruptionEnabledKey());
}

void WebPreferences::setNeedsInAppBrowserPrivacyQuirks(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::needsInAppBrowserPrivacyQuirksKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::needsInAppBrowserPrivacyQuirksKey(), value, true);
}

bool WebPreferences::needsInAppBrowserPrivacyQuirks() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::needsInAppBrowserPrivacyQuirksKey());
}

void WebPreferences::deleteNeedsInAppBrowserPrivacyQuirks()
{
    deleteKey(WebPreferencesKey::needsInAppBrowserPrivacyQuirksKey());
}

void WebPreferences::setNeedsSiteSpecificQuirks(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::needsSiteSpecificQuirksKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::needsSiteSpecificQuirksKey(), value, false);
}

bool WebPreferences::needsSiteSpecificQuirks() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::needsSiteSpecificQuirksKey());
}

void WebPreferences::deleteNeedsSiteSpecificQuirks()
{
    deleteKey(WebPreferencesKey::needsSiteSpecificQuirksKey());
}

void WebPreferences::setNeedsStorageAccessFromFileURLsQuirk(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::needsStorageAccessFromFileURLsQuirkKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::needsStorageAccessFromFileURLsQuirkKey(), value, false);
}

bool WebPreferences::needsStorageAccessFromFileURLsQuirk() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::needsStorageAccessFromFileURLsQuirkKey());
}

void WebPreferences::deleteNeedsStorageAccessFromFileURLsQuirk()
{
    deleteKey(WebPreferencesKey::needsStorageAccessFromFileURLsQuirkKey());
}

void WebPreferences::setFlexFormattingContextIntegrationEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::flexFormattingContextIntegrationEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::flexFormattingContextIntegrationEnabledKey(), value, true);
}

bool WebPreferences::flexFormattingContextIntegrationEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::flexFormattingContextIntegrationEnabledKey());
}

void WebPreferences::deleteFlexFormattingContextIntegrationEnabled()
{
    deleteKey(WebPreferencesKey::flexFormattingContextIntegrationEnabledKey());
}

void WebPreferences::setInlineFormattingContextIntegrationEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::inlineFormattingContextIntegrationEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::inlineFormattingContextIntegrationEnabledKey(), value, false);
}

bool WebPreferences::inlineFormattingContextIntegrationEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::inlineFormattingContextIntegrationEnabledKey());
}

void WebPreferences::deleteInlineFormattingContextIntegrationEnabled()
{
    deleteKey(WebPreferencesKey::inlineFormattingContextIntegrationEnabledKey());
}

void WebPreferences::setNotificationEventEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::notificationEventEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::notificationEventEnabledKey(), value, true);
}

bool WebPreferences::notificationEventEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::notificationEventEnabledKey());
}

void WebPreferences::deleteNotificationEventEnabled()
{
    deleteKey(WebPreferencesKey::notificationEventEnabledKey());
}

void WebPreferences::setNotificationsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::notificationsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::notificationsEnabledKey(), value, false);
}

bool WebPreferences::notificationsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::notificationsEnabledKey());
}

void WebPreferences::deleteNotificationsEnabled()
{
    deleteKey(WebPreferencesKey::notificationsEnabledKey());
}

void WebPreferences::setOffscreenCanvasInWorkersEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::offscreenCanvasInWorkersEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::offscreenCanvasInWorkersEnabledKey(), value, false);
}

bool WebPreferences::offscreenCanvasInWorkersEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::offscreenCanvasInWorkersEnabledKey());
}

void WebPreferences::deleteOffscreenCanvasInWorkersEnabled()
{
    deleteKey(WebPreferencesKey::offscreenCanvasInWorkersEnabledKey());
}

void WebPreferences::setOffscreenCanvasEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::offscreenCanvasEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::offscreenCanvasEnabledKey(), value, false);
}

bool WebPreferences::offscreenCanvasEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::offscreenCanvasEnabledKey());
}

void WebPreferences::deleteOffscreenCanvasEnabled()
{
    deleteKey(WebPreferencesKey::offscreenCanvasEnabledKey());
}

void WebPreferences::setOpusDecoderEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::opusDecoderEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::opusDecoderEnabledKey(), value, false);
}

bool WebPreferences::opusDecoderEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::opusDecoderEnabledKey());
}

void WebPreferences::deleteOpusDecoderEnabled()
{
    deleteKey(WebPreferencesKey::opusDecoderEnabledKey());
}

void WebPreferences::setPageVisibilityBasedProcessSuppressionEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::pageVisibilityBasedProcessSuppressionEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::pageVisibilityBasedProcessSuppressionEnabledKey(), value, true);
}

bool WebPreferences::pageVisibilityBasedProcessSuppressionEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::pageVisibilityBasedProcessSuppressionEnabledKey());
}

void WebPreferences::deletePageVisibilityBasedProcessSuppressionEnabled()
{
    deleteKey(WebPreferencesKey::pageVisibilityBasedProcessSuppressionEnabledKey());
}

void WebPreferences::setPaintTimingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::paintTimingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::paintTimingEnabledKey(), value, false);
}

bool WebPreferences::paintTimingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::paintTimingEnabledKey());
}

void WebPreferences::deletePaintTimingEnabled()
{
    deleteKey(WebPreferencesKey::paintTimingEnabledKey());
}

void WebPreferences::setBlobRegistryTopOriginPartitioningEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::blobRegistryTopOriginPartitioningEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::blobRegistryTopOriginPartitioningEnabledKey(), value, true);
}

bool WebPreferences::blobRegistryTopOriginPartitioningEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::blobRegistryTopOriginPartitioningEnabledKey());
}

void WebPreferences::deleteBlobRegistryTopOriginPartitioningEnabled()
{
    deleteKey(WebPreferencesKey::blobRegistryTopOriginPartitioningEnabledKey());
}

void WebPreferences::setPerformanceNavigationTimingAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::performanceNavigationTimingAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::performanceNavigationTimingAPIEnabledKey(), value, false);
}

bool WebPreferences::performanceNavigationTimingAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::performanceNavigationTimingAPIEnabledKey());
}

void WebPreferences::deletePerformanceNavigationTimingAPIEnabled()
{
    deleteKey(WebPreferencesKey::performanceNavigationTimingAPIEnabledKey());
}

void WebPreferences::setPerformanceResourceTimingSensitivePropertiesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::performanceResourceTimingSensitivePropertiesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::performanceResourceTimingSensitivePropertiesEnabledKey(), value, false);
}

bool WebPreferences::performanceResourceTimingSensitivePropertiesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::performanceResourceTimingSensitivePropertiesEnabledKey());
}

void WebPreferences::deletePerformanceResourceTimingSensitivePropertiesEnabled()
{
    deleteKey(WebPreferencesKey::performanceResourceTimingSensitivePropertiesEnabledKey());
}

void WebPreferences::setPermissionsAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::permissionsAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::permissionsAPIEnabledKey(), value, false);
}

bool WebPreferences::permissionsAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::permissionsAPIEnabledKey());
}

void WebPreferences::deletePermissionsAPIEnabled()
{
    deleteKey(WebPreferencesKey::permissionsAPIEnabledKey());
}

void WebPreferences::setPreferPageRenderingUpdatesNear60FPSEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::preferPageRenderingUpdatesNear60FPSEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::preferPageRenderingUpdatesNear60FPSEnabledKey(), value, false);
}

bool WebPreferences::preferPageRenderingUpdatesNear60FPSEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::preferPageRenderingUpdatesNear60FPSEnabledKey());
}

void WebPreferences::deletePreferPageRenderingUpdatesNear60FPSEnabled()
{
    deleteKey(WebPreferencesKey::preferPageRenderingUpdatesNear60FPSEnabledKey());
}

void WebPreferences::setPreferSandboxedMediaParsing(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::preferSandboxedMediaParsingKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::preferSandboxedMediaParsingKey(), value, true);
}

bool WebPreferences::preferSandboxedMediaParsing() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::preferSandboxedMediaParsingKey());
}

void WebPreferences::deletePreferSandboxedMediaParsing()
{
    deleteKey(WebPreferencesKey::preferSandboxedMediaParsingKey());
}

void WebPreferences::setPrivateClickMeasurementDebugModeEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::privateClickMeasurementDebugModeEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::privateClickMeasurementDebugModeEnabledKey(), value, false);
}

bool WebPreferences::privateClickMeasurementDebugModeEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::privateClickMeasurementDebugModeEnabledKey());
}

void WebPreferences::deletePrivateClickMeasurementDebugModeEnabled()
{
    deleteKey(WebPreferencesKey::privateClickMeasurementDebugModeEnabledKey());
}

void WebPreferences::setPrivateClickMeasurementFraudPreventionEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::privateClickMeasurementFraudPreventionEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::privateClickMeasurementFraudPreventionEnabledKey(), value, false);
}

bool WebPreferences::privateClickMeasurementFraudPreventionEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::privateClickMeasurementFraudPreventionEnabledKey());
}

void WebPreferences::deletePrivateClickMeasurementFraudPreventionEnabled()
{
    deleteKey(WebPreferencesKey::privateClickMeasurementFraudPreventionEnabledKey());
}

void WebPreferences::setPrivateClickMeasurementEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::privateClickMeasurementEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::privateClickMeasurementEnabledKey(), value, false);
}

bool WebPreferences::privateClickMeasurementEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::privateClickMeasurementEnabledKey());
}

void WebPreferences::deletePrivateClickMeasurementEnabled()
{
    deleteKey(WebPreferencesKey::privateClickMeasurementEnabledKey());
}

void WebPreferences::setPushAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::pushAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::pushAPIEnabledKey(), value, false);
}

bool WebPreferences::pushAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::pushAPIEnabledKey());
}

void WebPreferences::deletePushAPIEnabled()
{
    deleteKey(WebPreferencesKey::pushAPIEnabledKey());
}

void WebPreferences::setGoogleAntiFlickerOptimizationQuirkEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::googleAntiFlickerOptimizationQuirkEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::googleAntiFlickerOptimizationQuirkEnabledKey(), value, false);
}

bool WebPreferences::googleAntiFlickerOptimizationQuirkEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::googleAntiFlickerOptimizationQuirkEnabledKey());
}

void WebPreferences::deleteGoogleAntiFlickerOptimizationQuirkEnabled()
{
    deleteKey(WebPreferencesKey::googleAntiFlickerOptimizationQuirkEnabledKey());
}

void WebPreferences::setReadableByteStreamAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::readableByteStreamAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::readableByteStreamAPIEnabledKey(), value, true);
}

bool WebPreferences::readableByteStreamAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::readableByteStreamAPIEnabledKey());
}

void WebPreferences::deleteReadableByteStreamAPIEnabled()
{
    deleteKey(WebPreferencesKey::readableByteStreamAPIEnabledKey());
}

void WebPreferences::setReferrerPolicyAttributeEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::referrerPolicyAttributeEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::referrerPolicyAttributeEnabledKey(), value, false);
}

bool WebPreferences::referrerPolicyAttributeEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::referrerPolicyAttributeEnabledKey());
}

void WebPreferences::deleteReferrerPolicyAttributeEnabled()
{
    deleteKey(WebPreferencesKey::referrerPolicyAttributeEnabledKey());
}

void WebPreferences::setRemotePlaybackEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::remotePlaybackEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::remotePlaybackEnabledKey(), value, false);
}

bool WebPreferences::remotePlaybackEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::remotePlaybackEnabledKey());
}

void WebPreferences::deleteRemotePlaybackEnabled()
{
    deleteKey(WebPreferencesKey::remotePlaybackEnabledKey());
}

void WebPreferences::setRemoveBackgroundEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::removeBackgroundEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::removeBackgroundEnabledKey(), value, true);
}

bool WebPreferences::removeBackgroundEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::removeBackgroundEnabledKey());
}

void WebPreferences::deleteRemoveBackgroundEnabled()
{
    deleteKey(WebPreferencesKey::removeBackgroundEnabledKey());
}

void WebPreferences::setReportingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::reportingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::reportingEnabledKey(), value, false);
}

bool WebPreferences::reportingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::reportingEnabledKey());
}

void WebPreferences::deleteReportingEnabled()
{
    deleteKey(WebPreferencesKey::reportingEnabledKey());
}

void WebPreferences::setRequestVideoFrameCallbackEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::requestVideoFrameCallbackEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::requestVideoFrameCallbackEnabledKey(), value, false);
}

bool WebPreferences::requestVideoFrameCallbackEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::requestVideoFrameCallbackEnabledKey());
}

void WebPreferences::deleteRequestVideoFrameCallbackEnabled()
{
    deleteKey(WebPreferencesKey::requestVideoFrameCallbackEnabledKey());
}

void WebPreferences::setRequireUAGetDisplayMediaPrompt(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::requireUAGetDisplayMediaPromptKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::requireUAGetDisplayMediaPromptKey(), value, true);
}

bool WebPreferences::requireUAGetDisplayMediaPrompt() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::requireUAGetDisplayMediaPromptKey());
}

void WebPreferences::deleteRequireUAGetDisplayMediaPrompt()
{
    deleteKey(WebPreferencesKey::requireUAGetDisplayMediaPromptKey());
}

void WebPreferences::setSpeakerSelectionRequiresUserGesture(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::speakerSelectionRequiresUserGestureKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::speakerSelectionRequiresUserGestureKey(), value, true);
}

bool WebPreferences::speakerSelectionRequiresUserGesture() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::speakerSelectionRequiresUserGestureKey());
}

void WebPreferences::deleteSpeakerSelectionRequiresUserGesture()
{
    deleteKey(WebPreferencesKey::speakerSelectionRequiresUserGestureKey());
}

void WebPreferences::setFullscreenRequirementForScreenOrientationLockingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::fullscreenRequirementForScreenOrientationLockingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::fullscreenRequirementForScreenOrientationLockingEnabledKey(), value, false);
}

bool WebPreferences::fullscreenRequirementForScreenOrientationLockingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::fullscreenRequirementForScreenOrientationLockingEnabledKey());
}

void WebPreferences::deleteFullscreenRequirementForScreenOrientationLockingEnabled()
{
    deleteKey(WebPreferencesKey::fullscreenRequirementForScreenOrientationLockingEnabledKey());
}

void WebPreferences::setGetUserMediaRequiresFocus(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::getUserMediaRequiresFocusKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::getUserMediaRequiresFocusKey(), value, true);
}

bool WebPreferences::getUserMediaRequiresFocus() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::getUserMediaRequiresFocusKey());
}

void WebPreferences::deleteGetUserMediaRequiresFocus()
{
    deleteKey(WebPreferencesKey::getUserMediaRequiresFocusKey());
}

void WebPreferences::setResizeObserverEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::resizeObserverEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::resizeObserverEnabledKey(), value, false);
}

bool WebPreferences::resizeObserverEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::resizeObserverEnabledKey());
}

void WebPreferences::deleteResizeObserverEnabled()
{
    deleteKey(WebPreferencesKey::resizeObserverEnabledKey());
}

void WebPreferences::setResourceLoadSchedulingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::resourceLoadSchedulingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::resourceLoadSchedulingEnabledKey(), value, true);
}

bool WebPreferences::resourceLoadSchedulingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::resourceLoadSchedulingEnabledKey());
}

void WebPreferences::deleteResourceLoadSchedulingEnabled()
{
    deleteKey(WebPreferencesKey::resourceLoadSchedulingEnabledKey());
}

void WebPreferences::setResourceUsageOverlayVisible(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::resourceUsageOverlayVisibleKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::resourceUsageOverlayVisibleKey(), value, true);
}

bool WebPreferences::resourceUsageOverlayVisible() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::resourceUsageOverlayVisibleKey());
}

void WebPreferences::deleteResourceUsageOverlayVisible()
{
    deleteKey(WebPreferencesKey::resourceUsageOverlayVisibleKey());
}

void WebPreferences::setSKAttributionEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::sKAttributionEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::sKAttributionEnabledKey(), value, false);
}

bool WebPreferences::sKAttributionEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::sKAttributionEnabledKey());
}

void WebPreferences::deleteSKAttributionEnabled()
{
    deleteKey(WebPreferencesKey::sKAttributionEnabledKey());
}

void WebPreferences::setSafeBrowsingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::safeBrowsingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::safeBrowsingEnabledKey(), value, false);
}

bool WebPreferences::safeBrowsingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::safeBrowsingEnabledKey());
}

void WebPreferences::deleteSafeBrowsingEnabled()
{
    deleteKey(WebPreferencesKey::safeBrowsingEnabledKey());
}

void WebPreferences::setIsSameSiteStrictEnforcementEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::isSameSiteStrictEnforcementEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::isSameSiteStrictEnforcementEnabledKey(), value, true);
}

bool WebPreferences::isSameSiteStrictEnforcementEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::isSameSiteStrictEnforcementEnabledKey());
}

void WebPreferences::deleteIsSameSiteStrictEnforcementEnabled()
{
    deleteKey(WebPreferencesKey::isSameSiteStrictEnforcementEnabledKey());
}

void WebPreferences::setScreenOrientationLockingAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::screenOrientationLockingAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::screenOrientationLockingAPIEnabledKey(), value, true);
}

bool WebPreferences::screenOrientationLockingAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::screenOrientationLockingAPIEnabledKey());
}

void WebPreferences::deleteScreenOrientationLockingAPIEnabled()
{
    deleteKey(WebPreferencesKey::screenOrientationLockingAPIEnabledKey());
}

void WebPreferences::setScreenOrientationAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::screenOrientationAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::screenOrientationAPIEnabledKey(), value, false);
}

bool WebPreferences::screenOrientationAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::screenOrientationAPIEnabledKey());
}

void WebPreferences::deleteScreenOrientationAPIEnabled()
{
    deleteKey(WebPreferencesKey::screenOrientationAPIEnabledKey());
}

void WebPreferences::setScreenWakeLockAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::screenWakeLockAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::screenWakeLockAPIEnabledKey(), value, false);
}

bool WebPreferences::screenWakeLockAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::screenWakeLockAPIEnabledKey());
}

void WebPreferences::deleteScreenWakeLockAPIEnabled()
{
    deleteKey(WebPreferencesKey::screenWakeLockAPIEnabledKey());
}

void WebPreferences::setScreenCaptureEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::screenCaptureEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::screenCaptureEnabledKey(), value, false);
}

bool WebPreferences::screenCaptureEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::screenCaptureEnabledKey());
}

void WebPreferences::deleteScreenCaptureEnabled()
{
    deleteKey(WebPreferencesKey::screenCaptureEnabledKey());
}

void WebPreferences::setScrollingPerformanceTestingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::scrollingPerformanceTestingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::scrollingPerformanceTestingEnabledKey(), value, true);
}

bool WebPreferences::scrollingPerformanceTestingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::scrollingPerformanceTestingEnabledKey());
}

void WebPreferences::deleteScrollingPerformanceTestingEnabled()
{
    deleteKey(WebPreferencesKey::scrollingPerformanceTestingEnabledKey());
}

void WebPreferences::setScrollToTextFragmentIndicatorEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::scrollToTextFragmentIndicatorEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::scrollToTextFragmentIndicatorEnabledKey(), value, false);
}

bool WebPreferences::scrollToTextFragmentIndicatorEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::scrollToTextFragmentIndicatorEnabledKey());
}

void WebPreferences::deleteScrollToTextFragmentIndicatorEnabled()
{
    deleteKey(WebPreferencesKey::scrollToTextFragmentIndicatorEnabledKey());
}

void WebPreferences::setScrollToTextFragmentEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::scrollToTextFragmentEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::scrollToTextFragmentEnabledKey(), value, false);
}

bool WebPreferences::scrollToTextFragmentEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::scrollToTextFragmentEnabledKey());
}

void WebPreferences::deleteScrollToTextFragmentEnabled()
{
    deleteKey(WebPreferencesKey::scrollToTextFragmentEnabledKey());
}

void WebPreferences::setScrollAnimatorEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::scrollAnimatorEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::scrollAnimatorEnabledKey(), value, false);
}

bool WebPreferences::scrollAnimatorEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::scrollAnimatorEnabledKey());
}

void WebPreferences::deleteScrollAnimatorEnabled()
{
    deleteKey(WebPreferencesKey::scrollAnimatorEnabledKey());
}

void WebPreferences::setSearchInputIncrementalAttributeAndSearchEventEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::searchInputIncrementalAttributeAndSearchEventEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::searchInputIncrementalAttributeAndSearchEventEnabledKey(), value, false);
}

bool WebPreferences::searchInputIncrementalAttributeAndSearchEventEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::searchInputIncrementalAttributeAndSearchEventEnabledKey());
}

void WebPreferences::deleteSearchInputIncrementalAttributeAndSearchEventEnabled()
{
    deleteKey(WebPreferencesKey::searchInputIncrementalAttributeAndSearchEventEnabledKey());
}

void WebPreferences::setSecureContextChecksEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::secureContextChecksEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::secureContextChecksEnabledKey(), value, true);
}

bool WebPreferences::secureContextChecksEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::secureContextChecksEnabledKey());
}

void WebPreferences::deleteSecureContextChecksEnabled()
{
    deleteKey(WebPreferencesKey::secureContextChecksEnabledKey());
}

void WebPreferences::setSelectionAPIForShadowDOMEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::selectionAPIForShadowDOMEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::selectionAPIForShadowDOMEnabledKey(), value, false);
}

bool WebPreferences::selectionAPIForShadowDOMEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::selectionAPIForShadowDOMEnabledKey());
}

void WebPreferences::deleteSelectionAPIForShadowDOMEnabled()
{
    deleteKey(WebPreferencesKey::selectionAPIForShadowDOMEnabledKey());
}

void WebPreferences::setSelectionFlippingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::selectionFlippingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::selectionFlippingEnabledKey(), value, false);
}

bool WebPreferences::selectionFlippingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::selectionFlippingEnabledKey());
}

void WebPreferences::deleteSelectionFlippingEnabled()
{
    deleteKey(WebPreferencesKey::selectionFlippingEnabledKey());
}

void WebPreferences::setSendMouseEventsToDisabledFormControlsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::sendMouseEventsToDisabledFormControlsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::sendMouseEventsToDisabledFormControlsEnabledKey(), value, false);
}

bool WebPreferences::sendMouseEventsToDisabledFormControlsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::sendMouseEventsToDisabledFormControlsEnabledKey());
}

void WebPreferences::deleteSendMouseEventsToDisabledFormControlsEnabled()
{
    deleteKey(WebPreferencesKey::sendMouseEventsToDisabledFormControlsEnabledKey());
}

void WebPreferences::setServerTimingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::serverTimingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::serverTimingEnabledKey(), value, false);
}

bool WebPreferences::serverTimingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::serverTimingEnabledKey());
}

void WebPreferences::deleteServerTimingEnabled()
{
    deleteKey(WebPreferencesKey::serverTimingEnabledKey());
}

void WebPreferences::setServiceWorkerNavigationPreloadEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::serviceWorkerNavigationPreloadEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::serviceWorkerNavigationPreloadEnabledKey(), value, false);
}

bool WebPreferences::serviceWorkerNavigationPreloadEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::serviceWorkerNavigationPreloadEnabledKey());
}

void WebPreferences::deleteServiceWorkerNavigationPreloadEnabled()
{
    deleteKey(WebPreferencesKey::serviceWorkerNavigationPreloadEnabledKey());
}

void WebPreferences::setServiceWorkersEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::serviceWorkersEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::serviceWorkersEnabledKey(), value, false);
}

bool WebPreferences::serviceWorkersEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::serviceWorkersEnabledKey());
}

void WebPreferences::deleteServiceWorkersEnabled()
{
    deleteKey(WebPreferencesKey::serviceWorkersEnabledKey());
}

void WebPreferences::setShapeDetection(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::shapeDetectionKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::shapeDetectionKey(), value, true);
}

bool WebPreferences::shapeDetection() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::shapeDetectionKey());
}

void WebPreferences::deleteShapeDetection()
{
    deleteKey(WebPreferencesKey::shapeDetectionKey());
}

void WebPreferences::setSharedWorkerEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::sharedWorkerEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::sharedWorkerEnabledKey(), value, false);
}

bool WebPreferences::sharedWorkerEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::sharedWorkerEnabledKey());
}

void WebPreferences::deleteSharedWorkerEnabled()
{
    deleteKey(WebPreferencesKey::sharedWorkerEnabledKey());
}

void WebPreferences::setShowMediaStatsContextMenuItemEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::showMediaStatsContextMenuItemEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::showMediaStatsContextMenuItemEnabledKey(), value, false);
}

bool WebPreferences::showMediaStatsContextMenuItemEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::showMediaStatsContextMenuItemEnabledKey());
}

void WebPreferences::deleteShowMediaStatsContextMenuItemEnabled()
{
    deleteKey(WebPreferencesKey::showMediaStatsContextMenuItemEnabledKey());
}

void WebPreferences::setSiteIsolationEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::siteIsolationEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::siteIsolationEnabledKey(), value, true);
}

bool WebPreferences::siteIsolationEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::siteIsolationEnabledKey());
}

void WebPreferences::deleteSiteIsolationEnabled()
{
    deleteKey(WebPreferencesKey::siteIsolationEnabledKey());
}

void WebPreferences::setSpeechRecognitionEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::speechRecognitionEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::speechRecognitionEnabledKey(), value, false);
}

bool WebPreferences::speechRecognitionEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::speechRecognitionEnabledKey());
}

void WebPreferences::deleteSpeechRecognitionEnabled()
{
    deleteKey(WebPreferencesKey::speechRecognitionEnabledKey());
}

void WebPreferences::setSpeechSynthesisAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::speechSynthesisAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::speechSynthesisAPIEnabledKey(), value, false);
}

bool WebPreferences::speechSynthesisAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::speechSynthesisAPIEnabledKey());
}

void WebPreferences::deleteSpeechSynthesisAPIEnabled()
{
    deleteKey(WebPreferencesKey::speechSynthesisAPIEnabledKey());
}

void WebPreferences::setStorageAPIEstimateEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::storageAPIEstimateEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::storageAPIEstimateEnabledKey(), value, false);
}

bool WebPreferences::storageAPIEstimateEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::storageAPIEstimateEnabledKey());
}

void WebPreferences::deleteStorageAPIEstimateEnabled()
{
    deleteKey(WebPreferencesKey::storageAPIEstimateEnabledKey());
}

void WebPreferences::setStorageAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::storageAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::storageAPIEnabledKey(), value, false);
}

bool WebPreferences::storageAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::storageAPIEnabledKey());
}

void WebPreferences::deleteStorageAPIEnabled()
{
    deleteKey(WebPreferencesKey::storageAPIEnabledKey());
}

void WebPreferences::setStorageAccessAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::storageAccessAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::storageAccessAPIEnabledKey(), value, false);
}

bool WebPreferences::storageAccessAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::storageAccessAPIEnabledKey());
}

void WebPreferences::deleteStorageAccessAPIEnabled()
{
    deleteKey(WebPreferencesKey::storageAccessAPIEnabledKey());
}

void WebPreferences::setStorageBlockingPolicy(const uint32_t& value)
{
    if (!m_store.setUInt32ValueForKey(WebPreferencesKey::storageBlockingPolicyKey(), value))
        return;
    updateUInt32ValueForKey(WebPreferencesKey::storageBlockingPolicyKey(), value, false);
}

uint32_t WebPreferences::storageBlockingPolicy() const
{
    return m_store.getUInt32ValueForKey(WebPreferencesKey::storageBlockingPolicyKey());
}

void WebPreferences::deleteStorageBlockingPolicy()
{
    deleteKey(WebPreferencesKey::storageBlockingPolicyKey());
}

void WebPreferences::setProcessSwapOnCrossSiteNavigationEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::processSwapOnCrossSiteNavigationEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::processSwapOnCrossSiteNavigationEnabledKey(), value, false);
}

bool WebPreferences::processSwapOnCrossSiteNavigationEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::processSwapOnCrossSiteNavigationEnabledKey());
}

void WebPreferences::deleteProcessSwapOnCrossSiteNavigationEnabled()
{
    deleteKey(WebPreferencesKey::processSwapOnCrossSiteNavigationEnabledKey());
}

void WebPreferences::setProcessSwapOnCrossSiteWindowOpenEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::processSwapOnCrossSiteWindowOpenEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::processSwapOnCrossSiteWindowOpenEnabledKey(), value, true);
}

bool WebPreferences::processSwapOnCrossSiteWindowOpenEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::processSwapOnCrossSiteWindowOpenEnabledKey());
}

void WebPreferences::deleteProcessSwapOnCrossSiteWindowOpenEnabled()
{
    deleteKey(WebPreferencesKey::processSwapOnCrossSiteWindowOpenEnabledKey());
}

void WebPreferences::setSyntheticEditingCommandsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::syntheticEditingCommandsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::syntheticEditingCommandsEnabledKey(), value, false);
}

bool WebPreferences::syntheticEditingCommandsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::syntheticEditingCommandsEnabledKey());
}

void WebPreferences::deleteSyntheticEditingCommandsEnabled()
{
    deleteKey(WebPreferencesKey::syntheticEditingCommandsEnabledKey());
}

void WebPreferences::setShouldTakeNearSuspendedAssertions(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::shouldTakeNearSuspendedAssertionsKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::shouldTakeNearSuspendedAssertionsKey(), value, true);
}

bool WebPreferences::shouldTakeNearSuspendedAssertions() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::shouldTakeNearSuspendedAssertionsKey());
}

void WebPreferences::deleteShouldTakeNearSuspendedAssertions()
{
    deleteKey(WebPreferencesKey::shouldTakeNearSuspendedAssertionsKey());
}

void WebPreferences::setTextRecognitionInVideosEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::textRecognitionInVideosEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::textRecognitionInVideosEnabledKey(), value, true);
}

bool WebPreferences::textRecognitionInVideosEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::textRecognitionInVideosEnabledKey());
}

void WebPreferences::deleteTextRecognitionInVideosEnabled()
{
    deleteKey(WebPreferencesKey::textRecognitionInVideosEnabledKey());
}

void WebPreferences::setThreadedAnimationResolutionEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::threadedAnimationResolutionEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::threadedAnimationResolutionEnabledKey(), value, true);
}

bool WebPreferences::threadedAnimationResolutionEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::threadedAnimationResolutionEnabledKey());
}

void WebPreferences::deleteThreadedAnimationResolutionEnabled()
{
    deleteKey(WebPreferencesKey::threadedAnimationResolutionEnabledKey());
}

void WebPreferences::setTiledScrollingIndicatorVisible(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::tiledScrollingIndicatorVisibleKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::tiledScrollingIndicatorVisibleKey(), value, true);
}

bool WebPreferences::tiledScrollingIndicatorVisible() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::tiledScrollingIndicatorVisibleKey());
}

void WebPreferences::deleteTiledScrollingIndicatorVisible()
{
    deleteKey(WebPreferencesKey::tiledScrollingIndicatorVisibleKey());
}

void WebPreferences::setInputTypeTimeEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::inputTypeTimeEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::inputTypeTimeEnabledKey(), value, false);
}

bool WebPreferences::inputTypeTimeEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::inputTypeTimeEnabledKey());
}

void WebPreferences::deleteInputTypeTimeEnabled()
{
    deleteKey(WebPreferencesKey::inputTypeTimeEnabledKey());
}

void WebPreferences::setTrackConfigurationEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::trackConfigurationEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::trackConfigurationEnabledKey(), value, true);
}

bool WebPreferences::trackConfigurationEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::trackConfigurationEnabledKey());
}

void WebPreferences::deleteTrackConfigurationEnabled()
{
    deleteKey(WebPreferencesKey::trackConfigurationEnabledKey());
}

void WebPreferences::setTransformStreamAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::transformStreamAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::transformStreamAPIEnabledKey(), value, false);
}

bool WebPreferences::transformStreamAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::transformStreamAPIEnabledKey());
}

void WebPreferences::deleteTransformStreamAPIEnabled()
{
    deleteKey(WebPreferencesKey::transformStreamAPIEnabledKey());
}

void WebPreferences::setUndoManagerAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::undoManagerAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::undoManagerAPIEnabledKey(), value, true);
}

bool WebPreferences::undoManagerAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::undoManagerAPIEnabledKey());
}

void WebPreferences::deleteUndoManagerAPIEnabled()
{
    deleteKey(WebPreferencesKey::undoManagerAPIEnabledKey());
}

void WebPreferences::setUnprefixedFullscreenAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::unprefixedFullscreenAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::unprefixedFullscreenAPIEnabledKey(), value, false);
}

bool WebPreferences::unprefixedFullscreenAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::unprefixedFullscreenAPIEnabledKey());
}

void WebPreferences::deleteUnprefixedFullscreenAPIEnabled()
{
    deleteKey(WebPreferencesKey::unprefixedFullscreenAPIEnabledKey());
}

void WebPreferences::setUpgradeKnownHostsToHTTPSEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::upgradeKnownHostsToHTTPSEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::upgradeKnownHostsToHTTPSEnabledKey(), value, true);
}

bool WebPreferences::upgradeKnownHostsToHTTPSEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::upgradeKnownHostsToHTTPSEnabledKey());
}

void WebPreferences::deleteUpgradeKnownHostsToHTTPSEnabled()
{
    deleteKey(WebPreferencesKey::upgradeKnownHostsToHTTPSEnabledKey());
}

void WebPreferences::setUseARKitForModel(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::useARKitForModelKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::useARKitForModelKey(), value, true);
}

bool WebPreferences::useARKitForModel() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::useARKitForModelKey());
}

void WebPreferences::deleteUseARKitForModel()
{
    deleteKey(WebPreferencesKey::useARKitForModelKey());
}

void WebPreferences::setUseGeneralDirectoryForStorage(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::useGeneralDirectoryForStorageKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::useGeneralDirectoryForStorageKey(), value, true);
}

bool WebPreferences::useGeneralDirectoryForStorage() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::useGeneralDirectoryForStorageKey());
}

void WebPreferences::deleteUseGeneralDirectoryForStorage()
{
    deleteKey(WebPreferencesKey::useGeneralDirectoryForStorageKey());
}

void WebPreferences::setUseSCContentSharingPicker(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::useSCContentSharingPickerKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::useSCContentSharingPickerKey(), value, true);
}

bool WebPreferences::useSCContentSharingPicker() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::useSCContentSharingPickerKey());
}

void WebPreferences::deleteUseSCContentSharingPicker()
{
    deleteKey(WebPreferencesKey::useSCContentSharingPickerKey());
}

void WebPreferences::setUseSceneKitForModel(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::useSceneKitForModelKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::useSceneKitForModelKey(), value, true);
}

bool WebPreferences::useSceneKitForModel() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::useSceneKitForModelKey());
}

void WebPreferences::deleteUseSceneKitForModel()
{
    deleteKey(WebPreferencesKey::useSceneKitForModelKey());
}

void WebPreferences::setUseGiantTiles(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::useGiantTilesKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::useGiantTilesKey(), value, false);
}

bool WebPreferences::useGiantTiles() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::useGiantTilesKey());
}

void WebPreferences::deleteUseGiantTiles()
{
    deleteKey(WebPreferencesKey::useGiantTilesKey());
}

void WebPreferences::setUserActivationAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::userActivationAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::userActivationAPIEnabledKey(), value, false);
}

bool WebPreferences::userActivationAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::userActivationAPIEnabledKey());
}

void WebPreferences::deleteUserActivationAPIEnabled()
{
    deleteKey(WebPreferencesKey::userActivationAPIEnabledKey());
}

void WebPreferences::setUserGesturePromisePropagationEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::userGesturePromisePropagationEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::userGesturePromisePropagationEnabledKey(), value, true);
}

bool WebPreferences::userGesturePromisePropagationEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::userGesturePromisePropagationEnabledKey());
}

void WebPreferences::deleteUserGesturePromisePropagationEnabled()
{
    deleteKey(WebPreferencesKey::userGesturePromisePropagationEnabledKey());
}

void WebPreferences::setVP9SWDecoderEnabledOnBattery(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::vp9SWDecoderEnabledOnBatteryKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::vp9SWDecoderEnabledOnBatteryKey(), value, true);
}

bool WebPreferences::vp9SWDecoderEnabledOnBattery() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::vp9SWDecoderEnabledOnBatteryKey());
}

void WebPreferences::deleteVP9SWDecoderEnabledOnBattery()
{
    deleteKey(WebPreferencesKey::vp9SWDecoderEnabledOnBatteryKey());
}

void WebPreferences::setServiceWorkersUserGestureEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::serviceWorkersUserGestureEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::serviceWorkersUserGestureEnabledKey(), value, true);
}

bool WebPreferences::serviceWorkersUserGestureEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::serviceWorkersUserGestureEnabledKey());
}

void WebPreferences::deleteServiceWorkersUserGestureEnabled()
{
    deleteKey(WebPreferencesKey::serviceWorkersUserGestureEnabledKey());
}

void WebPreferences::setVerifyWindowOpenUserGestureFromUIProcess(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::verifyWindowOpenUserGestureFromUIProcessKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::verifyWindowOpenUserGestureFromUIProcessKey(), value, true);
}

bool WebPreferences::verifyWindowOpenUserGestureFromUIProcess() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::verifyWindowOpenUserGestureFromUIProcessKey());
}

void WebPreferences::deleteVerifyWindowOpenUserGestureFromUIProcess()
{
    deleteKey(WebPreferencesKey::verifyWindowOpenUserGestureFromUIProcessKey());
}

void WebPreferences::setVerticalFormControlsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::verticalFormControlsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::verticalFormControlsEnabledKey(), value, true);
}

bool WebPreferences::verticalFormControlsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::verticalFormControlsEnabledKey());
}

void WebPreferences::deleteVerticalFormControlsEnabled()
{
    deleteKey(WebPreferencesKey::verticalFormControlsEnabledKey());
}

void WebPreferences::setViewGestureDebuggingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::viewGestureDebuggingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::viewGestureDebuggingEnabledKey(), value, false);
}

bool WebPreferences::viewGestureDebuggingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::viewGestureDebuggingEnabledKey());
}

void WebPreferences::deleteViewGestureDebuggingEnabled()
{
    deleteKey(WebPreferencesKey::viewGestureDebuggingEnabledKey());
}

void WebPreferences::setVisualTranslationEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::visualTranslationEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::visualTranslationEnabledKey(), value, true);
}

bool WebPreferences::visualTranslationEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::visualTranslationEnabledKey());
}

void WebPreferences::deleteVisualTranslationEnabled()
{
    deleteKey(WebPreferencesKey::visualTranslationEnabledKey());
}

void WebPreferences::setVisualViewportAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::visualViewportAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::visualViewportAPIEnabledKey(), value, false);
}

bool WebPreferences::visualViewportAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::visualViewportAPIEnabledKey());
}

void WebPreferences::deleteVisualViewportAPIEnabled()
{
    deleteKey(WebPreferencesKey::visualViewportAPIEnabledKey());
}

void WebPreferences::setVorbisDecoderEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::vorbisDecoderEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::vorbisDecoderEnabledKey(), value, false);
}

bool WebPreferences::vorbisDecoderEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::vorbisDecoderEnabledKey());
}

void WebPreferences::deleteVorbisDecoderEnabled()
{
    deleteKey(WebPreferencesKey::vorbisDecoderEnabledKey());
}

void WebPreferences::setWebAPIStatisticsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webAPIStatisticsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webAPIStatisticsEnabledKey(), value, true);
}

bool WebPreferences::webAPIStatisticsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webAPIStatisticsEnabledKey());
}

void WebPreferences::deleteWebAPIStatisticsEnabled()
{
    deleteKey(WebPreferencesKey::webAPIStatisticsEnabledKey());
}

void WebPreferences::setWebAPIsInShadowRealmEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webAPIsInShadowRealmEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webAPIsInShadowRealmEnabledKey(), value, true);
}

bool WebPreferences::webAPIsInShadowRealmEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webAPIsInShadowRealmEnabledKey());
}

void WebPreferences::deleteWebAPIsInShadowRealmEnabled()
{
    deleteKey(WebPreferencesKey::webAPIsInShadowRealmEnabledKey());
}

void WebPreferences::setWebAnimationsCompositeOperationsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webAnimationsCompositeOperationsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webAnimationsCompositeOperationsEnabledKey(), value, false);
}

bool WebPreferences::webAnimationsCompositeOperationsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webAnimationsCompositeOperationsEnabledKey());
}

void WebPreferences::deleteWebAnimationsCompositeOperationsEnabled()
{
    deleteKey(WebPreferencesKey::webAnimationsCompositeOperationsEnabledKey());
}

void WebPreferences::setWebAnimationsCustomEffectsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webAnimationsCustomEffectsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webAnimationsCustomEffectsEnabledKey(), value, true);
}

bool WebPreferences::webAnimationsCustomEffectsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webAnimationsCustomEffectsEnabledKey());
}

void WebPreferences::deleteWebAnimationsCustomEffectsEnabled()
{
    deleteKey(WebPreferencesKey::webAnimationsCustomEffectsEnabledKey());
}

void WebPreferences::setWebAnimationsCustomFrameRateEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webAnimationsCustomFrameRateEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webAnimationsCustomFrameRateEnabledKey(), value, true);
}

bool WebPreferences::webAnimationsCustomFrameRateEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webAnimationsCustomFrameRateEnabledKey());
}

void WebPreferences::deleteWebAnimationsCustomFrameRateEnabled()
{
    deleteKey(WebPreferencesKey::webAnimationsCustomFrameRateEnabledKey());
}

void WebPreferences::setWebAnimationsIterationCompositeEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webAnimationsIterationCompositeEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webAnimationsIterationCompositeEnabledKey(), value, false);
}

bool WebPreferences::webAnimationsIterationCompositeEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webAnimationsIterationCompositeEnabledKey());
}

void WebPreferences::deleteWebAnimationsIterationCompositeEnabled()
{
    deleteKey(WebPreferencesKey::webAnimationsIterationCompositeEnabledKey());
}

void WebPreferences::setWebAnimationsMutableTimelinesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webAnimationsMutableTimelinesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webAnimationsMutableTimelinesEnabledKey(), value, false);
}

bool WebPreferences::webAnimationsMutableTimelinesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webAnimationsMutableTimelinesEnabledKey());
}

void WebPreferences::deleteWebAnimationsMutableTimelinesEnabled()
{
    deleteKey(WebPreferencesKey::webAnimationsMutableTimelinesEnabledKey());
}

void WebPreferences::setWebArchiveDebugModeEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webArchiveDebugModeEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webArchiveDebugModeEnabledKey(), value, false);
}

bool WebPreferences::webArchiveDebugModeEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webArchiveDebugModeEnabledKey());
}

void WebPreferences::deleteWebArchiveDebugModeEnabled()
{
    deleteKey(WebPreferencesKey::webArchiveDebugModeEnabledKey());
}

void WebPreferences::setWebArchiveTestingModeEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webArchiveTestingModeEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webArchiveTestingModeEnabledKey(), value, true);
}

bool WebPreferences::webArchiveTestingModeEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webArchiveTestingModeEnabledKey());
}

void WebPreferences::deleteWebArchiveTestingModeEnabled()
{
    deleteKey(WebPreferencesKey::webArchiveTestingModeEnabledKey());
}

void WebPreferences::setWebAuthenticationEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webAuthenticationEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webAuthenticationEnabledKey(), value, false);
}

bool WebPreferences::webAuthenticationEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webAuthenticationEnabledKey());
}

void WebPreferences::deleteWebAuthenticationEnabled()
{
    deleteKey(WebPreferencesKey::webAuthenticationEnabledKey());
}

void WebPreferences::setWebCryptoSafeCurvesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webCryptoSafeCurvesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webCryptoSafeCurvesEnabledKey(), value, false);
}

bool WebPreferences::webCryptoSafeCurvesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webCryptoSafeCurvesEnabledKey());
}

void WebPreferences::deleteWebCryptoSafeCurvesEnabled()
{
    deleteKey(WebPreferencesKey::webCryptoSafeCurvesEnabledKey());
}

void WebPreferences::setWebLocksAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webLocksAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webLocksAPIEnabledKey(), value, false);
}

bool WebPreferences::webLocksAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webLocksAPIEnabledKey());
}

void WebPreferences::deleteWebLocksAPIEnabled()
{
    deleteKey(WebPreferencesKey::webLocksAPIEnabledKey());
}

void WebPreferences::setWebShareFileAPIEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webShareFileAPIEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webShareFileAPIEnabledKey(), value, false);
}

bool WebPreferences::webShareFileAPIEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webShareFileAPIEnabledKey());
}

void WebPreferences::deleteWebShareFileAPIEnabled()
{
    deleteKey(WebPreferencesKey::webShareFileAPIEnabledKey());
}

void WebPreferences::setWebShareEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webShareEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webShareEnabledKey(), value, false);
}

bool WebPreferences::webShareEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webShareEnabledKey());
}

void WebPreferences::deleteWebShareEnabled()
{
    deleteKey(WebPreferencesKey::webShareEnabledKey());
}

void WebPreferences::setWebAssemblyESMIntegrationEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webAssemblyESMIntegrationEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webAssemblyESMIntegrationEnabledKey(), value, true);
}

bool WebPreferences::webAssemblyESMIntegrationEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webAssemblyESMIntegrationEnabledKey());
}

void WebPreferences::deleteWebAssemblyESMIntegrationEnabled()
{
    deleteKey(WebPreferencesKey::webAssemblyESMIntegrationEnabledKey());
}

void WebPreferences::setWebCodecsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webCodecsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webCodecsEnabledKey(), value, false);
}

bool WebPreferences::webCodecsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webCodecsEnabledKey());
}

void WebPreferences::deleteWebCodecsEnabled()
{
    deleteKey(WebPreferencesKey::webCodecsEnabledKey());
}

void WebPreferences::setWebCodecsAV1Enabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webCodecsAV1EnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webCodecsAV1EnabledKey(), value, false);
}

bool WebPreferences::webCodecsAV1Enabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webCodecsAV1EnabledKey());
}

void WebPreferences::deleteWebCodecsAV1Enabled()
{
    deleteKey(WebPreferencesKey::webCodecsAV1EnabledKey());
}

void WebPreferences::setWebCodecsHEVCEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webCodecsHEVCEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webCodecsHEVCEnabledKey(), value, false);
}

bool WebPreferences::webCodecsHEVCEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webCodecsHEVCEnabledKey());
}

void WebPreferences::deleteWebCodecsHEVCEnabled()
{
    deleteKey(WebPreferencesKey::webCodecsHEVCEnabledKey());
}

void WebPreferences::setWebGLDraftExtensionsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webGLDraftExtensionsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webGLDraftExtensionsEnabledKey(), value, true);
}

bool WebPreferences::webGLDraftExtensionsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webGLDraftExtensionsEnabledKey());
}

void WebPreferences::deleteWebGLDraftExtensionsEnabled()
{
    deleteKey(WebPreferencesKey::webGLDraftExtensionsEnabledKey());
}

void WebPreferences::setWebGLTimerQueriesEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webGLTimerQueriesEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webGLTimerQueriesEnabledKey(), value, false);
}

bool WebPreferences::webGLTimerQueriesEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webGLTimerQueriesEnabledKey());
}

void WebPreferences::deleteWebGLTimerQueriesEnabled()
{
    deleteKey(WebPreferencesKey::webGLTimerQueriesEnabledKey());
}

void WebPreferences::setWebGLUsingMetal(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webGLUsingMetalKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webGLUsingMetalKey(), value, true);
}

bool WebPreferences::webGLUsingMetal() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webGLUsingMetalKey());
}

void WebPreferences::deleteWebGLUsingMetal()
{
    deleteKey(WebPreferencesKey::webGLUsingMetalKey());
}

void WebPreferences::setWebGLEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webGLEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webGLEnabledKey(), value, false);
}

bool WebPreferences::webGLEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webGLEnabledKey());
}

void WebPreferences::deleteWebGLEnabled()
{
    deleteKey(WebPreferencesKey::webGLEnabledKey());
}

void WebPreferences::setWebGPUEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webGPUEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webGPUEnabledKey(), value, true);
}

bool WebPreferences::webGPUEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webGPUEnabledKey());
}

void WebPreferences::deleteWebGPUEnabled()
{
    deleteKey(WebPreferencesKey::webGPUEnabledKey());
}

void WebPreferences::setWebInspectorEngineeringSettingsAllowed(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webInspectorEngineeringSettingsAllowedKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webInspectorEngineeringSettingsAllowedKey(), value, true);
}

bool WebPreferences::webInspectorEngineeringSettingsAllowed() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webInspectorEngineeringSettingsAllowedKey());
}

void WebPreferences::deleteWebInspectorEngineeringSettingsAllowed()
{
    deleteKey(WebPreferencesKey::webInspectorEngineeringSettingsAllowedKey());
}

void WebPreferences::setWebRTCAV1CodecEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webRTCAV1CodecEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webRTCAV1CodecEnabledKey(), value, false);
}

bool WebPreferences::webRTCAV1CodecEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webRTCAV1CodecEnabledKey());
}

void WebPreferences::deleteWebRTCAV1CodecEnabled()
{
    deleteKey(WebPreferencesKey::webRTCAV1CodecEnabledKey());
}

void WebPreferences::setWebRTCAudioLatencyAdaptationEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webRTCAudioLatencyAdaptationEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webRTCAudioLatencyAdaptationEnabledKey(), value, true);
}

bool WebPreferences::webRTCAudioLatencyAdaptationEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webRTCAudioLatencyAdaptationEnabledKey());
}

void WebPreferences::deleteWebRTCAudioLatencyAdaptationEnabled()
{
    deleteKey(WebPreferencesKey::webRTCAudioLatencyAdaptationEnabledKey());
}

void WebPreferences::setWebRTCDTMFEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webRTCDTMFEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webRTCDTMFEnabledKey(), value, true);
}

bool WebPreferences::webRTCDTMFEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webRTCDTMFEnabledKey());
}

void WebPreferences::deleteWebRTCDTMFEnabled()
{
    deleteKey(WebPreferencesKey::webRTCDTMFEnabledKey());
}

void WebPreferences::setWebRTCEncodedTransformEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webRTCEncodedTransformEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webRTCEncodedTransformEnabledKey(), value, false);
}

bool WebPreferences::webRTCEncodedTransformEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webRTCEncodedTransformEnabledKey());
}

void WebPreferences::deleteWebRTCEncodedTransformEnabled()
{
    deleteKey(WebPreferencesKey::webRTCEncodedTransformEnabledKey());
}

void WebPreferences::setWebRTCH264HardwareEncoderEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webRTCH264HardwareEncoderEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webRTCH264HardwareEncoderEnabledKey(), value, true);
}

bool WebPreferences::webRTCH264HardwareEncoderEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webRTCH264HardwareEncoderEnabledKey());
}

void WebPreferences::deleteWebRTCH264HardwareEncoderEnabled()
{
    deleteKey(WebPreferencesKey::webRTCH264HardwareEncoderEnabledKey());
}

void WebPreferences::setWebRTCH264LowLatencyEncoderEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webRTCH264LowLatencyEncoderEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webRTCH264LowLatencyEncoderEnabledKey(), value, true);
}

bool WebPreferences::webRTCH264LowLatencyEncoderEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webRTCH264LowLatencyEncoderEnabledKey());
}

void WebPreferences::deleteWebRTCH264LowLatencyEncoderEnabled()
{
    deleteKey(WebPreferencesKey::webRTCH264LowLatencyEncoderEnabledKey());
}

void WebPreferences::setWebRTCH264SimulcastEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webRTCH264SimulcastEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webRTCH264SimulcastEnabledKey(), value, true);
}

bool WebPreferences::webRTCH264SimulcastEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webRTCH264SimulcastEnabledKey());
}

void WebPreferences::deleteWebRTCH264SimulcastEnabled()
{
    deleteKey(WebPreferencesKey::webRTCH264SimulcastEnabledKey());
}

void WebPreferences::setWebRTCH265CodecEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webRTCH265CodecEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webRTCH265CodecEnabledKey(), value, false);
}

bool WebPreferences::webRTCH265CodecEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webRTCH265CodecEnabledKey());
}

void WebPreferences::deleteWebRTCH265CodecEnabled()
{
    deleteKey(WebPreferencesKey::webRTCH265CodecEnabledKey());
}

void WebPreferences::setWebRTCMediaPipelineAdditionalLoggingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webRTCMediaPipelineAdditionalLoggingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webRTCMediaPipelineAdditionalLoggingEnabledKey(), value, true);
}

bool WebPreferences::webRTCMediaPipelineAdditionalLoggingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webRTCMediaPipelineAdditionalLoggingEnabledKey());
}

void WebPreferences::deleteWebRTCMediaPipelineAdditionalLoggingEnabled()
{
    deleteKey(WebPreferencesKey::webRTCMediaPipelineAdditionalLoggingEnabledKey());
}

void WebPreferences::setPeerConnectionEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::peerConnectionEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::peerConnectionEnabledKey(), value, false);
}

bool WebPreferences::peerConnectionEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::peerConnectionEnabledKey());
}

void WebPreferences::deletePeerConnectionEnabled()
{
    deleteKey(WebPreferencesKey::peerConnectionEnabledKey());
}

void WebPreferences::setWebRTCPlatformTCPSocketsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webRTCPlatformTCPSocketsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webRTCPlatformTCPSocketsEnabledKey(), value, true);
}

bool WebPreferences::webRTCPlatformTCPSocketsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webRTCPlatformTCPSocketsEnabledKey());
}

void WebPreferences::deleteWebRTCPlatformTCPSocketsEnabled()
{
    deleteKey(WebPreferencesKey::webRTCPlatformTCPSocketsEnabledKey());
}

void WebPreferences::setWebRTCPlatformUDPSocketsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webRTCPlatformUDPSocketsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webRTCPlatformUDPSocketsEnabledKey(), value, true);
}

bool WebPreferences::webRTCPlatformUDPSocketsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webRTCPlatformUDPSocketsEnabledKey());
}

void WebPreferences::deleteWebRTCPlatformUDPSocketsEnabled()
{
    deleteKey(WebPreferencesKey::webRTCPlatformUDPSocketsEnabledKey());
}

void WebPreferences::setWebRTCRemoteVideoFrameEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webRTCRemoteVideoFrameEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webRTCRemoteVideoFrameEnabledKey(), value, true);
}

bool WebPreferences::webRTCRemoteVideoFrameEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webRTCRemoteVideoFrameEnabledKey());
}

void WebPreferences::deleteWebRTCRemoteVideoFrameEnabled()
{
    deleteKey(WebPreferencesKey::webRTCRemoteVideoFrameEnabledKey());
}

void WebPreferences::setWebRTCSFrameTransformEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webRTCSFrameTransformEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webRTCSFrameTransformEnabledKey(), value, true);
}

bool WebPreferences::webRTCSFrameTransformEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webRTCSFrameTransformEnabledKey());
}

void WebPreferences::deleteWebRTCSFrameTransformEnabled()
{
    deleteKey(WebPreferencesKey::webRTCSFrameTransformEnabledKey());
}

void WebPreferences::setWebRTCSocketsProxyingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webRTCSocketsProxyingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webRTCSocketsProxyingEnabledKey(), value, true);
}

bool WebPreferences::webRTCSocketsProxyingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webRTCSocketsProxyingEnabledKey());
}

void WebPreferences::deleteWebRTCSocketsProxyingEnabled()
{
    deleteKey(WebPreferencesKey::webRTCSocketsProxyingEnabledKey());
}

void WebPreferences::setWebRTCVP9Profile0CodecEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webRTCVP9Profile0CodecEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webRTCVP9Profile0CodecEnabledKey(), value, true);
}

bool WebPreferences::webRTCVP9Profile0CodecEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webRTCVP9Profile0CodecEnabledKey());
}

void WebPreferences::deleteWebRTCVP9Profile0CodecEnabled()
{
    deleteKey(WebPreferencesKey::webRTCVP9Profile0CodecEnabledKey());
}

void WebPreferences::setWebRTCVP9Profile2CodecEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webRTCVP9Profile2CodecEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webRTCVP9Profile2CodecEnabledKey(), value, false);
}

bool WebPreferences::webRTCVP9Profile2CodecEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webRTCVP9Profile2CodecEnabledKey());
}

void WebPreferences::deleteWebRTCVP9Profile2CodecEnabled()
{
    deleteKey(WebPreferencesKey::webRTCVP9Profile2CodecEnabledKey());
}

void WebPreferences::setWebXRAugmentedRealityModuleEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webXRAugmentedRealityModuleEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webXRAugmentedRealityModuleEnabledKey(), value, true);
}

bool WebPreferences::webXRAugmentedRealityModuleEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webXRAugmentedRealityModuleEnabledKey());
}

void WebPreferences::deleteWebXRAugmentedRealityModuleEnabled()
{
    deleteKey(WebPreferencesKey::webXRAugmentedRealityModuleEnabledKey());
}

void WebPreferences::setWebXREnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webXREnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webXREnabledKey(), value, true);
}

bool WebPreferences::webXREnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webXREnabledKey());
}

void WebPreferences::deleteWebXREnabled()
{
    deleteKey(WebPreferencesKey::webXREnabledKey());
}

void WebPreferences::setWebXRGamepadsModuleEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webXRGamepadsModuleEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webXRGamepadsModuleEnabledKey(), value, true);
}

bool WebPreferences::webXRGamepadsModuleEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webXRGamepadsModuleEnabledKey());
}

void WebPreferences::deleteWebXRGamepadsModuleEnabled()
{
    deleteKey(WebPreferencesKey::webXRGamepadsModuleEnabledKey());
}

void WebPreferences::setWebXRHandInputModuleEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::webXRHandInputModuleEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::webXRHandInputModuleEnabledKey(), value, true);
}

bool WebPreferences::webXRHandInputModuleEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::webXRHandInputModuleEnabledKey());
}

void WebPreferences::deleteWebXRHandInputModuleEnabled()
{
    deleteKey(WebPreferencesKey::webXRHandInputModuleEnabledKey());
}

void WebPreferences::setInputTypeWeekEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::inputTypeWeekEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::inputTypeWeekEnabledKey(), value, false);
}

bool WebPreferences::inputTypeWeekEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::inputTypeWeekEnabledKey());
}

void WebPreferences::deleteInputTypeWeekEnabled()
{
    deleteKey(WebPreferencesKey::inputTypeWeekEnabledKey());
}

void WebPreferences::setWheelEventGesturesBecomeNonBlocking(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::wheelEventGesturesBecomeNonBlockingKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::wheelEventGesturesBecomeNonBlockingKey(), value, false);
}

bool WebPreferences::wheelEventGesturesBecomeNonBlocking() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::wheelEventGesturesBecomeNonBlockingKey());
}

void WebPreferences::deleteWheelEventGesturesBecomeNonBlocking()
{
    deleteKey(WebPreferencesKey::wheelEventGesturesBecomeNonBlockingKey());
}

void WebPreferences::setPassiveWheelListenersAsDefaultOnDocument(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::passiveWheelListenersAsDefaultOnDocumentKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::passiveWheelListenersAsDefaultOnDocumentKey(), value, false);
}

bool WebPreferences::passiveWheelListenersAsDefaultOnDocument() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::passiveWheelListenersAsDefaultOnDocumentKey());
}

void WebPreferences::deletePassiveWheelListenersAsDefaultOnDocument()
{
    deleteKey(WebPreferencesKey::passiveWheelListenersAsDefaultOnDocumentKey());
}

void WebPreferences::setIsFirstPartyWebsiteDataRemovalLiveOnTestingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::isFirstPartyWebsiteDataRemovalLiveOnTestingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::isFirstPartyWebsiteDataRemovalLiveOnTestingEnabledKey(), value, false);
}

bool WebPreferences::isFirstPartyWebsiteDataRemovalLiveOnTestingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::isFirstPartyWebsiteDataRemovalLiveOnTestingEnabledKey());
}

void WebPreferences::deleteIsFirstPartyWebsiteDataRemovalLiveOnTestingEnabled()
{
    deleteKey(WebPreferencesKey::isFirstPartyWebsiteDataRemovalLiveOnTestingEnabledKey());
}

void WebPreferences::setIsFirstPartyWebsiteDataRemovalReproTestingEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::isFirstPartyWebsiteDataRemovalReproTestingEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::isFirstPartyWebsiteDataRemovalReproTestingEnabledKey(), value, false);
}

bool WebPreferences::isFirstPartyWebsiteDataRemovalReproTestingEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::isFirstPartyWebsiteDataRemovalReproTestingEnabledKey());
}

void WebPreferences::deleteIsFirstPartyWebsiteDataRemovalReproTestingEnabled()
{
    deleteKey(WebPreferencesKey::isFirstPartyWebsiteDataRemovalReproTestingEnabledKey());
}

void WebPreferences::setInputTypeDateTimeLocalEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::inputTypeDateTimeLocalEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::inputTypeDateTimeLocalEnabledKey(), value, false);
}

bool WebPreferences::inputTypeDateTimeLocalEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::inputTypeDateTimeLocalEnabledKey());
}

void WebPreferences::deleteInputTypeDateTimeLocalEnabled()
{
    deleteKey(WebPreferencesKey::inputTypeDateTimeLocalEnabledKey());
}

void WebPreferences::setHTTPEquivEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::httpEquivEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::httpEquivEnabledKey(), value, false);
}

bool WebPreferences::httpEquivEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::httpEquivEnabledKey());
}

void WebPreferences::deleteHTTPEquivEnabled()
{
    deleteKey(WebPreferencesKey::httpEquivEnabledKey());
}

void WebPreferences::setIOSFormControlRefreshEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::iOSFormControlRefreshEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::iOSFormControlRefreshEnabledKey(), value, true);
}

bool WebPreferences::iOSFormControlRefreshEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::iOSFormControlRefreshEnabledKey());
}

void WebPreferences::deleteIOSFormControlRefreshEnabled()
{
    deleteKey(WebPreferencesKey::iOSFormControlRefreshEnabledKey());
}

void WebPreferences::setLineHeightUnitsEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::lineHeightUnitsEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::lineHeightUnitsEnabledKey(), value, false);
}

bool WebPreferences::lineHeightUnitsEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::lineHeightUnitsEnabledKey());
}

void WebPreferences::deleteLineHeightUnitsEnabled()
{
    deleteKey(WebPreferencesKey::lineHeightUnitsEnabledKey());
}

void WebPreferences::setRequestIdleCallbackEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::requestIdleCallbackEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::requestIdleCallbackEnabledKey(), value, true);
}

bool WebPreferences::requestIdleCallbackEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::requestIdleCallbackEnabledKey());
}

void WebPreferences::deleteRequestIdleCallbackEnabled()
{
    deleteKey(WebPreferencesKey::requestIdleCallbackEnabledKey());
}

void WebPreferences::setCSSWordBreakAutoEnabled(const bool& value)
{
    if (!m_store.setBoolValueForKey(WebPreferencesKey::cssWordBreakAutoEnabledKey(), value))
        return;
    updateBoolValueForKey(WebPreferencesKey::cssWordBreakAutoEnabledKey(), value, true);
}

bool WebPreferences::cssWordBreakAutoEnabled() const
{
    return m_store.getBoolValueForKey(WebPreferencesKey::cssWordBreakAutoEnabledKey());
}

void WebPreferences::deleteCSSWordBreakAutoEnabled()
{
    deleteKey(WebPreferencesKey::cssWordBreakAutoEnabledKey());
}


}
