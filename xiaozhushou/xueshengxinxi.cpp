#include "xueshengxinxi.h"
#include "ui_xueshengxinxi.h"
#include"structs.h"
#include <QFile>
#include <QTextStream>

extern std::vector<KeCheng> g_kechengs;
extern QString g_deskPath;
extern QString g_teacherNum;
extern int g_courseIndex;
extern QString g_ftpPath;
extern QString g_jsPath;

xueshengxinxi::xueshengxinxi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::xueshengxinxi)
{
    setWindowFlags(Qt::WindowTitleHint
                                  | Qt::CustomizeWindowHint |
                                  Qt::WindowMinimizeButtonHint |
                                  Qt::WindowMaximizeButtonHint|
                   Qt::WindowCloseButtonHint);
    ui->setupUi(this);

    auto vec=g_kechengs[g_courseIndex].xueshengs;
    ui->tableWidget->setColumnWidth(1,120);
    //ui->tableWidget->setColumnWidth(1,90);
    ui->tableWidget->setColumnWidth(2,60);
    ui->tableWidget->setColumnWidth(3,100);
    ui->tableWidget->setColumnWidth(4,210);
    ui->tableWidget->setColumnWidth(5,30);
    ui->tableWidget->setColumnWidth(6,30);
    ui->tableWidget->setColumnWidth(7,305);
    ui->tableWidget->setColumnWidth(8,92);
    ui->tableWidget->setColumnWidth(9,92);

    ui->tableWidget->setRowCount(vec.size());
    for(int i=0;i<vec.size();i++){
        Xuesheng &x=vec[i];

        ui->tableWidget->setItem(i,0,new QTableWidgetItem(x.number));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(x.name));//row,column,构建一个QTableWidgetItem对象
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(x.sex));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(x.classNum));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(x.major));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem("0"));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem("0"));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem("无"));
        ui->tableWidget->setItem(i,8,new QTableWidgetItem("待定"));
        ui->tableWidget->setItem(i,9,new QTableWidgetItem("待定"));
     }
    {

        std::ifstream in(g_jsPath.toStdString()+g_teacherNum.toStdString()+"/dianmingjilu.txt", std::ios::in);
        if (!in) {
            QMessageBox::warning(this,"Warnning","can't open "+g_jsPath+g_teacherNum+"/dianmingjilu.txt",QMessageBox::Yes);
            exit(-1);
        }

        int a,b;
        while(in>>a>>b)
        {
          ui->tableWidget->setItem(a,6,new QTableWidgetItem(QString::fromStdString(std::to_string(b))));
        }
    }


  /*  {
    QFile file(g_jsPath+g_teacherNum+"kname+/xshxinxi.txt");
    if(!file.open( QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::warning(this,"warning","打不开文件",QMessageBox::Yes);
        return;
    }

    QTextStream in(&file);
    QString str;
    while(!in.atEnd()) //读取文件中的内容到表格的对应单元里
    {
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            for(int k=5;k<10;k++)
            {
                str=in.readLine();
                ui->tableWidget->setItem(i,k,new QTableWidgetItem(str));
            }

        }

    }
}
*/


    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//不能修改表格内容
}

xueshengxinxi::~xueshengxinxi()
{
    delete ui;
}


void xueshengxinxi::on_pushButton_clicked()
{
    ui->tableWidget->setEditTriggers(QAbstractItemView::CurrentChanged);
}


void xueshengxinxi::on_pushButton_2_clicked()
{
    //KeCheng k;
    QString  filename=g_jsPath+g_teacherNum+"/xshxinxi.txt";
    QFile file(filename);
    if (!file.exists()) {
       file.open( QIODevice::ReadWrite | QIODevice::Text);//不存在就创建
       file.close();
    }

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        QMessageBox::warning(this,"Warnning","打不开文件",QMessageBox::Yes);
        return;
    }

    file.resize(0);
    QTextStream out(&file);



    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        out<< ui->tableWidget->item(i,5)->text()<<"\n" //写入到文件里。如同写到屏幕。
           << ui->tableWidget->item(i,6)->text()<<"\n"
           << ui->tableWidget->item(i,7)->text()<<"\n"
           << ui->tableWidget->item(i,8)->text()<<"\n"
           << ui->tableWidget->item(i,9)->text()<<endl;

    }
    file.close();

}
