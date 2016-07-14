#include "processinfolist.h"

ProcessInfoList::ProcessInfoList(){

    QDir *dir = new QDir("/proc");
    QStringList dirProcessList = dir->entryList(QStringList("*"), QDir::AllDirs);
    QFile *stat;
    foreach(QString  str, dirProcessList){
        if(str.toInt()){
            QString src = "/proc/"+str.toUtf8() + "/stat";
//            stat->setFileName(src);
            stat = new QFile(src);
            stat->open(QIODevice::ReadOnly);
            ProcessInfo *p = getProcessInfoByStat(stat);
            processList.append(p);
//            qDebug() << p->toString();
            stat->close();
        }
        else
            continue;
    }
}
int ProcessInfoList::getRunningNumber(){
    int r = 0;
    for(int i = 0;i<processList.size();i++){
        if(processList.at(i)->processState.startsWith("R")){
            r++;
        }
    }
    return r;
}

ProcessInfo* ProcessInfoList::at(int i){
    return processList.at(i);
}

int ProcessInfoList::size(){
    return processList.size();
}

ProcessInfoList::ProcessInfoList(ProcessInfoList *p){
    this->processList = p->processList;
}
ProcessInfo* ProcessInfoList::getProcessInfoByStat(QFile *stat){
    ProcessInfo *processInfo = new ProcessInfo;
    QTextStream stream;
    QStringList list;
    QString buffer;
    stream.setDevice(stat);
    buffer = stream.readLine();
    list = buffer.split(" ");
    processInfo->processID  = list[0];
    processInfo->processName = list[1].replace("(", "").replace(")", "");
    processInfo->processState = list[2];
    processInfo->processNice = list[18];

    QFile uptimeFile("/proc/uptime");
    uptimeFile.open(QIODevice::ReadOnly);

    stream.setDevice(&uptimeFile);
    buffer = stream.readLine();
    int uptime = buffer.replace(QRegExp("\.[0-9]+ [0-9]+\.[0-9]+"), "").toInt();
    uptimeFile.close();
    int dif = uptime - list[21].toInt() / 100;
    processInfo->processRunningTime = dif;
    QTime startTime = QTime::currentTime().addSecs(-dif);
    double total_time = list[13].toDouble() + list[14].toDouble() + list[15].toDouble() + list[16].toDouble();
    double seconds = (double)uptime - (list[21].toDouble() / 100.0);
    processInfo->processVmRss = (double)(100 * ((total_time / 100) / seconds));
    return processInfo;

}
