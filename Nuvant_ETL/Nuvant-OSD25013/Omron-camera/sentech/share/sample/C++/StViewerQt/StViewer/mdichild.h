#ifndef MDICHILD_H
#define MDICHILD_H

#include <QWidget>
#include "common.h"
#include "mainwindow.h"
#include "widgetnodemap.h"
#include "widgetgraphview.h"

namespace Ui {
class MdiChild;
}

class MainWindow;
class MdiChild : public QWidget
{
    Q_OBJECT

public:
    explicit MdiChild(QWidget *parent);
    virtual ~MdiChild();

    // Open Camera and do initialization. Return false if camera is not opened.
	virtual bool openCamera();

    // Store QMdiSubWindow pointer (used for signalling main window).
    void setMdiPointer(QMdiSubWindow *mdi);

	// Save a still image.
	void SaveStillImage();
	void GetImageToSave(StApi::IStImageBuffer *pIStImageBuffer);
	void ShowFileDlgAndSaveImage(StApi::IStImage *pIStImage);

	bool HasImage() const;

    // Get IStImageDisplayWnd pointer.
    StApi::IStImageDisplayWnd *GetIStImageDisplayWnd()
    {
        return (m_pIStImageDisplayWnd.IsValid() ? (StApi::IStImageDisplayWnd *)m_pIStImageDisplayWnd : nullptr);
    }

    // Set Graph Data source
    void SetGraphDataSource(bool isRegisteredImage)
    {
        if (m_pGraphView) m_pGraphView->SetGraphDataSource(isRegisteredImage);
    }

    // Get Graph Data source
    bool GetGraphDataSource()
    {
        if (m_pGraphView) return m_pGraphView->GetGraphDataSource();
        return false;
    }

	virtual void GetStatusBarText(size_t nIndex, QString &strText) = 0;
	void GetPixelInfoText(QString &strPixel);

signals:

    // Signal for main window to update log message.
    void on_addOutputLog(int logID, QString source);

    // Signal for main window to be removed from mdi child list.
    void on_removeMdiChild(QWidget *mdiChild);

    // Signal for main window to close mdi child.
    void on_closeMdiChild(MdiChild *mdichild);

    // Signal for main window to be enabled still image save button.
    void on_capturedFirstImage();

    // Signal for main window for adding/deleting dock widget.
    // If widget is nullptr, deletion is performed for the given name.
    // The parameter "visible" only applies for adding dock widget as the
    // value of the widget visibility.
    void on_dock(QString name, QWidget *widget, bool visible);


	void on_drawingItemSettingChanged();
protected:
#ifdef Q_OS_WIN32
	void resizeEvent(QResizeEvent *event) override;
#endif //Q_OS_WIN32
	StApi::CIStImageDisplayWndPtr m_pIStImageDisplayWnd;

    QString m_strDeviceName;
    QString m_strTitle;

    // Register nodes to be displayed in the NodeMap window.
    virtual void DisplayGenApiNodes();

    MainWindow *m_pParent;
    QMdiSubWindow *m_pMdi;

    WidgetNodeMap *m_pNodeMap;
    WidgetGraphView *m_pGraphView;

	virtual void OnCloseEvent() = 0;

	void OnDrawingItemSettingChanged(GenApi::INode *, void*);
private:
    // Close event handle (override from QWidget)
    void closeEvent(QCloseEvent *) override;

};

#endif // MDICHILD_H
