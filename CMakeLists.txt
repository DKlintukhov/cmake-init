cmake_minimum_required(VERSION 4.1.1)

if (PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed. You should create separate directory for build files")
endif()

option(ENABLE_TESTS "Enable tests" ON)
option(ENABLE_CLANG_TIDY "Enable CLang tidy" ON)
option(ENABLE_CPPCHECK "Enable Cppcheck" ON)

set(TARGET cmake-init)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

project(
    ${TARGET}
    VERSION 0.1.0
    HOMEPAGE_URL "https://github.com/DKlintukhov/cmake-init"
    DESCRIPTION "A CMake C++ project generator with professional tooling integration."
    LANGUAGES C CXX
)

set(PACKAGE_VERSION ${PROJECT_VERSION})
set(PACKAGE_NAME ${PROJECT_NAME})
set(PACKAGE_HOMEPAGE_URL ${PROJECT_HOMEPAGE_URL})
set(PACKAGE_BUGREPORT_URL ${PROJECT_HOMEPAGE_URL}/issues)
set(PACKAGE_RELEASES_URL ${PROJECT_HOMEPAGE_URL}/releases)

find_package(Threads REQUIRED)

add_executable(${TARGET} src/main.cpp)
target_include_directories(${TARGET} PRIVATE include)
target_link_libraries(${TARGET} PRIVATE Threads::Threads)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE 
        PROPERTY STRINGS 
        "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/bin)

set_target_properties(${TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/bin
)

if(ENABLE_TESTS)
    enable_testing()
   add_subdirectory(tests)
endif()

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if(CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
        message(STATUS "Clang-tidy enabled: ${CLANG_TIDY_EXE}")
    else()
        message(WARNING "Clang-tidy requested but executable not found")
    endif()
endif()

if(ENABLE_CPPCHECK)
    include(cmake/cppcheck.cmake)
endif()
