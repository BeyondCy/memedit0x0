#include "MemoryScanner.h"

MemoryScanner::MemoryScanner(void)
{
	this->_head = NULL;
}

MemoryScanner::~MemoryScanner(void)
{
	if (this->_hProc)
		CloseHandle (this->_hProc);

    while (this->_head)
    {
        MemoryCell *cell = this->_head;
        this->_head = this->_head->getNext();
        delete cell;
    }
}

MemoryCell* MemoryScanner::startScan(unsigned int pid, int data_size)
{
    MEMORY_BASIC_INFORMATION meminfo;
    unsigned char *addr = 0;
	this->_hProc = OpenProcess (PROCESS_ALL_ACCESS, FALSE, pid);
    if (this->_hProc)
    {
        while (1)
        {
            if (VirtualQueryEx (this->_hProc, addr, &meminfo, sizeof(meminfo)) == 0)
            {
                break;
            }

#define WRITABLE (PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)
            if ((meminfo.State & MEM_COMMIT) && (meminfo.Protect & WRITABLE))
            {
                MemoryCell *cell = new MemoryCell(this->_hProc, &meminfo, data_size);
                if (cell)
                {
                    cell->setNext(this->_head);
                    this->_head = cell;
                }
            }
            addr = (unsigned char*)meminfo.BaseAddress + meminfo.RegionSize;
        }
    }
	return this->_head;
}


MemoryCell* MemoryScanner::updateScan(SEARCH_CONDITION condition, unsigned int val)
{
	MemoryCell *cell = this->_head;
    while (cell)
    {
		cell->update(condition, val);
        cell = cell->getNext();
    }
	return this->_head;
}