#include "widgetgraphview.h"
#include "ui_widgetgraphview.h"

WidgetGraphView::WidgetGraphView(StApi::IStImageDisplayWnd *wnd, QWidget *parent):
    QWidget(parent),
    m_pIStImageDisplayWnd(wnd),
    m_isRegisteredImageGraphDataSource(false),
    ui(new Ui::WidgetGraphView)
{
    ui->setupUi(this);

    m_pIStGraphDataFilter = StApi::CreateIStFilter(StApi::StFilterType_GraphData);

    m_pIStGraphDisplayWnd.Reset(StApi::CreateIStWnd(StApi::StWindowType_GraphDisplay));
    m_pIStGraphDisplayWnd->SetVisibleStatusBar(false);
    m_pIStGraphDisplayWnd->SetVisibleMenu(false);
#ifdef Q_OS_WIN32
    m_pIStGraphDisplayWnd->Show((HWND)this->winId(), StApi::StWindowMode_Child);
#else
    m_pIStGraphDisplayWnd->Show(this, StApi::StWindowMode_Child);
#endif

    // Start timer for updating graph (200ms)
    m_nTimerID = this->startTimer(200);
}

WidgetGraphView::~WidgetGraphView()
{
    terminate();
    delete ui;
}

void WidgetGraphView::terminate()
{
    m_pIStImageDisplayWnd = nullptr;

    if (m_nTimerID != 0)
    {
        this->killTimer(m_nTimerID);
        m_nTimerID = 0;
    }

    if (m_pIStGraphDisplayWnd.IsValid())
    {
        m_pIStGraphDisplayWnd->Close();
        m_pIStGraphDisplayWnd.Reset(NULL);
    }
}

void WidgetGraphView::timerEvent(QTimerEvent *event)
{
    if (event->timerId() != this->m_nTimerID || m_pIStImageDisplayWnd == nullptr)
    {
        QWidget::timerEvent(event);
        return;
    }

    if (!this->isVisible()) return;

    try
    {
        if (m_pIStImageDisplayWnd->HasImage())
        {
            StApi::IStImage *pIStImage = m_isRegisteredImageGraphDataSource ? m_pIStImageDisplayWnd->GetRegisteredIStImage() : m_pIStImageDisplayWnd->GetConvertedIStImage();
            m_pIStGraphDataFilter->Filter(pIStImage);
            m_pIStGraphDisplayWnd->RegisterIStGraphDataBufferList(
                m_pIStGraphDataFilter->GetIStGraphDataBufferList());
        }
    }
    catch(...)
    {
    }
}
#ifdef Q_OS_WIN32
void WidgetGraphView::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	QRect rect = this->rect();
	m_pIStGraphDisplayWnd->SetPosition(0, 0, rect.width(), rect.height());
}
#endif //Q_OS_WIN32
