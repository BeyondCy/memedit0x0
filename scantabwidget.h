#ifndef SCANTABWIDGET_H
#define SCANTABWIDGET_H

#include <QTabWidget>
// QMap contains better functionality than std::map
#include <QMap>

#include "processlistwidget.h"
#include "MemoryScanner.h"

class ScanTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit ScanTabWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void on_tabWidget_tabCloseRequested(int index);
    //void on_tabWidget_destroyed();
    void on_tabWidget_currentChanged(int index);

    void on_actionNew_Scan_triggered();

    void on_ProcessSelected(int pid, QString name);


private:
    QMap<int, MemoryScanner*> scanners;
    int currentScanner; // updated when user switches tabs..
    
};

#endif // SCANTABWIDGET_H
