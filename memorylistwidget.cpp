#include "memorylistwidget.h"

MemoryListWidget::MemoryListWidget(QWidget *parent) :
    QTableWidget(parent)
{
    this->setAlternatingRowColors(true);
    this->setSortingEnabled(true);
    this->setColumnCount(3);
    QStringList labels;
    labels << tr("Address") << tr("Hex Value") << tr("Decimal"); //<< tr("Description");

    this->setHorizontalHeaderLabels(labels);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    //this->verticalHeader()->hide();
    this->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    this->setShowGrid(true);

    //this->connect(this, SIGNAL(currentCellChanged(int,int,int,int)), this, SLOT(on_CurrentCellChanged(int,int,int,int)));
    //this->connect(this, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(on_CellDoubleClicked(int,int)));
    this->connect(this, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(on_itemChanged(QTableWidgetItem*)));
    //this->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MemoryListWidget::setScanner(MemoryScanner *mscan)
{
    this->scanner = mscan;
}

void MemoryListWidget::on_cellDoubleClicked(int r, int c)
{
}



void MemoryListWidget::on_itemChanged(QTableWidgetItem* item)
{
    int row = item->row();
    if (row == -1) return;

    //if (item->column() == 1) // is hexedit

    unsigned int addr = this->scanner->convert(this->item(row, 0)->text().toAscii().data());
    unsigned int data = this->scanner->convert(item->text().toAscii().data());

    if (!this->scanner->poke(addr, data))
    {
        QMessageBox m;
        m.setWindowTitle("Error");
        m.setText("An error occurred writing to process memory.");
        m.setStandardButtons(QMessageBox::Ok);
        m.exec();
        return;
    }

    qDebug("Write %d at %d (0x%08x)", data, addr, addr);
}

void MemoryListWidget::scanUpdated(MemoryScanner *scan)
{
    int matchcount = scan->getMatchCount();
    if (matchcount > 1000)
    {
        QMessageBox m;
        QString msg = "There are " + QString::number(matchcount) +  " cells in the search.\n\n";
        msg += "Would you like to load the values now?\n\n";
        msg += "Warning: this action is not reccomended until search is narrowed down.";
        m.setText(msg);
        m.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        m.setDefaultButton(QMessageBox::No);
        m.setWindowTitle("Large Data Size");

        if (m.exec() != QMessageBox::Yes)
            return;
    }

    static char buffer[256];
    unsigned int offset;
    MemoryCell *mb = scan->getHead();

    //this->clear();
    this->setRowCount(0);

    // Block signals while we fill in search vals
    this->blockSignals(true);

    int row = 0;
    while (mb)
    {
        for (offset = 0; offset < mb->getSize(); offset += mb->getSearchDataSize())
        {
            if (mb->isInSearch(offset))
            {
                this->insertRow(row);

                //unsigned int val = peek (mb->hProc, mb->data_size, (unsigned int)mb->addr + offset);
                unsigned int val = mb->peek(offset);

                sprintf(buffer, "0x%08x", ((unsigned int)mb->getBaseAddress()) + offset);
                QTableWidgetItem *address = new QTableWidgetItem(QString(buffer));
                address->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                sprintf(buffer, "0x%08x", val);
                QTableWidgetItem *hexVal = new QTableWidgetItem(QString(buffer));


                QTableWidgetItem *decVal = new QTableWidgetItem(QString::number(val));

                //this->connect(decVal, SIGNAL(textEdited(QString)), this, SLOT(on_itemChanged(QString)));

                this->setItem(row, 0, address);
                this->setItem(row, 1, hexVal);
                this->setItem(row, 2, decVal);


                //qDebug ("0x%08x: 0x%08x (%d) \r\n", ((unsigned int)mb->getBaseAddress()) + offset, val, val);
            }
        }

        mb = mb->getNext();
    }

    this->blockSignals(false); // re-enable signals
}
