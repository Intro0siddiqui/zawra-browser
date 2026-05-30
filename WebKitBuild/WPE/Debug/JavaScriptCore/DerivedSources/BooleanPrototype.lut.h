// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/runtime/BooleanPrototype.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex booleanPrototypeTableIndex[4] = {
    { 0, -1 },
    { -1, -1 },
    { 1, -1 },
    { -1, -1 },
};

static const struct HashTableValue booleanPrototypeTableValues[2] = {
   { "toString"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, booleanProtoFuncToString, 0 } },
   { "valueOf"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, booleanProtoFuncValueOf, 0 } },
};

static const struct HashTable booleanPrototypeTable =
    { 2, 3, false, nullptr, booleanPrototypeTableValues, booleanPrototypeTableIndex };

} // namespace JSC
