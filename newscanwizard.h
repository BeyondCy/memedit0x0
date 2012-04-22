#ifndef NEWSCANWIZARD_H
#define NEWSCANWIZARD_H

#include <QWizard>
#include <QVBoxLayout>
#include <QAbstractButton>
#include "processlistwidget.h"
#include "startscanpage.h"

namespace Ui {
class NewScanWizard;
}

class NewScanWizard : public QWizard
{
    Q_OBJECT
    
public:
    explicit NewScanWizard(QWidget *parent = 0);
    ~NewScanWizard();

public slots:
    void on_currentIdChanged(int);
    
private:
    Ui::NewScanWizard *ui;

    StartScanPage* startScan;
    ProcessListWidget* processesListWidget;
};

#endif // NEWSCANWIZARD_H
