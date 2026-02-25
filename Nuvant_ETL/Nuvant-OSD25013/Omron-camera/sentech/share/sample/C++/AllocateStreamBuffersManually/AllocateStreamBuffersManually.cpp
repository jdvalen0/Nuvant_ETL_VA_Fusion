/*!
\file AllocateStreamBuffersManually.cpp
\brief 
 
 This sample shows how to manually create buffer for streaming.
 The following points will be demonstrated in this sample code:
 - Initialize StApi 
 - Connect to camera
 - Acquire image data (with waiting in main thread)
 - Create your own memory allocator for handling stream data.

 For more information, please refer to the help document of StApi.

*/

// If you want to use the GUI features, please refer to AllocateStreamBuffersManually-GUI.cpp

// Include files for using StApi.
#include <StApi_TL.h>


// Namespace for using StApi.
using namespace StApi;

// Namespace for using cout
using namespace std;

// Target counts of image to be grabbed.
const uint64_t nCountOfImagesToGrab = 100;

// Custom memory allocator class implementation.
class CMyAllocator : public IStAllocator
{
public:
    CMyAllocator() : m_nAllocateCount(0), m_nDeallocateCount(0)
    {}

    // Function for memory allocation.
    void Allocate(void **pCreatedBuffer, size_t nSize, void **pContext) throw()
    {
        // Display the requested memory size.
        cout << "Allocate[" << m_nAllocateCount << "] Size = " << nSize << endl;

        try
        {
            // Memory allocation of the requested size.
            *pCreatedBuffer = new uint8_t[nSize];

            // Assigning the number of allocation to pContext. 
            // Value assigned to pContext is passed as an argument when the memory is deallocated.
            *(size_t*)pContext = m_nAllocateCount;

            // Record number of times the memory is allocated.
            ++m_nAllocateCount;
        }
        catch (...)
        {
            *pCreatedBuffer = NULL;
        }
        
    }

    // Function for memory deallocation.
    void Deallocate(void *ptr, size_t nSize, void *pContext) throw()
    {
        // Display the size of the memory to be freed.
        cout << "Deallocate[" << m_nDeallocateCount << "] Size = " << nSize << "(Allocate[" << (size_t)pContext << "])" << endl;

        // Free the allocated memory.
        delete[] static_cast<uint8_t*>(ptr);

        // Record the number of times that the memory has been freed
        ++m_nDeallocateCount;
    }

    // Function called when registered allocator is no longer needed.
    void OnDeregister() throw()
    {
        cout << "OnDeregister Allocate Count=" << m_nAllocateCount << ", Deallocate Count=" << m_nDeallocateCount << endl;
    }
protected:
    size_t m_nAllocateCount;
    size_t m_nDeallocateCount;
};


int main(int, char **)
{
    try
    {
        // Initialize StApi before using.
        CStApiAutoInit objStApiAutoInit;

        // Create a system object for device scan and connection.
        CIStSystemPtr pIStSystem(CreateIStSystem());

        // Create a camera device object and connect to the first detected device.
        CIStDevicePtr pIStDevice(pIStSystem->CreateFirstIStDevice());

        // Display the DisplayName of the device.
        cout << "Device=" << pIStDevice->GetIStDeviceInfo()->GetDisplayName() << endl;

        // Create a custom class object for memory allocation.
        CMyAllocator m_objCMyAllocator;

        // Create a DataStream object for handling image stream data.
        // If you set a pointer of CMyAllocator class (m_objCMyAllocator), it will be used for creating buffer for this streaming.
        CIStDataStreamPtr pIStDataStream(pIStDevice->CreateIStDataStream(0, &m_objCMyAllocator));

        // Set the numbers of stream buffers.
        pIStDataStream->SetStreamBufferCount(8);

        // Start the image acquisition of the host (local machine) side.
        pIStDataStream->StartAcquisition(nCountOfImagesToGrab);

        // Start the image acquisition of the camera side.
        pIStDevice->AcquisitionStart();

        // A while loop for acquiring data and checking status. 
        // Here, the acquisition runs until it reaches the assigned numbers of frames.
        while (pIStDataStream->IsGrabbing())
        {
            // Retrieve the buffer pointer of image data with timeout of 5000ms.
            CIStStreamBufferPtr pIStStreamBuffer(pIStDataStream->RetrieveBuffer(5000));

            // Check if the acquired data contains image data.
            if (pIStStreamBuffer->GetIStStreamBufferInfo()->IsImagePresent())
            {
                // If yes, get the IStImage interface pointer to the acquired image data for further operation.
                IStImage *pIStImage = pIStStreamBuffer->GetIStImage();

                // Display the information of the acquired image data.
                cout << "BlockId=" << pIStStreamBuffer->GetIStStreamBufferInfo()->GetFrameID()
                    << " Size:" << pIStImage->GetImageWidth() << " x " << pIStImage->GetImageHeight()
                    << " First byte =" << (uint32_t)*(uint8_t*)pIStImage->GetImageBuffer() << endl;
            }
            else
            {
                // If the acquired data contains no image data.
                cout << "Image data not exist" << endl;
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
    while(cin.get() != '\n');

    return(0);
}
