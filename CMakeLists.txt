# cmake ..
# make
# ./runTests

cmake_minimum_required(VERSION 2.6)
project(dealg)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_library(baner Baner.cpp)
add_library(canvas Canvas.cpp) 
add_library(frame Frame.cpp)
add_library(game Game.cpp)
add_library(inputwindow InputWindow.cpp)
add_library(item Item.cpp) 
add_library(stock Stock.cpp)
add_library(system System.cpp)

add_executable(runTests 
  test/tests.cpp 
  test/test_canvas.cpp 
  test/test_frame.cpp 
  test/test_stock.cpp 
  test/test_listwindow.cpp
  test/test_baner.cpp
  test/test_helpers.cpp
  test/test_system.cpp
  test/test_inputwindow.cpp
  test/test_game.cpp
)

target_link_libraries(runTests 
  GTest::gtest_main 
  frame 
  canvas 
  item 
  stock
  baner
  system
  inputwindow
  game
  ${CURSES_LIBRARIES}
)

include(GoogleTest)
gtest_discover_tests(runTests)

# Prepare also main
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} 
  ${CURSES_LIBRARIES}  
  stock
  inputwindow
  game
  baner
  system
  canvas
  item
  frame
  )

