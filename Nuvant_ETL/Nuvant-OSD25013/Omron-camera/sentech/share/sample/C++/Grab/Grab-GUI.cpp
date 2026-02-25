/*!
\file Grab.cpp
\brief 

 This sample shows the basic operation of using StApi for connecting, controlling, and acquiring image from camera.
 The following points will be demonstrated in this sample code:
 - Initialize StApi
 - Connect to camera
 - Acquire image data (with waiting in main thread)
 - Preview window GUI
 This sample also shows the usage of automatic lifetime management class. 
 Note if you do not use the class with auto lifetime management, you will need to release the class object by yourself.

 If you want to acquire image by using callback functions, please reference "GrabCallback" sample for more information.
 For more information, please refer to the help document of StApi.

*/

// Include files for using StApi.
#include <StApi_TL.h>
#include <StApi_GUI.h>

#include <iomanip>    //std::setprecision
#include <thread>

//Namespace for using StApi.
using namespace StApi;

//Namespace for using cout and thread
using namespace std;

// Counts of images to grab.
const uint64_t nCountOfImagesToGrab = 100;

void acquisitionWorker(CIStDevicePtr *pIStDevice, CIStDataStreamPtr *pIStDataStream, CIStImageDisplayWndPtr *pIStImageDisplayWnd, bool *isCompleted)
{
    // A while loop for acquiring data and checking status. 
    // Here, the acquisition runs until it reaches the assigned numbers of frames.
    while ((*pIStDataStream)->IsGrabbing())
    {
        // Retrieve the buffer pointer of image data with a timeout of 5000ms.
        // Use CIStStreamBufferPtr for automatically managing the buffer re-queue action when it's no longer needed.
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
            // If the acquired data contains no image data...
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
        // Here we use CIStSystemPtr instead of IStSystemReleasable for automatically managing the IStSystemReleasable class with auto initial/deinitial.
        CIStSystemPtr pIStSystem(CreateIStSystem());

        // Create a camera device object and connect to first detected device by using the function of system object.
        // We use CIStDevicePtr instead of IStDeviceReleasable for automatically managing the IStDeviceReleasable class with auto initial/deinitial.
        CIStDevicePtr pIStDevice(pIStSystem->CreateFirstIStDevice());

        // Displays the DisplayName of the device.
        cout << "Device=" << pIStDevice->GetIStDeviceInfo()->GetDisplayName() << endl;

        // If using GUI for display, create a display window here.
        CIStImageDisplayWndPtr pIStImageDisplayWnd(CreateIStWnd(StWindowType_ImageDisplay));

        // Create a DataStream object for handling image stream data.
        // We use CIStDataStreamPtr instead of IStDataStreamReleasable for automatically managing the IStDataStreamReleasable class with auto initial/deinitial.
        CIStDataStreamPtr pIStDataStream(pIStDevice->CreateIStDataStream(0));

        // Start the image acquisition of the host (local machine) side.
        pIStDataStream->StartAcquisition(nCountOfImagesToGrab);

        // Start the image acquisition of the camera side.
        pIStDevice->AcquisitionStart();

        // Initialize thread for image acquisition
        bool isCompleted = false;
        thread worker(acquisitionWorker, &pIStDevice, &pIStDataStream, &pIStImageDisplayWnd, &isCompleted);

        // process the GUI event while waiting for thread completion
        while(!isCompleted)
        {
            // Check if display window is visible.
            if (!pIStImageDisplayWnd->IsVisible())
            {
                // Display the window.
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
        // If any exception occurred, display the description of the error here.
        cerr << endl << "An exception occurred." << endl << e.GetDescription() << endl;
    }

    // Wait until the Enter key is pressed to end program.
    cout << endl << "Press Enter to exit." << endl;
    while (cin.get() != '\n');

    return(0);
}
