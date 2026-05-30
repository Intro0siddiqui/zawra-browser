// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/runtime/TemporalInstantPrototype.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex instantPrototypeTableIndex[35] = {
    { -1, -1 },
    { -1, -1 },
    { 3, 32 },
    { -1, -1 },
    { 2, -1 },
    { -1, -1 },
    { 8, -1 },
    { -1, -1 },
    { 7, 34 },
    { 11, -1 },
    { -1, -1 },
    { -1, -1 },
    { 13, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { 1, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { 5, -1 },
    { 0, 33 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { 4, -1 },
    { 6, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { 9, -1 },
    { 10, -1 },
    { 12, -1 },
};

static const struct HashTableValue instantPrototypeTableValues[14] = {
   { "add"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, temporalInstantPrototypeFuncAdd, 1 } },
   { "subtract"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, temporalInstantPrototypeFuncSubtract, 1 } },
   { "until"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, temporalInstantPrototypeFuncUntil, 1 } },
   { "since"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, temporalInstantPrototypeFuncSince, 1 } },
   { "round"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, temporalInstantPrototypeFuncRound, 1 } },
   { "equals"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, temporalInstantPrototypeFuncEquals, 1 } },
   { "toString"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, temporalInstantPrototypeFuncToString, 0 } },
   { "toJSON"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, temporalInstantPrototypeFuncToJSON, 0 } },
   { "toLocaleString"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, temporalInstantPrototypeFuncToLocaleString, 0 } },
   { "valueOf"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, temporalInstantPrototypeFuncValueOf, 0 } },
   { "epochSeconds"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::ReadOnly|PropertyAttribute::CustomAccessor), NoIntrinsic, { HashTableValue::GetterSetterType, temporalInstantPrototypeGetterEpochSeconds, 0 } },
   { "epochMilliseconds"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::ReadOnly|PropertyAttribute::CustomAccessor), NoIntrinsic, { HashTableValue::GetterSetterType, temporalInstantPrototypeGetterEpochMilliseconds, 0 } },
   { "epochMicroseconds"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::ReadOnly|PropertyAttribute::CustomAccessor), NoIntrinsic, { HashTableValue::GetterSetterType, temporalInstantPrototypeGetterEpochMicroseconds, 0 } },
   { "epochNanoseconds"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::ReadOnly|PropertyAttribute::CustomAccessor), NoIntrinsic, { HashTableValue::GetterSetterType, temporalInstantPrototypeGetterEpochNanoseconds, 0 } },
};

static const struct HashTable instantPrototypeTable =
    { 14, 31, true, nullptr, instantPrototypeTableValues, instantPrototypeTableIndex };

} // namespace JSC
