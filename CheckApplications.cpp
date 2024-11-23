#include "CheckApplications.h"
#include <QDebug>

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
        QString temp;
        if (aProcesses[i] != 0 && hasVisibleWindow(aProcesses[i]))
            temp = GetProcessNameAndID(aProcesses[i]);

        if(temp.toUpper() != "TEXTINPUTHOST.EXE" \
            && temp.toUpper() != "SYSTEMSETTINGS.EXE" && temp.toUpper() != "CORTANA.EXE" \
                    && temp.toUpper() != "APPLICATIONFRAMEHOST.EXE" && temp.toUpper() != "EXPLORER.EXE")
            output.insert(temp);
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
    struct EnumData {
        DWORD processID;
        bool hasVisible;
    };

    EnumData data = { processID, false };

    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        EnumData* pData = reinterpret_cast<EnumData*>(lParam);

        DWORD pid;
        GetWindowThreadProcessId(hwnd, &pid);

        if (pid == pData->processID) {
            // Проверяем, что окно видимо и не является вспомогательным
            LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
            LONG_PTR exStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);

            if ((style & WS_VISIBLE) && !(exStyle & WS_EX_TOOLWINDOW)) {
                pData->hasVisible = true;
                return FALSE; // Прекращаем поиск
            }
        }

        return TRUE; // Продолжаем поиск
    }, reinterpret_cast<LPARAM>(&data));

    return data.hasVisible;
}


