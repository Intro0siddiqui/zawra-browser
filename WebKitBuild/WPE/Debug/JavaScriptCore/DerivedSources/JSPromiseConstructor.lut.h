// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/runtime/JSPromiseConstructor.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "JSCBuiltins.h"
#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex promiseConstructorTableIndex[18] = {
    { 2, -1 },
    { -1, -1 },
    { 0, 16 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { 4, 17 },
    { -1, -1 },
    { -1, -1 },
    { 1, -1 },
    { -1, -1 },
    { -1, -1 },
    { 3, -1 },
    { 5, -1 },
};

static const struct HashTableValue promiseConstructorTableValues[6] = {
   { "resolve"_s, ((static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function)) & ~PropertyAttribute::Function) | PropertyAttribute::Builtin, NoIntrinsic, { HashTableValue::BuiltinGeneratorType, promiseConstructorResolveCodeGenerator, 1 } },
   { "reject"_s, ((static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function)) & ~PropertyAttribute::Function) | PropertyAttribute::Builtin, NoIntrinsic, { HashTableValue::BuiltinGeneratorType, promiseConstructorRejectCodeGenerator, 1 } },
   { "race"_s, ((static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function)) & ~PropertyAttribute::Function) | PropertyAttribute::Builtin, NoIntrinsic, { HashTableValue::BuiltinGeneratorType, promiseConstructorRaceCodeGenerator, 1 } },
   { "all"_s, ((static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function)) & ~PropertyAttribute::Function) | PropertyAttribute::Builtin, NoIntrinsic, { HashTableValue::BuiltinGeneratorType, promiseConstructorAllCodeGenerator, 1 } },
   { "allSettled"_s, ((static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function)) & ~PropertyAttribute::Function) | PropertyAttribute::Builtin, NoIntrinsic, { HashTableValue::BuiltinGeneratorType, promiseConstructorAllSettledCodeGenerator, 1 } },
   { "any"_s, ((static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function)) & ~PropertyAttribute::Function) | PropertyAttribute::Builtin, NoIntrinsic, { HashTableValue::BuiltinGeneratorType, promiseConstructorAnyCodeGenerator, 1 } },
};

static const struct HashTable promiseConstructorTable =
    { 6, 15, false, nullptr, promiseConstructorTableValues, promiseConstructorTableIndex };

} // namespace JSC
