cmake_minimum_required(VERSION 3.10)
set(COMET_DIR $ENV{COMET_DIR})
project(simple LANGUAGES CXX)
add_executable(main main.cpp)

set(BUILD_SHARED_LIBS OFF)
target_link_libraries(main arith_s)
target_include_directories(main PUBLIC ${COMET_DIR}/include)
target_link_directories(main PUBLIC ${COMET_DIR}/lib)
