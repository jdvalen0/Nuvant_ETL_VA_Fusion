cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-FrameStartTriggerC C)

# FrameStartTriggerC
set (TARGET "FrameStartTriggerC")
doCompile(${TARGET} ${TARGET}.c)

# FrameStartTriggerC-GUI
set (TARGET "FrameStartTriggerC-GUI")
doCompile(${TARGET} ${TARGET}.c)
