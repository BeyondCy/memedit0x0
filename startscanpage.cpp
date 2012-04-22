#include "startscanpage.h"
#include "ui_startscanpage.h"

StartScanPage::StartScanPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::StartScanPage)
{
    ui->setupUi(this);
}

StartScanPage::~StartScanPage()
{
    delete ui;
}

void StartScanPage::setTargetProcess(RUNNINGPROCESS p)
{
    this->ui->lineEditPID->setText(QString::number(p.pid));
    this->ui->lineEditProcessName->setText(p.name);
}
