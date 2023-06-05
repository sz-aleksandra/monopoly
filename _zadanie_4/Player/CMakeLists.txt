cmake_minimum_required(VERSION 3.24)
project(player_task4)

set(CMAKE_CXX_STANDARD 17)

# this command should be used while building in debug mode, else comment it
add_compile_definitions(DEBUG)

add_executable(player_task4 main.cpp player.cpp player.h human_bot.cpp)
add_subdirectory(Google_tests)