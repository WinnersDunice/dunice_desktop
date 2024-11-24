// TrayOptions.cpp


#include "TrayOptions.h"

TrayOptions::TrayOptions(QWidget *parent) : QWidget(parent)
{
    // Устанавливаем иконку для системного трея
    _trayIcon = new QSystemTrayIcon(this);
    _trayIcon->setIcon(QIcon(":/icons/icons/icon.png"));

    // Создаем меню для трея
    _trayMenu = new QMenu(this);
    _openAction = new QAction("Выключить отправку информации", this);
    // QAction *exitAction = new QAction("Выход", this);

    // Подключаем действия
    connect(_openAction, &QAction::triggered, this, &TrayOptions::SetSendApps);

    _trayMenu->addAction(_openAction);

    _trayIcon->setContextMenu(_trayMenu);

    // Показываем иконку в системном трее
    _trayIcon->show();
}

void TrayOptions::SetSendApps()
{
    if(_sendDataOff)
    {
        _sendDataOff = false;
        if(_openAction != nullptr) delete _openAction;
        _openAction = new QAction("Выключить отправку информации", this);
        connect(_openAction, &QAction::triggered, this, &TrayOptions::SetSendApps);
        qDebug() << "ON";
        _trayMenu->addAction(_openAction);
    }
    else
    {
        _sendDataOff = true;
        if(_openAction != nullptr) delete _openAction;
        qDebug() << "OFF";
        _openAction = new QAction("Включить отправку информации", this);
        connect(_openAction, &QAction::triggered, this, &TrayOptions::SetSendApps);
        _trayMenu->addAction(_openAction);
    }
}
