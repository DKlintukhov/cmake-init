set(BOOST_VERSION 1.90.0)

set(BOOST_INCLUDE_LIBRARIES test json)
set(BOOST_ENABLE_CMAKE ON)

FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-${BOOST_VERSION}/boost-${BOOST_VERSION}-cmake.zip
    USES_TERMINAL_DOWNLOAD TRUE
    DOWNLOAD_NO_EXTRACT FALSE
)

FetchContent_MakeAvailable(Boost)
