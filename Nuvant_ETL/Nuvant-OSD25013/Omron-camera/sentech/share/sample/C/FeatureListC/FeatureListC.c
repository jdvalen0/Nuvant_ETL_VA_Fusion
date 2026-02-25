/*!
\file FeatureListC.c
\brief

This sample will list all support functions of connected camera.
The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to camera
- Access Nodes of NodeMap for displaying camera's features

For more information, please refer to the help document of StApiC.
If you want to use the GUI features, please refer to FeatureListC-GUI.c
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

/*

*/
EStApiCError_t DisplayNodes(PApiFunctions psApiFunctions, PStApiHandle_t pINodeHandle, size_t nLevel)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;

	for (;;)
	{
		bool8_t isImplemented;
		size_t nSize;
		EInterfaceType eInterfaceType;
		const char *szInterfaceName = NULL;
		char *szNodeName = NULL;
		size_t i;

		eStApiCError = psApiFunctions->GenApi->IBase->IsImplemented(pINodeHandle, &isImplemented);
		if (eStApiCError != StApiCError_NoError) break;
		if (!isImplemented) break;
	
		/* Display the names and interface type. */
		eStApiCError = psApiFunctions->GenApi->INode->GetInterfaceNameA(pINodeHandle, &szInterfaceName);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->GenApi->INode->GetNameA(pINodeHandle, false, NULL, &nSize);
		if (eStApiCError != StApiCError_NoError) break;

		szNodeName = (char*)malloc(nSize);
		if (szNodeName == NULL)
		{
			printf("Memory allocation error.\n");
			break;
		}

		eStApiCError = psApiFunctions->GenApi->INode->GetNameA(pINodeHandle, false, szNodeName, &nSize);
		if (eStApiCError == StApiCError_NoError)
		{
			for (i = 0; i < nLevel; ++i)	printf("\t");
			printf("%s[%s]\n", szNodeName, szInterfaceName);
		}
		if (szNodeName)
		{
			free(szNodeName);
			szNodeName = NULL;
		}
		if (eStApiCError != StApiCError_NoError) break;

		/* Get the interface type. */
		eStApiCError = psApiFunctions->GenApi->INode->GetPrincipalInterfaceType(pINodeHandle, &eInterfaceType);
		if (eStApiCError != StApiCError_NoError) break;

		if (eInterfaceType == intfICategory)
		{
			size_t nCount;
			PStApiHandle_t psIValueHandleArray = NULL;

			/* In the case of Category type, display all of the features that belong to the category. */
			eStApiCError = psApiFunctions->GenApi->ICategory->GetFeatures(pINodeHandle, NULL, &nCount);
			if (eStApiCError != StApiCError_NoError) break;

			/* Allocate memory for the interfaces of the entries. */
			psIValueHandleArray = (PStApiHandle_t)malloc(sizeof(StApiHandle_t) * nCount);
			if (psIValueHandleArray == NULL)
			{
				printf("Memory allocation error.\n");
				break;
			}
			else
			{
				/* Get the entries. */
				eStApiCError = psApiFunctions->GenApi->ICategory->GetFeatures(pINodeHandle, psIValueHandleArray, &nCount);
				if (eStApiCError == StApiCError_NoError)
				{
					for (i = 0; i < nCount; ++i)
					{
						eStApiCError = DisplayNodes(psApiFunctions, &psIValueHandleArray[i], nLevel + 1);
						if (eStApiCError != StApiCError_NoError) break;
					}
				}
				free(psIValueHandleArray);
				psIValueHandleArray = NULL;
			}
		}
		else if (eInterfaceType == intfIEnumeration)
		{
			size_t nCount;
			PStApiHandle_t psIEnumEntryHandleArray = NULL;

			/* Get a count of the entries. */
			eStApiCError = psApiFunctions->GenApi->IEnumeration->GetEntries(pINodeHandle, NULL, &nCount);
			if (eStApiCError != StApiCError_NoError) break;

			/* Allocate memory for the interfaces of the entries. */
			psIEnumEntryHandleArray = (PStApiHandle_t)malloc(sizeof(StApiHandle_t) * nCount);
			if (psIEnumEntryHandleArray == NULL)
			{
				printf("Memory allocation error.\n");
				break;
			}
			else
			{
				/* Get the entries. */
				eStApiCError = psApiFunctions->GenApi->IEnumeration->GetEntries(pINodeHandle, psIEnumEntryHandleArray, &nCount);
				if (eStApiCError == StApiCError_NoError)
				{
					for (i = 0; i < nCount; ++i)
					{
						/* In the case of Enumeration type, display all of the entries. */
						eStApiCError = DisplayNodes(psApiFunctions, &psIEnumEntryHandleArray[i], nLevel + 1);
						if (eStApiCError != StApiCError_NoError) break;
					}
				}
				free(psIEnumEntryHandleArray);
				psIEnumEntryHandleArray = NULL;
			}
		}

		break;
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

