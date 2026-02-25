cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-Grab C CXX)

# SaveVideo
set (TARGET "SaveVideo")
doCompile(${TARGET} ${TARGET}.cpp ON ON OFF)

# SaveVideo-GUI
set (TARGET "SaveVideo-GUI")
doCompile(${TARGET} ${TARGET}.cpp ON ON ON)

