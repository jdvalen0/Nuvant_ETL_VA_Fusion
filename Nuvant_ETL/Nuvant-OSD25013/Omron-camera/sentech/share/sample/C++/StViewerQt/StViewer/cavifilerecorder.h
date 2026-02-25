#ifndef CAVIFILERECORDER_H
#define CAVIFILERECORDER_H

#include "common.h"

class CAVIFileRecorder final
{
public:
    CAVIFileRecorder();
    ~CAVIFileRecorder();

    // Open configuration dialog for recording video of the given pIStDevice.
    // Return false if a configuration was cancelled or an exception occurred.
    bool Open(StApi::IStDevice *pIStDevice, StApi::IStImageDisplayWnd *pIStImageDisplayWnd);

    // Add new frame given by pIStStreamBuffer to AVI file.
    // Return true if AVI file is not opened or already closed.
    bool RegisterIStStreamBuffer(StApi::IStStreamBuffer *pIStStreamBuffer);

protected:
    StApi::CIStVideoFilerPtr m_pIStVideoFiler;
	StApi::CIStImageBufferPtr m_pIStImageBuffer;
	StApi::CIStPixelFormatConverterPtr m_pIStPixelFormatConverter;
    uint64_t m_iTimestampOffset;
    bool m_isFirstFrame;
    double m_dblCameraFrameRate;
	bool m_isNeedToConvBeforeReg;
};

#endif // CAVIFILE_H
