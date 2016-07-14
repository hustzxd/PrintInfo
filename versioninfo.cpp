#include "versioninfo.h"

VersionInfo::VersionInfo(){
    OsType = "null";
    QFile *file = new QFile("/proc/version");
    file->open(QIODevice::ReadOnly|QIODevice::Text);
    QString versionData = QString(file->readAll());
    OsVersion = versionData.mid(0,versionData.indexOf("("));
    int index = versionData.indexOf("gcc version");
    GccVersion = versionData.mid(index,18);
}
VersionInfo::VersionInfo(VersionInfo *v){
    this->OsType = v->OsType;
    this->OsVersion = v->OsVersion;
    this->GccVersion = v->GccVersion;
}
QString VersionInfo::getGccVersion(){
    return GccVersion;
}
QString VersionInfo::getOsType(){
    return OsType;
}
QString VersionInfo::getOsVersion(){
    return OsVersion;
}
QString VersionInfo::toString(){
    return "Ostype : " + OsType + "\n" +
            "Osversion : " + OsVersion + "\n" +
            "GccVersion: " + GccVersion + "\n";
}

