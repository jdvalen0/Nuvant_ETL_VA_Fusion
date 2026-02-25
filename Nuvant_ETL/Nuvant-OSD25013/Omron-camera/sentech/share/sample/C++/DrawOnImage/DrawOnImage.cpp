/*!
\file DrawOnImage.cpp
\brief

This sample shows the way of using drawing function.
The following points will be demonstrated in this sample code:
- Initialize StApi
- Connect to camera
- Register and use callback function with StApi
- Acquire image data via callback function
- Drawing on a preview image.
You will need to acquire the callback type for further handling. The parameter of each type of callback will have different parameter.
Please check OnCallback() function for the example of how to check the type of the callback.

For more information, please refer to the help document of StApi.

*/

// Include files for using StApi.
#include <StApi_TL.h>
#include <StApi_GUI.h>

#include "kbhit.h"

//Namespace for using StApi.
using namespace StApi;

//Namespace for using cout
using namespace std;

typedef IStImageDisplayWnd* UserParam_t;

//-----------------------------------------------------------------------------
// Function for handling callback action
//-----------------------------------------------------------------------------
void OnCallback(IStCallbackParamBase *pIStCallbackParamBase, UserParam_t pvContext)
{
	// Check callback type. Only NewBuffer event is handled in here
	if (pIStCallbackParamBase->GetCallbackType() == StCallbackType_GenTLEvent_DataStreamNewBuffer)
	{
		// In case of receiving a NewBuffer events:
		// Convert received callback parameter into IStCallbackParamGenTLEventNewBuffer for acquiring additional information.
		IStCallbackParamGenTLEventNewBuffer *pIStCallbackParamGenTLEventNewBuffer = dynamic_cast<IStCallbackParamGenTLEventNewBuffer*>(pIStCallbackParamBase);

		try
		{
			// Get the IStDataStream interface pointer from the received callback parameter.
			IStDataStream *pIStDataStream = pIStCallbackParamGenTLEventNewBuffer->GetIStDataStream();

			// Retrieve the buffer pointer of image data for that callback indicated there is a buffer received.
			CIStStreamBufferPtr pIStStreamBuffer(pIStDataStream->RetrieveBuffer(0));

			// Check if the acquired data contains image data.
			if (pIStStreamBuffer->GetIStStreamBufferInfo()->IsImagePresent())
			{

				// If yes, we create a IStImage object for further image handling.
				IStImage *pIStImage = pIStStreamBuffer->GetIStImage();

				// Register the image to be displayed.
				// This will have a copy of the image data and original buffer can be released if necessary.
				pvContext->RegisterIStImage(pIStImage);
			}
			else
			{
				// If the acquired data contains no image data...
				cout << "Image data does not exist." << endl;
			}
		}
		catch (const GenICam::GenericException &e)
		{
			// If any exception occurred, display the description of the error here.
			cerr << endl << "An exception occurred." << endl << e.GetDescription() << endl;
		}
	}
}

//-----------------------------------------------------------------------------
// Callback function for registering
//-----------------------------------------------------------------------------
void OnStCallbackCFunction(IStCallbackParamBase *pIStCallbackParamBase, UserParam_t pvContext)
{
	OnCallback(pIStCallbackParamBase, pvContext);
}

//-----------------------------------------------------------------------------
// Main thread
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

		// Create a display window.
		CIStImageDisplayWndPtr pIStImageDisplayWnd(CreateIStWnd(StWindowType_ImageDisplay));

        // Enables the ability to draw on the image.
        // This line is the only essential difference from the sample program "GrabCallback".
		pIStImageDisplayWnd->SetBuiltInDrawingToolbar(true);

		// Create a DataStream object for handling image stream data.
		CIStDataStreamPtr pIStDataStream(pIStDevice->CreateIStDataStream(0));

		// Register callback function. Note that by different usage, we pass different kinds/numbers of parameters in.
		RegisterCallback(pIStDataStream, &OnStCallbackCFunction, (UserParam_t)pIStImageDisplayWnd);

		// Start the image acquisition of the host (local machine) side.
		pIStDataStream->StartAcquisition();

		// Start the image acquisition of the camera side.
		pIStDevice->AcquisitionStart();

		// Keep getting image until any key is pressed.
        cout << endl << "Press any key to exit." << endl;
        for (;;)
        {
            if (_kbhit()) break;
            // Check if display window is visible.
            if (!pIStImageDisplayWnd->IsVisible())
            {
                pIStImageDisplayWnd->Show(NULL, StWindowMode_Modaless);
            }
            processEventGUI();
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

	return(0);
}
