cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(ood LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(catch2 INTERFACE)
target_include_directories(catch2 INTERFACE catch2/)

add_library(fakeit INTERFACE)
target_include_directories(fakeit INTERFACE fakeit/)

add_subdirectory(lab1)
add_subdirectory(lab2)
add_subdirectory(lab3)
add_subdirectory(lab4)
add_subdirectory(lab5)
add_subdirectory(lab6)
add_subdirectory(lab7)
add_subdirectory(lab8)
add_subdirectory(lab9)