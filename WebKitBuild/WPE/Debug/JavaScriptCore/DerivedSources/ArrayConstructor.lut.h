// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/runtime/ArrayConstructor.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "JSCBuiltins.h"
#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex arrayConstructorTableIndex[4] = {
    { -1, -1 },
    { -1, -1 },
    { 1, -1 },
    { 0, -1 },
};

static const struct HashTableValue arrayConstructorTableValues[2] = {
   { "of"_s, ((static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function)) & ~PropertyAttribute::Function) | PropertyAttribute::Builtin, NoIntrinsic, { HashTableValue::BuiltinGeneratorType, arrayConstructorOfCodeGenerator, 0 } },
   { "from"_s, ((static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function)) & ~PropertyAttribute::Function) | PropertyAttribute::Builtin, NoIntrinsic, { HashTableValue::BuiltinGeneratorType, arrayConstructorFromCodeGenerator, 1 } },
};

static const struct HashTable arrayConstructorTable =
    { 2, 3, false, nullptr, arrayConstructorTableValues, arrayConstructorTableIndex };

} // namespace JSC
