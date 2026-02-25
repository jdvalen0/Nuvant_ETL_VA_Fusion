CXX:=g++

TARGET1:=OpenCV

OPENCV_EXISTS=$(shell if pkg-config opencv --exists; then echo 1; elif pkg-config opencv4 --exists; then echo 2; else echo 0;fi;)

INCFLAGS:=-I${STAPI_ROOT_PATH}/include/GenICam \
		-I${STAPI_ROOT_PATH}/include/StApi

LIBFLAGS:=-L${STAPI_ROOT_PATH}/lib \
		-L${STAPI_ROOT_PATH}/lib/GenICam \
		-lGCBase \
		-lGenApi \
		-lpthread

COMPILEFLAGS:=-Wall -Wextra --pedantic -Wno-unknown-pragmas -Wno-switch \
		-Wno-unused-but-set-variable -Wno-pointer-arith -Wno-unused-parameter \
		-std=c++11

all: $(TARGET1) 


ifeq ($(OPENCV_EXISTS),0)
$(TARGET1):
	$(info ***OpenCV package is not found. OpenCV/OpenCV.cpp is not included in this compilation***)
endif
ifeq ($(OPENCV_EXISTS),1)
$(TARGET1): $(TARGET1).cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS) $(LIBFLAGS) -lStApi_TL `pkg-config --cflags opencv` `pkg-config --libs opencv`
endif
ifeq ($(OPENCV_EXISTS),2)
$(TARGET1): $(TARGET1).cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS) $(LIBFLAGS) -lStApi_TL `pkg-config --cflags opencv4` `pkg-config --libs opencv4`
endif

clean:
	rm -f $(TARGET1)
