//#include "mainwindow.h"
#include "CheckProcessor.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QtNetwork/QNetworkInterface>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString ID;
    CheckProcessor procCheck;
    ID = procCheck.BiosValue(2, 8, 8);

    qDebug() << ID;
    return app.exec();
}
