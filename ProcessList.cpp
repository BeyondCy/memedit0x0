#include "ProcessList.h"

std::vector<RUNNINGPROCESS> ProcessList()
{
    std::vector<RUNNINGPROCESS> processList;

    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;

    // allows listing of processes
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hProcessSnap == INVALID_HANDLE_VALUE) // major malfunction
        return processList; // just return empty list for now

    pe32.dwSize = sizeof(PROCESSENTRY32); // Set the size of the structure before using it

    if(!Process32First( hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);          // clean the snapshot object
        return processList; // empty
    }

    // Now walk the snapshot of processes
    do
    {
        RUNNINGPROCESS currentProcess;

        hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);

        if(hProcess == NULL) // major malfunction
            continue;

        std::wstring s = pe32.szExeFile;
        currentProcess.name = QString::fromStdWString(s);
        currentProcess.pid = pe32.th32ProcessID;

        HICON icon = ExtractIcon((HINSTANCE)hProcess, pe32.szExeFile, 0);
        if (icon)
        {
            QPixmap p = QPixmap::fromWinHICON(icon);
            currentProcess.icon = QIcon(p);
            DestroyIcon(icon); // free memory handle
        }/* */

        // ToDo: window title?  exe description?

        processList.push_back(currentProcess);
    }
    while(Process32Next(hProcessSnap, &pe32));

    return processList;
}
