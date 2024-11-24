//#include "mainwindow.h"
#define SLEEP 2000

#include "CheckProcessor.h"
#include "CheckApplications.h"
#include "DataSender.h"
#include "TrayOptions.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <vector>
#include <QString>
#include <QThread>
#include <QDir>
#include <QSettings>
#include <QtNetwork/QNetworkInterface>

void sendData(DataSender& sender, TrayOptions& Tray);
void addToStartup();

int main(int argc, char *argv[])
{
    addToStartup();

    QApplication app(argc, argv);
    TrayOptions Tray;
    QString ID;
    CheckProcessor procCheck;

    ID = procCheck.BiosValue(2, 8, 8);

    DataSender sender("https://dunicewinners.ru/user_info/" + ID.toStdString());

    QTimer timer;

    // Передаем функцию с фиксированным значением
    QObject::connect(&timer, &QTimer::timeout, [&]() { sendData(sender, Tray); });

    timer.start(SLEEP);


    return app.exec();
}

void startTimerWithFunction(QTimer& timer, std::function<void()> func, int interval)
{
    QObject::connect(&timer, &QTimer::timeout, [func]() {
        func();
    });
    timer.start(interval);
}

void sendData(DataSender& sender, TrayOptions& Tray)
{
    if(Tray.canSendAppsName())
    {
        try
        {
            CheckApplications Applications;
            std::vector<QString> out = Applications.GetListApps();
            qDebug() << "Try send data...";
            sender.sendData(out);
        }
        catch (QString& err)
        {
            qDebug() << err;
        }
    }
}

void addToStartup()
{
    // Путь к исполняемому файлу
    QString appPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());

    // Путь к ключу реестра для автозапуска
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);

    // Устанавливаем имя программы и путь
    settings.setValue("duniceDesktop", "\"" + appPath + "\"");

    if (settings.status() == QSettings::NoError)
        qDebug() << "Программа успешно добавлена в автозапуск.";
    else
        qDebug() << "Ошибка при добавлении программы в автозапуск.";
}
