cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-SaveAndLoadFeatures C CXX)

# SaveAndLoadFeatures
set (TARGET "SaveAndLoadFeatures")
doCompile(${TARGET} ${TARGET}.cpp ON OFF OFF)

