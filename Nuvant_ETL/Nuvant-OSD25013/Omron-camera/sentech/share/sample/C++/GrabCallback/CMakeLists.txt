cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-GrabCallback C CXX)

# GrabCallback
set (TARGET "GrabCallback")
doCompile(${TARGET} ${TARGET}.cpp ON OFF OFF)

# GrabCallback-GUI (GrabCallback with ENABLED_ST_GUI)
set (TARGET2 "GrabCallback-GUI")
doCompile(${TARGET2} GrabCallback.cpp ON OFF ON)
target_compile_definitions(${TARGET2} PRIVATE ENABLED_ST_GUI=1)
