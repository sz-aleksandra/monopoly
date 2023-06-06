cmake_minimum_required(VERSION 3.24)
project(monopoly)

set(CMAKE_CXX_STANDARD 17)

# choose one of these commands below to change mode
add_compile_definitions(DEBUG=true)
# add_compile_definitions(DEBUG=false)

include_directories(Player Board Dices Cards tests/Google)

add_subdirectory(Player)
add_subdirectory(Board)
add_subdirectory(Dices)
add_subdirectory(Cards)
add_subdirectory(tests/Google)