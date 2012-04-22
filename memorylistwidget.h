#ifndef MEMORYLISTWIDGET_H
#define MEMORYLISTWIDGET_H

#include <stdio.h>

#include <QTableWidget>
#include <QHeaderView>
#include "MemoryScanner.h"

class MemoryListWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit MemoryListWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void scanUpdated(MemoryCell* head);
    
};

#endif // MEMORYLISTWIDGET_H
