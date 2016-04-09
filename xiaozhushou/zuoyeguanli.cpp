#include "zuoyeguanli.h"
#include "ui_zuoyeguanli.h"
#include<QWebView>
#include<QProcess>
QString g_wangzhi="http://www.baidu.com";
extern QString g_ftpPath;
zuoyeguanli::zuoyeguanli(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zuoyeguanli)
{
    setWindowFlags(Qt::WindowTitleHint
                                  | Qt::CustomizeWindowHint |
                                  Qt::WindowMinimizeButtonHint |
                                  Qt::WindowMaximizeButtonHint|
                   Qt::WindowCloseButtonHint);
    ui->setupUi(this);

}

zuoyeguanli::~zuoyeguanli()
{
    delete ui;
}

void zuoyeguanli::on_webView_destroyed()
{

}

void zuoyeguanli::on_pushButton_2_clicked()
{
    QProcess::startDetached("explorer "+g_ftpPath);
}

void zuoyeguanli::on_pushButton_clicked()
{
     QProcess::startDetached("start "+g_wangzhi);
}
