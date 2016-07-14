#ifndef PROCESSINFO_H
#define PROCESSINFO_H
#include <QString>
#include <QFile>
#include <QDir>

class ProcessInfo
{
public:
    ProcessInfo();
    ProcessInfo(ProcessInfo *pi);
    QString processID;
    QString processName;
    QString processState;
    QString processNice;
    float processVmRss;
    float processRunningTime;

    QString toString();
};


#endif // PROCESSINFO_H
