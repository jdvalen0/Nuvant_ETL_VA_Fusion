#include <QDir>

#include "cconfigurationfile.h"
#include "dialogconfigurationfilesetting.h"

const char * CConfigurationFile::m_pstrConfigFileName[StConfigurationFileType_Count] = {
    "DeviceNodeMapWnd.cfg",
    "DisplayImageWnd.cfg",
    "DefectivePixelDetection.cfg",
    "PixelFormatConverter.cfg"
};

CConfigurationFile::CConfigurationFile() :
    m_eTargetForType{StConfigurationFileTarget_None, StConfigurationFileTarget_None}
{
    this->RefreshConfiguration();
}

CConfigurationFile::~CConfigurationFile()
{
}

QString CConfigurationFile::GetSettingDir(EStConfigurationFileTarget_t eTarget,
                                          const StApi::IStDevice *pIStDevice)
{
    if (eTarget == StConfigurationFileTarget_None) return QString("");
    if (!pIStDevice) return QString("");

    const StApi::IStDeviceInfo *pIStDeviceInfo = pIStDevice->GetIStDeviceInfo();
    if (!pIStDeviceInfo) return QString("");

    QString folder = m_dirConfiguration.path();
    switch(eTarget)
    {
    case StConfigurationFileTarget_All:
        folder.append("/All");
        break;
    case StConfigurationFileTarget_SameModel:
        folder += QString::asprintf("/%s", pIStDeviceInfo->GetModel().c_str());
        break;
    case StConfigurationFileTarget_SameID:
        folder += QString::asprintf("/%s/%s", pIStDeviceInfo->GetModel().c_str(),
                                                  pIStDeviceInfo->GetID().c_str());
        break;
    }
    return folder;
}

QString CConfigurationFile::GetSettingDir(EStConfigurationFileTarget_t eTarget,
		QString &strFileName)
{
    if (eTarget == StConfigurationFileTarget_None) return QString("");
    if (strFileName.length() == 0) return QString("");

    QString folder = m_dirConfiguration.path();
    switch(eTarget)
    {
    case StConfigurationFileTarget_All:
        folder.append("/All");
        break;
    case StConfigurationFileTarget_SameModel:
    case StConfigurationFileTarget_SameID:
		folder += QString("/StillImage/");
		folder += strFileName;
        break;
    }
    return folder;
}

void CConfigurationFile::RefreshConfiguration()
{
    DialogConfigurationFileSetting dlg;
    dlg.LoadConfigurationJson();

    for (int eType = 0; eType < (int)StConfigurationFileType_Count; eType++)
        m_eTargetForType[eType] = dlg.GetTargetForType((EStConfigurationFileType_t)eType);
    m_dirConfiguration.setPath(dlg.GetConfigPath());
}

EStConfigurationFileTarget_t CConfigurationFile::getTargetForType(EStConfigurationFileType_t eType)
{
    return this->m_eTargetForType[eType];
}

void CConfigurationFile::LoadNodeMapSettingFile(GenApi::INodeMap *pINodeMap,
                                                EStConfigurationFileType_t eType,
                                                const StApi::IStDevice *pIStDevice)
{
    EStConfigurationFileTarget_t eTarget = getTargetForType(eType);
    if (eTarget == StConfigurationFileTarget_None) return;

	QString settingDir = GetSettingDir(eTarget, pIStDevice);
	if (settingDir.length() == 0) return;

	mLoadNodeMapSettingFile(pINodeMap, eType, settingDir);
}

void CConfigurationFile::SaveNodeMapSettingFile(GenApi::INodeMap *pINodeMap,
                                                EStConfigurationFileType_t eType,
                                                const StApi::IStDevice *pIStDevice)
{
    EStConfigurationFileTarget_t eTarget = getTargetForType(eType);
    if (eTarget == StConfigurationFileTarget_None) return;

    QString settingDir = GetSettingDir(eTarget, pIStDevice);
    if (settingDir.length() == 0) return;

	mSaveNodeMapSettingFile(pINodeMap, eType, settingDir);
}

void CConfigurationFile::mLoadNodeMapSettingFile(GenApi::INodeMap *pINodeMap,
	EStConfigurationFileType_t eType,
	QString &settingDir)
{

	QDir directory(settingDir);
	if (!directory.isReadable()) return;

	try
	{
		QString settingFile = QString("%1/%2").arg(directory.path()).arg(m_pstrConfigFileName[eType]);
		StApi::CIStFeatureBagPtr pIStFeatureBagPtr(StApi::CreateIStFeatureBag());
		pIStFeatureBagPtr->StoreFileToBag(settingFile.toStdString().c_str());
		pIStFeatureBagPtr->Load(pINodeMap, true);
	}
	catch (const GenICam::GenericException &e)
	{
		OnException(e);
	}
}

void CConfigurationFile::mSaveNodeMapSettingFile(GenApi::INodeMap *pINodeMap,
	EStConfigurationFileType_t eType,
	QString &settingDir)
{
    QDir directory(settingDir);
    if (!directory.exists())
    {
        bool createDir = directory.mkpath(settingDir);
        if (!createDir) return;
    }

    try
    {
        QString settingFile = QString("%1/%2").arg(settingDir).arg(m_pstrConfigFileName[eType]);
        StApi::CIStFeatureBagPtr pIStFeatureBagPtr(StApi::CreateIStFeatureBag());
        pIStFeatureBagPtr->StoreNodeMapToBag(pINodeMap);
        pIStFeatureBagPtr->SaveToFile(settingFile.toStdString().c_str());
    }
    catch(const GenICam::GenericException &e)
    {
        OnException(e);
    }
}


void CConfigurationFile::LoadNodeMapSettingFile(GenApi::INodeMap *pINodeMap, EStConfigurationFileType_t eType, QString &strFileName)
{
	EStConfigurationFileTarget_t eTarget = getTargetForType(eType);
	if (eTarget == StConfigurationFileTarget_None) return;

	QString settingDir = GetSettingDir(eTarget, strFileName);
	if (settingDir.length() == 0) return;

	mLoadNodeMapSettingFile(pINodeMap, eType, settingDir);
}

void CConfigurationFile::SaveNodeMapSettingFile(GenApi::INodeMap *pINodeMap, EStConfigurationFileType_t eType, QString &strFileName)
{
	EStConfigurationFileTarget_t eTarget = getTargetForType(eType);
	if (eTarget == StConfigurationFileTarget_None) return;

	QString settingDir = GetSettingDir(eTarget, strFileName);
	if (settingDir.length() == 0) return;

	mSaveNodeMapSettingFile(pINodeMap, eType, settingDir);
}
