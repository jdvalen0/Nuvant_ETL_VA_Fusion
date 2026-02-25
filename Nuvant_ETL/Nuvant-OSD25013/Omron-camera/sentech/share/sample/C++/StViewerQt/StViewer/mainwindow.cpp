#include "mainwindow.h"
#include "dialogabout.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <QtGlobal>
#include "mdichild_device.h"
#include "mdichild_stillimage.h"


using namespace StApi;

MainWindow::MainWindow(QApplication *app, QWidget *parent) :
    QMainWindow(parent),
	m_Application(app),
    ui(new Ui::MainWindow),
    m_objStApiAutoInit(),
	m_actionTile(nullptr),
	m_actionCascade(nullptr),
	m_actionNext(nullptr),
	m_actionPrevious(nullptr),
	m_actionWindowMenuSeparator(nullptr),
	m_actionWindowFullScreen(nullptr),
    m_outputModel(),
	m_actionCopy(nullptr),
	m_actionClear(nullptr),
	m_pHGridComboBox(nullptr), m_pVGridComboBox(nullptr),
	m_qstrLastImagePath(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation))
{
    ui->setupUi(this);
	m_defaultIcon = windowIcon();
	ui->action_About_StViewer->setIcon(QApplication::style()->standardIcon(QStyle::SP_FileDialogInfoView));
	ui->action_Close->setIcon(QApplication::style()->standardIcon(QStyle::SP_BrowserStop));
	ui->action_Save_Still_Image->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogSaveButton));

	ui->action_Exit->setIcon(QApplication::style()->standardIcon(QStyle::SP_TitleBarCloseButton));

    // Resize main window
    this->resize(1280,800);

    // Start timer for updating status bar
    m_nTimerID = this->startTimer(500);

    InitAction();
    InitOutputLog();
    InitStatusBar();

    UpdateToolBar();
    UpdateMenuDrawing();

    const uint32_t nCount = StSystemVendor_Count;
    for (uint32_t i = StSystemVendor_Default; i < nCount; ++i)
    {
        EStSystemVendor_t eStSystemVendor = (EStSystemVendor_t)i;
        try
        {
            // Create a system object, to get the IStSystemReleasable interface pointer.
            m_objIStSystemPtrList.Register(CreateIStSystem(eStSystemVendor, StInterfaceType_All));
        }
        catch (const GenICam::GenericException &e)
        {
            if (eStSystemVendor == StSystemVendor_Default)
            {
                OnException(e);
            }
        }
    }

    // Action command
    m_objIStNodeMapDisplayWndForGigEActionCommand = StApi::CreateIStWnd(StWindowType_NodeMapDisplay);
    for (size_t i = 0; i < m_objIStSystemPtrList.GetSize(); ++i)
    {
        IStSystem *pIStSystem = m_objIStSystemPtrList[i];
        for (size_t j = 0; j < pIStSystem->GetInterfaceCount(); ++j)
        {
            IStInterface *pIStInterface = pIStSystem->GetIStInterface(j);
            GenApi::CNodeMapPtr pINodeMap(pIStInterface->GetIStPort()->GetINodeMap());
            GenApi::CCategoryPtr pICategory_ActionControl(pINodeMap->GetNode("ActionControl"));
            if (GenApi::IsAvailable(pICategory_ActionControl))
            {
                const GenICam::gcstring strInterfaceName(
                            pIStInterface->GetIStInterfaceInfo()->GetDisplayName());
                GenApi::CCategoryPtr pICategory_EventControl(pINodeMap->GetNode("EventControl"));

                m_objIStNodeMapDisplayWndForGigEActionCommand->RegisterINode(
                            pICategory_ActionControl->GetNode(), strInterfaceName);
                m_objIStNodeMapDisplayWndForGigEActionCommand->RegisterINode(
                            pICategory_EventControl->GetNode(), strInterfaceName);
            }
            pIStInterface->StartEventAcquisitionThread();
        }
    }

    // One time timer to trigger "Open" menu to display Device selection window.
    QTimer::singleShot(100, [this]() {
        emit InitOpen();
    } );

	setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    QList<QMdiSubWindow *> windows = ui->mdiArea->subWindowList();
    m_actionWindowMenuSeparator->setVisible(!windows.isEmpty());

    for (int i = 0; i < windows.size(); ++i)
    {
        QMdiSubWindow *mdiSubWindow = windows.at(i);

        MdiChild *child = qobject_cast<MdiChild *>(mdiSubWindow->widget());
        delete child;
    }

    for (size_t i = 0; i < m_objIStSystemPtrList.GetSize(); ++i)
    {
        IStSystem *pIStSystem = m_objIStSystemPtrList[i];
        for (size_t j = 0; j < pIStSystem->GetInterfaceCount(); ++j)
        {
            IStInterface *pIStInterface = pIStSystem->GetIStInterface(j);
            pIStInterface->StopEventAcquisitionThread();
        }
    }

    delete ui;
}

StApi::IStDeviceReleasable *MainWindow::CreateIStDevice()
{
    IStDeviceReleasable *pIStDeviceReleasable = NULL;

    // Create "DeviceSelectionWnd".
    CIStDeviceSelectionWndPtr pIStDeviceSelectionWnd(CreateIStWnd(StWindowType_DeviceSelection));

#ifdef __APPLE__
    pIStDeviceSelectionWnd->SetVisibleMenu(false);
#endif

    // Move the "DeviceSelectionWnd" to the center of the main window.
    int nWidth = 960;
    int nHeight = 720;
    int nOffsetX = this->x() + (this->width() - nWidth) / 2;
    if(nOffsetX < 0) nOffsetX = 0;
    int nOffsetY = this->y() + (this->height() - nHeight) / 2;
    if(nOffsetY < 0) nOffsetY = 0;
    pIStDeviceSelectionWnd->SetPosition(nOffsetX, nOffsetY, nWidth, nHeight);

    // Specify the "IStSystem" to use.
    pIStDeviceSelectionWnd->RegisterTargetIStSystemList(m_objIStSystemPtrList);

    // Show the "DeviceSelectionWnd".
    pIStDeviceSelectionWnd->Show(NULL, StWindowMode_Modal);

    // Get selected device information.
    StApi::IStInterface *pIStInterface = NULL;
    const StApi::IStDeviceInfo *pIStDeviceInfo = NULL;
    pIStDeviceSelectionWnd->GetSelectedDeviceInfo(&pIStInterface, &pIStDeviceInfo);

    if(pIStDeviceInfo !=  NULL)
    {
        // Get available DeviceAccessFlag.
        GenTL::DEVICE_ACCESS_FLAGS eDeviceAccessFlags = GenTL::DEVICE_ACCESS_CONTROL;
        switch(pIStDeviceInfo->GetAccessStatus())
        {
        case(GenTL::DEVICE_ACCESS_STATUS_READONLY):
            eDeviceAccessFlags = GenTL::DEVICE_ACCESS_READONLY;
            break;
        case(GenTL::DEVICE_ACCESS_STATUS_READWRITE):
            eDeviceAccessFlags = GenTL::DEVICE_ACCESS_CONTROL;
            break;
        }

        // For GigE Vision switchover function.
        if (eDeviceAccessFlags == GenTL::DEVICE_ACCESS_CONTROL)
        {
            const uint32_t nDevCount = pIStInterface->GetDeviceCount();
            for (uint32_t nDevIndex = 0; nDevIndex < nDevCount; ++nDevIndex)
            {
                if (pIStInterface->GetIStDeviceInfo(nDevIndex) == pIStDeviceInfo)
                {
                    GenApi::CIntegerPtr pInteger_DeviceSelector(
                        pIStInterface->GetIStPort()->GetINodeMap()->GetNode("DeviceSelector"));
                    pInteger_DeviceSelector->SetValue(nDevIndex);

                    GenApi::CIntegerPtr pInteger_SwitchoverKey(
                        pIStInterface->GetIStPort()->GetINodeMap()->GetNode("GevApplicationSwitchoverKey"));
                    if (pInteger_SwitchoverKey.IsValid())
                    {
                        if (GenApi::IsWritable(pInteger_SwitchoverKey))
                        {
                            // If you use switchover function for GigE Vision,
                            // please set a switchover key here.
                            const uint16_t nSwitchoverKey = 0;
                            pInteger_SwitchoverKey->SetValue(nSwitchoverKey);
                        }
                    }
                    break;
                }
            }
        }

        // Create object and get IStDeviceReleasable pointer.
        GenICam::gcstring strDeviceID = pIStDeviceInfo->GetID();
        pIStDeviceReleasable = pIStInterface->CreateIStDevice(strDeviceID, eDeviceAccessFlags);
    }

    return(pIStDeviceReleasable);
}

void MainWindow::ShowNodeMapForInterfaces(QWidget *parent)
{
#ifdef Q_OS_WIN32
    m_objIStNodeMapDisplayWndForGigEActionCommand->Show((HWND)parent->winId(), StApi::StWindowMode_Modaless);
#else
    m_objIStNodeMapDisplayWndForGigEActionCommand->Show(parent, StApi::StWindowMode_Modaless);
#endif
}

void MainWindow::on_addOutputLogTriggered(int logID, QString source)
{
    QString dtime = QDateTime::currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
    QString msg = "";
    switch(logID)
    {
        case IDS_STARTED:
            msg = tr("Started."); break;
        case IDS_DEVICE_OPENED:
            msg = tr("Device opened."); break;
        case IDS_IMAGE_FILE_OPENED:
            msg = tr("Image file opened."); break;
        case IDS_DEVICE_LOST:
            msg = tr("Device lost.");
            QMessageBox::information(this, "Information", msg);
            break;
        case IDS_DEVICE_CLOSED:
            msg = tr("Device closed."); break;
        case IDS_STREAMING_STARTED:
            msg = tr("Streaming started."); break;
        case IDS_STREAMING_STOPPED:
            msg = tr("Streaming stopped."); break;
    }
    QList<QStandardItem *> newRow;
    newRow << (new QStandardItem(dtime)) << (new QStandardItem(source)) << (new QStandardItem(msg));

    m_outputModel.appendRow(newRow);
    ui->tableViewOutput->scrollToBottom();
}

void MainWindow::on_removeMdiChildTriggered(QWidget *mdiChild)
{    
    ui->mdiArea->removeSubWindow(mdiChild);
    QList<QMdiSubWindow *> windows = ui->mdiArea->subWindowList();
    for (int i = 0; i < windows.size(); ++i) {
        QMdiSubWindow *mdiSubWindow = windows.at(i);
        mdiSubWindow->setWindowState(Qt::WindowMaximized);
    }
}

void MainWindow::on_closeMdiChildTriggered(MdiChild *mdichild)
{
    mdichild->close();
}

void MainWindow::on_dockTriggered(QString name, QWidget *widget, bool visible)
{
    if (widget == nullptr) // Close widget with the parameter name.
    {
        std::map<QString, QDockWidget *>::iterator iter = m_mapDockWidget.find(name);

        if (iter != m_mapDockWidget.end())
        {
            m_mapDockWidget.erase(iter);
        }

        QList<QDockWidget *> dockWidgets = findChildren<QDockWidget *>();
        for (QList<QDockWidget*>::iterator it = dockWidgets.begin(); it != dockWidgets.end(); it++)
        {
            QDockWidget *dock = *it;
            if (dock->windowTitle() == name)
            {
                dock->setAttribute(Qt::WA_DeleteOnClose);
                dock->close();
                break;
            }
        }
    }
    else // Add widget with the parameter name.
    {
        QDockWidget *dock = new QDockWidget(name, this);
        dock->setWidget(widget);
        addDockWidget(Qt::RightDockWidgetArea, dock, Qt::Horizontal);
        dock->setHidden(!visible);
        widget->setMinimumWidth(320);
        widget->resize(320, widget->height());
        m_mapDockWidget.insert(std::make_pair(name, dock));
    }

    // Update menu.
    ui->menu_Toolbars_and_Docking_Windows->clear();
    ui->menu_Toolbars_and_Docking_Windows->addAction(ui->action_Standard);
    ui->menu_Toolbars_and_Docking_Windows->addAction(ui->action_StDrawing);
    ui->menu_Toolbars_and_Docking_Windows->addSeparator();
    ui->menu_Toolbars_and_Docking_Windows->addAction(ui->action_Output);
    for (std::map<QString, QDockWidget*>::iterator iter = m_mapDockWidget.begin();
         iter != m_mapDockWidget.end(); iter++)
    {
        QAction *action = ui->menu_Toolbars_and_Docking_Windows->addAction(iter->first);
        action->setCheckable(true);

        // Add signal and slot for menu trigger.
        connect(action, &QAction::triggered, this, [=]() {
            QDockWidget *dock = iter->second;
            dock->blockSignals(true);
            dock->setVisible(action->isChecked());
            dock->blockSignals(false);

            if (dock->isHidden()) return;
            if (dock->isFloating())
            {
                dock->blockSignals(true);
                dock->setFloating(false);
                dock->blockSignals(false);
            }
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
            this->resizeDocks({dock},{250},Qt::Horizontal);
#endif
        });
        action->setChecked(!((QDockWidget*)iter->second)->isHidden());
    }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() != this->m_nTimerID)
    {
        QMainWindow::timerEvent(event);
        return;
    }
    if (ui->statusBar->isHidden()) return;

    // Update status bar
    MdiChild *c = GetCurrentMdiChild();
    if (c == nullptr) return;

    try
    {
        // Image count
		QString strCount = "";
		c->GetStatusBarText(0, strCount);
        m_statusImageCount.setText(strCount);

        // fps
        QString strFps = "";
		c->GetStatusBarText(1, strFps);
        m_statusFps.setText(strFps);

        // Pixel Information
        QString strPixel;
		c->GetPixelInfoText(strPixel);
        m_statusPixel.setText(strPixel);
    }
    catch(...) {}
}

void MainWindow::on_action_About_StViewer_triggered()
{
    DialogAbout d(this,QString("SentechSDK Version %1")
                  .arg(StApi::GetStApiVersionText().c_str()));
    d.setModal(true);
    d.show();
    d.exec();
}

void MainWindow::on_dockWidgetOutput_visibilityChanged(bool visible)
{
    ui->action_Output->setChecked(visible);
}

void MainWindow::on_action_Status_Bar_triggered()
{
    ui->statusBar->setVisible(ui->action_Status_Bar->isChecked());
}

void MainWindow::on_action_Interface_Node_triggered()
{
    ShowNodeMapForInterfaces(this);
}


void MainWindow::on_action_Close_triggered()
{
    MdiChild *c = GetCurrentMdiChild();
    if (c == nullptr) return;
    c->close();
    on_menuWindowNeedUpdateTriggered();
    UpdateToolBar();
    UpdateMenuDrawing();
}

void MainWindow::on_action_Exit_triggered()
{
    this->close();
}

void MainWindow::on_action_Open_a_camera_triggered()
{
	OpenCamera();
}

void MainWindow::OpenCamera()
{
	MdiChild *c = new MdiChildDevice(this);
	if (!c->openCamera())
	{
		delete c;
		return;
	}
	QMdiSubWindow *w = ui->mdiArea->addSubWindow(c);
	w->setWindowIcon(QIcon(":/icon/res/StViewerDoc.ico"));

	c->setMdiPointer(w);
	c->showMaximized();

	UpdateToolBar();
	UpdateMenuDrawing();
}
void MainWindow::on_action_Load_a_file_triggered()
{
	MdiChild *c = new MdiChildStillImage(this);
	if (!c->openCamera())
	{
		delete c;
		return;
	}
	QMdiSubWindow *w = ui->mdiArea->addSubWindow(c);
	w->setWindowIcon(QIcon(":/icon/res/StViewerDoc.ico"));

	c->setMdiPointer(w);
	c->showMaximized();

	UpdateToolBar();
	UpdateMenuDrawing();
}


void MainWindow::on_action_Start_Acquisition_triggered()
{
    MdiChild *c = GetCurrentMdiChild();
    if (c == nullptr) return;
	IStreamingCtrl *pIStreamingCtrl = dynamic_cast<IStreamingCtrl*>(c);
	if (pIStreamingCtrl == nullptr) return;
	pIStreamingCtrl->StartImageAcquisition();
    UpdateToolBar();
}

void MainWindow::on_action_Stop_Acquisition_triggered()
{
    MdiChild *c = GetCurrentMdiChild();
    if (c == nullptr) return;
	IStreamingCtrl *pIStreamingCtrl = dynamic_cast<IStreamingCtrl*>(c);
	if (pIStreamingCtrl == nullptr) return;
	pIStreamingCtrl->StopImageAcquisition();
    UpdateToolBar();
}

void MainWindow::on_action_Save_Still_Image_triggered()
{
    MdiChild *c = GetCurrentMdiChild();
    if (c == nullptr) return;
    c->SaveStillImage();
    UpdateToolBar();
}

void MainWindow::on_action_Start_Recording_triggered()
{
    MdiChild *c = GetCurrentMdiChild();
    if (c == nullptr) return;
	IStreamingCtrl *pIStreamingCtrl = dynamic_cast<IStreamingCtrl*>(c);
	if (pIStreamingCtrl == nullptr) return;
	pIStreamingCtrl->StartRecording();
    UpdateToolBar();
}

void MainWindow::on_action_Stop_Recording_triggered()
{
    MdiChild *c = GetCurrentMdiChild();
    if (c == nullptr) return;
	IStreamingCtrl *pIStreamingCtrl = dynamic_cast<IStreamingCtrl*>(c);
	if (pIStreamingCtrl == nullptr) return;
	pIStreamingCtrl->StopRecording();
    UpdateToolBar();
}

void MainWindow::on_action_Standard_triggered()
{
    ui->mainToolBar->setVisible(ui->action_Standard->isChecked());
}

void MainWindow::on_action_StDrawing_triggered()
{
	ui->drawingToolBar->setVisible(ui->action_StDrawing->isChecked());
    //MdiChild *c = GetCurrentMdiChild();
    //if (c == nullptr) return;
    //c->SetDrawingToolbarVisible(ui->action_StDrawing->isChecked());
}


void MainWindow::on_action_Output_triggered()
{
    ui->dockWidgetOutput->setVisible(ui->action_Output->isChecked());
    if (ui->dockWidgetOutput->isHidden()) return;
    if (ui->dockWidgetOutput->isFloating())
        ui->dockWidgetOutput->setFloating(false);
}


void MainWindow::on_mdiArea_subWindowActivated(QMdiSubWindow *mdiSubWindow)
{
	if (!mdiSubWindow)
	{
		UpdateToolBar();
		UpdateMenuDrawing();
		return;
	}

    MdiChild *c = qobject_cast<MdiChild *>(mdiSubWindow->widget());
    UpdateToolBar(c);
    UpdateMenuDrawing(c);
}

void MainWindow::on_action_Save_Camera_Description_File_triggered()
{
    MdiChild *c = GetCurrentMdiChild();
    if (c == nullptr) return;
	ICameraCtrl *pICameraCtrl = dynamic_cast<ICameraCtrl*>(c);
	if (pICameraCtrl == nullptr) return;
	pICameraCtrl->SaveCameraDescriptionFile();
}

void MainWindow::on_action_Save_Camera_Config_File_triggered()
{
    MdiChild *c = GetCurrentMdiChild();
    if (c == nullptr) return;
	ICameraCtrl *pICameraCtrl = dynamic_cast<ICameraCtrl*>(c);
	if (pICameraCtrl == nullptr) return;
	pICameraCtrl->CameraConfigFile(false);
}

void MainWindow::on_action_Load_Camera_Config_File_triggered()
{
    MdiChild *c = GetCurrentMdiChild();
    if (c == nullptr) return;
	ICameraCtrl *pICameraCtrl = dynamic_cast<ICameraCtrl*>(c);
	if (pICameraCtrl == nullptr) return;
	pICameraCtrl->CameraConfigFile(true);
}


void MainWindow::InitAction()
{
    ui->action_Standard->setChecked(true);
    ui->action_Status_Bar->setChecked(true);
    ui->action_Output->setChecked(true);
    ui->action_Save_Camera_Description_File->setVisible(false);
    ui->action_Save_Camera_Config_File->setVisible(false);
    ui->action_Load_Camera_Config_File->setVisible(false);

    m_actionWindowFullScreen = new QAction(tr("&Full Screen"), this);
    m_actionWindowFullScreen->setStatusTip(tr("Display Full Screen"));
	QIcon iconFullScreen;
	iconFullScreen.addFile(QString::fromUtf8(":/icon/res/fullscrean.png"), QSize(), QIcon::Normal, QIcon::Off);
	m_actionWindowFullScreen->setIcon(iconFullScreen);
    connect(m_actionWindowFullScreen, &QAction::triggered, this, &MainWindow::on_actionWindowFullScreenTriggered);

    m_actionTile = new QAction(tr("&Tile"), this);
    m_actionTile->setStatusTip(tr("Tile the windows"));
	QIcon iconTile;
	iconTile.addFile(QString::fromUtf8(":/icon/res/tile.png"), QSize(), QIcon::Normal, QIcon::Off);
	m_actionTile->setIcon(iconTile);
    connect(m_actionTile, &QAction::triggered, ui->mdiArea, &QMdiArea::tileSubWindows);

    m_actionCascade = new QAction(tr("&Cascade"), this);
    m_actionCascade->setStatusTip(tr("Cascade the windows"));
	QIcon iconCascade;
	iconCascade.addFile(QString::fromUtf8(":/icon/res/cascade.png"), QSize(), QIcon::Normal, QIcon::Off);
	m_actionCascade->setIcon(iconCascade);
    connect(m_actionCascade, &QAction::triggered, ui->mdiArea, &QMdiArea::cascadeSubWindows);

    m_actionNext = new QAction(tr("Ne&xt"), this);
    m_actionNext->setShortcuts(QKeySequence::NextChild);
    m_actionNext->setStatusTip(tr("Move the focus to the next window"));
	m_actionNext->setIcon(QApplication::style()->standardIcon(QStyle::SP_ArrowForward));
    connect(m_actionNext, &QAction::triggered, ui->mdiArea, &QMdiArea::activateNextSubWindow);

    m_actionPrevious = new QAction(tr("Pre&vious"), this);
    m_actionPrevious->setShortcuts(QKeySequence::PreviousChild);
    m_actionPrevious->setStatusTip(tr("Move the focus to the previous window"));
	m_actionPrevious->setIcon(QApplication::style()->standardIcon(QStyle::SP_ArrowBack));
    connect(m_actionPrevious, &QAction::triggered, ui->mdiArea, &QMdiArea::activatePreviousSubWindow);

    m_actionWindowMenuSeparator = new QAction(this);
    m_actionWindowMenuSeparator->setSeparator(true);

    connect(ui->menu_File, &QMenu::aboutToShow, this, [=](){
        MdiChild *c = GetCurrentMdiChild();
        bool isEnabled = c != nullptr;
		ICameraCtrl *pICameraCtrl = dynamic_cast<ICameraCtrl*>(c);
		bool isCamera = pICameraCtrl != nullptr;
        ui->action_Close->setEnabled(isEnabled);
        ui->action_Start_Calculating_FFC_Correction_Value->setVisible(
			isCamera ? pICameraCtrl->IsFFCCorrectionSupported() : false);
    });

    connect(ui->menu_Graph_data_source, &QMenu::aboutToShow, this, [=]() {
        MdiChild *mdichild = GetCurrentMdiChild();
        if (mdichild != nullptr)
        {
            ui->action_Registered_image->setChecked(mdichild->GetGraphDataSource());
            ui->action_Converted_image->setChecked(!ui->action_Registered_image->isChecked());
        }
    });

    connect(ui->menu_Toolbars_and_Docking_Windows, &QMenu::aboutToShow, this, [=] () {
        for (std::map<QString, QDockWidget*>::iterator iter = m_mapDockWidget.begin();
             iter != m_mapDockWidget.end(); iter++)
        {
            QDockWidget *dock = iter->second;
			QList<QAction*> tmpActions = ui->menu_Toolbars_and_Docking_Windows->actions();
			for (QList<QAction*>::iterator it =
				tmpActions.begin();
				it != tmpActions.end(); it++)
			{
				QAction *action = *it;
				if (action->text() == dock->windowTitle())
				{
					action->setChecked(!dock->isHidden());
					break;
				}
			}
        }
    });

    connect(ui->menu_Toolbars_and_Docking_Windows, &QMenu::aboutToShow, this, [=]() {
        ui->action_StDrawing->setChecked(ui->drawingToolBar->isVisible());
    });

    connect(ui->menu_Window, &QMenu::aboutToShow,
            this, &MainWindow::on_menuWindowNeedUpdateTriggered);

	for (size_t i = 0; i < 2; ++i)
	{
		QString strText;
		QComboBox *pGridComboBox = new QComboBox;
		if (i == 0)
		{
			strText = "H Line:";
			m_pHGridComboBox = pGridComboBox;
			connect(pGridComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),	this, &MainWindow::onEvent_HGridIndexChanged);
		}
		else
		{
			strText = "V Line:";
			m_pVGridComboBox = pGridComboBox;
			connect(pGridComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onEvent_VGridIndexChanged);
		}

		for (size_t j = 0; j <= 32; ++j)
		{
			pGridComboBox->addItem(strText + QString::number(j));
		}
		ui->drawingToolBar->addWidget(pGridComboBox);
	}
	ui->drawingToolBar->setVisible(false);

    on_menuWindowNeedUpdateTriggered();
}

void MainWindow::InitOutputLog()
{
    QList<QDockWidget*> docklist;
    docklist << ui->dockWidgetOutput;

    QList<int> sizelist;
    sizelist << 100;

#if QT_VERSION > QT_VERSION_CHECK(5, 6, 0)
    this->resizeDocks(docklist,sizelist,Qt::Orientation::Vertical);
#endif

    m_outputModel.setColumnCount(3);
    m_outputModel.setHorizontalHeaderItem(0, new QStandardItem(tr("Time")));
    m_outputModel.setHorizontalHeaderItem(1, new QStandardItem(tr("Source")));
    m_outputModel.setHorizontalHeaderItem(2, new QStandardItem(tr("Log")));       
    ui->tableViewOutput->setModel(&m_outputModel);

    ui->tableViewOutput->horizontalHeader()->resizeSection(0, 200);
    ui->tableViewOutput->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);
    ui->tableViewOutput->horizontalHeader()->resizeSection(1, 200);
    ui->tableViewOutput->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Interactive);
    ui->tableViewOutput->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->tableViewOutput->verticalHeader()->hide();

    m_actionCopy = new QAction(tr("Copy"),this);
    m_actionClear = new QAction(tr("Clear"), this);
    m_outputContextMenu.addAction(m_actionCopy);
    m_outputContextMenu.addAction(m_actionClear);
    ui->tableViewOutput->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->tableViewOutput, &QWidget::customContextMenuRequested, this, [=](const QPoint &pos) {
        m_outputContextMenu.exec(ui->tableViewOutput->mapToGlobal(pos));
    });

    connect(m_actionCopy, &QAction::triggered, this, [=]() {
        QClipboard *clipboard = QApplication::clipboard();
        if (!clipboard) return;
        QString txt = "";
        for (int i = 0; i < m_outputModel.rowCount(); i++)
        {
            txt += QString("%1, %2, %3\r\n").arg(m_outputModel.item(i,0)->text())
                  .arg(m_outputModel.item(i,1)->text())
                  .arg(m_outputModel.item(i,2)->text());
        }
        clipboard->setText(txt);
    });

    connect(m_actionClear, &QAction::triggered, this, [=](){
        m_outputModel.removeRows(0, m_outputModel.rowCount());
    });

    on_addOutputLogTriggered(IDS_STARTED, this->windowTitle());
}

void MainWindow::InitStatusBar()
{
    m_statusPixel.setFrameStyle(QFrame::Panel | QFrame::Sunken);
    m_statusImageCount.setFrameStyle(QFrame::Panel | QFrame::Sunken);
    m_statusFps.setFrameStyle(QFrame::Panel | QFrame::Sunken);

    ui->statusBar->addPermanentWidget(&m_statusPixel,1);
    ui->statusBar->addPermanentWidget(&m_statusImageCount);
    ui->statusBar->addPermanentWidget(&m_statusFps);
}
void MainWindow::on_capturedFirstImage()
{
	UpdateToolBar(GetCurrentMdiChild());
}
void MainWindow::UpdateToolBar(MdiChild *mdichild)
{
    if (mdichild == nullptr)
    {
        mdichild = GetCurrentMdiChild();
    }

	//Main
	bool isCamera = false;
	const bool isOpened = (mdichild != nullptr);
	if(isOpened)
	{
		setWindowIcon(mdichild->windowIcon());

		ui->action_Save_Still_Image->setEnabled(mdichild->HasImage());

		IStreamingCtrl *pIStreamingCtrl = dynamic_cast<IStreamingCtrl*>(mdichild);
		isCamera = (pIStreamingCtrl != nullptr);
		if (isCamera)
		{
			bool isAcquisitionRunning = pIStreamingCtrl->IsAcquisitionRunning();
			bool isRecording = pIStreamingCtrl->IsRecording();
			ui->action_Start_Acquisition->setEnabled(!isAcquisitionRunning);
			ui->action_Stop_Acquisition->setEnabled(isAcquisitionRunning);
			ui->action_Start_Recording->setEnabled(!isRecording);
			ui->action_Stop_Recording->setEnabled(isRecording);
		}
	}
	else
    {
		setWindowIcon(m_defaultIcon);
    }
	
	ui->action_Close->setEnabled(isOpened);
	ui->action_Close->setVisible(isOpened);
	ui->action_Save_Still_Image->setVisible(isOpened);
	ui->action_Start_Acquisition->setVisible(isCamera);
	ui->action_Stop_Acquisition->setVisible(isCamera);
	ui->action_Start_Recording->setVisible(isCamera);
	ui->action_Stop_Recording->setVisible(isCamera);
	ui->action_Save_Camera_Description_File->setVisible(isCamera);
	ui->action_Save_Camera_Config_File->setVisible(isCamera);
	ui->action_Load_Camera_Config_File->setVisible(isCamera);

	//Drawing
	if (isOpened)
	{
		try
		{
			StApi::IStImageDisplayWnd * pIStImageDisplayWnd = mdichild->GetIStImageDisplayWnd();
			GenApi::CNodeMapPtr pINodeMap(pIStImageDisplayWnd->GetINodeMap());
			GenApi::CIntegerPtr pIInteger_HGridLineCount(pINodeMap->GetNode("HorizontalGridLineCount"));
			m_pHGridComboBox->setCurrentIndex(pIInteger_HGridLineCount->GetValue());
			GenApi::CIntegerPtr pIInteger_VGridLineCount(pINodeMap->GetNode("VerticalGridLineCount"));
			m_pVGridComboBox->setCurrentIndex(pIInteger_VGridLineCount->GetValue());

			GenApi::CEnumerationPtr pIEnumeration_DrawingItemType = pINodeMap->GetNode("DrawingItemType");
			const int64_t nDrawingItemType = pIEnumeration_DrawingItemType->GetIntValue();
			ui->action_Draw_Disable->setChecked(nDrawingItemType == 0);
			ui->action_Draw_Select->setChecked(nDrawingItemType == 1);
			ui->action_Draw_Line->setChecked(nDrawingItemType == 2);
			ui->action_Draw_Rectangle->setChecked(nDrawingItemType == 3);
			ui->action_Draw_Ellipse->setChecked(nDrawingItemType == 4);
			ui->action_Draw_Text->setChecked(nDrawingItemType == 5);
			ui->action_Draw_Angle->setChecked(nDrawingItemType == 6);
			ui->action_Draw_Polygon->setChecked(nDrawingItemType == 7);
			ui->action_Draw_Perpendicular->setChecked(nDrawingItemType == 8);
			ui->action_Draw_Arc->setChecked(nDrawingItemType == 9);
			ui->action_Draw_Bezier->setChecked(nDrawingItemType == 10);
			ui->action_Draw_FreeHand->setChecked(nDrawingItemType == 11);
			ui->action_Draw_Cross->setChecked(nDrawingItemType == 12);
		}
		catch (const GenICam::GenericException &e)
		{
			OnException(e);
		}
	}
	ui->action_Draw_Disable->setEnabled(isOpened);
	ui->action_Draw_Select->setEnabled(isOpened);
	ui->action_Draw_Line->setEnabled(isOpened);
	ui->action_Draw_Rectangle->setEnabled(isOpened);
	ui->action_Draw_Ellipse->setEnabled(isOpened);
	ui->action_Draw_Text->setEnabled(isOpened);
	ui->action_Draw_Angle->setEnabled(isOpened);
	ui->action_Draw_Polygon->setEnabled(isOpened);
	ui->action_Draw_Perpendicular->setEnabled(isOpened);
	ui->action_Draw_Arc->setEnabled(isOpened);
	ui->action_Draw_Bezier->setEnabled(isOpened);
	ui->action_Draw_FreeHand->setEnabled(isOpened);
	ui->action_Draw_Cross->setEnabled(isOpened);
	m_pHGridComboBox->setEnabled(isOpened);
	m_pVGridComboBox->setEnabled(isOpened);
}

void MainWindow::UpdateMenuDrawing(MdiChild *mdichild)
{
    if (mdichild == nullptr)
        mdichild = GetCurrentMdiChild();

    ui->action_StDrawing->setEnabled(mdichild != nullptr);
    ui->action_StDrawing->setChecked(ui->drawingToolBar->isVisible());
}

MdiChild *MainWindow::GetCurrentMdiChild() const
{
    if (QMdiSubWindow *currentSubWindow = ui->mdiArea->currentSubWindow())
        return qobject_cast<MdiChild *>(currentSubWindow->widget());

    return nullptr;
}

void MainWindow::on_action_Start_Calculating_FFC_Correction_Value_triggered()
{
    MdiChild *c = GetCurrentMdiChild();
    if (c == nullptr) return;
	ICameraCtrl *pICameraCtrl = dynamic_cast<ICameraCtrl*>(c);
	if (pICameraCtrl == nullptr) return;

    if (QMessageBox::question(nullptr, "Confirmation",
        "Start calculating shading correction values. "
        "This operation takes tens of seconds, during which the application becomes inoperable.",
         QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Cancel)
        return;

    if (pICameraCtrl->ComputeFFCCorrection())
    {
        QMessageBox::information(nullptr, "Information",
            "Succeeded. If you want to save shading correction values to the camera, execute UserSetSave.");
        return;
    }

    QMessageBox::information(nullptr, "Information", "Failed.");
}

void MainWindow::on_action_Configuration_File_Setting_triggered()
{
    DialogConfigurationFileSetting dlg;
    dlg.exec();
}

void MainWindow::on_action_Registered_image_triggered()
{
   ui->action_Converted_image->setChecked(!ui->action_Registered_image->isChecked());

   MdiChild *c = GetCurrentMdiChild();
   if (c == nullptr) return;
   c->SetGraphDataSource(ui->action_Registered_image->isChecked());
}

void MainWindow::on_action_Converted_image_triggered()
{
   ui->action_Registered_image->setChecked(!ui->action_Converted_image->isChecked());

   MdiChild *c = GetCurrentMdiChild();
   if (c == nullptr) return;
   c->SetGraphDataSource(ui->action_Registered_image->isChecked());
}

void MainWindow::on_signalWindowMapperTriggered(QWidget *window)
{
    if (!window) return;
    this->ui->mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}

void MainWindow::on_menuWindowNeedUpdateTriggered()
{
    ui->menu_Window->clear();
    ui->menu_Window->addAction(m_actionWindowFullScreen);
    ui->menu_Window->addSeparator();
    ui->menu_Window->addAction(m_actionTile);
    ui->menu_Window->addAction(m_actionCascade);
    ui->menu_Window->addSeparator();
    ui->menu_Window->addAction(m_actionNext);
    ui->menu_Window->addAction(m_actionPrevious);
    ui->menu_Window->addAction(m_actionWindowMenuSeparator);

    QList<QMdiSubWindow *> windows = ui->mdiArea->subWindowList();
    m_actionWindowMenuSeparator->setVisible(!windows.isEmpty());

    for (int i = 0; i < windows.size(); ++i) {
        QMdiSubWindow *mdiSubWindow = windows.at(i);
        MdiChild *child = qobject_cast<MdiChild *>(mdiSubWindow->widget());

        QString text;
        if (i < 9) {
            text = tr("&%1 %2").arg(i + 1)
                               .arg(child->windowTitle());
        } else {
            text = tr("%1 %2").arg(i + 1)
                              .arg(child->windowTitle());
        }
        QAction *action = ui->menu_Window->addAction(text);
	connect(action, &QAction::triggered, [=]{ on_signalWindowMapperTriggered(mdiSubWindow);});

        action->setCheckable(true);
        action->setChecked(child == GetCurrentMdiChild());
    }
}

void MainWindow::on_actionWindowFullScreenTriggered()
{
    Qt::WindowStates states = this->windowState();
#if QT_VERSION >= 0x057000
    states.setFlag(Qt::WindowFullScreen, !states.testFlag(Qt::WindowFullScreen));
#else
    if ((states & Qt::WindowFullScreen) == Qt::WindowFullScreen)
        states &= ~Qt::WindowFullScreen;
    else
        states |= Qt::WindowFullScreen;
#endif
    this->setWindowState(states);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("text/uri-list"))
	{
		event->acceptProposedAction();
	}
}
void MainWindow::dropEvent(QDropEvent *event)
{
	OpenFile(event->mimeData()->urls().first().toLocalFile());
}

void MainWindow::OpenFile(const QString &strFileName)
{
	MdiChildStillImage *c = new MdiChildStillImage(this);
	if (!c->openCamera(strFileName))
	{
		delete c;
		return;
	}
	QMdiSubWindow *w = ui->mdiArea->addSubWindow(c);
	w->setWindowIcon(QIcon(":/icon/res/StViewerDoc.ico"));

	c->setMdiPointer(w);
	c->showMaximized();

	UpdateToolBar();
	UpdateMenuDrawing();
}
void MainWindow::InitOpen()
{
	if (1 < m_Application->arguments().size())
	{
		OpenFile(m_Application->arguments().at(1));
	}
	else
	{

		// One time timer to trigger "Open" menu to display Device selection window.
		QTimer::singleShot(100, [this]() {
		    emit ui->action_Open_a_camera->triggered();
		} );
	}

}


void MainWindow::SetLastImagePath(const QString &strPath)
{
	m_qstrLastImagePath = QFileInfo(strPath).path();
}
QString MainWindow::GetLastImagePath() const
{
	return(m_qstrLastImagePath);
}


void MainWindow::onEvent_HGridIndexChanged(int index)
{
	MdiChild *mdichild = GetCurrentMdiChild();
	if (mdichild == nullptr) return;

	try
	{
		StApi::IStImageDisplayWnd * pIStImageDisplayWnd = mdichild->GetIStImageDisplayWnd();
		GenApi::CNodeMapPtr pINodeMap(pIStImageDisplayWnd->GetINodeMap());
		GenApi::CIntegerPtr pIInteger_GridLineCount(pINodeMap->GetNode("HorizontalGridLineCount"));
		pIInteger_GridLineCount->SetValue(index);
	}
	catch (const GenICam::GenericException &e)
	{
		OnException(e);
	}

}
void MainWindow::onEvent_VGridIndexChanged(int index)
{
	MdiChild *mdichild = GetCurrentMdiChild();
	if (mdichild == nullptr) return;

	try
	{
		StApi::IStImageDisplayWnd * pIStImageDisplayWnd = mdichild->GetIStImageDisplayWnd();
		GenApi::CNodeMapPtr pINodeMap(pIStImageDisplayWnd->GetINodeMap());
		GenApi::CIntegerPtr pIInteger_GridLineCount(pINodeMap->GetNode("VerticalGridLineCount"));
		pIInteger_GridLineCount->SetValue(index);
	}
	catch (const GenICam::GenericException &e)
	{
		OnException(e);
	}

}

void MainWindow::on_action_Draw_Disable_triggered()
{
	SetDrawingItemType(0);
}
void MainWindow::on_action_Draw_Select_triggered()
{
	SetDrawingItemType(1);
}
void MainWindow::on_action_Draw_Line_triggered()
{
	SetDrawingItemType(2);
}
void MainWindow::on_action_Draw_Rectangle_triggered()
{
	SetDrawingItemType(3);
}
void MainWindow::on_action_Draw_Ellipse_triggered()
{
	SetDrawingItemType(4);
}
void MainWindow::on_action_Draw_Text_triggered()
{
	SetDrawingItemType(5);
}
void MainWindow::on_action_Draw_Angle_triggered()
{
	SetDrawingItemType(6);
}
void MainWindow::on_action_Draw_Polygon_triggered()
{
	SetDrawingItemType(7);
}
void MainWindow::on_action_Draw_Perpendicular_triggered()
{
	SetDrawingItemType(8);
}
void MainWindow::on_action_Draw_Arc_triggered()
{
	SetDrawingItemType(9);
}
void MainWindow::on_action_Draw_Bezier_triggered()
{
	SetDrawingItemType(10);
}
void MainWindow::on_action_Draw_FreeHand_triggered()
{
	SetDrawingItemType(11);
}
void MainWindow::on_action_Draw_Cross_triggered()
{
	SetDrawingItemType(12);
}

void MainWindow::SetDrawingItemType(int64_t nValue)
{
	MdiChild *mdichild = GetCurrentMdiChild();
	if (mdichild == nullptr) return;

	try
	{
		StApi::IStImageDisplayWnd * pIStImageDisplayWnd = mdichild->GetIStImageDisplayWnd();
		GenApi::CNodeMapPtr pINodeMap(pIStImageDisplayWnd->GetINodeMap());
		GenApi::CEnumerationPtr pIEnumeration_DrawingItemType = pINodeMap->GetNode("DrawingItemType");
		pIEnumeration_DrawingItemType->SetIntValue(nValue);
		UpdateToolBar();
	}
	catch (const GenICam::GenericException &e)
	{
		OnException(e);
	}
}
void MainWindow::on_drawingItemSettingChanged()
{
	UpdateToolBar();
}
