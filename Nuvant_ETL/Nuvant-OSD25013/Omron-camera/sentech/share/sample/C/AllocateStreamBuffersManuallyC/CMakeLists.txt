cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-AllocateStreamBuffersManuallyC C)

# AllocateStreamBuffersManuallyC
set (TARGET "AllocateStreamBuffersManuallyC")
doCompile(${TARGET} ${TARGET}.c)

# AllocateStreamBuffersManuallyC-GUI
set (TARGET "AllocateStreamBuffersManuallyC-GUI")
doCompile(${TARGET} ${TARGET}.c)
