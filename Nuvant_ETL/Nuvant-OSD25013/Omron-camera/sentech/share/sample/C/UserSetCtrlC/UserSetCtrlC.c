/*!
\file UserSetCtrlC.c
\brief

This sample shows how to use UserSet to load/save setting from/into camera ROM.
The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to camera
- Load/Save UserSet with FeatureBag

For more information, please refer to the help document of StApiC.
*/

#include <stdlib.h>

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

/* Feature names */
const char * USER_SET_SELECTOR = "UserSetSelector";						/* Standard */
const char * USER_SET_TARGET = "UserSet1";								/* Standard */
const char * USER_SET_LOAD = "UserSetLoad";								/* Standard */
const char * USER_SET_SAVE = "UserSetSave";								/* Standard */
const char * USER_SET_DEFAULT = "UserSetDefault";						/* Standard */
const char * USER_SET_DEFAULT_SELECTOR = "UserSetDefaultSelector";		/* Standard(Deprecated) */
const char * PIXEL_FORMAT = "PixelFormat";								/* Standard */

/*
Execute command of indicated node map.
*/
EStApiCError_t Execute(PApiFunctions psApiFunctions, PStApiHandle_t pINodeMapHandle, const char *szCommandName)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;

	/* Get the ICommand interface pointer, and call the Execute method */
	StApiHandle_t sICommandHandle = { NULL };
	eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, szCommandName, &sICommandHandle);
	if (eStApiCError == StApiCError_NoError)
	{
		eStApiCError = psApiFunctions->GenApi->ICommand->Execute(&sICommandHandle, false);
	}
	return(eStApiCError);
}

/*
Set the setting of indicated enumeration of the node map.
*/
EStApiCError_t SetEnumeration(PApiFunctions psApiFunctions, PStApiHandle_t pINodeMapHandle, const char *szEnumerationName, const char *szValueName)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;
	StApiHandle_t sIEnumerationHandle = { NULL };

	/* Get the IEnumeration interface pointer. */
	eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, szEnumerationName, &sIEnumerationHandle);
	if (eStApiCError == StApiCError_NoError)
	{
		/* Update the settings using the IEnumeration interface pointer. */
		eStApiCError = psApiFunctions->GenApi->IEnumeration->SetStringValueA(&sIEnumerationHandle, szValueName);
	}
	return(eStApiCError);
}
/*
Display current setting of indicated enumeration of the node map.
*/
EStApiCError_t DisplayEnumeration(PApiFunctions psApiFunctions, PStApiHandle_t pINodeMapHandle, const char *szEnumerationName)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;
	StApiHandle_t sIEnumerationHandle = { NULL };

	/* Get the IEnumeration interface pointer. */
	eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, szEnumerationName, &sIEnumerationHandle);
	if (eStApiCError == StApiCError_NoError)
	{
		/* Display the current settings. */
		char szText[256];
		size_t nLen = sizeof(szText);
		eStApiCError = psApiFunctions->GenApi->IEnumeration->GetStringValueA(&sIEnumerationHandle, szText, &nLen);
		if (eStApiCError == StApiCError_NoError)
		{
			printf("Current %s = %s\n", szEnumerationName, szText);
		}
	}
	return(eStApiCError);
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


int main(int argc, char **argv)
{
	/* Initialize StApiC before using. */
	PApiFunctions psApiFunctions = NULL;
	EStApiCError_t eStApiCError = StApiCInitialize(STAPI_VERSION, &psApiFunctions);

	StApiHandle_t sIStSystemHandle = { NULL };
	StApiHandle_t sIStDeviceHandle = { NULL };
	StApiHandle_t sIStFeatureBagHandle = { NULL };

	if (eStApiCError != StApiCError_NoError)
	{
		printf("initializing StApiC was failed.\n");
		return(0);
	}

	for (;;)
	{
		StApiHandle_t sIStPortRemoteHandle = { NULL };
		StApiHandle_t sINodeMapRemoteHandle = { NULL };
		int64_t nCount;
		StApiHandle_t sIEnumerationUserSetDefaultHandle = { NULL };
		bool8_t bValue;

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

		/* Set the UserSet to be used to UserSetSelector. */
		eStApiCError = SetEnumeration(psApiFunctions, &sINodeMapRemoteHandle, USER_SET_SELECTOR, USER_SET_TARGET);
		if (eStApiCError != StApiCError_NoError) break;

		/* Load the UserSet that is stored in the ROM reflected in the camera. */
		printf("Loading %s ...", USER_SET_TARGET);
		eStApiCError = Execute(psApiFunctions, &sINodeMapRemoteHandle, USER_SET_LOAD);
		if (eStApiCError != StApiCError_NoError) break;
		printf(" done\n");

		/* Create a FeatureBag object for acquiring/saving camera settings. */
		eStApiCError = psApiFunctions->StApi->IStFeatureBag->Create(&sIStFeatureBagHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Save the current settings to FeatureBag. */
		printf("Storing form FeatureBag ...");
		eStApiCError = psApiFunctions->StApi->IStFeatureBag->StoreNodeMapToBag(&sIStFeatureBagHandle, &sINodeMapRemoteHandle, -1, &nCount);
		printf(" done\n");
		if (eStApiCError != StApiCError_NoError) break;

		/*Set the pixel format. */
		eStApiCError = EnumerationNode(psApiFunctions, &sINodeMapRemoteHandle, PIXEL_FORMAT);
		if (eStApiCError != StApiCError_NoError) break;
		
		/* Display the current pixel format setting. */
		eStApiCError = DisplayEnumeration(psApiFunctions, &sINodeMapRemoteHandle, PIXEL_FORMAT);
		if (eStApiCError != StApiCError_NoError) break;

		/* Save current settings to UserSet. */
		printf("Saving %s ...", USER_SET_TARGET);
		eStApiCError = Execute(psApiFunctions, &sINodeMapRemoteHandle, USER_SET_SAVE);
		if (eStApiCError != StApiCError_NoError) break;
		printf(" done\n");

		/* Setting the pixel format. */
		eStApiCError = EnumerationNode(psApiFunctions, &sINodeMapRemoteHandle, PIXEL_FORMAT);
		if (eStApiCError != StApiCError_NoError) break;

		/* Display current pixel format setting. */
		eStApiCError = DisplayEnumeration(psApiFunctions, &sINodeMapRemoteHandle, PIXEL_FORMAT);
		if (eStApiCError != StApiCError_NoError) break;

		/* Load the UserSet that are stored in the ROM reflected in the camera. */
		printf("Loading %s ...", USER_SET_TARGET);
		eStApiCError = Execute(psApiFunctions, &sINodeMapRemoteHandle, USER_SET_LOAD);
		if (eStApiCError != StApiCError_NoError) break;
		printf(" done\n");

		/* Display current pixel format setting. */
		eStApiCError = DisplayEnumeration(psApiFunctions, &sINodeMapRemoteHandle, PIXEL_FORMAT);
		if (eStApiCError != StApiCError_NoError) break;

		/* Load the settings in the FeatureBag to the camera.*/
		printf("Loading form FeatureBag ...");
		eStApiCError = psApiFunctions->StApi->IStFeatureBag->Load(&sIStFeatureBagHandle, &sINodeMapRemoteHandle, false, &bValue);
		if (eStApiCError != StApiCError_NoError) break;
		printf(" done\n");

		/* Display current pixel format setting. */
		eStApiCError = DisplayEnumeration(psApiFunctions, &sINodeMapRemoteHandle, PIXEL_FORMAT);
		if (eStApiCError != StApiCError_NoError) break;

		/* Set the UserSet for UserSetSelector. */
		eStApiCError = SetEnumeration(psApiFunctions, &sINodeMapRemoteHandle, USER_SET_SELECTOR, USER_SET_TARGET);
		if (eStApiCError != StApiCError_NoError) break;

		/* Save current settings to UserSet. */
		printf("Saving %s ...", USER_SET_TARGET);
		eStApiCError = Execute(psApiFunctions, &sINodeMapRemoteHandle, USER_SET_SAVE);
		if (eStApiCError != StApiCError_NoError) break;
		printf(" done\n");

		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapRemoteHandle, USER_SET_DEFAULT, &sIEnumerationUserSetDefaultHandle);
		if (sIEnumerationUserSetDefaultHandle.Handle != NULL)
		{
			/* Display the UserSetDefault setting. */
			eStApiCError = DisplayEnumeration(psApiFunctions, &sINodeMapRemoteHandle, USER_SET_DEFAULT);
		}
		else
		{
			/* Display the UserSetDefaultSelector setting. */
			eStApiCError = DisplayEnumeration(psApiFunctions, &sINodeMapRemoteHandle, USER_SET_DEFAULT_SELECTOR);
		}
		if (eStApiCError != StApiCError_NoError) break;
		

		break;
	}

	if (eStApiCError != StApiCError_NoError)
	{
		/* If any error occurred, display the description of the error here. */
		OutputErrorInfo(psApiFunctions);
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

