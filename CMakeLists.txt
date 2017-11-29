cmake_minimum_required(VERSION 3.8)
project(ass1)

set(CMAKE_CXX_STANDARD 98)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)


set(SOURCE_FILES main.cpp Board.h Board.cpp Rule.h ReverseRule.cpp ReverseRule.h GameShower.h Cell.cpp Cell.h CellManger.cpp CellManger.h GameFlow.cpp GameFlow.h Player.h HumanPlayer.cpp HumanPlayer.h Point.cpp Point.h AIPlayer.cpp AIPlayer.h tests/PointT.cpp tests/Gtest_main.cpp tests/BoardTest.cpp tests/HumanTest.cpp tests/AiTest.cpp tests/CellTest.cpp tests/CellMangerTest.cpp tests/ReverseRuleTest.cpp)
add_executable(ass1 ${SOURCE_FILES} tests/PointT.cpp tests/BoardTest.cpp tests/HumanTest.cpp tests/AiTest.cpp)
target_link_libraries(ass1 gtest gtest_main)

