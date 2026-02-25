#include "cdefectivepixelmanager.h"

#include <QPainter>
#include <QColor>
#include <QPen>
#include <QBrush>

using namespace StApi;
using namespace GenApi;

CDefectivePixelManager::CDefectivePixelManager(GenApi::INodeMap *pINodeMap, StApi::IStImageDisplayWnd *pIStImageDisplayWnd) :
    m_pINodeMap_RemoteDevice(pINodeMap),
    m_pIStImageDisplayWnd(pIStImageDisplayWnd),
    m_pIBoolean_PixelCorrectionAllEnabled(m_pINodeMap_RemoteDevice->GetNode("PixelCorrectionAllEnabled")),
    m_pIInteger_PixelCorrectionIndex(m_pINodeMap_RemoteDevice->GetNode("PixelCorrectionIndex")),
    m_pIBoolean_PixelCorrectionEnabled(m_pINodeMap_RemoteDevice->GetNode("PixelCorrectionEnabled")),
    m_pIInteger_PixelCorrectionX(m_pINodeMap_RemoteDevice->GetNode("PixelCorrectionX")),
    m_pIInteger_PixelCorrectionY(m_pINodeMap_RemoteDevice->GetNode("PixelCorrectionY")),
    m_pIStDefectivePixelDetectionFilter(StApi::CreateIStFilter(StApi::StFilterType_DefectivePixelDetection)),
    m_pINodeMap_DefectivePixelDetectionFilter(m_pIStDefectivePixelDetectionFilter->GetINodeMap()),
    m_pIEnumeration_ExpectedPixelFormat(m_pINodeMap_DefectivePixelDetectionFilter->GetNode("ExpectedPixelFormat")),
    m_pIInteger_MaximumPixelCountToDetect(m_pINodeMap_DefectivePixelDetectionFilter->GetNode("MaximumPixelCountToDetect"))
{
    CEnumerationPtr pIEnumeration_PixelFormat(pINodeMap->GetNode("PixelFormat"));
    RegisterCallback(pIEnumeration_PixelFormat->GetNode(), *this, &CDefectivePixelManager::OnPixelFormatMayBeChanged, (void*)NULL, cbPostOutsideLock);
    try
    {
        m_pIEnumeration_ExpectedPixelFormat->SetIntValue(pIEnumeration_PixelFormat->GetIntValue());
        if (IsReadable(m_pIInteger_PixelCorrectionIndex))
        {
            m_pIInteger_MaximumPixelCountToDetect->SetValue(m_pIInteger_PixelCorrectionIndex->GetMax() - m_pIInteger_PixelCorrectionIndex->GetMin() + 1);
        }
    }
    catch (...)
    {
    }
}


CDefectivePixelManager::~CDefectivePixelManager()
{

}

bool CDefectivePixelManager::IsSupported(GenApi::INodeMap *pINodemap)
{
    return (
        IsImplemented(pINodemap->GetNode("PixelCorrectionAllEnabled")) &&
        IsImplemented(pINodemap->GetNode("PixelCorrectionIndex")) &&
        IsImplemented(pINodemap->GetNode("PixelCorrectionEnabled")) &&
        IsImplemented(pINodemap->GetNode("PixelCorrectionX")) &&
        IsImplemented(pINodemap->GetNode("PixelCorrectionY"))
        );
}

void CDefectivePixelManager::OnStCallbackForOverlay(IStCallbackParamBase *pIStCallbackParamBase, void* /*pvContext*/)
{
    if (pIStCallbackParamBase->GetCallbackType() != StCallbackType_StApiGUIEvent_DisplayImageWndDrawing)
    {
        return;
    }

    StApi::IStCallbackParamStApiGUIEventDrawing *pIStCallbackParamStApiGUIEventDrawing = dynamic_cast<StApi::IStCallbackParamStApiGUIEventDrawing*>(pIStCallbackParamBase);
    QPainter *hDC = (QPainter*)pIStCallbackParamStApiGUIEventDrawing->GetDC();

    const size_t nROIWidth = pIStCallbackParamStApiGUIEventDrawing->GetROIWidth();
    const size_t nDisplayWidth = pIStCallbackParamStApiGUIEventDrawing->GetDisplayWidth();

    const double dblMagnification = nDisplayWidth / (double)nROIWidth;

    const int32_t nSize = 4;

    GenApi::AutoLock objAuto(m_objLock);
    std::map<std::pair<size_t, size_t>, size_t> *pmapPixelIndex[] = { &m_mapDetectedDefectivePixelIndex,  &m_mapRegisteredDefectivePixelIndex };
    const QColor pColor[] = { QColor(255, 0, 0) , QColor(0, 255, 0) };

    QPen hOldPen = hDC->pen();
    QBrush hOldBrush = hDC->brush();
    QPen hPen(Qt::PenStyle::SolidLine);

    hDC->setBrush(Qt::BrushStyle::NoBrush);
    for (size_t i = 0; i < 2; ++i)
    {
        for (std::map<std::pair<size_t, size_t>, size_t>::const_iterator itr = pmapPixelIndex[i]->begin(); itr != pmapPixelIndex[i]->end(); ++itr)
        {
            const size_t x = itr->first.first;
            const size_t y = itr->first.second;

            const int32_t nLeft = (int32_t)x - nSize;
            const int32_t nRight = (int32_t)x + nSize;
            const int32_t nTop = (int32_t)y - nSize;
            const int32_t nBottom = (int32_t)y + nSize;

            hPen.setColor(pColor[i]);
            hDC->setPen(hPen);
            hDC->drawEllipse(
                QRect(QPoint(static_cast<long>(nLeft * dblMagnification), static_cast<long>(nTop * dblMagnification)),
                      QPoint(static_cast<long>(nRight * dblMagnification), static_cast<long>(nBottom * dblMagnification))));
        }
    }

    hPen.setColor(QColor(255, 0, 255));
    hDC->setPen(hPen);
    for (std::vector<std::pair<size_t, size_t>>::const_iterator itr = m_vecSelectedPixelInformation.begin(); itr != m_vecSelectedPixelInformation.end(); ++itr)
    {
        const size_t x = itr->first;
        const size_t y = itr->second;

        const int32_t nLeft = (int32_t)x - nSize;
        const int32_t nRight = (int32_t)x + nSize;
        const int32_t nTop = (int32_t)y - nSize;
        const int32_t nBottom = (int32_t)y + nSize;

        hDC->drawEllipse(
            QRect(QPoint(static_cast<long>(nLeft * dblMagnification), static_cast<long>(nTop * dblMagnification)),
                  QPoint(static_cast<long>(nRight * dblMagnification), static_cast<long>(nBottom * dblMagnification))));
    }

    hDC->setPen(hOldPen);
    hDC->setBrush(hOldBrush);
}

void CDefectivePixelManager::OnPixelFormatMayBeChanged(GenApi::INode* pINode, void * /*pParam*/)
{
    try
    {
        CEnumerationPtr pIEnumeration_PixelFormat(pINode);
        m_pIEnumeration_ExpectedPixelFormat->SetIntValue(pIEnumeration_PixelFormat->GetIntValue());
    }
    catch (...)
    {
    }
}

void CDefectivePixelManager::DetectDefectivePixel(StApi::IStImage *pIStImage)
{
    m_pIStDefectivePixelDetectionFilter->Filter(pIStImage);
    GenApi::AutoLock objAuto(m_objLock);
    GetDetectedDefectivePixelList();
}

void CDefectivePixelManager::GetDetectedDefectivePixelList()
{

    EStDefectivePixelDetectionStatus_t eStatus;
    size_t nCount;
    m_pIStDefectivePixelDetectionFilter->GetDetectionResult(&eStatus, &nCount, NULL);

    m_vecDefectivePixelInfomation.clear();
    m_mapDetectedDefectivePixelIndex.clear();

    if (
        (eStatus == StDefectivePixelDetectionStatus_Succeeded) ||
        (eStatus == StDefectivePixelDetectionStatus_TooManyDefectivePixelDetectedFailed)
        )
    {
        if (0 < nCount)
        {
            m_vecDefectivePixelInfomation.resize(nCount);
            m_pIStDefectivePixelDetectionFilter->GetDetectionResult(&eStatus, &nCount, &m_vecDefectivePixelInfomation[0]);

            for (size_t i = 0; i < nCount; ++i)
            {
                PSStDefectivePixelInformation_t pDPI = &m_vecDefectivePixelInfomation[i];
                std::pair<size_t, size_t> pairPos = std::make_pair(pDPI->x, pDPI->y);
                m_mapDetectedDefectivePixelIndex.insert(std::make_pair(pairPos, i));
            }
        }
    }
}

void CDefectivePixelManager::GetRegisteredDefectivePixelList()
{
    GenApi::AutoLock objAuto(m_objLock);
    m_mapRegisteredDefectivePixelIndex.clear();
    m_vecRegisteredDefectivePixel.clear();


    const bool bEnabledAll = m_pIBoolean_PixelCorrectionAllEnabled->GetValue();
    if (!bEnabledAll) m_pIBoolean_PixelCorrectionAllEnabled->SetValue(true);
    const int64_t nInitialIndex = m_pIInteger_PixelCorrectionIndex->GetValue();

    const int64_t nCount = m_pIInteger_PixelCorrectionIndex->GetMax() + 1;
    m_vecRegisteredDefectivePixel.resize(nCount);
    for (size_t i = 0; i < (size_t)nCount; ++i)
    {
        PSRegisteredDefectivePixel_t pRDP = &m_vecRegisteredDefectivePixel[i];
        m_pIInteger_PixelCorrectionIndex->SetValue(i);
        pRDP->isEnable = m_pIBoolean_PixelCorrectionEnabled->GetValue();
        if (pRDP->isEnable)
        {
            pRDP->x = m_pIInteger_PixelCorrectionX->GetValue();
            pRDP->y = m_pIInteger_PixelCorrectionY->GetValue();
            m_mapRegisteredDefectivePixelIndex.insert(std::make_pair(std::make_pair(pRDP->x, pRDP->y), i));
        }
    }

    m_pIInteger_PixelCorrectionIndex->SetValue(nInitialIndex);
    if (!bEnabledAll) m_pIBoolean_PixelCorrectionAllEnabled->SetValue(false);
}

void CDefectivePixelManager::ClearDetectedPixelList()
{
    GenApi::AutoLock objAuto(m_objLock);
    m_pIStDefectivePixelDetectionFilter->ClearDetectionResult();
    m_vecDefectivePixelInfomation.clear();
    m_mapDetectedDefectivePixelIndex.clear();
}

size_t CDefectivePixelManager::GetDetectedDefectivePixelCount()
{

    GenApi::AutoLock objAuto(m_objLock);
    return(m_vecDefectivePixelInfomation.size());
}

//Method for registering defective pixels to the camera
bool CDefectivePixelManager::RegisterSelectedPixel(std::vector<std::pair<size_t, size_t>> &vecPixelList)
{
    // Acquire the registered defective pixel list.
    GetRegisteredDefectivePixelList();

    GenApi::AutoLock objAuto(m_objLock);

    const bool bEnabledAll = m_pIBoolean_PixelCorrectionAllEnabled->GetValue();
    if (!bEnabledAll) m_pIBoolean_PixelCorrectionAllEnabled->SetValue(true);
    const int64_t nInitialIndex = m_pIInteger_PixelCorrectionIndex->GetValue();

    bool bOverflow = false;
    size_t nRegIndex = 0;
    for (std::vector<std::pair<size_t, size_t>>::const_iterator itr = vecPixelList.begin(); itr != vecPixelList.end(); ++itr)
    {
        std::pair<size_t, size_t> sPos = std::make_pair(itr->first, itr->second);
        if (m_mapRegisteredDefectivePixelIndex.find(sPos) == m_mapRegisteredDefectivePixelIndex.end())
        {
            for (; nRegIndex < m_vecRegisteredDefectivePixel.size(); ++nRegIndex)
            {
                if (!m_vecRegisteredDefectivePixel[nRegIndex].isEnable)
                {
                    m_pIInteger_PixelCorrectionIndex->SetValue(nRegIndex);
                    m_pIBoolean_PixelCorrectionEnabled->SetValue(true);
                    m_pIInteger_PixelCorrectionX->SetValue(itr->first);
                    m_pIInteger_PixelCorrectionY->SetValue(itr->second);

                    m_vecRegisteredDefectivePixel[nRegIndex].isEnable = true;
                    m_vecRegisteredDefectivePixel[nRegIndex].x = itr->first;
                    m_vecRegisteredDefectivePixel[nRegIndex].y = itr->second;
                    m_mapRegisteredDefectivePixelIndex.insert(std::make_pair(sPos, nRegIndex));
                    break;
                }
            }
            if (m_vecRegisteredDefectivePixel.size() <= nRegIndex)
            {
                bOverflow = true;
                break;
            }

        }
    }

    m_pIInteger_PixelCorrectionIndex->SetValue(nInitialIndex);
    if (!bEnabledAll) m_pIBoolean_PixelCorrectionAllEnabled->SetValue(false);
    return(bOverflow);
}

//Method to Unregister Defective Pixels in Camera
void CDefectivePixelManager::DeregisterSelectedPixel(std::vector<std::pair<size_t, size_t>> &vecPixelList)
{
    // Acquire the registered defective pixel list.
    GetRegisteredDefectivePixelList();

    const bool bEnabledAll = m_pIBoolean_PixelCorrectionAllEnabled->GetValue();
    if (!bEnabledAll) m_pIBoolean_PixelCorrectionAllEnabled->SetValue(true);
    const int64_t nInitialIndex = m_pIInteger_PixelCorrectionIndex->GetValue();

    for (std::vector<std::pair<size_t, size_t>>::const_iterator itr = vecPixelList.begin(); itr != vecPixelList.end(); ++itr)
    {
        std::pair<size_t, size_t> sPos = std::make_pair(itr->first, itr->second);
        std::map<std::pair<size_t, size_t>, size_t>::iterator itrReg = m_mapRegisteredDefectivePixelIndex.find(sPos);
        if (itrReg != m_mapRegisteredDefectivePixelIndex.end())
        {
            const size_t nRegIndex = itrReg->second;

            m_pIInteger_PixelCorrectionIndex->SetValue(nRegIndex);
            m_pIBoolean_PixelCorrectionEnabled->SetValue(false);

            m_vecRegisteredDefectivePixel[nRegIndex].isEnable = false;

            m_mapRegisteredDefectivePixelIndex.erase(itrReg);
        }
    }

    m_pIInteger_PixelCorrectionIndex->SetValue(nInitialIndex);
    if (!bEnabledAll) m_pIBoolean_PixelCorrectionAllEnabled->SetValue(false);
}

//Method for setting defective pixel selection information
void CDefectivePixelManager::SetSelectedPixelInformation(std::vector<std::pair<size_t, size_t>> &vecPixelList)
{
    GenApi::AutoLock objAuto(m_objLock);
    m_vecSelectedPixelInformation.clear();
    m_vecSelectedPixelInformation = vecPixelList;
}

//Method for updating the defective pixel list display
void CDefectivePixelManager::UpdateDefectivePixelList(IDefectivePixelListCtrl *pIDefectivePixelListCtrl)
{
    GenApi::AutoLock objAuto(m_objLock);

    std::map<std::pair<size_t, size_t>, size_t> mapAddedItem;
    for (int i = 0; i < (int)m_vecDefectivePixelInfomation.size(); ++i)
    {
        PSStDefectivePixelInformation_t pInfo = &m_vecDefectivePixelInfomation[i];

        std::pair<size_t, size_t> pairPos = std::make_pair(pInfo->x, pInfo->y);

        std::map<std::pair<size_t, size_t>, size_t>::iterator itr = m_mapRegisteredDefectivePixelIndex.find(pairPos);

        int32_t nRegistered = -1;
        if (m_mapRegisteredDefectivePixelIndex.end() != itr)
        {
            nRegistered = (int32_t)itr->second;
        }
        pIDefectivePixelListCtrl->AddDefectivePixel(pInfo, nRegistered);
        mapAddedItem.insert(std::make_pair(pairPos, i));
    }

    for (size_t i = 0; i < m_vecRegisteredDefectivePixel.size(); ++i)
    {
        PSRegisteredDefectivePixel_t pRDP = &m_vecRegisteredDefectivePixel[i];
        if (pRDP->isEnable)
        {
            std::pair<size_t, size_t> pairPos = std::make_pair(pRDP->x, pRDP->y);
            std::map<std::pair<size_t, size_t>, size_t>::iterator itr = mapAddedItem.find(pairPos);
            if (itr == mapAddedItem.end())
            {
                pIDefectivePixelListCtrl->AddDefectivePixel(pRDP->x, pRDP->y, (int32_t)i);
            }
        }
    }
}

bool CDefectivePixelManager::GetHighlight() const
{
    return m_pIStRegisteredCallback_Overlay.IsValid();
}

void CDefectivePixelManager::SetHighlight(bool value)
{
    if (value)
    {
        if (!m_pIStRegisteredCallback_Overlay.IsValid())
        {
            m_pIStRegisteredCallback_Overlay.Reset(RegisterCallback(m_pIStImageDisplayWnd, *this, &CDefectivePixelManager::OnStCallbackForOverlay, (void*)NULL));
        }
    }
    else
    {
        m_pIStRegisteredCallback_Overlay.Reset(NULL);
    }
}
