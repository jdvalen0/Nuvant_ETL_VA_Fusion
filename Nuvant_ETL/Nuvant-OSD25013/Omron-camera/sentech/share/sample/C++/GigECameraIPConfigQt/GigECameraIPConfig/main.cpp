#include "gigecameraipconfigdlg.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CGigECameraIPConfigDlg w;
    w.show();

    return a.exec();
}
