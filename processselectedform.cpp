#include "processselectedform.h"
#include "ui_processselectedform.h"

ProcessSelectedForm::ProcessSelectedForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProcessSelectedForm)
{
    ui->setupUi(this);

    //this->ui->groupBox->setTitle();
}

ProcessSelectedForm::~ProcessSelectedForm()
{
    delete ui;
}
