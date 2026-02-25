/*!
\file SingleConverter.cpp
\brief

This sample shows how to process received image with filter.
The following points will be demonstrated in this sample code:
- Initialize StApi
- Connect to camera
- Acquire image data (with waiting in main thread)
- Apply image processing with converter

For more information, please refer to the help document of StApi.

*/

// If you want to use the GUI features, please refer to Grab-GUI.cpp

// Include files for using StApi.
#include <StApi_TL.h>
#include <StApi_IP.h>

// Namespace for using StApi.
using namespace StApi;

// Namespace for using cout
using namespace std;

// Count of images to be grabbed.
const uint64_t nCountOfImagesToGrab = 5000;

//const EStConverterType_t eTargetConverter = StConverterType_PixelFormat;
const EStConverterType_t eTargetConverter = StConverterType_Reverse;

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
int main(int /* argc */, char ** /* argv */)
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

		// Create a converter object.
		CIStConverterPtr pIStConverter(CreateIStConverter(eTargetConverter));

		CIStImageBufferPtr pIStImageConverted(CreateIStImageBuffer());

		// Create a DataStream object for handling image stream data.
		CIStDataStreamPtr pIStDataStream(pIStDevice->CreateIStDataStream(0));

		// Start the image acquisition of the host side.
		pIStDataStream->StartAcquisition(nCountOfImagesToGrab);

		// Start the image acquisition of the camera side.
		pIStDevice->AcquisitionStart();

		// A while loop for acquiring data and checking status. 
		// Here, the acquisition runs until it reaches the assigned numbers of frames.
		while (pIStDataStream->IsGrabbing())
		{
			// Retrieve the buffer pointer of image data with a timeout of 5000ms.
			CIStStreamBufferPtr pIStStreamBuffer(pIStDataStream->RetrieveBuffer(5000));

			// Check if the acquired data contains image data.
			if (pIStStreamBuffer->GetIStStreamBufferInfo()->IsImagePresent())
			{
				// If yes, we create a IStImage object for further image handling.
				IStImage *pIStImage = pIStStreamBuffer->GetIStImage();

				// Convert the acquired image.
				pIStConverter->Convert(pIStImage, pIStImageConverted);

				// Display the information of the acquired image data.
				cout << "BlockId=" << pIStStreamBuffer->GetIStStreamBufferInfo()->GetFrameID()
					<< " Size:" << pIStImageConverted->GetIStImage()->GetImageWidth() << " x " << pIStImageConverted->GetIStImage()->GetImageHeight()
					<< " First byte =" << (uint32_t)*(uint8_t*)pIStImageConverted->GetIStImage()->GetImageBuffer() << endl;
			}
			else
			{
				// If the acquired data contains no image data
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
		// Display a description of the error.
		cerr << endl << "An exception occurred." << endl << e.GetDescription() << endl;
	}

	// Wait until the Enter key is pressed.
	cout << endl << "Press Enter to exit." << endl;
	while (cin.get() != '\n');

	return(0);
}
