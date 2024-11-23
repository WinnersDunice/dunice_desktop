// TrayOptions.cpp
#include "TrayOptions.h"

TrayOptions::TrayOptions(QWidget *parent) : QWidget(parent)
{
    // Устанавливаем иконку для системного трея
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon("C:/Users/Skrever/Documents/CyberGarden18/duniceDesktop/icons/icon.png"));

    // Создаем меню для трея
    QMenu *trayMenu = new QMenu(this);
    QAction *openAction = new QAction("Are u wining son?", this);
    // QAction *exitAction = new QAction("Выход", this);

    // Подключаем действия
    connect(openAction, &QAction::triggered, this, &TrayOptions::SetSendApps);
    // connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);

    trayMenu->addAction(openAction);
    // trayMenu->addAction(exitAction);

    trayIcon->setContextMenu(trayMenu);

    // Показываем иконку в системном трее
    trayIcon->show();
}
