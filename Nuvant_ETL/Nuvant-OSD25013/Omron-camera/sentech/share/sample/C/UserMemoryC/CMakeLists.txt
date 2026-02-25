cmake_minimum_required (VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-UserMemoryC C)

# UserMemoryC
set (TARGET "UserMemoryC")
doCompile(${TARGET} ${TARGET}.c)

