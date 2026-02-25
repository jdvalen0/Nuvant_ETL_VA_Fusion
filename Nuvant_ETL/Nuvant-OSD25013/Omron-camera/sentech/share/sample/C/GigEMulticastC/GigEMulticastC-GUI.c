/*!
\file GigEMulticastC-GUI.c
\brief

This sample shows how to use the multicast function of GigE camera for multiple receivers.
The monitor clients must connect after any one client connect to camera in control mode.
The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to camera
- Acquire image data (with waiting in main thread)
- Connect to camera in control mode / monitor mode
- Multicast the image data
- Broadcast the image data

Note: If the firewall is enabled, you may not be able to get the image data.
For more information, please refer to the help document of StApiC.
*/

#include <pthread.h>
#include <stdlib.h>

/* Include file for using StApiC. */
#include <StApi_C.h>

/* Counts of images to grab. */
const uint64_t nCountOfImagesToGrab = 100;

/* Feature names */
const char * DESTINATION_IP_ADDRESS = "DestinationIPAddress";	/* Custom */
const char * DESTINATION_PORT = "DestinationPort";	/* Custom */
const char * TRANSMISSION_TYPE = "TransmissionType";	/* Custom */
const char * TRANSMISSION_TYPE_USE_CAMERA_CONFIGURATION = "UseCameraConfiguration";	/* Custom */

PApiFunctions psApiFunctions = NULL;
StApiHandle_t sIStSystemHandle = { NULL };
StApiHandle_t sIStDeviceHandle = { NULL };
StApiHandle_t sIStDataStreamHandle = { NULL };
StApiHandle_t sIStImageDisplayWndHandle = { NULL };
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

void *acquisitionWorker(void *arg)
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
#ifdef ENABLED_ST_GUI
                double dblFPS;
                char szStatusText[1024];
                bool8_t isVisible;

                /* Acquire detail information of received image and display it onto the status bar of the display window. */
                eStApiCError = psApiFunctions->StApi->IStDataStream->GetCurrentFPS(&sIStDataStreamHandle, &dblFPS);
                if (eStApiCError != StApiCError_NoError) break;

                sprintf(szStatusText, "%lu x %lu %.2f[fps]", nImageWidth, nImageHeight, dblFPS);

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
#endif
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

	if (eStApiCError != StApiCError_NoError)
	{
		printf("initializing StApiC was failed.\n");
		return(0);
	}
	for (;;)
	{
		StApiHandle_t sIIntegerDestIPAddressHandle = { NULL };
		char szDestIPAddress[256];
		size_t nLen = sizeof(szDestIPAddress);
		bool8_t isMonitor = false;
		StApiHandle_t sIStPortDSHandle = { NULL };
		StApiHandle_t sINodeMapDSHandle = { NULL };
		StApiHandle_t sIEnumerationTransmissionTypeHandle = { NULL };
		
		/*
		Select the connecting mode (control/monitor) of the camera.
		You can connect to a camera in monitor mode if it has already connected by other host with control mode.
		Note if you connect to a camera in monitor mode, you cannot modify the camera settings.
		*/
		for (;;)
		{
			char chrInput;

			printf("C : Control mode\n");
			printf("M : Monitor mode\n");
			printf("Select a mode : ");
			for (;;)
			{
				char chrTmp = getchar();
				if (chrTmp == '\n') break;
				chrInput = chrTmp;
			}

			if ((chrInput == 'C') || (chrInput == 'c') || (chrInput == 'M') || (chrInput == 'm'))
			{
				isMonitor = (chrInput == 'M') || (chrInput == 'm');
				break;
			}
		}
		
		/* Create a system object for device scan and connection. */
		eStApiCError = psApiFunctions->StApi->IStSystem->CreateIStSystem(StSystemVendor_Default, StInterfaceType_GigEVision, &sIStSystemHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Create a camera device object and connect to first detected device by using the function of system object. */
		eStApiCError = psApiFunctions->StApi->IStSystem->CreateFirstIStDevice(&sIStSystemHandle, isMonitor ? DEVICE_ACCESS_READONLY : DEVICE_ACCESS_CONTROL, &sIStDeviceHandle);
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

		/* Use INodeMap object to access current setting of the datastream. */
		eStApiCError = psApiFunctions->StApi->IStDataStream->GetIStPort(&sIStDataStreamHandle, &sIStPortDSHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->StApi->IStPort->GetINodeMap(&sIStPortDSHandle, &sINodeMapDSHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Get the IEnumeration interface pointer of TRANSMISSION_TYPE node. */
		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapDSHandle, TRANSMISSION_TYPE, &sIEnumerationTransmissionTypeHandle);
		if (eStApiCError != StApiCError_NoError) break;


		/* Get the setting obeying to the connection type. */
		if (isMonitor)
		{
			/* Get the setting that represents the transmission type to accept the current camera settings. */
			eStApiCError = psApiFunctions->GenApi->IEnumeration->SetStringValueA(&sIEnumerationTransmissionTypeHandle, TRANSMISSION_TYPE_USE_CAMERA_CONFIGURATION);
			if (eStApiCError != StApiCError_NoError) break;
		}
		else
		{
			PStApiHandle_t psIEnumEntryHandleArray = NULL;
			size_t nCount;

			/* Get a list of the transmission type */
			eStApiCError = psApiFunctions->GenApi->IEnumeration->GetEntries(&sIEnumerationTransmissionTypeHandle, NULL, &nCount);
			if (eStApiCError != StApiCError_NoError) break;

			/* Allocate memory for the interfaces of the entries. */
			psIEnumEntryHandleArray = (PStApiHandle_t)malloc(sizeof(StApiHandle_t) * nCount);
			if (psIEnumEntryHandleArray != NULL)
			{
				for (;;)
				{
					size_t i;
					uint32_t nIndex;

					/* Get the entries. */
					eStApiCError = psApiFunctions->GenApi->IEnumeration->GetEntries(&sIEnumerationTransmissionTypeHandle, psIEnumEntryHandleArray, &nCount);
					if (eStApiCError != StApiCError_NoError) break;

					/* Display a list of the transmission type. */
					printf("Supported transmission types is as follows.\n");
					for (i = 0; i < nCount; ++i)
					{
						char szSymbolic[256];
						size_t nLen = sizeof(szSymbolic);

						eStApiCError = psApiFunctions->GenApi->IEnumEntry->GetSymbolicA(&psIEnumEntryHandleArray[i], szSymbolic, &nLen);
						if (eStApiCError != StApiCError_NoError) break;

						printf("%zu : %s\n", i, szSymbolic);
					}
					printf("Select a transmission type : ");

					/* Waiting for input. */
					{
						char szInput[] = { '\0', '\0' };
						for (;;)
						{
							char chrTmp = getchar();
							if (chrTmp == '\n') break;
							szInput[0] = chrTmp;
						}
						nIndex = atoi(szInput);
					}

					if (nIndex < nCount)
					{
						int64_t nValue;

						/* Get the setting of the selected transmission type. */
						eStApiCError = psApiFunctions->GenApi->IEnumEntry->GetValue(&psIEnumEntryHandleArray[nIndex], &nValue);
						if (eStApiCError != StApiCError_NoError) break;

						eStApiCError = psApiFunctions->GenApi->IEnumeration->SetIntValue(&sIEnumerationTransmissionTypeHandle, nValue, false);
						if (eStApiCError != StApiCError_NoError) break;

						break;
					}
				}
			}
			free(psIEnumEntryHandleArray);
			psIEnumEntryHandleArray = NULL;
		}

		/* Get the destination IP address of the image data. */
		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapDSHandle, DESTINATION_IP_ADDRESS, &sIIntegerDestIPAddressHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->GenApi->IValue->ToStringA(&sIIntegerDestIPAddressHandle, false, false, szDestIPAddress, &nLen);
		if (eStApiCError != StApiCError_NoError) break;

		/* Display the destination IP address of the image data. */
		printf("Destination IP Address = %s\n", szDestIPAddress);

		/* Start the image acquisition of the host (local machine) side. */
		eStApiCError = psApiFunctions->StApi->IStDataStream->StartAcquisition(&sIStDataStreamHandle, nCountOfImagesToGrab, ACQ_START_FLAGS_DEFAULT);
		if (eStApiCError != StApiCError_NoError) break;

		if (!isMonitor)
		{
			/* Start the image acquisition of the camera side. */
			eStApiCError = psApiFunctions->StApi->IStDevice->AcquisitionStart(&sIStDeviceHandle);
			if (eStApiCError != StApiCError_NoError) break;
		}

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


        if (!isMonitor)
        {
            /* Stop the image acquisition of the camera side. */
            psApiFunctions->StApi->IStDevice->AcquisitionStop(&sIStDeviceHandle);
        }

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
