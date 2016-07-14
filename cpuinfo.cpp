#include "cpuinfo.h"

CpuInfo::CpuInfo(){
    QFile *file = new QFile("/proc/cpuinfo");
    file->open(QIODevice::ReadOnly|QIODevice::Text);
    info = QString(file->readAll());
//    qDebug() << data << cpuInfo;
    QStringList datalist=info.split("\n");
//    qDebug() << cpuInfo;
    for(int i = 0 ;i < datalist.length();i++){
        QString line = datalist.at(i);
        if(line.startsWith("model name")){
            cpuName = line.mid(line.indexOf(":")+1);
            continue;
        }
        if(line.startsWith("vendor_id")){
            cpuType = line.mid(line.indexOf(":")+1);
            continue;
        }
        if(line.startsWith("cpu MHz")){
            cpuHz = line.mid(line.indexOf(":")+1);
            continue;
        }
        if(line.startsWith("cache size")){
            cache = line.mid(line.indexOf(":")+1);
            continue;
        }
        if(line.startsWith("cpu cores")){
            cpuNum = (line.mid(line.indexOf(":")+1)).toInt();
            continue;
        }
    }
    file->close();

}
CpuInfo::~CpuInfo(){

}

CpuInfo::CpuInfo(CpuInfo *cpuInfo){
    this->cpuName = cpuInfo->cpuName;
    this->cpuType = cpuInfo->cpuType;
    this->cpuHz = cpuInfo->cpuHz;
    this->cache = cpuInfo->cache;
    this->cpuNum = cpuInfo->cpuNum;
    this->info = cpuInfo->info;
}
QString CpuInfo::getCpuName(){
    return cpuName;
}
QString CpuInfo::getCpuType(){
    return cpuType;
}
QString CpuInfo::getCpuHz(){
    return cpuHz;
}
QString CpuInfo::getCache(){
    return cache;
}
QString CpuInfo::getInfo(){
    return info;
}
int CpuInfo::getCpuNum(){
    return cpuNum;
}


QString CpuInfo::toString(){
    return "cpuName = " + cpuName + "\n"+
            "cpuType  = " + cpuType +"\n"+
            "cpuHz = " + cpuHz + "\n"+
            "Cache = " + cache + "\n"+
            "cpuNum = " + QString::number(cpuNum) + "\n";
}
