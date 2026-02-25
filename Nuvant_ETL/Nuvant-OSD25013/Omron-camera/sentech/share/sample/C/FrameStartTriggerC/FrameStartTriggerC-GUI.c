/*!
\file FrameStartTriggerC-GUI.c
\brief

This sample shows how to use trigger mode of the camera
The The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to camera
- Set trigger mode and send trigger

For more information, please refer to the help document of StApiC.
If you want to use the GUI features, please refer to FrameStartTriggerC-GUI.c
*/

/* Include file for using StApiC. */
#include <StApi_C.h>

/* Counts of images to grab. */
const uint64_t nCountOfImagesToGrab = GENTL_INFINITE;


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
const char * TRIGGER_SELECTOR = "TriggerSelector";				/* Standard */
const char * TRIGGER_SELECTOR_FRAME_START = "FrameStart";		/* Standard */
const char * TRIGGER_SELECTOR_EXPOSURE_START = "ExposureStart";	/* Standard */
const char * TRIGGER_MODE = "TriggerMode";						/* Standard */
const char * TRIGGER_MODE_ON = "On";							/* Standard */
const char * TRIGGER_SOURCE = "TriggerSource";					/* Standard */
const char * TRIGGER_SOURCE_SOFTWARE = "Software";				/* Standard */
const char * TRIGGER_SOFTWARE = "TriggerSoftware";				/* Standard */

/*

*/
typedef struct _SCallbackParam_t
{
	PApiFunctions	pApiFunctions;
	PStApiHandle_t	pIStDataStreamHandle;
	PStApiHandle_t	pIStImageDisplayWndHandle;
}SCallbackParam_t, *PSCallbackParam_t;

/*

*/
void OnReceiveImage(const PSCallbackParam_t pCallbackParam, PStApiHandle_t pIStStreamBufferHandle)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;

	const PApiFunctions psApiFunctions = pCallbackParam->pApiFunctions;
	const PStApiHandle_t pDataStreamHandle = pCallbackParam->pIStDataStreamHandle;
	for (;;)
	{
		StApiHandle_t sIStImageHandle = { NULL };
		size_t nImageWidth;
		size_t nImageHeight;

		eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStImage(pIStStreamBufferHandle, &sIStImageHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->StApi->IStImage->GetImageWidth(&sIStImageHandle, &nImageWidth);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->StApi->IStImage->GetImageHeight(&sIStImageHandle, &nImageHeight);
		if (eStApiCError != StApiCError_NoError) break;

		{
			const PStApiHandle_t pIStImageDisplayWndHandle = pCallbackParam->pIStImageDisplayWndHandle;
			char szStatusText[1024];
			double dblFPS;
			bool8_t isVisible;

			/* Acquire detail information of received image and display it onto the status bar of the display window. */
			eStApiCError = psApiFunctions->StApi->IStDataStream->GetCurrentFPS(pDataStreamHandle, &dblFPS);
			if (eStApiCError != StApiCError_NoError) break;

			sprintf(szStatusText, "%zu x %zu %.2f[fps]", nImageWidth, nImageHeight, dblFPS);

			eStApiCError = psApiFunctions->StApi->IStWnd->SetUserStatusBarTextA(pIStImageDisplayWndHandle, szStatusText);
			if (eStApiCError != StApiCError_NoError) break;

			/* Check if display window is visible. */
			eStApiCError = psApiFunctions->StApi->IStWnd->IsVisible(pIStImageDisplayWndHandle, &isVisible);
			if (eStApiCError != StApiCError_NoError) break;

			if (!isVisible)
			{
				/* Set the position and size of the window. */
				eStApiCError = psApiFunctions->StApi->IStWnd->SetPosition(pIStImageDisplayWndHandle, 0, 0, (int32_t)nImageWidth, (int32_t)nImageHeight);
				if (eStApiCError != StApiCError_NoError) break;

				/* Create a new thread to display the window. */
				eStApiCError = psApiFunctions->StApi->IStWnd->Show(pIStImageDisplayWndHandle, NULL, StWindowMode_Modaless);
				if (eStApiCError != StApiCError_NoError) break;
			}

			/*
			Register the image to be displayed.
			This will have a copy of the image data and original buffer can be released if necessary and original buffer can be released if necessary.
			*/
			eStApiCError = psApiFunctions->StApi->IStImageDisplayWnd->RegisterIStImage(pIStImageDisplayWndHandle, &sIStImageHandle);
			if (eStApiCError != StApiCError_NoError) break;

		}
		break;
	}
	if (eStApiCError != StApiCError_NoError)
	{
		OutputErrorInfo(psApiFunctions);
	}

	psApiFunctions->StApi->IStStreamBuffer->Release(pIStStreamBufferHandle);
}


/*

*/
void OnDataStreamCallback(PStApiHandle_t pIStCallbackParamBaseHandle, void* pContext)
{
	const PSCallbackParam_t pCallbackParam = (PSCallbackParam_t)pContext;
	const PApiFunctions psApiFunctions = pCallbackParam->pApiFunctions;
	const PStApiHandle_t pDataStreamHandle = pCallbackParam->pIStDataStreamHandle;

	uint32_t iTimeoutTime = 0;
	StApiHandle_t sIStStreamBufferHandle = { NULL };
	EStApiCError_t eStApiCError = StApiCError_NoError;
	eStApiCError = psApiFunctions->StApi->IStDataStream->RetrieveBuffer(pDataStreamHandle, iTimeoutTime, &sIStStreamBufferHandle);

	if (eStApiCError == StApiCError_NoError)
	{
		OnReceiveImage(pCallbackParam, &sIStStreamBufferHandle);
	}
}

/*

*/
EStApiCError_t SetEnumerationNode(PApiFunctions psApiFunctions, PStApiHandle_t pINodeMapHandle, const char *szEnumerationName, const char *szValueName)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;
	StApiHandle_t sIEnumerationHandle = { NULL };

	/* Get the IEnumeration interface handle. */
	eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, szEnumerationName, &sIEnumerationHandle);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	/* Update the settings using the IEnumeration interface pointer. */
	eStApiCError = psApiFunctions->GenApi->IEnumeration->SetStringValueA(&sIEnumerationHandle, szValueName);
	return(eStApiCError);
}


/*

*/
int main(int argc, char **argv)
{
	/* Initialize StApiC before using. */
	PApiFunctions psApiFunctions = NULL;
	EStApiCError_t eStApiCError = StApiCInitialize(STAPI_VERSION, &psApiFunctions);

	StApiHandle_t sIStSystemHandle = { NULL };
	StApiHandle_t sIStDeviceHandle = { NULL };
	StApiHandle_t sIStDataStreamHandle = { NULL };
	StApiHandle_t	sIStRegisteredCallbackHandle = { NULL };

	StApiHandle_t sIStNodeMapDisplayWndHandle = { NULL };
	StApiHandle_t sIStImageDisplayWndHandle = { NULL };

	SCallbackParam_t sCallbackParam =
	{
		psApiFunctions,
		&sIStDataStreamHandle,
		&sIStImageDisplayWndHandle,
	};
	
	if (eStApiCError != StApiCError_NoError)
	{
		printf("initializing StApiC was failed.\n");
		return(0);
	}
	for (;;)
	{
		StApiHandle_t sIStPortRemoteHandle = { NULL };
		StApiHandle_t sINodeMapRemoteHandle = { NULL };
		StApiHandle_t sICommandTriggerSoftwareHandle = { NULL };

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

		/* Use INodeMap object to access current setting of the camera. */
		eStApiCError = psApiFunctions->StApi->IStDevice->GetRemoteIStPort(&sIStDeviceHandle, &sIStPortRemoteHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->StApi->IStPort->GetINodeMap(&sIStPortRemoteHandle, &sINodeMapRemoteHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Set the TriggerSelector to FrameStart or ExposureStart */
		eStApiCError = SetEnumerationNode(psApiFunctions, &sINodeMapRemoteHandle, TRIGGER_SELECTOR, TRIGGER_SELECTOR_FRAME_START);
		if (eStApiCError != StApiCError_NoError)
		{
			/*If "FrameStart" is not supported, use "ExposureStart". */
			eStApiCError = SetEnumerationNode(psApiFunctions, &sINodeMapRemoteHandle, TRIGGER_SELECTOR, TRIGGER_SELECTOR_EXPOSURE_START);
		}
		if (eStApiCError != StApiCError_NoError) break;

		/* Set the TriggerMode to On. */
		eStApiCError = SetEnumerationNode(psApiFunctions, &sINodeMapRemoteHandle, TRIGGER_MODE, TRIGGER_MODE_ON);
		if (eStApiCError != StApiCError_NoError) break;

		/* Set the TriggerSource to Software. */
		eStApiCError = SetEnumerationNode(psApiFunctions, &sINodeMapRemoteHandle, TRIGGER_SOURCE, TRIGGER_SOURCE_SOFTWARE);
		if (eStApiCError != StApiCError_NoError) break;

		/* Get the ICommand interface handle for the TriggerSoftware node. */
		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapRemoteHandle, TRIGGER_SOFTWARE, &sICommandTriggerSoftwareHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* If using GUI for display, create a display window here. */
		eStApiCError = psApiFunctions->StApi->IStWnd->CreateIStWnd(StWindowType_ImageDisplay, &sIStImageDisplayWndHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Create a DataStream object for handling image stream data. */
		eStApiCError = psApiFunctions->StApi->IStDevice->CreateIStDataStream(&sIStDeviceHandle, 0, NULL, &sIStDataStreamHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->StApi->IStDataStream->RegisterCallback(&sIStDataStreamHandle, &OnDataStreamCallback, (void*)&sCallbackParam, &sIStRegisteredCallbackHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Start the image acquisition of the host (local machine) side. */
		eStApiCError = psApiFunctions->StApi->IStDataStream->StartAcquisition(&sIStDataStreamHandle, nCountOfImagesToGrab, ACQ_START_FLAGS_DEFAULT);
		if (eStApiCError != StApiCError_NoError) break;

		/* Start the image acquisition of the camera side. */
		eStApiCError = psApiFunctions->StApi->IStDevice->AcquisitionStart(&sIStDeviceHandle);
		if (eStApiCError != StApiCError_NoError) break;
		
		/*
		Create a node map display window object, to get the IStWndReleasable interface handle
		After the window object is no longer needed, call the IStWnd->Release() to discard the window object.
		*/

		eStApiCError = psApiFunctions->StApi->IStWnd->CreateIStWnd(StWindowType_NodeMapDisplay, &sIStNodeMapDisplayWndHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->StApi->IStNodeMapDisplayWnd->RegisterINodeA(&sIStNodeMapDisplayWndHandle, &sICommandTriggerSoftwareHandle, "Trigger", NULL);
		if (eStApiCError != StApiCError_NoError) break;

		/* Display the window. */
		eStApiCError = psApiFunctions->StApi->IStWnd->Show(&sIStNodeMapDisplayWndHandle, NULL, StWindowMode_Modaless);
		if (eStApiCError != StApiCError_NoError) break;
        
        psApiFunctions->StApi->IStWnd->ProcessEventGUI(true, 0);

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

	if (sIStNodeMapDisplayWndHandle.Handle)
	{
		psApiFunctions->StApi->IStWnd->Release(&sIStNodeMapDisplayWndHandle);
	}
	if (sIStImageDisplayWndHandle.Handle)
	{
		psApiFunctions->StApi->IStWnd->Release(&sIStImageDisplayWndHandle);
	}

	if (sIStRegisteredCallbackHandle.Handle)
	{
		psApiFunctions->StApi->IStRegisteredCallback->Release(&sIStRegisteredCallbackHandle);
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

	return 0;
}

