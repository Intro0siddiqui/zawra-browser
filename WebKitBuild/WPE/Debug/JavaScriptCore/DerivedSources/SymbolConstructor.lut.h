// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/runtime/SymbolConstructor.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex symbolConstructorTableIndex[4] = {
    { 0, -1 },
    { -1, -1 },
    { -1, -1 },
    { 1, -1 },
};

static const struct HashTableValue symbolConstructorTableValues[2] = {
   { "for"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, symbolConstructorFor, 1 } },
   { "keyFor"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, symbolConstructorKeyFor, 1 } },
};

static const struct HashTable symbolConstructorTable =
    { 2, 3, false, nullptr, symbolConstructorTableValues, symbolConstructorTableIndex };

} // namespace JSC
