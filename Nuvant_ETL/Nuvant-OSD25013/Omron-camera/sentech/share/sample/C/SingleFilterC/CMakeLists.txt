cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-SingleFilterC C)

# SingleFilterC
set (TARGET "SingleFilterC")
doCompile(${TARGET} ${TARGET}.c)

# SingleFilterC-GUI
set (TARGET "SingleFilterC-GUI")
doCompile(${TARGET} ${TARGET}.c)
