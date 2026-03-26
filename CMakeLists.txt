cmake_minimum_required(VERSION 3.31)

project(
    cmake-init
    VERSION 0.1.0
    HOMEPAGE_URL "https://github.com/DKlintukhov/cmake-init"
    DESCRIPTION "A CMake C++ project generator with professional tooling integration."
    LANGUAGES C CXX
)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed. You should create separate directory for build files")
endif()

# Global build options
option(ENABLE_TESTS "Enable tests" ON)
option(ENABLE_CLANG_TIDY "Enable CLang tidy" ON)
option(ENABLE_CPPCHECK "Enable Cppcheck" ON)

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()

# Package metadata variables
set(PACKAGE_VERSION ${PROJECT_VERSION})
set(PACKAGE_NAME ${PROJECT_NAME})
set(PACKAGE_HOMEPAGE_URL ${PROJECT_HOMEPAGE_URL})
set(PACKAGE_BUGREPORT_URL ${PROJECT_HOMEPAGE_URL}/issues)
set(PACKAGE_RELEASES_URL ${PROJECT_HOMEPAGE_URL}/releases)

# Compiler standards and flags
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/bin)

include(FetchContent)

# Fetch Boost first since both our main executable and tests need it
include(cmake/boost.cmake)

# Setup main executable
set(TARGET cmake-init)
set(SRC ${CMAKE_SOURCE_DIR}/src/config.cpp)
add_executable(${TARGET} src/main.cpp ${SRC})

# Target configuration
target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src ${Boost_SOURCE_DIR})

find_package(Threads REQUIRED)
target_link_libraries(${TARGET} PRIVATE 
    Threads::Threads 
    Boost::json
)

# Copy config.json to the output directory
add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/config.json"
        "$<TARGET_FILE_DIR:${TARGET}>"
)

# Optional Tooling
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

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
