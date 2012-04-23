#ifndef MEMORYLISTWIDGET_H
#define MEMORYLISTWIDGET_H

#include <stdio.h>

#include <QTableWidget>
#include <QMessageBox>
#include <QLineEdit>
#include <QHeaderView>
#include "MemoryScanner.h"

class MemoryListWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit MemoryListWidget(QWidget *parent = 0);

    void setScanner(MemoryScanner* mscan);
    
signals:
    
public slots:
    void scanUpdated(MemoryScanner* scan);

    void on_itemChanged(QTableWidgetItem *item);
    void on_cellDoubleClicked(int r, int c);

private:
    MemoryScanner* scanner;
};

#endif // MEMORYLISTWIDGET_H
