#include "mingdan.h"
#include "ui_mingdan.h"
#include"structs.h"
#include<cstdlib>
#include<ctime>
extern std::vector<KeCheng> g_kechengs;
extern QString g_deskPath;
extern QString g_teacherNum;
extern int g_courseIndex;
extern QString g_ftpPath;
extern QString g_jsPath;

Mingdan::Mingdan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mingdan)
{
    setWindowFlags(Qt::WindowTitleHint
                                  | Qt::CustomizeWindowHint |
                                  Qt::WindowMinimizeButtonHint |
                                  Qt::WindowMaximizeButtonHint|
                   Qt::WindowCloseButtonHint);
    ui->setupUi(this);
    startx=-1;
    this->isDm=false;
}
void Mingdan::closeEvent(QCloseEvent *event){
    this->isDm=false;
    event->accept();
}

Mingdan::~Mingdan()
{
    delete ui;
}
void Mingdan::update(){
  //  this->ui->horizontalLayoutWidget->setWindowOpacity(0.7);
   auto vec=g_kechengs[g_courseIndex].xueshengs;
//   ui->tableWidget->setColumnWidth(0,50);
   ui->tableWidget->setColumnWidth(2,40);
   ui->tableWidget->setColumnWidth(4,240);
   ui->tableWidget->setColumnWidth(5,53);
   ui->tableWidget->setColumnWidth(6,287);
   ui->tableWidget->setRowCount(vec.size());
   for(int i=0;i<vec.size();i++){
       Xuesheng &x=vec[i];
  //    qDebug()<<x.index;
      // ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(x.index)));
       QTableWidgetItem* a=new QTableWidgetItem(x.number);
       ui->tableWidget->setItem(i,0,a);
        a=new QTableWidgetItem(x.name);
       ui->tableWidget->setItem(i,1,new QTableWidgetItem(x.name));
       a=new QTableWidgetItem(x.sex);
       ui->tableWidget->setItem(i,2,new QTableWidgetItem(x.sex));
        a=new QTableWidgetItem(x.classNum);
       ui->tableWidget->setItem(i,3,new QTableWidgetItem(x.classNum));
       a=new QTableWidgetItem(x.major);
       ui->tableWidget->setItem(i,4,new QTableWidgetItem(x.major));

       QTableWidgetItem* checkBox = new QTableWidgetItem;
       a->setFlags(Qt::NoItemFlags);
       a->setFlags(Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
       checkBox->setCheckState(Qt::Checked);
       ui->tableWidget->setItem(i, 5, checkBox);


   }
   connect(ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(changeTest(int, int)));

   QString filename=g_jsPath+g_teacherNum+"/dianmingjilu.txt";
   QFile file(filename);
   if (!file.exists()) {//只有这种方法新建文件
      file.open( QIODevice::ReadWrite | QIODevice::Text);
      file.close();
   }

   if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
       QMessageBox::warning(this,"Warnning","打不开桌面",QMessageBox::Yes);
       return;
   }
   std::ifstream sin(filename.toStdString(), std::ios::in);
   //index num
   int index,num;
  // std::string jfx;
   while(sin>>index>>num){
     g_kechengs[g_courseIndex].xueshengs[index].kuangdao=num;
   //  g_kechengs[g_courseIndex].xueshengs[index].jiafenxiang=QString::fromStdString(jfx);
   }
}
void Mingdan::changeTest(int row, int col)
{
    if(col==5){
    Xuesheng &x=g_kechengs[g_courseIndex].xueshengs[row];
    if(ui->tableWidget->item(row, col)->checkState() == Qt::Checked) //选中
    {
        x.isLaiLe=true;
    }
    else
        x.isLaiLe=false;
    }
}

void Mingdan::on_tableWidget_cellClicked(int row, int column)
{
    if(column>4)
        return;
    if(row>=g_kechengs[g_courseIndex].xueshengs.size()){
        return;
    }
    QFile file("tmp.vbs");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
         QMessageBox::warning(this,"Warnning","can't open tmp.vbs",QMessageBox::Yes);
        return;
    }
    QTextStream out(&file);
    ui->tableWidget->selectRow(row);
                ui->tableWidget->setFocus();
    QString name=g_kechengs[g_courseIndex].xueshengs[row].name;
    out << "CreateObject(\"SAPI.SpVoice\").Speak "<<"\""<<name<<"\"";
    QProcess::startDetached("C:/windows/system32/wscript.exe "
    "tmp.vbs");

}

void Mingdan::on_pushButton_clicked()
{
      QString filename=g_deskPath+g_teacherNum+"老师的点名记录.txt";
     {
      QFile file(filename);
      if (!file.exists()) {//只有这种方法新建文件
         file.open( QIODevice::ReadWrite | QIODevice::Text);
         file.close();
      }

      if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
          QMessageBox::warning(this,"Warnning","打不开桌面",QMessageBox::Yes);
          return;
      }
      QTextStream out(&file);
      auto vec=g_kechengs[g_courseIndex].xueshengs;
      out <<g_kechengs[g_courseIndex].name<<" "<<QString("\n未到名单：")<<endl;
      int count=0;
      for(int i=0;i<vec.size();i++){
        Xuesheng &x=vec[i];
        if(!x.isLaiLe){
            count++;
            out <<x.number<<" "<<x.name<<endl;
        }
      }
      out<<QString("未到共：") << count<<QString("人")<<endl;
      ui->label_2->setText(QString("未到共：")+QString::fromStdString(std::to_string(count))
                           +QString("人,旷到率:")+QString::fromStdString(std::to_string(((double)count/vec.size())*100))
                           +"%");
     }
      filename=g_jsPath+g_teacherNum+"/dianmingjilu.txt";
      QFile file(filename);
      if (!file.exists()) {//只有这种方法新建文件
         file.open( QIODevice::ReadWrite | QIODevice::Text);
         file.close();
      }

      if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
          QMessageBox::warning(this,"Warnning","打不开文件",QMessageBox::Yes);
          return;
      }
      QTextStream out(&file);
      auto vec=g_kechengs[g_courseIndex].xueshengs;
      for(int i=0;i<vec.size();i++){
        Xuesheng &x=vec[i];
        if(!x.isLaiLe){
            x.kuangdao++;
        }
        if(x.kuangdao>0)
          out <<x.index<<" "<<x.kuangdao<<endl;

      }
      /*
          课程:040124面向对象程序设计
          未到名单：
          2012211511 刘茂
          2013211420 梁义怀
          2013211464 张志远
          2013211511 雷晶
          未到共：4人
      */

      //meta
      /*

       */

    //TODO

   // std::ofstream out;
   // out.open(filename.toStdString(), std::ofstream::out);
   /*  FILE *f= fopen(filename.toStdString().c_str(),"w+");
    if(f<=0){
        exit(-1);
    }
    auto vec=g_kechengs[g_courseIndex].xueshengs;
    fprintf(f,"%s 未到名单：\n",g_kechengs[g_courseIndex].name.toStdString().c_str());
   // out <<g_kechengs[g_courseIndex].name.toStdString()<<" "<<std::string("未到名单：")<<"\r\n";
    for(int i=0;i<vec.size();i++){
        Xuesheng &x=vec[i];
        if(!x.isLaiLe){
             fprintf(f,"%s \n",(x.number+" "+x.name).toStdString().c_str()); ;
        }
    }
    fclose(f);*/

}

void Mingdan::on_tableWidget_activated(const QModelIndex &index)
{

}

void Mingdan::on_pushButton_2_clicked()
{
    on_pushButton_clicked();
    QProcess::startDetached("explorer "+g_ftpPath);
    ui->label->setText("请从桌面复制点名记录到云端按成保存。");
}

void Mingdan::on_pushButton_3_clicked()
{

    isDm=true;
    for(int i=startx;i<(int)g_kechengs[g_courseIndex].xueshengs.size();i++){
     if(i==-1){
        speak("现在开始点名");
     }else {
        on_tableWidget_cellClicked(i,2);
        startx=i;
     }
     this->ui->progressBar->setValue(100*startx/g_kechengs[g_courseIndex].xueshengs.size());
     QElapsedTimer t;
     t.start();
     while(t.elapsed()<3000){
        QCoreApplication::processEvents();
     }
     if(!isDm){
        return ;
     }


    }
    isDm=false;
    if(startx==(int)g_kechengs[g_courseIndex].xueshengs.size()-1){
        this->ui->progressBar->setValue(100);
        speak("点名结束");
    }

}

void Mingdan::on_pushButton_5_clicked()
{
    if(isDm){
        isDm=false;
        speak("暂停点名");
        return ;
    }
    this->ui->progressBar->setValue(100*startx/g_kechengs[g_courseIndex].xueshengs.size());
}

void Mingdan::on_pushButton_6_clicked()
{

    isDm=false;
    speak("点名取消");
    startx=-1;
    this->ui->progressBar->setValue(0);
}

void Mingdan::on_pushButton_4_clicked()
{
    isDm=true;
    for(int i=startx;i<(int)g_kechengs[g_courseIndex].xueshengs.size();){
     if(i==-1){
        speak("现在开始点名");
        i=0;
     }else {
        on_tableWidget_cellClicked(i,2);
        startx=i;
     }
     this->ui->progressBar->setValue(100*startx/g_kechengs[g_courseIndex].xueshengs.size());
     QElapsedTimer t;
     t.start();
     while(t.elapsed()<3000){
        QCoreApplication::processEvents();
     }
     if(!isDm){
        return ;
     }
     srand((unsigned)time(0));

     i+=(rand()%6+1);
     if(i>=(int)g_kechengs[g_courseIndex].xueshengs.size()){

         i=(int)g_kechengs[g_courseIndex].xueshengs.size();
          startx=i-1;
     }

    }
    isDm=false;
    if(startx==(int)g_kechengs[g_courseIndex].xueshengs.size()-1){
        this->ui->progressBar->setValue(100);
        speak("点名结束");
    }


}
