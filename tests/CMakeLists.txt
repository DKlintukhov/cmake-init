add_executable(${TARGET}_test
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/config.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generation_context.cpp
    ${SRC}
)

target_include_directories(${TARGET}_test PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(${TARGET}_test PRIVATE Boost::unit_test_framework Boost::json)

add_test(NAME ${TARGET}_test COMMAND ${TARGET}_test)

# Copy config.json to the test output directory
add_custom_command(TARGET ${TARGET}_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/config.json"
        "$<TARGET_FILE_DIR:${TARGET}_test>"
)