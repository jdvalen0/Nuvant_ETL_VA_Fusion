#ifndef ISTREAMINGCTRL_H
#define ISTREAMINGCTRL_H

#include <stdint.h>

struct IStreamingCtrl
{
    virtual bool IsAcquisitionRunning() const = 0;

    virtual void StartImageAcquisition() = 0;

    virtual void StopImageAcquisition() = 0;

	virtual void StartRecording() = 0;

	virtual void StopRecording() = 0;

	virtual bool IsRecording() const = 0;
};

#endif // ISTREAMINGCTRL_H
