#ifndef GIGECAMERAIPCONFIGDLG_H
#define GIGECAMERAIPCONFIGDLG_H

#include <QDialog>
#include <StApi_TL.h>
#include <StApi_IP.h>
#include <StApi_GUI.h>
#include "GenICam.h"

namespace Ui {
class CGigECameraIPConfigDlg;
}

class CGigECameraIPConfigDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CGigECameraIPConfigDlg(QWidget *parent = 0);
    ~CGigECameraIPConfigDlg();

    void OnException(const GenICam::GenericException &e);
    void OnNoCameras();

    bool DeviceSelection();
    void UpdateInterfaceAndDeviceInfo();
    void CheckPersistentAddress();
    bool IsValidIPAddress(QString ip_address);
    bool IsValidSubnetMask(QString mask);
    bool IsValidGateway(QString gateway, QString ip_address, QString mask);

private slots:
    void on_btnSelectCamera_clicked();
    void on_btnCopy_clicked();
    void on_btnApply_clicked();
    void on_txtPersist_IP_textEdited(const QString &);
    void on_txtPersist_Mask_textEdited(const QString &);
    void on_txtPersist_Gateway_textEdited(const QString &);
    void on_cbPersist_clicked();

private:
    Ui::CGigECameraIPConfigDlg *ui;
    StApi::CStApiAutoInit m_objStApiAutoInit;
    StApi::CIStSystemPtr m_pIStSystem;
    StApi::CIStDevicePtr m_pIStDevice;

    GenApi::CBooleanPtr m_pIBoolean_GevCurrentIPConfigurationLLA;
    GenApi::CBooleanPtr m_pIBoolean_GevCurrentIPConfigurationDHCP;
    GenApi::CBooleanPtr m_pIBoolean_GevCurrentIPConfigurationPersistentIP;

    GenApi::CIntegerPtr m_pIInteger_GevCurrentIPAddress;
    GenApi::CIntegerPtr m_pIInteger_GevCurrentSubnetMask;
    GenApi::CIntegerPtr m_pIInteger_GevCurrentDefaultGateway;

    GenApi::CIntegerPtr m_pIInteger_GevPersistentIPAddress;
    GenApi::CIntegerPtr m_pIInteger_GevPersistentSubnetMask;
    GenApi::CIntegerPtr m_pIInteger_GevPersistentDefaultGateway;

};

#endif // GIGECAMERAIPCONFIGDLG_H
