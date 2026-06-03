# -----------------------------------------------------------------------------
# Determine CMake version and build type.
# -----------------------------------------------------------------------------
# NOTE: cmake_minimum_required() and project() *MUST* be the two first commands
# used, see https://cmake.org/cmake/help/v3.3/command/project.html -- the
# latter in particular handles loading a bunch of shared CMake definitions
# and loading the cross-compilation settings from CMAKE_TOOLCHAIN_FILE.

cmake_minimum_required(VERSION 3.20)

# --- Zawra Project Overrides ---
# Silence noisy compiler warnings to save CPU cycles
add_compile_options("-Wno-#warnings" "-Wno-unnecessary-virtual-specifier")
# Use BOTH ccache and sccache (chained) for maximum caching efficiency
set(CMAKE_C_COMPILER_LAUNCHER "ccache;sccache" CACHE STRING "" FORCE)
set(CMAKE_CXX_COMPILER_LAUNCHER "ccache;sccache" CACHE STRING "" FORCE)
# Use the ultra-fast mold linker instead of LLD
add_link_options("-fuse-ld=mold")

# Disable WebKit's default Bubblewrap sandbox to prevent conflicts with Hajr
set(ENABLE_BUBBLEWRAP_SANDBOX OFF CACHE BOOL "Toggle Bubblewrap sandbox support" FORCE)
# -------------------------------
project(WebKit)

# Remove this cmake_policy() after upgrading cmake_minimum_required() to 3.20.
if (${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.20")
    cmake_policy(SET CMP0116 OLD)
endif ()

# -----------------------------------------------------------------------------
# Common configuration
#------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Source/cmake")
include(WebKitCommon)

# -----------------------------------------------------------------------------
# Enable API unit tests and create a target for the test runner
# -----------------------------------------------------------------------------
if (ENABLE_API_TESTS)
    enable_testing()
endif ()

# -----------------------------------------------------------------------------
# Add module directories
# -----------------------------------------------------------------------------
add_subdirectory(Source)

# -----------------------------------------------------------------------------
# Add tools
# -----------------------------------------------------------------------------
if (ENABLE_TOOLS)
    add_subdirectory(Tools)
endif ()

if (DEVELOPER_MODE)
    # add_subdirectory(PerformanceTests)
endif ()

# -----------------------------------------------------------------------------
# Print the features list last, for maximum visibility.
# -----------------------------------------------------------------------------
PRINT_WEBKIT_OPTIONS()
