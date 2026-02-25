/*!
\file SaveAndLoadImageC.c
\brief

This sample shows how to save a captured image into RAW file of StApiC.
After saving to RAW file, this sample will load the file, convert it to BGR8 image, and save as BMP/TIF/PNG/JPG files.
The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to camera
- Acquire 1 image data (with waiting in main thread)
- Save image to / Load image from file.
- Apply Pixel format conversion
- Create image buffer for processing the image

For more information, please refer to the help document of StApiC.

*/
#include <stdlib.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

/* Include file for using StApiC. */
#include <StApi_C.h>

#define MAX_PATH 255

/* Count of images to be grabbed. We'll only get 1 image to demo how to save image file. */
const uint64_t nCountOfImagesToGrab = 1;


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

	StApiHandle_t sIStSystemHandle = { NULL };
	StApiHandle_t sIStDeviceHandle = { NULL };
	StApiHandle_t sIStDataStreamHandle = { NULL };
	StApiHandle_t sIStStillImageFilerHandle = { NULL };
	StApiHandle_t sIStImageBufferHandle = { NULL };
	StApiHandle_t sIStPixelFormatConverterHandle = { NULL };

	if (eStApiCError != StApiCError_NoError)
	{
		printf("initializing StApiC was failed.\n");
		return(0);
	}

	for (;;)
	{
		char szFileNameHeader[MAX_PATH + 65];
		char szFileNameRaw[MAX_PATH + 96];
		bool8_t isImageSaved = false;
		StApiHandle_t sIStStreamBufferHandle = { NULL };
		StApiHandle_t sIStStreamBufferInfoHandle = { NULL };
		bool8_t isImagePresent;

		/* Create a system object for device scan and connection. */
		eStApiCError = psApiFunctions->StApi->IStSystem->CreateIStSystem(StSystemVendor_Default, StInterfaceType_All, &sIStSystemHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Create a camera device object and connect to first detected device by using the function of system object. */
		eStApiCError = psApiFunctions->StApi->IStSystem->CreateFirstIStDevice(&sIStSystemHandle, DEVICE_ACCESS_CONTROL, &sIStDeviceHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Displays the DisplayName of the device. */
		{
			StApiHandle_t sIStDeviceInfoHandle = { NULL };
			char szDisplayName[64];
			char szPath[MAX_PATH];
			size_t nLen = sizeof(szDisplayName);

			eStApiCError = psApiFunctions->StApi->IStDevice->GetIStDeviceInfo(&sIStDeviceHandle, &sIStDeviceInfoHandle);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->StApi->IStDeviceInfo->GetDisplayNameA(&sIStDeviceInfoHandle, szDisplayName, &nLen);
			if (eStApiCError != StApiCError_NoError) break;

			printf("Device=%s\n", szDisplayName);

            /* Get path of tmp for further usage and set up the file name. */
            if (getenv("TMPDIR") != NULL)
                sprintf(szPath, "%s", getenv("TMPDIR"));
            else
                sprintf(szPath, "/tmp");

            sprintf(szFileNameHeader, "%s/%s.", szPath, szDisplayName);
            sprintf(szFileNameRaw, "%s%s", szFileNameHeader, "StApiRaw");
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
		Retrieve the buffer pointer of image data with a timeout of 5000ms. 
		Note that we don't use a while loop here because we only retrieve one image for saving.
		*/
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
			uint64_t iFrameID;
			void *pBuffer = NULL;

			/* If yes, we create a IStImage object for further image handling. */
			eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStImage(&sIStStreamBufferHandle, &sIStImageHandle);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->StApi->IStImage->GetImageWidth(&sIStImageHandle, &nImageWidth);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->StApi->IStImage->GetImageHeight(&sIStImageHandle, &nImageHeight);
			if (eStApiCError != StApiCError_NoError) break;

			/* Display the information of the acquired image data. */
			eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStStreamBufferInfo(&sIStStreamBufferHandle, &sIStStreamBufferInfoHandle);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->StApi->IStStreamBufferInfo->GetFrameID(&sIStStreamBufferInfoHandle, &iFrameID);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->StApi->IStImage->GetImageBuffer(&sIStImageHandle, &pBuffer);
			if (eStApiCError != StApiCError_NoError) break;

			printf("BlockID=%" PRIu64 " Size: %zu x %zu First byte = %u\n", iFrameID, nImageWidth, nImageHeight, *(uint8_t*)pBuffer);

			/* Create a still image file handling class object (filer) for still image processing. */
			eStApiCError = psApiFunctions->StApi->IStFiler->CreateIStFiler(StFilerType_StillImage, &sIStStillImageFilerHandle);
			if (eStApiCError != StApiCError_NoError) break;

			/* Save the image file as StApiRaw file format with using the filer we created. */
			printf("Saving %s ...", szFileNameRaw);
			eStApiCError = psApiFunctions->StApi->IStStillImageFiler->SaveA(&sIStStillImageFilerHandle, &sIStImageHandle, StStillImageFileFormat_StApiRaw, szFileNameRaw);
			if (eStApiCError != StApiCError_NoError) break;
			printf(" done\n");

			eStApiCError = psApiFunctions->StApi->IStFiler->Release(&sIStStillImageFilerHandle);
			if (eStApiCError != StApiCError_NoError) break;

			isImageSaved = true;
		}
		else
		{
			/* If the acquired data contains no image data... */
			printf("Image data does not exist\n");
		}

		eStApiCError = psApiFunctions->StApi->IStStreamBuffer->Release(&sIStStreamBufferHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Stop the image acquisition of the camera side. */
		psApiFunctions->StApi->IStDevice->AcquisitionStop(&sIStDeviceHandle);

		/* Stop the image acquisition of the host side. */
		psApiFunctions->StApi->IStDataStream->StopAcquisition(&sIStDataStreamHandle, ACQ_STOP_FLAGS_DEFAULT);
		
		/* The following code shows how to load the saved StApiRaw and process it. */
		if (isImageSaved)
		{
			StApiHandle_t sIStImageHandle = { NULL };

			/* Create a still image file handling class object (filer) for still image processing. */
			eStApiCError = psApiFunctions->StApi->IStFiler->CreateIStFiler(StFilerType_StillImage, &sIStStillImageFilerHandle);
			if (eStApiCError != StApiCError_NoError) break;

			/* Create a buffer for storing the image data from StApiRaw file. */
			eStApiCError = psApiFunctions->StApi->IStImageBuffer->CreateIStImageBuffer(NULL, &sIStImageBufferHandle);
			if (eStApiCError != StApiCError_NoError) break;
			
			{
				/* Load the image from the StApiRaw file into buffer. */
				printf("Loading %s ...", szFileNameRaw);
				eStApiCError = psApiFunctions->StApi->IStStillImageFiler->LoadA(&sIStStillImageFilerHandle, &sIStImageBufferHandle, szFileNameRaw);
				if (eStApiCError != StApiCError_NoError) break;
				printf(" done\n");

				/* Create a data converter object for pixel format conversion. */
				eStApiCError = psApiFunctions->StApi->IStConverter->CreateIStConverter(StConverterType_PixelFormat, &sIStPixelFormatConverterHandle);
				if (eStApiCError != StApiCError_NoError) break;

				/* Convert the image data to StPFNC_BGR8 format */
				eStApiCError = psApiFunctions->StApi->IStPixelFormatConverter->SetDestinationPixelFormat(&sIStPixelFormatConverterHandle, StPFNC_BGR8);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->StApi->IStImageBuffer->GetIStImage(&sIStImageBufferHandle, &sIStImageHandle);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->StApi->IStConverter->Convert(&sIStPixelFormatConverterHandle, &sIStImageHandle, &sIStImageBufferHandle);
				if (eStApiCError != StApiCError_NoError) break;


				/* Get the IStImage interface pointer to the converted image data. */
				eStApiCError = psApiFunctions->StApi->IStImageBuffer->GetIStImage(&sIStImageBufferHandle, &sIStImageHandle);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->StApi->IStConverter->Release(&sIStPixelFormatConverterHandle);
				if (eStApiCError != StApiCError_NoError) break;
			}


			{
				typedef struct
				{
					EStStillImageFileFormat_t eStillImageFileFormat;
					const char * const szExt;
				} SSTILL_IMAGE_FORMAT;
				SSTILL_IMAGE_FORMAT psStillImageFormats[] = {
					{ StStillImageFileFormat_Bitmap, "bmp" },
					{ StStillImageFileFormat_TIFF, "tif" },
					{ StStillImageFileFormat_PNG, "png" },
					{ StStillImageFileFormat_JPEG, "jpg" },
					{ StStillImageFileFormat_CSV, "csv" },
				};
				size_t i;

				for (i = 0; i < sizeof(psStillImageFormats) / sizeof(SSTILL_IMAGE_FORMAT); ++i)
				{
					char szFileName[MAX_PATH + 65];

					sprintf(szFileName, "%s%s", szFileNameHeader, psStillImageFormats[i].szExt);

					printf("Saving %s ...", szFileName);
					eStApiCError = psApiFunctions->StApi->IStStillImageFiler->SaveA(&sIStStillImageFilerHandle, &sIStImageHandle, psStillImageFormats[i].eStillImageFileFormat, szFileName);
					if (eStApiCError != StApiCError_NoError) break;
					printf(" done\n");
				}
			}
			eStApiCError = psApiFunctions->StApi->IStFiler->Release(&sIStStillImageFilerHandle);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->StApi->IStImageBuffer->Release(&sIStImageBufferHandle);
			if (eStApiCError != StApiCError_NoError) break;
		}

		
		break;
	}

	if (eStApiCError != StApiCError_NoError)
	{
		/* If any error occurred, display the description of the error here. */
		OutputErrorInfo(psApiFunctions);
	}

	if (sIStPixelFormatConverterHandle.Handle)
	{
		psApiFunctions->StApi->IStConverter->Release(&sIStPixelFormatConverterHandle);
	}

	if (sIStStillImageFilerHandle.Handle)
	{
		psApiFunctions->StApi->IStFiler->Release(&sIStStillImageFilerHandle);
	}

	if (sIStImageBufferHandle.Handle)
	{
		psApiFunctions->StApi->IStImageBuffer->Release(&sIStImageBufferHandle);
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
