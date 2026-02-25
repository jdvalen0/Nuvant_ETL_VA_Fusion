#ifndef WIDGETNODEMAP_H
#define WIDGETNODEMAP_H

#include <QWidget>
#include "StApi_TL.h"
#include "StApi_GUI.h"

namespace Ui {
class WidgetNodeMap;
}

class WidgetNodeMap final : public QWidget
{
    Q_OBJECT

public:
    WidgetNodeMap(QWidget *parent = nullptr);
    ~WidgetNodeMap();

    // Return the NodeMap of the NodeMapWindow.
    GenApi::INodeMap *GetINodeMap()
    {
        return(m_pIStNodeMapDisplayWnd->GetINodeMap());
    }

    // Add pINode to the display window.
    void RegisterINode(GenApi::INode *pINode, const GenICam::gcstring strTitle)
    {
        m_pIStNodeMapDisplayWnd->RegisterINode(pINode, strTitle);
    }

    // Refresh display.
    void RefreshDisplay()
    {
        m_pIStNodeMapDisplayWnd->Refresh();
    }

    // Close and Release IStNodeMapDisplayWnd.
    void terminate();

private:
#ifdef Q_OS_WIN32
	void resizeEvent(QResizeEvent *event) override;
#endif //Q_OS_WIN32
    StApi::CIStNodeMapDisplayWndPtr m_pIStNodeMapDisplayWnd;
    Ui::WidgetNodeMap *ui;
};

#endif // WIDGETNODEMAP_H
