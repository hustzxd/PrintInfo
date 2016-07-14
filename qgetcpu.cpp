#include "qgetcpu.h"

QGetCpu::QGetCpu(QObject *parent) :
    QObject(parent)
{
    user0 = user1 = system1 = system0 = nice0 = nice1 = idle0 = idle1 = 0;
    flag = 0;

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(calCpu()));
    timer->start(500);

}

QGetCpu::~QGetCpu()
{
    timer->stop();
    timer->destroyed();
}

int QGetCpu::openFile()
{
    file = new QFile(tr("/proc/stat"));
    if(file->open(QIODevice::ReadOnly))
        ;
        //qDebug()<<tr("open file ok!");
    else
    {
        qDebug()<<tr("open file error!");
        return -1;
    }

    return 0;
}

int QGetCpu::readFile()
{
    /*
    QDataStream in(file);
    in.setVersion(QDataStream::Qt_5_1);
    char cpuname[10];
    char user[10],nice[10],system[10],idle[10];
    in >> cpuname >> user >> nice >> system >> idle;
    qDebug()<<cpuname<<tr(" ")<<user<<tr(" ")<<nice<<tr(" ")<<system<<tr(" ")<<idle;
*/
    char buffer[256];
    QString buf;
    qint64 lineLen = file->readLine(buffer,sizeof(buffer));
    if(lineLen != -1)
    {
        //qDebug()<<tr("read file ok!")<<lineLen;
        //qDebug()<<buffer;
        buf = QString(buffer);
        //qDebug()<<buf<<buf.size();
        getCpuOccupy(buf);

    }
    else
    {
        qDebug()<<tr("read file error!");
        return -1;
    }

    return 0;
}

void QGetCpu::getCpuOccupy(QString buffer)
{
    flag++;

    if(flag == 1)
    {
        QStringList list = buffer.split(" ");
        user0 = list.at(2).toInt(NULL,10);
        nice0 = list.at(3).toInt(NULL,10);
        system0 = list.at(4).toInt(NULL,10);
        idle0 = list.at(5).toInt(NULL,10);
    }

    if(flag == 2)
    {
        QStringList list = buffer.split(" ");
        user1 = list.at(2).toInt(NULL,10);
        nice1 = list.at(3).toInt(NULL,10);
        system1 = list.at(4).toInt(NULL,10);
        idle1 = list.at(5).toInt(NULL,10);

        int total,idle;

        total = (user0 + nice0 + system0 + idle0) - (user1 + nice1 + system1 + idle1);
        idle = idle0 - idle1;
        rate = (double)(total - idle) / total * 100;

        emit sendCpuOccupy(rate);

        flag = 0;
    }

}
double QGetCpu::getCpuOccupy(){
    return rate;
}

int QGetCpu::closeFile()
{
    file->close();
    return 0;
}

void QGetCpu::calCpu()
{
    this->openFile();
    this->readFile();
    this->closeFile();
}
