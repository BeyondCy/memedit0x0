#ifndef STARTSCANPAGE_H
#define STARTSCANPAGE_H

#include <QWizardPage>
#include "ProcessList.h"

namespace Ui {
class StartScanPage;
}

class StartScanPage : public QWizardPage
{
    Q_OBJECT
    
public:
    explicit StartScanPage(QWidget *parent = 0);
    ~StartScanPage();

    void setTargetProcess(RUNNINGPROCESS p);
    
private:
    Ui::StartScanPage *ui;
};

#endif // STARTSCANPAGE_H
