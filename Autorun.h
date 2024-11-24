#ifndef AUTORUN_H
#define AUTORUN_H

#include <QSettings>
#include <QCoreApplication>

class Autorun {
public:
    static bool setAutoRun(bool enable) {
        QString appName = QCoreApplication::applicationName();
        QString appPath = QCoreApplication::applicationFilePath();
        QString regPath = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";

        QSettings settings(regPath, QSettings::NativeFormat);

        if (enable) {
            // Добавление программы в автозапуск
            settings.setValue(appName, appPath.replace('/', '\\'));
        } else {
            // Удаление программы из автозапуска
            settings.remove(appName);
        }

        return settings.status() == QSettings::NoError;
    }

    static bool isAutoRunEnabled() {
        QString appName = QCoreApplication::applicationName();
        QString regPath = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";

        QSettings settings(regPath, QSettings::NativeFormat);
        return settings.contains(appName);
    }
};

#endif // AUTORUN_H
