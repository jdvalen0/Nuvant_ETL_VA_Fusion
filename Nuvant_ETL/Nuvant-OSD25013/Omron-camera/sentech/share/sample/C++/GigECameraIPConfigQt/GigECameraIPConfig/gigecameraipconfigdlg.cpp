#include <QMessageBox>
#include "gigecameraipconfigdlg.h"
#include "ui_gigecameraipconfigdlg.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace StApi;

CGigECameraIPConfigDlg::CGigECameraIPConfigDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CGigECameraIPConfigDlg)
{
    ui->setupUi(this);
    ui->cbLLA->setEnabled(false);

    try
    {
        m_pIStSystem = CreateIStSystem(StSystemVendor_Default, StInterfaceType_GigEVision);
    }
    catch (const GenICam::GenericException &e)
    {
        OnException(e);
    }
    if (!DeviceSelection())
    {
        QApplication::quit();
    }
}

CGigECameraIPConfigDlg::~CGigECameraIPConfigDlg()
{
    delete ui;
}

void CGigECameraIPConfigDlg::OnException(const GenICam::GenericException &e)
{
    // Get the exception contents.
    GenICam::gcstring strSourceFileName(e.GetSourceFileName());
    const unsigned int iSourceLine = e.GetSourceLine();
    GenICam::gcstring strDescription(e.GetDescription());

    // Make message string.
    QString strMessage = QString::asprintf("%s [%u]\r\n%s",strSourceFileName.c_str(),
                                           iSourceLine,strDescription.c_str());

    QMessageBox::warning(nullptr, "Warning", strMessage);
}

void CGigECameraIPConfigDlg::OnNoCameras()
{
    ui->lblTargetDevice->setText("");
    ui->txtNIC_IP->setText("");
    ui->txtNIC_Mask->setText("");
    ui->txtNIC_Gateway->setText("");

    ui->txtCurrent_IP->setText("");
    ui->txtCurrent_Mask->setText("");
    ui->txtCurrent_Gateway->setText("");

    ui->txtPersist_IP->setText("");
    ui->txtPersist_Mask->setText("");
    ui->txtPersist_Gateway->setText("");

    ui->txtPersist_IP->setEnabled(false);
    ui->txtPersist_Mask->setEnabled(false);
    ui->txtPersist_Gateway->setEnabled(false);
    ui->cbDHCP->setEnabled(false);
    ui->cbPersist->setEnabled(false);
    ui->btnApply->setEnabled(false);
}

bool CGigECameraIPConfigDlg::DeviceSelection()
{
    bool bSelected = false;
    try
    {
        //Create "DeviceSelectionWnd".
        CIStDeviceSelectionWndPtr pIStDeviceSelectionWnd(CreateIStWnd(StWindowType_DeviceSelection));

        //Move the "DeviceSelectionWnd" to the center of the main window.
        int nWidth = 960;
        int nHeight = 720;
        int nOffsetX = this->x() + (this->width() - nWidth) / 2;
        if(nOffsetX < 0) nOffsetX = 0;
        int nOffsetY = this->y() + (this->height() - nHeight) / 2;
        if(nOffsetY < 0) nOffsetY = 0;
        pIStDeviceSelectionWnd->SetPosition(nOffsetX, nOffsetY, nWidth, nHeight);

        //Specify the "IStSystem" to use.
        pIStDeviceSelectionWnd->RegisterTargetIStSystem(m_pIStSystem);

        //Show the "DeviceSelectionWnd".
        pIStDeviceSelectionWnd->Show(NULL, StWindowMode_Modal);

        //Get selected device information.
        StApi::IStInterface *pIStInterface = NULL;
        const StApi::IStDeviceInfo *pIStDeviceInfo = NULL;
        pIStDeviceSelectionWnd->GetSelectedDeviceInfo(&pIStInterface, &pIStDeviceInfo);

        if (pIStDeviceInfo != NULL)
        {
            //Get available DeviceAccessFlag.
            GenTL::DEVICE_ACCESS_FLAGS eDeviceAccessFlags = GenTL::DEVICE_ACCESS_CONTROL;

            //Create object and get IStDeviceReleasable pointer.
            GenICam::gcstring strDeviceID = pIStDeviceInfo->GetID();
            m_pIStDevice = pIStInterface->CreateIStDevice(strDeviceID, eDeviceAccessFlags);

            bSelected = true;
        }

        UpdateInterfaceAndDeviceInfo();
    }
    catch (const GenICam::GenericException &e)
    {
        OnException(e);
    }
    return(bSelected);
}

void CGigECameraIPConfigDlg::UpdateInterfaceAndDeviceInfo()
{
    if (!m_pIStDevice)
    {
        OnNoCameras();
        return;
    }
    try
    {
        //Device Name
        ui->lblTargetDevice->setText(GCSTRING_2_LPCTSTR(m_pIStDevice->GetIStDeviceInfo()->GetDisplayName()));

        //Interface
        {
            IStInterface *pIStInterface = m_pIStDevice->GetIStInterface();
            GenApi::CNodeMapPtr pINodeMap_Interface = pIStInterface->GetIStPort()->GetINodeMap();
            GenApi::CIntegerPtr pIInteger = pINodeMap_Interface->GetNode("GevInterfaceSubnetIPAddress");
            ui->txtNIC_IP->setText(GCSTRING_2_LPCTSTR(pIInteger->ToString()));
            pIInteger = pINodeMap_Interface->GetNode("GevInterfaceSubnetMask");
            ui->txtNIC_Mask->setText(GCSTRING_2_LPCTSTR(pIInteger->ToString()));
            pIInteger = pINodeMap_Interface->GetNode("GevInterfaceGateway");
            if (IsReadable(pIInteger))
            {
                ui->txtNIC_Gateway->setText(GCSTRING_2_LPCTSTR(pIInteger->ToString()));
            }
            else
            {
                ui->txtNIC_Gateway->setText("");
            }
        }
        //Device
        {
            GenApi::CNodeMapPtr pINodeMap_Device = m_pIStDevice->GetRemoteIStPort()->GetINodeMap();

            m_pIBoolean_GevCurrentIPConfigurationLLA = pINodeMap_Device->GetNode("GevCurrentIPConfigurationLLA");
            m_pIBoolean_GevCurrentIPConfigurationDHCP = pINodeMap_Device->GetNode("GevCurrentIPConfigurationDHCP");
            m_pIBoolean_GevCurrentIPConfigurationPersistentIP = pINodeMap_Device->GetNode("GevCurrentIPConfigurationPersistentIP");

            m_pIInteger_GevCurrentIPAddress = pINodeMap_Device->GetNode("GevCurrentIPAddress");
            m_pIInteger_GevCurrentSubnetMask = pINodeMap_Device->GetNode("GevCurrentSubnetMask");
            m_pIInteger_GevCurrentDefaultGateway = pINodeMap_Device->GetNode("GevCurrentDefaultGateway");

            m_pIInteger_GevPersistentIPAddress = pINodeMap_Device->GetNode("GevPersistentIPAddress");
            m_pIInteger_GevPersistentSubnetMask = pINodeMap_Device->GetNode("GevPersistentSubnetMask");
            m_pIInteger_GevPersistentDefaultGateway = pINodeMap_Device->GetNode("GevPersistentDefaultGateway");

            ui->txtCurrent_IP->setText(GCSTRING_2_LPCTSTR(m_pIInteger_GevCurrentIPAddress->ToString()));
            ui->txtCurrent_Mask->setText(GCSTRING_2_LPCTSTR(m_pIInteger_GevCurrentSubnetMask->ToString()));
            ui->txtCurrent_Gateway->setText(GCSTRING_2_LPCTSTR(m_pIInteger_GevCurrentDefaultGateway->ToString()));

            ui->txtPersist_IP->setText(GCSTRING_2_LPCTSTR(m_pIInteger_GevPersistentIPAddress->ToString()));
            ui->txtPersist_Mask->setText(GCSTRING_2_LPCTSTR(m_pIInteger_GevPersistentSubnetMask->ToString()));
            ui->txtPersist_Gateway->setText(GCSTRING_2_LPCTSTR(m_pIInteger_GevPersistentDefaultGateway->ToString()));

            GenApi::CEnumerationPtr pIEnumeration_GevSupportedOptionSelector(pINodeMap_Device->GetNode("GevSupportedOptionSelector"));
            GenApi::CBooleanPtr pIBoolean_GevSupportedOption(pINodeMap_Device->GetNode("GevSupportedOption"));
            if (!pIEnumeration_GevSupportedOptionSelector || !pIBoolean_GevSupportedOption)
            {
                ui->cbDHCP->setEnabled(true);
                ui->cbPersist->setEnabled(true);
            }
            else
            {
                *pIEnumeration_GevSupportedOptionSelector = "IPConfigurationDHCP";
                ui->cbDHCP->setEnabled(pIBoolean_GevSupportedOption->GetValue());
                *pIEnumeration_GevSupportedOptionSelector = "IPConfigurationPersistentIP";
                ui->cbPersist->setEnabled(pIBoolean_GevSupportedOption->GetValue());
            }

            ui->cbLLA->setChecked(m_pIBoolean_GevCurrentIPConfigurationLLA->GetValue());
            ui->cbDHCP->setChecked(m_pIBoolean_GevCurrentIPConfigurationDHCP->GetValue());
            ui->cbPersist->setChecked(m_pIBoolean_GevCurrentIPConfigurationPersistentIP->GetValue());
        }
        CheckPersistentAddress();
    }
    catch (const GenICam::GenericException &e)
    {
        OnException(e);
    }
}

void CGigECameraIPConfigDlg::CheckPersistentAddress()
{
    bool isValid = true;
    const bool isEnablePersistentIP = ui->cbPersist->isEnabled() && ui->cbPersist->isChecked();

    if (isEnablePersistentIP)
    {
        isValid = isValid && IsValidIPAddress(ui->txtPersist_IP->text());
        isValid = isValid && IsValidSubnetMask(ui->txtPersist_Mask->text());
        isValid = isValid && IsValidGateway(ui->txtPersist_Gateway->text(),
                                            ui->txtPersist_IP->text(),ui->txtPersist_Mask->text());
    }

    ui->txtPersist_IP->setEnabled(isEnablePersistentIP);
    ui->txtPersist_Mask->setEnabled(isEnablePersistentIP);
    ui->txtPersist_Gateway->setEnabled(isEnablePersistentIP);
    ui->btnCopy->setEnabled(isEnablePersistentIP);
    ui->btnApply->setEnabled(isValid);
}

bool CGigECameraIPConfigDlg::IsValidIPAddress(QString ip_address)
{
   uint32_t value = ntohl(inet_addr(ip_address.toStdString().c_str()));
   if ((value < 0x01000000) || (0xE0000000 <= value) || (0x7F000000 == (value & 0xFF000000)))
       return false;

   return true;
}

bool CGigECameraIPConfigDlg::IsValidSubnetMask(QString mask)
{
    uint32_t value = ntohl(inet_addr(mask.toStdString().c_str()));

    if ((value == 0) || (value == 0xFFFFFFFF))
        return false;

    const uint32_t value_mask = 0x80000000;
    while (value & value_mask)
    {
        value <<= 1;
    }

    return (value == 0);
}

bool CGigECameraIPConfigDlg::IsValidGateway(QString gateway, QString ip_address, QString mask)
{
    uint32_t value_gateway = ntohl(inet_addr(gateway.toStdString().c_str()));

    if (value_gateway == 0)
        return true;

    uint32_t value_ip = ntohl(inet_addr(ip_address.toStdString().c_str()));
    uint32_t value_mask = ntohl(inet_addr(mask.toStdString().c_str()));

    bool isValid = true;
    isValid = isValid && IsValidIPAddress(gateway);
    isValid = isValid && (value_ip != value_gateway);
    isValid = isValid && ((value_ip & value_mask) == (value_gateway & value_mask));

    return isValid;
}

void CGigECameraIPConfigDlg::on_btnSelectCamera_clicked()
{
    DeviceSelection();
}

void CGigECameraIPConfigDlg::on_btnCopy_clicked()
{
    ui->txtPersist_IP->setText(ui->txtCurrent_IP->text());
    ui->txtPersist_Mask->setText(ui->txtCurrent_Mask->text());
    ui->txtPersist_Gateway->setText(ui->txtCurrent_Gateway->text());
}

void CGigECameraIPConfigDlg::on_btnApply_clicked()
{
    ui->btnApply->setEnabled(false);
    try
    {
        //Device
        m_pIBoolean_GevCurrentIPConfigurationLLA->SetValue(ui->cbLLA->isChecked());
        m_pIBoolean_GevCurrentIPConfigurationDHCP->SetValue(ui->cbDHCP->isChecked());
        m_pIBoolean_GevCurrentIPConfigurationPersistentIP->SetValue(ui->cbPersist->isChecked());

        const bool isEnablePersistentIP = ui->cbPersist->isEnabled() && ui->cbPersist->isChecked();
        if (isEnablePersistentIP)
        {
            uint32_t nValue;
            nValue = ntohl(inet_addr(ui->txtPersist_IP->text().toStdString().c_str()));
            m_pIInteger_GevPersistentIPAddress->SetValue(nValue);
            nValue = ntohl(inet_addr(ui->txtPersist_Mask->text().toStdString().c_str()));
            m_pIInteger_GevPersistentSubnetMask->SetValue(nValue);
            nValue = ntohl(inet_addr(ui->txtPersist_Gateway->text().toStdString().c_str()));
            m_pIInteger_GevPersistentDefaultGateway->SetValue(nValue);
        }
    }
    catch (const GenICam::GenericException &e)
    {
        OnException(e);
    }
    ui->btnApply->setEnabled(true);
}

void CGigECameraIPConfigDlg::on_txtPersist_IP_textEdited(const QString &)
{
    CheckPersistentAddress();
}

void CGigECameraIPConfigDlg::on_txtPersist_Mask_textEdited(const QString &)
{
    CheckPersistentAddress();
}

void CGigECameraIPConfigDlg::on_txtPersist_Gateway_textEdited(const QString &)
{
    CheckPersistentAddress();
}

void CGigECameraIPConfigDlg::on_cbPersist_clicked()
{
    CheckPersistentAddress();
}
