cmake_minimum_required (VERSION 3.2)
project(SentechSDK-Samples C)

# CMakeLists.txt
# (C) 2018 OMRON-SENTECH CO., LTD
# Last Update: 2018/11/6

###############################################################################
# Main 
###############################################################################

set (SAMPLE_DIR
    AllocateStreamBuffersManuallyC
    AutoFunctionsC
    CameraSideROIC
    EventDeviceLostC
    FeatureListC
    FrameStartTriggerC
    GigEActionCommandC
    GigEConfigurationsC
    GigEMulticastC
    GrabC
    GrabCallbackC
    GrabCameraEventC
    GrabChunkImageC
    HostSideROIC
    MultipleCamerasC
    MultipleFiltersC
    MultipleSystemsC
    SaveAndLoadFeaturesC
    SaveAndLoadImageC
    SaveVideoC
    SingleFilterC
    UserMemoryC
    UserSetCtrlC
)

foreach(SAMPLE ${SAMPLE_DIR})
    add_subdirectory(${SAMPLE})
endforeach()
