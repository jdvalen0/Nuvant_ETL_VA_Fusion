/*!
\file SaveAndLoadFeatures.cpp
\brief 

 This sample shows how to save/load camera setting with using featureBag.
 The following points will be demonstrated in this sample code:
 - Initialize StApi
 - Connect to camera
 - Save/load camera setting to/from file
 - Apply the loaded setting to camera

 For more information, please refer to the help document of StApi.

*/

// Include files for using StApi.
#include <StApi_TL.h>

//Namespace for using StApi.
using namespace StApi;


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
        CIStDevicePtr pIStDevice(pIStSystem->CreateFirstIStDevice(GenTL::DEVICE_ACCESS_EXCLUSIVE));
        std::cout << "Device=" << pIStDevice->GetIStDeviceInfo()->GetDisplayName() << std::endl;

        GenICam::gcstring strFileName = GenICam::gcstring("/tmp");
        if (getenv("TMPDIR") != NULL)
            strFileName = GenICam::gcstring(getenv("TMPDIR"));
        strFileName.append("/Features.cfg");

        // Use INodeMap object to access current setting of the camera.
        GenApi::CNodeMapPtr pINodeMapRemote(pIStDevice->GetRemoteIStPort()->GetINodeMap());
        {
            // Create a FeatureBag object for acquiring/saving camera settings.
            CIStFeatureBagPtr pIStFeatureBagPtr(CreateIStFeatureBag());

            // Acquire and save all current settings from INodeMap object to FeatureBag.
            pIStFeatureBagPtr->StoreNodeMapToBag(pINodeMapRemote);

            // Display all settings.
            GenICam::gcstring strFeatures;
            pIStFeatureBagPtr->SaveToString(strFeatures);
            std::cout << strFeatures << std::endl;

            // Save the settings in the FeatureBag to file
            std::cout << std::endl << "Saving " << strFileName.c_str() << "... ";
            pIStFeatureBagPtr->SaveToFile(strFileName);
            std::cout << "done" << std::endl;
        }
        {
            // Create another FeatureBag for loading setting from file.
            CIStFeatureBagPtr pIStFeatureBagPtr(CreateIStFeatureBag());

            // Load the settings from file to the FeatureBag.
            // *Note: we load from the one we just created above.
            pIStFeatureBagPtr->StoreFileToBag(strFileName);

            // Load the settings from the FeatureBag to the camera
            std::cout << std::endl << "Loading to the camera " << "... ";
            pIStFeatureBagPtr->Load(pINodeMapRemote, true);
            std::cout << "done" << std::endl;
        }
    }
    catch (const GenICam::GenericException &e)
    {
        // Display the description of the error when occurred.
        std::cerr << std::endl << "An exception occurred." << std::endl << e.GetDescription() << std::endl;
    }

    // Wait until the Enter key is pressed.
    std::cout << std::endl << "Press Enter to exit." << std::endl;
    while(std::cin.get() != '\n');

    return(0);
}
