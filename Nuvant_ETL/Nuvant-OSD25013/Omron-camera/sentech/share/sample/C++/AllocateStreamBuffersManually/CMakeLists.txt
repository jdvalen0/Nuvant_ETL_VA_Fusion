cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-AllocateStreamBuffersManually C CXX)

# AllocateStreamBuffersManually
set (TARGET "AllocateStreamBuffersManually")
doCompile(${TARGET} ${TARGET}.cpp ON OFF OFF)

# AllocateStreamBuffersManually-GUI
set (TARGET "AllocateStreamBuffersManually-GUI")
doCompile(${TARGET} ${TARGET}.cpp ON OFF ON)
