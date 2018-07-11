cmake_minimum_required(VERSION 3.1)
project(chat)
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )

include_directories(${PROJECT_SOURCE_DIR})
message("Headers generados: ${PROJECT_SOURCE_DIR}")

add_subdirectory(src/server)
add_subdirectory(src/client)
