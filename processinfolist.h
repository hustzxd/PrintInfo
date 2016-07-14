#ifndef PROCESSINFOLIST_H
#define PROCESSINFOLIST_H

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QString>
#include "processinfo.h"
#include "main.h"

class ProcessInfoList{

public:

    ProcessInfoList();
    ProcessInfoList(ProcessInfoList *p);

    int size();
    ProcessInfo* at(int i);
    QList<ProcessInfo*> processList;

    ProcessInfo* getProcessInfoByStat(QFile *stat);
    int getRunningNumber();

};

#endif // PROCESSINFOLIST_H
