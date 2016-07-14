#ifndef MEMINFO_H
#define MEMINFO_H
#include <QString>
#include <QFile>

class MemInfo
{
public:
    MemInfo();
    MemInfo(MemInfo *m);
    int getMemTotal();
    int getMemAvaliable();
    int getMemFree();
    int getSwapTotal();
    int getSwapFree();
    QString toString();
    float getMemOccupancyRate();
    float getSwapOccupancyRate();
    int getCaches();
    int getBuffers();
private:
    int memTotal;
    int memAvaliable;
    int memFree;
    int swapTotal;
    int swapFree;
    int caches;
    int buffers;
};


#endif // MEMINFO_H
