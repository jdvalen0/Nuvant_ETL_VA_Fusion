cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-Graph C CXX)

# Graph
set (TARGET "Graph")
doCompile(${TARGET} ${TARGET}.cpp ON ON ON)

