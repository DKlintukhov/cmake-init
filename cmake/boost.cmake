FetchContent_Declare(
  Boost
  URL https://github.com/boostorg/boost/releases/download/boost-1.90.0/boost-1.90.0-cmake.zip
  USES_TERMINAL_DOWNLOAD TRUE
  DOWNLOAD_NO_EXTRACT FALSE
)
set(BOOST_INCLUDE_LIBRARIES test)
FetchContent_MakeAvailable(Boost)
