cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-MultipleSystemsC C)

# MultipleSystemsC
set (TARGET "MultipleSystemsC")
doCompile(${TARGET} ${TARGET}.c)

# MultipleSystemsC-GUI
set (TARGET "MultipleSystemsC-GUI")
doCompile(${TARGET} ${TARGET}.c)
