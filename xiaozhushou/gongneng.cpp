#include "gongneng.h"
#include "ui_gongneng.h"
#include "mingdan.h"
#include "kejian.h"
#include "xueshengxinxi.h"
#include "zuoyeguanli.h"
#include "structs.h"
#include"wkebiao.h"
#include "ui_wkebiao.h"
#include<QString>

extern bool g_bFanhui;
extern std::vector<KeCheng> g_kechengs;
extern int g_courseIndex;
extern QString g_jsPath;
extern QString g_teacherNum;
gongneng::gongneng(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gongneng)
{
    setWindowFlags(Qt::WindowTitleHint
                                  | Qt::CustomizeWindowHint |
                                  Qt::WindowMinimizeButtonHint |
                                  Qt::WindowMaximizeButtonHint|
                   Qt::WindowCloseButtonHint);
    ui->setupUi(this);
}

gongneng::~gongneng()
{
    delete ui;
}

void gongneng::on_pushButton_3_clicked()
{
    Mingdan m;
   // this->close();
    m.show();
    m.update();
    m.exec();
    this->show();
}
void gongneng::update2(){
    /*
    QString time;
    QString name;
    QString major;
    QString type;
    QString weekNum;
    QString classRoom;
    QString classesName;*/
    int i=g_courseIndex;
    ui->label->setText(QString("")+g_kechengs[i].classesName);
    int size=g_kechengs[i].time.size();
    ui->label_2->setText(QString("时间：")+g_kechengs[i].time.left(size-3).right(size-6));
    ui->label_3->setText(QString("")+g_kechengs[i].classRoom);
    ui->label_4->setText(QString("人数:")+QString::number(g_kechengs[i].xueshengs.size()));
    ui->label_9->setText(g_kechengs[i].weekNum);
    QPixmap pix(g_jsPath+g_teacherNum+".jpg");
    pix = pix.scaled(ui->label_10->width(),ui->label_10->height(),Qt::KeepAspectRatio);
    ui->label_10->setPixmap(pix);
     size=g_kechengs[i].name.size();
    ui->label_11->setText(g_kechengs[i].name.right(size-3));
}

void gongneng::on_pushButton_2_clicked()
{
    kejian k;
   // this->close();
    k.show();
    k.update();
    k.exec();
    this->show();
}



void gongneng::on_pushButton_clicked()
{
    this->close();
    g_bFanhui =true;
}

void gongneng::on_label_4_linkActivated(const QString &link)
{

}

void gongneng::on_pushButton_5_clicked()
{
    zuoyeguanli z;
   // this->close();
    z.show();
    z.update();
    z.exec();
    this->show();
}

void gongneng::on_pushButton_4_clicked()
{
    xueshengxinxi x;
    x.show();
    x.update();
    x.exec();
    this->show();
}

void gongneng::on_pushButton_6_clicked()
{
    QProcess::startDetached("D:/QT/5.5/mingw492_32/bin/br.exe",QStringList("http://jwzx.cqupt.edu.cn/new/labkebiao/showteakebiao2.php?tid="+ g_teacherNum));
}
