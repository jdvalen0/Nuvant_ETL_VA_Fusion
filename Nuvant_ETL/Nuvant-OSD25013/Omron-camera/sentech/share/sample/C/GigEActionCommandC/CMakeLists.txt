cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-GigEActionCommandC C)

# GigEActionCommandC
set (TARGET "GigEActionCommandC")
doCompile(${TARGET} ${TARGET}.c)

# GigEActionCommandC-GUI
set (TARGET "GigEActionCommandC-GUI")
doCompile(${TARGET} ${TARGET}.c)
