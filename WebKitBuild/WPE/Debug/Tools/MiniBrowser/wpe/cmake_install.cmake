# Install script for directory: /home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Tools/MiniBrowser/wpe

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/libexec/wpe-webkit-2.0/MiniBrowser" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/libexec/wpe-webkit-2.0/MiniBrowser")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/libexec/wpe-webkit-2.0/MiniBrowser"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/libexec/wpe-webkit-2.0/MiniBrowser")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/libexec/wpe-webkit-2.0" TYPE EXECUTABLE FILES "/home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/WebKitBuild/WPE/Debug/bin/MiniBrowser")
  if(EXISTS "$ENV{DESTDIR}/usr/local/libexec/wpe-webkit-2.0/MiniBrowser" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/libexec/wpe-webkit-2.0/MiniBrowser")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/local/libexec/wpe-webkit-2.0/MiniBrowser"
         OLD_RPATH "/home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/WebKitBuild/WPE/Debug/lib:/home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/../hajr/zig-out/lib:/home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/../z-net/rust_net/target/release:/home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/../Browser-db/bindings/target/release:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/llvm-strip" "$ENV{DESTDIR}/usr/local/libexec/wpe-webkit-2.0/MiniBrowser")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/WebKitBuild/WPE/Debug/Tools/MiniBrowser/wpe/CMakeFiles/MiniBrowser.dir/install-cxx-module-bmi-RelWithDebInfo.cmake" OPTIONAL)
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/WebKitBuild/WPE/Debug/Tools/MiniBrowser/wpe/qt/cmake_install.cmake")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/WebKitBuild/WPE/Debug/Tools/MiniBrowser/wpe/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
