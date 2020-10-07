# CMake config file for unit tests
# Requiring V 3.10 for gtest_discover_tests
cmake_minimum_required(VERSION 3.10)
find_package(OpenCV REQUIRED)
find_package(GTest REQUIRED)

# finds all .cpp files under this directory (./test) and add them to executable
file(GLOB_RECURSE tests "*.cpp")
file(GLOB_RECURSE source "../src/*.cpp")
add_executable(splitwebp_tests ${tests} ${source})

include_directories("../3rdparty/libwebp/include")

# Link gtest libraries
target_link_libraries(splitwebp_tests ${OpenCV_LIBS})
target_link_libraries(splitwebp_tests webp webpdemux pthread)
target_link_libraries(splitwebp_tests GTest::GTest GTest::Main)

set(CTEST_OUTPUT_ON_FAILURE 1)

# Find all tests in all .cpp files and convert to CTests
gtest_discover_tests(splitwebp_tests)