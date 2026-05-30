// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/runtime/IntlPluralRulesPrototype.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex pluralRulesPrototypeTableIndex[5] = {
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { 0, 4 },
    { 1, -1 },
};

static const struct HashTableValue pluralRulesPrototypeTableValues[2] = {
   { "select"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, intlPluralRulesPrototypeFuncSelect, 1 } },
   { "resolvedOptions"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, intlPluralRulesPrototypeFuncResolvedOptions, 0 } },
};

static const struct HashTable pluralRulesPrototypeTable =
    { 2, 3, false, nullptr, pluralRulesPrototypeTableValues, pluralRulesPrototypeTableIndex };

} // namespace JSC
