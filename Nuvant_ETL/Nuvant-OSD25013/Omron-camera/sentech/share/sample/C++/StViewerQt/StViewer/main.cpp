
#ifdef Q_OS_WIN32
#ifndef  _M_ARM64
#ifdef _DEBUG
#include <vld.h>
#endif //_DEBUG
#endif //_M_ARM64
#endif //Q_OS_WIN32
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w(&a);
	w.show();
	
    return a.exec();
}
