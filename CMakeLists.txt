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

add_subdirectory(${CMAKE_BINARY_DIR}/lib)

add_library(canvas Canvas.cpp) 
add_library(frame Frame.cpp)

add_executable(runTests test/tests.cpp test/test_canvas.cpp test/test_frame.cpp)
target_link_libraries(runTests GTest::gtest_main frame canvas)

add_library(test_canvas test/test_canvas.cpp)
add_library(test_frame test/test_frame.cpp)
target_link_libraries(runTests test_canvas test_frame)

include(GoogleTest)
gtest_discover_tests(runTests)

# Prepare also main
add_executable(main main.cpp)
target_link_libraries(main frame canvas)
