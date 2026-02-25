cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-AutoFunctions C CXX)

# CameraSideROI
set (TARGET "CameraSideROI")
doCompile(${TARGET} ${TARGET}.cpp ON OFF OFF)

# CameraSideROI-GUI
set (TARGET "CameraSideROI-GUI")
doCompile(${TARGET} ${TARGET}.cpp ON OFF ON)

