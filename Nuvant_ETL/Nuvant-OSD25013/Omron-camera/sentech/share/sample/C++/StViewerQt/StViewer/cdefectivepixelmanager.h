#ifndef CDEFECTIVEPIXELMANAGER_H
#define CDEFECTIVEPIXELMANAGER_H

#include "common.h"
#include <map>

#define LIST_COL_STATUS 0
#define LIST_COL_X 1
#define LIST_COL_Y 2
#define LIST_COL_EVALUATION 3
#define LIST_COL_REFERENCE 4
#define LIST_COL_DIFFERENCE 5

struct IDefectivePixelListCtrl
{
    virtual void AddDefectivePixel(StApi::PSStDefectivePixelInformation_t pInfo, int32_t nRegistered = -1) = 0;
    virtual void AddDefectivePixel(size_t x, size_t y, int32_t nRegistered = -1) = 0;
};


class CDefectivePixelManager final
{
public:
    CDefectivePixelManager(GenApi::INodeMap *pINodeMap, StApi::IStImageDisplayWnd *pIStImageDisplayWnd);
    ~CDefectivePixelManager();

    static bool IsSupported(GenApi::INodeMap *pINodemap);
    
    //Method for setting defective pixel selection information
    void SetSelectedPixelInformation(std::vector<std::pair<size_t, size_t>> &vecPixelList);

    //Method for registering defective pixels to the camera
    bool RegisterSelectedPixel(std::vector<std::pair<size_t, size_t>> &vecPixelList);

    //Method to Unregister Defective Pixels in Camera
    void DeregisterSelectedPixel(std::vector<std::pair<size_t, size_t>> &vecPixelList);

    //Method for updating the defective pixel list display
    void UpdateDefectivePixelList(IDefectivePixelListCtrl *pIDefectivePixelListCtrl);

    GenApi::INodeMap *GetINodeMapForDefectivePixelDetectionFilter()
    {
        return(m_pIStDefectivePixelDetectionFilter->GetINodeMap());
    }

    void DetectDefectivePixel(StApi::IStImage *pIStImage);

    bool GetHighlight() const;
    void SetHighlight(bool value);

    size_t GetDetectedDefectivePixelCount();
    void GetDetectedDefectivePixelList();
    void GetRegisteredDefectivePixelList();
    void ClearDetectedPixelList();

protected:
    const GenApi::CNodeMapPtr m_pINodeMap_RemoteDevice;
    StApi::IStImageDisplayWnd * const m_pIStImageDisplayWnd;
    StApi::CIStRegisteredCallbackPtr m_pIStRegisteredCallback_Overlay;

    const GenApi::CBooleanPtr m_pIBoolean_PixelCorrectionAllEnabled;
    const GenApi::CIntegerPtr m_pIInteger_PixelCorrectionIndex;
    const GenApi::CBooleanPtr m_pIBoolean_PixelCorrectionEnabled;
    const GenApi::CIntegerPtr m_pIInteger_PixelCorrectionX;
    const GenApi::CIntegerPtr m_pIInteger_PixelCorrectionY;

    StApi::CIStDefectivePixelDetectionFilterPtr m_pIStDefectivePixelDetectionFilter;
    const GenApi::CNodeMapPtr m_pINodeMap_DefectivePixelDetectionFilter;
    const GenApi::CEnumerationPtr m_pIEnumeration_ExpectedPixelFormat;
    const GenApi::CIntegerPtr m_pIInteger_MaximumPixelCountToDetect;
    void OnPixelFormatMayBeChanged(GenApi::INode* pINode, void *pParam);

    void OnStCallbackForOverlay(StApi::IStCallbackParamBase *pIStCallbackParamBase, void* pvContext);

    GenApi::CLock m_objLock;

    //Registered defective pixel information
    std::map<std::pair<size_t, size_t>, size_t> m_mapRegisteredDefectivePixelIndex;
    typedef struct _SRegisteredDefectivePixel_t
    {
        size_t x;
        size_t y;
        bool isEnable;
    }SRegisteredDefectivePixel_t, *PSRegisteredDefectivePixel_t;
    std::vector<SRegisteredDefectivePixel_t> m_vecRegisteredDefectivePixel;

    //Detected defective pixels information
    std::map<std::pair<size_t, size_t>, size_t> m_mapDetectedDefectivePixelIndex;
    std::vector<StApi::SStDefectivePixelInformation_t> m_vecDefectivePixelInfomation;

    //Selected defective pixels information
    std::vector<std::pair<size_t, size_t>> m_vecSelectedPixelInformation;
};

#endif // CDEFECTIVEPIXELMANAGER_H
