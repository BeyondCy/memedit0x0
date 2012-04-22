#ifndef SCANTABWIDGET_H
#define SCANTABWIDGET_H

#include <QTabWidget>
#include <QStatusBar>
#include <QLabel>
// QMap contains better functionality than std::map
#include <QMap>

#include "newscanwizard.h"
#include "memorylistwidget.h"
#include "processlistwidget.h"
#include "MemoryScanner.h"

class ScanTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit ScanTabWidget(QWidget *parent = 0, QStatusBar* statusBar = 0);
    
signals:
    void haveOpenScans(bool);
    void scanUpdated(MemoryScanner*);
    
public slots:
    void on_tabWidget_tabCloseRequested(int index);
    //void on_tabWidget_destroyed();
    void on_tabWidget_currentChanged(int index);

    void on_actionNew_Scan_triggered();
    void on_NewScan_rejected();

    void on_actionRefresh_triggered();
    void on_actionDecreased_triggered();
    void on_actionIncreased_triggered();
    void on_actionEquals_triggered();

    void on_processSelected(RUNNINGPROCESS p, int searchSize, bool useInitial, int initialValue);
    void on_scanUpdated(MemoryScanner *scan);

private:
    QMap<int, MemoryScanner*> scanners;
    int currentScanner; // updated when user switches tabs..

    NewScanWizard* newScan;
    QStatusBar* statusBar;
};

#endif // SCANTABWIDGET_H
