#include <QFileDialog>
#include <QStandardPaths>

#include "common.h"
#include "dialogvideoconfiguration.h"
#include "ui_dialogvideoconfiguration.h"

DialogVideoConfiguration::DialogVideoConfiguration(StApi::IStVideoFiler *pIStVideoFiler, QWidget *parent)
try:
    QDialog(parent),
    ui(new Ui::DialogVideoConfiguration),
    m_pIStVideoFiler(pIStVideoFiler)
{
    ui->setupUi(this);

    // Split between the nodemap for IStVideoFiler and the list of AVI files.
    ui->splitter->setStretchFactor(0, 7);
    ui->splitter->setStretchFactor(1, 3);
    ui->listViewFile->setModel(&m_fileModel);

    m_qstrLastSavedVideoPath = QStandardPaths::writableLocation(QStandardPaths::MoviesLocation);

    // Create a NodeMapDisplayWnd object to get the IStWndReleasable interface pointer.
    // After the NodeMapDisplayWnd object is no longer needed, IStWndReleasable::Release()
    // must be called to discard the NodeMapDisplayWnd object.
    // In the destructor of CIStNodeMapDisplayWndPtr, IStWndReleasable::Release()
    // is called automatically.
    m_pIStNodeMapDisplayWnd.Reset(StApi::CreateIStWnd(StApi::StWindowType_NodeMapDisplay));

    // Register the Root node of the NodeMap of IStVideoFiler.
    m_pIStNodeMapDisplayWnd->RegisterINode(m_pIStVideoFiler->GetINodeMap()->GetNode("Root"), "");

    // Hide unneeded controls.
    m_pIStNodeMapDisplayWnd->SetVisibleAlphabeticMode(false);
    m_pIStNodeMapDisplayWnd->SetVisibleCollapse(false);
    m_pIStNodeMapDisplayWnd->SetVisibleExpand(false);
    m_pIStNodeMapDisplayWnd->SetVisiblePolling(false);
    m_pIStNodeMapDisplayWnd->SetVisibleRefresh(false);
    m_pIStNodeMapDisplayWnd->SetVisibleVisibility(false);
    m_pIStNodeMapDisplayWnd->SetVisibleDescription(false);
    m_pIStNodeMapDisplayWnd->SetVisibleMenu(false);
    m_pIStNodeMapDisplayWnd->SetVisibleStatusBar(false);
#ifdef Q_OS_WIN32
	m_pIStNodeMapDisplayWnd->Show((HWND)ui->widget->winId(), StApi::StWindowMode_Child);
#else
    m_pIStNodeMapDisplayWnd->Show(ui->widget, StApi::StWindowMode_Child);
#endif
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}
catch (const GenICam::GenericException &e)
{
    OnException(e);
}

DialogVideoConfiguration::~DialogVideoConfiguration()
{
    // Delete
    m_pIStNodeMapDisplayWnd->Close();
    m_pIStNodeMapDisplayWnd.Reset(nullptr);

    delete ui;
}

void DialogVideoConfiguration::on_btnAdd_clicked()
{
    QString filename = QFileDialog::getSaveFileName(nullptr, tr("AVI File"),
        m_qstrLastSavedVideoPath, "AVI File(*.avi)",Q_NULLPTR, QFileDialog::DontUseNativeDialog);
    if (filename.length() > 0)
    {
        if (filename.lastIndexOf(".avi", -1, Qt::CaseInsensitive) != filename.length()-4)
            filename += ".avi";

        QList<QStandardItem *> newRow;
        newRow << (new QStandardItem(filename));
        m_fileModel.appendRow(newRow);

        m_pIStVideoFiler->RegisterFileName(filename.toStdString().c_str());

        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
		m_qstrLastSavedVideoPath = QFileInfo(filename).path();
    }
}

void DialogVideoConfiguration::on_buttonBox_accepted()
{
    this->accept();
}

void DialogVideoConfiguration::on_buttonBox_rejected()
{
    this->reject();
}
#ifdef Q_OS_WIN32
void DialogVideoConfiguration::resizeEvent(QResizeEvent *event)
{
	QDialog::resizeEvent(event);
	QRect rect = ui->layoutNode->contentsRect();
	m_pIStNodeMapDisplayWnd->SetPosition(0, 0, rect.width(), rect.height());
}
#endif //Q_OS_WIN32

