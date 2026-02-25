#ifndef MDICHILDDEVICE_H
#define MDICHILDDEVICE_H

#include <QWidget>
#include "mdichild.h"
#include "cavifilerecorder.h"
#include "widgetdefectivepixeldetection.h"
#include "istimagecallback.h"
#include "istreamingctrl.h"

namespace Ui {
class MdiChildDevice;
}
class MdiChild;
class MainWindow;

struct ICameraCtrl
{
	// Start recording.
	virtual void StartRecording() = 0;

	// Stop recording.
	virtual void StopRecording() = 0;

	// Save or load a camera config file.
	virtual void CameraConfigFile(bool isOpenMode) = 0;

	// Save camera description file (compressed file or xml)
	virtual void SaveCameraDescriptionFile() = 0;

	virtual bool IsFFCCorrectionSupported() = 0;

	virtual bool ComputeFFCCorrection() = 0;
};

class MdiChildDevice final : public MdiChild, public IStreamingCtrl, public ICameraCtrl
{
public:
    explicit MdiChildDevice(QWidget *parent);
    ~MdiChildDevice();

    // Open Camera and do initialization. Return false if camera is not opened.
    bool openCamera();

    // Get the current FPS value.
    void GetFPSString(QString &str);

    // Get the received image count.
    uint64_t GetReceivedImageCount() const
    {
        return m_nReceivedImageCount;
    }

    // Get the dropped frame count.
    uint64_t GetDroppedIDFrameCount() const
    {
        return m_nDroppedIDCount;
    }

    // Return true if recording is running.
    bool IsRecording() const
    {
        return (m_pCAVIFile != nullptr);
    }

    // Callback function for EventDeviceLost.
    void OnDeviceLost(GenApi::INode *pINode, void*);

    // Callback function for EventNewBuffer.
    void OnStCallback(StApi::IStCallbackParamBase *pIStCallbackParamBase, void *);

    // Implementation of IStreamingCtrl. Return true if image acquisition is running.
    bool IsAcquisitionRunning() const override
    {
        return m_IsAcquisitionRunning;
    }

    // Implementation of IStreamingCtrl. Start image acquisition.
    void StartImageAcquisition() override;

    // Implementation of IStreamingCtrl. Stop image acquisition.
    void StopImageAcquisition() override;

    // Start recording.
    void StartRecording();

    // Stop recording.
    void StopRecording();

    // Save or load a camera config file.
    void CameraConfigFile(bool isOpenMode);

    // Save camera description file (compressed file or xml)
    void SaveCameraDescriptionFile();


    // FFC correction related.
    bool IsFFCCorrectionSupported();
    bool ComputeFFCCorrection();
    CIStImageCallbackList m_objCIStImageCallbackList;


	void GetStatusBarText(size_t nIndex, QString &strText);
protected:


    StApi::CIStRegisteredCallbackPtr m_pIStRegisteredCallbackDeviceLost;
    StApi::CIStDataStreamPtr m_pIStDataStream;
    StApi::CIStDevicePtr m_pIStDevice;

    bool m_IsAcquisitionRunning;
    uint64_t m_nReceivedImageCount;
    uint64_t m_nDroppedIDCount;
    uint64_t m_nLastID;
    bool    m_bFirstFrame;

    bool    m_IsDeviceLost;

    GenApi::CLock m_CLockForAVI;
    CAVIFileRecorder *m_pCAVIFile;

    // Register nodes to be displayed in the NodeMap window.
    void DisplayGenApiNodes();


	void OnCloseEvent();
private:

    Ui::MdiChildDevice *ui;

    WidgetDefectivePixelDetection *m_pDefectivePixelDetection;
};

#endif // MDICHILDDEVICE_H
