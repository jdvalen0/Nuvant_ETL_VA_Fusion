/*!
\file FeatureList-GUI.cpp
\brief 
 
 This sample will list all support functions of connected camera.
 The following points will be demonstrated in this sample code:
 - Initialize StApi
 - Connect to camera
 - Access Nodes of NodeMap for displaying camera's features

 For more information, please refer to the help document of StApi.

*/
// Include files for using StApi.
#include <StApi_TL.h>
#include <StApi_GUI.h>
#include <iomanip>    //std::setprecision

//Namespace for using StApi.
using namespace StApi;

//Namespace for using GenApi.
using namespace GenApi;

//Namespace for using cout
using namespace std;


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void DisplayNodes(CNodePtr pINode)
{
    // Create an NodeMap display window object.
    CIStNodeMapDisplayWndPtr pIStNodeMapDisplayWnd(CreateIStWnd(StWindowType_NodeMapDisplay));

    // Register the node to NodeMap window.
    pIStNodeMapDisplayWnd->RegisterINode(pINode, "Root");

    // Set the position and size of the window.
    pIStNodeMapDisplayWnd->SetPosition(0, 0, 480, 640);

    // Display the window.
    pIStNodeMapDisplayWnd->Show(NULL, StWindowMode_Modal);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
int main(int, char**)
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

        // Display nodes.
        DisplayNodes(pIStDevice->GetRemoteIStPort()->GetINodeMap()->GetNode("Root"));
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
