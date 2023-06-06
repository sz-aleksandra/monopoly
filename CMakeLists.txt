cmake_minimum_required(VERSION 3.24)
project(monopoly)

set(CMAKE_CXX_STANDARD 17)

# choose one of these commands below to change mode
add_compile_definitions(DEBUG=true)
# add_compile_definitions(DEBUG=false)

# uncomment this line if you work in clion on linux (clearing window)
# add_compile_definitions(dummy=true)

include_directories(ConsoleView Menu Player Board Dices Cards tests/Google)

add_subdirectory(Menu)
add_subdirectory(Player)
add_subdirectory(Board)
add_subdirectory(Dices)
add_subdirectory(Cards)
add_subdirectory(tests/Google)

file(GLOB MY_FILES "*.txt")
file(COPY ${MY_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})