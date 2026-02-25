cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-MultipleSystems C CXX)

# MultipleSystems
set (TARGET "MultipleSystems")
doCompile(${TARGET} ${TARGET}.cpp ON OFF OFF)

# MultipleSystems-GUI
set (TARGET "MultipleSystems-GUI")
doCompile(${TARGET} ${TARGET}.cpp ON ON ON)

