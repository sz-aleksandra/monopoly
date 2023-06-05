cmake_minimum_required(VERSION 3.24)
project(player)

set(CMAKE_CXX_STANDARD 17)

# choose one of these commands below to change mode
add_compile_definitions(DEBUG=true)
# add_compile_definitions(DEBUG=false)

add_subdirectory(Player)
add_subdirectory(Dices)
add_subdirectory(tests/Google)