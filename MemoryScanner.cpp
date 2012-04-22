#include "MemoryScanner.h"

MemoryScanner::MemoryScanner(void)
{
    this->_hProc = NULL;
	this->_head = NULL;
    this->_matchCount = -1;
    this->_startAddress = 0;
}

MemoryScanner::~MemoryScanner(void)
{
    if (this->_hProc)
		CloseHandle (this->_hProc);

    while (this->_head != NULL)
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
        while (true)
        {
            // returns 0 on fail
            if (VirtualQueryEx (this->_hProc, addr, &meminfo, sizeof(meminfo)) == 0)
                break;

            if (this->_startAddress == 0)
                this->_startAddress = (unsigned char*)meminfo.BaseAddress;

            unsigned long base = (unsigned long) meminfo.BaseAddress;
            unsigned long start = (unsigned long) this->_startAddress;
            qDebug("Base: %d - Start: %d", base);
            unsigned long offset = (unsigned long)meminfo.BaseAddress - (unsigned long)this->_startAddress;
            qDebug("offset: 0x%08x\n\n", offset);

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

const unsigned char* MemoryScanner::getStartAddress()
{
    const unsigned char* start = this->_startAddress;
    return start;
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

int MemoryScanner::getMatchCount()
{
    return (this->_matchCount == -1) ? this->getMatchCount(this->_head) : this->_matchCount;
}

int MemoryScanner::getMatchCount(MemoryCell *memlist)
{
    MemoryCell *mb = memlist;
    int count = 0;

    while (mb)
    {
        count += mb->getMatches();
        mb = mb->getNext();
    }

    this->_matchCount = count;

    return count;
}
