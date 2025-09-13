find_program(CPPCHECK_EXE NAMES cppcheck)
if(CPPCHECK_EXE)
    message(STATUS "Cppcheck found: ${CPPCHECK_EXE}")
    
    # Run cppcheck during build
    add_custom_target(${TARGET}_cppcheck
        COMMAND ${CPPCHECK_EXE}
            --enable=all
            --suppress=missingIncludeSystem
            --project=${CMAKE_BINARY_DIR}/compile_commands.json
        COMMENT "Running cppcheck static analysis"
        VERBATIM
    )
    
    add_dependencies(${TARGET} ${TARGET}_cppcheck)
else()
    message(WARNING "Cppcheck requested but executable not found")
endif()
