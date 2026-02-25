/*!
\file Overlay.cpp
\brief 
 
 This sample shows how to use the callback functions to draw on top of the acquired image.
 The following points will be demonstrated in this sample code:
 - Initialize StApi
 - Connect to camera
 - Acquire image data (with waiting in main thread)
 - Use callback function to draw on top of the acquired image.

 For more information, please refer to the help document of StApi.

 This sample uses QPainter from Qt5. Please install Qt5 to compile this sample.

 Compile procedure:
  - execute: qmake to generate Makefile
  - execute: make
*/

// Include files for using StApi.
#include <StApi_TL.h>
#include <StApi_GUI.h>
#include <iomanip>    //std::setprecision
#include <thread>
#include <QPainter> //Qt painter

//Namespace for using StApi.
using namespace StApi;

//Namespace for using cout
using namespace std;

//Count of images to be grabbed.
const uint64_t nCountOfImagesToGrab = 500;


typedef void*    UserParam_t;
void OnCallback(IStCallbackParamBase *pIStCallbackParamBase, UserParam_t /*pvContext*/)
{
    if (pIStCallbackParamBase->GetCallbackType() == StCallbackType_StApiGUIEvent_DisplayImageWndDrawing)
    {

        StApi::IStCallbackParamStApiGUIEventDrawing *pIStCallbackParamStApiGUIEventDrawing = dynamic_cast<StApi::IStCallbackParamStApiGUIEventDrawing*>(pIStCallbackParamBase);

        QPainter *hDC = static_cast<QPainter *>(pIStCallbackParamStApiGUIEventDrawing->GetDC());
        StApi::IStImage *pIStImage = pIStCallbackParamStApiGUIEventDrawing->GetIStImage();
        const size_t nImageWidth = pIStImage->GetImageWidth();
        const size_t nImageHeight = pIStImage->GetImageHeight();

        const size_t nROIOffsetX = pIStCallbackParamStApiGUIEventDrawing->GetROIOffsetX();
        const size_t nROIOffsetY = pIStCallbackParamStApiGUIEventDrawing->GetROIOffsetY();
        const size_t nROIWidth = pIStCallbackParamStApiGUIEventDrawing->GetROIWidth();
        const size_t nROIHeight = pIStCallbackParamStApiGUIEventDrawing->GetROIHeight();
        const size_t nDisplayWidth = pIStCallbackParamStApiGUIEventDrawing->GetDisplayWidth();
        const size_t nDisplayHeight = pIStCallbackParamStApiGUIEventDrawing->GetDisplayHeight();

        const double dblMagnificationH = nDisplayWidth / (double)nROIWidth;
        const double dblMagnificationV = nDisplayHeight / (double)nROIHeight;

        // Draw an ellipse inside the display image
        {
            const QRect rect(-(nROIOffsetX * dblMagnificationH), -(nROIOffsetY * dblMagnificationV), (nImageWidth - nROIOffsetX) * dblMagnificationH, (nImageHeight - nROIOffsetY) * dblMagnificationV);
            hDC->drawEllipse(rect);
        }

        // Draw an ellipse inside the display area.
        {
            const QRect rect(0, 0, nDisplayWidth, nDisplayHeight);
            hDC->setPen(QColor(255,0,0));
            hDC->drawEllipse(rect);
        }

        // Center lines.
        {
            const QPoint ptStart(nImageWidth * dblMagnificationH / 2, 0);
            const QPoint ptEnd(nImageWidth * dblMagnificationH / 2, nImageHeight * dblMagnificationV);
            hDC->setPen(QColor(255,255,0));
            hDC->drawLine(ptStart, ptEnd);
        }
        {
            const QPoint ptStart(0, nImageHeight * dblMagnificationV / 2);
            const QPoint ptEnd(nImageWidth * dblMagnificationH, nImageHeight * dblMagnificationV / 2);
            hDC->setPen(QColor(255,255,0));
            hDC->drawLine(ptStart, ptEnd);
        }

        // Draw rect
        {
            const QRect rect(10, 10, 100, 100);
            hDC->drawRect(rect);
        }

        // Draw polygon
        {
            const int nOffsetX = 200;
            const int nOffsetY = 200;
            const QPoint pPoint[] =
            {
                QPoint(nOffsetX + 0, nOffsetY + 0),
                QPoint (nOffsetX + 100, nOffsetY + 50),
                QPoint (nOffsetX + 0, nOffsetY + 100),
            };
            hDC->drawPolygon(pPoint,3);
        }

        //Draw text
        {
            const QPoint ptPos(300, 300);
            hDC->drawText(ptPos, QString("Text"));
        }
    }
}



#ifdef ENABLED_CLASS_METHOD_TYPE_CALLBACK
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
class CCallback
{
public:
    CCallback(){};
    ~CCallback(){};


    void OnStCallbackClassMethod(IStCallbackParamBase *pIStCallbackParamBase, UserParam_t pvContext)
    {
        OnCallback(pIStCallbackParamBase, pvContext);
    };
};
#else
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void OnStCallbackCFunction(IStCallbackParamBase *pIStCallbackParamBase, UserParam_t pvContext)
{
    OnCallback(pIStCallbackParamBase, pvContext);
}
#endif


void acquisitionWorker(CIStDevicePtr *pIStDevice, CIStDataStreamPtr *pIStDataStream, CIStImageDisplayWndPtr *pIStImageDisplayWnd, bool *isTerminated)
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
            // If the acquired data contains no image data
            cout << "Image data does not exist" << endl;
        }
    }
    *isTerminated = true;
}

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

        // Create an image display window object for showing image.
        CIStImageDisplayWndPtr pIStImageDisplayWnd(CreateIStWnd(StWindowType_ImageDisplay));

        // Register a callback function. When an event occurs for ImageDisplayWnd, function registered is called.
#ifdef ENABLED_CLASS_METHOD_TYPE_CALLBACK
        CCallback objCCallback;
        RegisterCallback(pIStImageDisplayWnd, objCCallback, &CCallback::OnStCallbackClassMethod, (UserParam_t)NULL);
#else
        RegisterCallback(pIStImageDisplayWnd, &OnStCallbackCFunction, (UserParam_t)NULL);
#endif

        // Create a DataStream object for handling image stream data.
        CIStDataStreamPtr pIStDataStream(pIStDevice->CreateIStDataStream(0));

        // Start the image acquisition of the host side.
        pIStDataStream->StartAcquisition(nCountOfImagesToGrab);

        // Start the image acquisition of the camera side.
        pIStDevice->AcquisitionStart();

        // Initialize thread for image acquisition
        bool isTerminated = false;
        thread worker(acquisitionWorker, &pIStDevice, &pIStDataStream, &pIStImageDisplayWnd, &isTerminated);

        // process the GUI event while waiting for thread completion
        while(!isTerminated) 
        {
            processEventGUI();
            
            // Check if display window is visible.
            if (!pIStImageDisplayWnd->IsVisible())
            {
                // Display the window.
                pIStImageDisplayWnd->Show(NULL, StWindowMode_Modaless);
            }
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

    cout << endl << "done." << endl;

    return 0;
}
