cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-SaveVideoC C)

# SaveVideoC
set (TARGET "SaveVideoC")
doCompile(${TARGET} ${TARGET}.c)

# SaveVideoC-GUI
set (TARGET "SaveVideoC-GUI")
doCompile(${TARGET} ${TARGET}.c)
