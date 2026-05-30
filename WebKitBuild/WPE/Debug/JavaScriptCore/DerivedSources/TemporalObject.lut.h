// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/runtime/TemporalObject.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex temporalObjectTableIndex[17] = {
    { 4, -1 },
    { -1, -1 },
    { 1, -1 },
    { 0, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { 7, -1 },
    { -1, -1 },
    { -1, -1 },
    { 3, -1 },
    { 6, -1 },
    { 2, 16 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { 5, -1 },
};

static const struct HashTableValue temporalObjectTableValues[8] = {
   { "Calendar"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::PropertyCallback), NoIntrinsic, { HashTableValue::LazyPropertyType, createCalendarConstructor } },
   { "Duration"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::PropertyCallback), NoIntrinsic, { HashTableValue::LazyPropertyType, createDurationConstructor } },
   { "Instant"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::PropertyCallback), NoIntrinsic, { HashTableValue::LazyPropertyType, createInstantConstructor } },
   { "Now"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::PropertyCallback), NoIntrinsic, { HashTableValue::LazyPropertyType, createNowObject } },
   { "PlainDate"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::PropertyCallback), NoIntrinsic, { HashTableValue::LazyPropertyType, createPlainDateConstructor } },
   { "PlainDateTime"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::PropertyCallback), NoIntrinsic, { HashTableValue::LazyPropertyType, createPlainDateTimeConstructor } },
   { "PlainTime"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::PropertyCallback), NoIntrinsic, { HashTableValue::LazyPropertyType, createPlainTimeConstructor } },
   { "TimeZone"_s, static_cast<unsigned>(PropertyAttribute::DontEnum|PropertyAttribute::PropertyCallback), NoIntrinsic, { HashTableValue::LazyPropertyType, createTimeZoneConstructor } },
};

static const struct HashTable temporalObjectTable =
    { 8, 15, false, nullptr, temporalObjectTableValues, temporalObjectTableIndex };

} // namespace JSC
