#ifndef VERSIONINFO_H
#define VERSIONINFO_H
#include <QString>
#include <QFile>


class VersionInfo{
public:
    VersionInfo();
    VersionInfo(VersionInfo *v);
    QString getOsType();
    QString getOsVersion();
    QString getGccVersion();
    QString toString();
private:
    QString OsType;
    QString OsVersion;
    QString GccVersion;
};

#endif // VERSIONINFO_H
