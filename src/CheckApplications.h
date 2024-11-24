#ifndef CHECKAPPLICATIONS_H
#define CHECKAPPLICATIONS_H

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <Vector>
#include <set>
#include <QString>
#include <QException>

class CheckApplications
{
private:
    QString GetProcessNameAndID( DWORD processID );

public:
    CheckApplications();
    std::vector <QString> GetListApps();
    bool hasVisibleWindow(DWORD processID);
    bool isSystemProcess(const QString& processName);
};

#endif // CHECKAPPLICATIONS_H
