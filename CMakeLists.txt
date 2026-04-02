cmake_minimum_required(VERSION 3.31)

# Project metadata
project(
    cmake-init
    VERSION 0.1.0
    HOMEPAGE_URL "https://github.com/DKlintukhov/cmake-init"
    DESCRIPTION "A CMake C++ project generator following professional UNIX conventions."
    LANGUAGES C CXX
)

if (PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds are not allowed. Please create a separate directory for build files.")
endif()

# Global Options
option(ENABLE_TESTS "Enable tests" ON)
option(ENABLE_CLANG_TIDY "Enable Clang-Tidy" OFF)
option(ENABLE_CPPCHECK "Enable Cppcheck" OFF)

# Build settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()

# Output directories following UNIX conventions
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# External dependencies
include(FetchContent)
include(cmake/boost.cmake)

# Core Logic Library (libcmake-init)
# This library contains all the business logic, making it easily testable.
add_library(libcmake-init
    src/config.cpp
    src/prompter.cpp
    src/generation_context.cpp
    src/formatter.cpp
)

target_include_directories(libcmake-init
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        src
)

# Link Boost::json to the library (publicly if headers are exposed in include/)
target_link_libraries(libcmake-init PUBLIC Boost::json)

# CLI Executable (cmake-init)
add_executable(cmake-init src/main.cpp)
target_link_libraries(cmake-init PRIVATE libcmake-init)

# Resources/Data
add_custom_command(TARGET cmake-init POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/config.json"
        "$<TARGET_FILE_DIR:cmake-init>/config.json"
    COMMENT "Copying configuration file to build directory"
)

# Tooling Integration
if(ENABLE_CLANG_TIDY)
  find_program(CLANG_TIDY_EXE NAMES clang-tidy)
  if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
  else()
    message(WARNING "Clang-tidy requested but executable not found")
  endif()
endif()

if(ENABLE_CPPCHECK)
  include(cmake/cppcheck.cmake)
endif()

# Testing
if(ENABLE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
