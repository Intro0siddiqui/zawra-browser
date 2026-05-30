// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/runtime/ErrorPrototype.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex errorPrototypeTableIndex[2] = {
    { 0, -1 },
    { -1, -1 },
};

static const struct HashTableValue errorPrototypeTableValues[1] = {
   { "toString"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, errorProtoFuncToString, 0 } },
};

static const struct HashTable errorPrototypeTable =
    { 1, 1, false, nullptr, errorPrototypeTableValues, errorPrototypeTableIndex };

} // namespace JSC
