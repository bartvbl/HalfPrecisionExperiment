cmake_minimum_required(VERSION 3.8)

project(halftest)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 17)


set(CMAKE_SUPPRESS_REGENERATION TRUE) # Suppresses ZERO_CHECK



add_executable(halftest main.cpp)
