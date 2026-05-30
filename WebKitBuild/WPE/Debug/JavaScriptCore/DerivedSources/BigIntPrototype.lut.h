// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/runtime/BigIntPrototype.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex bigIntPrototypeTableIndex[8] = {
    { -1, -1 },
    { -1, -1 },
    { 2, -1 },
    { -1, -1 },
    { 0, -1 },
    { -1, -1 },
    { 1, -1 },
    { -1, -1 },
};

static const struct HashTableValue bigIntPrototypeTableValues[3] = {
   { "toString"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, bigIntProtoFuncToString, 0 } },
   { "toLocaleString"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, bigIntProtoFuncToLocaleString, 0 } },
   { "valueOf"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, bigIntProtoFuncValueOf, 0 } },
};

static const struct HashTable bigIntPrototypeTable =
    { 3, 7, false, nullptr, bigIntPrototypeTableValues, bigIntPrototypeTableIndex };

} // namespace JSC
