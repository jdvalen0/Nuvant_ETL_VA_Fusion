/*!
\file SaveVideoC.c
\brief

This sample shows how to save acquired image as AVI video file.
The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to camera
- Create AVI video file

For more information, please refer to the help document of StApiC.
If you want to use the GUI features, please refer to SaveVideoC-GUI.c

*/

#include <stdlib.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

/* Include file for using StApiC. */
#include <StApi_C.h>

#define MAX_PATH 255

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

/* Count of images to be grabbed. */
const uint64_t nCountOfImagesToGrab = 500;

/* The maximum number of images per file. */
const size_t iMaximumCountOfImagesPerFile = 200;

/* Count of video files. */
const size_t nCountOfVideoFiles = 3;


typedef struct _SCallbackParam_t
{
	PApiFunctions	pApiFunctions;
}SCallbackParam_t, *PSCallbackParam_t;


void OnStCallbackCFunction(PStApiHandle_t pIStCallbackParamBaseHandle, void* pContext)
{
	const PSCallbackParam_t pCallbackParam = (PSCallbackParam_t)pContext;
	const PApiFunctions psApiFunctions = pCallbackParam->pApiFunctions;
	EStApiCError_t eStApiCError = StApiCError_NoError;
	EStCallbackType_t eCallbackType;
	char szFileName[MAX_PATH];
	size_t nSize = sizeof(szFileName);

	eStApiCError = psApiFunctions->StApi->IStCallbackParamBase->GetCallbackType(pIStCallbackParamBaseHandle, &eCallbackType);
	if (eStApiCError != StApiCError_NoError) return;

	if (eCallbackType == StCallbackType_StApiIPEvent_VideoFilerOpen)
	{
		eStApiCError = psApiFunctions->StApi->IStCallbackParamStApiIPVideoFilerOpen->GetFileNameA(pIStCallbackParamBaseHandle, szFileName, &nSize);
		printf("Open:%s\n", szFileName);
	}
	else if (eCallbackType == StCallbackType_StApiIPEvent_VideoFilerClose)
	{
		eStApiCError = psApiFunctions->StApi->IStCallbackParamStApiIPVideoFilerClose->GetFileNameA(pIStCallbackParamBaseHandle, szFileName, &nSize);
		printf("Close:%s\n", szFileName);
	}
	else if (eCallbackType == StCallbackType_StApiIPEvent_VideoFilerError)
	{
		EStApiCError_t eVideoFilerError;
		eStApiCError = psApiFunctions->StApi->IStCallbackParamStApiIPVideoFilerError->GetException(pIStCallbackParamBaseHandle, &eVideoFilerError);
		printf("Error:%u\n", eVideoFilerError);

		OutputErrorInfo(psApiFunctions);
	}
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
	SCallbackParam_t sCallbackParam = { psApiFunctions };
	StApiHandle_t sIStVideoFilerHandle = { NULL };
	StApiHandle_t sIStRegisteredCallbackHandle = { NULL };

	if (eStApiCError != StApiCError_NoError)
	{
		printf("initializing StApiC was failed.\n");
		return(0);
	}
	for (;;)
	{
		StApiHandle_t sIStPortRemoteHandle = { NULL };
		StApiHandle_t sINodeMapRemoteHandle = { NULL };
		double fps = 60.0;
		double fpns = 0.00000006;
		StApiHandle_t sINodeAcquisitionFrameRateHandle = { NULL };
		char szPath[MAX_PATH];
		size_t i;
		bool8_t fFirstFrame = true;
		uint64_t nFirstFrameTimestamp = 0;

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

		/* Get the acquisition frame rate of the camera. */
		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapRemoteHandle, "AcquisitionFrameRate", &sINodeAcquisitionFrameRateHandle);
		if (eStApiCError != StApiCError_NoError) break;

		if (sINodeAcquisitionFrameRateHandle.Handle)
		{
			eStApiCError = psApiFunctions->GenApi->IFloat->GetValue(&sINodeAcquisitionFrameRateHandle, false, false, &fps);
			if (eStApiCError != StApiCError_NoError) break;

			fpns = fps / 1000000000.0;
		}

		/* Create a VideoFiler object for video file handling. */
		eStApiCError = psApiFunctions->StApi->IStFiler->CreateIStFiler(StFilerType_Video, &sIStVideoFilerHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Register a callback function. When an event occurs for IStVideoFiler, function registered is called. */
		eStApiCError = psApiFunctions->StApi->IStFiler->RegisterCallback(&sIStVideoFilerHandle, &OnStCallbackCFunction, (void*)&sCallbackParam, &sIStRegisteredCallbackHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Configure the video file settings. */
		eStApiCError = psApiFunctions->StApi->IStVideoFiler->SetMaximumFrameCountPerFile(&sIStVideoFilerHandle, iMaximumCountOfImagesPerFile);
		if (eStApiCError != StApiCError_NoError) break;
		eStApiCError = psApiFunctions->StApi->IStVideoFiler->SetVideoFileFormat(&sIStVideoFilerHandle, StVideoFileFormat_AVI2);
		if (eStApiCError != StApiCError_NoError) break;
		eStApiCError = psApiFunctions->StApi->IStVideoFiler->SetVideoFileCompression(&sIStVideoFilerHandle, StVideoFileCompression_MotionJPEG);
		if (eStApiCError != StApiCError_NoError) break;
		eStApiCError = psApiFunctions->StApi->IStVideoFiler->SetFPS(&sIStVideoFilerHandle, fps);
		if (eStApiCError != StApiCError_NoError) break;

		/* Get the path of tmp to store the video files. */
        if (getenv("TMPDIR") != NULL)
            sprintf(szPath, "%s", getenv("TMPDIR"));
        else
            sprintf(szPath, "/tmp");

		/* Register the file name of the video files */
		for (i = 0; i < nCountOfVideoFiles; i++)
		{
			char szFileName[MAX_PATH + 32];

			sprintf(szFileName, "%s/SaveVideo/%zu.avi", szPath, i);
			eStApiCError = psApiFunctions->StApi->IStVideoFiler->RegisterFileNameA(&sIStVideoFilerHandle, szFileName);
			if (eStApiCError != StApiCError_NoError) break;
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
			StApiHandle_t sIStStreamBufferInfoHandle = { NULL };
			bool8_t isImagePresent;
			StApiHandle_t sIStStreamBufferHandle = { NULL };

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
				StApiHandle_t sIStStreamBufferInfoHandle = { NULL };

				/* If yes, we create a IStImage object for further image handling. */
				eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStImage(&sIStStreamBufferHandle, &sIStImageHandle);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->StApi->IStImage->GetImageWidth(&sIStImageHandle, &nImageWidth);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->StApi->IStImage->GetImageHeight(&sIStImageHandle, &nImageHeight);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStStreamBufferInfo(&sIStStreamBufferHandle, &sIStStreamBufferInfoHandle);
				if (eStApiCError != StApiCError_NoError) break;

				{
					uint64_t iFrameID;
					void *pBuffer = NULL;

					/* Display the information of the acquired image data. */
					eStApiCError = psApiFunctions->StApi->IStStreamBufferInfo->GetFrameID(&sIStStreamBufferInfoHandle, &iFrameID);
					if (eStApiCError != StApiCError_NoError) break;

					eStApiCError = psApiFunctions->StApi->IStImage->GetImageBuffer(&sIStImageHandle, &pBuffer);
					if (eStApiCError != StApiCError_NoError) break;

					printf("BlockID=%" PRIu64 " Size: %zu x %zu First byte = %u\n", iFrameID, nImageWidth, nImageHeight, *(uint8_t*)pBuffer);
				}
				/* Calculating the frame number in consideration of the frame drop. */
				{
					uint32_t nFrameNo = 0;
					uint64_t nCurrentTimestamp;
					eStApiCError = psApiFunctions->StApi->IStStreamBufferInfo->GetTimestamp(&sIStStreamBufferInfoHandle, &nCurrentTimestamp);
					if (eStApiCError != StApiCError_NoError) break;

					if (fFirstFrame)
					{
						fFirstFrame = false;
						nFirstFrameTimestamp = nCurrentTimestamp;
					}
					else
					{
						const int64_t nDeltaNs = (int64_t)(nCurrentTimestamp - nFirstFrameTimestamp);
						const double dblFrameNo = nDeltaNs * fpns;
						nFrameNo = (uint32_t)(dblFrameNo + 0.5);
					}

					/* Add the image data to a video file. */
					eStApiCError = psApiFunctions->StApi->IStVideoFiler->RegisterIStImage(&sIStVideoFilerHandle, &sIStImageHandle, nFrameNo);
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

		/* Stop the image acquisition of the camera side. */
		psApiFunctions->StApi->IStDevice->AcquisitionStop(&sIStDeviceHandle);

		/* Stop the image acquisition of the host side. */
		psApiFunctions->StApi->IStDataStream->StopAcquisition(&sIStDataStreamHandle, ACQ_STOP_FLAGS_DEFAULT);

		psApiFunctions->StApi->IStDataStream->Release(&sIStVideoFilerHandle);
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

	if (sIStVideoFilerHandle.Handle)
	{
		psApiFunctions->StApi->IStFiler->Release(&sIStVideoFilerHandle);
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


