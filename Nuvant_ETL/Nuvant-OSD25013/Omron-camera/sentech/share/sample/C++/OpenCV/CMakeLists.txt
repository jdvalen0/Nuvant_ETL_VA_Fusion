cmake_minimum_required (VERSION 3.2)
include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt.in)

project(SentechSDK-Sample-OpenCV C CXX)

# OpenCV 
find_package(OpenCV)
if (OpenCV_FOUND)
    set (StApi_Library ${StApi_TL_Library})
    set (TARGET "OpenCV")
    set (SOURCES "${TARGET}.cpp")
    add_executable(${TARGET} ${SOURCES})
    target_link_libraries(${TARGET} ${Genicam_Library} ${StApi_Library} ${OpenCV_LIBS})
    set_target_properties(${TARGET}
        PROPERTIES LINK_FLAGS "${Genicam_LinkFlag} ${StApi_LinkFlag}")
else()
    message("**OpenCV package is not found. This compilation does not include OpenCV .")
    message("  To compile, please install OpenCV development package.") 
endif()
