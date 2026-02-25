cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-MultipleFilters C CXX)

# MultipleFilters
set (TARGET "MultipleFilters")
doCompile(${TARGET} ${TARGET}.cpp ON ON OFF)

# MultipleFilters-GUI
set (TARGET "MultipleFilters-GUI")
doCompile(${TARGET} ${TARGET}.cpp ON ON ON)

