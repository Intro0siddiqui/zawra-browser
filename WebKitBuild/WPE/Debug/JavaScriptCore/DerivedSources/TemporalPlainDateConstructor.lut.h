// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/runtime/TemporalPlainDateConstructor.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex temporalPlainDateConstructorTableIndex[4] = {
    { 1, -1 },
    { -1, -1 },
    { 0, -1 },
    { -1, -1 },
};

static const struct HashTableValue temporalPlainDateConstructorTableValues[2] = {
   { "from"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, temporalPlainDateConstructorFuncFrom, 1 } },
   { "compare"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, temporalPlainDateConstructorFuncCompare, 2 } },
};

static const struct HashTable temporalPlainDateConstructorTable =
    { 2, 3, false, nullptr, temporalPlainDateConstructorTableValues, temporalPlainDateConstructorTableIndex };

} // namespace JSC
