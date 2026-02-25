/*!
\file CameraSideROIC.c
\brief

This sample shows how to set ROI in camera side and handle the image data.
The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to camera
- Set image ROI parameter
- Acquire image data (with waiting in main thread)
- Process the acquired ROI images

For more information, please refer to the help document of StApiC.
If you want to use the GUI features, please refer to CameraSideROIC-GUI.c
*/

#include <stdlib.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

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
List up the contents of current enumeration node with current setting.
*/
EStApiCError_t EnumerationNode(PApiFunctions psApiFunctions, PStApiHandle_t pINodeMapHandle, const char *szEnumerationName)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;
	PStApiHandle_t psIEnumEntryHandleArray = NULL;

	for (;;)
	{
		StApiHandle_t sIEnumerationHandle = { NULL };
		bool8_t isWritable;
		size_t nCount;
		int64_t nCurrentValue;
		size_t nIndex;

		/* Get the IEnumeration interface handle */
		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, szEnumerationName, &sIEnumerationHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Check the node is writable. */
		eStApiCError = psApiFunctions->GenApi->IBase->IsWritable(&sIEnumerationHandle, &isWritable);
		if (eStApiCError != StApiCError_NoError) break;
		if (!isWritable) break;

		/* Get a count of the entries. */
		eStApiCError = psApiFunctions->GenApi->IEnumeration->GetEntries(&sIEnumerationHandle, NULL, &nCount);
		if (eStApiCError != StApiCError_NoError) break;

		/* Allocate memory for the interfaces of the entries. */
		psIEnumEntryHandleArray = (PStApiHandle_t)malloc(sizeof(StApiHandle_t) * nCount);
		if (psIEnumEntryHandleArray == NULL) break;

		/* Get the entries. */
		eStApiCError = psApiFunctions->GenApi->IEnumeration->GetEntries(&sIEnumerationHandle, psIEnumEntryHandleArray, &nCount);
		if (eStApiCError != StApiCError_NoError) break;

		/* Get a current integer value of the node. */
		eStApiCError = psApiFunctions->GenApi->IEnumeration->GetIntValue(&sIEnumerationHandle, false, false, &nCurrentValue);
		if (eStApiCError != StApiCError_NoError) break;

		/*  Display a configurable options. */
		printf("%s\n", szEnumerationName);

		/* Get enumeration entries. */
		for (nIndex = 0; nIndex < nCount; ++nIndex)
		{
			bool8_t isAvailable;

			eStApiCError = psApiFunctions->GenApi->IBase->IsAvailable(&psIEnumEntryHandleArray[nIndex], &isAvailable);
			if (eStApiCError != StApiCError_NoError) break;
			if (isAvailable)
			{
				char szText[256];
				size_t nSize = sizeof(szText);
				int64_t nEntryValue;

				eStApiCError = psApiFunctions->GenApi->IEnumEntry->GetSymbolicA(&psIEnumEntryHandleArray[nIndex], szText, &nSize);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->GenApi->IEnumEntry->GetValue(&psIEnumEntryHandleArray[nIndex], &nEntryValue);
				if (eStApiCError != StApiCError_NoError) break;

				printf("%zu : %s%s\n", nIndex, szText, (nCurrentValue == nEntryValue) ? " (Current)" : "");
			}
		}
		if (eStApiCError != StApiCError_NoError) break;

		printf("Select : ");

		/* Waiting for input. */
		scanf("%zu", &nIndex);

		/* Reflect the value entered. */
		if (nIndex < nCount)
		{
			int64_t nEntryValue;

			eStApiCError = psApiFunctions->GenApi->IEnumEntry->GetValue(&psIEnumEntryHandleArray[nIndex], &nEntryValue);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->GenApi->IEnumeration->SetIntValue(&sIEnumerationHandle, nEntryValue, false);
		}
		break;
	}

	if (psIEnumEntryHandleArray != NULL)
	{
		free(psIEnumEntryHandleArray);
		psIEnumEntryHandleArray = NULL;
	}
	return(eStApiCError);
}
/*
List up the numeric value of the current setting that the node indicated.
*/
EStApiCError_t IntegerNode(PApiFunctions psApiFunctions, PStApiHandle_t pINodeMapHandle, const char *szNodeName)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;
	StApiHandle_t sIIntegerHandle = { NULL };
	bool8_t isWritable;

	/* Get the IInteger interface handle */
	eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, szNodeName, &sIIntegerHandle);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	eStApiCError = psApiFunctions->GenApi->IBase->IsWritable(&sIIntegerHandle, &isWritable);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	if (isWritable)
	{
		for (;;)
		{
			int64_t nMin;
			int64_t nMax;
			int64_t nCurrent;
			EIncMode eIncMode;
			int64_t nValue;

			eStApiCError = psApiFunctions->GenApi->IInteger->GetMin(&sIIntegerHandle, &nMin);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			eStApiCError = psApiFunctions->GenApi->IInteger->GetMax(&sIIntegerHandle, &nMax);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			eStApiCError = psApiFunctions->GenApi->IInteger->GetValue(&sIIntegerHandle, false, false, &nCurrent);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			eStApiCError = psApiFunctions->GenApi->IInteger->GetIncMode(&sIIntegerHandle, &eIncMode);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			/* Display the feature name, range, current value, and incremental value. */
			printf("%s Min=%" PRId64 " Max=%" PRId64 " Current=%" PRId64, szNodeName, nMin, nMax, nCurrent);

			if (eIncMode == fixedIncrement)
			{
				int64_t nInc;

				eStApiCError = psApiFunctions->GenApi->IInteger->GetInc(&sIIntegerHandle, &nInc);
				if (eStApiCError != StApiCError_NoError) return(eStApiCError);
				printf(" Inc=%" PRId64, nInc);
			}
			printf("\nNew Value : ");

			/* Waiting for input of new value. */
			scanf("%" PRId64, &nValue);

			/* Reflect the value entered. */
			if ((nMin <= nValue) && (nValue <= nMax))
			{
				eStApiCError = psApiFunctions->GenApi->IInteger->SetValue(&sIIntegerHandle, nValue, false);
				break;
			}
		}
	}
	return(eStApiCError);
}

/* Use Numeric() to check and set the ROI region detail setting. */
EStApiCError_t EachRegion(PApiFunctions psApiFunctions, PStApiHandle_t pINodeMapHandle)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;

	/* Configure the OffsetX. */
	eStApiCError = IntegerNode(psApiFunctions, pINodeMapHandle, OFFSET_X);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	/* Configure the Width. */
	eStApiCError = IntegerNode(psApiFunctions, pINodeMapHandle, WIDTH);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	/* Configure the OffsetY. */
	eStApiCError = IntegerNode(psApiFunctions, pINodeMapHandle, OFFSET_Y);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	/* Configure the Height. */
	eStApiCError = IntegerNode(psApiFunctions, pINodeMapHandle, HEIGHT);
	return(eStApiCError);
}

/*

*/
EStApiCError_t CameraROISetting(PApiFunctions psApiFunctions, PStApiHandle_t pINodeMapHandle)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;

	StApiHandle_t sIEnumeration_RegionSelector = { NULL };
	bool8_t isWritable;

	/* Check and set PixelFormat. */
	eStApiCError = EnumerationNode(psApiFunctions, pINodeMapHandle, PIXEL_FORMAT);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	/*
	 Check and set CameraSideROI.
	 Get the IEnumeration interface pointer for RegionSelector.
	*/
	eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, REGION_SELECTOR, &sIEnumeration_RegionSelector);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	eStApiCError = psApiFunctions->GenApi->IBase->IsWritable(&sIEnumeration_RegionSelector, &isWritable);

	/* Check if target camera (the node represented) supports multi-ROI. */
	if (isWritable)
	{
		/* Multi ROI. */
		for (;;)
		{
			StApiHandle_t sIEnumeration_RegionMode = { NULL };
			StApiHandle_t sIEnumEntry_RegionModeOff = { NULL };
			int64_t nOffValue;
			int64_t nCurrentValue;
			char chrInput;

			eStApiCError = EnumerationNode(psApiFunctions, pINodeMapHandle, REGION_SELECTOR);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			/* Configure the RegionMode. */
			eStApiCError = EnumerationNode(psApiFunctions, pINodeMapHandle, REGION_MODE);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			/* Check whether the area is valid. */
			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, REGION_MODE, &sIEnumeration_RegionMode);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			eStApiCError = psApiFunctions->GenApi->IEnumeration->GetEntryByNameA(&sIEnumeration_RegionMode, "Off", &sIEnumEntry_RegionModeOff);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			eStApiCError = psApiFunctions->GenApi->IEnumEntry->GetValue(&sIEnumEntry_RegionModeOff, &nOffValue);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			eStApiCError = psApiFunctions->GenApi->IEnumeration->GetIntValue(&sIEnumeration_RegionMode, false, false, &nCurrentValue);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			if (nOffValue != nCurrentValue)
			{
				/* Configure the position and size of the region. */
				eStApiCError = EachRegion(psApiFunctions, pINodeMapHandle);
				if (eStApiCError != StApiCError_NoError) return(eStApiCError);
			}
			printf("Continue? (Yes:y, No:n) : ");
			for (;;)
			{
				chrInput = getchar();
				if ((chrInput == 'y') || (chrInput == 'n'))
				{
					break;
				}
			}
			if (chrInput == 'n') break;
		}
	}
	else
	{
		/*
			Single ROI.
			Configure the position and size of the region.
		*/
		eStApiCError = EachRegion(psApiFunctions, pINodeMapHandle);
	}

	getchar();

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
					uint64_t iFrameID = 0;
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
