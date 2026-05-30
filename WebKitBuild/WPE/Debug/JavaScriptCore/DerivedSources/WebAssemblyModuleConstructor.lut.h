// Automatically generated from /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/wasm/js/WebAssemblyModuleConstructor.cpp using /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {

static const struct CompactHashIndex constructorTableWebAssemblyModuleIndex[8] = {
    { 2, -1 },
    { 0, -1 },
    { 1, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
};

static const struct HashTableValue constructorTableWebAssemblyModuleValues[3] = {
   { "customSections"_s, static_cast<unsigned>(PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, webAssemblyModuleCustomSections, 2 } },
   { "imports"_s, static_cast<unsigned>(PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, webAssemblyModuleImports, 1 } },
   { "exports"_s, static_cast<unsigned>(PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, webAssemblyModuleExports, 1 } },
};

static const struct HashTable constructorTableWebAssemblyModule =
    { 3, 7, false, nullptr, constructorTableWebAssemblyModuleValues, constructorTableWebAssemblyModuleIndex };

} // namespace JSC
