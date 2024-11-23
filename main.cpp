//#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <QtNetwork/QNetworkInterface>

# include <cstdint>
# include <cstdio>

#include <stdio.h>

struct CPUIDinfo
{
    uint32_t EAX;
    uint32_t EBX;
    uint32_t ECX;
    uint32_t EDX;
};

static inline void CpuId(unsigned int func, unsigned int subfunc,
                         CPUIDinfo& info)
{
    __asm__ __volatile__ (
        "cpuid"
        : "=a"(info.EAX), "=b"(info.EBX), "=c"(info.ECX), "=d"(info.EDX)
        : "a"(func), "c"(subfunc)
        );
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    for(int i=0;i<6;++i)
    {
        CPUIDinfo info;
        CpuId(i,0,info);

        qDebug() << i << info.EAX << info.EBX << info.ECX << info.EDX << "\n";

        printf("%d,0:%d,%d,%d,%d\n",i,info.EAX,info.EBX,info.ECX,info.EDX);
    }
    return a.exec();
}
