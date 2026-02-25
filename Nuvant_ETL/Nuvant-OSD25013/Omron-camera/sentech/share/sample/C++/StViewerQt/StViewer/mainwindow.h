#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QtWidgets>
#include "common.h"
#include "mdichild.h"
#include "dialogconfigurationfilesetting.h"

namespace Ui {
class MainWindow;
}

class MdiChild;
class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QApplication *app, QWidget *parent = nullptr);
    ~MainWindow();

    // Select device and get IStDeviceReleasable pointer.
    StApi::IStDeviceReleasable *CreateIStDevice();

    // Show Interface module nodemap for action command.
    void ShowNodeMapForInterfaces(QWidget *parent);

	void InitOpen();
	void OpenFile(const QString &strFileName);
	void OpenCamera();

	void SetLastImagePath(const QString &strPath);
	QString GetLastImagePath() const;

public slots:
    // Custom slots. The slot naming is different from Qt slot naming convention
    // to avoid Qt confusion for its default signal/slot naming pattern.
    void on_addOutputLogTriggered(int logID, QString source);
    void on_removeMdiChildTriggered(QWidget *mdiChild);
    void on_closeMdiChildTriggered(MdiChild *mdichild);
    void on_dockTriggered(QString name, QWidget *widget, bool visible);
    void on_capturedFirstImage();
	void on_drawingItemSettingChanged();
protected:
    void timerEvent(QTimerEvent *event) override;

private slots:

    // Qt slots.
    void on_action_About_StViewer_triggered();
    void on_dockWidgetOutput_visibilityChanged(bool visible);
    void on_action_Status_Bar_triggered();
    void on_action_Interface_Node_triggered();
    void on_action_Close_triggered();
    void on_action_Exit_triggered();
	void on_action_Open_a_camera_triggered();
	void on_action_Load_a_file_triggered();
    void on_action_Start_Acquisition_triggered();
    void on_action_Stop_Acquisition_triggered();
    void on_action_Save_Still_Image_triggered();
    void on_action_Start_Recording_triggered();
    void on_action_Stop_Recording_triggered();
    void on_action_Standard_triggered();
    void on_action_StDrawing_triggered();
    void on_action_Output_triggered();
    void on_mdiArea_subWindowActivated(QMdiSubWindow *mdiSubWindow);
    void on_action_Save_Camera_Description_File_triggered();
    void on_action_Save_Camera_Config_File_triggered();
    void on_action_Load_Camera_Config_File_triggered();
    void on_action_Start_Calculating_FFC_Correction_Value_triggered();
    void on_action_Configuration_File_Setting_triggered();
    void on_action_Registered_image_triggered();
    void on_action_Converted_image_triggered();

	void on_action_Draw_Disable_triggered();
	void on_action_Draw_Select_triggered();
	void on_action_Draw_Line_triggered();
	void on_action_Draw_Rectangle_triggered();
	void on_action_Draw_Ellipse_triggered();
	void on_action_Draw_Text_triggered();
	void on_action_Draw_Angle_triggered();
	void on_action_Draw_Polygon_triggered();
	void on_action_Draw_Perpendicular_triggered();
	void on_action_Draw_Arc_triggered();
	void on_action_Draw_Bezier_triggered();
	void on_action_Draw_FreeHand_triggered();
	void on_action_Draw_Cross_triggered();

    // Custom slots. The slot naming is different from Qt slot naming convention
    // to avoid Qt confusion for its default signal/slot naming pattern.
    void on_signalWindowMapperTriggered(QWidget *window);
    void on_menuWindowNeedUpdateTriggered();
    void on_actionWindowFullScreenTriggered();

	void onEvent_HGridIndexChanged(int index);
	void onEvent_VGridIndexChanged(int index);
private:
	QApplication *m_Application;
    Ui::MainWindow *ui;
    StApi::CStApiAutoInit    m_objStApiAutoInit;
    StApi::CIStSystemPtrArray m_objIStSystemPtrList;

    // Dock
    std::map<QString, QDockWidget*> m_mapDockWidget;

    // Window menu
    QAction *m_actionTile;
    QAction *m_actionCascade;
    QAction *m_actionNext;
    QAction *m_actionPrevious;
    QAction *m_actionWindowMenuSeparator;
    QAction *m_actionWindowFullScreen;

    // output log
    QStandardItemModel m_outputModel;
    QMenu m_outputContextMenu;
    QAction *m_actionCopy;
    QAction *m_actionClear;

    // Status bar
    QLabel m_statusPixel;
    QLabel m_statusImageCount;
    QLabel m_statusFps;

	QIcon m_defaultIcon;

	//Combo Box
	QComboBox *m_pHGridComboBox;
	QComboBox *m_pVGridComboBox;

    int    m_nTimerID;

    StApi::CIStNodeMapDisplayWndPtr m_objIStNodeMapDisplayWndForGigEActionCommand;

	QString m_qstrLastImagePath;

    void InitAction();
    void InitOutputLog();
    void InitStatusBar();
    void UpdateToolBar(MdiChild *mdichild = nullptr);
    void UpdateMenuDrawing(MdiChild *mdichild = nullptr);
    MdiChild *GetCurrentMdiChild() const;

	void SetDrawingItemType(int64_t nValue);
protected:
	void dragEnterEvent(QDragEnterEvent *event) override;
	void dropEvent(QDropEvent *event) override;
};

#endif // MAINWINDOW_H
