add_library(libcmake-init
    config.cpp
    prompter.cpp
    generation_context.cpp
    formatter.cpp
)

target_include_directories(libcmake-init
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(libcmake-init PUBLIC Boost::json)

add_executable(cmake-init main.cpp)
target_link_libraries(cmake-init PRIVATE libcmake-init)

add_custom_command(TARGET cmake-init POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/../config.json
        $<TARGET_FILE_DIR:cmake-init>/config.json
    COMMENT "Copying configuration file to build directory"
)
