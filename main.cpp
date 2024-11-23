//#include "mainwindow.h"
#include "CheckProcessor.h"
#include "CheckApplications.h"
#include "DataSender.h"

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

    try
    {

    DataSender sender("https://dunicewinners.ru/user_info/" + ID.toStdString());
    sender.sendData(out);

    }
    catch (QString& err)
    {
        qDebug() << err;
    }

    return app.exec();
}
