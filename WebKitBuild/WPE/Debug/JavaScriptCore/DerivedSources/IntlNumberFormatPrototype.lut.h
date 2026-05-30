// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/runtime/IntlNumberFormatPrototype.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex numberFormatPrototypeTableIndex[9] = {
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { 2, -1 },
    { -1, -1 },
    { 0, 8 },
    { -1, -1 },
    { -1, -1 },
    { 1, -1 },
};

static const struct HashTableValue numberFormatPrototypeTableValues[3] = {
   { "format"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::ReadOnly|PropertyAttribute::CustomAccessor), NoIntrinsic, { HashTableValue::GetterSetterType, intlNumberFormatPrototypeGetterFormat, 0 } },
   { "formatToParts"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, intlNumberFormatPrototypeFuncFormatToParts, 1 } },
   { "resolvedOptions"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, intlNumberFormatPrototypeFuncResolvedOptions, 0 } },
};

static const struct HashTable numberFormatPrototypeTable =
    { 3, 7, true, nullptr, numberFormatPrototypeTableValues, numberFormatPrototypeTableIndex };

} // namespace JSC
