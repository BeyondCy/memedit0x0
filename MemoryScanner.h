#pragma once
#include <windows.h>
#include "MemoryCell.h"

class MemoryScanner
{
public:
	MemoryScanner(void);
	~MemoryScanner(void);

	MemoryCell* startScan(unsigned int pid, int data_size);
	MemoryCell* updateScan(SEARCH_CONDITION condition, unsigned int val);

private:
	MemoryCell* _head;

	HANDLE _hProc; // process being scanned.
};
