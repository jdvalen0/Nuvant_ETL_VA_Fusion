cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-SingleConverter C CXX)

# SingleConverter
set (TARGET "SingleConverter")
doCompile(${TARGET} ${TARGET}.cpp ON ON OFF)

# SingleConverter-GUI
set (TARGET "SingleConverter-GUI")
doCompile(${TARGET} ${TARGET}.cpp ON ON ON)

