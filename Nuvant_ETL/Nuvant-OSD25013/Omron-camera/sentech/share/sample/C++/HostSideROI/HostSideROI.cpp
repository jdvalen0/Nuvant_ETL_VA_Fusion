/*!
\file HostSideROI.cpp
\brief

 This sample shows how to divide image data into multiple ROI images in local side and display them.
 The following points will be demonstrated in this sample code:
 - Initialize StApi
 - Connect to camera
 - Acquire image data (with waiting in main thread)
 - Process image ROI in host side (local computer)
 
 For more information, please refer to the help document of StApi.

*/


// Include files for using StApi
#include <StApi_TL.h>
#include <StApi_GUI.h>
#include <iomanip>    //std::setprecision
#include <thread>

//Namespace for using StApi.
using namespace StApi;

//Namespace for using cout and thread
using namespace std;

//Namespace for using GenApi.
using namespace GenApi;

// Count of images to be grabbed.
const uint64_t nCountOfImagesToGrab = 2000;

// Count of regions of each direction.
const size_t nHorizontalRoiCount = 4;
const size_t nVerticalRoiCount = 2;
const size_t pnROIWindowCount[] = { nHorizontalRoiCount, nVerticalRoiCount };

void acquisitionWorker(CIStDevicePtr *pIStDevice, CIStDataStreamPtr *pIStDataStream, CIStImageDisplayWndPtr *pIStImageDisplayWnd, CIStImageDisplayWndPtrArray *pIStWndList, int32_t pnROIImageSize[], bool *isCompleted)
{
    // A while loop for acquiring data and checking status. 
    // Here, the acquisition runs until it reaches the assigned numbers of frames.
    while ((*pIStDataStream)->IsGrabbing())
    {
        // Retrieve the buffer pointer of image data with a timeout of 5000ms.
        CIStStreamBufferPtr pIStStreamBuffer((*pIStDataStream)->RetrieveBuffer(5000));
        
        // Check if the acquired data contains image data.
        if (pIStStreamBuffer->GetIStStreamBufferInfo()->IsImagePresent())
        {
            // If yes, get the IStImage interface pointer to the acquired image data for further operation.
            IStImage *pIStImage = pIStStreamBuffer->GetIStImage();

            // Set the position and size of the window.
            (*pIStImageDisplayWnd)->SetPosition(0, 0, pIStImage->GetImageWidth(), pIStImage->GetImageHeight());

            // Acquire detail information of received image and display it onto the status bar of the display window.
            stringstream ss;
            ss << (*pIStDevice)->GetIStDeviceInfo()->GetDisplayName();
            ss << "  ";
            ss << pIStImage->GetImageWidth() << " x " << pIStImage->GetImageHeight();
            ss << "  ";
            ss << fixed << std::setprecision(2) << (*pIStDataStream)->GetCurrentFPS();
            ss << "[fps]";
            GenICam::gcstring strText(ss.str().c_str());
            (*pIStImageDisplayWnd)->SetUserStatusBarText(strText);

            // Register the image to be displayed.
            // This will have a copy of the image data and original buffer can be released if necessary and original buffer can be released if necessary.
            (*pIStImageDisplayWnd)->RegisterIStImage(pIStImage);

            // Display each ROI image in different window.
            size_t nIndex = 0;
            for (size_t y = 0; y < pnROIWindowCount[1]; y++)
            {
                for (size_t x = 0; x < pnROIWindowCount[0]; x++)
                {
                    // Get the ROI image with IStImage object.
                    IStImage *pIStImageROI = pIStImage->GetROIImage(x * pnROIImageSize[0], y * pnROIImageSize[1], pnROIImageSize[0], pnROIImageSize[1]);

                    IStImageDisplayWnd *pIStImageROIDisplayWnd = NULL;
                    pIStImageROIDisplayWnd = (*pIStWndList)[nIndex];
                    pIStImageROIDisplayWnd->SetPosition(x * pnROIImageSize[0], y * pnROIImageSize[1], pnROIImageSize[0], pnROIImageSize[1]);

                    // Register the image to be displayed.
                    // This will have a copy of the image data and original buffer can be released if necessary and original buffer can be released if necessary.
                    pIStImageROIDisplayWnd->RegisterIStImage(pIStImageROI);

                    ++nIndex;
                }
            }
        }
        else
        {
            // If the acquired data contains no image data
            cout << "Image data does not exist" << endl;
        }
    }
    *isCompleted = true;
}

int main(int, char **)
{
    try
    {
        // Initialize StApi before using.
        CStApiAutoInit objStApiAutoInit;

        // Create a system object for device scan and connection.
        CIStSystemPtr pIStSystem(CreateIStSystem());

        // Create a camera device object and connect to first detected device.
        CIStDevicePtr pIStDevice(pIStSystem->CreateFirstIStDevice());

        // Displays the DisplayName of the device.
        cout << "Device=" << pIStDevice->GetIStDeviceInfo()->GetDisplayName() << endl;

        // Create DisplayImageWindow (For display whole Image)
        CIStImageDisplayWndPtr pIStImageDisplayWnd(CreateIStWnd(StWindowType_ImageDisplay));

        // Create DisplayImageWindows (For display ROI Images)
        CIStImageDisplayWndPtrArray pIStWndList;

        // Create a DataStream object for handling image stream data..
        CIStDataStreamPtr pIStDataStream(pIStDevice->CreateIStDataStream(0));

        // Create INodeMap object to access current setting of the camera.
        CNodeMapPtr pINodeMapRemote(pIStDevice->GetRemoteIStPort()->GetINodeMap());

        // Get current setting of the image size.
        CIntegerPtr pIIntegerWidth(pINodeMapRemote->GetNode("Width"));
        CIntegerPtr pIIntegerHeight(pINodeMapRemote->GetNode("Height"));
        const int32_t pnImageSize[] = {
            (int32_t)pIIntegerWidth->GetValue(),
            (int32_t)pIIntegerHeight->GetValue()
        };

        // Get current pixel format information.
        EStPixelFormatNamingConvention_t nPFNC = (EStPixelFormatNamingConvention_t)dynamic_cast<IEnumeration*>(pINodeMapRemote->GetNode("PixelFormat"))->GetIntValue();
        IStPixelFormatInfo *pIStPixelFormatInfo = GetIStPixelFormatInfo(nPFNC);

        // Get the minimum setting unit of both sides (X and Y).
        const size_t pnPixelIncrement[] = { pIStPixelFormatInfo->GetPixelIncrementX(), pIStPixelFormatInfo->GetPixelIncrementY() };

        // Calculate the size of the ROI.
        int32_t pnROIImageSize[2];
        for(size_t i = 0; i < 2; i++)
        {
            int32_t nSize = pnImageSize[i] / pnROIWindowCount[i];
            nSize -= nSize % pnPixelIncrement[i];
            pnROIImageSize[i] = nSize;
        }

        // Create Windows
        for (size_t y = 0; y < pnROIWindowCount[1]; y++)
        {
            for (size_t x = 0; x < pnROIWindowCount[0]; x++)
            {
                // Create an image display window object, to get the IStWndReleasable interface pointer.
                pIStWndList.Register(CreateIStWnd(StWindowType_ImageDisplay));
            }
        }
        
        // Start the image acquisition of the host side.
        pIStDataStream->StartAcquisition(nCountOfImagesToGrab);

        // Start the image acquisition of the camera side.
        pIStDevice->AcquisitionStart();
        
        // Initialize thread for image acquisition
        bool isCompleted = false;
        thread worker(acquisitionWorker, &pIStDevice, &pIStDataStream, &pIStImageDisplayWnd, &pIStWndList, pnROIImageSize, &isCompleted);

        // Process the GUI event while waiting for thread completion
        while(!isCompleted) 
        {
            // Check if the image display window is visible.
            if (!pIStImageDisplayWnd->IsVisible())
            {
                // Display the window.
                pIStImageDisplayWnd->Show(NULL, StWindowMode_Modaless);
            }

            //Check visibility of ROI window here.
            size_t nIndex = 0;
            for (size_t y = 0; y < pnROIWindowCount[1]; y++)
            {
                for (size_t x = 0; x < pnROIWindowCount[0]; x++)
                {
                    IStImageDisplayWnd *pIStImageROIDisplayWnd = pIStWndList[nIndex];
                    nIndex++;
                    // Check if the image display window is visible.
                    if (!pIStImageROIDisplayWnd->IsVisible())
                    {
                        // Display the window.
                        pIStImageROIDisplayWnd->Show(NULL, StWindowMode_Modaless);
                    }
                }
            }
            processEventGUI();
        }
        if (worker.joinable()) worker.join();
        
        // Stop the image acquisition of the camera side.
        pIStDevice->AcquisitionStop();

        // Stop the image acquisition of the host side.
        pIStDataStream->StopAcquisition();
    }
    catch (const GenICam::GenericException &e)
    {
        // Display a description of the error.
        cerr << endl << "An exception occurred." << endl << e.GetDescription() << endl;
    }

    // Wait until the Enter key is pressed.
    cout << endl << "Press Enter to exit." << endl;
    while (cin.get() != '\n');

    return(0);
}
