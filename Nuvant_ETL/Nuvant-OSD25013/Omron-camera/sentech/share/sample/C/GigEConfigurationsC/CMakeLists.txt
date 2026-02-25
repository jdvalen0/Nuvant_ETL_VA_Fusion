cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-GigEConfigurationsC C)

# GigEConfigurationsC
set (TARGET "GigEConfigurationsC")
doCompile(${TARGET} ${TARGET}.c)

