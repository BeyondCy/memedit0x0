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
