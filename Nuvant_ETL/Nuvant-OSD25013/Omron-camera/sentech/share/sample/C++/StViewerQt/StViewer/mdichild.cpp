#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>

#include "mdichild.h"
#include "cconfigurationfile.h"

MdiChild::MdiChild(QWidget *parent) :
    QWidget(nullptr),
    m_strDeviceName(""),
	m_strTitle(""),
	m_pParent(static_cast<MainWindow*>(parent)),
    m_pMdi(nullptr),
    m_pNodeMap(nullptr),
    m_pGraphView(nullptr)
{
    setAttribute(Qt::WA_DeleteOnClose);


}

MdiChild::~MdiChild()
{
    if (m_pGraphView)
    {
        m_pGraphView->terminate();
        emit on_dock("Graph-" + m_strTitle, nullptr, false);
		delete m_pGraphView;
		m_pGraphView = nullptr;
    }

	if (m_pIStImageDisplayWnd)
	{
		m_pIStImageDisplayWnd->Close();
		m_pIStImageDisplayWnd.Reset(NULL);
	}
}


bool MdiChild::openCamera()
{
	bool bRetval = false;

	try
	{
		// Create object and get IStImageDisplayWnd pointer.
		m_pIStImageDisplayWnd.Reset(StApi::CreateIStWnd(StApi::StWindowType_ImageDisplay));
		m_pIStImageDisplayWnd->SetVisibleStatusBar(false);
		m_pIStImageDisplayWnd->SetVisibleMenu(false);
#ifdef Q_OS_WIN32
		m_pIStImageDisplayWnd->Show((HWND)this->winId(), StApi::StWindowMode_Child);
#else
		m_pIStImageDisplayWnd->Show(this, StApi::StWindowMode_Child);
#endif
		StApi::RegisterCallback(m_pIStImageDisplayWnd->GetINodeMap()->GetNode("HorizontalGridLineCount"), *this, &MdiChild::OnDrawingItemSettingChanged, (void*)nullptr, GenApi::cbPostInsideLock);
		StApi::RegisterCallback(m_pIStImageDisplayWnd->GetINodeMap()->GetNode("VerticalGridLineCount"), *this, &MdiChild::OnDrawingItemSettingChanged, (void*)nullptr, GenApi::cbPostInsideLock);
		StApi::RegisterCallback(m_pIStImageDisplayWnd->GetINodeMap()->GetNode("DrawingItemType"), *this, &MdiChild::OnDrawingItemSettingChanged, (void*)nullptr, GenApi::cbPostInsideLock);

		// Create Graph widget
		m_pGraphView = new WidgetGraphView(m_pIStImageDisplayWnd, nullptr);

		// Create NodeMap widget
		m_pNodeMap = new WidgetNodeMap(nullptr);

		bRetval = true;
	}
	catch (const GenICam::GenericException &e)
	{
		m_pIStImageDisplayWnd.Reset(NULL);
		OnException(e);
	}
	return bRetval;

}

void MdiChild::setMdiPointer(QMdiSubWindow *mdi)
{
    m_pMdi = mdi;
}


void MdiChild::SaveStillImage()
{
    try
    {
        StApi::CIStImageBufferPtr pIStImageBuffer;
        pIStImageBuffer.Reset(StApi::CreateIStImageBuffer(NULL));

        GetImageToSave(pIStImageBuffer);
        ShowFileDlgAndSaveImage(pIStImageBuffer->GetIStImage());
    }
    catch (const GenICam::GenericException &e)
    {
        OnException(e);
    }
}
bool MdiChild::HasImage() const
{

	return(m_pIStImageDisplayWnd ? m_pIStImageDisplayWnd->HasImage() : false);
}
void MdiChild::GetImageToSave(StApi::IStImageBuffer *pIStImageBuffer)
{
    StApi::CIStImageBufferPtr pIStImageBufferRegistered;
    pIStImageBufferRegistered.Reset(StApi::CreateIStImageBuffer(NULL));

    {
        // Get registered image.
        StApi::IStImage *pIStImageRegisteredTmp =
                m_pIStImageDisplayWnd->GetRegisteredIStImage();
        if (!pIStImageRegisteredTmp) return;

        pIStImageBufferRegistered->CopyImage(pIStImageRegisteredTmp);
    }
    StApi::IStImage *pIStImageRegistered = pIStImageBufferRegistered->GetIStImage();
	const StApi::EStPixelFormatNamingConvention_t eSrcPixelFormat = pIStImageRegistered->GetImagePixelFormat();

	//Get curreng configuration.
	StApi::IStPixelFormatConverter *pIStPixelFormatConverterForPreview = m_pIStImageDisplayWnd->GetIStPixelFormatConverter();

	const StApi::EStPixelFormatNamingConvention_t eDestPixelFormat = pIStPixelFormatConverterForPreview->GetDestinationPixelFormat();


	if (eSrcPixelFormat == eDestPixelFormat)
	{
		pIStImageBuffer->CopyImage(pIStImageRegistered);
	}
	else
	{

		//Convert from a registered image to a preview image.
		StApi::CIStPixelFormatConverterPtr pIStPixelFormatConverter(StApi::CreateIStConverter(StApi::StConverterType_PixelFormat));

		GenApi::CNodeMapPtr pINodeMap_DisplayImage(m_pIStImageDisplayWnd->GetINodeMap());
		GenApi::CNodeMapPtr pINodeMap_PFConv_Preview(pIStPixelFormatConverterForPreview->GetINodeMap());
		GenApi::CNodeMapPtr pINodeMap_PFConv_Save(pIStPixelFormatConverter->GetINodeMap());


		GenApi::CEnumerationPtr pIEnumeration_BayerInterpolationMethodForStillImageFile(pINodeMap_DisplayImage->GetNode("BayerInterpolationMethodForStillImageFile"));
		if (pIEnumeration_BayerInterpolationMethodForStillImageFile->GetCurrentEntry()->GetSymbolic().compare("Auto") == 0)
		{
			pIStPixelFormatConverter->SetBayerInterpolationMethod(StApi::StBayerInterpolationMethod_BiLinear3);
		}
		else
		{
			pIStPixelFormatConverter->SetBayerInterpolationMethod(pIStPixelFormatConverterForPreview->GetBayerInterpolationMethod());
		}

		if (eSrcPixelFormat == StApi::StPFNC_Mono8)
		{
			{
				GenApi::CEnumerationPtr pIEnumeration_Preview(pINodeMap_PFConv_Preview->GetNode("ColorMapType"));
				GenApi::CEnumerationPtr pIEnumeration_Save(pINodeMap_PFConv_Save->GetNode("ColorMapType"));
				pIEnumeration_Save->SetIntValue(pIEnumeration_Preview->GetIntValue());
			}
			{
				GenApi::CBooleanPtr pIBoolean_Preview(pINodeMap_PFConv_Preview->GetNode("ColorMapInversion"));
				GenApi::CBooleanPtr pIBoolean_Save(pINodeMap_PFConv_Save->GetNode("ColorMapInversion"));
				pIBoolean_Save->SetValue(pIBoolean_Preview->GetValue());
			}
			{
				GenApi::CIntegerPtr pIInteger_Preview(pINodeMap_PFConv_Preview->GetNode("ColorMapPhase"));
				GenApi::CIntegerPtr pIInteger_Save(pINodeMap_PFConv_Save->GetNode("ColorMapPhase"));
				pIInteger_Save->SetValue(pIInteger_Preview->GetValue());
			}
		}


		{
			GenApi::CEnumerationPtr pIEnumeration_BitExpansionModeForPreview(pINodeMap_PFConv_Preview->GetNode("BitExpansionMode"));
			GenApi::CEnumerationPtr pIEnumeration_BitExpansionModeForSave(pINodeMap_PFConv_Save->GetNode("BitExpansionMode"));
			pIEnumeration_BitExpansionModeForSave->SetIntValue(pIEnumeration_BitExpansionModeForPreview->GetIntValue());
		}

		{
			GenApi::CEnumerationPtr pIEnumeration_PolarizationImageTransformationMethodForPreview(pINodeMap_PFConv_Preview->GetNode("PolarizationImageTransformationMethod"));
			GenApi::CEnumerationPtr pIEnumeration_PolarizationImageTransformationMethodForSave(pINodeMap_PFConv_Save->GetNode("PolarizationImageTransformationMethod"));
			pIEnumeration_PolarizationImageTransformationMethodForSave->SetIntValue(pIEnumeration_PolarizationImageTransformationMethodForPreview->GetIntValue());
			if (pIEnumeration_PolarizationImageTransformationMethodForSave->GetCurrentEntry()->GetSymbolic().compare("SpecifiedAngle") == 0)
			{
				GenApi::CFloatPtr pIFloat_PolarizationSpecifiedAngleForPreview(pINodeMap_PFConv_Preview->GetNode("PolarizationSpecifiedAngle"));
				GenApi::CFloatPtr pIFloat_PolarizationSpecifiedAngleForSave(pINodeMap_PFConv_Save->GetNode("PolarizationSpecifiedAngle"));
				pIFloat_PolarizationSpecifiedAngleForSave->SetValue(pIFloat_PolarizationSpecifiedAngleForPreview->GetValue());

				GenApi::CFloatPtr pIFloat_PolarizationSpecifiedAngleInterpolationMethodForPreview(pINodeMap_PFConv_Preview->GetNode("PolarizationSpecifiedAngleInterpolationMethod"));
				GenApi::CFloatPtr pIFloat_PolarizationSpecifiedAngleInterpolationMethodForSave(pINodeMap_PFConv_Save->GetNode("PolarizationSpecifiedAngleInterpolationMethod"));
				pIFloat_PolarizationSpecifiedAngleInterpolationMethodForSave->SetValue(pIFloat_PolarizationSpecifiedAngleInterpolationMethodForPreview->GetValue());
			}
			else if (pIEnumeration_PolarizationImageTransformationMethodForSave->GetCurrentEntry()->GetSymbolic().compare("AngleAndDegreeOfLinearPolarization") == 0)
			{
				{
					GenApi::CBooleanPtr pIBoolean_ADOLPDarkModeForPreview(pINodeMap_PFConv_Preview->GetNode("ADOLPDarkMode"));
					GenApi::CBooleanPtr pIBoolean_ADOLPDarkModeForSave(pINodeMap_PFConv_Save->GetNode("ADOLPDarkMode"));
					pIBoolean_ADOLPDarkModeForSave->SetValue(pIBoolean_ADOLPDarkModeForPreview->GetValue());
				}
				{
					GenApi::CBooleanPtr pIBoolean_ADOLPColorInversionForPreview(pINodeMap_PFConv_Preview->GetNode("ADOLPColorInversion"));
					GenApi::CBooleanPtr pIBoolean_ADOLPColorInversionForSave(pINodeMap_PFConv_Save->GetNode("ADOLPColorInversion"));
					pIBoolean_ADOLPColorInversionForSave->SetValue(pIBoolean_ADOLPColorInversionForPreview->GetValue());
				}
				{
					GenApi::CFloatPtr pIFloat_ADOLPColorPhaseForPreview(pINodeMap_PFConv_Preview->GetNode("ADOLPColorPhase"));
					GenApi::CFloatPtr pIFloat_ADOLPColorPhaseForSave(pINodeMap_PFConv_Save->GetNode("ADOLPColorPhase"));
					pIFloat_ADOLPColorPhaseForSave->SetValue(pIFloat_ADOLPColorPhaseForPreview->GetValue());
				}
			}

		}

		pIStPixelFormatConverter->SetGammaValue(pIStPixelFormatConverterForPreview->GetGammaValue());
		pIStPixelFormatConverter->SetReverseY(pIStPixelFormatConverterForPreview->GetReverseY());
		pIStPixelFormatConverter->SetDestinationPixelFormat(eDestPixelFormat);
		pIStPixelFormatConverter->Convert(pIStImageRegistered, pIStImageBuffer);
	}

    if(m_pIStImageDisplayWnd->GetEnableDrawingOnSavingImage())
    {
	    m_pIStImageDisplayWnd->GetIStDrawingTool()->DrawOnIStImageBuffer(pIStImageBuffer);
    }
}

void MdiChild::ShowFileDlgAndSaveImage(StApi::IStImage *pIStImage)
{    
    typedef struct
    {
        const StApi::EStStillImageFileFormat_t eFileType;
        const char *szExt;
        const char *szFilter;
    } SFILE_TYPE, *PSFILE_TYPE;

    SFILE_TYPE psFileTypeList[] = {
        { StApi::StStillImageFileFormat_Bitmap, (".bmp"), ("Bitmap File(*.bmp)") },
        { StApi::StStillImageFileFormat_JPEG, (".jpg"), ("Jpeg File(*.jpg)") },
        { StApi::StStillImageFileFormat_TIFF, (".tif"), ("Tiff File(*.tif)") },
        { StApi::StStillImageFileFormat_PNG, (".png"), ("PNG File(*.png)") },
        { StApi::StStillImageFileFormat_CSV, (".csv"), ("CSV File(*.csv)") },
        { StApi::StStillImageFileFormat_StApiRaw, (".straw"), ("StRaw File(*.straw)") },
    };


	const StApi::EStPixelFormatNamingConvention_t ePixelFormat = pIStImage->GetImagePixelFormat();

    StApi::CIStStillImageFilerPtr pIStStillImageFiler(
        StApi::CreateIStFiler(StApi::StFilerType_StillImage));

    QString strFilters = "";
    for (size_t i = 0; i < 6; ++i)
    {
        PSFILE_TYPE pFileType = &psFileTypeList[i];
        if (pIStStillImageFiler->IsSaveSupported(ePixelFormat, pFileType->eFileType))
        {
            if (strFilters.length() > 0)
                strFilters += ";;";
            strFilters += pFileType->szFilter;
        }
    }
    QString selectedFilter;
    QString strFileName = QFileDialog::getSaveFileName(nullptr, tr("Save Still Image File"), m_pParent->GetLastImagePath(), strFilters, &selectedFilter, QFileDialog::DontUseNativeDialog);
    if (strFileName.length() > 0)
    {
        StApi::EStStillImageFileFormat_t nFileType = StApi::StStillImageFileFormat_Bitmap;
        for (size_t i = 0; i < 6; ++i)
        {
            PSFILE_TYPE pFileType = &psFileTypeList[i];

            if (selectedFilter.compare(pFileType->szFilter,Qt::CaseInsensitive) == 0)
            {
                nFileType = pFileType->eFileType;
                if ((int)strFileName.lastIndexOf(pFileType->szExt, -1, Qt::CaseInsensitive) !=
                        (int)(strFileName.length()-strlen(pFileType->szExt)))
                    strFileName += pFileType->szExt;
                break;
            }
        }
		if (ePixelFormat == StApi::StPFNC_Mono8)
		{
			GenApi::CNodeMapPtr pINodeMap_PFConv_Preview(m_pIStImageDisplayWnd->GetINodeMap());
			GenApi::CNodeMapPtr pINodeMap_PFConv_Save(pIStStillImageFiler->GetINodeMap());

			{
				GenApi::CEnumerationPtr pIEnumeration_Preview(pINodeMap_PFConv_Preview->GetNode("ColorMapType"));
				GenApi::CEnumerationPtr pIEnumeration_Save(pINodeMap_PFConv_Save->GetNode("ColorMapType"));
				pIEnumeration_Save->SetIntValue(pIEnumeration_Preview->GetIntValue());
			}
			{
				GenApi::CBooleanPtr pIBoolean_Preview(pINodeMap_PFConv_Preview->GetNode("ColorMapInversion"));
				GenApi::CBooleanPtr pIBoolean_Save(pINodeMap_PFConv_Save->GetNode("ColorMapInversion"));
				pIBoolean_Save->SetValue(pIBoolean_Preview->GetValue());
			}
			{
				GenApi::CIntegerPtr pIInteger_Preview(pINodeMap_PFConv_Preview->GetNode("ColorMapPhase"));
				GenApi::CIntegerPtr pIInteger_Save(pINodeMap_PFConv_Save->GetNode("ColorMapPhase"));
				pIInteger_Save->SetValue(pIInteger_Preview->GetValue());
			}
		}
        pIStStillImageFiler->Save(pIStImage, nFileType, strFileName.toStdString().c_str());
		m_pParent->SetLastImagePath(strFileName);
    }
}


void MdiChild::closeEvent(QCloseEvent *)
{
    // Inform parent to remove from MDI child listing:
    emit on_removeMdiChild(this->m_pMdi);

	OnCloseEvent();
}

void MdiChild::DisplayGenApiNodes()
{
    assert(m_pNodeMap != nullptr);



    // NodeMap of the ImageDisplayWnd.
    if (m_pIStImageDisplayWnd)
    {
        {
            GenApi::CNodeMapPtr pINodeMap(m_pIStImageDisplayWnd->GetINodeMap());
            GenICam::gcstring strTitle("ImageDisplayWnd");
            m_pNodeMap->RegisterINode(pINodeMap->GetNode("Root"), strTitle);
        }

        {
            GenApi::CNodeMapPtr pINodeMap(m_pIStImageDisplayWnd->
                                          GetIStPixelFormatConverter()->GetINodeMap());
            GenICam::gcstring strTitle("PixelFormatConverter");
            m_pNodeMap->RegisterINode(pINodeMap->GetNode("Root"), strTitle);
        }

    }

    // NodeMap of the NodeMapDisplayWnd.
    m_pNodeMap->RegisterINode(m_pNodeMap->GetINodeMap()->GetNode("Root"), "NodeMapWnd");

    // NodeMap of the Graph Filter.
    GenApi::CNodeMapPtr pINodeMapGraphDataFilter(m_pGraphView->GetINodeMapForGraphDataFilter());
    m_pNodeMap->RegisterINode(pINodeMapGraphDataFilter->GetNode("Root"), "Graph Data Filter");

    // Nodemap of the Graph Display Window.
    m_pNodeMap->RegisterINode(
        m_pGraphView->GetINodeMapForGraphDisplayWnd()->GetNode("Root"), "Graph Display Wnd");



    m_pNodeMap->RefreshDisplay();
}

void MdiChild::GetPixelInfoText(QString &strPixel)
{
	// Pixel Information
	strPixel = "";
	if (m_pIStImageDisplayWnd.IsValid())
	{
#ifdef Q_OS_WIN32
		POINT sPoint;
		GetCursorPos(&sPoint);
		ScreenToClient(m_pIStImageDisplayWnd->GetWindowHandle(), &sPoint);
		QPoint pt(sPoint.x, sPoint.y);
#else
		QPoint pt = static_cast<QWidget *>(
			m_pIStImageDisplayWnd->GetWindowHandle())->mapFromGlobal(QCursor::pos());
#endif
		int nImagePos[] = { pt.x(), pt.y() };
		m_pIStImageDisplayWnd->ScreenToImage(&nImagePos[0], &nImagePos[1]);

		if (nImagePos[0] < 0 || nImagePos[1] < 0) return;

		strPixel = QString("(%1, %2) - ").arg(nImagePos[0]).arg(nImagePos[1]);
		StApi::EStPixelFormatNamingConvention_t ePrevPixelFormat = StApi::StPFNC_Unknown;
		for (size_t i = 0; i < 2; i++)
		{
			if (!m_pIStImageDisplayWnd->HasImage()) break;
			try
			{
				StApi::IStImage *pIStImage =
					(i == 0) ? m_pIStImageDisplayWnd->GetRegisteredIStImage() :
					m_pIStImageDisplayWnd->GetConvertedIStImage();
				if (pIStImage == NULL)
				{
					continue;
				}
				StApi::EStPixelFormatNamingConvention_t ePixelFormat =
					pIStImage->GetImagePixelFormat();

				// Skip second processing if the displayed image is same as the stored image.
				if (ePixelFormat != ePrevPixelFormat)
				{
					ePrevPixelFormat = ePixelFormat;
					if (0 < i) strPixel += " -> ";

					// Get pixel format name.
					StApi::IStPixelFormatInfo *pIStPixelFormatInfo =
						StApi::GetIStPixelFormatInfo(ePixelFormat);
					strPixel += pIStPixelFormatInfo->GetName().c_str();
					strPixel += " : ";

					// Get pixel information.
					StApi::IStPixelComponentValue *pIStPixelComponentValue =
						pIStImage->GetIStPixelComponentValue(nImagePos[0], nImagePos[1]);
					if (pIStPixelComponentValue)
					{
						size_t nCount = pIStPixelComponentValue->GetCount();
						for (size_t j = 0; j < nCount; j++)
						{
							int64_t nValue = pIStPixelComponentValue->GetValue(j);
							StApi::EStPixelComponent_t nPixelComponent =
								pIStPixelComponentValue->GetPixelComponent(j);
							StApi::IStPixelComponentInfo *pIStPixelComponentInfo =
								StApi::GetIStPixelComponentInfo(nPixelComponent);
							if (0 < j)
							{
								strPixel += ",";
							}

							if (pIStPixelFormatInfo->GetName().compare(pIStPixelComponentInfo->GetName()) == 0)
								strPixel += QString("%1").arg(nValue);
							else
								strPixel += QString("%1=%2")
								.arg(pIStPixelComponentInfo->GetName().c_str())
								.arg(nValue);
						}
					}
				}
			}
			catch (...) {}
		}
	}
}
#ifdef Q_OS_WIN32
void MdiChild::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	QRect rect = this->rect();
	m_pIStImageDisplayWnd->SetPosition(0, 0, rect.width(), rect.height());
}
#endif //Q_OS_WIN32


void MdiChild::OnDrawingItemSettingChanged(GenApi::INode *, void*)
{
	emit on_drawingItemSettingChanged();
}
