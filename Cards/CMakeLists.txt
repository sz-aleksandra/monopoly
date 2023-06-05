cmake_minimum_required(VERSION 3.24)
project(cards)

set(CMAKE_CXX_STANDARD 17)

add_executable(cards show_cards.cpp cards.cpp cards.h)