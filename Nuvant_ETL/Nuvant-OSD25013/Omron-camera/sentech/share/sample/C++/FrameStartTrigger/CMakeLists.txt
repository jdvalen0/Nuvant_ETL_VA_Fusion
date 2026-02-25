cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-FrameStartTrigger C CXX)

# FrameStartTrigger
set (TARGET "FrameStartTrigger")
doCompile(${TARGET} ${TARGET}.cpp ON OFF OFF)

# FrameStartTrigger-GUI
set (TARGET "FrameStartTrigger-GUI")
doCompile(${TARGET} ${TARGET}.cpp ON OFF ON)

