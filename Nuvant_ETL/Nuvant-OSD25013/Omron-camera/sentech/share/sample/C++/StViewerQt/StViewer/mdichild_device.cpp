#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>

#include "ui_mdichild_device.h"

#include "mdichild_device.h"
#include "ccamerasideffc.h"
#include "cconfigurationfile.h"

MdiChildDevice::MdiChildDevice(QWidget *parent) :
	MdiChild(parent),
    m_IsAcquisitionRunning(false),
    m_nReceivedImageCount(0),
    m_nDroppedIDCount(0),
    m_nLastID(0),
    m_bFirstFrame(true),
    m_IsDeviceLost(false),
    m_pCAVIFile(NULL),
    ui(new Ui::MdiChildDevice),
    m_pDefectivePixelDetection(nullptr)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

	connect(this, &MdiChildDevice::on_drawingItemSettingChanged, m_pParent, &MainWindow::on_drawingItemSettingChanged);
    connect(this, &MdiChildDevice::on_addOutputLog, m_pParent, &MainWindow::on_addOutputLogTriggered);
    connect(this, &MdiChildDevice::on_removeMdiChild, m_pParent, &MainWindow::on_removeMdiChildTriggered);
    connect(this, &MdiChildDevice::on_closeMdiChild, m_pParent, &MainWindow::on_closeMdiChildTriggered);
    connect(this, &MdiChildDevice::on_dock, m_pParent, &MainWindow::on_dockTriggered);
    connect(this, &MdiChildDevice::on_capturedFirstImage, m_pParent, &MainWindow::on_capturedFirstImage);
}

MdiChildDevice::~MdiChildDevice()
{
    this->StopRecording();

    CConfigurationFile config;

    if (m_pNodeMap)
    {
		if (m_pIStDevice)
		{
			config.SaveNodeMapSettingFile(m_pNodeMap->GetINodeMap(), StConfigurationFileType_NodeMapWnd, m_pIStDevice);
		}
        m_pNodeMap->terminate();
        emit on_dock("NodeMap-" + m_strTitle, nullptr, false);
		delete m_pNodeMap;
		m_pNodeMap = nullptr;
    }

    if (m_pDefectivePixelDetection)
    {
        config.SaveNodeMapSettingFile(m_pDefectivePixelDetection->GetINodeMapForDefectivePixelDetectionFilter(), StConfigurationFileType_DefectivePixelDetection, m_pIStDevice);
        m_pDefectivePixelDetection->terminate();
        emit on_dock("Defective Pixel Detection-" + m_strTitle, nullptr, false);
    }


    if (m_pIStDevice)
    {
        config.SaveNodeMapSettingFile(m_pIStImageDisplayWnd->GetINodeMap(),	StConfigurationFileType_DisplayImageWnd, m_pIStDevice);
        config.SaveNodeMapSettingFile(m_pIStImageDisplayWnd->GetIStPixelFormatConverter()->GetINodeMap(),	StConfigurationFileType_PixelFormatConverter, m_pIStDevice);
        StopImageAcquisition();

        // Stop event acquisition thread before closing "NodeMapView".
        m_pIStDevice->StopEventAcquisitionThread();

        m_pIStDataStream.Reset(NULL);
        m_pIStRegisteredCallbackDeviceLost.Reset(NULL);
        m_pIStDevice.Reset(NULL);
    }

    delete ui;
}

bool MdiChildDevice::openCamera()
{
    bool bRetval = false;

	bRetval = MdiChild::openCamera();
	if (!bRetval) return(bRetval);

    try
    {
		bRetval = false;

        // Open the device.
        m_pIStDevice.Reset(m_pParent->CreateIStDevice());
        if (!m_pIStDevice.IsValid()) return false;

        // Register device lost event.
        GenApi::CNodeMapPtr pINodeMapLocalDevice(
                                m_pIStDevice->GetLocalIStPort()->GetINodeMap());
        if (pINodeMapLocalDevice)
        {
            GenApi::CNodePtr pINodeEventDeviceLost(
                                pINodeMapLocalDevice->GetNode("EventDeviceLost"));
            if (pINodeEventDeviceLost != nullptr)
            {
                m_pIStRegisteredCallbackDeviceLost.Reset(
                    StApi::RegisterCallback(pINodeEventDeviceLost, *this,
                                            &MdiChildDevice::OnDeviceLost, (void*)NULL,
                                            GenApi::cbPostOutsideLock));
            }
        }

        // Start Event Acquisition Thread
        m_pIStDevice->StartEventAcquisitionThread();

        // Create object and get IStDataStream pointer.
        m_pIStDataStream.Reset(m_pIStDevice->CreateIStDataStream(0));
        if (m_pIStDataStream)
        {
            // Register callback function to receive images.
            StApi::RegisterCallback(m_pIStDataStream, *this,
                                    &MdiChildDevice::OnStCallback, (void*)NULL);

        }


        if (CDefectivePixelManager::IsSupported(m_pIStDevice->GetRemoteIStPort()->GetINodeMap()))
        {
            // Create Defective Pixel Detection widget
            m_pDefectivePixelDetection = new WidgetDefectivePixelDetection(
                        m_pIStDevice->GetRemoteIStPort()->GetINodeMap(), this, m_pIStImageDisplayWnd);
            m_objCIStImageCallbackList.Add(m_pDefectivePixelDetection);
        }

        // Display all nodes in the NodeMap widget.
        DisplayGenApiNodes();

        // Set window title based on the camera DisplayName and UserDefinedName.
        m_strTitle = QString("%1[%2]")
                .arg(m_pIStDevice->GetIStDeviceInfo()->GetDisplayName().c_str())
                .arg(m_pIStDevice->GetIStDeviceInfo()->GetUserDefinedName().c_str());
        this->setWindowTitle(m_strTitle);

        // Add NodeMap to dock with visibility = true.
        emit on_dock("NodeMap-" + m_strTitle, (QWidget*)m_pNodeMap, true);

        // Add Graph to dock with initial visibility = false.
        emit on_dock("Graph-" + m_strTitle, (QWidget*)m_pGraphView, false);

        if (CDefectivePixelManager::IsSupported(m_pIStDevice->GetRemoteIStPort()->GetINodeMap()))
        {
            // Add DefectivePixelDetection to dock with initial visibility = false.
            emit on_dock("Defective Pixel Detection-" + m_strTitle, (QWidget*)m_pDefectivePixelDetection, false);
        }

        // Add "device opened" message to log window.
        emit on_addOutputLog(IDS_DEVICE_OPENED, this->m_strDeviceName);

        bRetval = true;
    }
    catch (const GenICam::GenericException &e)
    {
        m_pIStRegisteredCallbackDeviceLost.Reset(NULL);
        m_pIStDataStream.Reset(NULL);
        m_pIStDevice.Reset(NULL);
        OnException(e);
    }
    return bRetval;
}

void MdiChildDevice::GetFPSString(QString &str)
{
    if (m_pIStDataStream)
    {
        // Get the current FPS value.
        double dblFPS = m_pIStDataStream->GetCurrentFPS();

        // Get the current BPS value.
        double dblBPS = m_pIStDataStream->GetCurrentBPS();

        const char *pszUnit[] = { "bps", "kbps", "Mbps", "Gbps", "Tbps"};
        const double dblUnit = 1000.0;
        dblBPS *= 8;
        const double dblThresh = dblUnit * 10;

        size_t iUnitIndex = 0;
        do
        {
            if ((dblBPS <= dblThresh) || (5 <= iUnitIndex))
            {
                break;
            }

            dblBPS /= dblUnit;
            ++iUnitIndex;
        } while (true);

        // Convert to a string.
        str = QString::asprintf("%.2lf[fps] / %.2lf[%s]", dblFPS, dblBPS, pszUnit[iUnitIndex]);
    }
}

void MdiChildDevice::OnDeviceLost(GenApi::INode *pINode, void *)
{
    if (GenApi::IsAvailable(pINode))
    {
        if (m_pIStDevice->IsDeviceLost())
        {
            m_IsDeviceLost = true;
            emit on_addOutputLog(IDS_DEVICE_LOST, this->m_strDeviceName);
            emit on_closeMdiChild(this);
        }
    }
}

void MdiChildDevice::OnStCallback(StApi::IStCallbackParamBase *pIStCallbackParamBase, void *)
{
    try
    {
        StApi::EStCallbackType_t eStCallbackType = pIStCallbackParamBase->GetCallbackType();
        if (eStCallbackType == StApi::StCallbackType_GenTLEvent_DataStreamNewBuffer)
        {
            StApi::IStCallbackParamGenTLEventNewBuffer *pIStCallbackParamGenTLEventNewBuffer =
                    dynamic_cast<StApi::IStCallbackParamGenTLEventNewBuffer*>(pIStCallbackParamBase);
            StApi::IStDataStream *pIStDataStream =
                    pIStCallbackParamGenTLEventNewBuffer->GetIStDataStream();

            // Wait until the data is acquired.
            // If the data has been received, IStStreamBufferReleasable interface
            // pointer is retrieved. When the received data is no longer needed,
            // immediately call the IStStreamBufferReleasable::Release() to return
            // the buffer to the streaming queue.
            // In the destructor of CIStStreamBufferPtr, IStStreamBufferReleasable::Release()
            // is called automatically.
	    StApi::CIStStreamBufferPtr pIStStreamBuffer(pIStDataStream->RetrieveBuffer(0));
            
	    const StApi::IStStreamBufferInfo *pIStStreamBufferInfo = pIStStreamBuffer->GetIStStreamBufferInfo();
	    const uint64_t nFrameID = pIStStreamBufferInfo->GetFrameID();
            if (!m_bFirstFrame)
            {
		    if (m_nLastID < nFrameID)
                    {
			    m_nDroppedIDCount += (nFrameID - m_nLastID - 1);
                    }
            }
            m_nLastID = nFrameID;
            if (pIStStreamBufferInfo->IsIncomplete())
            {
		    ++m_nDroppedIDCount;
            }
	    else
	    {
                ++m_nReceivedImageCount;
	    }
	   
	   if (m_pIStImageDisplayWnd && pIStStreamBufferInfo->IsImagePresent())
            {
                try
                {
                    // Get the IStImage interface pointer to the acquired image data.
                    StApi::IStImage *pIStImage = pIStStreamBuffer->GetIStImage();
#if 0
			printf("Frame[%lu]=0x%p\n", nFrameID, pIStImage->GetImageBuffer());
#endif
                    m_objCIStImageCallbackList.OnIStImage(pIStImage);

					const bool hasImage = m_pIStImageDisplayWnd->HasImage();

                    // Register the image to be displayed.
                    // Registered image is to be copied, the original data is no longer needed.
                    m_pIStImageDisplayWnd->RegisterIStImage(pIStImage);

                    if(!hasImage)
                    {
						emit on_capturedFirstImage();
                    }

                    if(m_pCAVIFile)
                    {
                        GenApi::AutoLock autoLock(m_CLockForAVI);
                        if (m_pCAVIFile)
                        {
                            if (m_pCAVIFile->RegisterIStStreamBuffer(pIStStreamBuffer))
                            {
                                StopRecording();
                            }
                        }
                    }
                }
                catch (...)
                {
                }
            }

        }
        else if (eStCallbackType == StApi::StCallbackType_GenTLEvent_DataStreamError)
        {
            StApi::IStCallbackParamGenTLEventErrorDS *pIStCallbackParamGenTLEventErrorDS =
                    dynamic_cast<StApi::IStCallbackParamGenTLEventErrorDS*>(pIStCallbackParamBase);
            qDebug() << __FILE__ << " line " << __LINE__ << __func__ << pIStCallbackParamGenTLEventErrorDS->GetDescription();
        }
    }
    catch(...)
    {
    }

    m_bFirstFrame = false;
}

void MdiChildDevice::StartImageAcquisition()
{
    StopImageAcquisition();

    try
    {
        // Clear received image count.
        m_nReceivedImageCount = 0;
        m_nDroppedIDCount = 0;
        m_nLastID = 0;
        m_bFirstFrame = true;

        // Start the image acquisition in the host side.
        m_pIStDataStream->StartAcquisition();
        m_IsAcquisitionRunning = true;

        if (m_pIStDevice->GetRemoteIStPort()->GetIStPortInfo()->IsAccessWrite())
        {
            // Start the image acquisition in the camera side.
            m_pIStDevice->AcquisitionStart();
        }
        // Log
        emit on_addOutputLog(IDS_STREAMING_STARTED, this->m_strDeviceName);
    }
    catch(const GenICam::GenericException &e)
    {
        OnException(e);
    }
}

void MdiChildDevice::StopImageAcquisition()
{
    if(!IsAcquisitionRunning()) return;

    if(!m_pIStDevice) return;
    try
    {
        if (!m_IsDeviceLost)
        {
            if (m_pIStDevice->GetRemoteIStPort()->GetIStPortInfo()->IsAccessWrite())
            {
                // Stop the image acquisition in the camera side.
                m_pIStDevice->AcquisitionStop();
            }
            // Log
            emit on_addOutputLog(IDS_STREAMING_STOPPED, this->m_strDeviceName);
        }

        // Stop the image acquisition in the host side.
        m_pIStDataStream->StopAcquisition();

        m_IsAcquisitionRunning = false;
    }
    catch(const GenICam::GenericException &e)
    {
        OnException(e);
    }

}

void MdiChildDevice::StartRecording()
{
    if(m_pCAVIFile  ==  NULL)
    {
        CAVIFileRecorder *pCAVIFile = new CAVIFileRecorder();
        try
        {
            if (!pCAVIFile->Open(m_pIStDevice, m_pIStImageDisplayWnd))
            {
                delete pCAVIFile;
            }
            else
            {
                GenApi::AutoLock autoLock(m_CLockForAVI);
                m_pCAVIFile = pCAVIFile;
            }
        }
        catch (const GenICam::GenericException &e)
        {
            delete pCAVIFile;
            OnException(e);
        }
    }
}

void MdiChildDevice::StopRecording()
{
    GenApi::AutoLock autoLock(m_CLockForAVI);
    if(m_pCAVIFile)
    {        
        delete m_pCAVIFile;
        m_pCAVIFile = NULL;
    }
}

void MdiChildDevice::OnCloseEvent()
{
    // Add log information in case of not device lost
    if (!m_IsDeviceLost) emit on_addOutputLog(IDS_DEVICE_CLOSED, this->m_strDeviceName);
}

void MdiChildDevice::CameraConfigFile(bool isOpenMode)
{
    try
    {
        QString filename = "";
        QString filter = "CFG File(*.cfg)";
        if (isOpenMode)
            filename = QFileDialog::getOpenFileName(
                           nullptr, tr("Open camera config file"), QString(),
                           filter, Q_NULLPTR, QFileDialog::DontUseNativeDialog);
        else
            filename = QFileDialog::getSaveFileName(
                           nullptr, tr("Save camera config file"), QString(),
                           filter, Q_NULLPTR, QFileDialog::DontUseNativeDialog);

        if (filename.length() > 0)
        {            
            if (filename.indexOf("cfg", 0, Qt::CaseInsensitive) == -1) filename += ".cfg";

            const GenICam::gcstring strFileName(filename.toStdString().c_str());
            StApi::CIStFeatureBagPtr pIStFeatureBag(StApi::CreateIStFeatureBag());

            // Get the INodeMap interface pointer for the camera settings.
            GenApi::CNodeMapPtr pINodeMapRemote(
                m_pIStDevice->GetRemoteIStPort()->GetINodeMap());

            if (isOpenMode)
            {
                pIStFeatureBag->StoreFileToBag(strFileName);
                pIStFeatureBag->Load(pINodeMapRemote, true);
            }
            else
            {
                pIStFeatureBag->StoreNodeMapToBag(pINodeMapRemote);
                pIStFeatureBag->SaveToFile(strFileName);
            }
        }
    }
    catch (const GenICam::GenericException &e)
    {
        OnException(e);
    }
}

void MdiChildDevice::SaveCameraDescriptionFile()
{
    try
    {
        // Get the IStPort interface pointer for the remote camera.
        StApi::IStPort *pIStPort = m_pIStDevice->GetRemoteIStPort();

        QString filter = "AllFiles(*.*)";
        QString strFileName = QFileDialog::getSaveFileName(
                                  nullptr, tr("Save camera description file"),
                                  QString(pIStPort->GetXMLFileName().c_str()),
                                  filter, Q_NULLPTR, QFileDialog::DontUseNativeDialog);
        if (strFileName.length() > 0)
        {
            pIStPort->SaveXMLFile(strFileName.toStdString().c_str());
        }
    }
    catch (const GenICam::GenericException &e)
    {
        OnException(e);
    }
}



bool MdiChildDevice::IsFFCCorrectionSupported()
{
    return CCameraSideFFC::IsSupported(m_pIStDevice->GetRemoteIStPort()->GetINodeMap());
}

bool MdiChildDevice::ComputeFFCCorrection()
{
    bool bReval = false;
    try
    {
        const bool isRunning = IsAcquisitionRunning();

        if (isRunning)
        {
            StopImageAcquisition();
        }

        {
            CCameraSideFFC objCCameraSideFFC(m_pIStDevice);
            m_objCIStImageCallbackList.Add(&objCCameraSideFFC);
            try
            {
                StartImageAcquisition();
                objCCameraSideFFC.Wait(30000);
                StopImageAcquisition();

                objCCameraSideFFC.Send();
                bReval = true;
            }
            catch (const GenICam::GenericException &e)
            {
                OnException(e);
            }
            m_objCIStImageCallbackList.Remove(&objCCameraSideFFC);
        }

        if (isRunning)
        {
            StartImageAcquisition();
        }
    }
    catch (const GenICam::GenericException &e)
    {
        OnException(e);
    } 

    return bReval;
}

void MdiChildDevice::DisplayGenApiNodes()
{

    assert(m_pNodeMap != nullptr);

    CConfigurationFile config;
    config.LoadNodeMapSettingFile(m_pIStImageDisplayWnd->GetINodeMap(), StConfigurationFileType_DisplayImageWnd, m_pIStDevice);
    config.LoadNodeMapSettingFile(m_pIStImageDisplayWnd->GetIStPixelFormatConverter()->GetINodeMap(), StConfigurationFileType_PixelFormatConverter, m_pIStDevice);
	config.LoadNodeMapSettingFile(m_pNodeMap->GetINodeMap(), StConfigurationFileType_NodeMapWnd, m_pIStDevice);

    // NodeMap of GigE Interface module for ActionCommand.
    if (m_pIStDevice->GetIStInterface()->GetIStInterfaceInfo()
        ->GetTLType().compare(TLTypeGEVName) == 0)
    {
        GenApi::CNodeMapPtr pINodeMapForInterface(
            m_pIStDevice->GetIStInterface()->GetIStPort()->GetINodeMap());
        GenICam::gcstring strTitle("Interface");
        m_pNodeMap->RegisterINode(
                    pINodeMapForInterface->GetNode("ActionControl"), strTitle);
        m_pNodeMap->RegisterINode(
                    pINodeMapForInterface->GetNode("EventControl"), strTitle);
    }

    // NodeMap of the device local port.
    StApi::IStPort *pIPortLocal = m_pIStDevice->GetLocalIStPort();
    if (pIPortLocal)
    {
        GenApi::CNodeMapPtr pINodeMap(pIPortLocal->GetINodeMap());
        GenICam::gcstring strTitle("Local Device");
        m_pNodeMap->RegisterINode(pINodeMap->GetNode("Root"), strTitle);
    }

    // NodeMap of the device remote port.
    StApi::IStPort *pIPortRemote = m_pIStDevice->GetRemoteIStPort();
    GenApi::CNodeMapPtr pINodeMapRemoteDevice(pIPortRemote->GetINodeMap());
    {
        GenICam::gcstring strTitle("Remote Device");
        m_pNodeMap->RegisterINode(pINodeMapRemoteDevice->GetNode("Root"), strTitle);
    }

    // NodeMap of the data stream port.
    if (m_pIStDataStream)
    {
        StApi::IStPort *pIPortDataStream = m_pIStDataStream->GetIStPort();
        if (pIPortDataStream)
        {
            GenApi::CNodeMapPtr pINodeMap(pIPortDataStream->GetINodeMap());
            GenICam::gcstring strTitle("Data Stream");
            m_pNodeMap->RegisterINode(pINodeMap->GetNode("Root"), strTitle);
        }
    }


    // NodeMap of the Graph Filter.
    GenApi::CNodeMapPtr pINodeMapGraphDataFilter(m_pGraphView->GetINodeMapForGraphDataFilter());
    GenApi::CIntegerPtr pIIntegerSensorWidth(pINodeMapRemoteDevice->GetNode("SensorWidth"));
    GenApi::CIntegerPtr pIIntegerSensorHeight(pINodeMapRemoteDevice->GetNode("SensorHeight"));
    GenApi::CIntegerPtr pIIntegerWidthMax(pINodeMapGraphDataFilter->GetNode("WidthMax"));
    GenApi::CIntegerPtr pIIntegerHeightMax(pINodeMapGraphDataFilter->GetNode("HeightMax"));

    if (GenApi::IsReadable(pIIntegerSensorWidth) && GenApi::IsWritable(pIIntegerWidthMax))
    {
        pIIntegerWidthMax->SetValue(pIIntegerSensorWidth->GetValue());
    }
    if (GenApi::IsReadable(pIIntegerSensorHeight) && GenApi::IsWritable(pIIntegerHeightMax))
    {
        pIIntegerHeightMax->SetValue(pIIntegerSensorHeight->GetValue());
    }


    if (CDefectivePixelManager::IsSupported(pINodeMapRemoteDevice))
    {
        // Nodemap of the Defective Pixel Correction.
        config.LoadNodeMapSettingFile(m_pDefectivePixelDetection->GetINodeMapForDefectivePixelDetectionFilter(), StConfigurationFileType_DefectivePixelDetection, m_pIStDevice);
        m_pNodeMap->RegisterINode(
            m_pDefectivePixelDetection->GetINodeMapForDefectivePixelDetectionFilter()->GetNode("Root"), "Defective Pixel Detection Filter");
    }

	MdiChild::DisplayGenApiNodes();

    m_pNodeMap->RefreshDisplay();
}

void MdiChildDevice::GetStatusBarText(size_t nIndex, QString &strText)
{
	if (nIndex == 0)
	{
		// Image count
		const uint64_t nRcvCount = GetReceivedImageCount();
		const uint64_t nDroppedCount = GetDroppedIDFrameCount();
		strText = QString("Received=%1[Dropped=%2]").arg(nRcvCount).arg(nDroppedCount);
	}
	else if (nIndex == 1)
	{
		// fps
		GetFPSString(strText);
	}
}
