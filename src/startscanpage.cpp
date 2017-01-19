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

int StartScanPage::initialValue()
{
    return this->ui->lineEditInitialValue->text().toInt();
}

int StartScanPage::searchSize()
{
    return this->ui->comboBoxSearchSize->currentText().at(0).digitValue();
}

bool StartScanPage::useInitial()
{
    return !this->ui->checkBoxUknownAll->isChecked();
}
