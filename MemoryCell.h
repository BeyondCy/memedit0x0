#pragma once
#include <windows.h>
#include <stdio.h>

typedef enum 
{
    COND_UNCONDITIONAL,
    COND_EQUALS,
    COND_INCREASED,
    COND_DECREASED,
} SEARCH_CONDITION;

class MemoryCell
{
public:
	MemoryCell(HANDLE hProc, MEMORY_BASIC_INFORMATION *meminfo, int data_size);
	~MemoryCell(void);

	void update(SEARCH_CONDITION condition, unsigned int val);
	bool isInSearch(unsigned int offset);
	void removeFromSearch(unsigned int offset);

	void setNext(MemoryCell* next);
	MemoryCell* getNext();

	int getSize() { return this->_size; }
	int getSearchDataSize() { return this->_searchDataSize; }

	void* getBaseAddress() { return this->_pBaseAddress; }

	unsigned int peek(unsigned int offset);
	void poke(unsigned int val/*, unsigned int offset*/);

protected:
	HANDLE _hProc; // the process the cell belongs to.
	unsigned char *_address; // the address of the cell
	void* _pBaseAddress; // address for windows calls
	int _size; // the size of the memory cell
    unsigned char *_buffer; // the data contained in the cell

    unsigned char *_searchMask; // boolean bit flags for each byte in the cell
    int _matches; // number of matches in a performed search
    int _searchDataSize; // the size of the search data

	MemoryCell* _next;
};
