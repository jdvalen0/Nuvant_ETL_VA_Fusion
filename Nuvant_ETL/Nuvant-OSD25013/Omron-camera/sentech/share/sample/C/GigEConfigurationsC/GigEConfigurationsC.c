/*!
\file GigEConfigurationsC.c
\brief

This sample shows how to setup the IP address and heartbeat timeout of GigE camera.
The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to camera
- Acquire image data (with waiting in main thread)
- Check and update IP address of GigE camera
- Update heartbeat timeout of GigE camera

For more information, please refer to the help document of StApiC.
*/
/* If you want to use the GUI features, uncomment the following for defining ENABLED_ST_GUI with further operation. */
/* #define ENABLED_ST_GUI */

#include <unistd.h>
#include <arpa/inet.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

/* Include file for using StApiC. */
#include <StApi_C.h>

/* Counts of images to grab. */
const uint64_t nCountOfImagesToGrab = 100;

/* Feature names */
const char * GEV_INTERFACE_SUBNET_IP_ADDRESS = "GevInterfaceSubnetIPAddress";	/* Standard */
const char * GEV_INTERFACE_SUBNET_MASK = "GevInterfaceSubnetMask";				/* Standard */

const char * DEVICE_SELECTOR = "DeviceSelector";								/* Standard */
const char * GEV_DEVICE_IP_ADDRESS = "GevDeviceIPAddress";						/* Standard */
const char * GEV_DEVICE_SUBNET_MASK = "GevDeviceSubnetMask";					/* Standard */

const char * GEV_DEVICE_FORCE_IP_ADDRESS = "GevDeviceForceIPAddress";	/* Standard */
const char * GEV_DEVICE_FORCE_SUBNET_MASK = "GevDeviceForceSubnetMask";	/* Standard */
const char * GEV_DEVICE_FORCE_IP = "GevDeviceForceIP";							/* Standard */
const char * DEVICE_LINK_HEARTBEAT_TIMEOUT = "DeviceLinkHeartbeatTimeout";		/* Standard[us] */
const char * GEV_HEARTBEAT_TIMEOUT = "GevHeartbeatTimeout";						/* Standard(Deprecated)[ms] */

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


#ifdef ENABLED_ST_GUI
/*
GUI for checking and updating IP address of camera.
*/
EStApiCError_t UpdateDeviceIPAddress(PApiFunctions psApiFunctions, PStApiHandle_t pINodeMapHandle)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;
	StApiHandle_t sIStNodeMapDisplayWndHandle = { NULL };

	/* Create an NodeMap display window object. */
	eStApiCError = psApiFunctions->StApi->IStWnd->CreateIStWnd(StWindowType_NodeMapDisplay, &sIStNodeMapDisplayWndHandle);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	for (;;)
	{
		StApiHandle_t sINodeHandle = { NULL };

		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, "Root", &sINodeHandle);
		if (eStApiCError != StApiCError_NoError) return(eStApiCError);

		/* Register the node to NodeMap window. */
		eStApiCError = psApiFunctions->StApi->IStNodeMapDisplayWnd->RegisterINodeA(&sIStNodeMapDisplayWndHandle, &sINodeHandle, "Interface", NULL);
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
	return(eStApiCError);
}
#else /* ENABLED_ST_GUI */
/*
Console function for checking and updating IP address of camera.
*/
EStApiCError_t UpdateDeviceIPAddress(PApiFunctions psApiFunctions, PStApiHandle_t pINodeMapHandle)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;
	StApiHandle_t sIIntegerHandle_InterfaceIPAddress = { NULL };
	char szText[256];
	size_t nLen = sizeof(szText);
	StApiHandle_t sIIntegerHandle_InterfaceSubnetMask = { NULL };
	bool8_t fExit = false;

	/* Display the IP address of the host side. */
	eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, GEV_INTERFACE_SUBNET_IP_ADDRESS, &sIIntegerHandle_InterfaceIPAddress);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	eStApiCError = psApiFunctions->GenApi->IValue->ToStringA(&sIIntegerHandle_InterfaceIPAddress, false, false, szText, &nLen);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);
	printf("Interface IP Address = %s\n", szText);

	/* Display the subnet mask of the host side. */
	eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, GEV_INTERFACE_SUBNET_MASK, &sIIntegerHandle_InterfaceSubnetMask);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	nLen = sizeof(szText);
	eStApiCError = psApiFunctions->GenApi->IValue->ToStringA(&sIIntegerHandle_InterfaceSubnetMask, false, false, szText, &nLen);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);
	printf("Interface Subnet Mask = %s\n", szText);

	for (;;)
	{
		StApiHandle_t sIIntegerHandle_DeviceSelector = { NULL };
		const int64_t nDeviceSelectorValue = 0;
		StApiHandle_t sIIntegerHandle_DeviceIPAddress = { NULL };
		StApiHandle_t sIIntegerHandle_DeviceSubnetMask = { NULL };
		char szValue[256];
		uint32_t nNewDeviceIPAddress;
		int64_t nSubnetMask;
		int64_t nInterfaceIPAddress;

		/* Select the first camera. */
		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, DEVICE_SELECTOR, &sIIntegerHandle_DeviceSelector);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->GenApi->IInteger->SetValue(&sIIntegerHandle_DeviceSelector, nDeviceSelectorValue, false);
		if (eStApiCError != StApiCError_NoError) break;

		/* Display the current IP address of the camera. */
		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, GEV_DEVICE_IP_ADDRESS, &sIIntegerHandle_DeviceIPAddress);
		if (eStApiCError != StApiCError_NoError) return(eStApiCError);

		nLen = sizeof(szText);
		eStApiCError = psApiFunctions->GenApi->IValue->ToStringA(&sIIntegerHandle_DeviceIPAddress, false, false, szText, &nLen);
		if (eStApiCError != StApiCError_NoError) return(eStApiCError);
		printf("Device IP Address = %s\n", szText);

		/* Display the current subnet mask of the camera. */
		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, GEV_DEVICE_SUBNET_MASK, &sIIntegerHandle_DeviceSubnetMask);
		if (eStApiCError != StApiCError_NoError) return(eStApiCError);

		nLen = sizeof(szText);
		eStApiCError = psApiFunctions->GenApi->IValue->ToStringA(&sIIntegerHandle_DeviceSubnetMask, false, false, szText, &nLen);
		if (eStApiCError != StApiCError_NoError) return(eStApiCError);
		printf("Device Subnet Mask = %s\n", szText);

		if (fExit)
		{
			break;
		}
		/* Waiting for new IP address. */
		printf("Input new device IP address : ");
#if 1400 <= _MSC_VER
		scanf_s("%s", szValue, (unsigned int)_countof(szValue));
#else
		scanf("%s", szValue);
#endif

		/* Convert the new IP address string to a 32-bit number. */
		nNewDeviceIPAddress = ntohl(inet_addr(szValue));

		/* Get the subnet mask of the host side. */
		eStApiCError = psApiFunctions->GenApi->IInteger->GetValue(&sIIntegerHandle_InterfaceSubnetMask, false, false, &nSubnetMask);
		if (eStApiCError != StApiCError_NoError) return(eStApiCError);

		/* Get the IP address of the host side.*/
		eStApiCError = psApiFunctions->GenApi->IInteger->GetValue(&sIIntegerHandle_InterfaceIPAddress, false, false, &nInterfaceIPAddress);
		if (eStApiCError != StApiCError_NoError) return(eStApiCError);
		
		/* Ensure that the subnet address of the host and the camera are matched, and that the host and IP address of camera are different. */
		if (((nInterfaceIPAddress & nSubnetMask) == (nNewDeviceIPAddress & nSubnetMask)) && (nInterfaceIPAddress != nNewDeviceIPAddress))
		{
			StApiHandle_t sIIntegerHandle_DeviceForceIPAddress = { NULL };
			StApiHandle_t sIIntegerHandle_DeviceForceSubnetMask = { NULL };
			StApiHandle_t sICommandHandle_DeviceForce = { NULL };

			/* Specify the new IP address of the camera. At this point, the camera settings will not be updated. */
			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, GEV_DEVICE_FORCE_IP_ADDRESS, &sIIntegerHandle_DeviceForceIPAddress);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);
			eStApiCError = psApiFunctions->GenApi->IInteger->SetValue(&sIIntegerHandle_DeviceForceIPAddress, nNewDeviceIPAddress, false);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			/* Specify the new subnet mask of the camera. At this point, the camera settings will not be updated. */
			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, GEV_DEVICE_FORCE_SUBNET_MASK, &sIIntegerHandle_DeviceForceSubnetMask);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);
			eStApiCError = psApiFunctions->GenApi->IInteger->SetValue(&sIIntegerHandle_DeviceForceSubnetMask, nSubnetMask, false);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			/* Update the camera settings. */
			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, GEV_DEVICE_FORCE_IP, &sICommandHandle_DeviceForce);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);
			eStApiCError = psApiFunctions->GenApi->ICommand->Execute(&sICommandHandle_DeviceForce, false);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			fExit = true;
		}
		else
		{
			printf("New IP address is not valid.\n");
		}
	}
	return(eStApiCError);
}
#endif /* ENABLED_ST_GUI */

/*
 Console function for reading and updating heartbeat timeout
*/
EStApiCError_t UpdateHeartbeatTimeout(PApiFunctions psApiFunctions, PStApiHandle_t pINodeMapHandle)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;
	StApiHandle_t sIValueHandle = { NULL };
	const char *szName = NULL;
	const char *szUnit = NULL;
	bool8_t fExit = false;

	eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, DEVICE_LINK_HEARTBEAT_TIMEOUT, &sIValueHandle);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	if (sIValueHandle.Handle != NULL)
	{
		/* IFloat[us] */
		szName = DEVICE_LINK_HEARTBEAT_TIMEOUT;
		szUnit = "us";
	}
	else
	{
		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, GEV_HEARTBEAT_TIMEOUT, &sIValueHandle);
		if (eStApiCError != StApiCError_NoError) return(eStApiCError);
		/* IInteger[ms] */
		szName = GEV_HEARTBEAT_TIMEOUT;
		szUnit = "ms";
	}
	if (sIValueHandle.Handle == NULL) return(eStApiCError);

	for (;;)
	{
		/* Display the current HeartbeatTimeout setting */
		char szValue[256];
		size_t nLen = sizeof(szValue);

		eStApiCError = psApiFunctions->GenApi->IValue->ToStringA(&sIValueHandle, false, false, szValue, &nLen);
		if (eStApiCError != StApiCError_NoError) break;

		printf("Current %s[%s] = %s\n", szName, szUnit, szValue);

		if (fExit)
		{
			break;
		}

		/* Waiting to enter a new HeartbeatTimeout setting. */
		printf("Warning: the heartbeat sending interval is fixed when the device is initialized (opened).\n");
		printf("Thus, changing the heartbeat timeout smaller than the current value may cause timeout.\n");
		printf("In practical situation, please either set environment variable STGENTL_GIGE_HEARTBEAT before opening the device\n");
		printf("or re-open the device after changing the heartbeat value without setting the environment variable and debugger.\n");
		printf("Input new Heartbeat Timeout [%s] : ", szUnit);

#if 1400 <= _MSC_VER
		scanf_s("%s", szValue, (unsigned int)_countof(szValue));
#else
		scanf("%s", szValue);
#endif

		/* Update the camera HeartbeatTimeout settings. */
		eStApiCError = psApiFunctions->GenApi->IValue->FromStringA(&sIValueHandle, szValue, true);
		if (eStApiCError != StApiCError_NoError) break;
		fExit = true;
	}
	return(eStApiCError);
}
/*

*/
EStApiCError_t CreateIStDeviceByIPAddress(PApiFunctions psApiFunctions, PStApiHandle_t pIStInterfaceHandle, PStApiHandle_t pINodeMapHandle, int64_t nNewIPAddress, DEVICE_ACCESS_FLAGS eDeviceAccessFlags, PStApiHandle_t pIStDeviceHandle)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;
	for (;;)
	{
		StApiHandle_t sIIntegerDeviceSelector = { NULL };
		StApiHandle_t sIIntegerGevDeviceIPAddress = { NULL };
		int64_t nMaxIndex;
		int64_t nDeviceIndex;

		eStApiCError = psApiFunctions->StApi->IStInterface->UpdateDeviceList(pIStInterfaceHandle, NULL);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, "DeviceSelector", &sIIntegerDeviceSelector);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, "GevDeviceIPAddress", &sIIntegerGevDeviceIPAddress);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->GenApi->IInteger->GetMax(&sIIntegerDeviceSelector, &nMaxIndex);
		if (eStApiCError != StApiCError_NoError) break;

		for (nDeviceIndex = 0; nDeviceIndex <= nMaxIndex; ++nDeviceIndex)
		{
			bool8_t isAvailable;
			eStApiCError = psApiFunctions->GenApi->IInteger->SetValue(&sIIntegerDeviceSelector, nDeviceIndex, true);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->GenApi->IBase->IsAvailable(&sIIntegerGevDeviceIPAddress, &isAvailable);
			if (eStApiCError != StApiCError_NoError) break;

			if (isAvailable)
			{
				int64_t nIPAddress;
				eStApiCError = psApiFunctions->GenApi->IInteger->GetValue(&sIIntegerGevDeviceIPAddress, true, false, &nIPAddress);
				if (eStApiCError != StApiCError_NoError) break;

				if (nIPAddress == nNewIPAddress)
				{
					eStApiCError = psApiFunctions->StApi->IStInterface->CreateIStDeviceByIndex(pIStInterfaceHandle, (size_t)nDeviceIndex, eDeviceAccessFlags, pIStDeviceHandle);
					if (eStApiCError != StApiCError_NoError) break;

					return(StApiCError_NoError);
				}
			}
		}
	}

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
		uint32_t nIntCount;
		StApiHandle_t sIStInterfaceHandle = { NULL };
		StApiHandle_t sIStPortHandle = { NULL };
		StApiHandle_t sINodeMapHandle = { NULL };
		StApiHandle_t sIStPortRemoteHandle = { NULL };
		StApiHandle_t sINodeMapRemoteHandle = { NULL };
		size_t i;

		/* Create a system object for device scan and connection. */
		eStApiCError = psApiFunctions->StApi->IStSystem->CreateIStSystem(StSystemVendor_Default, StInterfaceType_GigEVision, &sIStSystemHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/*
		Check GigE interface for devices.
		*/
		eStApiCError = psApiFunctions->StApi->IStSystem->GetInterfaceCount(&sIStSystemHandle, &nIntCount);
		if (eStApiCError != StApiCError_NoError) break;
		if (nIntCount == 0) break;

		for (i = 0; i < nIntCount; i++)
		{
			StApiHandle_t sIStInterfaceHandleTmp = { NULL };
			uint32_t nDevCount;

			eStApiCError = psApiFunctions->StApi->IStSystem->GetIStInterface(&sIStSystemHandle, i, &sIStInterfaceHandleTmp);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->StApi->IStInterface->GetDeviceCount(&sIStInterfaceHandleTmp, &nDevCount);
			if (eStApiCError != StApiCError_NoError) break;
			if (0 < nDevCount)
			{
				sIStInterfaceHandle = sIStInterfaceHandleTmp;
				break;
			}
		}
		if (sIStInterfaceHandle.Handle == NULL)
		{
			break;
		}

		/* Use INodeMap object to access current setting of the interface. */
		eStApiCError = psApiFunctions->StApi->IStInterface->GetIStPort(&sIStInterfaceHandle, &sIStPortHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->StApi->IStPort->GetINodeMap(&sIStPortHandle, &sINodeMapHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Update the IP address setting of the first camera on GigE interface. */
		eStApiCError = UpdateDeviceIPAddress(psApiFunctions, &sINodeMapHandle);
		if (eStApiCError != StApiCError_NoError) break;
	
		{
			StApiHandle_t sIIntegerHandle_DeviceForceIPAddress = { NULL };
			size_t i;
			int64_t nNewIPAddress;

			/* Specify the new IP address of the camera.  */
			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, GEV_DEVICE_FORCE_IP_ADDRESS, &sIIntegerHandle_DeviceForceIPAddress);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->GenApi->IInteger->GetValue(&sIIntegerHandle_DeviceForceIPAddress, true, false, &nNewIPAddress);
			if (eStApiCError != StApiCError_NoError) break;


			for (i = 0; i < 30; ++i)
			{
				sleep(1);
				eStApiCError = CreateIStDeviceByIPAddress(psApiFunctions, &sIStInterfaceHandle, &sINodeMapHandle, nNewIPAddress, DEVICE_ACCESS_CONTROL, &sIStDeviceHandle);
				if (eStApiCError != StApiCError_NoError) break;

				if (sIStDeviceHandle.Handle)
				{
					break;
				}
			}
			if (eStApiCError != StApiCError_NoError) break;
		}

		/* Use INodeMap object to access current setting of the camera. */
		eStApiCError = psApiFunctions->StApi->IStDevice->GetRemoteIStPort(&sIStDeviceHandle, &sIStPortRemoteHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->StApi->IStPort->GetINodeMap(&sIStPortRemoteHandle, &sINodeMapRemoteHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Update the camera HeartbeatTimeout settings. */
		eStApiCError = UpdateHeartbeatTimeout(psApiFunctions, &sINodeMapRemoteHandle);
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
				StApiHandle_t sIStStreamBufferInfoHandle = { NULL };
				uint64_t iFrameID;
				void *pBuffer = NULL;

				/* If yes, we create a IStImage object for further image handling. */
				eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStImage(&sIStStreamBufferHandle, &sIStImageHandle);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->StApi->IStImage->GetImageWidth(&sIStImageHandle, &nImageWidth);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->StApi->IStImage->GetImageHeight(&sIStImageHandle, &nImageHeight);
				if (eStApiCError != StApiCError_NoError) break;

				/* Display the information of the acquired image data. */
				eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStStreamBufferInfo(&sIStStreamBufferHandle, &sIStStreamBufferInfoHandle);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->StApi->IStStreamBufferInfo->GetFrameID(&sIStStreamBufferInfoHandle, &iFrameID);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->StApi->IStImage->GetImageBuffer(&sIStImageHandle, &pBuffer);
				if (eStApiCError != StApiCError_NoError) break;

				printf("BlockID=%" PRIu64 " Size: %zu x %zu First byte = %u\n", iFrameID, nImageWidth, nImageHeight, *(uint8_t*)pBuffer);
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


