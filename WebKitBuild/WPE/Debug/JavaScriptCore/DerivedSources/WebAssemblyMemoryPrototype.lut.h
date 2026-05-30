// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/wasm/js/WebAssemblyMemoryPrototype.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex prototypeTableWebAssemblyMemoryIndex[10] = {
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { 0, 8 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { 1, 9 },
    { 2, -1 },
};

static const struct HashTableValue prototypeTableWebAssemblyMemoryValues[3] = {
   { "grow"_s, static_cast<unsigned>(PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, webAssemblyMemoryProtoFuncGrow, 1 } },
   { "buffer"_s, static_cast<unsigned>(PropertyAttribute::ReadOnly|PropertyAttribute::CustomAccessor), NoIntrinsic, { HashTableValue::GetterSetterType, webAssemblyMemoryProtoGetterBuffer, 0 } },
   { "type"_s, static_cast<unsigned>(PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, webAssemblyMemoryProtoFuncType, 0 } },
};

static const struct HashTable prototypeTableWebAssemblyMemory =
    { 3, 7, true, nullptr, prototypeTableWebAssemblyMemoryValues, prototypeTableWebAssemblyMemoryIndex };

} // namespace JSC
