/*!
\file MultipleSystems-GUI.cpp
\brief 

  This sample shows how to use multiple GenTL modules (cti files) for acquiring image data.
  The following points will be demonstrated in this sample code:
  - Initialize StApi
  - Connect to the first detected camera of all system
  - Acquire image data (with waiting in main thread) 
  - Use multiple GenTL module.

  For more information, please refer to the help document of StApi.
  
*/

// Include files for using StApi.
#include <StApi_TL.h>
#include <StApi_GUI.h>
#include <iomanip>    //for setprecision
#include <thread>

//Namespace for using StApi.
using namespace StApi;

//Namespace for using cout
using namespace std;

// Count of images to be grabbed.
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

        // Create a system object list for store system object.
        // Then we try to create objects of all available systems.
        CIStSystemPtrArray pIStSystemList;
        for (EStSystemVendor_t eSystemVendor = StSystemVendor_Default; eSystemVendor < StSystemVendor_Count; eSystemVendor = (EStSystemVendor_t)(eSystemVendor + 1))
        {
            try
            {
                // For each available system, try to create object for it then register it into system list for further usage.
                pIStSystemList.Register(CreateIStSystem(eSystemVendor, StInterfaceType_All));
            }
            catch (const GenICam::GenericException &e)
            {
                // Display a description of error if any happens.
                cerr << "An exception occurred." << endl << e.GetDescription() << endl;
            }
        }

        // Create a device object of the first detected device to connect.
        CIStDevicePtr pIStDevice(pIStSystemList.CreateFirstIStDevice(GenTL::DEVICE_ACCESS_EXCLUSIVE));

        // Displays the DisplayName of the device.
        cout << "Device=" << pIStDevice->GetIStDeviceInfo()->GetDisplayName() << endl;
        
        // If using GUI for display, create a display window here.
        CIStImageDisplayWndPtr pIStImageDisplayWnd(CreateIStWnd(StWindowType_ImageDisplay));

        // Create a DataStream object for handling image stream data.
        CIStDataStreamPtr pIStDataStream(pIStDevice->CreateIStDataStream(0));

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
        // Display a description of the error.
        cerr << endl << "An exception occurred." << endl << e.GetDescription() << endl;
    }

    // Wait until the Enter key is pressed.
    cout << endl << "Press Enter to exit." << endl;
    while (cin.get() != '\n');

    return(0);
}
