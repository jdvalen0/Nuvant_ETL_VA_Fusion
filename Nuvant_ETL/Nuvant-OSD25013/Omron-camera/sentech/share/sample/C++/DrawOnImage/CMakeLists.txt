cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-DrawOnImage C CXX)

# DrawOnImage
set (TARGET "DrawOnImage")
doCompile(${TARGET} ${TARGET}.cpp ON OFF ON)

