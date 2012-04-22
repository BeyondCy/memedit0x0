#include "newscanwizard.h"
#include "ui_newscanwizard.h"

NewScanWizard::NewScanWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::NewScanWizard)
{
    ui->setupUi(this);

    QVBoxLayout* processesLayout = new QVBoxLayout(this);
    ProcessListWidget* processes = new ProcessListWidget(this);
    processesLayout->addWidget(processes);
    this->ui->wizardPage1->setLayout(processesLayout);

    this->removePage(1);
    StartScanPage *startScan = new StartScanPage();
    this->addPage(startScan);

    this->setButtonText(QWizard::FinishButton, "Start Scan");
}

NewScanWizard::~NewScanWizard()
{
    delete ui;
}
