cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-GigEMulticastC C)

# GigEMulticastC
set (TARGET "GigEMulticastC")
doCompile(${TARGET} ${TARGET}.c)

# GigEMulticastC-GUI
set (TARGET "GigEMulticastC-GUI")
doCompile(${TARGET} ${TARGET}.c)
