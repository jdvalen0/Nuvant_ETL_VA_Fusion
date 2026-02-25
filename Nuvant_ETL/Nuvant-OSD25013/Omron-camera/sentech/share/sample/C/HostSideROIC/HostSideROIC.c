/*!
\file HostSideROIC.c
\brief

This sample shows how to divide image data into multiple ROI images in local side and display them.
The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to camera
- Acquire image data (with waiting in main thread)
- Process image ROI in host side (local computer)

For more information, please refer to the help document of StApiC.
*/

#include <string.h>

/* Include file for using StApiC. */
#include <StApi_C.h>

/* Count of images to be grabbed. */
const uint64_t nCountOfImagesToGrab = 2000;

/* Count of regions of each direction. */
#define HORIZONTAL_ROI_COUNT 2
#define VERTICAL_ROI_COUNT 1
#define TOTAL_ROI_COUNT (HORIZONTAL_ROI_COUNT * VERTICAL_ROI_COUNT)

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

*/
int main(int argc, char **argv)
{
	/* Initialize StApiC before using. */
	PApiFunctions psApiFunctions = NULL;
	EStApiCError_t eStApiCError = StApiCInitialize(STAPI_VERSION, &psApiFunctions);

	StApiHandle_t sIStSystemHandle = { NULL };
	StApiHandle_t sIStDeviceHandle = { NULL };
	StApiHandle_t sIStDataStreamHandle = { NULL };

	/* For display whole Image */
	StApiHandle_t sIStImageDisplayWndHandle = { NULL };

	/* For display ROI Images */
	StApiHandle_t pIStImageDisplayWndHandleArray[TOTAL_ROI_COUNT];

	if (eStApiCError != StApiCError_NoError)
	{
		printf("initializing StApiC was failed.\n");
		return(0);
	}

	memset(pIStImageDisplayWndHandleArray, 0, sizeof(pIStImageDisplayWndHandleArray));
	for (;;)
	{
		StApiHandle_t sIStPortRemoteHandle = { NULL };
		StApiHandle_t sINodeMapRemoteHandle = { NULL };
		int64_t pnImageSize[2];
		StApiHandle_t sIIntegerWidthHandle = { NULL };
		StApiHandle_t sIIntegerHeightHandle = { NULL };
		StApiHandle_t sIEnumerationPixelFormatHandle = { NULL };
		int64_t nTmp;
		StApiHandle_t sIStPixelFormatInfoHandle = { NULL };
		size_t pnPixelIncrement[2];
		const size_t pnROIWindowCount[] = { HORIZONTAL_ROI_COUNT, VERTICAL_ROI_COUNT };
		int32_t pnROIImageSize[2];
		size_t i;
		size_t y;

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

		/* Get current setting of the image size. */
		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapRemoteHandle, "Width", &sIIntegerWidthHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->GenApi->IInteger->GetValue(&sIIntegerWidthHandle, false, false, &pnImageSize[0]);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapRemoteHandle, "Height", &sIIntegerHeightHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->GenApi->IInteger->GetValue(&sIIntegerHeightHandle, false, false, &pnImageSize[1]);
		if (eStApiCError != StApiCError_NoError) break;

		/* Get current pixel format information. */
		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapRemoteHandle, "PixelFormat", &sIEnumerationPixelFormatHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->GenApi->IEnumeration->GetIntValue(&sIEnumerationPixelFormatHandle, false, false, &nTmp);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->StApi->IStPixelFormatInfo->GetIStPixelFormatInfo((EStPixelFormatNamingConvention_t)nTmp, &sIStPixelFormatInfoHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Get the minimum setting unit of both sides (X and Y). */
		eStApiCError = psApiFunctions->StApi->IStPixelFormatInfo->GetPixelIncrementX(&sIStPixelFormatInfoHandle, &pnPixelIncrement[0]);
		if (eStApiCError != StApiCError_NoError) break;
		eStApiCError = psApiFunctions->StApi->IStPixelFormatInfo->GetPixelIncrementY(&sIStPixelFormatInfoHandle, &pnPixelIncrement[1]);
		if (eStApiCError != StApiCError_NoError) break;

		/* Calculate the size of the ROI. */
		for(i = 0; i < 2; i++)
		{
			int32_t nSize = (int32_t)(pnImageSize[i] / pnROIWindowCount[i]);
			nSize -= (int32_t)(nSize % pnPixelIncrement[i]);
			pnROIImageSize[i] = nSize;
		}

		i = 0;
		for (y = 0; y < pnROIWindowCount[1]; y++)
		{
			size_t x;
			for (x = 0; x < pnROIWindowCount[0]; x++)
			{
				StApiHandle_t sIStImageDisplayWndTmpHandle = { NULL };
				eStApiCError = psApiFunctions->StApi->IStWnd->CreateIStWnd(StWindowType_ImageDisplay, &sIStImageDisplayWndTmpHandle);
				if (eStApiCError != StApiCError_NoError) break;

				pIStImageDisplayWndHandleArray[i] = sIStImageDisplayWndTmpHandle;

				/* Set the position and size of the window. */
				eStApiCError = psApiFunctions->StApi->IStWnd->SetPosition(&sIStImageDisplayWndTmpHandle, (int32_t)(x * pnROIImageSize[0]), (int32_t)(y * pnROIImageSize[1]), pnROIImageSize[0], pnROIImageSize[1]);
				if (eStApiCError != StApiCError_NoError) break;

				++i;
			}
		}

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
				double dblFPS;
				char szStatusText[1024];
				bool8_t isVisible;
				size_t nIndex = 0;

				/* If yes, we create a IStImage object for further image handling. */
				eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStImage(&sIStStreamBufferHandle, &sIStImageHandle);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->StApi->IStImage->GetImageWidth(&sIStImageHandle, &nImageWidth);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->StApi->IStImage->GetImageHeight(&sIStImageHandle, &nImageHeight);
				if (eStApiCError != StApiCError_NoError) break;

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
				
				/* Display each ROI image in different window. */
				for (y = 0; y < pnROIWindowCount[1]; y++)
				{
					size_t x;
					for (x = 0; x < pnROIWindowCount[0]; x++)
					{
						StApiHandle_t sIStImageROIHandle = { NULL };
						PStApiHandle_t pIStImageDisplayWndROIHandle = &pIStImageDisplayWndHandleArray[nIndex];

						/* Get the ROI image with IStImage object. */
						eStApiCError = psApiFunctions->StApi->IStImage->GetROIImage(&sIStImageHandle, x * pnROIImageSize[0], y * pnROIImageSize[1], pnROIImageSize[0], pnROIImageSize[1], &sIStImageROIHandle);
						if (eStApiCError != StApiCError_NoError) break;

						/* Check if display window is visible. */
						eStApiCError = psApiFunctions->StApi->IStWnd->IsVisible(pIStImageDisplayWndROIHandle, &isVisible);
						if (eStApiCError != StApiCError_NoError) break;

						if (!isVisible)
						{
							/* Create a new thread to display the window. */
							eStApiCError = psApiFunctions->StApi->IStWnd->Show(pIStImageDisplayWndROIHandle, NULL, StWindowMode_ModalessOnNewThread);
							if (eStApiCError != StApiCError_NoError) break;
						}

						/*
						Register the image to be displayed.
						This will have a copy of the image data and original buffer can be released if necessary and original buffer can be released if necessary.
						*/
						eStApiCError = psApiFunctions->StApi->IStImageDisplayWnd->RegisterIStImage(pIStImageDisplayWndROIHandle, &sIStImageROIHandle);
						if (eStApiCError != StApiCError_NoError) break;

						++nIndex;
					}
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

	
	{
		size_t i;
		for (i = 0; i < TOTAL_ROI_COUNT; ++i)
		{
			psApiFunctions->StApi->IStWnd->Release(&pIStImageDisplayWndHandleArray[i]);
		}
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

