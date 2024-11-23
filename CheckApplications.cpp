#include "CheckApplications.h"

CheckApplications::CheckApplications() {}

std::vector<QString> CheckApplications::GetListApps()
{
    // Get the list of process identifiers.

    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;
    std::set<QString> output;

    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) throw 1;


    // Calculate how many process identifiers were returned.

    cProcesses = cbNeeded / sizeof(DWORD);

    // Print the name and process identifier for each process.

    for (i = 0; i < cProcesses; i++)
    {
        if (aProcesses[i] != 0 && hasVisibleWindow(aProcesses[i]))
            output.insert(GetProcessNameAndID(aProcesses[i]));
    }
    return std::vector<QString>(output.begin(), output.end());
}


QString CheckApplications::GetProcessNameAndID( DWORD processID )
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    // Get a handle to the process.

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                      PROCESS_VM_READ,
                                  FALSE, processID );
    // Get the process name.

    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod),
                               &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName,
                              sizeof(szProcessName)/sizeof(TCHAR) );
        }
    }

    QString output = "<unknown>";

    output = QString::fromWCharArray(szProcessName);

    // Release the handle to the process.
    CloseHandle( hProcess );

    return output;
}

bool CheckApplications::hasVisibleWindow(DWORD processID)
{
    bool hasVisible = false;

    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        DWORD pid;
        GetWindowThreadProcessId(hwnd, &pid);
        if (pid == lParam && IsWindowVisible(hwnd))
        {
            *(bool*)lParam = true;
            return FALSE; // Прекратить дальнейшее перечисление окон
        }
        return TRUE;
    }, (LPARAM)&hasVisible);

    return hasVisible;
}
