#include "meminfo.h"

MemInfo::MemInfo(){
    QFile *file = new QFile("/proc/meminfo");
    memTotal = 1;
    memAvaliable = 1;
    memFree = 1;
    swapTotal = 1;
    swapFree = 1;
    file->open(QIODevice::ReadOnly|QIODevice::Text);
    QString data = QString(file->readAll());
    QStringList dataList  = data.split("\n");
    for(int i =0 ;i<dataList.size();i++){
        QString line = dataList.at(i);
        if(line.startsWith("MemTotal:")){
            memTotal = line.simplified().section(" ",1,1).toInt();
            continue;
        }
        if(line.startsWith("MemFree:")){
            memFree = line.simplified().section(" ",1,1).toInt();
            continue;
        }
        if(line.startsWith("MemAvailable:")){
            memAvaliable = line.simplified().section(" ",1,1).toInt();
            continue;
        }
        if(line.startsWith("SwapTotal:")){
            swapTotal = line.simplified().section(" ",1,1).toInt();
            continue;
        }
        if(line.startsWith("SwapFree:")){
            swapFree = line.simplified().section(" ",1,1).toInt();
            continue;
        }
        if(line.startsWith("Buffers:")){
            buffers = line.simplified().section(" ",1,1).toInt();
            continue;
        }
        if(line.startsWith("Cached:")){
            caches = line.simplified().section(" ",1,1).toInt();
            continue;
        }
    }
    file->close();
}
MemInfo::MemInfo(MemInfo *m){
    memTotal = m->memTotal;
    memAvaliable = m->memAvaliable;
    memFree = m->memFree;
    swapTotal = m->swapTotal;
    swapFree = m->swapFree;
    caches = m->caches;
    buffers = m->buffers;
}
int MemInfo::getCaches(){
    return caches;
}
int MemInfo::getBuffers(){
    return buffers;
}

float MemInfo::getMemOccupancyRate(){
    return 1 - (float)memFree/memTotal;
}
float MemInfo::getSwapOccupancyRate(){
    return 1 - (float)swapFree/swapTotal;
}

int MemInfo::getMemTotal(){
    return memTotal;
}
int MemInfo::getMemFree(){
    return memFree;
}
int MemInfo::getSwapTotal(){
    return swapTotal;
}
int MemInfo::getSwapFree(){
    return swapFree;
}

QString MemInfo::toString(){
    return "memAvaliable" + QString::number(memAvaliable) + "\n"+
            "memFree: " + QString::number(memFree) + "\n" +
            "swapTotal: " +QString::number(swapTotal) + "\n"+
            "swapFree: " + QString::number(swapFree);

}
