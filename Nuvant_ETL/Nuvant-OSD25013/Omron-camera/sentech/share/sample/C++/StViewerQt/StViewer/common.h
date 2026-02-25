#ifndef COMMON_H
#define COMMON_H

#include <StApi_TL.h>
#include <StApi_IP.h>
#include <StApi_GUI.h>
#include "GenICam.h"

// List of Log message type
enum Enum_LogID
{
    IDS_STARTED = 0,
    IDS_DEVICE_OPENED,
	IDS_IMAGE_FILE_OPENED,
    IDS_DEVICE_LOST,
    IDS_DEVICE_CLOSED,
    IDS_STREAMING_STARTED,
    IDS_STREAMING_STOPPED
};

void OnException(const GenICam::GenericException &e);

#endif // COMMON_H
