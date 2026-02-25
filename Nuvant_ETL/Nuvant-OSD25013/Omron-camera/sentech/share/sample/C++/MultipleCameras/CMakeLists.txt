cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-MultipleCameras C CXX)

# MultipleCameras
set (TARGET "MultipleCameras")
doCompile(${TARGET} ${TARGET}.cpp ON OFF OFF)

