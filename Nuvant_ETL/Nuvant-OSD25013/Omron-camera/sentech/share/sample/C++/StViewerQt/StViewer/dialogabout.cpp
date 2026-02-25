#include "dialogabout.h"
#include "ui_dialogabout.h"

DialogAbout::DialogAbout(QWidget *parent, QString SDKVersion):
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
    ui->setupUi(this);

    ui->label->setText(QString(
        "<html><head/><body><p>StViewer<br />%1</p>"
        "</body></html>").arg(SDKVersion));

	// remove question mark
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

DialogAbout::~DialogAbout()
{
    delete ui;
}

void DialogAbout::on_btnOK_clicked()
{
    this->close();
}
