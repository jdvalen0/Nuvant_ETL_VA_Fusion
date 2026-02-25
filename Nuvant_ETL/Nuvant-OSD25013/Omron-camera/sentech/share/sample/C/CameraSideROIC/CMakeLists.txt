cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-CameraSideROIC C)

# CameraSideROIC
set (TARGET "CameraSideROIC")
doCompile(${TARGET} ${TARGET}.c)

# CameraSideROIC-GUI
set (TARGET "CameraSideROIC-GUI")
doCompile(${TARGET} ${TARGET}.c)
