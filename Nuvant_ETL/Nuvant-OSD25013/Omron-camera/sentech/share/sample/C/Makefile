#SAMPLEPATH: location of the sample code directories with trailing /
#OTUPUTPATH: path of the compile results with trailing /
SAMPLEPATH:=${STAPI_ROOT_PATH}/share/sample/C/
OUTPUTPATH:=./

OPENCV_EXISTS=$(shell if pkg-config opencv --exists; then echo 1; else echo 0;fi;)

CXX:=gcc

ifeq ($(INCFLAGS),)
	INCFLAGS:=-I${STAPI_ROOT_PATH}/include/GenICam \
		-I${STAPI_ROOT_PATH}/include/StApi
endif

ifeq ($(LIBFLAGS),)
	LIBFLAGS:=-L${STAPI_ROOT_PATH}/lib -lStApi_C -lpthread
endif

ifeq ($(COMPILEFLAGS),)
	COMPILEFLAGS:=-std=c99 -Wall -Wextra --pedantic -Wno-unknown-pragmas \
		-Wno-switch -Wno-unused-but-set-variable -Wno-pointer-arith \
		-Wno-unused-parameter 
endif

all: $(OUTPUTPATH)AllocateStreamBuffersManuallyC \
	$(OUTPUTPATH)AllocateStreamBuffersManuallyC-GUI \
	$(OUTPUTPATH)AutoFunctionsC \
	$(OUTPUTPATH)CameraSideROIC \
	$(OUTPUTPATH)CameraSideROIC-GUI \
	$(OUTPUTPATH)EventDeviceLostC \
	$(OUTPUTPATH)FeatureListC \
	$(OUTPUTPATH)FeatureListC-GUI \
	$(OUTPUTPATH)FrameStartTriggerC \
	$(OUTPUTPATH)FrameStartTriggerC-GUI \
	$(OUTPUTPATH)GigEActionCommandC \
	$(OUTPUTPATH)GigEActionCommandC-GUI \
	$(OUTPUTPATH)GigEConfigurationsC \
	$(OUTPUTPATH)GigEMulticastC \
	$(OUTPUTPATH)GigEMulticastC-GUI \
	$(OUTPUTPATH)GrabC \
	$(OUTPUTPATH)GrabC-GUI \
	$(OUTPUTPATH)GrabCallbackC \
	$(OUTPUTPATH)GrabCallbackC-GUI \
	$(OUTPUTPATH)GrabCameraEventC \
	$(OUTPUTPATH)GrabChunkImageC \
	$(OUTPUTPATH)HostSideROIC \
	$(OUTPUTPATH)MultipleCamerasC \
	$(OUTPUTPATH)MultipleFiltersC \
	$(OUTPUTPATH)MultipleFiltersC-GUI \
	$(OUTPUTPATH)MultipleSystemsC \
	$(OUTPUTPATH)MultipleSystemsC-GUI \
	$(OUTPUTPATH)SaveAndLoadFeaturesC \
	$(OUTPUTPATH)SaveAndLoadImageC \
	$(OUTPUTPATH)SaveVideoC \
	$(OUTPUTPATH)SaveVideoC-GUI \
	$(OUTPUTPATH)SingleFilterC \
	$(OUTPUTPATH)SingleFilterC-GUI \
	$(OUTPUTPATH)UserMemoryC \
	$(OUTPUTPATH)UserSetCtrlC

clean:
	rm -f $(OUTPUTPATH)AllocateStreamBuffersManuallyC 
	rm -f $(OUTPUTPATH)AllocateStreamBuffersManuallyC-GUI 
	rm -f $(OUTPUTPATH)AutoFunctionsC 
	rm -f $(OUTPUTPATH)CameraSideROIC
	rm -f $(OUTPUTPATH)CameraSideROIC-GUI 
	rm -f $(OUTPUTPATH)EventDeviceLostC 
	rm -f $(OUTPUTPATH)FeatureListC 
	rm -f $(OUTPUTPATH)FeatureListC-GUI 
	rm -f $(OUTPUTPATH)FrameStartTriggerC 
	rm -f $(OUTPUTPATH)FrameStartTriggerC-GUI 
	rm -f $(OUTPUTPATH)GigEActionCommandC 
	rm -f $(OUTPUTPATH)GigEActionCommandC-GUI 
	rm -f $(OUTPUTPATH)GigEConfigurationsC 
	rm -f $(OUTPUTPATH)GigEMulticastC 
	rm -f $(OUTPUTPATH)GigEMulticastC-GUI 
	rm -f $(OUTPUTPATH)GrabC 
	rm -f $(OUTPUTPATH)GrabC-GUI 
	rm -f $(OUTPUTPATH)GrabCallbackC 
	rm -f $(OUTPUTPATH)GrabCallbackC-GUI 
	rm -f $(OUTPUTPATH)GrabCameraEventC 
	rm -f $(OUTPUTPATH)GrabChunkImageC 
	rm -f $(OUTPUTPATH)HostSideROIC 
	rm -f $(OUTPUTPATH)MultipleCamerasC 
	rm -f $(OUTPUTPATH)MultipleFiltersC 
	rm -f $(OUTPUTPATH)MultipleFiltersC-GUI 
	rm -f $(OUTPUTPATH)MultipleSystemsC 
	rm -f $(OUTPUTPATH)MultipleSystemsC-GUI 
	rm -f $(OUTPUTPATH)SaveAndLoadFeaturesC
	rm -f $(OUTPUTPATH)SaveAndLoadImageC 
	rm -f $(OUTPUTPATH)SaveVideoC 
	rm -f $(OUTPUTPATH)SaveVideoC-GUI 
	rm -f $(OUTPUTPATH)SingleFilterC 
	rm -f $(OUTPUTPATH)SingleFilterC-GUI 
	rm -f $(OUTPUTPATH)UserMemoryC 
	rm -f $(OUTPUTPATH)UserSetCtrlC



$(OUTPUTPATH)AllocateStreamBuffersManuallyC: $(SAMPLEPATH)AllocateStreamBuffersManuallyC/AllocateStreamBuffersManuallyC.c 
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)AllocateStreamBuffersManuallyC-GUI: $(SAMPLEPATH)AllocateStreamBuffersManuallyC/AllocateStreamBuffersManuallyC-GUI.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)AutoFunctionsC: $(SAMPLEPATH)AutoFunctionsC/AutoFunctionsC.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)CameraSideROIC: $(SAMPLEPATH)CameraSideROIC/CameraSideROIC.c 
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)CameraSideROIC-GUI: $(SAMPLEPATH)CameraSideROIC/CameraSideROIC-GUI.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)EventDeviceLostC: $(SAMPLEPATH)EventDeviceLostC/EventDeviceLostC.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)FeatureListC: $(SAMPLEPATH)FeatureListC/FeatureListC.c 
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)FeatureListC-GUI: $(SAMPLEPATH)FeatureListC/FeatureListC-GUI.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)FrameStartTriggerC: $(SAMPLEPATH)FrameStartTriggerC/FrameStartTriggerC.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)FrameStartTriggerC-GUI: $(SAMPLEPATH)FrameStartTriggerC/FrameStartTriggerC-GUI.c 
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)GigEActionCommandC: $(SAMPLEPATH)GigEActionCommandC/GigEActionCommandC.c 
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)GigEActionCommandC-GUI: $(SAMPLEPATH)GigEActionCommandC/GigEActionCommandC-GUI.c 
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)GigEConfigurationsC: $(SAMPLEPATH)GigEConfigurationsC/GigEConfigurationsC.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)GigEMulticastC: $(SAMPLEPATH)GigEMulticastC/GigEMulticastC.c 
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)GigEMulticastC-GUI: $(SAMPLEPATH)GigEMulticastC/GigEMulticastC-GUI.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)GrabC: $(SAMPLEPATH)GrabC/GrabC.c 
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) 

$(OUTPUTPATH)GrabC-GUI: $(SAMPLEPATH)GrabC/GrabC-GUI.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)GrabCallbackC: $(SAMPLEPATH)GrabCallbackC/GrabCallbackC.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)GrabCallbackC-GUI: $(SAMPLEPATH)GrabCallbackC/GrabCallbackC.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -DENABLED_ST_GUI

$(OUTPUTPATH)GrabCameraEventC: $(SAMPLEPATH)GrabCameraEventC/GrabCameraEventC.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)GrabChunkImageC: $(SAMPLEPATH)GrabChunkImageC/GrabChunkImageC.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)HostSideROIC: $(SAMPLEPATH)HostSideROIC/HostSideROIC.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)MultipleCamerasC: $(SAMPLEPATH)MultipleCamerasC/MultipleCamerasC.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)MultipleFiltersC: $(SAMPLEPATH)MultipleFiltersC/MultipleFiltersC.c 
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)MultipleFiltersC-GUI: $(SAMPLEPATH)MultipleFiltersC/MultipleFiltersC-GUI.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)MultipleSystemsC: $(SAMPLEPATH)MultipleSystemsC/MultipleSystemsC.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)MultipleSystemsC-GUI: $(SAMPLEPATH)MultipleSystemsC/MultipleSystemsC-GUI.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)SaveAndLoadFeaturesC: $(SAMPLEPATH)SaveAndLoadFeaturesC/SaveAndLoadFeaturesC.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)SaveAndLoadImageC: $(SAMPLEPATH)SaveAndLoadImageC/SaveAndLoadImageC.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)SaveVideoC: $(SAMPLEPATH)SaveVideoC/SaveVideoC.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)SaveVideoC-GUI: $(SAMPLEPATH)SaveVideoC/SaveVideoC-GUI.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)SingleFilterC: $(SAMPLEPATH)SingleFilterC/SingleFilterC.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)SingleFilterC-GUI: $(SAMPLEPATH)SingleFilterC/SingleFilterC-GUI.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)UserMemoryC: $(SAMPLEPATH)UserMemoryC/UserMemoryC.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

$(OUTPUTPATH)UserSetCtrlC: $(SAMPLEPATH)UserSetCtrlC/UserSetCtrlC.c
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS)

