#ifndef TRAYOPTIONS_H
#define TRAYOPTIONS_H

#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QWidget>
#include <QIcon>
#include <QTimer>

class TrayOptions : public QWidget
{

private:
    QSystemTrayIcon* _trayIcon;

    bool _sendDataOff = false; //Отключил ли пользователь отправку сообщений о запущенных приложениях
    QAction* _openAction; // Ссылка на переключатель
    QMenu* _trayMenu; // Ссылка на меню

    Q_OBJECT

private slots:
    void SetSendApps();
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

public:
    explicit TrayOptions(QWidget *parent = nullptr);
    bool canSendAppsName(){return !_sendDataOff;};


};

#endif // TRAYOPTIONS_H
