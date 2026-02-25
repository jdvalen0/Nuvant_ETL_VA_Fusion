#ifndef MDICHILDSTILLIMAGE_H
#define MDICHILDSTILLIMAGE_H

#include <QWidget>
#include "mdichild.h"

namespace Ui {
class MdiChildStillImage;
}
class MdiChild;
class MainWindow;

class MdiChildStillImage final : public MdiChild
{
public:
    explicit MdiChildStillImage(QWidget *parent);
    ~MdiChildStillImage();

    // Open Camera and do initialization. Return false if camera is not opened.
    bool openCamera();
	bool openCamera(const QString &strFileName);

	void GetStatusBarText(size_t nIndex, QString &strText);

protected:
    // Register nodes to be displayed in the NodeMap window.
    void DisplayGenApiNodes();

	void OnCloseEvent();

	QString m_strUpdateTime;
private:
    Ui::MdiChildStillImage *ui;
};

#endif // MDICHILDSTILLIMAGE_H
