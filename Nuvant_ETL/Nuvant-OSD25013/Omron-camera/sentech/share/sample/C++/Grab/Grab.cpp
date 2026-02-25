/*!
\file Grab.cpp
\brief 

 This sample shows the basic operation of using StApi for connecting, controlling, and acquiring image from camera.
 The following points will be demonstrated in this sample code:
 - Initialize StApi
 - Connect to camera
 - Acquire image data (with waiting in main thread)
 This sample also shows the usage of automatic lifetime management class. 
 Note if you do not use the class with auto lifetime management, you will need to release the class object by yourself.

 If you want to acquire image by using callback functions, please refer to "GrabCallback" sample for more information.
 For more information, please refer to the help document of StApi.

*/

// If you want to use the GUI features, please refer to Grab-GUI.cpp

// Include files for using StApi.
#include <StApi_TL.h>

//Namespace for using StApi.
using namespace StApi;

//Namespace for using cout
using namespace std;

// Counts of images to grab.
const uint64_t nCountOfImagesToGrab = 100;

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

        // Create a DataStream object for handling image stream data.
        // We use CIStDataStreamPtr instead of IStDataStreamReleasable for automatically managing the IStDataStreamReleasable class with auto initial/deinitial.
        CIStDataStreamPtr pIStDataStream(pIStDevice->CreateIStDataStream(0));

        // Start the image acquisition of the host (local machine) side.
        pIStDataStream->StartAcquisition(nCountOfImagesToGrab);

        // Start the image acquisition of the camera side.
        pIStDevice->AcquisitionStart();

        // A while loop for acquiring data and checking status. 
        // Here, the acquisition runs until it reaches the assigned numbers of frames.
        while (pIStDataStream->IsGrabbing())
        {
            // Retrieve the buffer pointer of image data with a timeout of 5000ms.
            // Use CIStStreamBufferPtr for automatically managing the buffer re-queue action when it's no longer needed.
            CIStStreamBufferPtr pIStStreamBuffer(pIStDataStream->RetrieveBuffer(5000));

            // Check if the acquired data contains image data.
            if (pIStStreamBuffer->GetIStStreamBufferInfo()->IsImagePresent())
            {
                // If yes, we create a IStImage object for further image handling.
                IStImage *pIStImage = pIStStreamBuffer->GetIStImage();

                // Display the information of the acquired image data.
                cout << "BlockId=" << pIStStreamBuffer->GetIStStreamBufferInfo()->GetFrameID()
                    << " Size:" << pIStImage->GetImageWidth() << " x " << pIStImage->GetImageHeight()
                    << " First byte =" << (uint32_t)*(uint8_t*)pIStImage->GetImageBuffer() << endl;
            }
            else
            {
                // If the acquired data contains no image data.
                cout << "Image data does not exist" << endl;
            }
        }

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
