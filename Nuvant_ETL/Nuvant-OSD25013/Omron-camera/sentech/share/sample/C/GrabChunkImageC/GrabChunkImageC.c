/*!
\file GrabChunkImage.cpp
\brief

This sample shows the basic operation of using StApi and display chunk data of the received image.
The following points will be demonstrated in this sample code:
- Initialize StApiC
- Connect to camera
- Acquire and display chunk data.

For more information, please refer to the help document of StApiC.
*/

#include <stdlib.h>
#include <string.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

/* Include file for using StApiC. */
#include <StApi_C.h>

/* Target counts of image to be grabbed. */
const uint64_t nCountOfImagesToGrab = 100;

/* Enable the following comment if you want to enable all of the chunks */
/* #define ENABLED_ALL_CHUNKS */


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
const char * CHUNK_MODE_ACTIVE = "ChunkModeActive"; /* Standard */
const char * CHUNK_SELECTOR = "ChunkSelector";      /* Standard */
const char * CHUNK_ENABLE = "ChunkEnable";          /* Standard */

#ifdef  ENABLED_ALL_CHUNKS
#define MAXIMUM_CHUNK_COUNT 10
#else
const char * TARGET_CHUNK_NAME = "ExposureTime";    /* Standard */
#define MAXIMUM_CHUNK_COUNT 1
#endif


void DisplayNodeValues(PApiFunctions psApiFunctions, PStApiHandle_t pINodeChunkArray, const size_t nValidChunkCount)
{
    size_t i;
    for (i = 0; i < nValidChunkCount; ++i)
    {
        PStApiHandle_t    pINode = &pINodeChunkArray[i];
        char szName[256];
        size_t nSize = sizeof(szName);
        EStApiCError_t eStApiCError = StApiCError_NoError;
        bool8_t isReadable;

        /* Get the node name */
        eStApiCError = psApiFunctions->GenApi->INode->GetNameA(pINode, false, szName, &nSize);
        if (eStApiCError != StApiCError_NoError) break;

        eStApiCError = psApiFunctions->GenApi->IBase->IsReadable(pINode, &isReadable);
        if (eStApiCError != StApiCError_NoError) break;

        /* Get the value of the node */
        if (!isReadable)
        {
            printf(" %s is not readable.\n", szName);
        }
        else
        {
            char szValue[256];
            nSize = sizeof(szValue);

            eStApiCError = psApiFunctions->GenApi->IValue->ToStringA(pINode, true, false, szValue, &nSize);
            printf(" %s = %s\n", szName, szValue);
        }
    }
}


EStApiCError_t EnabledChunkEntry(PApiFunctions psApiFunctions, PStApiHandle_t psINodeEnumerationChunkSelectorHandle, PStApiHandle_t psINodeBooleanChunkEnableHandle, PStApiHandle_t psINodeEnumEntryChunkSelectorHandle, PStApiHandle_t psINodeMapRemoteHandle, PStApiHandle_t    pINodeChunkArray)
{
    EStApiCError_t eStApiCError = StApiCError_NoError;

    for (;;)
    {
        char szSymbolic[256];
        size_t nSize = sizeof(szSymbolic);
        bool8_t isAvailable;

        eStApiCError = psApiFunctions->GenApi->IEnumEntry->GetSymbolicA(psINodeEnumEntryChunkSelectorHandle, szSymbolic, &nSize);
        if (eStApiCError != StApiCError_NoError) break;

        if (strcmp(szSymbolic, "Image") == 0)
        {
            break;
        }

        eStApiCError = psApiFunctions->GenApi->IBase->IsAvailable(psINodeEnumEntryChunkSelectorHandle, &isAvailable);
        if (eStApiCError != StApiCError_NoError) break;

        if (isAvailable)
        {
            int64_t nValue;
            bool8_t isWritable;

            /* If Chunk is valid, set to the selector */
            eStApiCError = psApiFunctions->GenApi->IEnumEntry->GetValue(psINodeEnumEntryChunkSelectorHandle, &nValue);
            if (eStApiCError != StApiCError_NoError) break;

            eStApiCError = psApiFunctions->GenApi->IEnumeration->SetIntValue(psINodeEnumerationChunkSelectorHandle, nValue, true);
            if (eStApiCError != StApiCError_NoError) break;

            eStApiCError = psApiFunctions->GenApi->IBase->IsWritable(psINodeBooleanChunkEnableHandle, &isWritable);
            if (eStApiCError != StApiCError_NoError) break;
            if (isWritable)
            {
                char szChunkValueName[262];
                StApiHandle_t sChunkValueHandle = { NULL };

                /* If ChunkEnable settings can be changed, enable it. */
                eStApiCError = psApiFunctions->GenApi->IBoolean->SetValue(psINodeBooleanChunkEnableHandle, true, true);
                if (eStApiCError != StApiCError_NoError) break;

                /* Get the node for the value of Chunk, be registered in the list. */

                sprintf(szChunkValueName, "Chunk%s", szSymbolic);

                eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(psINodeMapRemoteHandle, szChunkValueName, &sChunkValueHandle);
                if (eStApiCError != StApiCError_NoError) break;
                if (sChunkValueHandle.Handle == NULL)
                {
                    printf("Not found a feature %s.\n", szChunkValueName);
                    break;
                }

                *pINodeChunkArray = sChunkValueHandle;
            }
        }
        else
        {
            printf("%s is not implemented.\n", szSymbolic);
        }
        break;
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

    /* INode interface handle list for the value of Chunk */
    StApiHandle_t    pINodeChunkArray[MAXIMUM_CHUNK_COUNT];
    size_t nValidChunkCount = 0;

    if (eStApiCError != StApiCError_NoError)
    {
        printf("initializing StApiC was failed.\n");
        return(0);
    }

    memset(pINodeChunkArray, 0, sizeof(pINodeChunkArray));
    for (;;)
    {
        StApiHandle_t sIStPortRemoteHandle = { NULL };
        StApiHandle_t sINodeMapRemoteHandle = { NULL };
        StApiHandle_t sINodeBooleanChunkModeActiveHandle = { NULL };
        StApiHandle_t sINodeEnumerationChunkSelectorHandle = { NULL };
        StApiHandle_t sINodeBooleanChunkEnableHandle = { NULL };

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
        /* Create a DataStream object for handling image stream data. */
        eStApiCError = psApiFunctions->StApi->IStDevice->CreateIStDataStream(&sIStDeviceHandle, 0, NULL, &sIStDataStreamHandle);
        if (eStApiCError != StApiCError_NoError) break;

        /* Use INodeMap object to access current setting of the camera. */
        eStApiCError = psApiFunctions->StApi->IStDevice->GetRemoteIStPort(&sIStDeviceHandle, &sIStPortRemoteHandle);
        if (eStApiCError != StApiCError_NoError) break;

        eStApiCError = psApiFunctions->StApi->IStPort->GetINodeMap(&sIStPortRemoteHandle, &sINodeMapRemoteHandle);
        if (eStApiCError != StApiCError_NoError) break;


        /* Get related INode to access and active the chunk mode. */
        eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapRemoteHandle, CHUNK_MODE_ACTIVE, &sINodeBooleanChunkModeActiveHandle);
        if (eStApiCError != StApiCError_NoError) break;
        if (sINodeBooleanChunkModeActiveHandle.Handle == NULL)
        {
            printf("Not found a feature %s.\n", CHUNK_MODE_ACTIVE);
            break;
        }
        eStApiCError = psApiFunctions->GenApi->IBoolean->SetValue(&sINodeBooleanChunkModeActiveHandle, true, false);
        if (eStApiCError != StApiCError_NoError) break;

        /* Get the IEnumeration interface pointer to access ChunkSelector node. */
        eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapRemoteHandle, CHUNK_SELECTOR, &sINodeEnumerationChunkSelectorHandle);
        if (eStApiCError != StApiCError_NoError) break;
        if (sINodeEnumerationChunkSelectorHandle.Handle == NULL)
        {
            printf("Not found a feature %s.\n", CHUNK_SELECTOR);
            break;
        }

        /* Get the IBoolean interface pointer to access the ChunkEnable node. */
        eStApiCError = psApiFunctions->GenApi->INodeMap->GetNodeA(&sINodeMapRemoteHandle, CHUNK_ENABLE, &sINodeBooleanChunkEnableHandle);
        if (eStApiCError != StApiCError_NoError) break;
        if (sINodeBooleanChunkEnableHandle.Handle == NULL)
        {
            printf("Not found a feature %s.\n", CHUNK_ENABLE);
            break;
        }

        {
            size_t nIndex;
            size_t nEntryCount;
            StApiHandle_t psINodeEnumEntryChunkSelectorArray[MAXIMUM_CHUNK_COUNT];
#ifdef ENABLED_ALL_CHUNKS

            /* Get the Chunk entry list described in the XML file. */
            eStApiCError = psApiFunctions->GenApi->IEnumeration->GetEntries(&sINodeEnumerationChunkSelectorHandle, NULL, &nEntryCount);
            if (eStApiCError != StApiCError_NoError) break;

            if (MAXIMUM_CHUNK_COUNT < nEntryCount)
            {
                nEntryCount = MAXIMUM_CHUNK_COUNT;
            }

            eStApiCError = psApiFunctions->GenApi->IEnumeration->GetEntries(&sINodeEnumerationChunkSelectorHandle, psINodeEnumEntryChunkSelectorArray, &nEntryCount);
            if (eStApiCError != StApiCError_NoError) break;
#else
            /* Get the IEnumEntry interface pointer for the specified Chunk. */
            eStApiCError = psApiFunctions->GenApi->IEnumeration->GetEntryByNameA(&sINodeEnumerationChunkSelectorHandle, TARGET_CHUNK_NAME, &psINodeEnumEntryChunkSelectorArray[0]);
            if (eStApiCError != StApiCError_NoError) break;
            if (psINodeEnumEntryChunkSelectorArray[0].Handle == NULL)
            {
                printf("Not found a feature %s.\n", TARGET_CHUNK_NAME);
                break;
            }
            nEntryCount = 1;
#endif
            for (nIndex = 0; nIndex < nEntryCount; ++nIndex)
            {
                EnabledChunkEntry(psApiFunctions, &sINodeEnumerationChunkSelectorHandle, &sINodeBooleanChunkEnableHandle, &psINodeEnumEntryChunkSelectorArray[nIndex], &sINodeMapRemoteHandle, &pINodeChunkArray[nValidChunkCount]);
                if (pINodeChunkArray[nValidChunkCount].Handle)
                {
                    ++nValidChunkCount;
                }
            }
        }

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
                
                /* Display the Chunk data. */
                DisplayNodeValues(psApiFunctions, pINodeChunkArray, nValidChunkCount);

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
