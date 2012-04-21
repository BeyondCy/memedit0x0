#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->tabWidget->clear();
    this->setCentralWidget(this->ui->tabWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Quit_triggered()
{
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    QMessageBox m;
    m.setText("Are you sure you wish to exit?");
    m.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    m.setWindowTitle("Exit");

    if (m.exec() == QMessageBox::Yes)
        e->accept();
    else
        e->ignore();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "About MemEdit0x0 v0.1", "For science...", QMessageBox::Ok);
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
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
    QWidget* page = this->ui->tabWidget->widget(index);
    this->ui->tabWidget->removeTab(index);
    delete page;
}

void MainWindow::on_tabWidget_destroyed()
{
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    this->currentScanner = index;
}

void MainWindow::on_actionNew_Scan_triggered()
{
    ProcessListWidget* table = new ProcessListWidget(this);
    int index = this->ui->tabWidget->addTab(table, QIcon(":/new/icons/icons/help.png"), "New Scan");
    this->connect(table, SIGNAL(processSelected(int, QString)), this, SLOT(on_ProcessSelected(int, QString)));
    this->scanners[index] = new MemoryScanner();
}

void MainWindow::on_ProcessSelected(int pid, QString name)
{
    qDebug("Got signal from the tablewidget.");
    int index = this->ui->tabWidget->currentIndex();
    this->ui->tabWidget->setTabText(index, name.append(" - ").append(QString::number(pid)));
    ProcessListWidget* w = (ProcessListWidget*) this->ui->tabWidget->widget(index);
    this->ui->tabWidget->setCurrentWidget(0);
}
