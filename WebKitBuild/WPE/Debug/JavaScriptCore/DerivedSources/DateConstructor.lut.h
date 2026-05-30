// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/runtime/DateConstructor.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex dateConstructorTableIndex[9] = {
    { -1, -1 },
    { 0, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { 1, 8 },
    { -1, -1 },
    { -1, -1 },
    { 2, -1 },
};

static const struct HashTableValue dateConstructorTableValues[3] = {
   { "parse"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, dateParse, 1 } },
   { "UTC"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, dateUTC, 7 } },
   { "now"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, dateNow, 0 } },
};

static const struct HashTable dateConstructorTable =
    { 3, 7, false, nullptr, dateConstructorTableValues, dateConstructorTableIndex };

} // namespace JSC
