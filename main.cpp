//#include "mainwindow.h"
#include "CheckProcessor.h"
#include "CheckApplications.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <vector>
#include <QString>
#include <QtNetwork/QNetworkInterface>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString ID;
    CheckProcessor procCheck;
    ID = procCheck.BiosValue(2, 8, 8);

    CheckApplications Applications;
    std::vector<QString> out = Applications.GetListApps();

    for(QString& str : out)
    {
        qDebug() << str;
    }

    qDebug() << ID;
    return app.exec();
}
