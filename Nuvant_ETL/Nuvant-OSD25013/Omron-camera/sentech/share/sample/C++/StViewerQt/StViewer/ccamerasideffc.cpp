#include "StApi_IP.h"
#include "ccamerasideffc.h"

using namespace StApi;
using namespace GenApi;
CCameraSideFFC::CCameraSideFFC(StApi::IStDevice *pIStDevice) : 
    m_pIStDevice(pIStDevice), 
    m_pIStImageAveragingFilter(CreateIStFilter(StFilterType_ImageAveraging)),
    m_pIStImageBuffer(CreateIStImageBuffer()),
    m_dblBackLevelValue(0),
    m_nFrameCount(50), 
    m_nRcvedFrameCount(0), 
    m_pINodeMap(pIStDevice->GetRemoteIStPort()->GetINodeMap()),
    m_pIIntegerFFCMeshWidth(m_pINodeMap->GetNode("FFCMeshWidth")),
    m_pIIntegerFFCMeshHeight(m_pINodeMap->GetNode("FFCMeshHeight")),
    m_pIBooleanFFCEnable(m_pINodeMap->GetNode("FFCEnable")),
    m_pIIntegerFFCIndex(m_pINodeMap->GetNode("FFCIndex")),
    m_pIIntegerFFCValue(m_pINodeMap->GetNode("FFCValue")),
    m_pIRegisterFFCValueAll(m_pINodeMap->GetNode("FFCValueAll")),
    m_pIEnumerationDeviceRegistersEndianness(m_pINodeMap->GetNode("DeviceRegistersEndianness")),
    m_bImageDone(false)
{
    CIntegerPtr pIIntegerWidthMax(m_pINodeMap->GetNode("WidthMax"));
    m_nImageWidthMax = (size_t)pIIntegerWidthMax->GetValue();

    CIntegerPtr pIIntegerHeightMax(m_pINodeMap->GetNode("HeightMax"));
    m_nImageHeightMax = (size_t)pIIntegerHeightMax->GetValue();


    const size_t nMeshWidth = (size_t)m_pIIntegerFFCMeshWidth->GetValue();
    const size_t nMeshHeight = (size_t)m_pIIntegerFFCMeshHeight->GetValue();

    m_nAreaCountX = (size_t)((m_nImageWidthMax + nMeshWidth - 1) / nMeshWidth);
    m_nAreaCountY = (size_t)((m_nImageHeightMax + nMeshHeight - 1) / nMeshHeight);
    m_nAreaCount = m_nAreaCountX * m_nAreaCountY;

    m_pIBooleanFFCEnable->SetValue(false);
    m_nMaxGainValue = m_pIIntegerFFCValue->GetMax();

    CFloatPtr pIFloat_BlackLevel(m_pINodeMap->GetNode("BlackLevel"));
    if (IsReadable(pIFloat_BlackLevel))
    {
        m_dblBackLevelValue = pIFloat_BlackLevel->GetValue();
    }
}

CCameraSideFFC::~CCameraSideFFC()
{
}

bool CCameraSideFFC::IsSupported(CNodeMapPtr pINodeMap)
{
    try
    {
        CEnumerationPtr pIEnumeration_FFCType(pINodeMap->GetNode("FFCType"));
        CEnumerationPtr pIEnumeration_FFCSelector(pINodeMap->GetNode("FFCSelector"));

        if(IsImplemented(pIEnumeration_FFCType) && IsImplemented(pIEnumeration_FFCSelector))
	{
	        return(
	            (pIEnumeration_FFCType->GetCurrentEntry()->GetSymbolic().compare("Mesh") == 0) &&
        	    (pIEnumeration_FFCSelector->GetCurrentEntry()->GetSymbolic().compare("Gain") == 0)
	            );
	}
    }
    catch (...)
    {
    }
    return(false);
}

void CCameraSideFFC::OnIStImage(StApi::IStImage *pIStImage)
{
    m_mutexImageDone.lock();
    try
    {
        if (m_nRcvedFrameCount < m_nFrameCount)
        {
            m_pIStImageAveragingFilter->Filter(pIStImage);

            if (++m_nRcvedFrameCount == m_nFrameCount)
            {
                m_pIStImageAveragingFilter->GetAveragedImage(m_pIStImageBuffer, 16);
                m_bImageDone = true;
            }
        }
    }
    catch (...)
    {
    }
    m_mutexImageDone.unlock();
}

void CCameraSideFFC::Wait(uint32_t waitms)
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

void CCameraSideFFC::Send()
{
    const IStImage *pIStImage =  m_pIStImageBuffer->GetIStImage();
    const EStPixelFormatNamingConvention_t ePFNC = pIStImage->GetImagePixelFormat();
    const StApi::IStPixelFormatInfo *pIStPixelFormatInfo = GetIStPixelFormatInfo(ePFNC);

    if (pIStPixelFormatInfo->GetEachComponentValidBitCount() <= 8)
    {
        if (m_nMaxGainValue < 256)
        {
            mSend<uint8_t, uint8_t>(pIStPixelFormatInfo);
        }
        else
        {
            mSend<uint8_t, uint16_t>(pIStPixelFormatInfo);
        }
    }
    else
    {
        if (m_nMaxGainValue < 256)
        {
            mSend<uint16_t, uint8_t>(pIStPixelFormatInfo);
        }
        else
        {
            mSend<uint16_t, uint16_t>(pIStPixelFormatInfo);
        }
    }
}


