cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-GigEMulticast C CXX)

# GigEMulticast
set (TARGET "GigEMulticast")
doCompile(${TARGET} ${TARGET}.cpp ON OFF OFF)

# GigEMulticast-GUI
set (TARGET "GigEMulticast-GUI")
doCompile(${TARGET} ${TARGET}.cpp ON OFF ON)

