cmake_minimum_required(VERSION 3.24)
project(menu)

set(CMAKE_CXX_STANDARD 17)

add_executable(menu show_menu.cpp menu.h menu.cpp ../Player/player.cpp ../Player/player.h ../Dices/dices.cpp ../Dices/dices.h)