#include "newscanwizard.h"
#include "ui_newscanwizard.h"

NewScanWizard::NewScanWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::NewScanWizard)
{
    ui->setupUi(this);

    QVBoxLayout* processesLayout = new QVBoxLayout(this);
    this->processesListWidget = new ProcessListWidget(this);
    processesLayout->addWidget(processesListWidget);
    this->ui->wizardPage1->setLayout(processesLayout);

    this->removePage(1); // 2nd page
    this->startScan = new StartScanPage();
    this->addPage(startScan);

    this->setButtonText(QWizard::FinishButton, "Start Scan");

    this->connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(on_currentIdChanged(int)));
    //this->connect(this->button(QWizard::NextButton), SIGNAL(pressed()), this, SLOT();
}

NewScanWizard::~NewScanWizard()
{
    delete ui;
}

void NewScanWizard::on_currentIdChanged(int id)
{
    if (id == 1) // 2nd page.
    {
        RUNNINGPROCESS p = this->processesListWidget->selectedProcess();
        this->startScan->setTargetProcess(p);
        //this->startScan->getUi;
    }
}
