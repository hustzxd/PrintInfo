#include "processinfo.h"

ProcessInfo::ProcessInfo()
{
    this->processID = "";
    this->processName = "";
    this->processNice = "";
    this->processRunningTime = 0.0;
    this->processState = "";
    this->processVmRss = 0;

}

ProcessInfo::ProcessInfo(ProcessInfo *pi)
{
    this->processID = pi->processID;
    this->processName = pi->processName;
    this->processState = pi->processState;
    this->processNice = pi->processNice;
    this->processVmRss = pi->processVmRss;
    this->processRunningTime = pi->processRunningTime;
}
QString ProcessInfo::toString(){
    return "Id:" + processID + " name:"+processName+" state:"+processState+" nice:"+processNice+"\n";
}
