// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/runtime/BigIntConstructor.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex bigIntConstructorTableIndex[4] = {
    { 1, -1 },
    { 0, -1 },
    { -1, -1 },
    { -1, -1 },
};

static const struct HashTableValue bigIntConstructorTableValues[2] = {
   { "asUintN"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, bigIntConstructorFuncAsUintN, 2 } },
   { "asIntN"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, bigIntConstructorFuncAsIntN, 2 } },
};

static const struct HashTable bigIntConstructorTable =
    { 2, 3, false, nullptr, bigIntConstructorTableValues, bigIntConstructorTableIndex };

} // namespace JSC
