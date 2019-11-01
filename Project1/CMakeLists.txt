cmake_minimum_required(VERSION 3.15)
project(Project1)

set(CMAKE_CXX_STANDARD 11)

add_library(Project1 cmake-build-debug/Dictionary.cpp cmake-build-debug/Dictionary.h cmake-build-debug/dictionary_test.cpp cmake-build-debug/dictionary_test.h)