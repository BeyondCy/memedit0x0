#include "processlistwidget.h"

ProcessListWidget::ProcessListWidget(QWidget *parent) :
    QTableWidget(parent)
{
    this->setColumnCount(2);
    QStringList labels;
    labels << tr("PID") << tr("Executable"); //<< tr("Description");
    this->setHorizontalHeaderLabels(labels);
    this->verticalHeader()->hide();
    this->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    this->setShowGrid(true);


    std::vector<RUNNINGPROCESS> processes = ProcessList();

    int row = 0;
    for (std::vector<RUNNINGPROCESS>::size_type i = 0; i != processes.size(); i++)
    {
        this->insertRow(row);

        QTableWidgetItem *pid = new QTableWidgetItem(QString::number(processes[i].pid));
        QTableWidgetItem *name =
                new QTableWidgetItem(/*QIcon(":/new/icons/icons/help.png"),*/
                                     QString::fromStdWString(processes[i].name));

        pid->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        name->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

        this->setItem(row, 0, pid);
        this->setItem(row, 1, name);

        qDebug("%d - %s", processes[i].pid, processes[i].name);
        row++;
    }

    this->connect(this, SIGNAL(currentCellChanged(int,int,int,int)), this, SLOT(on_CellActivated(int,int,int,int)));
    this->connect(this, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(on_CellDoubleClicked(int,int)));
}

void ProcessListWidget::on_CellActivated(int row, int column, int prevR, int prevC)
{
   this->selectRow(row);
   //this->item(row, column)->setText("wut");
}

void ProcessListWidget::on_CellDoubleClicked(int row, int column)
{
    int pid = this->item(row, 0)->text().toInt();
    QString name = this->item(row, 1)->text();
    emit processSelected(pid, name);
}
