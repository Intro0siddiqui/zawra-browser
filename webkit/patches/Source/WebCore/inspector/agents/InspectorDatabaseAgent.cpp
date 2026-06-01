/*
 * Copyright (C) 2010 Google Inc. All rights reserved.
 * Copyright (C) 2015 Apple Inc. All rights reserved.
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
#include "InspectorDatabaseAgent.h"

#include <JavaScriptCore/InspectorFrontendRouter.h>

namespace WebCore {

using namespace Inspector;

InspectorDatabaseAgent::InspectorDatabaseAgent(WebAgentContext& context)
    : InspectorAgentBase("Database"_s, context)
    , m_frontendDispatcher(makeUnique<Inspector::DatabaseFrontendDispatcher>(context.frontendRouter))
    , m_backendDispatcher(Inspector::DatabaseBackendDispatcher::create(context.backendDispatcher, this))
{
}

InspectorDatabaseAgent::~InspectorDatabaseAgent() = default;

void InspectorDatabaseAgent::didCreateFrontendAndBackend(Inspector::FrontendRouter*, Inspector::BackendDispatcher*)
{
}

void InspectorDatabaseAgent::willDestroyFrontendAndBackend(Inspector::DisconnectReason)
{
    disable();
}

Protocol::ErrorStringOr<void> InspectorDatabaseAgent::enable()
{
    return { };
}

Protocol::ErrorStringOr<void> InspectorDatabaseAgent::disable()
{
    return { };
}

Protocol::ErrorStringOr<Ref<JSON::ArrayOf<String>>> InspectorDatabaseAgent::getDatabaseTableNames(const Protocol::Database::DatabaseId&)
{
    return JSON::ArrayOf<String>::create();
}

void InspectorDatabaseAgent::executeSQL(const Protocol::Database::DatabaseId&, const String&, Ref<ExecuteSQLCallback>&& requestCallback)
{
    requestCallback->sendFailure("Web SQL Database is not supported"_s);
}

void InspectorDatabaseAgent::didCommitLoad()
{
}

String InspectorDatabaseAgent::databaseId(void*)
{
    return String();
}

} // namespace WebCore
