#include "logging.h"
#include "kebiao.h"
#include "mingdan.h"
#include <QApplication>
#include<QDebug>
#include <QDesktopServices>
#include"structs.h"
#include "gongneng.h"
bool g_haveNextStep=false;
bool g_bFanhui=false;
QString g_deskPath;
QString g_jsPath = "E:/QTWorkspace/tmpjs/";
QString g_jsRunPath = "E:/QTWorkspace/tmpjs/run.js";
QString g_teacherNum;//教师账号//这些将在输入之后读取进去
QString g_totalCoursesNumPath;
QString g_coursesPath;
QString g_ftpPath="ftp://172.16.38.100/";//10.0.0.121
int g_lastCourseIndex;
int g_courseNum=-1;
int g_courseIndex=0;
std::vector<KeCheng> g_kechengs;
logging *g_loggingPtr;

int main(int argc, char *argv[])
{


   // speak("欢迎使用甘玲小助手");
    QApplication a(argc, argv);
    g_deskPath=QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    logging w;
    g_loggingPtr=&w;
    w.show();
    a.exec();
Lable:
    Kebiao k;
    {
        QString   filename=g_jsPath+g_teacherNum+"/lastCourseIndex.txt";
        QFile file(filename);
        if (!file.exists()) {//只有这种方法新建文件
           file.open( QIODevice::ReadWrite | QIODevice::Text);
           QTextStream out(&file);
           out<<0;
           file.close();
        }

        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){

            return -2;
        }
         QTextStream in(&file);
         in>>g_lastCourseIndex;
    if(g_haveNextStep){
        k.show();
        auto tmp=g_kechengs[g_lastCourseIndex];
        g_kechengs[g_lastCourseIndex]=g_kechengs[0];
        g_kechengs[0]=tmp;
        for(int i=0;i<g_courseNum;i++){
            KeCheng j= g_kechengs[i];
            QString tmp=j.time+" "+j.name+" "+j.weekNum+" "+j.classesName;
            QListWidgetItem * lw=new QListWidgetItem;
            k.getUi()->listWidget->addItem(lw);
            k.getUi()->listWidget->item(i)->setText(tmp);
        }
        g_haveNextStep=false;

        a.exec();
    }
    }
    gongneng z;
    g_bFanhui=false;
    if(g_haveNextStep){
        z.show();
        z.update2();
        z.update();
        z.exec();
    }
    if(g_bFanhui){
        goto Lable;
    }
        return 0;
}
