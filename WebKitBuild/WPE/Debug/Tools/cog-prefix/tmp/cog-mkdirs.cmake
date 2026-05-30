# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Tools/wpe/cog")
  file(MAKE_DIRECTORY "/home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/dependencies/WebKit/Tools/wpe/cog")
endif()
file(MAKE_DIRECTORY
  "/home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/WebKitBuild/WPE/Debug/Tools/cog-prefix/src/cog-build"
  "/home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/WebKitBuild/WPE/Debug/Tools/cog-prefix"
  "/home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/WebKitBuild/WPE/Debug/Tools/cog-prefix/tmp"
  "/home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/WebKitBuild/WPE/Debug/Tools/cog-prefix/src/cog-stamp"
  "/home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/WebKitBuild/WPE/Debug/Tools/cog-prefix/src"
  "/home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/WebKitBuild/WPE/Debug/Tools/cog-prefix/src/cog-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/WebKitBuild/WPE/Debug/Tools/cog-prefix/src/cog-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/WebKitBuild/WPE/Debug/Tools/cog-prefix/src/cog-stamp${cfgdir}") # cfgdir has leading slash
endif()
