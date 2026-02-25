/*!
\file MultipleFilters.cpp
\brief 
 
 This sample shows how to process received image with multiple filters.
 The following points will be demonstrated in this sample code:
 - Initialize StApi
 - Connect to camera
 - Acquire image data (with waiting in main thread)
 - Set up multiple filters
 - Process image with multiple filters

 For more information, please refer to the help document of StApi.

*/

// Include files for using StApi.
#include <StApi_TL.h>
#include <StApi_IP.h>
#include <StApi_GUI.h>
#include <iomanip>    //std::setprecision
#include <thread>

//Namespace for using StApi.
using namespace StApi;

//Namespace for using cout
using namespace std;

// Count of images to be grabbed.
const uint64_t nCountOfImagesToGrab = 5000;


void acquisitionWorker(CIStDevicePtr *pIStDevice, CIStDataStreamPtr *pIStDataStream, CIStImageDisplayWndPtr *pIStImageDisplayWnd, CIStFilterPtrArray *pIStFilterPtrList, bool *isCompleted)
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

            // Filter the acquired image.
            (*pIStFilterPtrList).Filter(pIStImage);

            // Create a string to be displayed on the status bar
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
void SelectFilters(IStDevice *pIStDevice, CIStFilterPtrArray &pIStFilterPtrList)
{
    // Get the IEnumeration interface pointer of PixelFormat node
    GenApi::CEnumerationPtr pIEnumerationPtr(pIStDevice->GetRemoteIStPort()->GetINodeMap()->GetNode("PixelFormat"));
    if (pIEnumerationPtr == nullptr)
    {
        throw ACCESS_EXCEPTION("PixelFormat node does not exist.");
    }

    // Get the current pixel format value
    EStPixelFormatNamingConvention_t nPFNC = (EStPixelFormatNamingConvention_t)pIEnumerationPtr->GetIntValue();

    //
    for (;;)
    {
        // Display a filter that corresponds to the current pixel format as an option
        cout << nCountOfImagesToGrab << " frames will be captured." << endl;
        cout << "Select filters:" << endl;
        for (size_t i = 0; i < StFilterType_Count; i++)
        {
            IStFilterInfo* pIStFilterInfo = GetIStFilterInfo((EStFilterType_t)i);
            if (pIStFilterInfo->IsSupported(nPFNC))
            {
                cout << i << " : " << pIStFilterInfo->GetFilterName().c_str() << endl;
            }
        }
        cout << "Else : Exit filter selection" << endl;
        cout << "Input index of the filter to be inserted : ";

        //Waiting for input
        size_t nIndex;
        cin >> nIndex;
        if (cin.fail()) break;

        if ((nIndex < StFilterType_Count) && GetIStFilterInfo((EStFilterType_t)nIndex)->IsSupported(nPFNC))
        {
            // Create a selected filter object, to get the IStFilterReleasable interface pointer.
            // If the filter object is no longer needed, call the IStFilterReleasable::Release() to discard the filter object.
            // (In the destructor of CIStFilterPtrArray, IStFilterReleasable::Release() is automatically called.)
            pIStFilterPtrList.Register(CreateIStFilter((EStFilterType_t)nIndex));
        }
        else
        {
            break;
        }
            
    } 


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
        
        // Select the filters.
        CIStFilterPtrArray pIStFilterPtrList;
        SelectFilters(pIStDevice, pIStFilterPtrList);

        
        // Create an NodeMap display window object.
        CIStNodeMapDisplayWndPtr pIStNodeMapDisplayWnd(CreateIStWnd(StWindowType_NodeMapDisplay));
        const size_t nCount = pIStFilterPtrList.GetSize();
        for (size_t i = 0; i < nCount; i++)
        {
            // Register the node to NodeMap window.
            IStFilter *pIStFilter = pIStFilterPtrList[i];
            pIStNodeMapDisplayWnd->RegisterINode(pIStFilter->GetINodeMap()->GetNode("Root"), pIStFilter->GetIStFilterInfo()->GetFilterName());
        }
        // Sets the position and size of the window.
        pIStNodeMapDisplayWnd->SetPosition(0, 0, 480, 1024);

        // Display the window.
        pIStNodeMapDisplayWnd->Show(NULL, StWindowMode_Modaless);

        // Create an image display window object for image display.
        CIStImageDisplayWndPtr pIStImageDisplayWnd(CreateIStWnd(StWindowType_ImageDisplay));

        // Sets the position and size of the window.
        pIStImageDisplayWnd->SetPosition(480, 0, 1280, 1024);

        // Create a DataStream object for handling image stream data.
        CIStDataStreamPtr pIStDataStream(pIStDevice->CreateIStDataStream(0));

        // Start the image acquisition of the host side.
        pIStDataStream->StartAcquisition(nCountOfImagesToGrab);

        // Start the image acquisition of the camera side.
        pIStDevice->AcquisitionStart();
        
        // Initialize thread for image acquisition
        bool isCompleted = false;
        std::thread worker(acquisitionWorker, &pIStDevice, &pIStDataStream, &pIStImageDisplayWnd, &pIStFilterPtrList, &isCompleted);
        
        // process the GUI event while waiting for thread completion
        while(!isCompleted) 
        {
            // Display window
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

    cin.ignore();
    // Wait until the Enter key is pressed.
    cout << endl << "Press Enter to exit." << endl;
    while (cin.get() != '\n');

    return(0);
}
