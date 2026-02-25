/*!
\file FeatureListC-GUI.c
\brief

This sample will list all support functions of connected camera.
The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to camera
- Access Nodes of NodeMap for displaying camera's features

For more information, please refer to the help document of StApiC.
*/

#include <stdlib.h>

/* Include file for using StApiC. */
#include <StApi_C.h>

/* Counts of images to grab. */
const uint64_t nCountOfImagesToGrab = 100;

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


EStApiCError_t DisplayNodes(PApiFunctions psApiFunctions, PStApiHandle_t pINodeHandle, size_t nLevel)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;
	
	/* Create an NodeMap display window object. */
	StApiHandle_t sIStNodeMapDisplayWndHandle = { NULL };
	eStApiCError = psApiFunctions->StApi->IStWnd->CreateIStWnd(StWindowType_NodeMapDisplay, &sIStNodeMapDisplayWndHandle);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	for (;;)
	{

		/* Register the node to NodeMap window. */
		eStApiCError = psApiFunctions->StApi->IStNodeMapDisplayWnd->RegisterINodeA(&sIStNodeMapDisplayWndHandle, pINodeHandle, "Root", NULL);
		if (eStApiCError != StApiCError_NoError) break;;

		/* Set the position and size of the window. */
		eStApiCError = psApiFunctions->StApi->IStWnd->SetPosition(&sIStNodeMapDisplayWndHandle, 0, 0, 480, 640);
		if (eStApiCError != StApiCError_NoError) break;;

		/* Display the window. */
		eStApiCError = psApiFunctions->StApi->IStWnd->Show(&sIStNodeMapDisplayWndHandle, NULL, StWindowMode_Modal);

		break;
	}

	if (sIStNodeMapDisplayWndHandle.Handle)
	{
		psApiFunctions->StApi->IStWnd->Release(&sIStNodeMapDisplayWndHandle);
	}
	return(StApiCError_NoError);
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

	if (eStApiCError != StApiCError_NoError)
	{
		printf("initializing StApiC was failed.\n");
		return(0);
	}

	for (;;)
	{
		StApiHandle_t sIStPortRemoteHandle = { NULL };
		StApiHandle_t sINodeMapRemoteHandle = { NULL };
		StApiHandle_t sINodeHandle = { NULL };

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

		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapRemoteHandle, "Root", &sINodeHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Display nodes. */
		eStApiCError = DisplayNodes(psApiFunctions, &sINodeHandle, 0);

		break;
	}

	if (eStApiCError != StApiCError_NoError)
	{
		/* If any error occurred, display the description of the error here. */
		OutputErrorInfo(psApiFunctions);
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

