#ifndef DIALOGVIDEOCONFIGURATION_H
#define DIALOGVIDEOCONFIGURATION_H

#include <QDialog>
#include <QAbstractButton>
#include <QStandardItemModel>
#include "StApi_IP.h"
#include "StApi_GUI.h"

namespace Ui {
class DialogVideoConfiguration;
}

class DialogVideoConfiguration final : public QDialog
{
    Q_OBJECT

public:
    explicit DialogVideoConfiguration(StApi::IStVideoFiler *pIStVideoFiler, QWidget *parent = nullptr);
    ~DialogVideoConfiguration();

private slots:
    void on_btnAdd_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::DialogVideoConfiguration *ui;
    QStandardItemModel m_fileModel;

    StApi::IStVideoFiler *m_pIStVideoFiler;
    StApi::CIStNodeMapDisplayWndPtr m_pIStNodeMapDisplayWnd;
    QString m_qstrLastSavedVideoPath;

#ifdef Q_OS_WIN32
protected:
	void resizeEvent(QResizeEvent *event) override;
#endif //Q_OS_WIN32
};

#endif // DIALOGVIDEOCONFIGURATION_H
