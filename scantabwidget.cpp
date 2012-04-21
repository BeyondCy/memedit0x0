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
    ProcessListWidget* table = new ProcessListWidget(this);
    int index = this->addTab(table, QIcon(":/new/icons/icons/help.png"), "New Scan");
    this->connect(table, SIGNAL(processSelected(int, QString)), this, SLOT(on_ProcessSelected(int, QString)));
    this->scanners[index] = new MemoryScanner();
}

void ScanTabWidget::on_ProcessSelected(int pid, QString name)
{
    qDebug("Got signal from the tablewidget.");
    int index = this->currentIndex();
    this->setTabText(index, name.append(" - ").append(QString::number(pid)));
    ProcessListWidget* w = (ProcessListWidget*) this->widget(index);
    this->setCurrentWidget(0);
    //delete w;
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
