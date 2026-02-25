/*!
\file GigEActionCommandC.c
\brief

This sample shows how to use GigE Action command.
The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to GigE camera
- Set and send action command

For more information, please refer to the help document of StApiC.
If you want to use the GUI features, please refer to GigEActionCommandC-GUI.c
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

/* Include file for using StApiC. */
#include <StApi_C.h>

/* Counts of images to grab. */
const uint64_t nCountOfImagesToGrab = 10;

#define MAXIMUM_DEVICE_COUNT 10
#define MAXIMUM_INTERFACE_COUNT 5

const uint32_t nDeviceKey = 0x12345678;
const uint32_t nGroupKey = 0x00000001;
const uint32_t nGroupMask = 0xFFFFFFFF;
const uint32_t nActionSelector = 0;
const bool8_t bScheduledTimeEnable = false;
const char *szTriggerName = "FrameStart";
uint64_t nScheduledTime = 0;
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
Adjust GevSCPD  (Only for same configuration cameras.)
*/
EStApiCError_t AdjustGevSCPD(PApiFunctions	psApiFunctions, PStApiHandle_t	pIStDeviceHandleArray, const size_t nValidDeviceCount)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;

	int64_t nSCPDValue;
	size_t i;

	for (i = 0; i < nValidDeviceCount; ++i)
	{
		StApiHandle_t sIStPortHandle = { NULL };
		StApiHandle_t sINodeMapHandle = { NULL };
		StApiHandle_t sIIntegerHandle_GevSCPD = { NULL };
		PStApiHandle_t	pIStDeviceHandle = &pIStDeviceHandleArray[i];

		/* Get packet size.*/
		eStApiCError = psApiFunctions->StApi->IStDevice->GetRemoteIStPort(pIStDeviceHandle, &sIStPortHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->StApi->IStPort->GetINodeMap(&sIStPortHandle, &sINodeMapHandle);
		if (eStApiCError != StApiCError_NoError) break;

		if (i == 0)
		{
			StApiHandle_t sIIntegerHandle_GevSCPSPacketSize = { NULL };
			int64_t nPacketSize;
			const int64_t nMaxBps = 100000000;	/* 800Mbps */
			int64_t nEachPacketTimeNs;
			int64_t nTimestampUnit;

			StApiHandle_t sIIntegerHandle_TimestampLatchValue = { NULL };

			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "TimestampLatchValue", &sIIntegerHandle_TimestampLatchValue);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->GenApi->IInteger->GetInc(&sIIntegerHandle_TimestampLatchValue, &nTimestampUnit);
			if (eStApiCError != StApiCError_NoError) break;

			if (nTimestampUnit == 0)
			{
				nTimestampUnit = 40;
			}

			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "GevSCPSPacketSize", &sIIntegerHandle_GevSCPSPacketSize);
			if (eStApiCError != StApiCError_NoError) break;


			eStApiCError = psApiFunctions->GenApi->IInteger->GetValue(&sIIntegerHandle_GevSCPSPacketSize, false, false, &nPacketSize);
			if (eStApiCError != StApiCError_NoError) break;


			nEachPacketTimeNs = nPacketSize * 1000000000 * (nValidDeviceCount - 1) / nMaxBps;

			nSCPDValue = nEachPacketTimeNs / nTimestampUnit;
		}

		eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "GevSCPD", &sIIntegerHandle_GevSCPD);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->GenApi->IInteger->SetValue(&sIIntegerHandle_GevSCPD, nSCPDValue, false);
		if (eStApiCError != StApiCError_NoError) break;

	}
	return(eStApiCError);
}

/*
Set device action command parameters.
*/
EStApiCError_t SetDeviceActionCommandParam(PApiFunctions psApiFunctions, PStApiHandle_t pIStDeviceHandle)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;

	for (;;)
	{
		StApiHandle_t sIStPortHandle = { NULL };
		StApiHandle_t sINodeMapHandle = { NULL };

		eStApiCError = psApiFunctions->StApi->IStDevice->GetRemoteIStPort(pIStDeviceHandle, &sIStPortHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->StApi->IStPort->GetINodeMap(&sIStPortHandle, &sINodeMapHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* TriggerSelector */
		{
			StApiHandle_t sIEnumeration = { NULL };

			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "TriggerSelector", &sIEnumeration);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->GenApi->IEnumeration->SetStringValueA(&sIEnumeration, szTriggerName);
			if (eStApiCError != StApiCError_NoError) break;
			printf("\tTriggerSelector = FrameStart\n");
		}

		/* TriggerMode */
		{
			StApiHandle_t sIEnumeration = { NULL };

			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "TriggerMode", &sIEnumeration);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->GenApi->IEnumeration->SetStringValueA(&sIEnumeration, "On");
			if (eStApiCError != StApiCError_NoError) break;
			printf("\tTriggerMode[%s] = On\n", szTriggerName);
		}

		/* TriggerSource */
		{
			StApiHandle_t sIEnumeration = { NULL };

			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "TriggerSource", &sIEnumeration);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->GenApi->IEnumeration->SetStringValueA(&sIEnumeration, "Action0");
			if (eStApiCError != StApiCError_NoError) break;
			printf("\tTriggerSource = Action0\n");
		}

		/* ActionDeviceKey */
		{
			StApiHandle_t sIInteger = { NULL };

			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "ActionDeviceKey", &sIInteger);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->GenApi->IInteger->SetValue(&sIInteger, nDeviceKey, false);
			if (eStApiCError != StApiCError_NoError) break;
			printf("\tActionDeviceKey = 0x%08X\n", nDeviceKey);
		}

		/* ActionSelector */
		{
			StApiHandle_t sIInteger = { NULL };

			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "ActionSelector", &sIInteger);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->GenApi->IInteger->SetValue(&sIInteger, nActionSelector, false);
			if (eStApiCError != StApiCError_NoError) break;
			printf("\tActionSelector = %u\n", nActionSelector);
		}

		/* ActionGroupKey */
		{
			StApiHandle_t sIInteger = { NULL };

			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "ActionGroupKey", &sIInteger);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->GenApi->IInteger->SetValue(&sIInteger, nGroupKey, false);
			if (eStApiCError != StApiCError_NoError) break;
			printf("\tActionGroupKey[%u] = 0x%08X\n", nActionSelector, nGroupKey);
		}

		/* ActionGroupMask */
		{
			StApiHandle_t sIInteger = { NULL };

			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "ActionGroupMask", &sIInteger);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->GenApi->IInteger->SetValue(&sIInteger, nGroupMask, false);
			if (eStApiCError != StApiCError_NoError) break;
			printf("\tActionGroupMask[%u] = 0x%08X\n", nActionSelector, nGroupMask);
		}

		break;
	}
	return(eStApiCError);
}

/*
Set host action command parameters.
*/
EStApiCError_t SetHostActionCommandParam(PApiFunctions psApiFunctions, PStApiHandle_t pIStInterfaceHandle)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;

	for (;;)
	{
		StApiHandle_t sIStPortHandle = { NULL };
		StApiHandle_t sINodeMapHandle = { NULL };

		eStApiCError = psApiFunctions->StApi->IStInterface->GetIStPort(pIStInterfaceHandle, &sIStPortHandle);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = psApiFunctions->StApi->IStPort->GetINodeMap(&sIStPortHandle, &sINodeMapHandle);
		if (eStApiCError != StApiCError_NoError) break;

		{
			StApiHandle_t sIEnumeration_EventSelector = { NULL };
			StApiHandle_t sIEnumeration_EventNotification = { NULL };
			const char *pszEventNames[] = { "ActionCommand", "ActionCommandAcknowledge" };
			size_t i;

			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "EventSelector", &sIEnumeration_EventSelector);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "EventNotification", &sIEnumeration_EventNotification);
			if (eStApiCError != StApiCError_NoError) break;

			for (i = 0; i < sizeof(pszEventNames) / sizeof(pszEventNames[0]); ++i)
			{
				eStApiCError = psApiFunctions->GenApi->IEnumeration->SetStringValueA(&sIEnumeration_EventSelector, pszEventNames[i]);
				if (eStApiCError != StApiCError_NoError) break;
				printf("\tEventSelector = %s\n", pszEventNames[i]);

				eStApiCError = psApiFunctions->GenApi->IEnumeration->SetStringValueA(&sIEnumeration_EventNotification, "On");
				if (eStApiCError != StApiCError_NoError) break;
				printf("\tEventNotification[%s] = On\n", pszEventNames[i]);

			}
			if (eStApiCError != StApiCError_NoError) break;
		}

		/* ActionDeviceKey */
		{
			StApiHandle_t sIInteger = { NULL };

			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "ActionDeviceKey", &sIInteger);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->GenApi->IInteger->SetValue(&sIInteger, nDeviceKey, false);
			if (eStApiCError != StApiCError_NoError) break;
			printf("\tActionDeviceKey = 0x%08X\n", nDeviceKey);
		}

		/* ActionGroupKey */
		{
			StApiHandle_t sIInteger = { NULL };

			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "ActionGroupKey", &sIInteger);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->GenApi->IInteger->SetValue(&sIInteger, nGroupKey, false);
			if (eStApiCError != StApiCError_NoError) break;
			printf("\tActionGroupKey = 0x%08X\n", nGroupKey);
		}

		/* ActionGroupMask */
		{
			StApiHandle_t sIInteger = { NULL };

			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "ActionGroupMask", &sIInteger);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->GenApi->IInteger->SetValue(&sIInteger, nGroupMask, false);
			if (eStApiCError != StApiCError_NoError) break;
			printf("\tActionGroupMask = 0x%08X\n", nGroupMask);
		}

		/* ActionScheduledTimeEnable */
		{
			StApiHandle_t sIBoolean = { NULL };

			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "ActionScheduledTimeEnable", &sIBoolean);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->GenApi->IBoolean->SetValue(&sIBoolean, bScheduledTimeEnable, false);
			if (eStApiCError != StApiCError_NoError) break;
			printf("\tActionScheduledTimeEnable = %s\n", bScheduledTimeEnable ? "true" : "false");
		}

		if (bScheduledTimeEnable)
		{
			StApiHandle_t sIInteger = { NULL };

			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "ActionScheduledTime", &sIInteger);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->GenApi->IInteger->SetValue(&sIInteger, nScheduledTime, false);
			if (eStApiCError != StApiCError_NoError) break;
			printf("\tActionScheduledTime = %" PRIu64 "\n", nScheduledTime);
		}
		break;
	}
	return(eStApiCError);
}
void OnCommand(StApiHandle_t* pINodeHandle, void* pContext)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;
	const PApiFunctions psApiFunctions = (PApiFunctions)pContext;

	for (;;)
	{
		char szNodeName[256];
		size_t nLen = sizeof(szNodeName);
		EInterfaceType eInterfaceType;

		eStApiCError = psApiFunctions->GenApi->INode->GetNameA(pINodeHandle, false, szNodeName, &nLen);
		if (eStApiCError != StApiCError_NoError) break;

		printf("OnCallback:%s\n", szNodeName);

		eStApiCError = psApiFunctions->GenApi->INode->GetPrincipalInterfaceType(pINodeHandle, &eInterfaceType);
		if (eStApiCError != StApiCError_NoError) break;

		if (eInterfaceType == intfICategory)
		{
			size_t nCount;
			PStApiHandle_t psIValueHandleArray = NULL;

			eStApiCError = psApiFunctions->GenApi->ICategory->GetFeatures(pINodeHandle, NULL, &nCount);
			if (eStApiCError != StApiCError_NoError) break;

			/* Allocate memory for the interfaces of the entries. */
			psIValueHandleArray = (PStApiHandle_t)malloc(sizeof(StApiHandle_t) * nCount);
			if (psIValueHandleArray != NULL)
			{
				/* Get the entries. */
				eStApiCError = psApiFunctions->GenApi->ICategory->GetFeatures(pINodeHandle, psIValueHandleArray, &nCount);
				if (eStApiCError == StApiCError_NoError)
				{
					size_t i;

					for (i = 0; i < nCount; ++i)
					{
						char szValue[256];

						nLen = sizeof(szNodeName);
						eStApiCError = psApiFunctions->GenApi->INode->GetNameA(&psIValueHandleArray[i], false, szNodeName, &nLen);
						if (eStApiCError != StApiCError_NoError) break;

						nLen = sizeof(szValue);
						eStApiCError = psApiFunctions->GenApi->IValue->ToStringA(&psIValueHandleArray[i], false, false, szValue, &nLen);
						if (eStApiCError != StApiCError_NoError) break;
						printf("\t%s:%s\n", szNodeName, szValue);

					}
				}
				free(psIValueHandleArray);
				psIValueHandleArray = NULL;
			}
		}

		break;
	}
}

/*
Console function for sending action command.
*/
EStApiCError_t SendActionCommand(PApiFunctions psApiFunctions, PStApiHandle_t	pIStInterfaceHandleArray, const size_t nValidInterfaceCount)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;

	StApiHandle_t	pICommandHandleArray[MAXIMUM_INTERFACE_COUNT];
	StApiHandle_t	pIStRegisteredCallbackHandleArray_Sent[MAXIMUM_INTERFACE_COUNT];
	StApiHandle_t	pIStRegisteredCallbackHandleArray_Rcv[MAXIMUM_INTERFACE_COUNT];

	memset(pICommandHandleArray, 0, sizeof(pICommandHandleArray));
	memset(pIStRegisteredCallbackHandleArray_Sent, 0, sizeof(pIStRegisteredCallbackHandleArray_Sent));
	memset(pIStRegisteredCallbackHandleArray_Rcv, 0, sizeof(pIStRegisteredCallbackHandleArray_Rcv));
	for (;;)
	{
		size_t i;
		for (i = 0; i < nValidInterfaceCount; ++i)
		{
			PStApiHandle_t pIStInterfaceHandle = &pIStInterfaceHandleArray[i];
			StApiHandle_t sIStPortHandle = { NULL };
			StApiHandle_t sINodeMapHandle = { NULL };
			StApiHandle_t sINode_EventActionCommandData = { NULL };
			StApiHandle_t sINode_EventActionCommandAcknowledgeData = { NULL };

			eStApiCError = psApiFunctions->StApi->IStInterface->GetIStPort(pIStInterfaceHandle, &sIStPortHandle);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->StApi->IStPort->GetINodeMap(&sIStPortHandle, &sINodeMapHandle);
			if (eStApiCError != StApiCError_NoError) break;

			/* ActionCommandHandle. */
			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "ActionCommand", &pICommandHandleArray[i]);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "EventActionCommandData", &sINode_EventActionCommandData);
			if (eStApiCError != StApiCError_NoError) break;

			/*
			Register acquired INode interface pointer with callback function for calling.
			When the event of passed-in INode indicated is triggered, the registered callback function will be called.
			*/
			{
				eStApiCError = psApiFunctions->GenApi->INode->RegisterCallback(&sINode_EventActionCommandData, OnCommand, cbPostInsideLock, psApiFunctions, &pIStRegisteredCallbackHandleArray_Sent[i]);
				if (eStApiCError != StApiCError_NoError) break;
			}

			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "EventActionCommandAcknowledgeData", &sINode_EventActionCommandAcknowledgeData);
			if (eStApiCError != StApiCError_NoError) break;
			{
				eStApiCError = psApiFunctions->GenApi->INode->RegisterCallback(&sINode_EventActionCommandAcknowledgeData, OnCommand, cbPostInsideLock, psApiFunctions, &pIStRegisteredCallbackHandleArray_Rcv[i]);
				if (eStApiCError != StApiCError_NoError) break;
			}
		}
		if (eStApiCError != StApiCError_NoError) break;

		{
			uint64_t i;
			for (i = 0; i < nCountOfImagesToGrab; ++i)
			{
				size_t j = 0;
				/* Send action command. */
				for (j = 0; j < nValidInterfaceCount; ++j)
				{
					eStApiCError = psApiFunctions->GenApi->ICommand->Execute(&pICommandHandleArray[j], false);
					if (eStApiCError != StApiCError_NoError) break;
				}
				sleep(1);

			}
		}
		break;
	}

	{
		size_t i;
		for (i = 0; i < nValidInterfaceCount; ++i)
		{
			psApiFunctions->StApi->IStRegisteredCallback->Release(&pIStRegisteredCallbackHandleArray_Sent[i]);
		}
	}

	{
		size_t i;
		for (i = 0; i < nValidInterfaceCount; ++i)
		{
			psApiFunctions->StApi->IStRegisteredCallback->Release(&pIStRegisteredCallbackHandleArray_Rcv[i]);
		}
	}

	return(eStApiCError);
}

/*

*/
typedef struct _SCallbackParam_t
{
	PApiFunctions	psApiFunctions;
	StApiHandle_t	sIStDataStreamHandle;
	StApiHandle_t	sIStRegisteredCallbackHandle;
}SCallbackParam_t, *PSCallbackParam_t;


/*
Function for handling callback action
*/
void OnReceiveImage(const PSCallbackParam_t pCallbackParam, PStApiHandle_t pIStStreamBufferHandle)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;

	const PApiFunctions psApiFunctions = pCallbackParam->psApiFunctions;
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
			StApiHandle_t sIStStreamBufferInfoHandle = { NULL };
			uint64_t iFrameID;
			void *pBuffer;

			eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStStreamBufferInfo(pIStStreamBufferHandle, &sIStStreamBufferInfoHandle);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->StApi->IStStreamBufferInfo->GetFrameID(&sIStStreamBufferInfoHandle, &iFrameID);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->StApi->IStImage->GetImageBuffer(&sIStImageHandle, &pBuffer);
			if (eStApiCError != StApiCError_NoError) break;

			printf("BlockID=%" PRIu64 " Size: %zu x %zu First byte = %u\n", iFrameID, nImageWidth, nImageHeight, *(uint8_t*)pBuffer);
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
	const PApiFunctions psApiFunctions = pCallbackParam->psApiFunctions;
	const PStApiHandle_t pDataStreamHandle = &pCallbackParam->sIStDataStreamHandle;

	uint32_t iTimeoutTime = 0;
	StApiHandle_t sIStStreamBufferHandle = { NULL };
	EStApiCError_t eStApiCError = StApiCError_NoError;
	eStApiCError = psApiFunctions->StApi->IStDataStream->RetrieveBuffer(pDataStreamHandle, iTimeoutTime, &sIStStreamBufferHandle);

	if (eStApiCError == StApiCError_NoError)
	{
		OnReceiveImage(pCallbackParam, &sIStStreamBufferHandle);
	}
}

/*

*/
int main(int argc, char ** argv)
{
	/* Initialize StApiC before using. */
	PApiFunctions psApiFunctions = NULL;
	EStApiCError_t eStApiCError = StApiCInitialize(STAPI_VERSION, &psApiFunctions);

	StApiHandle_t sIStSystemHandle = { NULL };
	StApiHandle_t	pIStInterfaceHandleArray[MAXIMUM_INTERFACE_COUNT];
	StApiHandle_t	pIStDeviceHandleArray[MAXIMUM_DEVICE_COUNT];
	StApiHandle_t	pIStDataStreamHandleArray[MAXIMUM_DEVICE_COUNT];

	PSCallbackParam_t	pCallbackParam = NULL;
	size_t nValidDeviceCount = 0;
	size_t nValidInterfaceCount = 0;

	if (eStApiCError != StApiCError_NoError)
	{
		printf("initializing StApiC was failed.\n");
		return(0);
	}

	memset(pIStInterfaceHandleArray, 0, sizeof(pIStInterfaceHandleArray));
	memset(pIStDeviceHandleArray, 0, sizeof(pIStDeviceHandleArray));
	memset(pIStDataStreamHandleArray, 0, sizeof(pIStDataStreamHandleArray));
	for (;;)
	{
		uint32_t nInterfaceCount;
		size_t i;

		/* Create a system object for device scan and connection. */
		eStApiCError = psApiFunctions->StApi->IStSystem->CreateIStSystem(StSystemVendor_Default, StInterfaceType_GigEVision, &sIStSystemHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* 
		Check GigE interface for devices.
		*/
		eStApiCError = psApiFunctions->StApi->IStSystem->GetInterfaceCount(&sIStSystemHandle, &nInterfaceCount);
		if (eStApiCError != StApiCError_NoError) break;

		for (i = 0; i < nInterfaceCount; ++i)
		{
			StApiHandle_t sIStInterfaceHandle = { NULL };
			StApiHandle_t sIStPortHandle = { NULL };
			StApiHandle_t sINodeMapHandle = { NULL };
			StApiHandle_t sIIntegerHandle_InterfaceIPAddress = { NULL };
			char szText[256];
			size_t nLen = sizeof(szText);

			eStApiCError = psApiFunctions->StApi->IStSystem->GetIStInterface(&sIStSystemHandle, i, &sIStInterfaceHandle);
			if (eStApiCError != StApiCError_NoError) break;

			/* Use INodeMap object to access current setting of the interface. */
			eStApiCError = psApiFunctions->StApi->IStInterface->GetIStPort(&sIStInterfaceHandle, &sIStPortHandle);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->StApi->IStPort->GetINodeMap(&sIStPortHandle, &sINodeMapHandle);
			if (eStApiCError != StApiCError_NoError) break;

			/* Display the IP address of the host side. */
			eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapHandle, "GevInterfaceSubnetIPAddress", &sIIntegerHandle_InterfaceIPAddress);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			/* Displays the DisplayName of the interface. */
			eStApiCError = psApiFunctions->GenApi->IValue->ToStringA(&sIIntegerHandle_InterfaceIPAddress, false, false, szText, &nLen);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			printf("Interface[%zu]IP Address = %s\n", i, szText);

			SetHostActionCommandParam(psApiFunctions, &sIStInterfaceHandle);

			/*Start Event Acquisition Thread*/
			eStApiCError = psApiFunctions->StApi->IStInterface->StartEventAcquisitionThread(&sIStInterfaceHandle);
			if (eStApiCError != StApiCError_NoError) break;

			/* Add the interface into interface object list for later usage. */
			pIStInterfaceHandleArray[nValidInterfaceCount++] = sIStInterfaceHandle;
		}
		if (eStApiCError != StApiCError_NoError) break;
		if (nValidInterfaceCount == 0)
		{
			printf("There is no interface.\n");
			break;
		}

		/* Here we try to connect to all possible device with a do-while loop. */
		for (; nValidDeviceCount < MAXIMUM_DEVICE_COUNT;)
		{
			/* Create a camera device object and connect to first detected device by using the function of system object. */
			StApiHandle_t sIStDeviceHandle = { NULL };
			eStApiCError = psApiFunctions->StApi->IStSystem->CreateFirstIStDevice(&sIStSystemHandle, DEVICE_ACCESS_CONTROL, &sIStDeviceHandle);
			if (eStApiCError != StApiCError_NoError)
			{
				if (1 <= nValidDeviceCount)
				{
					eStApiCError = StApiCError_NoError;
				}
				break;
			}

			/* Add the camera into device object list for later usage. */
			pIStDeviceHandleArray[nValidDeviceCount++] = sIStDeviceHandle;

			/* Displays the DisplayName of the device. */
			{
				StApiHandle_t sIStDeviceInfoHandle = { NULL };
				char szDisplayName[1024];
				size_t nLen = sizeof(szDisplayName);

				eStApiCError = psApiFunctions->StApi->IStDevice->GetIStDeviceInfo(&sIStDeviceHandle, &sIStDeviceInfoHandle);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->StApi->IStDeviceInfo->GetDisplayNameA(&sIStDeviceInfoHandle, szDisplayName, &nLen);
				if (eStApiCError != StApiCError_NoError) break;

				printf("Device%zu=%s\n", nValidDeviceCount, szDisplayName);
			}

			eStApiCError = SetDeviceActionCommandParam(psApiFunctions, &sIStDeviceHandle);
			if (eStApiCError != StApiCError_NoError) break;

		}

		if (eStApiCError != StApiCError_NoError) break;
		if (nValidDeviceCount == 0)
		{
			printf("There is no device.\n");
			break;
		}

		pCallbackParam = (PSCallbackParam_t)malloc(sizeof(SCallbackParam_t) * nValidDeviceCount);
		if (pCallbackParam == NULL)
		{
			printf("Couldn't allocate memory for callback function parameters.");
			break;
		}

		{
			PSCallbackParam_t	pCallbackParamPos = pCallbackParam;
			for (i = 0; i < nValidDeviceCount; ++i)
			{
				PStApiHandle_t pIStDeviceHandle = &pIStDeviceHandleArray[i];

				pCallbackParamPos->psApiFunctions = psApiFunctions;

				/* Create a DataStream object for handling image stream data. */
				eStApiCError = psApiFunctions->StApi->IStDevice->CreateIStDataStream(pIStDeviceHandle, 0, NULL, &pCallbackParamPos->sIStDataStreamHandle);
				if (eStApiCError != StApiCError_NoError) break;

				/* Create a DataStream object for handling image stream data then add into DataStream list for later usage. */
				pIStDataStreamHandleArray[i] = pCallbackParamPos->sIStDataStreamHandle;

				eStApiCError = psApiFunctions->StApi->IStDataStream->RegisterCallback(&pCallbackParamPos->sIStDataStreamHandle, &OnDataStreamCallback, pCallbackParamPos, &pCallbackParamPos->sIStRegisteredCallbackHandle);
				if (eStApiCError != StApiCError_NoError) break;


				++pCallbackParamPos;
			}
		}
		if (eStApiCError != StApiCError_NoError) break;

		/* Start the image acquisition of the host (local machine) side. */
		eStApiCError = psApiFunctions->StApi->IStDataStreamArray->StartAcquisition(pIStDataStreamHandleArray, nValidDeviceCount, nCountOfImagesToGrab, ACQ_START_FLAGS_DEFAULT);
		if (eStApiCError != StApiCError_NoError) break;

		/* Start the image acquisition of the camera side. */
		eStApiCError = psApiFunctions->StApi->IStDeviceArray->AcquisitionStart(pIStDeviceHandleArray, nValidDeviceCount);
		if (eStApiCError != StApiCError_NoError) break;

		/* Adjust GevSCPD. */
		eStApiCError = AdjustGevSCPD(psApiFunctions, pIStDeviceHandleArray, nValidDeviceCount);
		if (eStApiCError != StApiCError_NoError) break;

		eStApiCError = SendActionCommand(psApiFunctions, pIStInterfaceHandleArray, nValidInterfaceCount);
		if (eStApiCError != StApiCError_NoError) break;

		/* Stop the image acquisition of the camera side. */
		psApiFunctions->StApi->IStDeviceArray->AcquisitionStop(pIStDeviceHandleArray, nValidDeviceCount);

		/* Stop the image acquisition of the host side. */
		psApiFunctions->StApi->IStDataStreamArray->StopAcquisition(pIStDataStreamHandleArray, nValidDeviceCount, ACQ_STOP_FLAGS_DEFAULT);

		{
			for (i = 0; i < nValidInterfaceCount; ++i)
			{
				/* Stop Event Acquisition Thread. */
				psApiFunctions->StApi->IStInterface->StopEventAcquisitionThread(&pIStInterfaceHandleArray[i]);
			}
		}
		break;
	}

	if (eStApiCError != StApiCError_NoError)
	{
		/* If any error occurred, display the description of the error here. */
		OutputErrorInfo(psApiFunctions);
	}


	if (pCallbackParam)
	{
		size_t i;
		for (i = 0; i < nValidDeviceCount; ++i)
		{
			psApiFunctions->StApi->IStRegisteredCallback->Release(&pCallbackParam[i].sIStRegisteredCallbackHandle);
		}
		free(pCallbackParam);
		pCallbackParam = NULL;
	}

	{
		size_t i;
		for (i = 0; i < nValidDeviceCount; ++i)
		{
			psApiFunctions->StApi->IStDataStream->Release(&pIStDataStreamHandleArray[i]);
		}
	}

	{
		size_t i;
		for (i = 0; i < nValidDeviceCount; ++i)
		{
			psApiFunctions->StApi->IStDevice->Release(&pIStDeviceHandleArray[i]);
		}
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

