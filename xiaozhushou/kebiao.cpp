#include"mingdan.h"
#include "kebiao.h"
#include "wkebiao.h"
#include "ui_wkebiao.h"
#include "ui_kebiao.h"
#include"structs.h"
#include <QUrl>
#include<QMessageBox>
#include<QDebug>
#include<string>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<QProcess>
#include<QStringList>

extern int g_courseIndex;
extern bool g_haveNextStep;
extern int g_courseNum;
extern QString g_jsPath;
extern QString g_jsRunPath;
extern bool g_haveNextStep;
extern QString g_teacherNum;//这些将在输入之后读取进去
extern QString g_totalCoursesNumPath;
extern QString g_coursesPath;
extern std::vector<KeCheng> g_kechengs;
extern int g_courseNum;

Kebiao::Kebiao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Kebiao)
{    setWindowFlags(Qt::WindowTitleHint
                    | Qt::CustomizeWindowHint |
                    Qt::WindowMinimizeButtonHint |
                    Qt::WindowMaximizeButtonHint|
     Qt::WindowCloseButtonHint);

    ui->setupUi(this);
  //  ui->webView->load(QUrl("http://jwzx.cqupt.edu.cn/new/labkebiao/showteakebiao2.php?tid=040317"));
  //  ui->webView->show();
}

Kebiao::~Kebiao()
{
    delete ui;
}




void Kebiao::on_listWidget_doubleClicked(const QModelIndex &index)
{
    int num=index.row();
    g_courseIndex=num;
    if(num>=g_courseNum){
        return;
    }
    this->close();
    QString   filename=g_jsPath+g_teacherNum+"/lastCourseIndex.txt";
    QFile file(filename);
    if (file.exists()) {//只有这种方法新建文件
       file.open( QIODevice::ReadWrite | QIODevice::Text);
       QTextStream out(&file);
       file.resize(0);
       out<<num;
       file.close();
       g_haveNextStep=true;
    }

}

void Kebiao::on_listWidget_clicked(const QModelIndex &index)
{

}
std::string getFileContent(QWidget *parent,QString lujing){
    QFile f(lujing);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(parent,"Warnning","打不开"+lujing,QMessageBox::Yes);
        exit(-1);
    }
    return f.readAll().toStdString();

}

void Kebiao::on_pushButton_clicked()
{
    int num=0;
    g_courseIndex=num;
    if(num>=g_courseNum){
        return;
    }
    this->close();
    QString   filename=g_jsPath+g_teacherNum+"/lastCourseIndex.txt";
    QFile file(filename);
    if (file.exists()) {//只有这种方法新建文件
       file.open( QIODevice::ReadWrite | QIODevice::Text);
       QTextStream out(&file);
       file.resize(0);
       out<<num;
       file.close();
       g_haveNextStep=true;
    }
   // using namespace std;
    //显示webview
   /* WKebiao m;
   // this->close();
    m.show();
    string head=getFileContent(this,g_jsPath+"head.html");
    string tail=getFileContent(this,g_jsPath+"tail.html");
    string thead="<tr style=\"height: 163.567px;\">";
    string ttail="</tr>";
   // string ktemp1[][]={{,},{,},{,}};

            <div style="display: block;" class="class-item">
            <p class="course">马克思主义基本原理</p>
            <p class="classroom">2107</p>
            <p class="teacher">刘红梅</p><p class="ts">1-18周</p>
            </div>

    for(int i=0;i<g_kechengs.size();i++){
        KeCheng &k=g_kechengs[i];
       // qDebug()<<k.time;
    }
    m.getUi()->webView->show();
    m.getUi()->webView->load("file:///"+g_jsPath+"kebiao.html");

    m.exec();*/

}

void Kebiao::on_pushButton_2_clicked()
{
    ;

    QProcess::startDetached("D:/QT/5.5/mingw492_32/bin/br.exe",QStringList("http://jwzx.cqupt.edu.cn/new/labkebiao/showteakebiao2.php?tid="+ g_teacherNum));

}

void Kebiao::on_pushButton_3_clicked()
{

}
