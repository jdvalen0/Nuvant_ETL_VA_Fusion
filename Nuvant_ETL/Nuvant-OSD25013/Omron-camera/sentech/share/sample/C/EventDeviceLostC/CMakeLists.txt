cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-EventDeviceLostC C)

# AutoFUnctionsC
set (TARGET "EventDeviceLostC")
doCompile(${TARGET} ${TARGET}.c)

