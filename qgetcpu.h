#ifndef QGETCPU_H
#define QGETCPU_H

#include <QObject>
#include <QFile>
#include <QtDebug>
#include <QDataStream>
#include <QTimer>
#include <QStringList>


class QGetCpu : public QObject
{
    Q_OBJECT
public:
    explicit QGetCpu(QObject *parent = 0);

    ~QGetCpu();

    int openFile(void);

    int readFile(void);

    int closeFile(void);

    void getCpuOccupy(QString);

    double getCpuOccupy();

signals:

    void sendCpuOccupy(double);

public slots:
    void calCpu(void);

private:

    QFile *file;
    QTimer *timer;

    int user0;
    int nice0;
    int system0;
    int idle0;

    int user1;
    int nice1;
    int system1;
    int idle1;

    int flag;
    double rate;
};

#endif // QGETCPU_H
