cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-GrabCameraEventC C)

# GrabCameraEventC
set (TARGET "GrabCameraEventC")
doCompile(${TARGET} ${TARGET}.c)

# GrabCameraEventC-GUI
set (TARGET "GrabCameraEventC-GUI")
doCompile(${TARGET} ${TARGET}.c)
