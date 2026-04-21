find_program(CPPCHECK_EXE NAMES cppcheck)
if(CPPCHECK_EXE)
    message(STATUS "Cppcheck found: ${CPPCHECK_EXE}")

    add_custom_target(cppcheck
        COMMAND ${CPPCHECK_EXE}
            --enable=all
            --suppress=missingIncludeSystem
            --project=${CMAKE_BINARY_DIR}/compile_commands.json
        COMMENT "Running cppcheck static analysis"
        VERBATIM
    )
else()
    message(WARNING "Cppcheck requested but executable not found")
endif()
