cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-EventDeviceLost C CXX)

# EventDeviceLost
set (TARGET "EventDeviceLost")
doCompile(${TARGET} ${TARGET}.cpp ON OFF OFF)

