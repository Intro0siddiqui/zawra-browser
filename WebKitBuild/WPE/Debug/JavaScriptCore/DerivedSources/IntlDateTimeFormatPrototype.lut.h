// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/runtime/IntlDateTimeFormatPrototype.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex dateTimeFormatPrototypeTableIndex[9] = {
    { -1, -1 },
    { 1, -1 },
    { -1, -1 },
    { 3, -1 },
    { -1, -1 },
    { 0, 8 },
    { -1, -1 },
    { -1, -1 },
    { 2, -1 },
};

static const struct HashTableValue dateTimeFormatPrototypeTableValues[4] = {
   { "format"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::ReadOnly|PropertyAttribute::CustomAccessor), NoIntrinsic, { HashTableValue::GetterSetterType, intlDateTimeFormatPrototypeGetterFormat, 0 } },
   { "formatRange"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, intlDateTimeFormatPrototypeFuncFormatRange, 2 } },
   { "formatToParts"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, intlDateTimeFormatPrototypeFuncFormatToParts, 1 } },
   { "resolvedOptions"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, intlDateTimeFormatPrototypeFuncResolvedOptions, 0 } },
};

static const struct HashTable dateTimeFormatPrototypeTable =
    { 4, 7, true, nullptr, dateTimeFormatPrototypeTableValues, dateTimeFormatPrototypeTableIndex };

} // namespace JSC
