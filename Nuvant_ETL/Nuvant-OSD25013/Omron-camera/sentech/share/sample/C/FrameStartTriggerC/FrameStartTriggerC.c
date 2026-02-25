/*!
\file FrameStartTriggerC.c
\brief

This sample shows how to use trigger mode of the camera
The The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to camera
- Set trigger mode and send trigger

For more information, please refer to the help document of StApiC.
If you want to use the GUI features, please refer to FrameStartTriggerC-GUI.c
*/

#include <unistd.h> 
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

/* Include file for using StApiC. */
#include <StApi_C.h>

/* Counts of images to grab. */
const uint64_t nCountOfImagesToGrab = 100;

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
}SCallbackParam_t, *PSCallbackParam_t;

/*

*/
void OnReceiveImage(const PSCallbackParam_t pCallbackParam, PStApiHandle_t pIStStreamBufferHandle)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;

	const PApiFunctions psApiFunctions = pCallbackParam->pApiFunctions;
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
			StApiHandle_t sIStStreamBufferInfoHandle = { NULL };
			uint64_t iFrameID;
			void *pBuffer = NULL;

			eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStStreamBufferInfo(pIStStreamBufferHandle, &sIStStreamBufferInfoHandle);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->StApi->IStStreamBufferInfo->GetFrameID(&sIStStreamBufferInfoHandle, &iFrameID);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->StApi->IStImage->GetImageBuffer(&sIStImageHandle, &pBuffer);
			if (eStApiCError != StApiCError_NoError) break;

			printf("BlockID=%" PRIu64 " Size: %zu x %zu First byte = %u\n", iFrameID, nImageWidth, nImageHeight, *(uint8_t*)pBuffer);
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

	SCallbackParam_t sCallbackParam =
	{
		psApiFunctions,
		&sIStDataStreamHandle,
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
		
		{
			uint64_t i;
			for (i = 0; i < nCountOfImagesToGrab; ++i)
			{
				eStApiCError = psApiFunctions->GenApi->ICommand->Execute(&sICommandTriggerSoftwareHandle, true);
				if (eStApiCError != StApiCError_NoError) break;
				printf("Generated trigger %" PRIu64 " / %" PRIu64 "\n", i + 1, nCountOfImagesToGrab);
                sleep(1);

			}
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

