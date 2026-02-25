CC:=gcc

TARGET1:=GrabCallbackC

INCFLAGS:=-I${STAPI_ROOT_PATH}/include/GenICam \
		-I${STAPI_ROOT_PATH}/include/StApi

LIBFLAGS:=-L${STAPI_ROOT_PATH}/lib -lStApi_C -lpthread

COMPILEFLAGS:=-std=c99 -Wall -Wextra --pedantic -Wno-unknown-pragmas -Wno-switch \
		-Wno-unused-but-set-variable -Wno-pointer-arith -Wno-unused-parameter 

all: $(TARGET1)

$(TARGET1): $(TARGET1).c
	$(CC) $^ -o $@ $(COMPILEFLAGS) $(INCFLAGS)	$(LIBFLAGS) 

clean:
	rm -f $(TARGET1)
