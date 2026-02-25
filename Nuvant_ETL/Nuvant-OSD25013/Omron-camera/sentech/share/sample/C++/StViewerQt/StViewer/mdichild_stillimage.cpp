#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>
#include "ui_mdichild_stillimage.h"
#include "mdichild_stillimage.h"
#include "cconfigurationfile.h"

MdiChildStillImage::MdiChildStillImage(QWidget *parent) :
	MdiChild(parent),
    ui(new Ui::MdiChildStillImage)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

	connect(this, &MdiChildStillImage::on_drawingItemSettingChanged, m_pParent, &MainWindow::on_drawingItemSettingChanged);
    connect(this, &MdiChildStillImage::on_addOutputLog, m_pParent, &MainWindow::on_addOutputLogTriggered);
    connect(this, &MdiChildStillImage::on_removeMdiChild, m_pParent, &MainWindow::on_removeMdiChildTriggered);
    connect(this, &MdiChildStillImage::on_closeMdiChild, m_pParent, &MainWindow::on_closeMdiChildTriggered);
    connect(this, &MdiChildStillImage::on_dock, m_pParent, &MainWindow::on_dockTriggered);
}

MdiChildStillImage::~MdiChildStillImage()
{
    CConfigurationFile config;

    if (m_pNodeMap)
    {
		if (!m_strTitle.isEmpty())
		{
			config.SaveNodeMapSettingFile(m_pNodeMap->GetINodeMap(), StConfigurationFileType_NodeMapWnd, m_strTitle);
		}
        m_pNodeMap->terminate();
        emit on_dock("NodeMap-" + m_strTitle, nullptr, false);
		delete m_pNodeMap;
		m_pNodeMap = nullptr;
    }

	if (m_pIStImageDisplayWnd)
	{
		if (!m_strTitle.isEmpty())
		{
			config.SaveNodeMapSettingFile(m_pIStImageDisplayWnd->GetINodeMap(), StConfigurationFileType_DisplayImageWnd, m_strTitle);
            config.SaveNodeMapSettingFile(m_pIStImageDisplayWnd->GetIStPixelFormatConverter()->GetINodeMap(), StConfigurationFileType_PixelFormatConverter, m_strTitle);
		}
	}

    delete ui;
}

bool MdiChildStillImage::openCamera()
{
	const QString strFilters = "Image File(*.png *.bmp *.straw)";
	const QString strFileName = QFileDialog::getOpenFileName(nullptr, tr("Open Still Image File"), m_pParent->GetLastImagePath(),	strFilters, nullptr, QFileDialog::DontUseNativeDialog);
    return openCamera(strFileName);
}

bool MdiChildStillImage::openCamera(const QString &strFileName)
{
	bool bRetval = false;

	if (strFileName.length() <= 0)
	{
		return(false);
	}

	bRetval = MdiChild::openCamera();
	if (!bRetval) return(bRetval);

	try
	{
		bRetval = false;

		StApi::CIStImageBufferPtr pIStImageBuffer(StApi::CreateIStImageBuffer());
		StApi::CIStStillImageFilerPtr pIStStillImageFiler(
			StApi::CreateIStFiler(StApi::StFilerType_StillImage));
		
		pIStStillImageFiler->Load(pIStImageBuffer, strFileName.toStdString().c_str());
		m_pParent->SetLastImagePath(strFileName);
		m_strDeviceName = strFileName;
		
		QFileInfo objFileInfo(strFileName);
		m_strUpdateTime = objFileInfo.lastModified().toString("yyyy/MM/dd HH:mm:ss");
		
		m_pIStImageDisplayWnd->RegisterIStImage(pIStImageBuffer->GetIStImage());

		// Set window title based on the camera DisplayName and UserDefinedName.
		m_strTitle = objFileInfo.fileName();
		this->setWindowTitle(m_strTitle);

		// Display all nodes in the NodeMap widget.
		DisplayGenApiNodes();

		// Add NodeMap to dock with visibility = true.
		emit on_dock("NodeMap-" + m_strTitle, (QWidget*)m_pNodeMap, true);

		// Add Graph to dock with initial visibility = false.
		emit on_dock("Graph-" + m_strTitle, (QWidget*)m_pGraphView, false);

		// Add "device opened" message to log window.
		emit on_addOutputLog(IDS_IMAGE_FILE_OPENED, this->m_strDeviceName);

		bRetval = true;
	}
	catch (const GenICam::GenericException &e)
	{
		OnException(e);
	}
	return bRetval;
}

void MdiChildStillImage::OnCloseEvent()
{
    // Add log information in case of not device lost
    emit on_addOutputLog(IDS_DEVICE_CLOSED, this->m_strDeviceName);
}

void MdiChildStillImage::DisplayGenApiNodes()
{
    assert(m_pNodeMap != nullptr);

	CConfigurationFile config;
	config.LoadNodeMapSettingFile(m_pIStImageDisplayWnd->GetINodeMap(), StConfigurationFileType_DisplayImageWnd, m_strTitle);
    config.LoadNodeMapSettingFile(m_pIStImageDisplayWnd->GetIStPixelFormatConverter()->GetINodeMap(), StConfigurationFileType_PixelFormatConverter, m_strTitle);
	config.LoadNodeMapSettingFile(m_pNodeMap->GetINodeMap(), StConfigurationFileType_NodeMapWnd, m_strTitle);

	StApi::IStImage *pIStImage = m_pIStImageDisplayWnd->GetRegisteredIStImage();

    // NodeMap of the Graph Filter.
    GenApi::CNodeMapPtr pINodeMapGraphDataFilter(m_pGraphView->GetINodeMapForGraphDataFilter());
    GenApi::CIntegerPtr pIIntegerWidthMax(pINodeMapGraphDataFilter->GetNode("WidthMax"));
    GenApi::CIntegerPtr pIIntegerHeightMax(pINodeMapGraphDataFilter->GetNode("HeightMax"));

    if (GenApi::IsWritable(pIIntegerWidthMax))
    {
        pIIntegerWidthMax->SetValue(pIStImage->GetImageWidth());
    }
    if (GenApi::IsWritable(pIIntegerHeightMax))
    {
        pIIntegerHeightMax->SetValue(pIStImage->GetImageHeight());
    }

	MdiChild::DisplayGenApiNodes();

    m_pNodeMap->RefreshDisplay();
}

void MdiChildStillImage::GetStatusBarText(size_t nIndex, QString &strText)
{
	if (nIndex == 0)
	{
		strText = m_strTitle;
	}
	else if (nIndex == 1)
	{
		strText = m_strUpdateTime;
	}
}
