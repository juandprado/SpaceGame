cmake_minimum_required(VERSION 3.3)
project(SpaceGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_custom_target(main COMMAND make -C ${PROJECT_SOURCE_DIR}
                                       CLION_EXE_DIR=${PROJECT_BINARY_DIR})