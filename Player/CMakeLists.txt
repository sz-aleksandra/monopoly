cmake_minimum_required(VERSION 3.24)
project(player)

set(CMAKE_CXX_STANDARD 17)

# this command should be used while building in debug mode, else comment it
add_compile_definitions(DEBUG)

add_executable(player main.cpp player.cpp player.h human_bot.cpp)
# add_subdirectory(Google_tests)