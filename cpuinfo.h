#ifndef CPUINFO_H
#define CPUINFO_H
#include <QString>
#include <QFile>
#include <QDebug>

class CpuInfo
{
public:
    CpuInfo();
    CpuInfo(CpuInfo *cpuInfo);
    ~CpuInfo();
    QString getCpuName();
    QString getCpuType();
    QString getCpuHz();
    QString getCache();
    int getCpuNum();
    QString toString();
    QString getInfo();
private:
    QString cpuName;
    QString cpuType;
    QString cpuHz;
    QString cache;
    int cpuNum;
    QString info;
};

#endif // CPUINFO_H
