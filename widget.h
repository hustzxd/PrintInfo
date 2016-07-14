#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QTimer>
#include "qgetcpu.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_tabWidget_main_tabBarClicked(int index);

    void on_cancel_process_btn_clicked();

    // my slot to update process informations
    void updateProcess();

    void updateMemInfo();

    void updateCPUInfo();

    void updateProcessInfo();
    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    int highLightIndex;
    QGetCpu *qGetCpu;
    double rate;
};

#endif // WIDGET_H
