add_executable(tests
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(tests PRIVATE Boost::unit_test_framework Boost::json)

add_test(NAME AllTests COMMAND tests)
