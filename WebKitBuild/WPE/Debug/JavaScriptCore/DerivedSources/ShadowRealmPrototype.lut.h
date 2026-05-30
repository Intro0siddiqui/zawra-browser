// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/runtime/ShadowRealmPrototype.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "JSCBuiltins.h"
#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex shadowRealmPrototypeTableIndex[5] = {
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { 0, 4 },
    { 1, -1 },
};

static const struct HashTableValue shadowRealmPrototypeTableValues[2] = {
   { "evaluate"_s, ((static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function)) & ~PropertyAttribute::Function) | PropertyAttribute::Builtin, NoIntrinsic, { HashTableValue::BuiltinGeneratorType, shadowRealmPrototypeEvaluateCodeGenerator, 1 } },
   { "importValue"_s, ((static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function)) & ~PropertyAttribute::Function) | PropertyAttribute::Builtin, NoIntrinsic, { HashTableValue::BuiltinGeneratorType, shadowRealmPrototypeImportValueCodeGenerator, 2 } },
};

static const struct HashTable shadowRealmPrototypeTable =
    { 2, 3, false, nullptr, shadowRealmPrototypeTableValues, shadowRealmPrototypeTableIndex };

} // namespace JSC
