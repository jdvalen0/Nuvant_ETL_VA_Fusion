cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-MultipleFiltersC C)

# MultipleFiltersC
set (TARGET "MultipleFiltersC")
doCompile(${TARGET} ${TARGET}.c)

# MultipleFiltersC-GUI
set (TARGET "MultipleFiltersC-GUI")
doCompile(${TARGET} ${TARGET}.c)
