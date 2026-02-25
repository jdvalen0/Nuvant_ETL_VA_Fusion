CXX:=g++

TARGET1:=MultipleSystems
TARGET2:=$(TARGET1)-GUI

INCFLAGS:=-I${STAPI_ROOT_PATH}/include/GenICam \
		-I${STAPI_ROOT_PATH}/include/StApi

LIBFLAGS:=-L${STAPI_ROOT_PATH}/lib \
		-L${STAPI_ROOT_PATH}/lib/GenICam \
		-lGCBase \
		-lGenApi \
		-llog4cpp \
		-lLog \
		-lMathParser \
		-lNodeMapData \
		-lXmlParser \
		-lpthread

COMPILEFLAGS:=-Wall -Wextra --pedantic -Wno-unknown-pragmas -Wno-switch \
		-Wno-unused-but-set-variable -Wno-pointer-arith -Wno-unused-parameter \
		-std=c++11

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(TARGET1).cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL

$(TARGET2): $(TARGET2).cpp
	$(CXX) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) -lStApi_TL -lStApi_GUI_qt

clean:
	rm -f $(TARGET1)
	rm -f $(TARGET2)
