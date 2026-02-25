/*!
\file MultipleSystemsC.c
\brief

  This sample shows how to use multiple GenTL modules (cti files) for acquiring image data.
  The following points will be demonstrated in this sample code:
  - Initialize StApiC
  - Connect to the first detected camera of all system
  - Acquire image data (with waiting in main thread) 
  - Use multiple GenTL module.

If you want to acquire image by using callback functions, please reference "GrabCallbackC" sample for more information.
For more information, please refer to the help document of StApiC.
If you want to use the GUI features, please refer to MultipleSystemC-GUI.c
*/

#include <string.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

/* Include file for using StApiC. */
#include <StApi_C.h>

/* Counts of images to grab. */
const uint64_t nCountOfImagesToGrab = 100;

#define MAXIMUM_SYSTEM_COUNT StSystemVendor_Count


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


int main(int argc, char **argv)
{
	/* Initialize StApiC before using. */
	PApiFunctions psApiFunctions = NULL;
	EStApiCError_t eStApiCError = StApiCInitialize(STAPI_VERSION, &psApiFunctions);

	StApiHandle_t	pIStSystemHandleArray[MAXIMUM_SYSTEM_COUNT];
	StApiHandle_t sIStDeviceHandle = { NULL };
	StApiHandle_t sIStDataStreamHandle = { NULL };
	size_t nValidSystemCount = 0;

	if (eStApiCError != StApiCError_NoError)
	{
		printf("initializing StApiC was failed.\n");
		return(0);
	}
	memset(pIStSystemHandleArray, 0, sizeof(pIStSystemHandleArray));
	for (;;)
	{
		EStSystemVendor_t eSystemVendor;

		/* Create a system object list for store system object. */
		/* Then we try to create objects of all available systems. */
		for (eSystemVendor = StSystemVendor_Default; eSystemVendor < StSystemVendor_Count; eSystemVendor = (EStSystemVendor_t)(eSystemVendor + 1))
		{
			/* Create a system object. */
			StApiHandle_t sIStSystemHandle = { NULL };
			eStApiCError = psApiFunctions->StApi->IStSystem->CreateIStSystem(StSystemVendor_Default, StInterfaceType_All, &sIStSystemHandle);
			if (eStApiCError == StApiCError_NoError)
			{

				/* Add the system into system hancle list for later usage. */
				pIStSystemHandleArray[nValidSystemCount++] = sIStSystemHandle;
			}
		}

		/* Create a camera device object and connect to first detected device by using the function of system object. */
		eStApiCError = psApiFunctions->StApi->IStSystemArray->CreateFirstIStDevice(pIStSystemHandleArray, nValidSystemCount, DEVICE_ACCESS_CONTROL, &sIStDeviceHandle);
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

		/* Create a DataStream object for handling image stream data. */
		eStApiCError = psApiFunctions->StApi->IStDevice->CreateIStDataStream(&sIStDeviceHandle, 0, NULL, &sIStDataStreamHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Start the image acquisition of the host (local machine) side. */
		eStApiCError = psApiFunctions->StApi->IStDataStream->StartAcquisition(&sIStDataStreamHandle, nCountOfImagesToGrab, ACQ_START_FLAGS_DEFAULT);
		if (eStApiCError != StApiCError_NoError) break;

		/* Start the image acquisition of the camera side. */
		eStApiCError = psApiFunctions->StApi->IStDevice->AcquisitionStart(&sIStDeviceHandle);
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
					StApiHandle_t sIStStreamBufferInfoHandle = { NULL };
					uint64_t iFrameID;
					void *pBuffer = NULL;

					/* Display the information of the acquired image data. */
					eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStStreamBufferInfo(&sIStStreamBufferHandle, &sIStStreamBufferInfoHandle);
					if (eStApiCError != StApiCError_NoError) break;

					eStApiCError = psApiFunctions->StApi->IStStreamBufferInfo->GetFrameID(&sIStStreamBufferInfoHandle, &iFrameID);
					if (eStApiCError != StApiCError_NoError) break;

					eStApiCError = psApiFunctions->StApi->IStImage->GetImageBuffer(&sIStImageHandle, &pBuffer);
					if (eStApiCError != StApiCError_NoError) break;
					printf("BlockID=%" PRIu64 " Size: %zu x %zu First byte = %u\n", iFrameID, nImageWidth, nImageHeight, *(uint8_t*)pBuffer);
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

	if (sIStDataStreamHandle.Handle)
	{
		psApiFunctions->StApi->IStDataStream->Release(&sIStDataStreamHandle);
	}

	if (sIStDeviceHandle.Handle)
	{
		psApiFunctions->StApi->IStDevice->Release(&sIStDeviceHandle);
	}

	{
		size_t i;
		for (i = 0; i < nValidSystemCount; ++i)
		{
			psApiFunctions->StApi->IStSystem->Release(&pIStSystemHandleArray[i]);
		}
	};

	psApiFunctions->StApi->StApiCTerminate();

	/* Wait until the Enter key is pressed to end program. */
	printf("Press Enter to exit.");
	getchar();

	return 0;
}
