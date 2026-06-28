/*
 * Copyright (C) 2021 Apple Inc. All rights reserved.
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

// Zawra patch stub implementation of DatabaseUtilities (SQLite removed).

#include "config.h"
#include "DatabaseUtilities.h"

namespace WebKit {

DatabaseUtilities::DatabaseUtilities(String&& storageFilePath)
    : m_storageFilePath(WTFMove(storageFilePath))
{
}

DatabaseUtilities::~DatabaseUtilities()
{
}

int DatabaseUtilities::scopedStatement(std::unique_ptr<void*>&, ASCIILiteral, ASCIILiteral) const
{
    return 0;
}

ScopeExit<Function<void()>> DatabaseUtilities::beginTransactionIfNecessary()
{
    return makeScopeExit(Function<void()> { [] { } });
}

auto DatabaseUtilities::openDatabaseAndCreateSchemaIfNecessary() -> CreatedNewFile
{
    return CreatedNewFile::No;
}

void DatabaseUtilities::enableForeignKeys()
{
}

void DatabaseUtilities::close()
{
}

void DatabaseUtilities::interrupt()
{
}

TableAndIndexPair DatabaseUtilities::currentTableAndIndexQueries(const String&)
{
    return { };
}

String DatabaseUtilities::stripIndexQueryToMatchStoredValue(const char* originalQuery)
{
    return String::fromLatin1(originalQuery);
}

void DatabaseUtilities::migrateDataToNewTablesIfNecessary()
{
}

Vector<String> DatabaseUtilities::columnsForTable(ASCIILiteral)
{
    return { };
}

bool DatabaseUtilities::addMissingColumnToTable(ASCIILiteral, ASCIILiteral)
{
    return false;
}

} // namespace WebKit
