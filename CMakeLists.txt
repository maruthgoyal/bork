project(bork)
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
include_directories (${CMAKE_SOURCE_DIR}/stdlib ${CMAKE_SOURCE_DIR}/parser ${CMAKE_SOURCE_DIR}/eval ${CMAKE_SOURCE_DIR}/util)

add_library(bork_lib SHARED ${CMAKE_SOURCE_DIR}/stdlib/stdlib.cpp ${CMAKE_SOURCE_DIR}/eval/eval.cpp ${CMAKE_SOURCE_DIR}/parser/parser.cpp ${CMAKE_SOURCE_DIR}/util/pprint.cpp)


add_executable(bork bork.cpp)
target_link_libraries(bork bork_lib)
