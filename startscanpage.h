#ifndef STARTSCANPAGE_H
#define STARTSCANPAGE_H

#include <QWizardPage>

namespace Ui {
class StartScanPage;
}

class StartScanPage : public QWizardPage
{
    Q_OBJECT
    
public:
    explicit StartScanPage(QWidget *parent = 0);
    ~StartScanPage();
    
private:
    Ui::StartScanPage *ui;
};

#endif // STARTSCANPAGE_H
