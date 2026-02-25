#include <QFileDialog>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonObject>

#include "dialogconfigurationfilesetting.h"
#include "ui_dialogconfigurationfilesetting.h"

QString DialogConfigurationFileSetting::m_qstrJsonPath = QString(
    QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.sentech").toStdString().c_str();

const char *DialogConfigurationFileSetting::m_strJsonFile = "StViewer.json";

DialogConfigurationFileSetting::DialogConfigurationFileSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfigurationFileSetting),
    m_qstrLastPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)),
    m_eTargetForType{StConfigurationFileTarget_None, StConfigurationFileTarget_None}
{
    ui->setupUi(this);

    QStringList comboItemText({"None", "All cameras and all files", "Each model of camera and each type of file", "Each camera and each file"});
    for (auto itemText: comboItemText)
    {
        ui->comboBoxNodeMap->addItem(itemText);
        ui->comboBoxImageDisplay->addItem(itemText);
        ui->comboBoxDefectivePixelDetection->addItem(itemText);
        ui->comboBoxPixelFormatConverter->addItem(itemText);
    }

    LoadConfigurationJson();

	// remove question mark
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

DialogConfigurationFileSetting::~DialogConfigurationFileSetting()
{
    delete ui;
}

QString DialogConfigurationFileSetting::GetConfigPath()
{
    return this->m_qstrLastPath + "/StViewer";
}

void DialogConfigurationFileSetting::SetPairTypeTarget(EStConfigurationFileType_t eType, EStConfigurationFileTarget_t eTarget)
{
    this->m_eTargetForType[eType] = eTarget;
}

EStConfigurationFileTarget_t DialogConfigurationFileSetting::GetTargetForType(EStConfigurationFileType_t eType)
{
    return this->m_eTargetForType[eType];
}

void DialogConfigurationFileSetting::LoadConfigurationJson()
{
    QString jsonFile = QString("%1/%2").arg(m_qstrJsonPath).arg(m_strJsonFile);
    try
    {
        QFile loadFile(jsonFile);
        if (!loadFile.open(QIODevice::ReadOnly)) return;

        QByteArray data = loadFile.readAll();
        QJsonDocument loadDoc(QJsonDocument::fromJson(data));
        QJsonObject json = loadDoc.object();

        QString path = json["ConfigurationFileSetting"].toObject()["Path"].toString();
        if (path.trimmed().length() > 0)
            m_qstrLastPath = path;

        for (int eType = 0; eType < (int)StConfigurationFileType_Count; eType++)
        {
            QString jsonKey = QString::asprintf("FileType_%d", eType);
            m_eTargetForType[eType] = (EStConfigurationFileTarget_t)json["ConfigurationFileSetting"].toObject()[jsonKey].toInt();
        }

        loadFile.close();
    }
    catch(...)
    {
    }
}

void DialogConfigurationFileSetting::SaveConfigurationJson()
{
    QString jsonFile = QString("%1/%2").arg(m_qstrJsonPath).arg(m_strJsonFile);
    try
    {
        QDir dirName(m_qstrJsonPath);
        if (!dirName.exists())
            dirName.mkdir(m_qstrJsonPath);

        QFile saveFile(jsonFile);
        if (saveFile.open(QIODevice::WriteOnly) != true) return;

        QJsonObject objConfiguration;
        objConfiguration["Path"] = m_qstrLastPath;

        for (int eType = 0; eType < (int)StConfigurationFileType_Count; eType++)
        {
            QString jsonKey = QString::asprintf("FileType_%d", eType);
            objConfiguration[jsonKey] = m_eTargetForType[eType];
        }

        QJsonObject json;
        json["SentechSDKVersion"] = StApi::GetStApiVersionText().c_str();
        json["ConfigurationFileSetting"] = objConfiguration;

        QJsonDocument doc;
        doc.setObject(json);
        saveFile.write(doc.toJson());
    }
    catch(...)
    {
        QString message("Unable to save configuration to " + jsonFile);
        throw RUNTIME_EXCEPTION(message.toStdString().c_str());
    }
}

void DialogConfigurationFileSetting::showEvent(QShowEvent *)
{
    ui->lineEditPath->setText(m_qstrLastPath);
    ui->comboBoxNodeMap->setCurrentIndex(
                this->GetTargetForType(StConfigurationFileType_NodeMapWnd));
    ui->comboBoxImageDisplay->setCurrentIndex(
                this->GetTargetForType(StConfigurationFileType_DisplayImageWnd));
    ui->comboBoxDefectivePixelDetection->setCurrentIndex(
                this->GetTargetForType(StConfigurationFileType_DefectivePixelDetection));
    ui->comboBoxPixelFormatConverter->setCurrentIndex(
                this->GetTargetForType(StConfigurationFileType_PixelFormatConverter));
}

void DialogConfigurationFileSetting::on_buttonBox_accepted()
{
    this->SetPairTypeTarget(StConfigurationFileType_NodeMapWnd,
                            (EStConfigurationFileTarget_t)ui->comboBoxNodeMap->currentIndex());
    this->SetPairTypeTarget(StConfigurationFileType_DisplayImageWnd,
                            (EStConfigurationFileTarget_t)ui->comboBoxImageDisplay->currentIndex());
	this->SetPairTypeTarget(StConfigurationFileType_DefectivePixelDetection,
		(EStConfigurationFileTarget_t)ui->comboBoxDefectivePixelDetection->currentIndex());
    this->SetPairTypeTarget(StConfigurationFileType_PixelFormatConverter,
                            (EStConfigurationFileTarget_t)ui->comboBoxPixelFormatConverter->currentIndex());

    try
    {
        SaveConfigurationJson();
    }
    catch(GenICam::GenericException &e)
    {
        OnException(e);
    }

    this->accept();
}

void DialogConfigurationFileSetting::on_buttonBox_rejected()
{
    this->reject();
}

void DialogConfigurationFileSetting::on_pushButtonBrowse_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(
                this, "Select Base Directory to store StViewer configuration", m_qstrLastPath,
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks |
                QFileDialog::DontUseNativeDialog);
    if (dir.length() > 0)
    {
        m_qstrLastPath = dir;
        ui->lineEditPath->setText(m_qstrLastPath);
    }
}
