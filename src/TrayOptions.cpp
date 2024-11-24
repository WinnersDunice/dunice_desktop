// TrayOptions.cpp


#include "TrayOptions.h"

TrayOptions::TrayOptions(QWidget *parent) : QWidget(parent)
{
    // Устанавливаем иконку для системного трея
    _trayIcon = new QSystemTrayIcon(this);
    _trayIcon->setIcon(QIcon(":/icons/icons/IBSon.png"));
    _trayIcon->setToolTip("Нажмите для отключения передачи информации");

    // Создаем меню для трея
    _trayMenu = new QMenu(this);
    // QAction *exitAction = new QAction("Выход", this);

    _trayIcon->setContextMenu(_trayMenu);
    // Подключаем действия
    connect(_trayIcon, &QSystemTrayIcon::activated, this, &TrayOptions::onTrayIconActivated);

    // Показываем иконку в системном трее
    _trayIcon->show();
}

void TrayOptions::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:  // Левый клик
        SetSendApps();
    default:
        break;
    }
}


void TrayOptions::SetSendApps()
{
    if(_sendDataOff)
    {
        _trayIcon->setIcon(QIcon(":/icons/icons/IBSon.png"));
        _trayIcon->setToolTip("Нажмите для отключения передачи информации");
        _sendDataOff = false;
        qDebug() << "ON";
    }
    else
    {
        _trayIcon->setIcon(QIcon(":/icons/icons/IBSoff.png"));
        _trayIcon->setToolTip("Нажмите для включения передачи информации");
        _sendDataOff = true;
        qDebug() << "OFF";
    }
}
