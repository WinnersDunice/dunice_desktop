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
    QSystemTrayIcon* trayIcon;
    Q_OBJECT

private slots:
    void SetSendApps()
    {
        qDebug() << "penis.";
    }
public:
    //explicit TrayOptions(QWidget *parent = nullptr);
    explicit TrayOptions(QWidget *parent = nullptr);

//signals:
};

#endif // TRAYOPTIONS_H
