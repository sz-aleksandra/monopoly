cmake_minimum_required(VERSION 3.24)
project(dices)

set(CMAKE_CXX_STANDARD 17)

add_executable(dices show_dices.cpp dices.cpp dices.h)