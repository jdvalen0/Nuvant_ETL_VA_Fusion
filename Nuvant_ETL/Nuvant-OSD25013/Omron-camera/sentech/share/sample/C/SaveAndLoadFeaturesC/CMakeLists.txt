cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-SaveAndLoadFeaturesC C)

# SaveAndLoadFeaturesC
set (TARGET "SaveAndLoadFeaturesC")
doCompile(${TARGET} ${TARGET}.c)

