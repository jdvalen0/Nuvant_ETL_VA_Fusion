#ifndef DIALOGCONFIGURATIONFILESETTING_H
#define DIALOGCONFIGURATIONFILESETTING_H

#include <QDialog>

#include "StApi_TL.h"
#include "cconfigurationfile.h"

namespace Ui {
class DialogConfigurationFileSetting;
}

class DialogConfigurationFileSetting final : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConfigurationFileSetting(QWidget *parent = 0);
    ~DialogConfigurationFileSetting();

    void SetPairTypeTarget(EStConfigurationFileType_t eType, EStConfigurationFileTarget_t eTarget);
    EStConfigurationFileTarget_t GetTargetForType(EStConfigurationFileType_t eType);
    QString GetConfigPath();

    // Base configuration is located at $HOME/.sentech/StViewer and stored in Json format.
    void LoadConfigurationJson();
    void SaveConfigurationJson();

protected:
    void showEvent(QShowEvent *) override;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_pushButtonBrowse_clicked();

private:
    Ui::DialogConfigurationFileSetting *ui;
    QString m_qstrLastPath;
    EStConfigurationFileTarget_t m_eTargetForType[StConfigurationFileType_Count];

    static QString m_qstrJsonPath;
    static const char *m_strJsonFile;
};

#endif // DIALOGCONFIGURATIONFILESETTING_H
