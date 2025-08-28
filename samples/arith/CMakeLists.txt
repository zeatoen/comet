cmake_minimum_required(VERSION 3.10)
project(NoOverflowArithmetic LANGUAGES CXX)
add_library(arith_d SHARED arith.cpp)
add_library(arith_s arith.cpp)
