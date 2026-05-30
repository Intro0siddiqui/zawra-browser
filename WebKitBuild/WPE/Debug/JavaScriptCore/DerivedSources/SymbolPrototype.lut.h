// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/runtime/SymbolPrototype.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex symbolPrototypeTableIndex[8] = {
    { -1, -1 },
    { -1, -1 },
    { 2, -1 },
    { -1, -1 },
    { 1, -1 },
    { -1, -1 },
    { -1, -1 },
    { 0, -1 },
};

static const struct HashTableValue symbolPrototypeTableValues[3] = {
   { "description"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::ReadOnly|PropertyAttribute::CustomAccessor), NoIntrinsic, { HashTableValue::GetterSetterType, symbolProtoGetterDescription, 0 } },
   { "toString"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, symbolProtoFuncToString, 0 } },
   { "valueOf"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, symbolProtoFuncValueOf, 0 } },
};

static const struct HashTable symbolPrototypeTable =
    { 3, 7, true, nullptr, symbolPrototypeTableValues, symbolPrototypeTableIndex };

} // namespace JSC
