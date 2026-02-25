#ifndef WIDGETDEFECTIVEPIXELDETECTION_H
#define WIDGETDEFECTIVEPIXELDETECTION_H

#include <QAction>
#include <QMutex>
#include <QWaitCondition>
#include <QWidget>
#include <QToolBar>
#include <QSortFilterProxyModel>
#include "common.h"
#include "istimagecallback.h"
#include "istreamingctrl.h"
#include "cdefectivepixelmanager.h"
#include "tablemodeldefectivepixel.h"

namespace Ui {
class WidgetDefectivePixelDetection;
}

class WidgetDefectivePixelDetection final : public QWidget, public IStImageCallback
{
    Q_OBJECT

public:
    explicit WidgetDefectivePixelDetection(
        GenApi::INodeMap *pINodeMap, IStreamingCtrl *pIStreamingCtrl,
        StApi::IStImageDisplayWnd *pIStImageDisplayWnd, QWidget *parent = 0);
    ~WidgetDefectivePixelDetection();

    // IStImageCallback
    void OnIStImage(StApi::IStImage *pIStImage) override;

    GenApi::INodeMap *GetINodeMapForDefectivePixelDetectionFilter()
    {
        return(m_objCDefectivePixelManager.GetINodeMapForDefectivePixelDetectionFilter());
    }

    void OnNodeCallback(GenApi::INode *pINode, void *)
    {
        if (GenApi::IsReadable(pINode))
        {
            bool checked = m_actionEnabledCorrection.isChecked();
            if (m_pIBoolean_PixelCorrectionAllEnabled->GetValue() != checked)
            {
				emit SetEnabledCorrectionChecked(!checked);
            }
        }
		emit SetEnabledCorrectionEnabled(GenApi::IsWritable(pINode));
    }
    void terminate();

signals:
	void SetEnabledCorrectionChecked(bool);
	void SetEnabledCorrectionEnabled(bool);
private slots:
	void OnSetEnabledCorrectionChecked(bool bChecked)
	{
		m_actionEnabledCorrection.setChecked(bChecked);
	}
	void OnSetEnabledCorrectionEnabled(bool bChecked)
	{
		m_actionEnabledCorrection.setEnabled(bChecked);
	}

private slots:
    void on_actionDetectTriggered(bool checked = false);
    void on_actionClearTriggered(bool checked = false);
    void on_actionRegisterTriggered(bool checked = false);
    void on_actionDeregisterTriggered(bool checked = false);
    void on_actionRefreshTriggered(bool checked = false);
    void on_actionSaveImageTriggered(bool checked = false);
    void on_actionHighlightTriggered(bool checked = false);
    void on_actionEnabledCorrectionTriggered(bool checked = false);
    void on_tableViewSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

protected:
	void	showEvent(QShowEvent * /*event*/)
	{
		if (m_bFirstTime)
		{
			on_actionRefreshTriggered();
			m_bFirstTime = false;
		}
	}

private:
    Ui::WidgetDefectivePixelDetection *ui;

    // Toolbar
    QToolBar m_toolbarDefectivePixelDetection;
    QAction m_actionDetect;
    QAction m_actionClear;
    QAction m_actionRegister;
    QAction m_actionDeregister;
    QAction m_actionRefresh;
    QAction m_actionSaveImage;
    QAction m_actionHighlight;
    QAction m_actionEnabledCorrection;

    IStreamingCtrl * const m_pIStreamingCtrl;
    StApi::CIStImageAveragingFilterPtr m_pIStImageAveragingFilter;
    StApi::CIStImageBufferPtr m_pIStImageBuffer;
    size_t m_nRcvedFrameCount;
    size_t m_nFrameCount;
    bool m_bSaveAveragedImage;

    CDefectivePixelManager m_objCDefectivePixelManager;

    QSortFilterProxyModel m_proxy;
    TableModelDefectivePixel m_ModelDefectivePixel;

    const GenApi::CBooleanPtr m_pIBoolean_PixelCorrectionAllEnabled;
    const GenApi::CFloatPtr m_pIFloat_AcquisitionFrameRate;
    const GenApi::CFloatPtr m_pIFloat_ExposureTime;
    StApi::CIStRegisteredCallbackPtr m_pIStRegisteredCallbackPixelCorrectionAllEnabled;

    QString m_qstrLastSavedImagePath;

    volatile bool m_bImageDone;
    QMutex m_mutexImageDone;
    QWaitCondition m_waitConditionImageDone;

	bool m_bFirstTime;

    void SaveImage(StApi::IStImage *pIStImage, GenICam::gcstring &strFileName);
    void Wait(uint32_t waitms);
};

#endif // WIDGETDEFECTIVEPIXELDETECTION_H
