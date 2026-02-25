/*!
\file Graph.cpp
\brief 
 
 This sample shows how to use the callback functions to draw on top of the acquired image.
 The following points will be demonstrated in this sample code:
 - Initialize StApi
 - Connect to camera
 - Acquire image data via callback function
 - Use callback function to draw on top of the acquired image.
 - Retrieving graph data with the Filter function.
 - Displaying graph data with the GUI function.
 For more information, please refer to the help document of StApi.

*/

// Include files for using StApi.
#include <StApi_TL.h>
#include <StApi_GUI.h>
#include <iomanip>    //std::setprecision

#include "kbhit.h"

//Namespace for using StApi.
using namespace StApi;

//Namespace for using cout
using namespace std;

//#define DRAW_AS_CHILD
//#define USE_REGISTERED_IMAGE

#include <stdlib.h>

typedef struct
{
	IStGraphDisplayWnd *pIStGraphDisplayWnd;
	IStGraphDataFilter *pIStGraphDataFilter;
}ImageDisplayCallbackParam_t, *PImageDisplayCallbackParam_t;

typedef struct
{
	IStImageDisplayWnd *pIStImageDisplayWnd;
}GrabCallbackParam_t, *PGrabCallbackParam_t;


typedef ImageDisplayCallbackParam_t*	UserParamImageDisplay_t;
typedef GrabCallbackParam_t* UserParamGrab_t;

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void OnGrab(IStCallbackParamBase *pIStCallbackParamBase, UserParamGrab_t pCallbackParam)
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
                // This will have a copy of the image data and original buffer can be released if necessary and original buffer can be released if necessary.
                pCallbackParam->pIStImageDisplayWnd->RegisterIStImage(pIStImage);
            }
            else
            {
                // If the acquired data contains no image data
                cout << "Image data does not exist" << endl;
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
//
//-----------------------------------------------------------------------------
void OnImageDisplay(IStCallbackParamBase *pIStCallbackParamBase, UserParamImageDisplay_t pCallbackParam)
{
    if (pIStCallbackParamBase->GetCallbackType() == StCallbackType_StApiGUIEvent_DisplayImageWndDrawing)
    {

        StApi::IStCallbackParamStApiGUIEventDrawing *pIStCallbackParamStApiGUIEventDrawing = dynamic_cast<StApi::IStCallbackParamStApiGUIEventDrawing*>(pIStCallbackParamBase);

#ifdef DRAW_AS_CHILD
        HDC hDC = 
#endif
        	pIStCallbackParamStApiGUIEventDrawing->GetDC();
        

        IStImageDisplayWnd *pIStImageDisplayWnd = dynamic_cast<IStImageDisplayWnd*>(pIStCallbackParamStApiGUIEventDrawing->GetIStWnd());

#ifdef USE_REGISTERED_IMAGE
        StApi::IStImage *pIStImage = pIStImageDisplayWnd->GetRegisteredIStImage();
#else
        StApi::IStImage *pIStImage = pIStImageDisplayWnd->GetConvertedIStImage();
#endif
        IStGraphDataFilter *pIStGraphDataFilter = pCallbackParam->pIStGraphDataFilter;
        pIStGraphDataFilter->Filter(pIStImage);
        const IStGraphDataBufferList *pIStGraphDataBufferList(pIStGraphDataFilter->GetIStGraphDataBufferList());

        pCallbackParam->pIStGraphDisplayWnd->RegisterIStGraphDataBufferList(pIStGraphDataBufferList);

#ifdef DRAW_AS_CHILD
        pCallbackParam->pIStGraphDisplayWnd->Draw(hDC, 400, 250);
#endif

    }
}


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

		// Create an graph display window object for showing graph.
		CIStGraphDisplayWndPtr pIStGraphDisplayWnd(CreateIStWnd(StWindowType_GraphDisplay));

		// Create a filter object to compute the graph data.
		CIStGraphDataFilterPtr pIStGraphDataFilter(StApi::CreateIStFilter(StApi::StFilterType_GraphData));

		// Create an image display window object for showing image.
		CIStImageDisplayWndPtr pIStImageDisplayWnd(CreateIStWnd(StWindowType_ImageDisplay));

		// Create an NodeMap display window object.
		CIStNodeMapDisplayWndPtr pIStNodeMapDisplayWnd(CreateIStWnd(StWindowType_NodeMapDisplay));

        GenICam::gcstring strNodeName("Root");
		pIStNodeMapDisplayWnd->RegisterINode(pIStGraphDataFilter->GetINodeMap()->GetNode(strNodeName), "Graph data filter");
		pIStNodeMapDisplayWnd->RegisterINode(pIStGraphDisplayWnd->GetINodeMap()->GetNode(strNodeName), "Graph display window");
		pIStNodeMapDisplayWnd->RegisterINode(pIStImageDisplayWnd->GetINodeMap()->GetNode(strNodeName), "Image display window");
		pIStNodeMapDisplayWnd->RegisterINode(pIStDevice->GetRemoteIStPort()->GetINodeMap()->GetNode(strNodeName), "RemoteDevice");
        pIStNodeMapDisplayWnd->Show(NULL, StWindowMode_ModalessOnNewThread);

        ImageDisplayCallbackParam_t sCallbackParam = { pIStGraphDisplayWnd, pIStGraphDataFilter };
        pIStImageDisplayWnd->GetIStPixelFormatConverter()->SetBayerInterpolationMethod(StBayerInterpolationMethod_BiLinear2);

        // Register a callback function. When an event occurs for ImageDisplayWnd, function registered is called.
        RegisterCallback(pIStImageDisplayWnd, &OnImageDisplay, &sCallbackParam);

        // Create a DataStream object for handling image stream data.
        CIStDataStreamPtr pIStDataStream(pIStDevice->CreateIStDataStream(0));

        GrabCallbackParam_t sGrabCallbackParam = { pIStImageDisplayWnd };
        RegisterCallback(pIStDataStream, &OnGrab, &sGrabCallbackParam);

        // Start the image acquisition of the host side.
        pIStDataStream->StartAcquisition();

        // Start the image acquisition of the camera side.
        pIStDevice->AcquisitionStart();

        // Keep getting image until Enter key pressed.
        cout << endl << "Press any key to exit." << endl;
        for (;;)
        {
            if (_kbhit()) break;
            // Check if display window is visible.
            if (!pIStImageDisplayWnd->IsVisible())
            {
                pIStImageDisplayWnd->Show(NULL, StWindowMode_Modaless);
            }
#ifndef DRAW_AS_CHILD
            if (!pIStGraphDisplayWnd->IsVisible())
            {
                pIStGraphDisplayWnd->Show(NULL, StWindowMode_ModalessOnNewThread);
            }
#endif
 
            processEventGUI();
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

    return(0);
}
