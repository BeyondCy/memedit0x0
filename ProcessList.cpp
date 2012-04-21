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

        currentProcess.name = pe32.szExeFile;
        currentProcess.pid = pe32.th32ProcessID;


        HICON icon = ExtractIcon((HINSTANCE)hProcess, pe32.szExeFile, 0);
        if (icon)
        {
            QPixmap p = QPixmap::fromWinHICON(icon);
            currentProcess.icon = p;
            DestroyIcon(icon); // free memory handle
        }/* */
        else
        {
            DWORD err = GetLastError();
            qDebug("Error: %d", err);
        }


        processList.push_back(currentProcess);
    }
    while(Process32Next(hProcessSnap, &pe32));

    return processList;
}
/*
' Grab the first window handle that Windows finds:
 tempHwnd = FindWindow(vbNullString, vbNullString)

 ' Loop until you find a match or there are no more window handles:
 Do Until tempHwnd = 0
    ' Check if no parent for this window
    If GetParent(tempHwnd) = 0 Then
       ' Check for PID match
       If hInstance = ProcIDFromWnd(tempHwnd) Then
          ' Return found handle
          GetWinHandle = tempHwnd
          ' Exit search loop
          Exit Do
       End If
    End If

    *.
    ' Get the next window handle
    tempHwnd = GetWindow(tempHwnd, GW_HWNDNEXT)
 Loop
End Function
*/
