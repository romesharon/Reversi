cmake_minimum_required(VERSION 3.8)
project(ass1)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp Board.h Board.cpp Rule.h ReverseRule.cpp ReverseRule.h GameShower.h Cell.cpp Cell.h CellManger.cpp CellManger.h GameFlow.cpp GameFlow.h Player.h HumanPlayer.cpp HumanPlayer.h Point.cpp Point.h)
add_executable(ass1 ${SOURCE_FILES})