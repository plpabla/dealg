# cmake ..
# make
# ./runTests

cmake_minimum_required(VERSION 2.6)
project(runTest)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_library(canvas Canvas.cpp) 
add_library(frame Frame.cpp)
add_library(test_canvas test/test_canvas.cpp)

add_executable(runTests test/tests.cpp test/test_canvas.cpp test/test_frame.cpp)
target_link_libraries(runTests GTest::gtest_main frame canvas test_canvas)

include(GoogleTest)
gtest_discover_tests(runTests)

# Prepare also main
add_executable(main main.cpp)
target_link_libraries(main frame canvas)
