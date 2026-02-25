/*!
\file GrabCallbackC.c
\brief 

 This sample shows the way of using callback function to acquire image data from camera.
 The following points will be demonstrated in this sample code:
 - Initialize StApiC
 - Connect to camera
 - Register and use callback function with StApiC
 - Acquire image data via callback function
 You will need to acquire the callback type for further handling. The parameter of each type of callback will have different parameter.
 Please check OnCallback() function for the example of how to check the type of the callback.

 For more information, please refer to the help document of StApiC.
*/

/* If you want to use the GUI features, uncomment the following for defining ENABLED_ST_GUI with further operation. */
/* #define ENABLED_ST_GUI */

#include "kbhitc.h"
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

/* Include file for using StApiC. */
#include <StApi_C.h>


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


typedef struct _SCallbackParam_t
{
	PApiFunctions	pApiFunctions;
	PStApiHandle_t	pIStDataStreamHandle;
#ifdef ENABLED_ST_GUI
	PStApiHandle_t	pIStImageDisplayWndHandle;
#endif
}SCallbackParam_t, *PSCallbackParam_t;


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
#ifdef ENABLED_ST_GUI
			const PStApiHandle_t pDataStreamHandle = pCallbackParam->pIStDataStreamHandle;
			const PStApiHandle_t pIStImageDisplayWndHandle = pCallbackParam->pIStImageDisplayWndHandle;
			double dblFPS;
			char szStatusText[1024];
			bool8_t isVisible;

			/* Acquire detail information of received image and display it onto the status bar of the display window. */
			eStApiCError = psApiFunctions->StApi->IStDataStream->GetCurrentFPS(pDataStreamHandle, &dblFPS);
			if (eStApiCError != StApiCError_NoError) break;

			sprintf(szStatusText, "%zu x %zu %.2f[fps]", nImageWidth, nImageHeight, dblFPS);

			eStApiCError = psApiFunctions->StApi->IStWnd->SetUserStatusBarTextA(pIStImageDisplayWndHandle, szStatusText);
			if (eStApiCError != StApiCError_NoError) break;

			/* Check if display window is visible. */
			eStApiCError = psApiFunctions->StApi->IStWnd->IsVisible(pIStImageDisplayWndHandle, &isVisible);
			if (eStApiCError != StApiCError_NoError) break;

			if (!isVisible)
			{
				/* Set the position and size of the window. */
				eStApiCError = psApiFunctions->StApi->IStWnd->SetPosition(pIStImageDisplayWndHandle, 0, 0, (int32_t)nImageWidth, (int32_t)nImageHeight);
				if (eStApiCError != StApiCError_NoError) break;

				/* Create a new thread to display the window. */
				eStApiCError = psApiFunctions->StApi->IStWnd->Show(pIStImageDisplayWndHandle, NULL, StWindowMode_ModalessOnNewThread);
				if (eStApiCError != StApiCError_NoError) break;
			}

			/*
			Register the image to be displayed.
			This will have a copy of the image data and original buffer can be released if necessary and original buffer can be released if necessary.
			*/
			eStApiCError = psApiFunctions->StApi->IStImageDisplayWnd->RegisterIStImage(pIStImageDisplayWndHandle, &sIStImageHandle);
			if (eStApiCError != StApiCError_NoError) break;
#else
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
			printf("Press any key to exit. ");
#endif
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


int main(int argc, char **argv)
{
	/* Initialize StApiC before using. */
	PApiFunctions psApiFunctions = NULL;
	EStApiCError_t eStApiCError = StApiCInitialize(STAPI_VERSION, &psApiFunctions);

	StApiHandle_t sSystemHandle = { NULL };
	StApiHandle_t sIStDeviceHandle = { NULL };
	StApiHandle_t sIStDataStreamHandle = { NULL };

#ifdef ENABLED_ST_GUI
	StApiHandle_t sIStImageDisplayWndHandle = { NULL };
#endif
	SCallbackParam_t sCallbackParam =
	{
		psApiFunctions,
		&sIStDataStreamHandle,
#ifdef ENABLED_ST_GUI
		&sIStImageDisplayWndHandle,
#endif
	};

	if (eStApiCError != StApiCError_NoError)
	{
		printf("initializing StApiC was failed.\n");
		return(0);
	}
	for (;;)
	{
		StApiHandle_t	sIStRegisteredCallbackHandle = { NULL };
		const uint64_t iNumToAcquire = GENTL_INFINITE;

		/* Create a system object for device scan and connection. */
		eStApiCError = psApiFunctions->StApi->IStSystem->CreateIStSystem(StSystemVendor_Default, StInterfaceType_All, &sSystemHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Create a camera device object and connect to first detected device by using the function of system object. */
		eStApiCError = psApiFunctions->StApi->IStSystem->CreateFirstIStDevice(&sSystemHandle, DEVICE_ACCESS_CONTROL, &sIStDeviceHandle);
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

#ifdef ENABLED_ST_GUI
		/* If using GUI for display, create a display window here. */
		eStApiCError = psApiFunctions->StApi->IStWnd->CreateIStWnd(StWindowType_ImageDisplay, &sIStImageDisplayWndHandle);
		if (eStApiCError != StApiCError_NoError) break;
#endif

		/* Create a DataStream object for handling image stream data. */
		eStApiCError = psApiFunctions->StApi->IStDevice->CreateIStDataStream(&sIStDeviceHandle, 0, NULL, &sIStDataStreamHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->StApi->IStDataStream->RegisterCallback(&sIStDataStreamHandle, &OnDataStreamCallback, (void*)&sCallbackParam, &sIStRegisteredCallbackHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->StApi->IStDataStream->StartAcquisition(&sIStDataStreamHandle, iNumToAcquire, ACQ_START_FLAGS_DEFAULT);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->StApi->IStDevice->AcquisitionStart(&sIStDeviceHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Wait until key is pressed to end program. */
		printf("Press any key to exit.\n");
        for (;;)
        {
#ifdef ENABLED_ST_GUI
            /* Check if display window is visible. */
            bool8_t isVisible;
            eStApiCError = psApiFunctions->StApi->IStWnd->IsVisible(&sIStImageDisplayWndHandle, &isVisible);
            if (eStApiCError != StApiCError_NoError) break;
            if (!isVisible)
            {
                eStApiCError = psApiFunctions->StApi->IStWnd->Show(&sIStImageDisplayWndHandle, NULL, StWindowMode_Modaless);
                if (eStApiCError != StApiCError_NoError) break;
            }
            psApiFunctions->StApi->IStWnd->ProcessEventGUI(false, 0);
#endif
            if (_kbhit()) break;
        }

		psApiFunctions->StApi->IStDevice->AcquisitionStop(&sIStDeviceHandle);
		psApiFunctions->StApi->IStDataStream->StopAcquisition(&sIStDataStreamHandle, ACQ_STOP_FLAGS_DEFAULT);
		psApiFunctions->StApi->IStRegisteredCallback->Release(&sIStRegisteredCallbackHandle);

		break;
	}

	if (eStApiCError != StApiCError_NoError)
	{
		/* If any error occurred, display the description of the error here. */
		OutputErrorInfo(psApiFunctions);
	}

#ifdef ENABLED_ST_GUI
	if (sIStImageDisplayWndHandle.Handle)
	{
		psApiFunctions->StApi->IStWnd->Release(&sIStImageDisplayWndHandle);
	}
#endif

	if (sIStDataStreamHandle.Handle)
	{
		psApiFunctions->StApi->IStDataStream->Release(&sIStDataStreamHandle);
	}

	if (sIStDeviceHandle.Handle)
	{
		psApiFunctions->StApi->IStDevice->Release(&sIStDeviceHandle);
	}

	if (sSystemHandle.Handle)
	{
		psApiFunctions->StApi->IStSystem->Release(&sSystemHandle);
	}

	psApiFunctions->StApi->StApiCTerminate();

	return 0;
}

