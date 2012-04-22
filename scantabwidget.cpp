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

void ScanTabWidget::on_actionNew_Scan_triggered()
{
    NewScanWizard* newScan = new NewScanWizard(this);
    newScan->show();
    /*
    QStackedWidget *sw = new QStackedWidget(this);
    ProcessListWidget* table = new ProcessListWidget(sw);
    ProcessSelectedForm* selectedForm = new ProcessSelectedForm(sw);

    ProcessListWidget* table2 = new ProcessListWidget();
    table2->show();



    sw->addWidget(table);
    sw->addWidget(selectedForm);
    //sw->addWidget(scannerTable);

    QSignalMapper *m = new QSignalMapper(this);

    sw->connect(table, SIGNAL(processSelected()), m, SLOT(map()));
    sw->connect(m, SIGNAL(mapped(int)), sw, SLOT(setCurrentIndex(int)));
    sw->setCurrentIndex(1);


    int index = this->addTab(sw, QIcon(":/new/icons/icons/help.png"), "New Scan");
    this->connect(table, SIGNAL(processSelected(RUNNINGPROCESS)), this, SLOT(on_ProcessSelected(RUNNINGPROCESS)));
    this->scanners[index] = new MemoryScanner();
    */
}

void ScanTabWidget::on_ProcessSelected(RUNNINGPROCESS p)
{
    int index = this->currentIndex();
    this->setTabText(index, p.name);
    this->setTabIcon(index, p.icon);

    // selected form time
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
}
