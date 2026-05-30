// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/runtime/TemporalInstantConstructor.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex temporalInstantConstructorTableIndex[16] = {
    { 4, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { 5, -1 },
    { -1, -1 },
    { 0, -1 },
    { -1, -1 },
    { -1, -1 },
    { 2, -1 },
    { 1, -1 },
    { 3, -1 },
};

static const struct HashTableValue temporalInstantConstructorTableValues[6] = {
   { "from"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, temporalInstantConstructorFuncFrom, 1 } },
   { "fromEpochSeconds"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, temporalInstantConstructorFuncFromEpochSeconds, 1 } },
   { "fromEpochMilliseconds"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, temporalInstantConstructorFuncFromEpochMilliseconds, 1 } },
   { "fromEpochMicroseconds"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, temporalInstantConstructorFuncFromEpochMicroseconds, 1 } },
   { "fromEpochNanoseconds"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, temporalInstantConstructorFuncFromEpochNanoseconds, 1 } },
   { "compare"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, temporalInstantConstructorFuncCompare, 2 } },
};

static const struct HashTable temporalInstantConstructorTable =
    { 6, 15, false, nullptr, temporalInstantConstructorTableValues, temporalInstantConstructorTableIndex };

} // namespace JSC
