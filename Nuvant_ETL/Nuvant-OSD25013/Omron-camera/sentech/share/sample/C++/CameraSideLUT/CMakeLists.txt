cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-CameraSideLUT C CXX)

# CameraSideLUT
set (TARGET "CameraSideLUT")
doCompile(${TARGET} ${TARGET}.cpp ON ON ON)

