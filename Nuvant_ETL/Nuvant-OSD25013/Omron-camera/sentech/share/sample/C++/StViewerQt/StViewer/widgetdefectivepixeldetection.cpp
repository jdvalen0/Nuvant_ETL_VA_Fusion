#include "widgetdefectivepixeldetection.h"
#include "ui_widgetdefectivepixeldetection.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>

WidgetDefectivePixelDetection::WidgetDefectivePixelDetection(
        GenApi::INodeMap *pINodeMap, IStreamingCtrl *pIStreamingCtrl,
        StApi::IStImageDisplayWnd *pIStImageDisplayWnd, QWidget *parent):
    QWidget(parent),
    ui(new Ui::WidgetDefectivePixelDetection),
    m_toolbarDefectivePixelDetection("Defective Pixel Detection", this),
    m_actionDetect("Detect", &m_toolbarDefectivePixelDetection),
    m_actionClear("Clear", &m_toolbarDefectivePixelDetection),
    m_actionRegister("Register", &m_toolbarDefectivePixelDetection),
    m_actionDeregister("Deregister", &m_toolbarDefectivePixelDetection),
    m_actionRefresh("Refresh", &m_toolbarDefectivePixelDetection),
    m_actionSaveImage("Save Image", &m_toolbarDefectivePixelDetection),
    m_actionHighlight("Highlight", &m_toolbarDefectivePixelDetection),
    m_actionEnabledCorrection("Enabled Correction", &m_toolbarDefectivePixelDetection),
    m_pIStreamingCtrl(pIStreamingCtrl),
    m_pIStImageAveragingFilter(StApi::CreateIStFilter(StApi::StFilterType_ImageAveraging)),
    m_pIStImageBuffer(StApi::CreateIStImageBuffer()),
    m_nRcvedFrameCount(SIZE_MAX),
    m_nFrameCount(10),
    m_bSaveAveragedImage(false),
    m_objCDefectivePixelManager(pINodeMap, pIStImageDisplayWnd),
    m_ModelDefectivePixel(&m_objCDefectivePixelManager),
    m_pIBoolean_PixelCorrectionAllEnabled(pINodeMap->GetNode("PixelCorrectionAllEnabled")),
    m_pIFloat_AcquisitionFrameRate(pINodeMap->GetNode("AcquisitionFrameRate")),
    m_pIFloat_ExposureTime(pINodeMap->GetNode("ExposureTime")),
    m_qstrLastSavedImagePath(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)),
    m_bImageDone(false), m_bFirstTime(true)
{
    ui->setupUi(this);

    std::vector<QAction*> actionList = {
        &m_actionDetect,
        &m_actionClear,
        &m_actionRegister,
        &m_actionDeregister,
        &m_actionRefresh,
        &m_actionSaveImage,
        &m_actionHighlight,
        &m_actionEnabledCorrection
    };
    std::vector<const char *> actionTooltip = {
        "Start detecting defective pixel.\n"
            "When the number of defective pixels exceeds the detectable number, the\n"
            "pixels with a poor evaluation value are left preferentially.",
            "Clear detected defective pixel information.",
        "Register selecting defective pixel information to the camera.\n"
        "The number of defective pixels actually registered is limited to the number\n"
            "of defective pixels that can be registered with the camera. If you want the\n"
            "defective pixel registration to be valid after the power is turned on again,\n"
            "execute ""UserSetSave"" additionally.",
        "Deregister selecting defective pixel information from the camera.\n"
            "To enable the unregistration of defective pixels even after the power supply\n"
            "is turned on again, execute ""UserSetSave"" additionally.",
        "Refresh registered defective pixels information.",
        "Saves the averaged monochrome image used to detect the defective pixels.",
        "Defective pixel highlighting (Overlay).",
        "Enabled defective pixel correction.\n"
		"Some cameras cannot enable or disable defect pixel correction during streaming."
    };
    QPixmap iconPixmap(":/icon/res/DefectivePixelDetection256.png");

    for (size_t i = 0; i < actionList.size(); i++)
    {
        QIcon icon;
        QAction *act = actionList[i];
        icon.addPixmap(iconPixmap.copy(i * 16, 0, 16, 16));
        act->setIcon(icon);
        act->setToolTip(QString(actionTooltip[i]));
        if (i > 4) // SaveImage, Highlight, and Enabled Correction are checkable.
        {
            act->setCheckable(true);
            act->setChecked(false);
        }
        m_toolbarDefectivePixelDetection.addAction(act);
    }
    connect(&m_actionDetect, &QAction::triggered, this, &WidgetDefectivePixelDetection::on_actionDetectTriggered);
    connect(&m_actionClear, &QAction::triggered, this, &WidgetDefectivePixelDetection::on_actionClearTriggered);
    connect(&m_actionRegister, &QAction::triggered, this, &WidgetDefectivePixelDetection::on_actionRegisterTriggered);
    connect(&m_actionDeregister, &QAction::triggered, this, &WidgetDefectivePixelDetection::on_actionDeregisterTriggered);
    connect(&m_actionRefresh, &QAction::triggered, this, &WidgetDefectivePixelDetection::on_actionRefreshTriggered);
    connect(&m_actionSaveImage, &QAction::triggered, this, &WidgetDefectivePixelDetection::on_actionSaveImageTriggered);
    connect(&m_actionHighlight, &QAction::triggered, this, &WidgetDefectivePixelDetection::on_actionHighlightTriggered);
    connect(&m_actionEnabledCorrection, &QAction::triggered, this, &WidgetDefectivePixelDetection::on_actionEnabledCorrectionTriggered);

    m_actionEnabledCorrection.setEnabled(GenApi::IsWritable(m_pIBoolean_PixelCorrectionAllEnabled));
    m_actionClear.setEnabled(0 < m_objCDefectivePixelManager.GetDetectedDefectivePixelCount());
    m_actionDeregister.setEnabled(false);
    m_actionRegister.setEnabled(false);

    ui->layoutToolBar->addWidget(&m_toolbarDefectivePixelDetection);

    m_proxy.setSourceModel(&m_ModelDefectivePixel);
    m_proxy.setSortRole(Qt::InitialSortOrderRole);

    ui->tableView->setModel(&m_proxy);

    QItemSelectionModel *sm = ui->tableView->selectionModel();
    connect(sm, &QItemSelectionModel::selectionChanged,
                this, &WidgetDefectivePixelDetection::on_tableViewSelectionChanged);

    try
    {
        GenApi::CNodePtr node(pINodeMap->GetNode("PixelCorrectionAllEnabled"));
        m_pIStRegisteredCallbackPixelCorrectionAllEnabled.Reset(
            StApi::RegisterCallback(node, *this, &WidgetDefectivePixelDetection::OnNodeCallback,
            (void*)NULL, GenApi::cbPostOutsideLock));

        m_objCDefectivePixelManager.GetRegisteredDefectivePixelList();
        m_ModelDefectivePixel.UpdateDefectivePixelList();
    }
    catch(...)
    {
        // Exception happens if the device is opened read only.
        m_pIStRegisteredCallbackPixelCorrectionAllEnabled.Reset(NULL);
    }

	connect(this, &WidgetDefectivePixelDetection::SetEnabledCorrectionChecked, this, &WidgetDefectivePixelDetection::OnSetEnabledCorrectionChecked);
	connect(this, &WidgetDefectivePixelDetection::SetEnabledCorrectionEnabled, this, &WidgetDefectivePixelDetection::OnSetEnabledCorrectionEnabled);
}

WidgetDefectivePixelDetection::~WidgetDefectivePixelDetection()
{
    terminate();
    delete ui;
}

void WidgetDefectivePixelDetection::OnIStImage(StApi::IStImage *pIStImage)
{
    m_mutexImageDone.lock();
    try
    {
        if (m_nRcvedFrameCount < m_nFrameCount)
        {

            m_pIStImageAveragingFilter->Filter(pIStImage);

            if (++m_nRcvedFrameCount == m_nFrameCount)
            {
                m_bImageDone = true;
            }
        }
    }
    catch (...)
    {
    }
    m_mutexImageDone.unlock();
}

void WidgetDefectivePixelDetection::terminate()
{
    m_pIStRegisteredCallbackPixelCorrectionAllEnabled.Reset(NULL);
    m_objCDefectivePixelManager.SetHighlight(false);
    m_pIStImageAveragingFilter.Reset(NULL);
}

void WidgetDefectivePixelDetection::on_actionDetectTriggered(bool)
{
    QString message = "Click the [OK] button in a shaded or uniform subject. If you click the [OK] button while shooting a non-uniform subject, normal pixels will be detected as defective pixels, and detection will take longer.";
    if (QMessageBox::Cancel ==  QMessageBox::question(nullptr, "Confirmation", message, QMessageBox::Ok|QMessageBox::Cancel)) return;

    try
    {
        m_pIStImageAveragingFilter->ClearImageData();

        m_bImageDone = false;

        m_nRcvedFrameCount = 0;

        const bool isRunning = m_pIStreamingCtrl->IsAcquisitionRunning();
        if (!isRunning)
        {
            m_pIStreamingCtrl->StartImageAcquisition();
        }

        ui->labelStatus->setText("During image acquisition.");
        QApplication::processEvents();

        const double dblExposureTimeMs = IsReadable(m_pIFloat_ExposureTime) ? m_pIFloat_ExposureTime->GetValue() / 1000 : 0;
        const double dblAcquisitionFrameTimeMs = IsReadable(m_pIFloat_AcquisitionFrameRate) ? 1000.0 / m_pIFloat_AcquisitionFrameRate->GetValue() : 0;
		const double dblMaxFrameTime = (std::max)(dblExposureTimeMs, dblAcquisitionFrameTimeMs);
        const uint32_t dwTotalTimeout = 1000 + (uint32_t)(dblMaxFrameTime * (m_nFrameCount + 1) * 1.5);
        this->Wait(dwTotalTimeout);

        if (!isRunning)
        {
            m_pIStreamingCtrl->StopImageAcquisition();
        }

        m_pIStImageAveragingFilter->GetAveragedImage(m_pIStImageBuffer);

        ui->labelStatus->setText("Detecting defective pixels.");
        QApplication::processEvents();
        m_objCDefectivePixelManager.DetectDefectivePixel(m_pIStImageBuffer->GetIStImage());
        m_ModelDefectivePixel.UpdateDefectivePixelList();
	m_actionClear.setEnabled(0 < m_objCDefectivePixelManager.GetDetectedDefectivePixelCount());

        if (m_bSaveAveragedImage)
        {
            QString filename = QFileDialog::getSaveFileName(nullptr, tr("Save Still Image File"),
                            m_qstrLastSavedImagePath, "Bitmap File(*.bmp)", Q_NULLPTR, QFileDialog::DontUseNativeDialog);

            if (filename.length() > 0)
            {
                if (filename.lastIndexOf(".bmp", -1, Qt::CaseInsensitive) != filename.length()-4)
                    filename += ".bmp";

                GenICam::gcstring strFileName(filename.toStdString().c_str());
                SaveImage(m_pIStImageBuffer->GetIStImage(), strFileName);

				m_qstrLastSavedImagePath = QFileInfo(filename).path();
            }
        }

        ui->labelStatus->setText("Defective pixel detection completed.");
        QApplication::processEvents();
    }
    catch (const GenICam::GenericException &e)
    {
        OnException(e);
        const GenICam::gcstring strMsg(e.GetDescription());
#ifdef Q_OS_WIN32
        ui->labelStatus->setText(strMsg.c_str());
#else
        ui->labelStatus->setText(GCSTRING_2_LPCTSTR(strMsg));
#endif
    }
}

void WidgetDefectivePixelDetection::on_actionClearTriggered(bool)
{
    try
    {
        m_objCDefectivePixelManager.ClearDetectedPixelList();
        m_ModelDefectivePixel.UpdateDefectivePixelList();
    	m_actionClear.setEnabled(0 < m_objCDefectivePixelManager.GetDetectedDefectivePixelCount());
    }
    catch (const GenICam::GenericException &e)
    {
        OnException(e);
    }
}

void WidgetDefectivePixelDetection::on_actionRegisterTriggered(bool)
{
    const bool isRunning = m_pIStreamingCtrl->IsAcquisitionRunning();
    if (isRunning)
    {
        m_pIStreamingCtrl->StopImageAcquisition();
    }

    m_ModelDefectivePixel.RegisterSelectedPixel();

    if (isRunning)
    {
        m_pIStreamingCtrl->StartImageAcquisition();
    }
}

void WidgetDefectivePixelDetection::on_actionDeregisterTriggered(bool)
{
    const bool isRunning = m_pIStreamingCtrl->IsAcquisitionRunning();
    if (isRunning)
    {
        m_pIStreamingCtrl->StopImageAcquisition();
    }

    m_ModelDefectivePixel.DeregisterSelectedPixel();

    if (isRunning)
    {
        m_pIStreamingCtrl->StartImageAcquisition();
    }
}

void WidgetDefectivePixelDetection::on_actionRefreshTriggered(bool)
{
    const bool isRunning = m_pIStreamingCtrl->IsAcquisitionRunning();
    if (isRunning)
    {
        m_pIStreamingCtrl->StopImageAcquisition();
    }
    m_objCDefectivePixelManager.GetRegisteredDefectivePixelList();
    m_ModelDefectivePixel.UpdateDefectivePixelList();

    if (isRunning)
    {
        m_pIStreamingCtrl->StartImageAcquisition();
    }
}

void WidgetDefectivePixelDetection::on_actionSaveImageTriggered(bool)
{
    m_bSaveAveragedImage = !m_bSaveAveragedImage;
}

void WidgetDefectivePixelDetection::on_actionHighlightTriggered(bool)
{
    m_objCDefectivePixelManager.SetHighlight(!m_objCDefectivePixelManager.GetHighlight());
}

void WidgetDefectivePixelDetection::on_actionEnabledCorrectionTriggered(bool)
{
    if (GenApi::IsWritable(m_pIBoolean_PixelCorrectionAllEnabled))
    {
        m_pIBoolean_PixelCorrectionAllEnabled->SetValue(!m_pIBoolean_PixelCorrectionAllEnabled->GetValue());
    }
}

void WidgetDefectivePixelDetection::on_tableViewSelectionChanged(const QItemSelection &/*selected*/, const QItemSelection & /*deselected*/)
{
    std::vector<size_t> rows;
    int selectedCount = ui->tableView->selectionModel()->selectedRows().count();
    for (int i = 0; i < selectedCount; i++)
    {
        QModelIndex sourceIndex = m_proxy.mapToSource(
                    ui->tableView->selectionModel()->selectedRows().at(i));
        int row = sourceIndex.row();
        rows.push_back(row);
    }
    m_ModelDefectivePixel.SetSelectedList(rows);

    m_actionDeregister.setEnabled(0 < m_ModelDefectivePixel.GetSelectedRegisteredItemCount());
    m_actionRegister.setEnabled(0 < m_ModelDefectivePixel.GetSelectedNotRegisteredItemCount());
}

void WidgetDefectivePixelDetection::SaveImage(StApi::IStImage *pIStImage, GenICam::gcstring &strFileName)
{
    StApi::CIStImageBufferPtr pIStImageBuffer;
    if (pIStImage->GetImagePixelFormat() != StApi::StPFNC_Mono8)
    {
        pIStImageBuffer = StApi::CreateIStImageBuffer();

        StApi::CIStPixelFormatConverterPtr pIStPixelFormatConverter(StApi::CreateIStConverter(StApi::StConverterType_PixelFormat));
        pIStPixelFormatConverter->SetDestinationPixelFormat(StApi::StPFNC_Mono8);
        pIStPixelFormatConverter->SetBayerInterpolationMethod(StApi::StBayerInterpolationMethod_Mono);
        pIStPixelFormatConverter->Convert(pIStImage, pIStImageBuffer);
        pIStImage = pIStImageBuffer->GetIStImage();
    }

    StApi::CIStStillImageFilerPtr pIStStillImageFiler(StApi::CreateIStFiler(StApi::StFilerType_StillImage));
    pIStStillImageFiler->Save(pIStImage, StApi::StStillImageFileFormat_Bitmap, strFileName);
}

void WidgetDefectivePixelDetection::Wait(uint32_t waitms)
{
    m_mutexImageDone.lock();
    m_bImageDone = false;
    m_waitConditionImageDone.wait(&m_mutexImageDone, waitms);
    bool result = m_bImageDone;
    m_mutexImageDone.unlock();
    if (!result)
    {
        throw RUNTIME_EXCEPTION("Timeout");
    }
}
