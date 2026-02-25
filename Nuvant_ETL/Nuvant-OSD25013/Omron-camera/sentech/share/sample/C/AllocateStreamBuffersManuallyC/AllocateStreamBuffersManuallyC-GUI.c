/*!
\file AllocateStreamBuffersManuallyC-GUI.c
\brief

This sample shows how to manually create buffer for streaming.
The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to camera
- Acquire image data (with waiting in main thread)
- Create your own memory allocator for handling stream data.

For more information, please refer to the help document of StApiC.
*/

#include <stdlib.h>
#include <pthread.h>

/* Include file for using StApiC. */
#include <StApi_C.h>

/* Target counts of image to be grabbed. */
const uint64_t nCountOfImagesToGrab = 100;

void OutputErrorInfo(PApiFunctions psApiFunctions)
{
	/* If any exception occurred, display the description of the error here. */
	char szText[1024];
	size_t nLen = sizeof(szText);
	EStApiCError_t eStApiCError = psApiFunctions->StApi->GetLastErrorDescriptionA(szText, &nLen);
	if (eStApiCError == StApiCError_NoError)
	{
		printf("Description:%s\r\n", szText);
	}
}

size_t m_nAllocateCount = 0;
size_t m_nDeallocateCount = 0;

PApiFunctions psApiFunctions = NULL;
StApiHandle_t sIStSystemHandle = { NULL };
StApiHandle_t sIStDeviceHandle = { NULL };
StApiHandle_t sIStAllocatorHandle = { NULL };
StApiHandle_t sIStDataStreamHandle = { NULL };
StApiHandle_t sIStImageDisplayWndHandle = { NULL };
bool8_t isThreadCompleted = false;

/* Function for memory allocation. */
void AllocateCallback(void **  ppBuffer, size_t  nSize, void **  ppContext)
{
	/* Display the requested memory size. */
	printf("Allocate[%zu] Size = %zu\n", m_nAllocateCount, nSize);

	/* Memory allocation of the requested size. */
	*ppBuffer = malloc(nSize);

	/*
		Assigning the number of allocation to pContext. 
		Value assigned to pContext is passed as an argument when the memory is deallocated.
	*/
	*(size_t*)ppContext = m_nAllocateCount;

	/* Record number of times the memory is allocated. */
	++m_nAllocateCount;
}
/* Function for memory deallocation. */
void DeallocateCallback(void *  pBuffer, size_t  nSize, void *  pContext)
{
	/* Display the size of the memory to be freed. */
	printf("Deallocate[%zu] Size = %zu (Allocate[%p])\n", m_nDeallocateCount, nSize, pContext);

	/* Free the allocated memory. */
	free(pBuffer);

	/* Record the number of times that the memory has been freed */
	++m_nDeallocateCount;
}
/* Function called when registered allocator is no longer needed. */
void OnDeregisterCallback(void)
{
	printf("OnDeregister Allocate Count=%zu, Deallocate Count=%zu\n", m_nAllocateCount, m_nDeallocateCount);
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
                    eStApiCError = psApiFunctions->StApi->IStWnd->Show(&sIStImageDisplayWndHandle, NULL, StWindowMode_ModalessOnNewThread);
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
            printf("Image data does not exist\r\n");
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

/*

*/
int main(int argc, char **argv)
{
	/* Initialize StApiC before using. */
	EStApiCError_t eStApiCError = StApiCInitialize(STAPI_VERSION, &psApiFunctions);

	if (eStApiCError != StApiCError_NoError)
	{
		printf("initializing StApiC was failed.\n");
		return(0);
	}

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

			printf("Device=%s\r\n", szDisplayName);
		}

		/* If using GUI for display, create a display window here. */
		eStApiCError = psApiFunctions->StApi->IStWnd->CreateIStWnd(StWindowType_ImageDisplay, &sIStImageDisplayWndHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Create a object for memory allocation. */
		eStApiCError = psApiFunctions->StApi->IStAllocator->CreateIStAllocator(AllocateCallback, DeallocateCallback, OnDeregisterCallback, &sIStAllocatorHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Create a DataStream object for handling image stream data. */
		eStApiCError = psApiFunctions->StApi->IStDevice->CreateIStDataStream(&sIStDeviceHandle, 0, &sIStAllocatorHandle, &sIStDataStreamHandle);
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

	if (sIStDataStreamHandle.Handle)
	{
		psApiFunctions->StApi->IStDataStream->Release(&sIStDataStreamHandle);
	}

	if (sIStAllocatorHandle.Handle)
	{
		psApiFunctions->StApi->IStAllocator->Release(&sIStAllocatorHandle);
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

