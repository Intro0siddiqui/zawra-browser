# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "RelWithDebInfo")
  file(REMOVE_RECURSE
  "Source/WebKit/CMakeFiles/qtwpe_autogen.dir/AutogenUsed.txt"
  "Source/WebKit/CMakeFiles/qtwpe_autogen.dir/ParseCache.txt"
  "Source/WebKit/qtwpe_autogen"
  "Tools/MiniBrowser/wpe/qt/CMakeFiles/qt-wpe-mini-browser_autogen.dir/AutogenUsed.txt"
  "Tools/MiniBrowser/wpe/qt/CMakeFiles/qt-wpe-mini-browser_autogen.dir/ParseCache.txt"
  "Tools/MiniBrowser/wpe/qt/qt-wpe-mini-browser_autogen"
  )
endif()
