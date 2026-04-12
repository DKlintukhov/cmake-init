add_executable(cmake-init_tests
    main.cpp
    config.cpp
    generation_context.cpp
    formatter.cpp
    location.cpp
)

target_link_libraries(cmake-init_tests
    PRIVATE
        libcmake-init
        Boost::unit_test_framework
)

add_test(NAME test_config             COMMAND cmake-init_tests --run_test=ConfigTestSuite)
add_test(NAME test_generation_context COMMAND cmake-init_tests --run_test=GenerationContextTestSuite)
add_test(NAME test_formatter          COMMAND cmake-init_tests --run_test=CMakeListsFormatterTestSuite)
add_test(NAME test_location           COMMAND cmake-init_tests --run_test=LocationTests)

add_custom_command(TARGET cmake-init_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/../config.json"
        "$<TARGET_FILE_DIR:cmake-init_tests>/config.json"
    COMMENT "Copying configuration file to test directory"
)
