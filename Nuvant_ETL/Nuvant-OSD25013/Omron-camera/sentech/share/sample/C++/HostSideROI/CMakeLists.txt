cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-HostSideROI C CXX)

# HostSideROI
set (TARGET "HostSideROI")
doCompile(${TARGET} ${TARGET}.cpp ON OFF ON)
