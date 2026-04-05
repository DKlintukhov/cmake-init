add_library(cmake-init-headers INTERFACE)

target_include_directories(cmake-init-headers
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)
