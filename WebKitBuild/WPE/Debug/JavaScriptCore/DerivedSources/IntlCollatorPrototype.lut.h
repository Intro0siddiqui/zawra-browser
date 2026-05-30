// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/runtime/IntlCollatorPrototype.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex collatorPrototypeTableIndex[4] = {
    { 0, -1 },
    { -1, -1 },
    { -1, -1 },
    { 1, -1 },
};

static const struct HashTableValue collatorPrototypeTableValues[2] = {
   { "compare"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::ReadOnly|PropertyAttribute::CustomAccessor), NoIntrinsic, { HashTableValue::GetterSetterType, intlCollatorPrototypeGetterCompare, 0 } },
   { "resolvedOptions"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, intlCollatorPrototypeFuncResolvedOptions, 0 } },
};

static const struct HashTable collatorPrototypeTable =
    { 2, 3, true, nullptr, collatorPrototypeTableValues, collatorPrototypeTableIndex };

} // namespace JSC
