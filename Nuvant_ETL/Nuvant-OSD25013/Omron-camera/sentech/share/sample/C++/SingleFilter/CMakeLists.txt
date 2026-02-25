cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-SingleFilter C CXX)

# SingleFilter
set (TARGET "SingleFilter")
doCompile(${TARGET} ${TARGET}.cpp ON ON OFF)

# SingleFilter-GUI
set (TARGET "SingleFilter-GUI")
doCompile(${TARGET} ${TARGET}.cpp ON ON ON)

