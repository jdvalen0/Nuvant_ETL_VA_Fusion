/*!
\file UserMemoryC.c
\brief

This sample shows how to use UserMemory function.
The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to camera
- How to read user data from the rom and to write user data to the rom.

For more information, please refer to the help document of StApiC.
*/

#include <stdlib.h>
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

/* Feature names */
const char * DEVICE_USER_MEMORY = "DeviceUserMemory";	/* Custom */


EStApiCError_t PrintHexData(uint8_t *pbyteData, int64_t nLength, int64_t nAddOffset)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;
	int64_t i;
	for (i = 0; i < nLength; i++)
	{
		if ((i & 0xF) == 0)
		{
			const int64_t nAddress = i + nAddOffset;
			printf("0x%" PRIX64 "\t", nAddress);
		}

		printf(" %02X", pbyteData[i]);

		if ((i & 0xF) == 0xF)
		{
			printf("\n");
		}
	}
	printf("\n");
	return(eStApiCError);
}


EStApiCError_t WriteRegister(PApiFunctions psApiFunctions, PStApiHandle_t pIRegisterHandle)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;

	int64_t nLength;
	eStApiCError = psApiFunctions->GenApi->IRegister->GetLength(pIRegisterHandle, &nLength);
	if (eStApiCError == StApiCError_NoError)
	{
		uint8_t *pbyteBuffer = (uint8_t*)malloc((size_t)nLength);
		if (pbyteBuffer != NULL)
		{
			size_t i;
			for (i = 0; i < (size_t)nLength; ++i)
			{
				pbyteBuffer[i] = (uint8_t)(i & 0xFF);
			}
			eStApiCError = psApiFunctions->GenApi->IRegister->Set(pIRegisterHandle, pbyteBuffer, nLength, false);
			if (eStApiCError == StApiCError_NoError)
			{
				PrintHexData(pbyteBuffer, nLength, 0);
			}
			free(pbyteBuffer);
		}
	}
	return(eStApiCError);
}


EStApiCError_t ReadRegister(PApiFunctions psApiFunctions, PStApiHandle_t pIRegisterHandle)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;

	int64_t nLength;
	eStApiCError = psApiFunctions->GenApi->IRegister->GetLength(pIRegisterHandle, &nLength);
	if (eStApiCError == StApiCError_NoError)
	{
		uint8_t *pbyteBuffer = (uint8_t*)malloc((size_t)nLength);
		if (pbyteBuffer != NULL)
		{
			eStApiCError = psApiFunctions->GenApi->IRegister->Get(pIRegisterHandle, pbyteBuffer, nLength, false, false);
			if (eStApiCError == StApiCError_NoError)
			{
				PrintHexData(pbyteBuffer, nLength, 0);
			}
			free(pbyteBuffer);
		}
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

	if (eStApiCError != StApiCError_NoError)
	{
		printf("initializing StApiC was failed.\n");
		return(0);
	}

	for (;;)
	{
		StApiHandle_t sIStPortRemoteHandle = { NULL };
		StApiHandle_t sINodeMapRemoteHandle = { NULL };
		StApiHandle_t sIRegisterUserMemory = { NULL };

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

		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapRemoteHandle, DEVICE_USER_MEMORY, &sIRegisterUserMemory);
		if (sIRegisterUserMemory.Handle == NULL)
		{
			printf("%s is not supported by this camera.\n", DEVICE_USER_MEMORY);
		}
		else
		{
			ReadRegister(psApiFunctions, &sIRegisterUserMemory);
		}

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
