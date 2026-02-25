#ifndef DIALOGABOUT_H
#define DIALOGABOUT_H

#include <QDialog>

namespace Ui {
class DialogAbout;
}

class DialogAbout final : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAbout(QWidget *parent = nullptr, QString SDKVersion="");
    ~DialogAbout();

private slots:
    void on_btnOK_clicked();

private:
    Ui::DialogAbout *ui;
};

#endif // DIALOGABOUT_H
