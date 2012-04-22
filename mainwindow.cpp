#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ScanTabWidget* scanTabs = new ScanTabWidget(this);
    this->connect(scanTabs, SIGNAL(haveOpenScans(bool)), this, SLOT(on_scanTab_haveOpenScans(bool)));
    this->connect(this->ui->actionNew_Scan, SIGNAL(triggered()), scanTabs, SLOT(on_actionNew_Scan_triggered()));
    this->setCentralWidget(scanTabs);
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
{/*
    QMessageBox m;
    m.setText("Are you sure you wish to exit?");
    m.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    m.setWindowTitle("Exit");

    if (m.exec() == QMessageBox::Yes)
        e->accept();
    else
        e->ignore();
        */
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "About MemEdit0x0 v0.1", "For science...", QMessageBox::Ok);
}

void MainWindow::on_scanTab_haveOpenScans(bool havescans)
{
    this->ui->actionPoke_Address->setEnabled(havescans);
    this->ui->actionRefresh->setEnabled(havescans);
    this->ui->actionSearch_Decreased->setEnabled(havescans);
    this->ui->actionSearch_Increased->setEnabled(havescans);
    this->ui->actionSearch_Value->setEnabled(havescans);
}
