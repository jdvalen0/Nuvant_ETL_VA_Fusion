/*!
\file GrabCameraEventC-GUI.c
\brief

This sample shows how to register an event callback with callback function.
Here we register the callback function to "ExposureEnd" event (Defined as TARGET_EVENT_NAME) with a callback function to handle this event.
The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to camera
- Acquire image data with callback function
- Enable the event message sending function of camera
- Register callback function of indicated event

For more information, please refer to the help document of StApiC.
*/

#include <stdlib.h>
#include <pthread.h>

/* Include file for using StApiC. */
#include <StApi_C.h>

/* Target counts of image to be grabbed. */
const uint64_t nCountOfImagesToGrab = 100;

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


/* Feature names */
const char * EVENT_SELECTOR = "EventSelector";			/* Standard */
const char * EVENT_NOTIFICATION = "EventNotification";	/* Standard */
const char * EVENT_NOTIFICATION_ON = "On";				/* Standard */
const char * TARGET_EVENT_NAME = "ExposureEnd";			/* Standard */
const char * CALLBACK_NODE_NAME = "EventExposureEndTimestamp";	/* Standard */


typedef struct _SCallbackParam_t
{
	PApiFunctions	pApiFunctions;
}SCallbackParam_t, *PSCallbackParam_t;

/*
	Callback function 
*/
void OnNodeCallbackCFunction(StApiHandle_t* pINodeHandle, void* pContext)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;

	const PSCallbackParam_t pCallbackParam = (PSCallbackParam_t)pContext;
	const PApiFunctions psApiFunctions = pCallbackParam->pApiFunctions;
	
	for (;;)
	{
		char szName[256];
		size_t nSize = sizeof(szName);
		bool8_t isReadable;

		eStApiCError = psApiFunctions->GenApi->INode->GetNameA(pINodeHandle, false, szName, &nSize);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->GenApi->IBase->IsReadable(pINodeHandle, &isReadable);
		if (eStApiCError != StApiCError_NoError) break;

		if (isReadable)
		{
			char szValue[256];

			nSize = sizeof(szValue);
			eStApiCError = psApiFunctions->GenApi->IValue->ToStringA(pINodeHandle, false, false, szValue, &nSize);
			if (eStApiCError != StApiCError_NoError) break;
			printf("%s = %s\n", szName, szValue);
		}
		else
		{
			printf("%s is not readable.\n", szName);
		}
		break;
	}
	if (eStApiCError != StApiCError_NoError)
	{
		/* If any error occurred, display the description of the error here. */
		OutputErrorInfo(psApiFunctions);
	}
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
                double dblFPS;
                char szStatusText[1024];
                bool8_t isVisible;

                /* Acquire detail information of received image and display it onto the status bar of the display window. */
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
                    eStApiCError = psApiFunctions->StApi->IStWnd->Show(&sIStImageDisplayWndHandle, NULL, StWindowMode_ModalessOnNewThread);
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

	SCallbackParam_t sCallbackParam = { psApiFunctions };
	StApiHandle_t sIStRegisteredCallbackHandle = { psApiFunctions, ApiHandleType_StApi_IStRegisteredCallback};

	if (eStApiCError != StApiCError_NoError)
	{
		printf("initializing StApiC was failed.\n");
		return(0);
	}
	for (;;)
	{
		StApiHandle_t sIStPortRemoteHandle = { NULL };
		StApiHandle_t sINodeMapRemoteHandle = { NULL };
		StApiHandle_t sINodeCallbackHandle = { NULL };
		StApiHandle_t sIEnumerationEevntSelectorHandle = { NULL };
		StApiHandle_t sIEnumerationEevntNotificationHandle = { NULL };

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

		/* Create a display window here. */
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

		/* Get INode interface pointer of "EventExposureEndTimestamp" for later registering use. */
		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapRemoteHandle, CALLBACK_NODE_NAME, &sINodeCallbackHandle);
		if (eStApiCError != StApiCError_NoError) break;
		if (sINodeCallbackHandle.Handle == NULL)
		{
			printf("Not found a feature %s.\n", CALLBACK_NODE_NAME);
			break;
		}

		/*
			Register acquired INode interface pointer with callback function for calling.
			When the event of passed-in INode indicated is triggered, the registered callback function will be called.
		*/
		eStApiCError = psApiFunctions->GenApi->INode->RegisterCallback(&sINodeCallbackHandle, OnNodeCallbackCFunction, cbPostInsideLock, &sCallbackParam, &sIStRegisteredCallbackHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Enabling the transmission of the target event. */
		/* For enabling the event sending function of camera, you need to select the event by EventSelector and switch EventNotification to ON. */
		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapRemoteHandle, EVENT_SELECTOR, &sIEnumerationEevntSelectorHandle);
		if (eStApiCError != StApiCError_NoError) break;
		if (sIEnumerationEevntSelectorHandle.Handle == NULL)
		{
			printf("Not found a feature %s.\n", EVENT_SELECTOR);
			break;
		}

		eStApiCError = psApiFunctions->GenApi->IEnumeration->SetStringValueA(&sIEnumerationEevntSelectorHandle, TARGET_EVENT_NAME);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapRemoteHandle, EVENT_NOTIFICATION, &sIEnumerationEevntNotificationHandle);
		if (eStApiCError != StApiCError_NoError) break;
		if (sIEnumerationEevntNotificationHandle.Handle == NULL)
		{
			printf("Not found a feature %s.\n", EVENT_NOTIFICATION);
			break;
		}
		eStApiCError = psApiFunctions->GenApi->IEnumeration->SetStringValueA(&sIEnumerationEevntNotificationHandle, EVENT_NOTIFICATION_ON);
		if (eStApiCError != StApiCError_NoError) break;

		/*
			Start event handling thread for listening to the events.
			You must start event handling thread in order to acquire the events.
		*/
		psApiFunctions->StApi->IStDevice->StartEventAcquisitionThread(&sIStDeviceHandle);

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

		/* Stop the event acquisition thread. */
		psApiFunctions->StApi->IStDevice->StopEventAcquisitionThread(&sIStDeviceHandle);

		psApiFunctions->StApi->IStRegisteredCallback->Release(&sIStRegisteredCallbackHandle);
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

