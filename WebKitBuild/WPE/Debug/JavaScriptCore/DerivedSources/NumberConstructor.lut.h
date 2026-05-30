// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/runtime/NumberConstructor.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "JSCBuiltins.h"
#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex numberConstructorTableIndex[8] = {
    { -1, -1 },
    { 2, -1 },
    { -1, -1 },
    { 0, -1 },
    { -1, -1 },
    { 1, -1 },
    { -1, -1 },
    { -1, -1 },
};

static const struct HashTableValue numberConstructorTableValues[3] = {
   { "isFinite"_s, ((static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function)) & ~PropertyAttribute::Function) | PropertyAttribute::Builtin, NoIntrinsic, { HashTableValue::BuiltinGeneratorType, numberConstructorIsFiniteCodeGenerator, 1 } },
   { "isNaN"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NumberIsNaNIntrinsic, { HashTableValue::NativeFunctionType, numberConstructorFuncIsNaN, 1 } },
   { "isSafeInteger"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, numberConstructorFuncIsSafeInteger, 1 } },
};

static const struct HashTable numberConstructorTable =
    { 3, 7, false, nullptr, numberConstructorTableValues, numberConstructorTableIndex };

} // namespace JSC
