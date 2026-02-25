cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-FeatureList C CXX)

# FeatureList 
set (TARGET "FeatureList")
doCompile(${TARGET} ${TARGET}.cpp ON OFF OFF)

# FeatureList-GUI
set (TARGET "FeatureList-GUI")
doCompile(${TARGET} ${TARGET}.cpp ON OFF ON)

