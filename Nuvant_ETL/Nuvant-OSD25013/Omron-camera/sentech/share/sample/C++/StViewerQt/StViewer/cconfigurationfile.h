#ifndef CCONFIGURATIONFILE_H
#define CCONFIGURATIONFILE_H

#include <QString>
#include <QDir>

#include "common.h"

typedef enum _EStConfigurationFileTarget_t
{
    StConfigurationFileTarget_First = 0,
    StConfigurationFileTarget_None = 0,
    StConfigurationFileTarget_All,
    StConfigurationFileTarget_SameModel,
    StConfigurationFileTarget_SameID,
    StConfigurationFileTarget_Count
}EStConfigurationFileTarget_t;

typedef enum _EStConfigurationFileType_t
{
    StConfigurationFileType_First = 0,
    StConfigurationFileType_NodeMapWnd = 0,
    StConfigurationFileType_DisplayImageWnd,
    StConfigurationFileType_DefectivePixelDetection,
    StConfigurationFileType_PixelFormatConverter,
    StConfigurationFileType_Count
}EStConfigurationFileType_t;

class CConfigurationFile final
{
public:
    CConfigurationFile();
    ~CConfigurationFile();
    QString GetSettingDir(EStConfigurationFileTarget_t eTarget,
                          const StApi::IStDevice *pIStDevice);
	QString GetSettingDir(EStConfigurationFileTarget_t eTarget,
							QString &strFileName);

    void RefreshConfiguration();
    EStConfigurationFileTarget_t getTargetForType(EStConfigurationFileType_t eType);

    void LoadNodeMapSettingFile(GenApi::INodeMap *pINodeMap,
                                EStConfigurationFileType_t eType,
                                const StApi::IStDevice *pIStDevice);

	void LoadNodeMapSettingFile(GenApi::INodeMap *pINodeMap,
		EStConfigurationFileType_t eType,
		QString &strFileName);

    void SaveNodeMapSettingFile(GenApi::INodeMap *pINodeMap,
                                EStConfigurationFileType_t eType,
                                const StApi::IStDevice *pIStDevice);

	void SaveNodeMapSettingFile(GenApi::INodeMap *pINodeMap,
		EStConfigurationFileType_t eType,
		QString &strFileName);

private:
	void mLoadNodeMapSettingFile(GenApi::INodeMap *pINodeMap,
		EStConfigurationFileType_t eType,
		QString &settingDir);

	void mSaveNodeMapSettingFile(GenApi::INodeMap *pINodeMap,
		EStConfigurationFileType_t eType,
		QString &settingDir);
    EStConfigurationFileTarget_t m_eTargetForType[StConfigurationFileType_Count];
    QDir m_dirConfiguration;

    static const char *m_pstrConfigFileName[StConfigurationFileType_Count];
};

#endif // CCONFIGURATIONFILE_H
