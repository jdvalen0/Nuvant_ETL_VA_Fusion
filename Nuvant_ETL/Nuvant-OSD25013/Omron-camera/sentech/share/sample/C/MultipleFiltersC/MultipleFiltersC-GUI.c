/*!
\file MultipleFiltersC-GUI.c
\brief

This sample shows how to process received image with multiple filters.
The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to camera
- Acquire image data (with waiting in main thread)
- Set up multiple filters
- Process image with multiple filters

For more information, please refer to the help document of StApiC.
*/

#include <pthread.h>
#include <string.h>

/* Include file for using StApiC. */
#include <StApi_C.h>

#define MAXIMUM_FILTER_COUNT 10

/* Counts of images to grab. */
const uint64_t nCountOfImagesToGrab = 5000;

PApiFunctions psApiFunctions = NULL;
StApiHandle_t sIStSystemHandle = { NULL };
StApiHandle_t sIStDeviceHandle = { NULL };
StApiHandle_t sIStDataStreamHandle = { NULL };
StApiHandle_t sIStNodeMapWndHandle = { NULL };
StApiHandle_t sIStImageDisplayWndHandle = { NULL };
StApiHandle_t	pIStFilterHandleArray[MAXIMUM_FILTER_COUNT];
size_t nValidFilterCount = 0;
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


EStApiCError_t SelectFilters(PApiFunctions psApiFunctions, PStApiHandle_t pIStDeviceHandle, PStApiHandle_t pIStFilterHandleArray, const size_t nMaxFilterCount, size_t *pnValidFilterCount)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;
	StApiHandle_t sIStPortRemoteHandle = { NULL };
	StApiHandle_t sINodeMapHandle = { NULL };
	StApiHandle_t sIEnumerationPixelFormatHandle = { NULL };
	int64_t nTmp;
	size_t nValidFilterCount = 0;

	/* Use INodeMap object to access current setting of the camera. */
	eStApiCError = psApiFunctions->StApi->IStDevice->GetRemoteIStPort(pIStDeviceHandle, &sIStPortRemoteHandle);
	if (eStApiCError != StApiCError_NoError)	return(eStApiCError);

	eStApiCError = psApiFunctions->StApi->IStPort->GetINodeMap(&sIStPortRemoteHandle, &sINodeMapHandle);
	if (eStApiCError != StApiCError_NoError)	return(eStApiCError);

	/* Get the IEnumeration interface pointer of PixelFormat node */
	eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "PixelFormat", &sIEnumerationPixelFormatHandle);
	if (eStApiCError != StApiCError_NoError)	return(eStApiCError);
	if (sIEnumerationPixelFormatHandle.Handle == NULL)
	{
		printf("PixelFormat node does not exist.\n");
		return(eStApiCError);
	}

	/* Get the current pixel format value */
	eStApiCError = psApiFunctions->GenApi->IEnumeration->GetIntValue(&sIEnumerationPixelFormatHandle, false, false, &nTmp);
	if (eStApiCError != StApiCError_NoError)	return(eStApiCError);

	for (;;)
	{
		EStPixelFormatNamingConvention_t nPFNC = (EStPixelFormatNamingConvention_t)nTmp;
		uint32_t i;
		uint32_t nInput;

		/* Display a filter that corresponds to the current pixel format as an option */
		for (i = 0; i < StFilterType_Count; i++)
		{
			StApiHandle_t sIStFilterInfoHandle = { NULL };
			bool8_t isSupported;

			eStApiCError = psApiFunctions->StApi->IStFilterInfo->GetIStFilterInfo((EStFilterType_t)i, &sIStFilterInfoHandle);
			if (eStApiCError != StApiCError_NoError)	break;

			eStApiCError = psApiFunctions->StApi->IStFilterInfo->IsSupported(&sIStFilterInfoHandle, nPFNC, &isSupported);
			if (eStApiCError != StApiCError_NoError)	break;

			if (isSupported)
			{
				char szFilterName[256];
				size_t nLen = sizeof(szFilterName);

				eStApiCError = psApiFunctions->StApi->IStFilterInfo->GetFilterNameA(&sIStFilterInfoHandle, szFilterName, &nLen);
				if (eStApiCError != StApiCError_NoError)	break;

				printf("%u : %s\n", i, szFilterName);
			}
		}
		printf("Else : Exit filter selection\n");
		printf("Input index of the filter to be inserted : ");

		/* Waiting for input. */
#if 1400 <= _MSC_VER
		scanf_s("%u", &nInput);
#else
		scanf("%u", &nInput);
#endif

		if (nInput < StFilterType_Count)
		{
			StApiHandle_t sIStFilterInfoHandle = { NULL };
			bool8_t isSupported;

			eStApiCError = psApiFunctions->StApi->IStFilterInfo->GetIStFilterInfo((EStFilterType_t)nInput, &sIStFilterInfoHandle);
			if (eStApiCError != StApiCError_NoError)	break;

			eStApiCError = psApiFunctions->StApi->IStFilterInfo->IsSupported(&sIStFilterInfoHandle, nPFNC, &isSupported);
			if (eStApiCError != StApiCError_NoError)	break;

			if (isSupported)
			{
				/*
				Create a selected filter object, to get the IStFilter interface handle.
				If the filter object is no longer needed, call the IStFilter->Release() to discard the filter object.
				*/
				StApiHandle_t sIStFilterHandle = { NULL };
				eStApiCError = psApiFunctions->StApi->IStFilter->CreateIStFilter((EStFilterType_t)nInput, &sIStFilterHandle);
				if (eStApiCError != StApiCError_NoError)	break;

				pIStFilterHandleArray[nValidFilterCount++] = sIStFilterHandle;
				if (nMaxFilterCount <= nValidFilterCount) break;
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}

	}
	*pnValidFilterCount = nValidFilterCount;
	return(eStApiCError);
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
            
            /*  Filter the acquired image. */
            eStApiCError = psApiFunctions->StApi->IStFilterArray->Filter(pIStFilterHandleArray, nValidFilterCount, &sIStImageHandle);
            if (eStApiCError != StApiCError_NoError) break;

            eStApiCError = psApiFunctions->StApi->IStImage->GetImageWidth(&sIStImageHandle, &nImageWidth);
            if (eStApiCError != StApiCError_NoError) break;

            eStApiCError = psApiFunctions->StApi->IStImage->GetImageHeight(&sIStImageHandle, &nImageHeight);
            if (eStApiCError != StApiCError_NoError) break;

            {
                /* Acquire detail information of received image and display it onto the status bar of the display window. */
                double dblFPS;
                char szStatusText[1024];
                bool8_t isVisible;

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
                    eStApiCError = psApiFunctions->StApi->IStWnd->Show(&sIStImageDisplayWndHandle, NULL, StWindowMode_Modaless);
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

	size_t i;

	if (eStApiCError != StApiCError_NoError)
	{
		printf("initializing StApiC was failed.\n");
		return(0);
	}

	memset(pIStFilterHandleArray, 0, sizeof(pIStFilterHandleArray));

	for (;;)
	{

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
		/* Select the filters. */
		eStApiCError = SelectFilters(psApiFunctions, &sIStDeviceHandle, pIStFilterHandleArray, sizeof(pIStFilterHandleArray) / sizeof(StApiHandle_t), &nValidFilterCount);
		if (eStApiCError != StApiCError_NoError) break;

		
		/* Create an NodeMap display window object. */
		eStApiCError = psApiFunctions->StApi->IStWnd->CreateIStWnd(StWindowType_NodeMapDisplay, &sIStNodeMapWndHandle);
		if (eStApiCError != StApiCError_NoError) break;

		for (i = 0; i < nValidFilterCount; ++i)
		{
			PStApiHandle_t pIStFilterHandle = &pIStFilterHandleArray[i];
			StApiHandle_t sIStFilterInfoHandle = { NULL };
			char szFilterName[256];
			size_t nLen = sizeof(szFilterName);
			StApiHandle_t sINodeMapHandle = { NULL };
			StApiHandle_t sINodeHandle = { NULL };

			eStApiCError = psApiFunctions->StApi->IStFilter->GetIStFilterInfo(pIStFilterHandle, &sIStFilterInfoHandle);
			if (eStApiCError != StApiCError_NoError)	break;

			eStApiCError = psApiFunctions->StApi->IStFilterInfo->GetFilterNameA(&sIStFilterInfoHandle, szFilterName, &nLen);
			if (eStApiCError != StApiCError_NoError)	break;

			/* Register the node to NodeMap window. */
			eStApiCError = psApiFunctions->StApi->IStFilter->GetINodeMap(pIStFilterHandle, &sINodeMapHandle);
			if (eStApiCError != StApiCError_NoError)	break;

			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "Root", &sINodeHandle);
			if (eStApiCError != StApiCError_NoError)	break;

			eStApiCError = psApiFunctions->StApi->IStNodeMapDisplayWnd->RegisterINodeA(&sIStNodeMapWndHandle, &sINodeHandle, szFilterName, NULL);
			if (eStApiCError != StApiCError_NoError)	break;
		};
		
		/* Set the position and size of the window. */
		eStApiCError = psApiFunctions->StApi->IStWnd->SetPosition(&sIStNodeMapWndHandle, 0, 0, 480, 1024);
		if (eStApiCError != StApiCError_NoError) break;

		/* Create a new thread to display the window. */
		eStApiCError = psApiFunctions->StApi->IStWnd->Show(&sIStNodeMapWndHandle, NULL, StWindowMode_Modaless);
		if (eStApiCError != StApiCError_NoError) break;

		/* If using GUI for display, create a display window here. */
		eStApiCError = psApiFunctions->StApi->IStWnd->CreateIStWnd(StWindowType_ImageDisplay, &sIStImageDisplayWndHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Create a DataStream object for handling image stream data. */
		eStApiCError = psApiFunctions->StApi->IStDevice->CreateIStDataStream(&sIStDeviceHandle, 0, NULL, &sIStDataStreamHandle);
		if (eStApiCError != StApiCError_NoError) break;

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
	if (sIStNodeMapWndHandle.Handle)
	{
		psApiFunctions->StApi->IStWnd->Release(&sIStNodeMapWndHandle);
	}

	if (sIStDataStreamHandle.Handle)
	{
		psApiFunctions->StApi->IStDataStream->Release(&sIStDataStreamHandle);
	}

	for (i = 0; i < nValidFilterCount; ++i)
	{
		PStApiHandle_t pIStFilterHandle = &pIStFilterHandleArray[i];
		psApiFunctions->StApi->IStFilter->Release(pIStFilterHandle);
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
