#include "MemoryCell.h"

MemoryCell::MemoryCell(HANDLE hProc, MEMORY_BASIC_INFORMATION *meminfo, int data_size)
{
	this->_hProc = hProc;
	this->_address = (unsigned char*) meminfo->BaseAddress;
	this->_pBaseAddress = meminfo->BaseAddress; 
	this->_size = meminfo->RegionSize;
	this->_buffer = (unsigned char*) operator new(meminfo->RegionSize);
	this->_searchMask = (unsigned char*) operator new(meminfo->RegionSize/8);
	memset (this->_searchMask, 0xff, meminfo->RegionSize/8); // sets entire mask to true
	this->_matches = meminfo->RegionSize;
	this->_searchDataSize = data_size;
	this->_next = NULL;
}

MemoryCell::~MemoryCell(void)
{
    if (this->_buffer)
        operator delete(this->_buffer);

    if (this->_searchMask)
        operator delete(this->_searchMask);
}


void MemoryCell::update(SEARCH_CONDITION condition, unsigned int val)
{
	static unsigned char tempbuf[128*1024]; // 128k
    unsigned int bytes_left;
    unsigned int total_read;
    unsigned int bytes_to_read;
    unsigned int bytes_read;

	// if its already 0, skip this memcell during scans because prior search already failed
	if (this->_matches > 0) 
    {
        bytes_left = this->_size;
        total_read = 0;
        this->_matches = 0; // set it to 0 til we find some this time.
    
        while (bytes_left)
        {
            bytes_to_read = (bytes_left > sizeof(tempbuf)) ? sizeof(tempbuf) : bytes_left;
            ReadProcessMemory (this->_hProc, 
				((unsigned char*)this->_pBaseAddress) + total_read, 
				tempbuf, bytes_to_read, (DWORD*)&bytes_read);
            
			if (bytes_read != bytes_to_read) // unknown error, didn't read as much as expected
				break;
    
            if (condition == COND_UNCONDITIONAL) // not searching for anything
            {
                memset (this->_searchMask + (total_read/8), 0xff, bytes_read/8); // set all good
                this->_matches += bytes_read; // 100% matches
            }
            else
            {
                unsigned int offset;
    
                for (offset = 0; offset < bytes_read; offset += this->_searchDataSize)
                {
                    if (this->isInSearch(total_read+offset))
                    {
                        bool is_match = false;
                        unsigned int temp_val;
                        unsigned int prev_val = 0;
    
                        switch (this->_searchDataSize)
                        {
                            case 1: // 1 byte
                                temp_val = tempbuf[offset];
                                prev_val = *((unsigned char*)&this->_buffer[total_read+offset]);
                                break;

                            case 2: // 2 bytes
                                temp_val = *((unsigned short*)&tempbuf[offset]);
                                prev_val = *((unsigned short*)&this->_buffer[total_read+offset]);
                                break;

                            case 4: // 4 bytes
                            default:
                                temp_val = *((unsigned int*)&tempbuf[offset]);
                                prev_val = *((unsigned int*)&this->_buffer[total_read+offset]);
                                break;
                        }
    
                        switch (condition)
                        {
                            case COND_EQUALS:
                                is_match = (temp_val == val);
                                break;
                            case COND_INCREASED:
                                is_match = (temp_val > prev_val);
                                break;
                            case COND_DECREASED:
                                is_match = (temp_val < prev_val);
                                break;
                            default:
                                break;
                        }
    
                        if (is_match)
                        {
                            this->_matches++;
                        }
                        else
                        {
                            this->removeFromSearch(total_read+offset);
                        }
                    }
                }
            }
    
            memcpy (this->_buffer + total_read, tempbuf, bytes_read);
    
            bytes_left -= bytes_read;
            total_read += bytes_read;
        }
    
        this->_size = total_read;
    }
}

bool MemoryCell::isInSearch(unsigned int offset)
{
	return this->_searchMask[(offset)/8] & (1<<((offset)%8));
}

void MemoryCell::removeFromSearch(unsigned int offset)
{
	this->_searchMask[(offset)/8] &= ~(1<<((offset)%8));
}

void MemoryCell::setNext(MemoryCell* next)
{
	this->_next = next;
}

MemoryCell* MemoryCell::getNext()
{
	return this->_next;
}

unsigned int MemoryCell::peek(unsigned int offset)
{
	unsigned int val = 0;//= peek (mb->hProc, mb->data_size, );

	if (ReadProcessMemory (this->_hProc, ((unsigned char*)this->_pBaseAddress) + offset, 
		&val, this->_searchDataSize, NULL) == 0)
    {
        printf ("peek failed\r\n");
    }

	return val;
}

void MemoryCell::poke(/*int data_size, unsigned int offset,*/ unsigned int val)
{
    if (WriteProcessMemory (this->_hProc, this->_pBaseAddress, &val, this->_searchDataSize, NULL) == 0)
    {
        printf ("poke failed\r\n");
    }
}
