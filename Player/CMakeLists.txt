cmake_minimum_required(VERSION 3.24)
project(player)

set(CMAKE_CXX_STANDARD 17)

add_executable(player main.cpp player.cpp player.h custom_exceptions.h player_driver.cpp player_driver.h ../Dices/dices.h ../Dices/dices.cpp)