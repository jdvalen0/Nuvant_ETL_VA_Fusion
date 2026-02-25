cmake_minimum_required (VERSION 3.2)
project(SentechSDK-Samples C CXX)

# CMakeLists.txt
# (C) 2017 OMRON-SENTECH CO., LTD
# Last Update: 2017/8/3

###############################################################################
# Main 
###############################################################################

set (SAMPLE_DIR
    AllocateStreamBuffersManually
    AutoFunctions
    CameraSideROI
    CameraSideLUT
    DrawOnImage
    EventDeviceLost
    FeatureList
    FrameStartTrigger
    GigEActionCommand
    GigEConfigurations
    GigEMulticast
    Grab
    GrabCallback
    GrabCameraEvent
    GrabChunkImage
    Graph
    HostSideROI
    MultipleCameras
    MultipleFilters
    MultipleSystems
    OpenCV
    OverlayQt
    SaveAndLoadFeatures
    SaveAndLoadImage
    SaveVideo
    SingleConverter
    SingleFilter
    StViewerQt
    UserMemory
    UserSetCtrl
)

foreach(SAMPLE ${SAMPLE_DIR})
    add_subdirectory(${SAMPLE})
endforeach()
