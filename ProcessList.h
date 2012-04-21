#ifndef PROCESSLIST_H
#define PROCESSLIST_H

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <vector>
#include <locale>
#include <sstream>
#include <string>
#include <iostream>

#include <QPixmap>

typedef struct _RUNNINGPROCESS {
    unsigned int pid;
    std::wstring name;
    std::string description;
    QPixmap icon;
} RUNNINGPROCESS;


std::vector<RUNNINGPROCESS> ProcessList();


#endif // PROCESSLIST_H
