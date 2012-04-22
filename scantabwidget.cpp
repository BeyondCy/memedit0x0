#include "scantabwidget.h"

ScanTabWidget::ScanTabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    this->setTabPosition(QTabWidget::South);
    this->setTabShape(QTabWidget::Triangular);
    this->setCurrentIndex(0);
    this->setTabsClosable(true);
    this->setMovable(true); // can move tabs around

    this->connect(this, SIGNAL(currentChanged(int)), this, SLOT(on_tabWidget_currentChanged(int)));
    this->connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(on_tabWidget_tabCloseRequested(int)));
}

void ScanTabWidget::on_tabWidget_currentChanged(int index)
{
    this->currentScanner = index;
}

void ScanTabWidget::on_processSelected(RUNNINGPROCESS p, int searchSize, bool useInitial, int initialValue)
{
    MemoryListWidget* memoryTable = new MemoryListWidget(this);
    int index = this->addTab(memoryTable, p.icon, p.name);
    this->connect(this, SIGNAL(scanUpdated(MemoryCell*)),
                  memoryTable, SLOT(scanUpdated(MemoryCell*)));
    this->setCurrentIndex(index);
    this->scanners[index] = new MemoryScanner();

    if (this->count() == 1) // 1st open tab
        emit haveOpenScans(true);  // only need to send it once

    qDebug("PID: %d - searchsize: %d - useinitial: %d - initVal: %d", p.pid, searchSize, useInitial, initialValue);
    try {
        this->scanners[index]->startScan(p.pid, searchSize);
        SEARCH_CONDITION cond = (useInitial) ? COND_EQUALS : COND_UNCONDITIONAL;
        MemoryCell* head = this->scanners[index]->updateScan(cond, initialValue);

        emit scanUpdated(head);
    }catch(...){
        qDebug("Unhandled exception occurred...");
    }

    this->on_NewScan_rejected(); // just does cleanup
}

void ScanTabWidget::on_NewScan_rejected()
{
    delete this->newScan;
}

void ScanTabWidget::on_actionNew_Scan_triggered()
{
    this->newScan = new NewScanWizard(this);
    this->newScan->show();

    this->connect(this->newScan, SIGNAL(rejected()), this, SLOT(on_NewScan_rejected()));
    this->connect(this->newScan, SIGNAL(processSelected(RUNNINGPROCESS,int,bool,int)),
                  this, SLOT(on_processSelected(RUNNINGPROCESS,int,bool,int)));
    /*
    */
}

void ScanTabWidget::on_tabWidget_tabCloseRequested(int index)
{
    if (this->scanners.contains(index) && this->scanners[index])
    {
        delete this->scanners[index];
        this->scanners.remove(index);

        // we must shift all the keys above index down 1
        QMutableMapIterator<int, MemoryScanner*> i(this->scanners);
        while (i.hasNext())
        {
            i.next();
            if (i.key() <= index) continue;

            this->scanners.insert(i.key() - 1, i.value());
            this->scanners.remove(i.key());
        }
    }

    // QTabWidget does not free the actual tabs widget automatically
    QWidget* page = this->widget(index);
    this->removeTab(index);
    delete page;

    if (this->count() == 0)
        emit haveOpenScans(false);
}
