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
    
signals:
    
public slots:
    void scanUpdated(MemoryScanner* scan);

    void on_itemChanged(QString item);
    void on_cellDoubleClicked(int r, int c);
};

#endif // MEMORYLISTWIDGET_H
