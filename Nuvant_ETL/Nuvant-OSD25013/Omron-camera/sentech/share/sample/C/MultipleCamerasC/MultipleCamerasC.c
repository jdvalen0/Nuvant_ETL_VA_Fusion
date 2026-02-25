/*!
\file MultipleCamerasC.c
\brief

This sample shows how to conect and get images from all available cameras.
The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to all available cameras
- Acquire image from the list of camera
You can see how to handle multiple cameras/stream objects in this sample.

For more information, please refer to the help document of StApiC.
*/

#include <string.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

/* Include file for using StApiC. */
#include <StApi_C.h>

/* Counts of images to grab. */
const uint64_t nCountOfImagesToGrab = 100;

#define MAXIMUM_DEVICE_COUNT 10


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


int main(int argc, char ** argv)
{
	/* Initialize StApiC before using. */
	PApiFunctions psApiFunctions = NULL;
	EStApiCError_t eStApiCError = StApiCInitialize(STAPI_VERSION, &psApiFunctions);

	StApiHandle_t sIStSystemHandle = { NULL };
	StApiHandle_t	pIStDeviceHandleArray[MAXIMUM_DEVICE_COUNT];
	StApiHandle_t	pIStDataStreamHandleArray[MAXIMUM_DEVICE_COUNT];
	size_t nValidDeviceCount = 0;

	if (eStApiCError != StApiCError_NoError)
	{
		printf("initializing StApiC was failed.\n");
		return(0);
	}

	memset(pIStDeviceHandleArray, 0, sizeof(pIStDeviceHandleArray));
	memset(pIStDataStreamHandleArray, 0, sizeof(pIStDataStreamHandleArray));

	for (;;)
	{
		/* Create a system object for device scan and connection. */
		eStApiCError = psApiFunctions->StApi->IStSystem->CreateIStSystem(StSystemVendor_Default, StInterfaceType_All, &sIStSystemHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Here we try to connect to all possible device with a do-while loop. */
		for (nValidDeviceCount = 0; nValidDeviceCount < MAXIMUM_DEVICE_COUNT;)
		{
			StApiHandle_t sIStDeviceHandle = { NULL };
			StApiHandle_t sIStDataStreamHandle = { NULL };

			/* Create a camera device object and connect to first detected device by using the function of system object. */
			eStApiCError = psApiFunctions->StApi->IStSystem->CreateFirstIStDevice(&sIStSystemHandle, DEVICE_ACCESS_CONTROL, &sIStDeviceHandle);
			if (eStApiCError != StApiCError_NoError) break;
			
			/* Add the camera into device object list for later usage. */
			pIStDeviceHandleArray[nValidDeviceCount] = sIStDeviceHandle;
			
			/* Create a DataStream object for handling image stream data. */
			eStApiCError = psApiFunctions->StApi->IStDevice->CreateIStDataStream(&sIStDeviceHandle, 0, NULL, &sIStDataStreamHandle);
			if (eStApiCError != StApiCError_NoError) break;

			/* Create a DataStream object for handling image stream data then add into DataStream list for later usage. */
			pIStDataStreamHandleArray[nValidDeviceCount] = sIStDataStreamHandle;

			++nValidDeviceCount;

			/* Displays the DisplayName of the device. */
			{
				StApiHandle_t sIStDeviceInfoHandle = { NULL };
				char szDisplayName[1024];
				size_t nLen = sizeof(szDisplayName);

				eStApiCError = psApiFunctions->StApi->IStDevice->GetIStDeviceInfo(&sIStDeviceHandle, &sIStDeviceInfoHandle);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->StApi->IStDeviceInfo->GetDisplayNameA(&sIStDeviceInfoHandle, szDisplayName, &nLen);
				if (eStApiCError != StApiCError_NoError) break;

				printf("Device%zu=%s\n", nValidDeviceCount, szDisplayName);
			}
		}

		if (eStApiCError != StApiCError_NoError)
		{
			if (nValidDeviceCount == 0)
			{
				break;
			}
		}

		/* Start the image acquisition of the host (local machine) side. */
		eStApiCError = psApiFunctions->StApi->IStDataStreamArray->StartAcquisition(pIStDataStreamHandleArray, nValidDeviceCount, nCountOfImagesToGrab, ACQ_START_FLAGS_DEFAULT);
		if (eStApiCError != StApiCError_NoError) break;

		/* Start the image acquisition of the camera side. */
		eStApiCError = psApiFunctions->StApi->IStDeviceArray->AcquisitionStart(pIStDeviceHandleArray, nValidDeviceCount);
		if (eStApiCError != StApiCError_NoError) break;

		/*
			A while loop for acquiring data and checking status.
		*/
		for (;;)
		{
			bool8_t isGrabbing;
			StApiHandle_t sIStStreamBufferHandle = { NULL };
			StApiHandle_t sIStStreamBufferInfoHandle = { NULL };
			bool8_t isImagePresent;

			/*
				Here we use DataStream list function to check if any cameras in the list is on grabbing.
			*/
			eStApiCError = psApiFunctions->StApi->IStDataStreamArray->IsGrabbingAny(pIStDataStreamHandleArray, nValidDeviceCount, &isGrabbing);
			if (eStApiCError != StApiCError_NoError) break;
			if (!isGrabbing) break;

			/* Retrieve data buffer pointer of image data from any camera with a timeout of 5000ms. */
			eStApiCError = psApiFunctions->StApi->IStDataStreamArray->RetrieveBuffer(pIStDataStreamHandleArray, nValidDeviceCount, 5000, &sIStStreamBufferHandle);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStStreamBufferInfo(&sIStStreamBufferHandle, &sIStStreamBufferInfoHandle);
			if (eStApiCError != StApiCError_NoError) break;

			/* Check if the acquired data contains image data. */
			eStApiCError = psApiFunctions->StApi->IStStreamBufferInfo->IsImagePresent(&sIStStreamBufferInfoHandle, &isImagePresent);
			if (eStApiCError != StApiCError_NoError) break;

			if (isImagePresent)
			{
				StApiHandle_t sIStStreamBufferInfoHandle = { NULL };
				uint64_t iFrameID;
				char szDisplayName[1024];
				double dblFPS = 0;

				/* Display the information of the acquired image data. */
				eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStStreamBufferInfo(&sIStStreamBufferHandle, &sIStStreamBufferInfoHandle);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->StApi->IStStreamBufferInfo->GetFrameID(&sIStStreamBufferInfoHandle, &iFrameID);
				if (eStApiCError != StApiCError_NoError) break;

				/* Displays the DisplayName of the device. */
				{
					StApiHandle_t sIStDataStreamHandle = { NULL };
					StApiHandle_t sIStDeviceHandle = { NULL };
					StApiHandle_t sIStDeviceInfoHandle = { NULL };
					size_t nLen = sizeof(szDisplayName);

					eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStDataStream(&sIStStreamBufferHandle, &sIStDataStreamHandle);
					if (eStApiCError != StApiCError_NoError) break;

					eStApiCError = psApiFunctions->StApi->IStDataStream->GetCurrentFPS(&sIStDataStreamHandle, &dblFPS);

					eStApiCError = psApiFunctions->StApi->IStDataStream->GetIStDevice(&sIStDataStreamHandle, &sIStDeviceHandle);
					if (eStApiCError != StApiCError_NoError) break;

					eStApiCError = psApiFunctions->StApi->IStDevice->GetIStDeviceInfo(&sIStDeviceHandle, &sIStDeviceInfoHandle);
					if (eStApiCError != StApiCError_NoError) break;

					eStApiCError = psApiFunctions->StApi->IStDeviceInfo->GetDisplayNameA(&sIStDeviceInfoHandle, szDisplayName, &nLen);
					if (eStApiCError != StApiCError_NoError) break;

				}

				printf("%s BlockID=%" PRIu64 " %.4fFPS\n", szDisplayName, iFrameID, dblFPS);
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
		psApiFunctions->StApi->IStDeviceArray->AcquisitionStop(pIStDeviceHandleArray, nValidDeviceCount);

		/* Stop the image acquisition of the host side. */
		psApiFunctions->StApi->IStDataStreamArray->StopAcquisition(pIStDataStreamHandleArray, nValidDeviceCount, ACQ_STOP_FLAGS_DEFAULT);

		break;
	}

	if (eStApiCError != StApiCError_NoError)
	{
		/* If any error occurred, display the description of the error here. */
		OutputErrorInfo(psApiFunctions);
	}

	{
		size_t i;
		for (i = 0; i < nValidDeviceCount; ++i)
		{
			psApiFunctions->StApi->IStDataStream->Release(&pIStDataStreamHandleArray[i]);
		}
	}

	{
		size_t i;
		for (i = 0; i < nValidDeviceCount; ++i)
		{
			psApiFunctions->StApi->IStDevice->Release(&pIStDeviceHandleArray[i]);
		}
	};

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
