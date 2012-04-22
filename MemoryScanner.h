#pragma once
#include <windows.h>
#include <BaseTsd.h>
#include <QDebug>
#include "MemoryCell.h"

class MemoryScanner
{
public:
	MemoryScanner(void);
	~MemoryScanner(void);

    MemoryCell* startScan(unsigned int pid, int data_size);
    MemoryCell* updateScan(SEARCH_CONDITION condition, unsigned int val);

    int getMatchCount();
    int getMatchCount(MemoryCell*); // for older searches

    MemoryCell* getHead() { return this->_head; }

private:
    MemoryCell* _head;
	HANDLE _hProc; // process being scanned.
    int _matchCount;

};
