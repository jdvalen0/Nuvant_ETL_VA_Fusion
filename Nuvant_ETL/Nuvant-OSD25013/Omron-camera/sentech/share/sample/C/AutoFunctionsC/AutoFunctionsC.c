/*!
\file AutoFunctionsC.c
\brief

This sample demostrates how to set AWB, AGC, and AE function.
The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to camera
- Acquire image via callback function
- Set AWB, AGC, AE

For more information, please refer to the help document of StApiC.
*/

#include <pthread.h>
#include <stdlib.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

/* Include file for using StApiC. */
#include <StApi_C.h>

/* Feature names */
const char * EXPOSURE_AUTO = "ExposureAuto";			/* Standard */
const char * GAIN_AUTO = "GainAuto";					/* Standard */
const char * BALANCE_WHITE_AUTO = "BalanceWhiteAuto";	/* Standard */

const char * AUTO_LIGHT_TARGET = "AutoLightTarget";		/* Custom */
const char * GAIN = "Gain";								/* Standard */
const char * GAIN_RAW = "GainRaw";						/* Custom */

const char * EXPOSURE_MODE = "ExposureMode";			/* Standard */
const char * EXPOSURE_TIME = "ExposureTime";			/* Standard */
const char * EXPOSURE_TIME_RAW = "ExposureTimeRaw";		/* Custom */

const char * BALANCE_RATIO_SELECTOR = "BalanceRatioSelector";	/* Standard */
const char * BALANCE_RATIO = "BalanceRatio";			/* Standard */


PApiFunctions psApiFunctions = NULL;
StApiHandle_t sSystemHandle = { NULL };
StApiHandle_t sIStDeviceHandle = { NULL };
StApiHandle_t sDataStreamHandle = { NULL };
StApiHandle_t sIStImageDisplayWndHandle = { NULL };
bool8_t isThreadCompleted = false;

void OutputErrorInfo()
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
	PStApiHandle_t	pIStImageDisplayWndHandle;
}SCallbackParam_t, *PSCallbackParam_t;

/*
Callback function for image display.
*/
void OnReceiveImage(const PSCallbackParam_t pCallbackParam, PStApiHandle_t pIStStreamBufferHandle)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;

	const PApiFunctions psApiFunctions = pCallbackParam->pApiFunctions;
	const PStApiHandle_t pDataStreamHandle = pCallbackParam->pIStDataStreamHandle;
	for (;;)
	{
		StApiHandle_t sIStStreamBufferInfoHandle = { NULL };
		bool8_t isImagePresent;
		eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStStreamBufferInfo(pIStStreamBufferHandle, &sIStStreamBufferInfoHandle);
		if (eStApiCError != StApiCError_NoError) break;

		/* Check if the acquired data contains image data. */
		eStApiCError = psApiFunctions->StApi->IStStreamBufferInfo->IsImagePresent(&sIStStreamBufferInfoHandle, &isImagePresent);
		if (eStApiCError != StApiCError_NoError) break;

		if (isImagePresent)
		{
			StApiHandle_t sIStImageHandle = { NULL };
			size_t nImageWidth;
			size_t nImageHeight;
			const PStApiHandle_t pIStImageDisplayWndHandle = pCallbackParam->pIStImageDisplayWndHandle;
			double dblFPS;
			char szStatusText[1024];
			bool8_t isVisible;

			eStApiCError = psApiFunctions->StApi->IStStreamBuffer->GetIStImage(pIStStreamBufferHandle, &sIStImageHandle);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->StApi->IStImage->GetImageWidth(&sIStImageHandle, &nImageWidth);
			if (eStApiCError != StApiCError_NoError) break;

			eStApiCError = psApiFunctions->StApi->IStImage->GetImageHeight(&sIStImageHandle, &nImageHeight);
			if (eStApiCError != StApiCError_NoError) break;

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
		}
		break;
	}
	if (eStApiCError != StApiCError_NoError)
	{
		OutputErrorInfo();
	}

	psApiFunctions->StApi->IStStreamBuffer->Release(pIStStreamBufferHandle);
	}

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

/*
List up the numeric value of the current setting that the node indicated.
*/
EStApiCError_t IntegerNode(PApiFunctions psApiFunctions, PStApiHandle_t pINodeMapHandle, const char *szNodeName)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;
	StApiHandle_t sIIntegerHandle = { NULL };
	bool8_t isWritable;

	/* Get the IInteger interface handle */
	eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, szNodeName, &sIIntegerHandle);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	eStApiCError = psApiFunctions->GenApi->IBase->IsWritable(&sIIntegerHandle, &isWritable);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	if (isWritable)
	{
		for (;;)
		{
			int64_t nMin;
			int64_t nMax;
			int64_t nCurrent;
			EIncMode eIncMode;
			int64_t nValue;

			eStApiCError = psApiFunctions->GenApi->IInteger->GetMin(&sIIntegerHandle, &nMin);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			eStApiCError = psApiFunctions->GenApi->IInteger->GetMax(&sIIntegerHandle, &nMax);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			eStApiCError = psApiFunctions->GenApi->IInteger->GetValue(&sIIntegerHandle, false, false, &nCurrent);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			eStApiCError = psApiFunctions->GenApi->IInteger->GetIncMode(&sIIntegerHandle, &eIncMode);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			/* Display the feature name, range, current value, and incremental value. */
			printf("%s Min=%" PRId64 " Max=%" PRId64 " Current=%" PRId64, szNodeName, nMin, nMax, nCurrent);

			if (eIncMode == fixedIncrement)
			{
				int64_t nInc;

				eStApiCError = psApiFunctions->GenApi->IInteger->GetInc(&sIIntegerHandle, &nInc);
				if (eStApiCError != StApiCError_NoError) return(eStApiCError);
				printf(" Inc=%" PRId64, nInc);
			}
			printf("\nNew Value : ");

			/* Waiting for input of new value. */
			scanf("%" PRId64, &nValue);

			/* Reflect the value entered. */
			if ((nMin <= nValue) && (nValue <= nMax))
			{
				eStApiCError = psApiFunctions->GenApi->IInteger->SetValue(&sIIntegerHandle, nValue, false);
				break;
			}
		}

	}
	

	return(eStApiCError);
}

/*
List up the numeric value of the current setting that the node indicated.
*/
EStApiCError_t FloatNode(PApiFunctions psApiFunctions, PStApiHandle_t pINodeMapHandle, const char *szNodeName)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;
	StApiHandle_t sIFloatHandle = { NULL };
	bool8_t isWritable;

	/* Get the Float interface handle */
	eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, szNodeName, &sIFloatHandle);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	eStApiCError = psApiFunctions->GenApi->IBase->IsWritable(&sIFloatHandle, &isWritable);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	if (isWritable)
	{
		for (;;)
		{
			double nMin;
			double nMax;
			double nCurrent;
			EIncMode eIncMode;
			double dblValue;

			eStApiCError = psApiFunctions->GenApi->IFloat->GetMin(&sIFloatHandle, &nMin);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			eStApiCError = psApiFunctions->GenApi->IFloat->GetMax(&sIFloatHandle, &nMax);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			eStApiCError = psApiFunctions->GenApi->IFloat->GetValue(&sIFloatHandle, false, false, &nCurrent);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			eStApiCError = psApiFunctions->GenApi->IFloat->GetIncMode(&sIFloatHandle, &eIncMode);
			if (eStApiCError != StApiCError_NoError) return(eStApiCError);

			/* Display the feature name, range, current value, and incremental value. */
			printf("%s Min=%f Max=%f Current=%f", szNodeName, nMin, nMax, nCurrent);

			if (eIncMode == fixedIncrement)
			{
				double nInc;

				eStApiCError = psApiFunctions->GenApi->IFloat->GetInc(&sIFloatHandle, &nInc);
				if (eStApiCError != StApiCError_NoError) return(eStApiCError);
				printf(" Inc=%f", nInc);
			}
			printf("\nNew Value : ");

			/* Waiting for input of new value. */
			scanf("%lf", &dblValue);

			/* Reflect the value entered. */
			if ((nMin <= dblValue) && (dblValue <= nMax))
			{
				eStApiCError = psApiFunctions->GenApi->IFloat->SetValue(&sIFloatHandle, dblValue, false);
				break;
			}
		}
	}
	
	return(eStApiCError);
}

typedef EStApiCError_t(*SelectedNodeOperation_t)(PApiFunctions psApiFunctions, PStApiHandle_t pINodeMapHandle);

/*
List up the contents of current enumeration node with current numeric setting.
*/
EStApiCError_t EnumerationAndNumericNode(PApiFunctions psApiFunctions, PStApiHandle_t pINodeMapHandle, const char *szEnumerationName, SelectedNodeOperation_t pFunc)
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
				EVisibility eVisibility;
				bool8_t isVisible;

				/* Check the node is visible. */
				eStApiCError = psApiFunctions->GenApi->INode->GetVisibility(&psIEnumEntryHandleArray[nIndex], &eVisibility);
				if (eStApiCError != StApiCError_NoError) break;

				eStApiCError = psApiFunctions->GenApi->IPublic->IsVisible(eVisibility, Guru, &isVisible);
				if (isVisible)
				{
					int64_t nValue;
					char szName[256];
					size_t nSize = sizeof(szName);

					eStApiCError = psApiFunctions->GenApi->IEnumEntry->GetValue(&psIEnumEntryHandleArray[nIndex], &nValue);
					if (eStApiCError != StApiCError_NoError) break;

					/* Switch the setting target using the IEnumeration interface pointer */
					eStApiCError = psApiFunctions->GenApi->IEnumeration->SetIntValue(&sIEnumerationHandle, nValue, false);
					if (eStApiCError != StApiCError_NoError) break;

					eStApiCError = psApiFunctions->GenApi->IEnumEntry->GetSymbolicA(&psIEnumEntryHandleArray[nIndex], szName, &nSize);
					if (eStApiCError != StApiCError_NoError) break;

					/* Display the selected setting target */
					printf("%s = %s\n", szEnumerationName, szName);

					/* Configure a numerical value */
					eStApiCError = pFunc(psApiFunctions, pINodeMapHandle);
					if (eStApiCError != StApiCError_NoError) break;
				}
			}
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


/*

*/
EStApiCError_t ExposureAuto(PApiFunctions psApiFunctions, PStApiHandle_t pINodeMapHandle)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;
	StApiHandle_t sINodeHandle = { NULL };

	/* Configure the ExposureMode */
	eStApiCError = EnumerationNode(psApiFunctions, pINodeMapHandle, EXPOSURE_MODE);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	/* Configure the ExposureAuto */
	eStApiCError = EnumerationNode(psApiFunctions, pINodeMapHandle, EXPOSURE_AUTO);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	/* Configure the AutoLightTarget */
	eStApiCError = IntegerNode(psApiFunctions, pINodeMapHandle, AUTO_LIGHT_TARGET);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, EXPOSURE_TIME, &sINodeHandle);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	if (sINodeHandle.Handle)
	{
		/* Configure the ExposureTime */
		eStApiCError = FloatNode(psApiFunctions, pINodeMapHandle, EXPOSURE_TIME);
	}
	else
	{
		/* Configure the ExposureTimeRaw if the ExposureTime function does not exist */
		eStApiCError = IntegerNode(psApiFunctions, pINodeMapHandle, EXPOSURE_TIME_RAW);
	}
	return(eStApiCError);
}

/*

*/
EStApiCError_t GainAuto(PApiFunctions psApiFunctions, PStApiHandle_t pINodeMapHandle)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;
	StApiHandle_t sINodeHandle = { NULL };

	/* Configure the GainAuto */
	eStApiCError = EnumerationNode(psApiFunctions, pINodeMapHandle, GAIN_AUTO);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	/* Configure the AutoLightTarget */
	eStApiCError = IntegerNode(psApiFunctions, pINodeMapHandle, AUTO_LIGHT_TARGET);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(pINodeMapHandle, GAIN, &sINodeHandle);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	if (sINodeHandle.Handle)
	{
		/* Configure the Gain */
		eStApiCError = FloatNode(psApiFunctions, pINodeMapHandle, GAIN);
	}
	else
	{
		/* Configure the GainRaw if the Gain function does not exist */
		eStApiCError = IntegerNode(psApiFunctions, pINodeMapHandle, GAIN_RAW);
	}
	return(eStApiCError);
}

/*

*/
EStApiCError_t BalanceRatio(PApiFunctions psApiFunctions, PStApiHandle_t pINodeMapHandle)
{
	return(FloatNode(psApiFunctions, pINodeMapHandle, BALANCE_RATIO));
}
/*

*/
EStApiCError_t BalanceWhiteAuto(PApiFunctions psApiFunctions, PStApiHandle_t pINodeMapHandle)
{
	EStApiCError_t eStApiCError = StApiCError_NoError;

	/* Configure the BalanceWhiteAuto */
	eStApiCError = EnumerationNode(psApiFunctions, pINodeMapHandle, BALANCE_WHITE_AUTO);
	if (eStApiCError != StApiCError_NoError) return(eStApiCError);

	/* While switching the BalanceRatioSelector, configure the BalanceRatio */
	eStApiCError = EnumerationAndNumericNode(psApiFunctions, pINodeMapHandle, BALANCE_RATIO_SELECTOR, BalanceRatio);
	return(eStApiCError);
}

void* displayChoiceWorker(void *arg)
{
    const uint64_t iNumToAcquire = GENTL_INFINITE;
    const char* pszAutoFunctionNames[] = { EXPOSURE_AUTO, GAIN_AUTO, BALANCE_WHITE_AUTO };
    size_t i;
    bool8_t pisWritable[] = { false, false, false };
    StApiHandle_t sIStPortRemoteHandle = { NULL };
    StApiHandle_t sINodeMapRemoteHandle = { NULL };

    EStApiCError_t eStApiCError = psApiFunctions->StApi->IStDataStream->StartAcquisition(&sDataStreamHandle, iNumToAcquire, ACQ_START_FLAGS_DEFAULT);
    if (eStApiCError != StApiCError_NoError) return NULL;

    eStApiCError = psApiFunctions->StApi->IStDevice->AcquisitionStart(&sIStDeviceHandle);
    if (eStApiCError != StApiCError_NoError) return NULL;

    /* Use INodeMap object to access current setting of the camera. */
    eStApiCError = psApiFunctions->StApi->IStDevice->GetRemoteIStPort(&sIStDeviceHandle, &sIStPortRemoteHandle);
    if (eStApiCError != StApiCError_NoError) return NULL;

    eStApiCError = psApiFunctions->StApi->IStPort->GetINodeMap(&sIStPortRemoteHandle, &sINodeMapRemoteHandle);
    if (eStApiCError != StApiCError_NoError) return NULL;

    /* Check if the camera has AE, AWB and AWB functions. */
    for (i = 0; i < sizeof(pisWritable) / sizeof(bool8_t); i++)
    {
        StApiHandle_t sINodeHandle = { NULL };

        /* User INode interface to acquire the setting of camera with function name. */
        eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapRemoteHandle, pszAutoFunctionNames[i], &sINodeHandle);
        if (eStApiCError != StApiCError_NoError) continue;

        eStApiCError = psApiFunctions->GenApi->IBase->IsWritable(&sINodeHandle, &pisWritable[i]);
        if (eStApiCError != StApiCError_NoError) continue;
    }
    if (eStApiCError != StApiCError_NoError) return NULL;

    for (;;)
    {
        size_t nInput;

        /* Display menu of setting function */
        printf("Auto Functions\n");
        for (i = 0; i < sizeof(pisWritable) / sizeof(bool8_t); i++)
        {
            if (pisWritable[i])
            {
                printf("%zu : %s\n", i, pszAutoFunctionNames[i]);
            }
        }
        printf("Else : Exit\n");
        printf("Select : ");

        /* Waiting for input. */
        scanf("%zu", &nInput);

        if ((nInput < sizeof(pisWritable) / sizeof(bool8_t)) && pisWritable[nInput])
        {
            /* Call the function for setting according to the input. */
            switch (nInput)
            {
                case(0) : eStApiCError = ExposureAuto(psApiFunctions, &sINodeMapRemoteHandle); break;
                case(1) : eStApiCError = GainAuto(psApiFunctions, &sINodeMapRemoteHandle); break;
                case(2) : eStApiCError = BalanceWhiteAuto(psApiFunctions, &sINodeMapRemoteHandle); break;
            }
            if (eStApiCError != StApiCError_NoError) break;

        }
        else
        {
            /* Exit */
            break;
        }
    }
    psApiFunctions->StApi->IStDevice->AcquisitionStop(&sIStDeviceHandle);
    psApiFunctions->StApi->IStDataStream->StopAcquisition(&sDataStreamHandle, ACQ_STOP_FLAGS_DEFAULT);
    isThreadCompleted = true;
    return NULL;
}


int main(int argc, char **argv)
{
	/* Initialize StApiC before using. */
	EStApiCError_t eStApiCError = StApiCInitialize(STAPI_VERSION, &psApiFunctions);

    StApiHandle_t	sIStRegisteredCallbackHandle = { NULL };
    StApiHandle_t sIStDeviceInfoHandle = { NULL };

	SCallbackParam_t sCallbackParam =
	{
		psApiFunctions,
		&sDataStreamHandle,
		&sIStImageDisplayWndHandle,
	};

	if (eStApiCError != StApiCError_NoError)
	{
		printf("initializing StApiC was failed.\n");
		return(0);
	}

    /* Create a system object for device scan and connection. */
    eStApiCError = psApiFunctions->StApi->IStSystem->CreateIStSystem(StSystemVendor_Default, StInterfaceType_All, &sSystemHandle);
    if (eStApiCError != StApiCError_NoError) return 0;

    /* Create a camera device object and connect to first detected device by using the function of system object. */
    eStApiCError = psApiFunctions->StApi->IStSystem->CreateFirstIStDevice(&sSystemHandle, DEVICE_ACCESS_CONTROL, &sIStDeviceHandle);
    if (eStApiCError != StApiCError_NoError) return 0;

    /* Displays the DisplayName of the device. */
    {
        char szDisplayName[1024];
        size_t nLen = sizeof(szDisplayName);

        eStApiCError = psApiFunctions->StApi->IStDevice->GetIStDeviceInfo(&sIStDeviceHandle, &sIStDeviceInfoHandle);
        if (eStApiCError != StApiCError_NoError) return 0;

        eStApiCError = psApiFunctions->StApi->IStDeviceInfo->GetDisplayNameA(&sIStDeviceInfoHandle, szDisplayName, &nLen);
        if (eStApiCError != StApiCError_NoError) return 0;

        printf("Device=%s\n", szDisplayName);
    }

    /* Create a display window here. */
    eStApiCError = psApiFunctions->StApi->IStWnd->CreateIStWnd(StWindowType_ImageDisplay, &sIStImageDisplayWndHandle);
    if (eStApiCError != StApiCError_NoError) return 0;

    /* Create a DataStream object for handling image stream data. */
    eStApiCError = psApiFunctions->StApi->IStDevice->CreateIStDataStream(&sIStDeviceHandle, 0, NULL, &sDataStreamHandle);
    if (eStApiCError != StApiCError_NoError) return 0;

    eStApiCError = psApiFunctions->StApi->IStDataStream->RegisterCallback(&sDataStreamHandle, &OnDataStreamCallback, (void*)&sCallbackParam, &sIStRegisteredCallbackHandle);
    if (eStApiCError != StApiCError_NoError) return 0;

    /* Create a thread for receiving user's input and check the thread status */
    {
        bool8_t isVisible;
        pthread_t thread;
        pthread_create(&thread, NULL, displayChoiceWorker, (void*)NULL);
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

    psApiFunctions->StApi->IStRegisteredCallback->Release(&sIStRegisteredCallbackHandle);

	if (eStApiCError != StApiCError_NoError)
	{
		/* If any error occurred, display the description of the error here. */
		OutputErrorInfo();
	}

	if (sIStImageDisplayWndHandle.Handle)
	{
		psApiFunctions->StApi->IStWnd->Release(&sIStImageDisplayWndHandle);
	}

	if (sDataStreamHandle.Handle)
	{
		psApiFunctions->StApi->IStDataStream->Release(&sDataStreamHandle);
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

