/*!
\file SaveAndLoadFeaturesC.c
\brief

This sample shows how to save/load camera setting with using featureBag.
The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to camera
- Save/load camera setting to/from file
- Apply the loaded setting to camera

For more information, please refer to the help document of StApiC.
*/

#include <stdlib.h>

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

/*

*/
int main(int argc, char **argv)
{
	/* Initialize StApiC before using. */
	PApiFunctions psApiFunctions = NULL;
	EStApiCError_t eStApiCError = StApiCInitialize(STAPI_VERSION, &psApiFunctions);

	StApiHandle_t sIStSystemHandle = { NULL };
	StApiHandle_t sIStDeviceHandle = { NULL };
	StApiHandle_t sIStFeatureBagHandle = { NULL };
	char *szFeatures = NULL;

	if (eStApiCError != StApiCError_NoError)
	{
		printf("initializing StApiC was failed.\n");
		return(0);
	}

	for (;;)
	{
		char szPath[MAX_PATH];
		char szFileName[MAX_PATH + 16];
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

		/* Get path of tmp for further usage. */
        if (getenv("TMPDIR") != NULL)
            sprintf(szPath, "%s", getenv("TMPDIR"));
        else
            sprintf(szPath, "/tmp");


		/* Set up file name. */
		sprintf(szFileName, "%s/Features.cfg", szPath);

		/* Use INodeMap object to access current setting of the camera. */
		eStApiCError = psApiFunctions->StApi->IStDevice->GetRemoteIStPort(&sIStDeviceHandle, &sIStPortRemoteHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Use INodeMap object to access current setting of the camera. */
		eStApiCError = psApiFunctions->StApi->IStPort->GetINodeMap(&sIStPortRemoteHandle, &sINodeMapRemoteHandle);
		if (eStApiCError != StApiCError_NoError) break;

		{
			int64_t nCount;
			size_t nSize;

			/* Create a FeatureBag object for acquiring/saving camera settings. */
			eStApiCError = psApiFunctions->StApi->IStFeatureBag->Create(&sIStFeatureBagHandle);
			if (eStApiCError != StApiCError_NoError) break;

			/* Acquire and save all current settings from INodeMap object to FeatureBag. */
			eStApiCError = psApiFunctions->StApi->IStFeatureBag->StoreNodeMapToBag(&sIStFeatureBagHandle, &sINodeMapRemoteHandle, -1, &nCount);
			if (eStApiCError != StApiCError_NoError) break;

			/* Display all settings. */
			eStApiCError = psApiFunctions->StApi->IStFeatureBag->SaveToStringA(&sIStFeatureBagHandle, NULL, &nSize);
			if (eStApiCError != StApiCError_NoError) break;

			szFeatures = (char*)malloc(nSize);

			eStApiCError = psApiFunctions->StApi->IStFeatureBag->SaveToStringA(&sIStFeatureBagHandle, szFeatures, &nSize);
			if (eStApiCError != StApiCError_NoError) break;

			printf("%s\n", szFeatures);

			/* Save the settings in the FeatureBag to file. */
			printf("Saving %s ... ", szFileName);
			eStApiCError = psApiFunctions->StApi->IStFeatureBag->SaveToFileA(&sIStFeatureBagHandle, szFileName);
			printf("done\n");

			if (sIStFeatureBagHandle.Handle)
			{
				psApiFunctions->StApi->IStFeatureBag->Release(&sIStFeatureBagHandle);
			}
		}
		{
			bool8_t bValue;

			/* Create another FeatureBag for loading setting from file. */
			eStApiCError = psApiFunctions->StApi->IStFeatureBag->Create(&sIStFeatureBagHandle);
			if (eStApiCError != StApiCError_NoError) break;

			/*
				Load the settings from file to the FeatureBag.
				Note: we load from the one we just created above.
			*/
			eStApiCError = psApiFunctions->StApi->IStFeatureBag->StoreFileToBagA(&sIStFeatureBagHandle, szFileName);
			if (eStApiCError != StApiCError_NoError) break;

			/* Load the settings from the FeatureBag to the camera */
			printf("Loading to the camera ... ");
			eStApiCError = psApiFunctions->StApi->IStFeatureBag->Load(&sIStFeatureBagHandle, &sINodeMapRemoteHandle, true, &bValue);
			if (eStApiCError != StApiCError_NoError) break;
			
			printf("done\n");

			if (sIStFeatureBagHandle.Handle)
			{
				psApiFunctions->StApi->IStFeatureBag->Release(&sIStFeatureBagHandle);
			}
		}
		break;
	}

	if (eStApiCError != StApiCError_NoError)
	{
		/* If any error occurred, display the description of the error here. */
		OutputErrorInfo(psApiFunctions);
	}

	if (szFeatures)
	{
		free(szFeatures);
		szFeatures = NULL;
	}

	if (sIStFeatureBagHandle.Handle)
	{
		psApiFunctions->StApi->IStFeatureBag->Release(&sIStFeatureBagHandle);
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
