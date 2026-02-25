/*!
\file GigEActionCommand.cpp
\brief 
 
This sample shows how to use GigE Action command.
 The following points will be demonstrated in this sample code:
 - Initialize StApi
 - Connect to GigE camera
 - Set and send action command

 For more information, please refer to the help document of StApi.

*/

// If you want to use the GUI features, please refer to GigEActionCommand-GUI.cpp

// Include files for using StApi.
#include <StApi_TL.h>
#include <unistd.h>

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
		if (GenApi::IsAvailable(pIEnumEntry_Action0))
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
#define InterfaceVector_t vector<CActionCommandInterface*>
typedef IStInterface*    ActionCommandCallbackUserParam_t;

//-----------------------------------------------------------------------------
// Class for action commande event.
//-----------------------------------------------------------------------------
class CActionCommandEvent
{
public:
    CActionCommandEvent(IStInterface *pIStInterface) : m_pIStInterface(pIStInterface)
    {
        CNodeMapPtr pINodeMap(pIStInterface->GetIStPort()->GetINodeMap());
        m_pIInteger_EventActionCommand = pINodeMap->GetNode("EventActionCommand");
        m_pIInteger_EventActionCommandRequestID = pINodeMap->GetNode("EventActionCommandRequestID");
        m_objCIStRegisteredCallbackPtr_OnCommandSent = RegisterCallback(m_pIInteger_EventActionCommand->GetNode(), *this, &CActionCommandEvent::OnCommandSent, pIStInterface, cbPostOutsideLock);

        m_pIInteger_EventActionCommandAcknowledge = pINodeMap->GetNode("EventActionCommandAcknowledge");
        m_pIInteger_EventActionCommandAcknowledgeSourceIPAddress = pINodeMap->GetNode("EventActionCommandAcknowledgeSourceIPAddress");
        m_pIEnumeration_EventActionCommandAcknowledgeStatus = pINodeMap->GetNode("EventActionCommandAcknowledgeStatus");
        m_pIInteger_EventActionCommandAcknowledgeAcknowledgeID = pINodeMap->GetNode("EventActionCommandAcknowledgeAcknowledgeID");
        m_objCIStRegisteredCallbackPtr_OnAcknowledgeRcv = RegisterCallback(m_pIInteger_EventActionCommandAcknowledge->GetNode(), *this, &CActionCommandEvent::OnAcknowledgeRcv, pIStInterface, cbPostOutsideLock);

        m_pIInteger_GevActionDestinationIPAddress = pINodeMap->GetNode("GevActionDestinationIPAddress");
    };
    ~CActionCommandEvent()
    {
    };
    void OnCommandSent(INode* pINode, ActionCommandCallbackUserParam_t pIStInterface)
    {
        stringstream ss;
        ss
            << "Sent action command[" << dec << m_pIInteger_EventActionCommandRequestID->GetValue() << "]:"
            << m_pIInteger_GevActionDestinationIPAddress->ToString()
            << endl;
        cout << ss.str();
    };
    void OnAcknowledgeRcv(INode* pINode, ActionCommandCallbackUserParam_t pIStInterface)
    {
        stringstream ss;
        if (m_pIEnumeration_EventActionCommandAcknowledgeStatus->GetCurrentEntry()!=NULL)
        {
        ss
            << "Rcv action command[" << dec << m_pIInteger_EventActionCommandAcknowledgeAcknowledgeID->GetValue() << "]:"
            << m_pIInteger_EventActionCommandAcknowledgeSourceIPAddress->ToString()
            << "(" << m_pIEnumeration_EventActionCommandAcknowledgeStatus->GetCurrentEntry()->GetNode()->GetDisplayName() << ")"
            << endl;
        }
        else 
            ss << "Rcv action command[" << dec << m_pIInteger_EventActionCommandAcknowledgeAcknowledgeID->GetValue() << "]:null";
        cout << ss.str();
    };
protected:
    IStInterface *m_pIStInterface;
    CIntegerPtr m_pIInteger_EventActionCommand;
    CIntegerPtr m_pIInteger_EventActionCommandRequestID;
    StApi::CIStRegisteredCallbackPtr m_objCIStRegisteredCallbackPtr_OnCommandSent;

    CIntegerPtr m_pIInteger_EventActionCommandAcknowledge;
    CIntegerPtr m_pIInteger_EventActionCommandAcknowledgeSourceIPAddress;
    CEnumerationPtr m_pIEnumeration_EventActionCommandAcknowledgeStatus;
    CIntegerPtr m_pIInteger_EventActionCommandAcknowledgeAcknowledgeID;
    StApi::CIStRegisteredCallbackPtr m_objCIStRegisteredCallbackPtr_OnAcknowledgeRcv;

    CIntegerPtr m_pIInteger_GevActionDestinationIPAddress;
};
//-----------------------------------------------------------------------------
// Class for Action Command interface.
//-----------------------------------------------------------------------------
class CActionCommandInterface
{
public:
    CActionCommandInterface(IStInterface *pIStInterface) : 
        m_objCActionCommandEvent(pIStInterface), 
        m_pIStInterface(pIStInterface)
    {
        CNodeMapPtr pINodeMap(pIStInterface->GetIStPort()->GetINodeMap());
        m_pICommand_ActionCommand = pINodeMap->GetNode("ActionCommand");
    };
    virtual ~CActionCommandInterface() {};

    IStInterface *GetIStInterface() {    return(m_pIStInterface);    };
    void Execute()
    {
        m_pICommand_ActionCommand->Execute();
    }
protected:
    CActionCommandEvent m_objCActionCommandEvent;
    IStInterface *m_pIStInterface;
    CCommandPtr m_pICommand_ActionCommand;
};

//-----------------------------------------------------------------------------
// Console function for sending action command.
//-----------------------------------------------------------------------------
size_t SendActionCommand(InterfaceVector_t &vecInterface)
{
    size_t nInput = 0;    //1:exit
    //const uint64_t nScheduledTime = 12345;


    do
    {
        // Display a choice of setting function
        cout << "Input (0:Action Command, 1:Exit) : ";

        // Waiting for input.
        cin >> nInput;
        while (cin.get() != '\n');
    } while (1 < nInput);

    if (nInput == 0)
    {
        //Send action command.
        for (InterfaceVector_t::iterator itr = vecInterface.begin(); itr != vecInterface.end(); ++itr)
        {
            CActionCommandInterface *pCActionCommandInterface = *itr;
            pCActionCommandInterface->Execute();
        }
    }

    return(nInput);
}

typedef void*    UserParam_t;


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

            // Check if the acquired data contains image data.
            if (pIStStreamBuffer->GetIStStreamBufferInfo()->IsImagePresent())
            {

                // If yes, we create a IStImage object for further image handling.
                IStImage *pIStImage = pIStStreamBuffer->GetIStImage();

                // Display the information of the acquired image data.
                GenApi::CIntegerPtr pIInteger_GevDeviceIPAddress(pIStDataStream->GetIStDevice()->GetLocalIStPort()->GetINodeMap()->GetNode("GevDeviceIPAddress"));
                stringstream ss;
                ss 
                    << "IPAddress=" << pIInteger_GevDeviceIPAddress->ToString()
                    << " BlockId=" << pIStStreamBuffer->GetIStStreamBufferInfo()->GetFrameID()
                    << " Size:" << pIStImage->GetImageWidth() << " x " << pIStImage->GetImageHeight()
                    << " Timestamp =" << pIStStreamBuffer->GetIStStreamBufferInfo()->GetTimestampNS() << "[ns]" << endl;
                cout << ss.str();
            }
            else
            {
                // If the acquired data contains no image data.
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

                vecInterface.push_back(new CActionCommandInterface(pIStInterface));
                
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

        // Create a DataStream list object to store all the data stream object related to the cameras.
        CIStDataStreamPtrArray pIStDataStreamList;

        // Here we try to connect to all possible device with a do-while loop.
        for (;;)
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

            RegisterCallback(pIStDataStream, &OnStCallbackCFunction, (UserParam_t)NULL);


        } 

        // Start the image acquisition of the host side.
        pIStDataStreamList.StartAcquisition();

        // Start the image acquisition of the camera side.
        pIStDeviceList.AcquisitionStart();

		// Adjust GevSCPD;
		AdjustGevSCPD(pIStDeviceList);

        while (SendActionCommand(vecInterface) == 0)
        {
            usleep(200000);
        };

        // Stop the image acquisition of the camera side.
        pIStDeviceList.AcquisitionStop();

        // Stop the image acquisition of the host side.
        pIStDataStreamList.StopAcquisition();

        for(InterfaceVector_t::iterator itr = vecInterface.begin(); itr != vecInterface.end(); ++itr)
        {
            CActionCommandInterface *pCActionCommandInterface = *itr;

            //Stop Event Acquisition Thread
            pCActionCommandInterface->GetIStInterface()->StopEventAcquisitionThread();

            delete pCActionCommandInterface;
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
