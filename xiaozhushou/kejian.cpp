#include "kejian.h"
#include "ui_kejian.h"
#include <QProcess>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
extern QString g_jsPath;
extern QString g_ftpPath;
extern QString g_teacherNum;
kejian::kejian(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kejian)
{
    setWindowFlags(Qt::WindowTitleHint|
                   Qt::CustomizeWindowHint |
                   Qt::WindowMinimizeButtonHint |
                   Qt::WindowMaximizeButtonHint|
                   Qt::WindowCloseButtonHint);
     ui->setupUi(this);
     QString   filename=g_jsPath+g_teacherNum+"/kechengjilu.txt";
     QFile file(filename);
     if (!file.exists()) {//只有这种方法新建文件
        file.open( QIODevice::ReadWrite | QIODevice::Text);
        file.close();
     }

     if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
         QMessageBox::warning(this,"Warnning","打不开文件",QMessageBox::Yes);
         return;
     }

     QTextStream txtInput(&file);//写文本文件
     QString lineStr;
     while(!txtInput.atEnd())//一行一行读文件，直到文件末尾
     {
         lineStr += txtInput.readLine();
     }
      ui->label_4->setText(lineStr);//显示
}

kejian::~kejian()
{
    delete ui;
}



void kejian::on_lineEdit_textChanged(const QString &arg1)
{
    this->ui->label_4->setText(arg1);
}


void kejian::on_pushButton_4_clicked() //保存备忘，若不存在文件kejianjilu.txt，就新建文件，把记录写入到文件里
{
    QString   filename=g_jsPath+g_teacherNum+"/kechengjilu.txt";
    QFile file(filename);
    if (!file.exists()) {//只有这种方法新建文件
       file.open( QIODevice::ReadWrite | QIODevice::Text);
       file.close();
    }

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        QMessageBox::warning(this,"Warnning","打不开文件",QMessageBox::Yes);
        return;
    }

    file.resize(0);
    QTextStream out(&file);        //使用QTextStream写入到文件kechengjilu.txt  QTextStream是操作纯文本文件的类
    out <<this->ui->label_4->text()<<endl;

    file.close();


}


void kejian::on_pushButton_clicked()
{
    QProcess::startDetached("explorer "+g_ftpPath);
}

void kejian::on_pushButton_2_clicked()
{
    QProcess::startDetached("explorer "+g_ftpPath);
}



void kejian::on_pushButton_3_clicked()
{
    this->close();
}
