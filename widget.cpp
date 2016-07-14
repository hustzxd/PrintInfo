#include "widget.h"
#include "ui_widget.h"
#include "main.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    highLightIndex = -1;

    CpuInfo cpuInfo = new CpuInfo;
    ui->cpu_name->setText(cpuInfo.getCpuName());
    ui->cpu_core->setText(QString::number(cpuInfo.getCpuNum()));
    ui->cpu_frequency->setText(cpuInfo.getCpuHz()+"MHz");
    ui->cache_size->setText(cpuInfo.getCache());
    ui->textEdit->setText(cpuInfo.getInfo());

    VersionInfo versionInfo = new VersionInfo;
    ui->kernel_version->setText(versionInfo.getOsVersion());
    ui->gcc_version->setText(versionInfo.getGccVersion());

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateMemInfo()));
    connect(timer,SIGNAL(timeout()),this,SLOT(updateProcessInfo()));
    qGetCpu = new QGetCpu;
    connect(qGetCpu,SIGNAL(sendCpuOccupy(double)),this,SLOT(updateCPUInfo()));
    timer->start(1000);

    ui->tableView->horizontalHeader()->setHighlightSections(false);
    ui->tableView->verticalHeader()->hide();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateProcessInfo(){
    //first get highlight index of colum;
    highLightIndex = ui->tableView->currentIndex().row();

    ProcessInfoList prolist = new ProcessInfoList;
    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("进程号")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("进程名")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("状态")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("优先级")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("CPU")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("运行时间")));

    for(int i=0;i<prolist.size();i++) {
//        model->setVerticalHeaderItem(i,QStandardItem(QString::number(i)));
        model->setItem(i,0,new QStandardItem("  "+prolist.at(i)->processID));
//        qDebug() << prolist.at(i)->processID;
        model->setItem(i,1,new QStandardItem(prolist.at(i)->processName));
        model->setItem(i,2,new QStandardItem(prolist.at(i)->processState));
        model->setItem(i,3,new QStandardItem(prolist.at(i)->processNice));
        model->setItem(i,4,new QStandardItem(QString::number(prolist.at(i)->processVmRss)));
        model->setItem(i,5,new QStandardItem(QString::number(prolist.at(i)->processRunningTime) +"s"));
    }
    ui->tableView->setModel(model);
    ui->tableView->setCurrentIndex(model->index(highLightIndex,0));

    ui->process_number->setText(QString::number(prolist.size()));
    ui->process_number_running->setText(QString::number(prolist.getRunningNumber()));

}


void Widget::updateCPUInfo(){
//    qDebug() << qGetCpu->getCpuOccupy();
    ui->progressBar->setValue((int)qGetCpu->getCpuOccupy());
}

void Widget::updateMemInfo(){
//    qDebug("update");
    MemInfo memInfo = new MemInfo;
    ui->progressBar_2->setValue(memInfo.getMemOccupancyRate()*100);
    ui->mem_total->setText(QString::number(memInfo.getMemTotal()/ 1000) + "MB");
    ui->mem_free->setText(QString::number(memInfo.getMemFree()/1000) + "MB");
    ui->mem_used->setText(QString::number((memInfo.getMemTotal()-memInfo.getMemFree())/1000) + "MB");
    ui->cached->setText(QString::number(memInfo.getCaches()/1000) + "MB");
    ui->buffer->setText(QString::number(memInfo.getBuffers()/1000)+ "MB");
    ui->swap_total->setText(QString::number(memInfo.getSwapTotal()/1000) + "MB");
    ui->swap_free->setText(QString::number(memInfo.getSwapFree() /1000) + "MB");
    ui->swap_used->setText(QString::number((memInfo.getSwapTotal()-memInfo.getSwapFree())/1000) + "MB");
    ui->progressBar_3->setValue(memInfo.getSwapOccupancyRate()*100);
}


void Widget::on_tableView_clicked(const QModelIndex &index)
{
//    index.column();
}

void Widget::on_cancel_process_btn_clicked()
{
    //kill the process
    QModelIndex index = ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0);
    QVariant spid = ui->tableView->model()->data(index, Qt::DisplayRole);
    pid_t pid = spid.toInt();
    qDebug() << QString::number(pid);
    QMessageBox message(QMessageBox::Warning,"Information","Really to kill process?",QMessageBox::Yes|QMessageBox::No,NULL);
    if (message.exec()==QMessageBox::Yes)
    {
        qDebug()<<"clicked yes\n";
        if (kill(pid, SIGHUP) == -1)
                QMessageBox::warning(0, "Kill", "ddddd");
    }
    else
    {
        qDebug()<<"clicked no\n";
    }
}

