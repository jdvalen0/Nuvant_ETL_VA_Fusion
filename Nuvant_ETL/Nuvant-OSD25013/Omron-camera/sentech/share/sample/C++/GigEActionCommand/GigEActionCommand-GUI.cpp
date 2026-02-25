/*!
\file GigEActionCommand-GUI.cpp
\brief 
 
 This sample shows how to use GigE Action command.
 The following points will be demonstrated in this sample code:
 - Initialize StApi
 - Connect to GigE camera
 - Set and send action command

 For more information, please refer to the help document of StApi.
 
*/

// Include files for using StApi.
#include <StApi_TL.h>
#include <StApi_GUI.h>
#include "kbhit.h" //helper function to detect key pressed

//Namespace for using StApi.
using namespace StApi;

//Namespace for using GenApi.
using namespace GenApi;

//Namespace for using cout
using namespace std;

const uint32_t nDeviceKey = 0x12345678;
const uint32_t nGroupKey = 0x00000001;
const uint32_t nGroupMask = 0xFFFFFFFF;
const bool bScheduledTimeEnable = false;
uint64_t nScheduledTime = 0;

//-----------------------------------------------------------------------------
//Adjust GevSCPD (Only for same configuration cameras.)
//-----------------------------------------------------------------------------
void AdjustGevSCPD(CIStDevicePtrArray &pIStDeviceList)
{
	//Get packet size.
	CIntegerPtr pIIntegerGevSCPSPacketSize(pIStDeviceList[0]->GetRemoteIStPort()->GetINodeMap()->GetNode("GevSCPSPacketSize"));
	if (!pIIntegerGevSCPSPacketSize.IsValid()) return;

	CIntegerPtr pIIntegerTimestampLatchValue(pIStDeviceList[0]->GetRemoteIStPort()->GetINodeMap()->GetNode("TimestampLatchValue"));
	if (!pIIntegerTimestampLatchValue.IsValid()) return;

	const int64_t nPacketSize(pIIntegerGevSCPSPacketSize->GetValue());

	size_t nCount = pIStDeviceList.GetSize();
	const int64_t nMaxBps = 100000000;	//800Mbps
	const int64_t nEachPacketTimeNs = nPacketSize * 1000000000 * (nCount - 1) / nMaxBps;
	int64_t nTimestampUnit = pIIntegerTimestampLatchValue->GetInc();
	if (nTimestampUnit == 0)
	{
		nTimestampUnit = 40;
	}

	for (size_t i = 0; i < nCount; ++i)
	{
		CIntegerPtr pIntegerGevSCPD(pIStDeviceList[i]->GetRemoteIStPort()->GetINodeMap()->GetNode("GevSCPD"));
		pIntegerGevSCPD->SetValue(nEachPacketTimeNs / nTimestampUnit);
	}
}


//-----------------------------------------------------------------------------
//Set device action command parameters.
//-----------------------------------------------------------------------------
void SetDeviceActionCommandParam(IStDevice *pIStDevice)
{
    CNodeMapPtr pINodeMap(pIStDevice->GetRemoteIStPort()->GetINodeMap());
    CEnumerationPtr pIEnumeration_TriggerSelector(pINodeMap->GetNode("TriggerSelector"));
    CEnumEntryPtr pIEnumEntry_FrameStart(pIEnumeration_TriggerSelector->GetEntryByName("FrameStart"));
    pIEnumeration_TriggerSelector->SetIntValue(pIEnumEntry_FrameStart->GetValue());
    cout << "  TriggerSelector = FrameStart" << endl;

    CEnumerationPtr pIEnumeration_TriggerMode(pINodeMap->GetNode("TriggerMode"));
    CEnumEntryPtr pIEnumEntry_On(pIEnumeration_TriggerMode->GetEntryByName("On"));
    pIEnumeration_TriggerMode->SetIntValue(pIEnumEntry_On->GetValue());
    cout << "  TriggerMode = On" << endl;

	CEnumerationPtr pIEnumeration_TriggerSource(pINodeMap->GetNode("TriggerSource"));
	const char *pszTriggerSourceNames[] = { "Action0", "Action1" };
	for (size_t i = 0; i < 2; ++i)
	{
		CEnumEntryPtr pIEnumEntry_Action0(pIEnumeration_TriggerSource->GetEntryByName(pszTriggerSourceNames[i]));
		if (IsReadable(pIEnumEntry_Action0))
		{
			pIEnumeration_TriggerSource->SetIntValue(pIEnumEntry_Action0->GetValue());
			cout << "  TriggerSource = " << pszTriggerSourceNames[i] << endl;
			break;
		}
	}

    CIntegerPtr pIInteger_ActionDeviceKey(pINodeMap->GetNode("ActionDeviceKey"));
    pIInteger_ActionDeviceKey->SetValue(nDeviceKey);
    cout << "  ActionDeviceKey = " << hex << showbase << nDeviceKey << endl;

    CIntegerPtr pIInteger_ActionSelector(pINodeMap->GetNode("ActionSelector"));
	pIInteger_ActionSelector->SetValue(pIInteger_ActionSelector->GetMin());
	cout << "  ActionSelector = " << pIInteger_ActionSelector->GetMin() << endl;

    CIntegerPtr pIInteger_ActionGroupKey(pINodeMap->GetNode("ActionGroupKey"));
    pIInteger_ActionGroupKey->SetValue(nGroupKey);
    cout << "  ActionGroupKey = " << hex << showbase << nGroupKey << endl;

    CIntegerPtr pIInteger_ActionGroupMask(pINodeMap->GetNode("ActionGroupMask"));
    pIInteger_ActionGroupMask->SetValue(nGroupMask);
    cout << "  ActionGroupMask = " << hex << showbase << nGroupMask << endl;
}

//-----------------------------------------------------------------------------
//Set host action command parameters.
//-----------------------------------------------------------------------------
void SetHostActionCommandParam(IStInterface* pIStInterface)
{
    CNodeMapPtr pINodeMap(pIStInterface->GetIStPort()->GetINodeMap());

    CEnumerationPtr pEnumeration_EventSelector(pINodeMap->GetNode("EventSelector"));
    CEnumerationPtr pEnumeration_EventNotification(pINodeMap->GetNode("EventNotification"));

    const char *pszEventNames[] = {"ActionCommand", "ActionCommandAcknowledge"};

    for (size_t i = 0; i < 2; ++i)
    {
        pEnumeration_EventSelector->SetIntValue(pEnumeration_EventSelector->GetEntryByName(pszEventNames[i])->GetValue());
        cout << "  EventSelector = " << pszEventNames[i] << endl;
        pEnumeration_EventNotification->SetIntValue(pEnumeration_EventNotification->GetEntryByName("On")->GetValue());
        cout << "  EventNotification = On" << endl;
    }

    CIntegerPtr pIInteger_ActionDeviceKey(pINodeMap->GetNode("ActionDeviceKey"));
    pIInteger_ActionDeviceKey->SetValue(nDeviceKey);
    cout << "  ActionDeviceKey = " << hex << showbase << nDeviceKey << endl;

    CIntegerPtr pIInteger_ActionGroupKey(pINodeMap->GetNode("ActionGroupKey"));
    pIInteger_ActionGroupKey->SetValue(nGroupKey);
    cout << "  ActionGroupKey = " << hex << showbase << nGroupKey << endl;

    CIntegerPtr pIInteger_ActionGroupMask(pINodeMap->GetNode("ActionGroupMask"));
    pIInteger_ActionGroupMask->SetValue(nGroupMask);
    cout << "  ActionGroupMask = " << hex << showbase << nGroupMask << endl;

    CBooleanPtr pIBoolean_ActionScheduledTimeEnable(pINodeMap->GetNode("ActionScheduledTimeEnable"));
    pIBoolean_ActionScheduledTimeEnable->SetValue(bScheduledTimeEnable);
    cout << "  ActionScheduledTimeEnable = " << bScheduledTimeEnable << endl;

    if (bScheduledTimeEnable)
    {
        CIntegerPtr pIInteger_ActionScheduledTime(pINodeMap->GetNode("ActionScheduledTime"));
        pIInteger_ActionScheduledTime->SetValue(nScheduledTime);
        cout << "  ActionScheduledTime = " << dec << nScheduledTime << endl;
    }
}
#define InterfaceVector_t vector<IStInterface*>
typedef IStImageDisplayWnd* UserParam_t;


//-----------------------------------------------------------------------------
// Function for handling callback action
//-----------------------------------------------------------------------------
void OnStCallbackCFunction(IStCallbackParamBase *pIStCallbackParamBase, UserParam_t pvContext)
{
    // Check callback type.
    // We only handle NewBuffer event in here.
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

            // Check if acquired data contains image data.
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
//
//-----------------------------------------------------------------------------
int main(int, char **)
{
    InterfaceVector_t vecInterface;

    try
    {
        // Initialize StApi before using.
        CStApiAutoInit objStApiAutoInit;

        // Create a system object for device scan and connection.
        CIStSystemPtr pIStSystem(CreateIStSystem(StSystemVendor_Default, StInterfaceType_GigEVision));

        // Check GigE interface for devices.
        // If there is no camera, throw exception.
        for (size_t i = 0; i < pIStSystem->GetInterfaceCount(); i++)
        {
            IStInterface *pIStInterface = pIStSystem->GetIStInterface(i);

            try
            {
                // Displays the DisplayName of the interface.
                GenApi::CIntegerPtr pIInteger_GevInterfaceSubnetIPAddress(pIStInterface->GetIStPort()->GetINodeMap()->GetNode("GevInterfaceSubnetIPAddress"));
                cout << "Interface" << dec << i << "=" << pIStInterface->GetIStInterfaceInfo()->GetDisplayName() << "[" << pIInteger_GevInterfaceSubnetIPAddress->ToString() << "]" << endl;

                SetHostActionCommandParam(pIStInterface);

                vecInterface.push_back(pIStInterface);
                
                //Start Event Acquisition Thread
                pIStInterface->StartEventAcquisitionThread();
            }
            catch (const GenICam::GenericException &e)
            {
                // Display a description of the error.

                cerr << endl << "An exception occurred." << endl << e.GetDescription() << endl;
            }
        }
        if (vecInterface.empty())
        {
            throw RUNTIME_EXCEPTION("There is no interface.");
        }

        // Create a camera device list object to store all the cameras.
        CIStDevicePtrArray pIStDeviceList;

        // If using GUI for display, create a display window here.
        CIStImageDisplayWndPtrArray pIStWndList;

        // Create a DataStream list object to store all the data stream object related to the cameras.
        CIStDataStreamPtrArray pIStDataStreamList;

        // Here we try to connect to all possible device with a do-while loop.
        do
        {
            IStDeviceReleasable *pIStDeviceReleasable = NULL;

            try
            {
                // Create a camera device object and connect to first detected device.
                pIStDeviceReleasable = pIStSystem->CreateFirstIStDevice();
            }
            catch (...)
            {
                if (pIStDeviceList.GetSize() == 0)
                {
                    throw;
                }
                else
                {
                    break;
                }
            }

            // Add the camera into device object list for later usage.
            pIStDeviceList.Register(pIStDeviceReleasable);

            // Displays the DisplayName of the device.
            GenApi::CIntegerPtr pIInteger_GevDeviceIPAddress(pIStDeviceReleasable->GetLocalIStPort()->GetINodeMap()->GetNode("GevDeviceIPAddress"));
            cout << "Device" << dec << pIStDeviceList.GetSize() << "=" << pIStDeviceReleasable->GetIStDeviceInfo()->GetDisplayName() << "[" << pIInteger_GevDeviceIPAddress->ToString() << "]" << endl;


            //Set action command parameter
            try
            {
                SetDeviceActionCommandParam(pIStDeviceReleasable);
            }
            catch (const GenICam::GenericException &e)
            {
                // Display a description of the error.

                cerr << endl << "An exception occurred." << endl << e.GetDescription() << endl;
            }


            // Create a DataStream object for handling image stream data then add into DataStream list for later usage.
            pIStDataStreamList.Register(pIStDeviceReleasable->CreateIStDataStream(0));

            IStDataStream *pIStDataStream = pIStDataStreamList[pIStDataStreamList.GetSize() - 1];

            // Create an image display window object, to get the IStWndReleasable interface pointer.
            pIStWndList.Register(CreateIStWnd(StWindowType_ImageDisplay));
            IStImageDisplayWnd *pIStImageDisplayWnd = pIStWndList[pIStWndList.GetSize() - 1];
            // Display the window.
            pIStImageDisplayWnd->Show(NULL, StWindowMode_Modaless);

            RegisterCallback(pIStDataStream, &OnStCallbackCFunction, (UserParam_t)pIStImageDisplayWnd);

        } while (true);

        // Start the image acquisition of the host side.
        pIStDataStreamList.StartAcquisition();

        // Start the image acquisition of the camera side.
        pIStDeviceList.AcquisitionStart();
        
		// Adjust GevSCPD;
		AdjustGevSCPD(pIStDeviceList);

        // Create an NodeMap display window.
        CIStNodeMapDisplayWndPtr pIStNodeMapDisplayWnd(StApi::CreateIStWnd(StWindowType_NodeMapDisplay));

        for (InterfaceVector_t::iterator itr = vecInterface.begin(); itr != vecInterface.end(); ++itr)
        {
            IStInterface *pIStInterface = *itr;
            GenICam::gcstring strInterfaceName(pIStInterface->GetIStInterfaceInfo()->GetDisplayName());

            // Register the node to NodeMap window.
            pIStNodeMapDisplayWnd->RegisterINode((*itr)->GetIStPort()->GetINodeMap()->GetNode("ActionControl"), strInterfaceName);
            pIStNodeMapDisplayWnd->RegisterINode((*itr)->GetIStPort()->GetINodeMap()->GetNode("EventControl"), strInterfaceName);
        }

        // Display the nodemap window.
        pIStNodeMapDisplayWnd->Show(NULL, StWindowMode_Modaless);

        cout << "Press any key to terminate" << endl;
        // Wait until any key is pressed.
        do
        {
            if (_kbhit()) break;
            processEventGUI();
        }
        while(true);

        // Stop the image acquisition of the camera side.
        pIStDeviceList.AcquisitionStop();

        // Stop the image acquisition of the host side.
        pIStDataStreamList.StopAcquisition();

        for(InterfaceVector_t::iterator itr = vecInterface.begin(); itr != vecInterface.end(); ++itr)
        {
            //Stop Event Acquisition Thread
            (*itr)->StopEventAcquisitionThread();
        }
        vecInterface.clear();
    }
    catch (const GenICam::GenericException &e)
    {
        // Display a description of the error.
        cerr << endl << "An exception occurred." << endl << e.GetDescription() << endl;
    }

    return(0);
}
