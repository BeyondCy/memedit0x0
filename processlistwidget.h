#ifndef PROCESSLISTWIDGET_H
#define PROCESSLISTWIDGET_H

#include <QTableWidget>
#include <QHeaderView>
#include "ProcessList.h"

class ProcessListWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit ProcessListWidget(QWidget *parent = 0);

private:
    void fillProcessList();
    
public slots:
    void on_CurrentCellChanged(int row, int column, int prevR, int prevC);
    void on_CellDoubleClicked(int row, int column);

signals:
    void processSelected(RUNNINGPROCESS process);
    void processSelected();
    
};

#endif // PROCESSLISTWIDGET_H
