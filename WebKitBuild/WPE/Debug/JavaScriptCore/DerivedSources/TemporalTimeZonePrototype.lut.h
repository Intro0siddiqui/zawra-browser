// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/runtime/TemporalTimeZonePrototype.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex temporalTimeZonePrototypeTableIndex[8] = {
    { 1, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { 0, -1 },
    { 2, -1 },
    { -1, -1 },
    { -1, -1 },
};

static const struct HashTableValue temporalTimeZonePrototypeTableValues[3] = {
   { "toString"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, temporalTimeZonePrototypeFuncToString, 0 } },
   { "toJSON"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, temporalTimeZonePrototypeFuncToJSON, 0 } },
   { "id"_s, static_cast<unsigned>(PropertyAttribute::ReadOnly|PropertyAttribute::DontEnum|PropertyAttribute::CustomAccessor), NoIntrinsic, { HashTableValue::GetterSetterType, temporalTimeZonePrototypeGetterId, 0 } },
};

static const struct HashTable temporalTimeZonePrototypeTable =
    { 3, 7, true, nullptr, temporalTimeZonePrototypeTableValues, temporalTimeZonePrototypeTableIndex };

} // namespace JSC
