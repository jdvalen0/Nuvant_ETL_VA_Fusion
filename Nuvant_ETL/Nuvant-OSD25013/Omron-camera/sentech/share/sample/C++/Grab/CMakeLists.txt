cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-Grab C CXX)

# Grab
set (TARGET "Grab")
doCompile(${TARGET} ${TARGET}.cpp ON OFF OFF)

# Grab-GUI
set (TARGET "Grab-GUI")
doCompile(${TARGET} ${TARGET}.cpp ON OFF ON)

