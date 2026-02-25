cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-GrabC C)

# GrabC
set (TARGET "GrabC")
doCompile(${TARGET} ${TARGET}.c)

# GrabC-GUI
set (TARGET "GrabC-GUI")
doCompile(${TARGET} ${TARGET}.c)
