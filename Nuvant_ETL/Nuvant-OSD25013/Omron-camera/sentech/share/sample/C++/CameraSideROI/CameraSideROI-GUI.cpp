/*!
\file CameraSideROI-GUI.cpp
\brief 

 This sample shows how to set ROI in camera side and handle the image data.
 The following points will be demonstrated in this sample code:
 - Initialize StApi
 - Connect to camera
 - Set image ROI parameter 
 - Acquire image data (with waiting in main thread)
 - Process the acquired ROI images 

 For more information, please refer to the help document of StApi.
*/


// Include files for using StApi.
#include <StApi_TL.h>
#include <StApi_GUI.h>

#include <iomanip>    //std::setprecision
#include <thread>

// Namespace for using StApi.
using namespace StApi;

// Namespace for using cout and thread
using namespace std;

// Namespace for using GenApi.
using namespace GenApi;

// Counts of images to be grabbed.
const uint64_t nCountOfImagesToGrab = 100;

//Feature names
const char * PIXEL_FORMAT = "PixelFormat";            //Standard
const char * REGION_SELECTOR = "RegionSelector";    //Standard
const char * REGION_MODE = "RegionMode";            //Standard
const char * OFFSET_X = "OffsetX";                    //Standard
const char * OFFSET_Y = "OffsetY";                    //Standard
const char * WIDTH = "Width";                        //Standard
const char * HEIGHT = "Height";                        //Standard


void acquisitionWorker(CIStDevicePtr *pIStDevice, CIStDataStreamPtr *pIStDataStream, CIStImageDisplayWndPtr *pIStImageDisplayWnd, bool *isCompleted)
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
            // If yes, we create a IStImage object for further image handling.
            IStImage *pIStImage = pIStStreamBuffer->GetIStImage();

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
        }
        else
        {
            // If the acquired data contains no image data
            cout << "Image data does not exist" << endl;
        }
    }
    *isCompleted = true;

}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
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

        // Create a display window here.
        CIStImageDisplayWndPtr pIStImageDisplayWnd(CreateIStWnd(StWindowType_ImageDisplay));

        // Create a DataStream object for handling image stream data.
        CIStDataStreamPtr pIStDataStream(pIStDevice->CreateIStDataStream(0));

        // Create INodeMap object to access current setting of the camera.
        CNodeMapPtr pINodeMapRemote(pIStDevice->GetRemoteIStPort()->GetINodeMap());

        // Create a node map display window object, to get the IStWndReleasable interface pointer.
        // After the window object is no longer needed, call the IStWndReleasable::Release() to discard the window object.
        // (In the destructor of CIStNodeMapDisplayWndPtr, IStWndReleasable::Release() is automatically called.)
        CIStNodeMapDisplayWndPtr pIStNodeMapDisplayWnd(CreateIStWnd(StWindowType_NodeMapDisplay));

        pIStNodeMapDisplayWnd->RegisterINode(pINodeMapRemote->GetNode(PIXEL_FORMAT), "CameraSideROI");
        pIStNodeMapDisplayWnd->RegisterINode(pINodeMapRemote->GetNode(REGION_SELECTOR), "CameraSideROI");
        pIStNodeMapDisplayWnd->RegisterINode(pINodeMapRemote->GetNode(REGION_MODE), "CameraSideROI");
        pIStNodeMapDisplayWnd->RegisterINode(pINodeMapRemote->GetNode(OFFSET_X), "CameraSideROI");
        pIStNodeMapDisplayWnd->RegisterINode(pINodeMapRemote->GetNode(OFFSET_Y), "CameraSideROI");
        pIStNodeMapDisplayWnd->RegisterINode(pINodeMapRemote->GetNode(WIDTH), "CameraSideROI");
        pIStNodeMapDisplayWnd->RegisterINode(pINodeMapRemote->GetNode(HEIGHT), "CameraSideROI");
        pIStNodeMapDisplayWnd->Show(NULL, StWindowMode_Modal);
        
        // Start the image acquisition of the host side.
        pIStDataStream->StartAcquisition(nCountOfImagesToGrab);

        // Start the image acquisition of the camera side.
        pIStDevice->AcquisitionStart();
        
        // Initialize thread for image acquisition
        bool isCompleted = false;
        thread worker(acquisitionWorker, &pIStDevice, &pIStDataStream, &pIStImageDisplayWnd, &isCompleted);
        
        // Process the GUI event while waiting for thread completion
        while(!isCompleted) 
        {
            // Check if display window is visible.
            if (!pIStImageDisplayWnd->IsVisible())
            {
                // Create a new thread to display the window.
                pIStImageDisplayWnd->Show(NULL, StWindowMode_Modaless);
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
