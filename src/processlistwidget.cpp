#include "processlistwidget.h"

ProcessListWidget::ProcessListWidget(QWidget *parent) :
    QTableWidget(parent)
{
    this->setAlternatingRowColors(true);
    this->setSortingEnabled(true);
    this->setColumnCount(2);
    QStringList labels;
    labels << tr("PID") << tr("Binary"); //<< tr("Description");
    this->setHorizontalHeaderLabels(labels);
    this->verticalHeader()->hide();
    this->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    this->setShowGrid(true);

    this->connect(this, SIGNAL(currentCellChanged(int,int,int,int)), this, SLOT(on_CurrentCellChanged(int,int,int,int)));
    this->connect(this, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(on_CellDoubleClicked(int,int)));

    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    fillProcessList(); //
}

void ProcessListWidget::on_CurrentCellChanged(int row, int column, int prevR, int prevC)
{
    this->selectRow(row);
   //this->item(row, column)->setText("wut");
}

void ProcessListWidget::on_CellDoubleClicked(int row, int column)
{
    RUNNINGPROCESS p;
    p.pid =  this->item(row, 0)->text().toInt();
    p.name = this->item(row, 1)->text();
    p.icon = this->item(row, 1)->icon();
}

RUNNINGPROCESS ProcessListWidget::selectedProcess()
{
    int row = this->currentRow();
    RUNNINGPROCESS p;
    p.pid =  this->item(row, 0)->text().toInt();
    p.name = this->item(row, 1)->text();
    p.icon = this->item(row, 1)->icon();
    return p;
}

void ProcessListWidget::fillProcessList()
{
    std::vector<RUNNINGPROCESS> processes = ProcessList();

    int row = 0;
    for (std::vector<RUNNINGPROCESS>::size_type i = 0; i != processes.size(); i++)
    {
        this->insertRow(row);

        QTableWidgetItem *pid = new QTableWidgetItem(QString::number(processes[i].pid));
        QTableWidgetItem *name =
                new QTableWidgetItem(/*QIcon(":/new/icons/icons/help.png"),*/
                                     processes[i].name);


            name->setIcon(processes[i].icon);

        pid->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        name->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

        this->setItem(row, 0, pid);
        this->setItem(row, 1, name);

        row++;
    }

}
