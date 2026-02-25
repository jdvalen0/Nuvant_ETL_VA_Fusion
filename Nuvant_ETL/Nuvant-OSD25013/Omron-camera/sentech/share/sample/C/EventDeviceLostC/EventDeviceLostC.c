/*!
\file EventDeviceLostC.c
\brief

This sample shows how to setup and detect device connection lost.
The following points will be demonstrated in this sample code:
- Initialize StApiS
- Connect to camera
- Detect the disconnection of camera

For more information, please refer to the help document of StApiC.
*/

/* Include file for using StApiC. */
#include <StApi_C.h>

/* Count of images to be grabbed. */
const uint64_t nCountOfImagesToGrab = GENTL_INFINITE;

/* Feature names */
const char * EVENT_SELECTOR = "EventSelector";				/* Standard */
const char * EVENT_NOTIFICATION = "EventNotification";		/* Standard */
const char * EVENT_NOTIFICATION_ON = "On";					/* Standard */
const char * TARGET_EVENT_NAME = "DeviceLost";				/* Standard */
const char * CALLBACK_NODE_NAME = "EventDeviceLost";		/* Standard */

#include <stdlib.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

/*

*/
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
/*
Callback function parameter
*/
typedef struct
{
	PApiFunctions psApiFunctions;
	PStApiHandle_t psIStDeviceHandle;
}SCallbackFunctionParam_t, *PSCallbackFunctionParam_t;
/*
Callback function
*/
void OnNodeCallbackCFunction(PStApiHandle_t psINodeHandle, void* pvContext)
{
	PSCallbackFunctionParam_t pParam = (PSCallbackFunctionParam_t)pvContext;
	EAccessMode eAccessMode;
	pParam->psApiFunctions->GenApi->IBase->GetAccessMode(psINodeHandle, &eAccessMode);
	if ((eAccessMode != NA) && (eAccessMode != NI))
	{
		/*
			Node event will be triggered when it is invalidated.
			Check if DeviceLost occurred.
		*/
		char szName[1024];
		size_t nLen = sizeof(szName);
		bool8_t isDeviceLost;

		pParam->psApiFunctions->GenApi->INode->GetNameA(psINodeHandle, 0, szName, &nLen);

		pParam->psApiFunctions->StApi->IStDevice->IsDeviceLost(pParam->psIStDeviceHandle, &isDeviceLost);
		printf("OnNodeEvent: %s : %s\n", szName, isDeviceLost ? "DeviceLost" : "Invalidated");
	}
}

/*

*/
EStApiCError_t GrabLoop(PApiFunctions psApiFunctions, PStApiHandle_t psIStDeviceHandle)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;

	StApiHandle_t sIStDataStreamHandle = { NULL };
	StApiHandle_t sIStRegisteredCallbackHandle = { NULL };

	for (;;)
	{
		StApiHandle_t sIStPortHandle = { NULL };
		StApiHandle_t sINodeMapHandle = { NULL };
		StApiHandle_t sINodeCallbackHandle = { NULL };
		SCallbackFunctionParam_t sCallbackFunctionParam;
		StApiHandle_t sINodeEventSelectorHandle = { NULL };
		StApiHandle_t sINodeEventNotificationHandle = { NULL };

		/* Displays the DisplayName of the device. */
		{
			StApiHandle_t sIStDeviceInfoHandle = { NULL };
			char szDisplayName[1024];
			size_t nLen = sizeof(szDisplayName);

			eStApiCError = psApiFunctions->StApi->IStDevice->GetIStDeviceInfo(psIStDeviceHandle, &sIStDeviceInfoHandle);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->StApi->IStDeviceInfo->GetDisplayNameA(&sIStDeviceInfoHandle, szDisplayName, &nLen);
			if (eStApiCError != StApiCError_NoError) break;

			printf("Device=%s\n", szDisplayName);
		}

		/* Get the INodeMap interface pointer for the host side device settings */
		eStApiCError = psApiFunctions->StApi->IStDevice->GetLocalIStPort(psIStDeviceHandle, &sIStPortHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->StApi->IStPort->GetINodeMap(&sIStPortHandle, &sINodeMapHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Get the INode interface pointer for the EventDeviceLost node */
		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, CALLBACK_NODE_NAME, &sINodeCallbackHandle);
		if (eStApiCError != StApiCError_NoError) break;

		if (sINodeCallbackHandle.Handle == NULL)
		{
			printf("%s node does not exist.\n", CALLBACK_NODE_NAME);
			break;
		}

		/* Register a callback function.When an event occurs for Data strem, function registered will be called. */
		sCallbackFunctionParam.psApiFunctions = psApiFunctions;
		sCallbackFunctionParam.psIStDeviceHandle = psIStDeviceHandle;
		eStApiCError = psApiFunctions->GenApi->INode->RegisterCallback(&sINodeCallbackHandle, &OnNodeCallbackCFunction, cbPostOutsideLock, &sCallbackFunctionParam, &sIStRegisteredCallbackHandle);

		/* Enabling the transmission of the target event. */
		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, EVENT_SELECTOR, &sINodeEventSelectorHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->GenApi->IEnumeration->SetStringValueA(&sINodeEventSelectorHandle, TARGET_EVENT_NAME);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, EVENT_NOTIFICATION, &sINodeEventNotificationHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->GenApi->IEnumeration->SetStringValueA(&sINodeEventNotificationHandle, EVENT_NOTIFICATION_ON);
		if (eStApiCError != StApiCError_NoError) break;

		/* Start the event acquisition thread for listening to event. */
		eStApiCError = psApiFunctions->StApi->IStDevice->StartEventAcquisitionThread(psIStDeviceHandle);
		if (eStApiCError != StApiCError_NoError) break;
		
		/* Create a DataStream object for handling image stream data. */
		eStApiCError = psApiFunctions->StApi->IStDevice->CreateIStDataStream(psIStDeviceHandle, 0, NULL, &sIStDataStreamHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Start the image acquisition of the host side. */
		eStApiCError = psApiFunctions->StApi->IStDataStream->StartAcquisition(&sIStDataStreamHandle, nCountOfImagesToGrab, ACQ_START_FLAGS_DEFAULT);
		if (eStApiCError != StApiCError_NoError) break;

		/* Start the image acquisition of the camera side. */
		eStApiCError = psApiFunctions->StApi->IStDevice->AcquisitionStart(psIStDeviceHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/*
			A while loop for acquiring data and checking status.
			Here, the acquisition runs until it reaches the assigned numbers of frames.
		*/
		for (;;)
		{
			bool8_t isGrabbing;
			StApiHandle_t sIStStreamBufferHandle = { NULL };
			StApiHandle_t sIStStreamBufferInfoHandle = { NULL };
			bool8_t isImagePresent;

			eStApiCError = psApiFunctions->StApi->IStDataStream->IsGrabbing(&sIStDataStreamHandle, &isGrabbing);
			if (eStApiCError != StApiCError_NoError) break;
			if (!isGrabbing) break;

			/* Retrieve the buffer pointer of image data with a timeout of 5000ms. */

			eStApiCError = psApiFunctions->StApi->IStDataStream->RetrieveBuffer(&sIStDataStreamHandle, 5000, &sIStStreamBufferHandle);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStStreamBufferInfo(&sIStStreamBufferHandle, &sIStStreamBufferInfoHandle);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->StApi->IStStreamBufferInfo->IsImagePresent(&sIStStreamBufferInfoHandle, &isImagePresent);
			if (eStApiCError != StApiCError_NoError) break;
			/* Check if the acquired data contains image data. */
			if (isImagePresent)
			{	
				StApiHandle_t sIStImageHandle = { NULL };
				StApiHandle_t sIStStreamBufferInfoHandle = { NULL };
				uint64_t iFrameID;
				size_t nImageWidth;
				size_t nImageHeight;
				void *pBuffer;

				/* If yes, we create a IStImage object for further image handling. */
				eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStImage(&sIStStreamBufferHandle, &sIStImageHandle);
				if (eStApiCError != StApiCError_NoError) break;

				/* Display the information of the acquired image data. */
				eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStStreamBufferInfo(&sIStStreamBufferHandle, &sIStStreamBufferInfoHandle);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->StApi->IStStreamBufferInfo->GetFrameID(&sIStStreamBufferInfoHandle, &iFrameID);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->StApi->IStImage->GetImageWidth(&sIStImageHandle, &nImageWidth);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->StApi->IStImage->GetImageHeight(&sIStImageHandle, &nImageHeight);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->StApi->IStImage->GetImageBuffer(&sIStImageHandle, &pBuffer);
				if (eStApiCError != StApiCError_NoError) break;

				printf("BlockID=%" PRIu64 " Size: %zu x %zu First byte = %u\n", iFrameID, nImageWidth, nImageHeight, *(uint8_t*)pBuffer);
			}
			else
			{
				/* If the acquired data contains no image data. */
				printf("Image data does not exist.\n");
			}

			eStApiCError = psApiFunctions->StApi->IStStreamBuffer->Release(&sIStStreamBufferHandle);
			if (eStApiCError != StApiCError_NoError) break;
		}

		/* Stop the image acquisition of the camera side. */
		psApiFunctions->StApi->IStDevice->AcquisitionStop(psIStDeviceHandle);

		/* Stop the image acquisition of the host side. */
		psApiFunctions->StApi->IStDataStream->StopAcquisition(&sIStDataStreamHandle, ACQ_STOP_FLAGS_DEFAULT);

		/* Stop the event acquisition thread. */
		psApiFunctions->StApi->IStDevice->StopEventAcquisitionThread(psIStDeviceHandle);

		break;
	}
	if (sIStRegisteredCallbackHandle.Handle)
	{
		psApiFunctions->StApi->IStRegisteredCallback->Release(&sIStRegisteredCallbackHandle);
	}
	if (sIStDataStreamHandle.Handle)
	{
		psApiFunctions->StApi->IStDataStream->Release(&sIStDataStreamHandle);
	}
	if (psIStDeviceHandle->Handle)
	{
		psApiFunctions->StApi->IStDevice->Release(psIStDeviceHandle);
	}
	return(eStApiCError);
}

/*
 
*/
int main(int argc, char **argv)
{
	/* Initialize StApiC before using. */
	PApiFunctions psApiFunctions = NULL;
	EStApiCError_t eStApiCError = StApiCInitialize(STAPI_VERSION, &psApiFunctions);
	StApiHandle_t sSystemHandle = { NULL };

	if (eStApiCError != StApiCError_NoError)
	{
		printf("initializing StApiC was failed.\n");
		return(0);
	}

	/* Create a system object for device scan and connection. */
	eStApiCError = psApiFunctions->StApi->IStSystem->CreateIStSystem(StSystemVendor_Default, StInterfaceType_All, &sSystemHandle);
	if (eStApiCError == StApiCError_NoError)
	{
		StApiHandle_t sIStDeviceHandle = { NULL };
		bool8_t isFirstTime = 1;
		char szDeviceID[1024];

		for (;;)
		{
			if (isFirstTime)
			{
				StApiHandle_t sDeviceInfoHandle = { NULL };
				size_t nLen = sizeof(szDeviceID);

				/* Create a camera device object and connect to first detected device by using the function of system object. */
				eStApiCError = psApiFunctions->StApi->IStSystem->CreateFirstIStDevice(&sSystemHandle, DEVICE_ACCESS_CONTROL, &sIStDeviceHandle);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->StApi->IStDevice->GetIStDeviceInfo(&sIStDeviceHandle, &sDeviceInfoHandle);
				if (eStApiCError != StApiCError_NoError) break;

				/* Hold the device ID for re - open */
				eStApiCError = psApiFunctions->StApi->IStDeviceInfo->GetIDA(&sDeviceInfoHandle, szDeviceID, &nLen);
				if (eStApiCError != StApiCError_NoError) break;
			}
			else
			{
				uint32_t iInterfaceCount;
				uint32_t iInterface;

				/* Get the number of interfaces. */
				eStApiCError = psApiFunctions->StApi->IStSystem->GetInterfaceCount(&sSystemHandle, &iInterfaceCount);
				if (eStApiCError != StApiCError_NoError) break;

				for (iInterface = 0; iInterface < iInterfaceCount; ++iInterface)
				{
					StApiHandle_t sIStInterfaceHandle = { NULL };

					/* Get the IStInterface interface handle. */
					eStApiCError = psApiFunctions->StApi->IStSystem->GetIStInterface(&sSystemHandle, iInterface, &sIStInterfaceHandle);
					if (eStApiCError != StApiCError_NoError) break;

					eStApiCError = psApiFunctions->StApi->IStInterface->CreateIStDeviceByIDA(&sIStInterfaceHandle, szDeviceID, DEVICE_ACCESS_CONTROL, &sIStDeviceHandle);
					if (eStApiCError == StApiCError_NoError) break;
				}
			}

			if (sIStDeviceHandle.Handle)
			{
				/* Repeat the acquisition of the image until the device is disconnected. */
				GrabLoop(psApiFunctions, &sIStDeviceHandle);
			}

			/* Display choices */
			printf("0 : Reopen the same Device.\n");
			printf("Else : Exit\n");
			printf("Selection : ");

			/* Waiting for input */
			{
				char chrInput;
				for (;;)
				{
					char chrTmp = getchar();
					if (chrTmp == '\n') break;
					chrInput = chrTmp;
				} 
				if (chrInput != '0') break;
			}
			isFirstTime = 0;
		}
	}

	if (eStApiCError != StApiCError_NoError)
	{
		/* If any error occurred, display the description of the error here. */
		OutputErrorInfo(psApiFunctions);
	}

	if (sSystemHandle.Handle)
	{
		psApiFunctions->StApi->IStSystem->Release(&sSystemHandle);
	}

	psApiFunctions->StApi->StApiCTerminate();

	/* Wait until the Enter key is pressed to end program. */
	printf("Press Enter to exit.");
	getchar();

	return(0);
}
