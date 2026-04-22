find_program(CLANG_FORMAT_EXE NAMES clang-format)
if(NOT CLANG_FORMAT_EXE)
    message(WARNING "Clang-format executable not found")
    return()
endif()

message(STATUS "Clang-format found: ${CLANG_FORMAT_EXE}")

file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/include/*.h"
)

add_custom_target(clang-format
    COMMAND ${CLANG_FORMAT_EXE} -i ${SOURCE_FILES}
    COMMENT "Running clang-format"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)