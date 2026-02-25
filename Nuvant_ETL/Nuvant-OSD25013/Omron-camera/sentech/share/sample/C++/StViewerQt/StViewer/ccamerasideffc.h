#ifndef CCAMERASIDEFFC_H
#define CCAMERASIDEFFC_H

#include <algorithm>
#include <QMutex>
#include <QWaitCondition>

#include "IStImageAveragingFilter.h"

#include "istimagecallback.h"

using namespace StApi;

class CCameraSideFFC final : public IStImageCallback
{
public:
    CCameraSideFFC(StApi::IStDevice *pIStDevice);
    ~CCameraSideFFC();
    static bool IsSupported(GenApi::CNodeMapPtr pINodeMap);
    void Wait(uint32_t waitms);
    void OnIStImage(StApi::IStImage *pIStImage);
    void Send();

protected:
    StApi::IStDevice * const m_pIStDevice;
    StApi::CIStImageAveragingFilterPtr m_pIStImageAveragingFilter;
    StApi::CIStImageBufferPtr m_pIStImageBuffer;

    int64_t m_nMaxGainValue;
    double m_dblBackLevelValue;
    size_t m_nFrameCount;
    size_t m_nRcvedFrameCount;

    size_t m_nImageWidthMax;
    size_t m_nImageHeightMax;
    size_t m_nAreaCountX;
    size_t m_nAreaCountY;
    size_t m_nAreaCount;

    const GenApi::CNodeMapPtr m_pINodeMap;
    const GenApi::CIntegerPtr m_pIIntegerFFCMeshWidth;
    const GenApi::CIntegerPtr m_pIIntegerFFCMeshHeight;
    const GenApi::CBooleanPtr m_pIBooleanFFCEnable;
    const GenApi::CIntegerPtr m_pIIntegerFFCIndex;
    const GenApi::CIntegerPtr m_pIIntegerFFCValue;
    const GenApi::CRegisterPtr m_pIRegisterFFCValueAll;
    const GenApi::CEnumerationPtr m_pIEnumerationDeviceRegistersEndianness;

    volatile bool m_bImageDone;
    QMutex m_mutexImageDone;
    QWaitCondition m_waitConditionImageDone;

    bool isLittleEndian() const
    {
        const uint16_t nValue = 1;
        return((*(char*)&nValue) != 0);
    }

    uint8_t SwapEndian(uint8_t nValue) const 
    { 
        return(nValue); 
    }

    uint16_t SwapEndian(uint16_t nValue) const 
    { 
        return(((nValue & 0xFF) << 8) | (nValue >> 8)); 
    }

    uint32_t SwapEndian(uint32_t nValue) const 
    { 
        return(((nValue & 0xFF) << 24) | ((nValue & 0xFF00) << 8) | ((nValue & 0xFF0000) >> 8) | (nValue >> 24)); 
    }

    template <class PixelComponentTypt_t, class GainCorrectionType_t>
    void mSend(const StApi::IStPixelFormatInfo *pIStPixelFormatInfo)
    {

        std::vector<PixelComponentTypt_t> vecEachAreaMedianValue;
        vecEachAreaMedianValue.resize((m_nAreaCountX + 1) * (m_nAreaCountY + 1));

        if (pIStPixelFormatInfo->IsMono())
        {
            GetMedianMono<PixelComponentTypt_t>(m_pIStImageBuffer->GetIStImage(), vecEachAreaMedianValue);
        }
        else if (pIStPixelFormatInfo->IsBayer())
        {
            switch (pIStPixelFormatInfo->GetPixelColorFilter())
            {
            case(StPixelColorFilter_BayerRG) :
            case(StPixelColorFilter_BayerBG) :
                GetMedianBayer<PixelComponentTypt_t>(m_pIStImageBuffer->GetIStImage(), vecEachAreaMedianValue, false);
                break;
            case(StPixelColorFilter_BayerGR) :
            case(StPixelColorFilter_BayerGB) :
                GetMedianBayer<PixelComponentTypt_t>(m_pIStImageBuffer->GetIStImage(), vecEachAreaMedianValue, true);
                break;
            }
        }
        else
        {
            throw RUNTIME_EXCEPTION("Invalid pixel format");
        }

        PixelComponentTypt_t nMax = 0;

        for (size_t i = 0; i < vecEachAreaMedianValue.size(); ++i)
        {
            if (nMax < vecEachAreaMedianValue[i])
            {
                nMax = vecEachAreaMedianValue[i];
            }
        }

        const PixelComponentTypt_t nBlackLevelSum = (PixelComponentTypt_t)(m_dblBackLevelValue * m_nRcvedFrameCount);
        if (nMax <= nBlackLevelSum)
        {
            nMax = 0;
        }
        else
        {
            nMax -= nBlackLevelSum;
        }


        std::vector<GainCorrectionType_t> vecGainList;
		size_t nGainListSize =(m_nAreaCountX + 1) * (m_nAreaCountY + 1) ;
		if ((sizeof(GainCorrectionType_t) * nGainListSize) % 4)
		{
			nGainListSize += (4 - ((sizeof(GainCorrectionType_t) * nGainListSize) % 4)) / sizeof(GainCorrectionType_t);
		}
		vecGainList.resize(nGainListSize);
		memset(&vecGainList[0], 0, sizeof(GainCorrectionType_t) * nGainListSize);

        for (size_t i = 0; i < vecEachAreaMedianValue.size(); ++i)
        {
            int64_t nGainValue = m_nMaxGainValue;
            if (nBlackLevelSum < vecEachAreaMedianValue[i])
            {
                double dblGain = nMax / (double)(vecEachAreaMedianValue[i] - nBlackLevelSum);
                dblGain -= 1.0;
                nGainValue = (int64_t)(dblGain * 128);
                if (m_nMaxGainValue < nGainValue) nGainValue = m_nMaxGainValue;
            }
            vecGainList[i] = (GainCorrectionType_t)nGainValue;
        }

        m_pIBooleanFFCEnable->SetValue(false);

        if (m_pIRegisterFFCValueAll.IsValid())
        {
            //ValueAll
            const bool isSysLE = isLittleEndian();
            bool isCamLE = true;
            if (m_pIEnumerationDeviceRegistersEndianness)
            {
                isCamLE = (m_pIEnumerationDeviceRegistersEndianness->GetCurrentEntry()->GetSymbolic().compare("Little") == 0);
            }
            if ((isSysLE && (!isCamLE)) || ((!isSysLE) && isCamLE))
            {
                //Swap endian
                for (size_t i = 0; i < vecGainList.size(); ++i)
                {
                    vecGainList[i] = SwapEndian(vecGainList[i]);
                }
            }

            m_pIRegisterFFCValueAll->Set((uint8_t*)&vecGainList[0], sizeof(vecGainList[0]) * vecGainList.size());
        }
        else
        {
            for (size_t i = 0; i < vecGainList.size(); ++i)
            {
                m_pIIntegerFFCIndex->SetValue(i);
                m_pIIntegerFFCValue->SetValue(vecGainList[i]);
            }
        }

        m_pIBooleanFFCEnable->SetValue(true);
    }

    #define MEDIAN_SIZE 3
    template <class X> X GetEachAreaMedianMono(X *pxTLBuffer, size_t nLinePitch)
    {
        std::vector<X> vecData;
        for (size_t y = 0; y < MEDIAN_SIZE; ++y)
        {
            for (size_t x = 0; x < MEDIAN_SIZE; ++x)
            {
                vecData.push_back(pxTLBuffer[x]);
            }
            pxTLBuffer = (X*)((uint8_t*)pxTLBuffer + nLinePitch);
        }

        std::sort(vecData.begin(), vecData.end());

        const size_t nCount = vecData.size();
        if (nCount & 1)
        {
            return(vecData[nCount / 2]);
        }
        else
        {
            size_t nIndex = nCount / 2;
            return((X)((vecData[nIndex] + vecData[nIndex - 1]) / 2));
        }
    }
    template <class X> void GetMedianMono(StApi::IStImage *pIStImage, std::vector<X> &vecEachAreaMedian)
    {
        const size_t nImageLinePitch = pIStImage->GetImageLinePitch();
        const size_t nMeshWidth = (size_t)m_pIIntegerFFCMeshWidth->GetValue();
        const size_t nMeshHeight = (size_t)m_pIIntegerFFCMeshHeight->GetValue();

        size_t nAreaIndex = 0;
        size_t nOffsetY = 0;
        for (size_t nY = 0; nY < m_nAreaCountY + 1; ++nY)
        {
            X * pxSrcBufferLine = (X*)((uint8_t*)pIStImage->GetImageBuffer() + nOffsetY * nImageLinePitch);

            size_t nOffsetX = 0;
            for (size_t nX = 0; nX < m_nAreaCountX + 1; ++nX)
            {
                vecEachAreaMedian[nAreaIndex] = GetEachAreaMedianMono<X>(&pxSrcBufferLine[nOffsetX], nImageLinePitch);
                ++nAreaIndex;

                nOffsetX += nMeshWidth;
                if (nX + 1 == m_nAreaCountX)
                {
                    nOffsetX = m_nImageWidthMax - MEDIAN_SIZE;
                }
            }

            nOffsetY += nMeshHeight;
            if (nY + 1 == m_nAreaCountY)
            {
                nOffsetY = m_nImageHeightMax - MEDIAN_SIZE;
            }
        }
    }
    template <class X> X GetEachAreaMedianBayer(X *pxTLBuffer, size_t nLinePitch, bool isGreen)    //eType 0:RG or BG, 1:GR or GB
    {
        std::vector<X> vecData;
        for (size_t y = 0; y < MEDIAN_SIZE; ++y)
        {
            if ((y & 1) == (size_t)(isGreen ? 0 : 1))
            {
                for (size_t x = 0; x < MEDIAN_SIZE; ++x)
                {
                    if ((x & 1) == 0)
                    {
                        vecData.push_back(pxTLBuffer[x]);
                    }
                }
            }
            else
            {
                for (size_t x = 0; x < MEDIAN_SIZE; ++x)
                {
                    if ((x & 1) == 1)
                    {
                        vecData.push_back(pxTLBuffer[x]);
                    }
                }
            }
            pxTLBuffer = (X*)((uint8_t*)pxTLBuffer + nLinePitch);
        }

        std::sort(vecData.begin(), vecData.end());

        const size_t nCount = vecData.size();
        if (nCount & 1)
        {
            return(vecData[nCount / 2]);
        }
        else
        {
            size_t nIndex = nCount / 2;
            return((X)((vecData[nIndex] + vecData[nIndex - 1]) / 2));
        }
    }
    template <class X> void GetMedianBayer(StApi::IStImage *pIStImage, std::vector<X> &vecEachAreaMedian, bool isGreen)
    {
        const size_t nImageLinePitch = pIStImage->GetImageLinePitch();
        const size_t nMeshWidth = (size_t)m_pIIntegerFFCMeshWidth->GetValue();
        const size_t nMeshHeight = (size_t)m_pIIntegerFFCMeshHeight->GetValue();
        const bool isGreenOnEdge = (MEDIAN_SIZE & 1) ? (isGreen ? false : true) : isGreen;
        size_t nAreaIndex = 0;
        size_t nOffsetY = 0;
        for (size_t nY = 0; nY < m_nAreaCountY; ++nY)
        {
            X * pxSrcBufferLine = (X*)((uint8_t*)pIStImage->GetImageBuffer() + nOffsetY * nImageLinePitch);

            size_t nOffsetX = 0;
            for (size_t nX = 0; nX < m_nAreaCountX; ++nX)
            {
                vecEachAreaMedian[nAreaIndex] = GetEachAreaMedianBayer<X>(&pxSrcBufferLine[nOffsetX], nImageLinePitch, isGreen);
                ++nAreaIndex;

                nOffsetX += nMeshWidth;
                if (nX + 1 == m_nAreaCountX)
                {
                    nOffsetX = m_nImageWidthMax - MEDIAN_SIZE;
                }
            }

            //Right
            vecEachAreaMedian[nAreaIndex] = GetEachAreaMedianBayer<X>(&pxSrcBufferLine[nOffsetX], nImageLinePitch, isGreenOnEdge);
            ++nAreaIndex;

            nOffsetY += nMeshHeight;
            if (nY + 1 == m_nAreaCountY)
            {
                nOffsetY = m_nImageHeightMax - MEDIAN_SIZE;
            }
        }
        {
            //Bottom
            X * pxSrcBufferLine = (X*)((uint8_t*)pIStImage->GetImageBuffer() + nOffsetY * nImageLinePitch);

            size_t nOffsetX = 0;
            for (size_t nX = 0; nX < m_nAreaCountX; ++nX)
            {
                vecEachAreaMedian[nAreaIndex] = GetEachAreaMedianBayer<X>(&pxSrcBufferLine[nOffsetX], nImageLinePitch, isGreenOnEdge);
                ++nAreaIndex;

                nOffsetX += nMeshWidth;
                if (nX + 1 == m_nAreaCountX)
                {
                    nOffsetX = m_nImageWidthMax - MEDIAN_SIZE;
                }
            }
            
            //Bottom / Right
            vecEachAreaMedian[nAreaIndex] = GetEachAreaMedianBayer<X>(&pxSrcBufferLine[nOffsetX], nImageLinePitch, isGreen);
        }
    }
};


#endif // CCAMERASIDEFFC_H
