/*!
\file CameraSideROIC-GUI.c
\brief

This sample shows how to set ROI in camera side and handle the image data.
The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to camera
- Set image ROI parameter
- Acquire image data (with waiting in main thread)
- Process the acquired ROI images

For more information, please refer to the help document of StApiC.
*/

#include <stdlib.h>
#include <pthread.h>

/* Include file for using StApiC. */
#include <StApi_C.h>

/* Counts of images to grab. */
const uint64_t nCountOfImagesToGrab = 100;

/* Feature names */
const char * PIXEL_FORMAT = "PixelFormat";			/* Standard */ 
const char * REGION_SELECTOR = "RegionSelector";	/* Standard */
const char * REGION_MODE = "RegionMode";			/* Standard */
const char * OFFSET_X = "OffsetX";					/* Standard */
const char * OFFSET_Y = "OffsetY";					/* Standard */
const char * WIDTH = "Width";						/* Standard */
const char * HEIGHT = "Height";						/* Standard */

PApiFunctions psApiFunctions = NULL;
StApiHandle_t sIStSystemHandle = { NULL };
StApiHandle_t sIStDeviceHandle = { NULL };
StApiHandle_t sIStDataStreamHandle = { NULL };
StApiHandle_t sIStImageDisplayWndHandle = { NULL };
bool8_t isThreadCompleted = false;

void OutputErrorInfo(PApiFunctions psApiFunctions)
{
	/* If any exception occurred, display the description of the error here. */
	char szText[1024];
	size_t nLen = sizeof(szText);
	EStApiCError_t eStApiCError = psApiFunctions->StApi->GetLastErrorDescriptionA(szText, &nLen);
	if (eStApiCError == StApiCError_NoError)
	{
		printf("Description:%s\n", szText);
	}
}


EStApiCError_t CameraROISetting(PApiFunctions psApiFunctions, PStApiHandle_t pINodeMapHandle)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;

	StApiHandle_t sIStNodeMapDisplayWndHandle = { NULL };
	const char * const pszNodeNames[] =
	{
		PIXEL_FORMAT,
		REGION_SELECTOR,
		REGION_MODE,
		OFFSET_X,
		OFFSET_Y,
		WIDTH,
		HEIGHT
	};
	size_t i;
	/*
	 Create a node map display window object, to get the IStWndReleasable interface pointer.
	 After the window object is no longer needed, call the IStWndReleasable::Release() to discard the window object.
	 (In the destructor of CIStNodeMapDisplayWndPtr, IStWndReleasable::Release() is automatically called.)
	*/
	eStApiCError = psApiFunctions->StApi->IStWnd->CreateIStWnd(StWindowType_NodeMapDisplay, &sIStNodeMapDisplayWndHandle);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	for (i = 0; i < sizeof(pszNodeNames) / sizeof(char*); ++i)
	{
		StApiHandle_t sINodeHandle = { NULL };
		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, pszNodeNames[i], &sINodeHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->StApi->IStNodeMapDisplayWnd->RegisterINodeA(&sIStNodeMapDisplayWndHandle, &sINodeHandle, "CameraSideROI", NULL);
		if (eStApiCError != StApiCError_NoError) break;
	}

	if (eStApiCError == StApiCError_NoError)
	{
		eStApiCError = psApiFunctions->StApi->IStWnd->Show(&sIStNodeMapDisplayWndHandle, NULL, StWindowMode_Modal);
	}
	psApiFunctions->StApi->IStWnd->Release(&sIStNodeMapDisplayWndHandle);

	return(eStApiCError);
}


void* acquisitionWorker(void *arg)
{
    bool8_t isGrabbing;
    StApiHandle_t sIStStreamBufferHandle = { NULL };
    StApiHandle_t sIStStreamBufferInfoHandle = { NULL };
    bool8_t isImagePresent;
    EStApiCError_t eStApiCError;

    for (;;)
    {

        eStApiCError = psApiFunctions->StApi->IStDataStream->IsGrabbing(&sIStDataStreamHandle, &isGrabbing);
        if (eStApiCError != StApiCError_NoError) break;
        if (!isGrabbing) break;

        /* Retrieve the buffer pointer of image data with a timeout of 5000ms. */
        eStApiCError = psApiFunctions->StApi->IStDataStream->RetrieveBuffer(&sIStDataStreamHandle, 5000, &sIStStreamBufferHandle);
        if (eStApiCError != StApiCError_NoError) break;

        eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStStreamBufferInfo(&sIStStreamBufferHandle, &sIStStreamBufferInfoHandle);
        if (eStApiCError != StApiCError_NoError) break;

        /* Check if the acquired data contains image data. */
        eStApiCError = psApiFunctions->StApi->IStStreamBufferInfo->IsImagePresent(&sIStStreamBufferInfoHandle, &isImagePresent);
        if (eStApiCError != StApiCError_NoError) break;

        if (isImagePresent)
        {
            StApiHandle_t sIStImageHandle = { NULL };
            size_t nImageWidth;
            size_t nImageHeight;

            /* If yes, we create a IStImage object for further image handling. */
            eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStImage(&sIStStreamBufferHandle, &sIStImageHandle);
            if (eStApiCError != StApiCError_NoError) break;

            eStApiCError = psApiFunctions->StApi->IStImage->GetImageWidth(&sIStImageHandle, &nImageWidth);
            if (eStApiCError != StApiCError_NoError) break;

            eStApiCError = psApiFunctions->StApi->IStImage->GetImageHeight(&sIStImageHandle, &nImageHeight);
            if (eStApiCError != StApiCError_NoError) break;

            {
                /* Acquire detail information of received image and display it onto the status bar of the display window. */
                double dblFPS;
                char szStatusText[1024];
                bool8_t isVisible;

                eStApiCError = psApiFunctions->StApi->IStDataStream->GetCurrentFPS(&sIStDataStreamHandle, &dblFPS);
                if (eStApiCError != StApiCError_NoError) break;

                sprintf(szStatusText, "%zu x %zu %.2f[fps]", nImageWidth, nImageHeight, dblFPS);

                eStApiCError = psApiFunctions->StApi->IStWnd->SetUserStatusBarTextA(&sIStImageDisplayWndHandle, szStatusText);
                if (eStApiCError != StApiCError_NoError) break;

                /* Check if display window is visible. */
                eStApiCError = psApiFunctions->StApi->IStWnd->IsVisible(&sIStImageDisplayWndHandle, &isVisible);
                if (eStApiCError != StApiCError_NoError) break;

                if (!isVisible)
                {
                    /* Set the position and size of the window. */
                    eStApiCError = psApiFunctions->StApi->IStWnd->SetPosition(&sIStImageDisplayWndHandle, 0, 0, (int32_t)nImageWidth, (int32_t)nImageHeight);
                    if (eStApiCError != StApiCError_NoError) break;

                    /* Create a new thread to display the window. */
                    eStApiCError = psApiFunctions->StApi->IStWnd->Show(&sIStImageDisplayWndHandle, NULL, StWindowMode_Modaless);
                    if (eStApiCError != StApiCError_NoError) break;
                }

                /*
                Register the image to be displayed.
                This will have a copy of the image data and original buffer can be released if necessary and original buffer can be released if necessary.
                */
                eStApiCError = psApiFunctions->StApi->IStImageDisplayWnd->RegisterIStImage(&sIStImageDisplayWndHandle, &sIStImageHandle);
                if (eStApiCError != StApiCError_NoError) break;

            }
        }
        else
        {
            /* If the acquired data contains no image data... */
            printf("Image data does not exist\n");
        }
        eStApiCError = psApiFunctions->StApi->IStStreamBuffer->Release(&sIStStreamBufferHandle);
        if (eStApiCError != StApiCError_NoError) break;
    }

	if (eStApiCError != StApiCError_NoError)
	{
		/* If any error occurred, display the description of the error here. */
		OutputErrorInfo(psApiFunctions);
	}

    isThreadCompleted = true;
    return NULL;
}


int main(int argc, char **argv)
{
	/* Initialize StApiC before using. */
	EStApiCError_t eStApiCError = StApiCInitialize(STAPI_VERSION, &psApiFunctions);

	if (eStApiCError != StApiCError_NoError)
	{
		printf("initializing StApiC was failed.\n");
		return(0);
	}
	for (;;)
	{
		StApiHandle_t sIStPortRemoteHandle = { NULL };
		StApiHandle_t sINodeMapRemoteHandle = { NULL };

		/* Create a system object for device scan and connection. */
		eStApiCError = psApiFunctions->StApi->IStSystem->CreateIStSystem(StSystemVendor_Default, StInterfaceType_All, &sIStSystemHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Create a camera device object and connect to first detected device by using the function of system object. */
		eStApiCError = psApiFunctions->StApi->IStSystem->CreateFirstIStDevice(&sIStSystemHandle, DEVICE_ACCESS_CONTROL, &sIStDeviceHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Displays the DisplayName of the device. */
		{
			StApiHandle_t sIStDeviceInfoHandle = { NULL };
			char szDisplayName[1024];
			size_t nLen = sizeof(szDisplayName);

			eStApiCError = psApiFunctions->StApi->IStDevice->GetIStDeviceInfo(&sIStDeviceHandle, &sIStDeviceInfoHandle);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->StApi->IStDeviceInfo->GetDisplayNameA(&sIStDeviceInfoHandle, szDisplayName, &nLen);
			if (eStApiCError != StApiCError_NoError) break;

			printf("Device=%s\n", szDisplayName);
		}


		/* If using GUI for display, create a display window here. */
		eStApiCError = psApiFunctions->StApi->IStWnd->CreateIStWnd(StWindowType_ImageDisplay, &sIStImageDisplayWndHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Create a DataStream object for handling image stream data. */
		eStApiCError = psApiFunctions->StApi->IStDevice->CreateIStDataStream(&sIStDeviceHandle, 0, NULL, &sIStDataStreamHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Use INodeMap object to access current setting of the camera. */
		eStApiCError = psApiFunctions->StApi->IStDevice->GetRemoteIStPort(&sIStDeviceHandle, &sIStPortRemoteHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->StApi->IStPort->GetINodeMap(&sIStPortRemoteHandle, &sINodeMapRemoteHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = CameraROISetting(psApiFunctions, &sINodeMapRemoteHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Start the image acquisition of the host (local machine) side. */
		eStApiCError = psApiFunctions->StApi->IStDataStream->StartAcquisition(&sIStDataStreamHandle, nCountOfImagesToGrab, ACQ_START_FLAGS_DEFAULT);
		if (eStApiCError != StApiCError_NoError) break;

		/* Start the image acquisition of the camera side. */
		eStApiCError = psApiFunctions->StApi->IStDevice->AcquisitionStart(&sIStDeviceHandle);
		if (eStApiCError != StApiCError_NoError) break;

        /* Create an acquisition thread and check the thread status.  */
        {
            bool8_t isVisible;
            pthread_t thread;
            pthread_create(&thread, NULL, acquisitionWorker, (void*)NULL); 
            while(!isThreadCompleted) 
            {
                eStApiCError = psApiFunctions->StApi->IStWnd->IsVisible(&sIStImageDisplayWndHandle, &isVisible);
                if (eStApiCError == StApiCError_NoError && !isVisible)
                {
                    psApiFunctions->StApi->IStWnd->Show(&sIStImageDisplayWndHandle, 
                            NULL, StWindowMode_Modaless);
                }
                psApiFunctions->StApi->IStWnd->ProcessEventGUI(false, 0);
            }
            pthread_join(thread, NULL);
        }


		/* Stop the image acquisition of the camera side. */
		psApiFunctions->StApi->IStDevice->AcquisitionStop(&sIStDeviceHandle);

		/* Stop the image acquisition of the host side. */
		psApiFunctions->StApi->IStDataStream->StopAcquisition(&sIStDataStreamHandle, ACQ_STOP_FLAGS_DEFAULT);

		break;
	}

	if (eStApiCError != StApiCError_NoError)
	{
		/* If any error occurred, display the description of the error here. */
		OutputErrorInfo(psApiFunctions);
	}

	if (sIStImageDisplayWndHandle.Handle)
	{
		psApiFunctions->StApi->IStWnd->Release(&sIStImageDisplayWndHandle);
	}

	if (sIStDataStreamHandle.Handle)
	{
		psApiFunctions->StApi->IStDataStream->Release(&sIStDataStreamHandle);
	}

	if (sIStDeviceHandle.Handle)
	{
		psApiFunctions->StApi->IStDevice->Release(&sIStDeviceHandle);
	}

	if (sIStSystemHandle.Handle)
	{
		psApiFunctions->StApi->IStSystem->Release(&sIStSystemHandle);
	}

	psApiFunctions->StApi->StApiCTerminate();

	/* Wait until the Enter key is pressed to end program. */
	printf("Press Enter to exit.");
	getchar();

	return 0;
}
