cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-GigEActionCommand C CXX)

# GigEActionCommand
set (TARGET "GigEActionCommand")
doCompile(${TARGET} ${TARGET}.cpp ON OFF OFF)

# GigEActionCommand-GUI
set (TARGET "GigEActionCommand-GUI")
doCompile(${TARGET} ${TARGET}.cpp ON OFF ON)

