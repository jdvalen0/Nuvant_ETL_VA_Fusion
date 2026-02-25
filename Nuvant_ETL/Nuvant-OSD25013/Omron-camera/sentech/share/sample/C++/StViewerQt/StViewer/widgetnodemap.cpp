#include "widgetnodemap.h"
#include "ui_widgetnodemap.h"

WidgetNodeMap::WidgetNodeMap(QWidget *parent):
    QWidget(parent),
    m_pIStNodeMapDisplayWnd(nullptr),
    ui(new Ui::WidgetNodeMap)
{
    ui->setupUi(this);

    m_pIStNodeMapDisplayWnd.Reset(StApi::CreateIStWnd(StApi::StWindowType_NodeMapDisplay));
    m_pIStNodeMapDisplayWnd->SetVisibleStatusBar(false);
    m_pIStNodeMapDisplayWnd->SetVisibleMenu(false);
    m_pIStNodeMapDisplayWnd->SetVisibleFilter(true);

#ifdef Q_OS_WIN32
    m_pIStNodeMapDisplayWnd->Show((HWND)this->winId(), StApi::StWindowMode_Child);
#else
    m_pIStNodeMapDisplayWnd->Show(this, StApi::StWindowMode_Child);
#endif
}

WidgetNodeMap::~WidgetNodeMap()
{
    terminate();
    delete ui;
}

void WidgetNodeMap::terminate()
{
    if (m_pIStNodeMapDisplayWnd.IsValid())
    {
        m_pIStNodeMapDisplayWnd->Close();
        m_pIStNodeMapDisplayWnd.Reset(NULL);
    }
}
#ifdef Q_OS_WIN32
void WidgetNodeMap::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	QRect rect = this->rect();
	m_pIStNodeMapDisplayWnd->SetPosition(0, 0, rect.width(), rect.height());
}
#endif //Q_OS_WIN32
