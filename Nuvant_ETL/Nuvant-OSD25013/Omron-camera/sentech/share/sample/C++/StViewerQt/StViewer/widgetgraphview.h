#ifndef WIDGETGRAPHVIEW_H
#define WIDGETGRAPHVIEW_H

#include <QWidget>
#include "StApi_IP.h"
#include "StApi_GUI.h"

namespace Ui {
class WidgetGraphView;
}

class WidgetGraphView final : public QWidget
{
    Q_OBJECT

public:
    WidgetGraphView(StApi::IStImageDisplayWnd *wnd, QWidget *parent = nullptr);
    ~WidgetGraphView();

    // Return the NodeMap of the Graph Data Filter.
    GenApi::INodeMap *GetINodeMapForGraphDataFilter()
    {
        return(m_pIStGraphDataFilter->GetINodeMap());
    }

    // Return the NodeMap of the Graph Display Window.
    GenApi::INodeMap *GetINodeMapForGraphDisplayWnd()
    {
        return(m_pIStGraphDisplayWnd->GetINodeMap());
    }

    bool GetGraphDataSource() const
    {
        return m_isRegisteredImageGraphDataSource;
    }

    void SetGraphDataSource(bool isRegisteredImage)
    {
        m_isRegisteredImageGraphDataSource = isRegisteredImage;
    }

    // Terminate update timer, close and release the Graph Display Window.
    void terminate();

protected:
    void timerEvent(QTimerEvent *event) override;
#ifdef Q_OS_WIN32
	void resizeEvent(QResizeEvent *event) override;
#endif //Q_OS_WIN32

private:
    StApi::CIStGraphDataFilterPtr m_pIStGraphDataFilter;
    StApi::CIStGraphDisplayWndPtr m_pIStGraphDisplayWnd;
    StApi::IStImageDisplayWnd *m_pIStImageDisplayWnd;
    int m_nTimerID;
    bool m_isRegisteredImageGraphDataSource;
    Ui::WidgetGraphView *ui;
};

#endif // WIDGETGRAPHVIEW_H
