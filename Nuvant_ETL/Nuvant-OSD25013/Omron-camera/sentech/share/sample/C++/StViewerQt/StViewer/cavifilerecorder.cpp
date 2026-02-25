#include "cavifilerecorder.h"
#include "dialogvideoconfiguration.h"

using namespace GenApi;
using namespace StApi;


CAVIFileRecorder::CAVIFileRecorder():
    m_iTimestampOffset(0), m_isFirstFrame(true), m_dblCameraFrameRate(60), m_isNeedToConvBeforeReg(false)
{
}

CAVIFileRecorder::~CAVIFileRecorder()
{
}

bool CAVIFileRecorder::Open(StApi::IStDevice *pIStDevice, StApi::IStImageDisplayWnd *pIStImageDisplayWnd)
{
    // Create a VideoFiler object to get the IStFilerReleasable interface pointer.
    // After the VideoFiler object is no longer needed, IStFilerReleasable::Release()
    // must be called to discard the VideoFiler object.
    // In the destructor of CIStVideoFilerPtr, IStFilerReleasable::Release() is
    // called automatically.
    m_pIStVideoFiler.Reset(StApi::CreateIStFiler(StApi::StFilerType_Video));
	m_pIStPixelFormatConverter.Reset(StApi::CreateIStConverter(StApi::StConverterType_PixelFormat));


	{
		GenApi::CNodeMapPtr pINodeMap_PFConv_Preview(pIStImageDisplayWnd->GetINodeMap());
		GenApi::CNodeMapPtr pINodeMap_PFConv_Save(m_pIStVideoFiler->GetINodeMap());
		{
			pINodeMap_PFConv_Save->GetNode("ColorMap")->ImposeVisibility(Invisible);
		}
		{
			GenApi::CEnumerationPtr pIEnumeration_Preview(pINodeMap_PFConv_Preview->GetNode("ColorMapType"));
			GenApi::CEnumerationPtr pIEnumeration_Save(pINodeMap_PFConv_Save->GetNode("ColorMapType"));
			pIEnumeration_Save->SetIntValue(pIEnumeration_Preview->GetIntValue());
			pIEnumeration_Save->GetNode()->ImposeVisibility(Invisible);
		}
		{
			GenApi::CBooleanPtr pIBoolean_Preview(pINodeMap_PFConv_Preview->GetNode("ColorMapInversion"));
			GenApi::CBooleanPtr pIBoolean_Save(pINodeMap_PFConv_Save->GetNode("ColorMapInversion"));
			pIBoolean_Save->SetValue(pIBoolean_Preview->GetValue());
			pIBoolean_Save->GetNode()->ImposeVisibility(Invisible);
		}
		{
			GenApi::CIntegerPtr pIInteger_Preview(pINodeMap_PFConv_Preview->GetNode("ColorMapPhase"));
			GenApi::CIntegerPtr pIInteger_Save(pINodeMap_PFConv_Save->GetNode("ColorMapPhase"));
			pIInteger_Save->SetValue(pIInteger_Preview->GetValue());
			pIInteger_Save->GetNode()->ImposeVisibility(Invisible);
		}
	}

	{
		IStPixelFormatConverter *pIStPixelFormatConverterForPreview = pIStImageDisplayWnd->GetIStPixelFormatConverter();
		GenApi::CNodeMapPtr pINodeMap_DisplayImage(pIStImageDisplayWnd->GetINodeMap());
		GenApi::CNodeMapPtr pINodeMap_PFConv_Preview(pIStImageDisplayWnd->GetIStPixelFormatConverter()->GetINodeMap());
		GenApi::CNodeMapPtr pINodeMap_PFConv_Save(m_pIStPixelFormatConverter->GetINodeMap());


		GenApi::CEnumerationPtr pIEnumeration_BayerInterpolationMethodForStillImageFile(pINodeMap_DisplayImage->GetNode("BayerInterpolationMethodForStillImageFile"));
		if (pIEnumeration_BayerInterpolationMethodForStillImageFile->GetCurrentEntry()->GetSymbolic().compare("Auto") == 0)
		{
			m_pIStPixelFormatConverter->SetBayerInterpolationMethod(StApi::StBayerInterpolationMethod_BiLinear2);
		}
		else
		{
			m_pIStPixelFormatConverter->SetBayerInterpolationMethod(pIStPixelFormatConverterForPreview->GetBayerInterpolationMethod());
		}

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

		m_pIStPixelFormatConverter->SetGammaValue(pIStPixelFormatConverterForPreview->GetGammaValue());
		m_pIStPixelFormatConverter->SetReverseY(pIStPixelFormatConverterForPreview->GetReverseY());
		m_pIStPixelFormatConverter->SetDestinationPixelFormat(pIStPixelFormatConverterForPreview->GetDestinationPixelFormat());

	}

    // Get the INodeMap interface pointer for the camera settings.
    GenApi::CNodeMapPtr pINodeMapRemote(pIStDevice->GetRemoteIStPort()->GetINodeMap());

    // Get "AcquisitionFrameRate" to estimate frame number from timestamp value.
    GenApi::CFloatPtr pIFloat_AcquisitionFrameRate(
                pINodeMapRemote->GetNode("AcquisitionFrameRate"));
    if(pIFloat_AcquisitionFrameRate)
    {
        m_dblCameraFrameRate = pIFloat_AcquisitionFrameRate->GetValue();
    }
    m_pIStVideoFiler->SetFPS(m_dblCameraFrameRate);

    // Show configuration dialog.
    DialogVideoConfiguration dlg(m_pIStVideoFiler);
    dlg.setModal(true);
    dlg.show();

    return (dlg.exec() == QDialog::Accepted ? true : false);
}

bool CAVIFileRecorder::RegisterIStStreamBuffer(StApi::IStStreamBuffer *pIStStreamBuffer)
{
    // Returned true if AVI file is not opened or already closed.
    if(!(m_pIStVideoFiler)) return true;

	StApi::IStImage *pIStImage = pIStStreamBuffer->GetIStImage();

    // Get timestamp value.
    uint64_t nCurrentTimestampNs = 0;
    try
    {
        nCurrentTimestampNs = pIStStreamBuffer->GetIStStreamBufferInfo()->GetTimestampNS();
    }
    catch (...)
    {
        nCurrentTimestampNs =  pIStStreamBuffer->GetIStStreamBufferInfo()->GetTimestamp();
    }

    // Calculating the frame number in consideration of the frame drop.
    uint32_t nEstimatedFrameNo = 0;
    if(m_isFirstFrame)
    {
        // Initialize timestamp offset value.
        m_iTimestampOffset = nCurrentTimestampNs;
        m_isFirstFrame = false;

		switch (pIStImage->GetImagePixelFormat())
		{
		case(StPFNC_Pol1Mono8):
		case(StPFNC_Pol1MonoX8):
		case(StPFNC_Pol1MonoY8):
		case(StPFNC_Pol1MonoXY8):
		case(StPFNC_Pol1Mono10):
		case(StPFNC_Pol1MonoX10):
		case(StPFNC_Pol1MonoY10):
		case(StPFNC_Pol1MonoXY10):
		case(StPFNC_Pol1Mono12):
		case(StPFNC_Pol1MonoX12):
		case(StPFNC_Pol1MonoY12):
		case(StPFNC_Pol1MonoXY12):
		case(StPFNC_Pol1BayerRG8):
		case(StPFNC_Pol1BayerRGX8):
		case(StPFNC_Pol1BayerRGY8):
		case(StPFNC_Pol1BayerRGXY8):
		case(StPFNC_Pol1BayerRG10):
		case(StPFNC_Pol1BayerRGX10):
		case(StPFNC_Pol1BayerRGY10):
		case(StPFNC_Pol1BayerRGXY10):
		case(StPFNC_Pol1BayerRG12):
		case(StPFNC_Pol1BayerRGX12):
		case(StPFNC_Pol1BayerRGY12):
		case(StPFNC_Pol1BayerRGXY12):
		case(StPFNC_Pol1Mono10p):
		case(StPFNC_Pol1MonoX10p):
		case(StPFNC_Pol1MonoY10p):
		case(StPFNC_Pol1MonoXY10p):
		case(StPFNC_Pol1Mono12p):
		case(StPFNC_Pol1MonoX12p):
		case(StPFNC_Pol1MonoY12p):
		case(StPFNC_Pol1MonoXY12p):
		case(StPFNC_Pol1BayerRG10p):
		case(StPFNC_Pol1BayerRGX10p):
		case(StPFNC_Pol1BayerRGY10p):
		case(StPFNC_Pol1BayerRGXY10p):
		case(StPFNC_Pol1BayerRG12p):
		case(StPFNC_Pol1BayerRGX12p):
		case(StPFNC_Pol1BayerRGY12p):
		case(StPFNC_Pol1BayerRGXY12p):
		case(StPFNC_Pol1MonoC8):
		case(StPFNC_Pol1MonoXC8):
		case(StPFNC_Pol1MonoYC8):
		case(StPFNC_Pol1MonoXYC8):
		case(StPFNC_Pol1MonoC10):
		case(StPFNC_Pol1MonoXC10):
		case(StPFNC_Pol1MonoYC10):
		case(StPFNC_Pol1MonoXYC10):
		case(StPFNC_Pol1MonoC12):
		case(StPFNC_Pol1MonoXC12):
		case(StPFNC_Pol1MonoYC12):
		case(StPFNC_Pol1MonoXYC12):
		case(StPFNC_Pol1BayerRGC8):
		case(StPFNC_Pol1BayerRGXC8):
		case(StPFNC_Pol1BayerRGYC8):
		case(StPFNC_Pol1BayerRGXYC8):
		case(StPFNC_Pol1BayerRGC10):
		case(StPFNC_Pol1BayerRGXC10):
		case(StPFNC_Pol1BayerRGYC10):
		case(StPFNC_Pol1BayerRGXYC10):
		case(StPFNC_Pol1BayerRGC12):
		case(StPFNC_Pol1BayerRGXC12):
		case(StPFNC_Pol1BayerRGYC12):
		case(StPFNC_Pol1BayerRGXYC12):
		case(StPFNC_Pol1MonoC10p):
		case(StPFNC_Pol1MonoXC10p):
		case(StPFNC_Pol1MonoYC10p):
		case(StPFNC_Pol1MonoXYC10p):
		case(StPFNC_Pol1MonoC12p):
		case(StPFNC_Pol1MonoXC12p):
		case(StPFNC_Pol1MonoYC12p):
		case(StPFNC_Pol1MonoXYC12p):
		case(StPFNC_Pol1BayerRGC10p):
		case(StPFNC_Pol1BayerRGXC10p):
		case(StPFNC_Pol1BayerRGYC10p):
		case(StPFNC_Pol1BayerRGXYC10p):
		case(StPFNC_Pol1BayerRGC12p):
		case(StPFNC_Pol1BayerRGXC12p):
		case(StPFNC_Pol1BayerRGYC12p):
		case(StPFNC_Pol1BayerRGXYC12p):
			m_isNeedToConvBeforeReg = true;
			break;
		}
    }
    else
    {
        // Estimate frame number from timestamp value.
        uint64_t nDelta = nCurrentTimestampNs - m_iTimestampOffset;
        double dblTmp = nDelta * m_dblCameraFrameRate;
        dblTmp /= 1000000000;

        nEstimatedFrameNo = (uint32_t)(dblTmp + 0.5);
    }

	if (m_isNeedToConvBeforeReg)
	{
		if (!m_pIStImageBuffer.IsValid())
		{
			m_pIStImageBuffer.Reset(StApi::CreateIStImageBuffer(NULL));
		}
		m_pIStPixelFormatConverter->Convert(pIStImage, m_pIStImageBuffer);
		pIStImage = m_pIStImageBuffer->GetIStImage();
	}

    // Add new frame to the avi file.
	m_pIStVideoFiler->RegisterIStImage(pIStImage, nEstimatedFrameNo);

    return m_pIStVideoFiler->IsStopped();
}
