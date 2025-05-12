# See: 
# https://github.com/ElectricRCAircraftGuy/eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2/blob/main/CMakeLists.txt

cmake_minimum_required(VERSION 3.23)
project(Poll_server_demo)

# enable CMake's `ctest` unit testing, which also support gtest
enable_testing()

# Get MSYSTEM environment variable and define it for C and C++ code. 
# - Example `MSYSTEM` values in MSYS2 on Windows are as follows. 
#   See my answer here: https://stackoverflow.com/a/79201770/4561887
#   1. MSYS
#   2. MINGW32
#   3. MINGW64
#   4. UCRT64
#   5. CLANG64
#   6. CLANG32
#   7. CLANGARM64
# - See what `MSYSTEM` is set to by searching 
#   "build/Release/compile_commands.json", for instance, for `-DMSYSTEM` 
#   after building.
set(MSYSTEM_VALUE $ENV{MSYSTEM})
if(MSYSTEM_VALUE)
    add_compile_definitions("MSYSTEM_${MSYSTEM_VALUE}")
else()
    add_compile_definitions("MSYSTEM_NOTSET")
endif()

# Generate a compile_commands.json file for use with clangd. 
# - See: https://cmake.org/cmake/help/latest/variable/CMAKE_EXPORT_COMPILE_COMMANDS.html
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)
target_compile_options(compiler_flags INTERFACE -Wall -Wextra -Werror -O3)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "  Debug build")
    add_compile_options(-ggdb -O0)
endif()

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

# Add all include directories
include_directories(
    # NA
)

add_executable(poll_server
    "main.cpp"
)

target_link_libraries(poll_server PUBLIC compiler_flags)

# include(unittests.cmake)
