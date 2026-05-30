/*
 * Copyright (C) 2021-2023 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
#include "RemoteGraphicsContextGL.h"

#include "ArgumentCoders.h" // NOLINT
#if PLATFORM(COCOA)
#include "ArgumentCodersDarwin.h" // NOLINT
#endif
#include "ArrayReference.h" // NOLINT
#include "ArrayReferenceTuple.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#if ENABLE(VIDEO) && PLATFORM(COCOA) || PLATFORM(COCOA)
#include "IPCSemaphore.h" // NOLINT
#endif
#include "RemoteGraphicsContextGLMessages.h" // NOLINT
#if ENABLE(MEDIA_STREAM) || ENABLE(WEB_CODECS)
#include "RemoteVideoFrameProxy.h" // NOLINT
#endif
#include "SharedMemory.h" // NOLINT
#if ENABLE(VIDEO) && PLATFORM(COCOA)
#include "SharedVideoFrame.h" // NOLINT
#endif
#if USE(GRAPHICS_LAYER_WC)
#include "WCContentBufferIdentifier.h" // NOLINT
#endif
#include "WebCoreArgumentCoders.h" // NOLINT
#if USE(GBM)
#include <WebCore/DMABufObject.h> // NOLINT
#endif
#include <WebCore/DestinationColorSpace.h> // NOLINT
#include <WebCore/GraphicsContextGL.h> // NOLINT
#include <WebCore/GraphicsTypesGL.h> // NOLINT
#include <WebCore/IntRect.h> // NOLINT
#include <WebCore/IntSize.h> // NOLINT
#include <WebCore/PixelBuffer.h> // NOLINT
#include <WebCore/RenderingResourceIdentifier.h> // NOLINT
#include <optional> // NOLINT
#if PLATFORM(COCOA)
#include <wtf/MachSendRight.h> // NOLINT
#endif
#include <wtf/RefCounted.h> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteGraphicsContextGL::didReceiveStreamMessage(IPC::StreamServerConnection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Reshape::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Reshape>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::reshape);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::EnsureExtensionEnabled::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::EnsureExtensionEnabled>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::ensureExtensionEnabled);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::MarkContextChanged::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::MarkContextChanged>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::markContextChanged);
#if ENABLE(VIDEO) && PLATFORM(COCOA)
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::SetSharedVideoFrameSemaphore::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::SetSharedVideoFrameSemaphore>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::setSharedVideoFrameSemaphore);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::SetSharedVideoFrameMemory::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::SetSharedVideoFrameMemory>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::setSharedVideoFrameMemory);
#endif
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::SimulateEventForTesting::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::SimulateEventForTesting>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::simulateEventForTesting);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::MultiDrawArraysANGLE::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::MultiDrawArraysANGLE>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::multiDrawArraysANGLE);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::MultiDrawArraysInstancedANGLE::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::MultiDrawArraysInstancedANGLE>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::multiDrawArraysInstancedANGLE);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::MultiDrawElementsANGLE::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::MultiDrawElementsANGLE>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::multiDrawElementsANGLE);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::MultiDrawElementsInstancedANGLE::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::MultiDrawElementsInstancedANGLE>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::multiDrawElementsInstancedANGLE);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::MultiDrawArraysInstancedBaseInstanceANGLE::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::MultiDrawArraysInstancedBaseInstanceANGLE>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::multiDrawArraysInstancedBaseInstanceANGLE);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::MultiDrawElementsInstancedBaseVertexBaseInstanceANGLE::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::MultiDrawElementsInstancedBaseVertexBaseInstanceANGLE>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::multiDrawElementsInstancedBaseVertexBaseInstanceANGLE);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ActiveTexture::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::ActiveTexture>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::activeTexture);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::AttachShader::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::AttachShader>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::attachShader);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BindAttribLocation::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BindAttribLocation>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::bindAttribLocation);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BindBuffer::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BindBuffer>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::bindBuffer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BindFramebuffer::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BindFramebuffer>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::bindFramebuffer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BindRenderbuffer::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BindRenderbuffer>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::bindRenderbuffer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BindTexture::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BindTexture>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::bindTexture);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BlendColor::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BlendColor>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::blendColor);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BlendEquation::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BlendEquation>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::blendEquation);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BlendEquationSeparate::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BlendEquationSeparate>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::blendEquationSeparate);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BlendFunc::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BlendFunc>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::blendFunc);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BlendFuncSeparate::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BlendFuncSeparate>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::blendFuncSeparate);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Clear::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Clear>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::clear);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ClearColor::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::ClearColor>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::clearColor);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ClearDepth::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::ClearDepth>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::clearDepth);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ClearStencil::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::ClearStencil>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::clearStencil);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ColorMask::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::ColorMask>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::colorMask);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CompileShader::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::CompileShader>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::compileShader);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CopyTexImage2D::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::CopyTexImage2D>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::copyTexImage2D);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CopyTexSubImage2D::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::CopyTexSubImage2D>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::copyTexSubImage2D);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CullFace::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::CullFace>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::cullFace);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DeleteBuffer::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DeleteBuffer>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::deleteBuffer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DeleteFramebuffer::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DeleteFramebuffer>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::deleteFramebuffer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DeleteProgram::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DeleteProgram>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::deleteProgram);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DeleteRenderbuffer::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DeleteRenderbuffer>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::deleteRenderbuffer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DeleteShader::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DeleteShader>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::deleteShader);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DeleteTexture::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DeleteTexture>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::deleteTexture);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DepthFunc::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DepthFunc>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::depthFunc);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DepthMask::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DepthMask>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::depthMask);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DepthRange::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DepthRange>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::depthRange);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DestroyEGLImage::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DestroyEGLImage>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::destroyEGLImage);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DetachShader::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DetachShader>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::detachShader);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Disable::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Disable>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::disable);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DisableVertexAttribArray::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DisableVertexAttribArray>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::disableVertexAttribArray);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DrawArrays::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DrawArrays>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::drawArrays);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DrawElements::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DrawElements>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::drawElements);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Enable::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Enable>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::enable);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::EnableVertexAttribArray::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::EnableVertexAttribArray>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::enableVertexAttribArray);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Finish::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Finish>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::finish);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Flush::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Flush>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::flush);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::FramebufferRenderbuffer::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::FramebufferRenderbuffer>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::framebufferRenderbuffer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::FramebufferTexture2D::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::FramebufferTexture2D>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::framebufferTexture2D);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::FrontFace::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::FrontFace>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::frontFace);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GenerateMipmap::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::GenerateMipmap>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::generateMipmap);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Hint::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Hint>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::hint);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::LineWidth::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::LineWidth>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::lineWidth);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::LinkProgram::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::LinkProgram>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::linkProgram);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::PixelStorei::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::PixelStorei>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::pixelStorei);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::PolygonOffset::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::PolygonOffset>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::polygonOffset);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::RenderbufferStorage::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::RenderbufferStorage>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::renderbufferStorage);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::SampleCoverage::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::SampleCoverage>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::sampleCoverage);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Scissor::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Scissor>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::scissor);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ShaderSource::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::ShaderSource>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::shaderSource);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::StencilFunc::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::StencilFunc>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::stencilFunc);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::StencilFuncSeparate::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::StencilFuncSeparate>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::stencilFuncSeparate);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::StencilMask::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::StencilMask>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::stencilMask);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::StencilMaskSeparate::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::StencilMaskSeparate>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::stencilMaskSeparate);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::StencilOp::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::StencilOp>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::stencilOp);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::StencilOpSeparate::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::StencilOpSeparate>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::stencilOpSeparate);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::TexParameterf::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::TexParameterf>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::texParameterf);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::TexParameteri::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::TexParameteri>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::texParameteri);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform1f::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform1f>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform1f);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform1fv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform1fv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform1fv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform1i::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform1i>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform1i);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform1iv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform1iv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform1iv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform2f::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform2f>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform2f);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform2fv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform2fv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform2fv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform2i::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform2i>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform2i);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform2iv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform2iv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform2iv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform3f::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform3f>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform3f);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform3fv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform3fv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform3fv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform3i::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform3i>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform3i);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform3iv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform3iv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform3iv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform4f::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform4f>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform4f);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform4fv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform4fv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform4fv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform4i::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform4i>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform4i);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform4iv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform4iv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform4iv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::UniformMatrix2fv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::UniformMatrix2fv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniformMatrix2fv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::UniformMatrix3fv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::UniformMatrix3fv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniformMatrix3fv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::UniformMatrix4fv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::UniformMatrix4fv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniformMatrix4fv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::UseProgram::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::UseProgram>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::useProgram);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ValidateProgram::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::ValidateProgram>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::validateProgram);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::VertexAttrib1f::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::VertexAttrib1f>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::vertexAttrib1f);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::VertexAttrib1fv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::VertexAttrib1fv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::vertexAttrib1fv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::VertexAttrib2f::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::VertexAttrib2f>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::vertexAttrib2f);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::VertexAttrib2fv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::VertexAttrib2fv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::vertexAttrib2fv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::VertexAttrib3f::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::VertexAttrib3f>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::vertexAttrib3f);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::VertexAttrib3fv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::VertexAttrib3fv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::vertexAttrib3fv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::VertexAttrib4f::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::VertexAttrib4f>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::vertexAttrib4f);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::VertexAttrib4fv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::VertexAttrib4fv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::vertexAttrib4fv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::VertexAttribPointer::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::VertexAttribPointer>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::vertexAttribPointer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Viewport::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Viewport>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::viewport);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BufferData0::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BufferData0>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::bufferData0);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BufferData1::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BufferData1>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::bufferData1);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BufferSubData::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BufferSubData>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::bufferSubData);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ReadPixelsBufferObject::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::ReadPixelsBufferObject>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::readPixelsBufferObject);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::TexImage2D0::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::TexImage2D0>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::texImage2D0);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::TexImage2D1::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::TexImage2D1>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::texImage2D1);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::TexSubImage2D0::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::TexSubImage2D0>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::texSubImage2D0);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::TexSubImage2D1::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::TexSubImage2D1>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::texSubImage2D1);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CompressedTexImage2D0::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::CompressedTexImage2D0>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::compressedTexImage2D0);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CompressedTexImage2D1::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::CompressedTexImage2D1>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::compressedTexImage2D1);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CompressedTexSubImage2D0::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::CompressedTexSubImage2D0>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::compressedTexSubImage2D0);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CompressedTexSubImage2D1::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::CompressedTexSubImage2D1>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::compressedTexSubImage2D1);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DrawArraysInstanced::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DrawArraysInstanced>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::drawArraysInstanced);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DrawElementsInstanced::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DrawElementsInstanced>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::drawElementsInstanced);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::VertexAttribDivisor::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::VertexAttribDivisor>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::vertexAttribDivisor);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DeleteVertexArray::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DeleteVertexArray>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::deleteVertexArray);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BindVertexArray::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BindVertexArray>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::bindVertexArray);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CopyBufferSubData::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::CopyBufferSubData>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::copyBufferSubData);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BlitFramebuffer::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BlitFramebuffer>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::blitFramebuffer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::FramebufferTextureLayer::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::FramebufferTextureLayer>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::framebufferTextureLayer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::InvalidateFramebuffer::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::InvalidateFramebuffer>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::invalidateFramebuffer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::InvalidateSubFramebuffer::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::InvalidateSubFramebuffer>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::invalidateSubFramebuffer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ReadBuffer::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::ReadBuffer>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::readBuffer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::RenderbufferStorageMultisample::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::RenderbufferStorageMultisample>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::renderbufferStorageMultisample);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::TexStorage2D::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::TexStorage2D>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::texStorage2D);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::TexStorage3D::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::TexStorage3D>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::texStorage3D);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::TexImage3D0::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::TexImage3D0>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::texImage3D0);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::TexImage3D1::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::TexImage3D1>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::texImage3D1);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::TexSubImage3D0::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::TexSubImage3D0>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::texSubImage3D0);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::TexSubImage3D1::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::TexSubImage3D1>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::texSubImage3D1);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CopyTexSubImage3D::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::CopyTexSubImage3D>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::copyTexSubImage3D);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CompressedTexImage3D0::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::CompressedTexImage3D0>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::compressedTexImage3D0);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CompressedTexImage3D1::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::CompressedTexImage3D1>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::compressedTexImage3D1);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CompressedTexSubImage3D0::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::CompressedTexSubImage3D0>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::compressedTexSubImage3D0);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CompressedTexSubImage3D1::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::CompressedTexSubImage3D1>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::compressedTexSubImage3D1);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform1ui::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform1ui>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform1ui);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform2ui::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform2ui>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform2ui);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform3ui::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform3ui>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform3ui);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform4ui::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform4ui>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform4ui);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform1uiv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform1uiv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform1uiv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform2uiv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform2uiv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform2uiv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform3uiv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform3uiv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform3uiv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::Uniform4uiv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::Uniform4uiv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniform4uiv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::UniformMatrix2x3fv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::UniformMatrix2x3fv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniformMatrix2x3fv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::UniformMatrix3x2fv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::UniformMatrix3x2fv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniformMatrix3x2fv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::UniformMatrix2x4fv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::UniformMatrix2x4fv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniformMatrix2x4fv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::UniformMatrix4x2fv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::UniformMatrix4x2fv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniformMatrix4x2fv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::UniformMatrix3x4fv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::UniformMatrix3x4fv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniformMatrix3x4fv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::UniformMatrix4x3fv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::UniformMatrix4x3fv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniformMatrix4x3fv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::VertexAttribI4i::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::VertexAttribI4i>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::vertexAttribI4i);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::VertexAttribI4iv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::VertexAttribI4iv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::vertexAttribI4iv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::VertexAttribI4ui::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::VertexAttribI4ui>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::vertexAttribI4ui);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::VertexAttribI4uiv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::VertexAttribI4uiv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::vertexAttribI4uiv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::VertexAttribIPointer::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::VertexAttribIPointer>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::vertexAttribIPointer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DrawRangeElements::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DrawRangeElements>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::drawRangeElements);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DrawBuffers::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DrawBuffers>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::drawBuffers);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ClearBufferiv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::ClearBufferiv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::clearBufferiv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ClearBufferuiv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::ClearBufferuiv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::clearBufferuiv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ClearBufferfv::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::ClearBufferfv>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::clearBufferfv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ClearBufferfi::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::ClearBufferfi>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::clearBufferfi);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DeleteQuery::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DeleteQuery>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::deleteQuery);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BeginQuery::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BeginQuery>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::beginQuery);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::EndQuery::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::EndQuery>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::endQuery);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DeleteSampler::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DeleteSampler>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::deleteSampler);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BindSampler::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BindSampler>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::bindSampler);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::SamplerParameteri::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::SamplerParameteri>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::samplerParameteri);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::SamplerParameterf::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::SamplerParameterf>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::samplerParameterf);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DeleteSync::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DeleteSync>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::deleteSync);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::WaitSync::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::WaitSync>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::waitSync);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DeleteTransformFeedback::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DeleteTransformFeedback>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::deleteTransformFeedback);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BindTransformFeedback::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BindTransformFeedback>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::bindTransformFeedback);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BeginTransformFeedback::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BeginTransformFeedback>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::beginTransformFeedback);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::EndTransformFeedback::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::EndTransformFeedback>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::endTransformFeedback);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::TransformFeedbackVaryings::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::TransformFeedbackVaryings>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::transformFeedbackVaryings);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::PauseTransformFeedback::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::PauseTransformFeedback>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::pauseTransformFeedback);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ResumeTransformFeedback::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::ResumeTransformFeedback>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::resumeTransformFeedback);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BindBufferBase::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BindBufferBase>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::bindBufferBase);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BindBufferRange::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BindBufferRange>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::bindBufferRange);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::UniformBlockBinding::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::UniformBlockBinding>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::uniformBlockBinding);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DrawBuffersEXT::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DrawBuffersEXT>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::drawBuffersEXT);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DeleteQueryEXT::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DeleteQueryEXT>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::deleteQueryEXT);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BeginQueryEXT::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BeginQueryEXT>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::beginQueryEXT);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::EndQueryEXT::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::EndQueryEXT>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::endQueryEXT);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::QueryCounterEXT::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::QueryCounterEXT>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::queryCounterEXT);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::EnableiOES::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::EnableiOES>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::enableiOES);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DisableiOES::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DisableiOES>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::disableiOES);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BlendEquationiOES::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BlendEquationiOES>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::blendEquationiOES);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BlendEquationSeparateiOES::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BlendEquationSeparateiOES>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::blendEquationSeparateiOES);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BlendFunciOES::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BlendFunciOES>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::blendFunciOES);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BlendFuncSeparateiOES::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BlendFuncSeparateiOES>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::blendFuncSeparateiOES);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ColorMaskiOES::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::ColorMaskiOES>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::colorMaskiOES);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DrawArraysInstancedBaseInstanceANGLE::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DrawArraysInstancedBaseInstanceANGLE>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::drawArraysInstancedBaseInstanceANGLE);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DrawElementsInstancedBaseVertexBaseInstanceANGLE::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::DrawElementsInstancedBaseVertexBaseInstanceANGLE>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::drawElementsInstancedBaseVertexBaseInstanceANGLE);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ClipControlEXT::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::ClipControlEXT>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::clipControlEXT);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ProvokingVertexANGLE::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::ProvokingVertexANGLE>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::provokingVertexANGLE);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::PolygonModeANGLE::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::PolygonModeANGLE>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::polygonModeANGLE);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::PolygonOffsetClampEXT::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::PolygonOffsetClampEXT>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::polygonOffsetClampEXT);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::RenderbufferStorageMultisampleANGLE::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::RenderbufferStorageMultisampleANGLE>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::renderbufferStorageMultisampleANGLE);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::BlitFramebufferANGLE::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::BlitFramebufferANGLE>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::blitFramebufferANGLE);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::SetDrawingBufferColorSpace::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::SetDrawingBufferColorSpace>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::setDrawingBufferColorSpace);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ClientWaitEGLSyncWithFlush::name())
        return IPC::handleMessage<Messages::RemoteGraphicsContextGL::ClientWaitEGLSyncWithFlush>(connection.connection(), decoder, this, &RemoteGraphicsContextGL::clientWaitEGLSyncWithFlush);
#if PLATFORM(COCOA)
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::PrepareForDisplay::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::PrepareForDisplay>(connection, decoder, this, &RemoteGraphicsContextGL::prepareForDisplay);
#endif
#if USE(GRAPHICS_LAYER_WC)
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::PrepareForDisplay::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::PrepareForDisplay>(connection, decoder, this, &RemoteGraphicsContextGL::prepareForDisplay);
#endif
#if USE(GBM)
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::PrepareForDisplay::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::PrepareForDisplay>(connection, decoder, this, &RemoteGraphicsContextGL::prepareForDisplay);
#endif
#if !PLATFORM(COCOA) && !USE(GRAPHICS_LAYER_WC) && !USE(GBM)
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::PrepareForDisplay::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::PrepareForDisplay>(connection, decoder, this, &RemoteGraphicsContextGL::prepareForDisplay);
#endif
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetErrors::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetErrors>(connection, decoder, this, &RemoteGraphicsContextGL::getErrors);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::PaintRenderingResultsToCanvas::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::PaintRenderingResultsToCanvas>(connection, decoder, this, &RemoteGraphicsContextGL::paintRenderingResultsToCanvas);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::PaintCompositedResultsToCanvas::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::PaintCompositedResultsToCanvas>(connection, decoder, this, &RemoteGraphicsContextGL::paintCompositedResultsToCanvas);
#if ENABLE(VIDEO) && PLATFORM(COCOA)
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CopyTextureFromVideoFrame::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::CopyTextureFromVideoFrame>(connection, decoder, this, &RemoteGraphicsContextGL::copyTextureFromVideoFrame);
#endif
#if ENABLE(MEDIA_STREAM) || ENABLE(WEB_CODECS)
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::PaintCompositedResultsToVideoFrame::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::PaintCompositedResultsToVideoFrame>(connection, decoder, this, &RemoteGraphicsContextGL::paintCompositedResultsToVideoFrame);
#endif
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ReadPixelsInline::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::ReadPixelsInline>(connection, decoder, this, &RemoteGraphicsContextGL::readPixelsInline);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ReadPixelsSharedMemory::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::ReadPixelsSharedMemory>(connection, decoder, this, &RemoteGraphicsContextGL::readPixelsSharedMemory);
#if PLATFORM(COCOA)
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CreateAndBindEGLImage::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::CreateAndBindEGLImage>(connection, decoder, this, &RemoteGraphicsContextGL::createAndBindEGLImage);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CreateEGLSync::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::CreateEGLSync>(connection, decoder, this, &RemoteGraphicsContextGL::createEGLSync);
#endif
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CheckFramebufferStatus::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::CheckFramebufferStatus>(connection, decoder, this, &RemoteGraphicsContextGL::checkFramebufferStatus);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CreateBuffer::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::CreateBuffer>(connection, decoder, this, &RemoteGraphicsContextGL::createBuffer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CreateFramebuffer::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::CreateFramebuffer>(connection, decoder, this, &RemoteGraphicsContextGL::createFramebuffer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CreateProgram::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::CreateProgram>(connection, decoder, this, &RemoteGraphicsContextGL::createProgram);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CreateRenderbuffer::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::CreateRenderbuffer>(connection, decoder, this, &RemoteGraphicsContextGL::createRenderbuffer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CreateShader::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::CreateShader>(connection, decoder, this, &RemoteGraphicsContextGL::createShader);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CreateTexture::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::CreateTexture>(connection, decoder, this, &RemoteGraphicsContextGL::createTexture);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetActiveAttrib::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetActiveAttrib>(connection, decoder, this, &RemoteGraphicsContextGL::getActiveAttrib);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetActiveUniform::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetActiveUniform>(connection, decoder, this, &RemoteGraphicsContextGL::getActiveUniform);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetAttribLocation::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetAttribLocation>(connection, decoder, this, &RemoteGraphicsContextGL::getAttribLocation);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetBufferParameteri::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetBufferParameteri>(connection, decoder, this, &RemoteGraphicsContextGL::getBufferParameteri);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetString::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetString>(connection, decoder, this, &RemoteGraphicsContextGL::getString);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetFloatv::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetFloatv>(connection, decoder, this, &RemoteGraphicsContextGL::getFloatv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetIntegerv::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetIntegerv>(connection, decoder, this, &RemoteGraphicsContextGL::getIntegerv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetIntegeri_v::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetIntegeri_v>(connection, decoder, this, &RemoteGraphicsContextGL::getIntegeri_v);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetInteger64::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetInteger64>(connection, decoder, this, &RemoteGraphicsContextGL::getInteger64);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetInteger64i::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetInteger64i>(connection, decoder, this, &RemoteGraphicsContextGL::getInteger64i);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetProgrami::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetProgrami>(connection, decoder, this, &RemoteGraphicsContextGL::getProgrami);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetBooleanv::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetBooleanv>(connection, decoder, this, &RemoteGraphicsContextGL::getBooleanv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetFramebufferAttachmentParameteri::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetFramebufferAttachmentParameteri>(connection, decoder, this, &RemoteGraphicsContextGL::getFramebufferAttachmentParameteri);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetProgramInfoLog::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetProgramInfoLog>(connection, decoder, this, &RemoteGraphicsContextGL::getProgramInfoLog);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetRenderbufferParameteri::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetRenderbufferParameteri>(connection, decoder, this, &RemoteGraphicsContextGL::getRenderbufferParameteri);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetShaderi::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetShaderi>(connection, decoder, this, &RemoteGraphicsContextGL::getShaderi);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetShaderInfoLog::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetShaderInfoLog>(connection, decoder, this, &RemoteGraphicsContextGL::getShaderInfoLog);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetShaderPrecisionFormat::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetShaderPrecisionFormat>(connection, decoder, this, &RemoteGraphicsContextGL::getShaderPrecisionFormat);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetShaderSource::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetShaderSource>(connection, decoder, this, &RemoteGraphicsContextGL::getShaderSource);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetTexParameterf::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetTexParameterf>(connection, decoder, this, &RemoteGraphicsContextGL::getTexParameterf);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetTexParameteri::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetTexParameteri>(connection, decoder, this, &RemoteGraphicsContextGL::getTexParameteri);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetUniformfv::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetUniformfv>(connection, decoder, this, &RemoteGraphicsContextGL::getUniformfv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetUniformiv::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetUniformiv>(connection, decoder, this, &RemoteGraphicsContextGL::getUniformiv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetUniformuiv::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetUniformuiv>(connection, decoder, this, &RemoteGraphicsContextGL::getUniformuiv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetUniformLocation::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetUniformLocation>(connection, decoder, this, &RemoteGraphicsContextGL::getUniformLocation);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetVertexAttribOffset::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetVertexAttribOffset>(connection, decoder, this, &RemoteGraphicsContextGL::getVertexAttribOffset);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::IsBuffer::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::IsBuffer>(connection, decoder, this, &RemoteGraphicsContextGL::isBuffer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::IsEnabled::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::IsEnabled>(connection, decoder, this, &RemoteGraphicsContextGL::isEnabled);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::IsFramebuffer::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::IsFramebuffer>(connection, decoder, this, &RemoteGraphicsContextGL::isFramebuffer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::IsProgram::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::IsProgram>(connection, decoder, this, &RemoteGraphicsContextGL::isProgram);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::IsRenderbuffer::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::IsRenderbuffer>(connection, decoder, this, &RemoteGraphicsContextGL::isRenderbuffer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::IsShader::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::IsShader>(connection, decoder, this, &RemoteGraphicsContextGL::isShader);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::IsTexture::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::IsTexture>(connection, decoder, this, &RemoteGraphicsContextGL::isTexture);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CreateVertexArray::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::CreateVertexArray>(connection, decoder, this, &RemoteGraphicsContextGL::createVertexArray);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::IsVertexArray::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::IsVertexArray>(connection, decoder, this, &RemoteGraphicsContextGL::isVertexArray);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetBufferSubData::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetBufferSubData>(connection, decoder, this, &RemoteGraphicsContextGL::getBufferSubData);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetFragDataLocation::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetFragDataLocation>(connection, decoder, this, &RemoteGraphicsContextGL::getFragDataLocation);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CreateQuery::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::CreateQuery>(connection, decoder, this, &RemoteGraphicsContextGL::createQuery);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::IsQuery::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::IsQuery>(connection, decoder, this, &RemoteGraphicsContextGL::isQuery);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetQuery::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetQuery>(connection, decoder, this, &RemoteGraphicsContextGL::getQuery);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetQueryObjectui::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetQueryObjectui>(connection, decoder, this, &RemoteGraphicsContextGL::getQueryObjectui);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CreateSampler::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::CreateSampler>(connection, decoder, this, &RemoteGraphicsContextGL::createSampler);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::IsSampler::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::IsSampler>(connection, decoder, this, &RemoteGraphicsContextGL::isSampler);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetSamplerParameterf::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetSamplerParameterf>(connection, decoder, this, &RemoteGraphicsContextGL::getSamplerParameterf);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetSamplerParameteri::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetSamplerParameteri>(connection, decoder, this, &RemoteGraphicsContextGL::getSamplerParameteri);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::FenceSync::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::FenceSync>(connection, decoder, this, &RemoteGraphicsContextGL::fenceSync);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::IsSync::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::IsSync>(connection, decoder, this, &RemoteGraphicsContextGL::isSync);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::ClientWaitSync::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::ClientWaitSync>(connection, decoder, this, &RemoteGraphicsContextGL::clientWaitSync);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetSynci::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetSynci>(connection, decoder, this, &RemoteGraphicsContextGL::getSynci);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CreateTransformFeedback::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::CreateTransformFeedback>(connection, decoder, this, &RemoteGraphicsContextGL::createTransformFeedback);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::IsTransformFeedback::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::IsTransformFeedback>(connection, decoder, this, &RemoteGraphicsContextGL::isTransformFeedback);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetTransformFeedbackVarying::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetTransformFeedbackVarying>(connection, decoder, this, &RemoteGraphicsContextGL::getTransformFeedbackVarying);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetUniformIndices::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetUniformIndices>(connection, decoder, this, &RemoteGraphicsContextGL::getUniformIndices);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetActiveUniforms::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetActiveUniforms>(connection, decoder, this, &RemoteGraphicsContextGL::getActiveUniforms);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetUniformBlockIndex::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetUniformBlockIndex>(connection, decoder, this, &RemoteGraphicsContextGL::getUniformBlockIndex);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetActiveUniformBlockName::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetActiveUniformBlockName>(connection, decoder, this, &RemoteGraphicsContextGL::getActiveUniformBlockName);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetActiveUniformBlockiv::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetActiveUniformBlockiv>(connection, decoder, this, &RemoteGraphicsContextGL::getActiveUniformBlockiv);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetTranslatedShaderSourceANGLE::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetTranslatedShaderSourceANGLE>(connection, decoder, this, &RemoteGraphicsContextGL::getTranslatedShaderSourceANGLE);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::CreateQueryEXT::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::CreateQueryEXT>(connection, decoder, this, &RemoteGraphicsContextGL::createQueryEXT);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::IsQueryEXT::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::IsQueryEXT>(connection, decoder, this, &RemoteGraphicsContextGL::isQueryEXT);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetQueryiEXT::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetQueryiEXT>(connection, decoder, this, &RemoteGraphicsContextGL::getQueryiEXT);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetQueryObjectiEXT::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetQueryObjectiEXT>(connection, decoder, this, &RemoteGraphicsContextGL::getQueryObjectiEXT);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetQueryObjectui64EXT::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetQueryObjectui64EXT>(connection, decoder, this, &RemoteGraphicsContextGL::getQueryObjectui64EXT);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetInteger64EXT::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetInteger64EXT>(connection, decoder, this, &RemoteGraphicsContextGL::getInteger64EXT);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::GetInternalformativ::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::GetInternalformativ>(connection, decoder, this, &RemoteGraphicsContextGL::getInternalformativ);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::PaintRenderingResultsToPixelBuffer::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::PaintRenderingResultsToPixelBuffer>(connection, decoder, this, &RemoteGraphicsContextGL::paintRenderingResultsToPixelBuffer);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::DestroyEGLSync::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::DestroyEGLSync>(connection, decoder, this, &RemoteGraphicsContextGL::destroyEGLSync);
    if (decoder.messageName() == Messages::RemoteGraphicsContextGL::EnableRequiredWebXRExtensions::name())
        return IPC::handleMessageSynchronous<Messages::RemoteGraphicsContextGL::EnableRequiredWebXRExtensions>(connection, decoder, this, &RemoteGraphicsContextGL::enableRequiredWebXRExtensions);
    UNUSED_PARAM(decoder);
    UNUSED_PARAM(connection);
#if ENABLE(IPC_TESTING_API)
    if (connection.connection().ignoreInvalidMessageForTesting())
        return;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled stream message %s to %" PRIu64, IPC::description(decoder.messageName()), decoder.destinationID());
}

} // namespace WebKit

#if ENABLE(IPC_TESTING_API)

namespace IPC {

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Reshape>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Reshape::Arguments>(globalObject, decoder);
}
#if PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_PrepareForDisplay>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PrepareForDisplay::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_PrepareForDisplay>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PrepareForDisplay::ReplyArguments>(globalObject, decoder);
}
#endif
#if USE(GRAPHICS_LAYER_WC)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_PrepareForDisplay>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PrepareForDisplay::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_PrepareForDisplay>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PrepareForDisplay::ReplyArguments>(globalObject, decoder);
}
#endif
#if USE(GBM)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_PrepareForDisplay>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PrepareForDisplay::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_PrepareForDisplay>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PrepareForDisplay::ReplyArguments>(globalObject, decoder);
}
#endif
#if !PLATFORM(COCOA) && !USE(GRAPHICS_LAYER_WC) && !USE(GBM)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_PrepareForDisplay>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PrepareForDisplay::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_PrepareForDisplay>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PrepareForDisplay::ReplyArguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_EnsureExtensionEnabled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::EnsureExtensionEnabled::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_MarkContextChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::MarkContextChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetErrors>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetErrors::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetErrors>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetErrors::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_PaintRenderingResultsToCanvas>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PaintRenderingResultsToCanvas::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_PaintRenderingResultsToCanvas>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PaintRenderingResultsToCanvas::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_PaintCompositedResultsToCanvas>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PaintCompositedResultsToCanvas::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_PaintCompositedResultsToCanvas>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PaintCompositedResultsToCanvas::ReplyArguments>(globalObject, decoder);
}
#if ENABLE(VIDEO) && PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CopyTextureFromVideoFrame>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CopyTextureFromVideoFrame::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_CopyTextureFromVideoFrame>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CopyTextureFromVideoFrame::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_SetSharedVideoFrameSemaphore>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::SetSharedVideoFrameSemaphore::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_SetSharedVideoFrameMemory>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::SetSharedVideoFrameMemory::Arguments>(globalObject, decoder);
}
#endif
#if ENABLE(MEDIA_STREAM) || ENABLE(WEB_CODECS)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_PaintCompositedResultsToVideoFrame>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PaintCompositedResultsToVideoFrame::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_PaintCompositedResultsToVideoFrame>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PaintCompositedResultsToVideoFrame::ReplyArguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_SimulateEventForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::SimulateEventForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ReadPixelsInline>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ReadPixelsInline::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_ReadPixelsInline>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ReadPixelsInline::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ReadPixelsSharedMemory>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ReadPixelsSharedMemory::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_ReadPixelsSharedMemory>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ReadPixelsSharedMemory::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_MultiDrawArraysANGLE>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::MultiDrawArraysANGLE::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_MultiDrawArraysInstancedANGLE>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::MultiDrawArraysInstancedANGLE::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_MultiDrawElementsANGLE>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::MultiDrawElementsANGLE::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_MultiDrawElementsInstancedANGLE>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::MultiDrawElementsInstancedANGLE::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_MultiDrawArraysInstancedBaseInstanceANGLE>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::MultiDrawArraysInstancedBaseInstanceANGLE::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_MultiDrawElementsInstancedBaseVertexBaseInstanceANGLE>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::MultiDrawElementsInstancedBaseVertexBaseInstanceANGLE::Arguments>(globalObject, decoder);
}
#if PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CreateAndBindEGLImage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateAndBindEGLImage::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_CreateAndBindEGLImage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateAndBindEGLImage::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CreateEGLSync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateEGLSync::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_CreateEGLSync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateEGLSync::ReplyArguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ActiveTexture>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ActiveTexture::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_AttachShader>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::AttachShader::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BindAttribLocation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BindAttribLocation::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BindBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BindBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BindFramebuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BindFramebuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BindRenderbuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BindRenderbuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BindTexture>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BindTexture::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BlendColor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BlendColor::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BlendEquation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BlendEquation::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BlendEquationSeparate>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BlendEquationSeparate::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BlendFunc>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BlendFunc::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BlendFuncSeparate>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BlendFuncSeparate::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CheckFramebufferStatus>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CheckFramebufferStatus::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_CheckFramebufferStatus>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CheckFramebufferStatus::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Clear>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Clear::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ClearColor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ClearColor::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ClearDepth>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ClearDepth::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ClearStencil>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ClearStencil::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ColorMask>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ColorMask::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CompileShader>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CompileShader::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CopyTexImage2D>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CopyTexImage2D::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CopyTexSubImage2D>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CopyTexSubImage2D::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CreateBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_CreateBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateBuffer::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CreateFramebuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateFramebuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_CreateFramebuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateFramebuffer::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CreateProgram>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateProgram::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_CreateProgram>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateProgram::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CreateRenderbuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateRenderbuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_CreateRenderbuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateRenderbuffer::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CreateShader>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateShader::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_CreateShader>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateShader::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CreateTexture>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateTexture::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_CreateTexture>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateTexture::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CullFace>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CullFace::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DeleteBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DeleteBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DeleteFramebuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DeleteFramebuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DeleteProgram>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DeleteProgram::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DeleteRenderbuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DeleteRenderbuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DeleteShader>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DeleteShader::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DeleteTexture>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DeleteTexture::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DepthFunc>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DepthFunc::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DepthMask>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DepthMask::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DepthRange>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DepthRange::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DestroyEGLImage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DestroyEGLImage::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DetachShader>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DetachShader::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Disable>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Disable::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DisableVertexAttribArray>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DisableVertexAttribArray::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DrawArrays>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DrawArrays::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DrawElements>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DrawElements::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Enable>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Enable::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_EnableVertexAttribArray>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::EnableVertexAttribArray::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Finish>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Finish::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Flush>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Flush::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_FramebufferRenderbuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::FramebufferRenderbuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_FramebufferTexture2D>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::FramebufferTexture2D::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_FrontFace>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::FrontFace::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GenerateMipmap>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GenerateMipmap::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetActiveAttrib>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetActiveAttrib::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetActiveAttrib>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetActiveAttrib::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetActiveUniform>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetActiveUniform::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetActiveUniform>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetActiveUniform::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetAttribLocation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetAttribLocation::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetAttribLocation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetAttribLocation::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetBufferParameteri>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetBufferParameteri::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetBufferParameteri>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetBufferParameteri::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetString>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetString::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetString>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetString::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetFloatv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetFloatv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetFloatv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetFloatv::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetIntegerv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetIntegerv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetIntegerv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetIntegerv::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetIntegeri_v>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetIntegeri_v::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetIntegeri_v>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetIntegeri_v::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetInteger64>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetInteger64::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetInteger64>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetInteger64::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetInteger64i>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetInteger64i::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetInteger64i>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetInteger64i::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetProgrami>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetProgrami::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetProgrami>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetProgrami::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetBooleanv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetBooleanv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetBooleanv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetBooleanv::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetFramebufferAttachmentParameteri>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetFramebufferAttachmentParameteri::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetFramebufferAttachmentParameteri>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetFramebufferAttachmentParameteri::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetProgramInfoLog>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetProgramInfoLog::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetProgramInfoLog>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetProgramInfoLog::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetRenderbufferParameteri>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetRenderbufferParameteri::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetRenderbufferParameteri>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetRenderbufferParameteri::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetShaderi>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetShaderi::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetShaderi>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetShaderi::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetShaderInfoLog>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetShaderInfoLog::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetShaderInfoLog>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetShaderInfoLog::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetShaderPrecisionFormat>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetShaderPrecisionFormat::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetShaderPrecisionFormat>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetShaderPrecisionFormat::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetShaderSource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetShaderSource::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetShaderSource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetShaderSource::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetTexParameterf>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetTexParameterf::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetTexParameterf>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetTexParameterf::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetTexParameteri>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetTexParameteri::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetTexParameteri>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetTexParameteri::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetUniformfv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetUniformfv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetUniformfv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetUniformfv::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetUniformiv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetUniformiv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetUniformiv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetUniformiv::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetUniformuiv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetUniformuiv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetUniformuiv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetUniformuiv::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetUniformLocation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetUniformLocation::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetUniformLocation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetUniformLocation::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetVertexAttribOffset>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetVertexAttribOffset::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetVertexAttribOffset>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetVertexAttribOffset::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Hint>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Hint::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_IsBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_IsBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsBuffer::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_IsEnabled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsEnabled::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_IsEnabled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsEnabled::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_IsFramebuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsFramebuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_IsFramebuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsFramebuffer::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_IsProgram>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsProgram::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_IsProgram>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsProgram::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_IsRenderbuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsRenderbuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_IsRenderbuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsRenderbuffer::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_IsShader>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsShader::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_IsShader>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsShader::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_IsTexture>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsTexture::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_IsTexture>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsTexture::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_LineWidth>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::LineWidth::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_LinkProgram>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::LinkProgram::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_PixelStorei>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PixelStorei::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_PolygonOffset>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PolygonOffset::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_RenderbufferStorage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::RenderbufferStorage::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_SampleCoverage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::SampleCoverage::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Scissor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Scissor::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ShaderSource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ShaderSource::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_StencilFunc>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::StencilFunc::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_StencilFuncSeparate>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::StencilFuncSeparate::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_StencilMask>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::StencilMask::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_StencilMaskSeparate>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::StencilMaskSeparate::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_StencilOp>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::StencilOp::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_StencilOpSeparate>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::StencilOpSeparate::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_TexParameterf>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::TexParameterf::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_TexParameteri>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::TexParameteri::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform1f>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform1f::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform1fv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform1fv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform1i>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform1i::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform1iv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform1iv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform2f>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform2f::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform2fv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform2fv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform2i>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform2i::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform2iv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform2iv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform3f>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform3f::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform3fv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform3fv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform3i>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform3i::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform3iv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform3iv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform4f>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform4f::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform4fv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform4fv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform4i>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform4i::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform4iv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform4iv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_UniformMatrix2fv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::UniformMatrix2fv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_UniformMatrix3fv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::UniformMatrix3fv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_UniformMatrix4fv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::UniformMatrix4fv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_UseProgram>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::UseProgram::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ValidateProgram>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ValidateProgram::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_VertexAttrib1f>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::VertexAttrib1f::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_VertexAttrib1fv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::VertexAttrib1fv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_VertexAttrib2f>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::VertexAttrib2f::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_VertexAttrib2fv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::VertexAttrib2fv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_VertexAttrib3f>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::VertexAttrib3f::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_VertexAttrib3fv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::VertexAttrib3fv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_VertexAttrib4f>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::VertexAttrib4f::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_VertexAttrib4fv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::VertexAttrib4fv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_VertexAttribPointer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::VertexAttribPointer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Viewport>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Viewport::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BufferData0>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BufferData0::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BufferData1>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BufferData1::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BufferSubData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BufferSubData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ReadPixelsBufferObject>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ReadPixelsBufferObject::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_TexImage2D0>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::TexImage2D0::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_TexImage2D1>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::TexImage2D1::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_TexSubImage2D0>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::TexSubImage2D0::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_TexSubImage2D1>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::TexSubImage2D1::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CompressedTexImage2D0>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CompressedTexImage2D0::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CompressedTexImage2D1>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CompressedTexImage2D1::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CompressedTexSubImage2D0>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CompressedTexSubImage2D0::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CompressedTexSubImage2D1>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CompressedTexSubImage2D1::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DrawArraysInstanced>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DrawArraysInstanced::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DrawElementsInstanced>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DrawElementsInstanced::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_VertexAttribDivisor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::VertexAttribDivisor::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CreateVertexArray>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateVertexArray::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_CreateVertexArray>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateVertexArray::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DeleteVertexArray>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DeleteVertexArray::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_IsVertexArray>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsVertexArray::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_IsVertexArray>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsVertexArray::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BindVertexArray>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BindVertexArray::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CopyBufferSubData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CopyBufferSubData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetBufferSubData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetBufferSubData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetBufferSubData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetBufferSubData::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BlitFramebuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BlitFramebuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_FramebufferTextureLayer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::FramebufferTextureLayer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_InvalidateFramebuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::InvalidateFramebuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_InvalidateSubFramebuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::InvalidateSubFramebuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ReadBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ReadBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_RenderbufferStorageMultisample>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::RenderbufferStorageMultisample::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_TexStorage2D>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::TexStorage2D::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_TexStorage3D>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::TexStorage3D::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_TexImage3D0>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::TexImage3D0::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_TexImage3D1>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::TexImage3D1::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_TexSubImage3D0>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::TexSubImage3D0::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_TexSubImage3D1>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::TexSubImage3D1::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CopyTexSubImage3D>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CopyTexSubImage3D::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CompressedTexImage3D0>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CompressedTexImage3D0::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CompressedTexImage3D1>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CompressedTexImage3D1::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CompressedTexSubImage3D0>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CompressedTexSubImage3D0::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CompressedTexSubImage3D1>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CompressedTexSubImage3D1::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetFragDataLocation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetFragDataLocation::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetFragDataLocation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetFragDataLocation::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform1ui>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform1ui::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform2ui>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform2ui::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform3ui>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform3ui::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform4ui>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform4ui::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform1uiv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform1uiv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform2uiv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform2uiv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform3uiv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform3uiv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_Uniform4uiv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::Uniform4uiv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_UniformMatrix2x3fv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::UniformMatrix2x3fv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_UniformMatrix3x2fv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::UniformMatrix3x2fv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_UniformMatrix2x4fv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::UniformMatrix2x4fv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_UniformMatrix4x2fv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::UniformMatrix4x2fv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_UniformMatrix3x4fv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::UniformMatrix3x4fv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_UniformMatrix4x3fv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::UniformMatrix4x3fv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_VertexAttribI4i>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::VertexAttribI4i::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_VertexAttribI4iv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::VertexAttribI4iv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_VertexAttribI4ui>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::VertexAttribI4ui::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_VertexAttribI4uiv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::VertexAttribI4uiv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_VertexAttribIPointer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::VertexAttribIPointer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DrawRangeElements>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DrawRangeElements::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DrawBuffers>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DrawBuffers::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ClearBufferiv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ClearBufferiv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ClearBufferuiv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ClearBufferuiv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ClearBufferfv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ClearBufferfv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ClearBufferfi>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ClearBufferfi::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CreateQuery>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateQuery::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_CreateQuery>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateQuery::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DeleteQuery>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DeleteQuery::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_IsQuery>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsQuery::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_IsQuery>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsQuery::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BeginQuery>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BeginQuery::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_EndQuery>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::EndQuery::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetQuery>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetQuery::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetQuery>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetQuery::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetQueryObjectui>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetQueryObjectui::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetQueryObjectui>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetQueryObjectui::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CreateSampler>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateSampler::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_CreateSampler>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateSampler::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DeleteSampler>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DeleteSampler::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_IsSampler>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsSampler::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_IsSampler>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsSampler::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BindSampler>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BindSampler::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_SamplerParameteri>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::SamplerParameteri::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_SamplerParameterf>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::SamplerParameterf::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetSamplerParameterf>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetSamplerParameterf::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetSamplerParameterf>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetSamplerParameterf::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetSamplerParameteri>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetSamplerParameteri::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetSamplerParameteri>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetSamplerParameteri::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_FenceSync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::FenceSync::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_FenceSync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::FenceSync::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_IsSync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsSync::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_IsSync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsSync::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DeleteSync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DeleteSync::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ClientWaitSync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ClientWaitSync::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_ClientWaitSync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ClientWaitSync::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_WaitSync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::WaitSync::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetSynci>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetSynci::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetSynci>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetSynci::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CreateTransformFeedback>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateTransformFeedback::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_CreateTransformFeedback>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateTransformFeedback::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DeleteTransformFeedback>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DeleteTransformFeedback::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_IsTransformFeedback>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsTransformFeedback::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_IsTransformFeedback>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsTransformFeedback::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BindTransformFeedback>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BindTransformFeedback::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BeginTransformFeedback>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BeginTransformFeedback::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_EndTransformFeedback>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::EndTransformFeedback::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_TransformFeedbackVaryings>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::TransformFeedbackVaryings::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetTransformFeedbackVarying>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetTransformFeedbackVarying::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetTransformFeedbackVarying>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetTransformFeedbackVarying::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_PauseTransformFeedback>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PauseTransformFeedback::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ResumeTransformFeedback>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ResumeTransformFeedback::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BindBufferBase>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BindBufferBase::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BindBufferRange>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BindBufferRange::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetUniformIndices>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetUniformIndices::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetUniformIndices>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetUniformIndices::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetActiveUniforms>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetActiveUniforms::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetActiveUniforms>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetActiveUniforms::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetUniformBlockIndex>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetUniformBlockIndex::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetUniformBlockIndex>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetUniformBlockIndex::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetActiveUniformBlockName>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetActiveUniformBlockName::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetActiveUniformBlockName>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetActiveUniformBlockName::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_UniformBlockBinding>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::UniformBlockBinding::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetActiveUniformBlockiv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetActiveUniformBlockiv::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetActiveUniformBlockiv>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetActiveUniformBlockiv::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetTranslatedShaderSourceANGLE>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetTranslatedShaderSourceANGLE::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetTranslatedShaderSourceANGLE>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetTranslatedShaderSourceANGLE::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DrawBuffersEXT>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DrawBuffersEXT::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_CreateQueryEXT>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateQueryEXT::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_CreateQueryEXT>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::CreateQueryEXT::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DeleteQueryEXT>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DeleteQueryEXT::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_IsQueryEXT>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsQueryEXT::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_IsQueryEXT>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::IsQueryEXT::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BeginQueryEXT>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BeginQueryEXT::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_EndQueryEXT>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::EndQueryEXT::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_QueryCounterEXT>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::QueryCounterEXT::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetQueryiEXT>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetQueryiEXT::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetQueryiEXT>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetQueryiEXT::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetQueryObjectiEXT>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetQueryObjectiEXT::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetQueryObjectiEXT>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetQueryObjectiEXT::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetQueryObjectui64EXT>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetQueryObjectui64EXT::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetQueryObjectui64EXT>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetQueryObjectui64EXT::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetInteger64EXT>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetInteger64EXT::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetInteger64EXT>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetInteger64EXT::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_EnableiOES>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::EnableiOES::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DisableiOES>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DisableiOES::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BlendEquationiOES>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BlendEquationiOES::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BlendEquationSeparateiOES>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BlendEquationSeparateiOES::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BlendFunciOES>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BlendFunciOES::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BlendFuncSeparateiOES>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BlendFuncSeparateiOES::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ColorMaskiOES>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ColorMaskiOES::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DrawArraysInstancedBaseInstanceANGLE>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DrawArraysInstancedBaseInstanceANGLE::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DrawElementsInstancedBaseVertexBaseInstanceANGLE>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DrawElementsInstancedBaseVertexBaseInstanceANGLE::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ClipControlEXT>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ClipControlEXT::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ProvokingVertexANGLE>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ProvokingVertexANGLE::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_PolygonModeANGLE>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PolygonModeANGLE::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_PolygonOffsetClampEXT>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PolygonOffsetClampEXT::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_RenderbufferStorageMultisampleANGLE>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::RenderbufferStorageMultisampleANGLE::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_BlitFramebufferANGLE>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::BlitFramebufferANGLE::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_GetInternalformativ>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetInternalformativ::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_GetInternalformativ>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::GetInternalformativ::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_SetDrawingBufferColorSpace>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::SetDrawingBufferColorSpace::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_PaintRenderingResultsToPixelBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PaintRenderingResultsToPixelBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_PaintRenderingResultsToPixelBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::PaintRenderingResultsToPixelBuffer::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_DestroyEGLSync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DestroyEGLSync::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_DestroyEGLSync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::DestroyEGLSync::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_ClientWaitEGLSyncWithFlush>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::ClientWaitEGLSyncWithFlush::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteGraphicsContextGL_EnableRequiredWebXRExtensions>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::EnableRequiredWebXRExtensions::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteGraphicsContextGL_EnableRequiredWebXRExtensions>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteGraphicsContextGL::EnableRequiredWebXRExtensions::ReplyArguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
