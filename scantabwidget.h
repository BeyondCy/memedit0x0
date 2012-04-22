#ifndef SCANTABWIDGET_H
#define SCANTABWIDGET_H

#include <QTabWidget>
#include <QStackedWidget>
#include <QSignalMapper>
// QMap contains better functionality than std::map
#include <QMap>

#include "newscanwizard.h"
#include "processlistwidget.h"
#include "MemoryScanner.h"

class ScanTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit ScanTabWidget(QWidget *parent = 0);
    
signals:
    void haveOpenScans(bool);
    
public slots:
    void on_tabWidget_tabCloseRequested(int index);
    //void on_tabWidget_destroyed();
    void on_tabWidget_currentChanged(int index);

    void on_actionNew_Scan_triggered();
    void on_NewScan_rejected();
    void on_NewScan_accepted();

    void on_ProcessSelected(RUNNINGPROCESS process);


private:
    QMap<int, MemoryScanner*> scanners;
    int currentScanner; // updated when user switches tabs..

    NewScanWizard* newScan;
    
};

#endif // SCANTABWIDGET_H
