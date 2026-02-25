#SAMPLEPATH: location of the sample code directories with trailing /
#OTUPUTPATH: path of the compile results with trailing /
SAMPLEPATH:=${STAPI_ROOT_PATH}/share/sample/C++/
OUTPUTPATH:=./

OPENCV_EXISTS=$(shell if pkg-config opencv --exists; then echo 1; elif pkg-config opencv4 --exists; then echo 2; else echo 0;fi;)

ifeq ($(CXX),)
	CXX:=g++
endif

ifeq ($(INCFLAGS),)
	INCFLAGS:=-I${STAPI_ROOT_PATH}/include/GenICam \
		-I${STAPI_ROOT_PATH}/include/StApi
endif

ifeq ($(LIBFLAGS),)
	LIBFLAGS:=-L${STAPI_ROOT_PATH}/lib \
			-L${STAPI_ROOT_PATH}/lib/GenICam \
			-lGCBase \
			-lGenApi \
			-lpthread
endif

ifeq ($(COMPILEFLAGS),)
	COMPILEFLAGS:=-Wall -Wextra --pedantic -Wno-unknown-pragmas -Wno-switch \
		-Wno-unused-but-set-variable -Wno-pointer-arith -Wno-unused-parameter \
		-std=c++11
endif

all: $(OUTPUTPATH)AllocateStreamBuffersManually \
	$(OUTPUTPATH)AllocateStreamBuffersManually-GUI \
	$(OUTPUTPATH)AutoFunctions \
	$(OUTPUTPATH)CameraSideLUT \
	$(OUTPUTPATH)CameraSideROI \
	$(OUTPUTPATH)CameraSideROI-GUI \
	$(OUTPUTPATH)DrawOnImage \
	$(OUTPUTPATH)EventDeviceLost \
	$(OUTPUTPATH)FeatureList \
	$(OUTPUTPATH)FeatureList-GUI \
	$(OUTPUTPATH)FrameStartTrigger \
	$(OUTPUTPATH)FrameStartTrigger-GUI \
	$(OUTPUTPATH)GigEActionCommand \
	$(OUTPUTPATH)GigEActionCommand-GUI \
	$(OUTPUTPATH)GigEConfigurations \
	$(OUTPUTPATH)GigEMulticast \
	$(OUTPUTPATH)GigEMulticast-GUI \
	$(OUTPUTPATH)Grab \
	$(OUTPUTPATH)Grab-GUI \
	$(OUTPUTPATH)GrabCallback \
	$(OUTPUTPATH)GrabCallback-GUI \
	$(OUTPUTPATH)GrabCameraEvent \
	$(OUTPUTPATH)GrabChunkImage \
	$(OUTPUTPATH)Graph\
	$(OUTPUTPATH)HostSideROI \
	$(OUTPUTPATH)MultipleCameras \
	$(OUTPUTPATH)MultipleFilters \
	$(OUTPUTPATH)MultipleFilters-GUI \
	$(OUTPUTPATH)MultipleSystems \
	$(OUTPUTPATH)MultipleSystems-GUI \
	$(OUTPUTPATH)OpenCV \
	$(OUTPUTPATH)OverlayQt \
	$(OUTPUTPATH)SaveAndLoadFeatures \
	$(OUTPUTPATH)SaveAndLoadImage \
	$(OUTPUTPATH)SaveVideo \
	$(OUTPUTPATH)SaveVideo-GUI \
	$(OUTPUTPATH)SingleConverter \
	$(OUTPUTPATH)SingleConverter-GUI \
	$(OUTPUTPATH)SingleFilter \
	$(OUTPUTPATH)SingleFilter-GUI \
	$(OUTPUTPATH)StViewerQt \
	$(OUTPUTPATH)UserMemory \
	$(OUTPUTPATH)UserSetCtrl

clean:
	rm -f $(OUTPUTPATH)AllocateStreamBuffersManually 
	rm -f $(OUTPUTPATH)AllocateStreamBuffersManually-GUI 
	rm -f $(OUTPUTPATH)AutoFunctions 
	rm -f $(OUTPUTPATH)CameraSideLUT
	rm -f $(OUTPUTPATH)CameraSideROI
	rm -f $(OUTPUTPATH)CameraSideROI-GUI 
	rm -f $(OUTPUTPATH)DrawOnImage
	rm -f $(OUTPUTPATH)EventDeviceLost 
	rm -f $(OUTPUTPATH)FeatureList 
	rm -f $(OUTPUTPATH)FeatureList-GUI 
	rm -f $(OUTPUTPATH)FrameStartTrigger 
	rm -f $(OUTPUTPATH)FrameStartTrigger-GUI 
	rm -f $(OUTPUTPATH)GigEActionCommand 
	rm -f $(OUTPUTPATH)GigEActionCommand-GUI 
	rm -f $(OUTPUTPATH)GigEConfigurations 
	rm -f $(OUTPUTPATH)GigEMulticast 
	rm -f $(OUTPUTPATH)GigEMulticast-GUI 
	rm -f $(OUTPUTPATH)Grab 
	rm -f $(OUTPUTPATH)Grab-GUI 
	rm -f $(OUTPUTPATH)GrabCallback 
	rm -f $(OUTPUTPATH)GrabCallback-GUI 
	rm -f $(OUTPUTPATH)GrabCameraEvent 
	rm -f $(OUTPUTPATH)GrabChunkImage 
	rm -f $(OUTPUTPATH)Graph
	rm -f $(OUTPUTPATH)HostSideROI 
	rm -f $(OUTPUTPATH)MultipleCameras 
	rm -f $(OUTPUTPATH)MultipleFilters 
	rm -f $(OUTPUTPATH)MultipleFilters-GUI 
	rm -f $(OUTPUTPATH)MultipleSystems 
	rm -f $(OUTPUTPATH)MultipleSystems-GUI 
	rm -f $(OUTPUTPATH)OpenCV 
	rm -f $(OUTPUTPATH)OverlayQt 
	rm -f $(OUTPUTPATH)SaveAndLoadFeatures 
	rm -f $(OUTPUTPATH)SaveAndLoadImage 
	rm -f $(OUTPUTPATH)SaveVideo 
	rm -f $(OUTPUTPATH)SaveVideo-GUI 
	rm -f $(OUTPUTPATH)SingleConverter
	rm -f $(OUTPUTPATH)SingleFilter 
	rm -f $(OUTPUTPATH)SingleFilter-GUI 
	rm -f $(OUTPUTPATH)StViewerQt 
	rm -f $(OUTPUTPATH)UserMemory 
	rm -f $(OUTPUTPATH)UserSetCtrl



$(OUTPUTPATH)AllocateStreamBuffersManually: $(SAMPLEPATH)AllocateStreamBuffersManually/AllocateStreamBuffersManually.cpp 
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL

$(OUTPUTPATH)AllocateStreamBuffersManually-GUI: $(SAMPLEPATH)AllocateStreamBuffersManually/AllocateStreamBuffersManually-GUI.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_GUI_qt

$(OUTPUTPATH)AutoFunctions: $(SAMPLEPATH)AutoFunctions/AutoFunctions.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_GUI_qt

$(OUTPUTPATH)CameraSideLUT: $(SAMPLEPATH)CameraSideLUT/CameraSideLUT.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_IP -lStApi_GUI_qt

$(OUTPUTPATH)CameraSideROI: $(SAMPLEPATH)CameraSideROI/CameraSideROI.cpp 
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL 

$(OUTPUTPATH)CameraSideROI-GUI: $(SAMPLEPATH)CameraSideROI/CameraSideROI-GUI.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_GUI_qt

$(OUTPUTPATH)DrawOnImage: $(SAMPLEPATH)DrawOnImage/DrawOnImage.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_GUI_qt 

$(OUTPUTPATH)EventDeviceLost: $(SAMPLEPATH)EventDeviceLost/EventDeviceLost.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL 

$(OUTPUTPATH)FeatureList: $(SAMPLEPATH)FeatureList/FeatureList.cpp 
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL 

$(OUTPUTPATH)FeatureList-GUI: $(SAMPLEPATH)FeatureList/FeatureList-GUI.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_GUI_qt

$(OUTPUTPATH)FrameStartTrigger: $(SAMPLEPATH)FrameStartTrigger/FrameStartTrigger.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL 

$(OUTPUTPATH)FrameStartTrigger-GUI: $(SAMPLEPATH)FrameStartTrigger/FrameStartTrigger-GUI.cpp 
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_GUI_qt

$(OUTPUTPATH)GigEActionCommand: $(SAMPLEPATH)GigEActionCommand/GigEActionCommand.cpp 
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL

$(OUTPUTPATH)GigEActionCommand-GUI: $(SAMPLEPATH)GigEActionCommand/GigEActionCommand-GUI.cpp 
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_GUI_qt

$(OUTPUTPATH)GigEConfigurations: $(SAMPLEPATH)GigEConfigurations/GigEConfigurations.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_GUI_qt

$(OUTPUTPATH)GigEMulticast: $(SAMPLEPATH)GigEMulticast/GigEMulticast.cpp 
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL 

$(OUTPUTPATH)GigEMulticast-GUI: $(SAMPLEPATH)GigEMulticast/GigEMulticast-GUI.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_GUI_qt

$(OUTPUTPATH)Grab: $(SAMPLEPATH)Grab/Grab.cpp 
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL 

$(OUTPUTPATH)Grab-GUI: $(SAMPLEPATH)Grab/Grab-GUI.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_GUI_qt

$(OUTPUTPATH)GrabCallback: $(SAMPLEPATH)GrabCallback/GrabCallback.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL 

$(OUTPUTPATH)GrabCallback-GUI: $(SAMPLEPATH)GrabCallback/GrabCallback.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_GUI_qt -DENABLED_ST_GUI

$(OUTPUTPATH)GrabCameraEvent: $(SAMPLEPATH)GrabCameraEvent/GrabCameraEvent.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL 

$(OUTPUTPATH)GrabChunkImage: $(SAMPLEPATH)GrabChunkImage/GrabChunkImage.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL 

$(OUTPUTPATH)Graph: $(SAMPLEPATH)Graph/Graph.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_IP -lStApi_GUI_qt 

$(OUTPUTPATH)HostSideROI: $(SAMPLEPATH)HostSideROI/HostSideROI.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_GUI_qt

$(OUTPUTPATH)MultipleCameras: $(SAMPLEPATH)MultipleCameras/MultipleCameras.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL 

$(OUTPUTPATH)MultipleFilters: $(SAMPLEPATH)MultipleFilters/MultipleFilters.cpp 
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_IP 

$(OUTPUTPATH)MultipleFilters-GUI: $(SAMPLEPATH)MultipleFilters/MultipleFilters-GUI.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_IP -lStApi_GUI_qt

$(OUTPUTPATH)MultipleSystems: $(SAMPLEPATH)MultipleSystems/MultipleSystems.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL 

$(OUTPUTPATH)MultipleSystems-GUI: $(SAMPLEPATH)MultipleSystems/MultipleSystems-GUI.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_GUI_qt

ifeq ($(OPENCV_EXISTS),0)
$(OUTPUTPATH)OpenCV: 
	$(info ***OpenCV package is not found. OpenCV/OpenCV.cpp is not included in this compilation***)
endif
ifeq ($(OPENCV_EXISTS),1)
$(OUTPUTPATH)OpenCV: $(SAMPLEPATH)OpenCV/OpenCV.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL `pkg-config --cflags opencv` `pkg-config --libs opencv`
endif
ifeq ($(OPENCV_EXISTS),2)
$(OUTPUTPATH)OpenCV: $(SAMPLEPATH)OpenCV/OpenCV.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL `pkg-config --cflags opencv4` `pkg-config --libs opencv4`
endif

$(OUTPUTPATH)OverlayQt: 
	$(info ***OverlayQt is not included in this compilation. Please build by using either Qt Creator or qmake and make with Qt SDK >= 5.5.1***)

$(OUTPUTPATH)SaveAndLoadFeatures: $(SAMPLEPATH)SaveAndLoadFeatures/SaveAndLoadFeatures.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL 

$(OUTPUTPATH)SaveAndLoadImage: $(SAMPLEPATH)SaveAndLoadImage/SaveAndLoadImage.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_IP

$(OUTPUTPATH)SaveVideo: $(SAMPLEPATH)SaveVideo/SaveVideo.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_IP

$(OUTPUTPATH)SaveVideo-GUI: $(SAMPLEPATH)SaveVideo/SaveVideo-GUI.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_IP -lStApi_GUI_qt

$(OUTPUTPATH)SingleConverter: $(SAMPLEPATH)SingleConverter/SingleConverter.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_IP 

$(OUTPUTPATH)SingleConverter-GUI: $(SAMPLEPATH)SingleConverter/SingleConverter-GUI.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_IP -lStApi_GUI_qt


$(OUTPUTPATH)SingleFilter: $(SAMPLEPATH)SingleFilter/SingleFilter.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_IP 

$(OUTPUTPATH)SingleFilter-GUI: $(SAMPLEPATH)SingleFilter/SingleFilter-GUI.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_IP -lStApi_GUI_qt

$(OUTPUTPATH)StViewerQt:
	$(info ***StViewerQt is not included in this compilation. Please build by using either Qt Creator or qmake and make with Qt SDK >= 5.5.1***)

$(OUTPUTPATH)UserMemory: $(SAMPLEPATH)UserMemory/UserMemory.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL

$(OUTPUTPATH)UserSetCtrl: $(SAMPLEPATH)UserSetCtrl/UserSetCtrl.cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL

