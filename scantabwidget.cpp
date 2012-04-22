#include "scantabwidget.h"

ScanTabWidget::ScanTabWidget(QWidget *parent, QStatusBar* statusBar) :
    QTabWidget(parent)
{
    this->statusBar = statusBar;

    this->setTabPosition(QTabWidget::South);
    this->setTabShape(QTabWidget::Triangular);
    this->setCurrentIndex(0);
    this->setTabsClosable(true);
    this->setMovable(false); // cant move tabs around til more signals

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

    this->connect(this, SIGNAL(scanUpdated(MemoryScanner*)),
                  this, SLOT(on_scanUpdated(MemoryScanner*)));

    this->setCurrentIndex(index);
    this->scanners[index] = new MemoryScanner();

    if (this->count() == 1) // 1st open tab
        emit haveOpenScans(true);  // only need to send it once

    try {
        this->scanners[index]->startScan(p.pid, searchSize);
        SEARCH_CONDITION cond = (useInitial) ? COND_EQUALS : COND_UNCONDITIONAL;
        MemoryCell* head = this->scanners[index]->updateScan(cond, initialValue);
        this->on_actionRefresh_triggered(); // to emit update

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

void ScanTabWidget::on_scanUpdated(MemoryScanner *scan)
{
    int amt = scan->getMatchCount(scan->getHead());
    this->statusBar->showMessage(QString::number(amt) + " matches found.", 10000);
}

void ScanTabWidget::on_actionRefresh_triggered()
{
    int index = this->currentIndex();

    MemoryListWidget* memoryTable = (MemoryListWidget*)this->widget(index);
    this->connect(this, SIGNAL(scanUpdated(MemoryScanner*)),
              memoryTable, SLOT(scanUpdated(MemoryScanner*)));
    emit scanUpdated(this->scanners[index]);

    this->disconnect(memoryTable);
}


void ScanTabWidget::on_actionDecreased_triggered()
{
    int index = this->currentIndex();
    this->scanners[index]->updateScan(COND_DECREASED, 0);
    this->on_actionRefresh_triggered();
}

void ScanTabWidget::on_actionIncreased_triggered()
{
    int index = this->currentIndex();
    this->scanners[index]->updateScan(COND_INCREASED, 0);
    this->on_actionRefresh_triggered();
}

void ScanTabWidget::on_actionEquals_triggered()
{
    int index = this->currentIndex();

    bool ok = false;
    int searchVal = QInputDialog::getInt(this, tr("Find"), "Enter search value:",
                                         0, -2147483647, 2147483647, 1, &ok);

    if (!ok) // pressed cancel
        return;

    this->scanners[index]->updateScan(COND_EQUALS, searchVal);
    this->on_actionRefresh_triggered();
}
