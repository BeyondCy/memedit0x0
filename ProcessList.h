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

#include <QIcon>

typedef struct _RUNNINGPROCESS {
    unsigned int pid;
    QString name;
    std::string description;
    QIcon icon;
} RUNNINGPROCESS;


std::vector<RUNNINGPROCESS> ProcessList();
HWND hInstance2hWnd(HINSTANCE hIstance);


#endif // PROCESSLIST_H
