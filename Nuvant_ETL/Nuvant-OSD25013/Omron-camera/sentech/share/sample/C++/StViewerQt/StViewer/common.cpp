#include "common.h"
#include <QMessageBox>

void OnException(const GenICam::GenericException &e)
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
