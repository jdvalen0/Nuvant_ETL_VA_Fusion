cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-FeatureListC C)

# FeatureListC
set (TARGET "FeatureListC")
doCompile(${TARGET} ${TARGET}.c)

# FeatureListC-GUI
set (TARGET "FeatureListC-GUI")
doCompile(${TARGET} ${TARGET}.c)
