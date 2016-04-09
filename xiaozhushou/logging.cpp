#include "logging.h"
#include "ui_logging.h"
#include"structs.h"
#include"logging.h"
#include<QMessageBox>
#include <vector>
#include <fstream>
#include<stdlib.h>
#include<string.h>
#include<QProcess>
#include<QElapsedTimer>
#include<QDebug>
#include<QFile>
#include<vector>
extern QString g_jsPath;
extern QString g_jsRunPath;
extern bool g_haveNextStep;
extern QString g_teacherNum;//这些将在输入之后读取进去
extern QString g_totalCoursesNumPath;
extern QString g_coursesPath;
extern std::vector<KeCheng> g_kechengs;
extern int g_courseNum;
extern logging *g_loggingPtr;

QString g_nowId;
bool g_bRemove = false;
QString mingDanPath(int index){
    return g_jsPath+g_teacherNum+"/"+QString::number(index)+".tmp.txt";
}

logging::logging(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logging)
{

    setWindowFlags(Qt::WindowTitleHint
                                  | Qt::CustomizeWindowHint |
                                  Qt::WindowMinimizeButtonHint |
                                  Qt::WindowMaximizeButtonHint|
                   Qt::WindowCloseButtonHint);
    ui->setupUi(this);


    m_nTimerCount = 0;
    account_combo_box = ui->comboBox;
    list_widget = new QListWidget();

    account_combo_box->setModel(list_widget->model());
    account_combo_box->setView(list_widget);

    list_widget->setStyleSheet("QListView {show-decoration-selected: 0;}"
         " QListView::item:alternate {\
              background: #EEEEEE;\
          }"
         " QListView::item:selected {\
              border: -2px solid #FFFFFF;\
          }"
         "QListView::item:selected:active {\
             background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
                                         stop: 0 #358ccc, stop: 1 #358ccc);\
         }");
   // account_combo_box->setEditable(true); //设置QComboBox可编辑
    //登录记录格式：
    //TODO按照文件记录来读取头像和账号
    //
    std::ifstream in((g_jsPath+"logging.txt").toStdString(), std::ios::in);
    if (!in) {
      QMessageBox::warning(this,"Warnning","can't open "+g_coursesPath,QMessageBox::Yes);
       exit(-1);
    }
    std::string id;
    std::string name;
    QString firstId;
    for(int i=0; i<10; i++)
    {
         if(in>>id>>name==0)break;
         if(i==0)firstId=QString::fromStdString(id);
         AccountItem *account_item = new AccountItem();
         account_item->id=QString::fromStdString(id);
         account_item->name=QString::fromStdString(name);
         g_nowId=QString::fromStdString(id);
         account_item->touxPath=g_jsPath+QString::fromStdString(id)+".jpg";
         account_item->setAccountNumber(QString::fromStdString(id));
         connect(account_item, SIGNAL(showAccount(QString)), this, SLOT(showAccount(QString)));
         connect(account_item, SIGNAL(removeAccount(QString)), this, SLOT(removeAccount(QString)));
         connect(account_item, SIGNAL(changeAccount(QString)), this, SLOT(changeAccount(QString)));
         QListWidgetItem *list_item = new QListWidgetItem(list_widget);
         list_widget->setItemWidget(list_item, account_item);
         account_item->setMouseTracking(true);
         if(i == 0)
         {
          //     list_item->setSelected(true);
               list_item->setSizeHint(QSize(TX_BIG,TX_BIG));
         }
         else
               list_item->setSizeHint(QSize(TX_SMALL,TX_SMALL));
    }

   timer = new QTimer();
   this->connect(timer,SIGNAL(timeout()),this,SLOT(slotTime()));
   showAccount(firstId);

}
void logging::showAccount(QString account)
{
    int list_count = list_widget->count();
    for(int i=0; i < list_count;i++)
    {
        QListWidgetItem *item = list_widget->item(i);
        AccountItem *account_item = (AccountItem *)(list_widget->itemWidget(item));
        QString account_number = account_item->getAccountNumber();
        if(account == account_number)
        {
            QPixmap pix(account_item->touxPath);
            pix = pix.scaled(ui->label_2->width(),ui->label_2->height(),Qt::KeepAspectRatio);
            ui->label_2->setPixmap(pix);
            break;
        }
    }

       account_combo_box->setEditText(account);
       account_combo_box->hidePopup();
}

void logging::removeAccount(QString account)
{


       int list_count = list_widget->count();
       for(int i=0; i < list_count;i++)
       {
           QListWidgetItem *item = list_widget->item(i);
           AccountItem *account_item = (AccountItem *)(list_widget->itemWidget(item));
           QString account_number = account_item->getAccountNumber();
           if(account == account_number)
           {
               delete list_widget->takeItem(i);
               break;
           }
       }
       if(list_count > 0&&list_widget->item(0)!=0)
       {
           QListWidgetItem *item = list_widget->item(0);
           item->setSizeHint(QSize(TX_BIG,TX_BIG));
           g_bRemove = true;
       }
       account_combo_box->hidePopup();
       account_combo_box->showPopup();
}

void logging::proxyChange(int index)
{
}

void logging::slotTime()
{
       m_nTimerCount += 2;

       QListWidgetItem *item0 = list_widget->item(m_nNow);
       QListWidgetItem *item1 = list_widget->item(m_nLast);
       if(item0 != NULL)
           item0->setSizeHint(QSize(TX_SMALL+m_nTimerCount,TX_SMALL+m_nTimerCount));
       if(item1 != NULL)
           item1->setSizeHint(QSize(TX_BIG-m_nTimerCount,TX_BIG-m_nTimerCount));
       if(m_nTimerCount >= 10)
           timer->stop();
}
void logging::changeAccount(QString account)
{
   //    account_combo_box->setEditText(account);

       static QString str = "";
     int list_count = list_widget->count();
       if(timer->isActive())
       {
           timer->stop();
           QListWidgetItem *item0 = list_widget->item(m_nNow);
           QListWidgetItem *item1 = list_widget->item(m_nLast);
           if(item0 != NULL)
               item0->setSizeHint(QSize(TX_BIG,TX_BIG));
           if(item1 != NULL)
               item1->setSizeHint(QSize(TX_SMALL,TX_SMALL));
       }
       for(int i=0; i < list_count;i++)
       {
           QListWidgetItem *item = list_widget->item(i);
           AccountItem *account_item = (AccountItem *)(list_widget->itemWidget(item));
           QString account_number = account_item->getAccountNumber();
           if(account == account_number && account != str) //避免重复
           {
               m_nNow = i;
               item->setSelected(true);
               m_nTimerCount = 0;
           }
           if(account != account_number && account_number == str)
           {
               m_nLast = i;
           }
       }
       if(g_bRemove)
       {
           str = account;
           g_bRemove = false;
           return;
       }
       timer->start(30);
       str = account;

}

void logging::mousePressEvent(QMouseEvent *)
{
           account_combo_box->hidePopup();
}
AccountItem::AccountItem(QWidget *parent)
{
       mouse_press = false;
       account_number = new QLabel();
       delede_button = new QPushButton();
       QPixmap pixmap(g_jsPath+"icon_error.bmp");
       delede_button->setIcon(pixmap);
       delede_button->setIconSize(pixmap.size());
       delede_button->setStyleSheet("background:transparent;");
       connect(delede_button, SIGNAL(clicked()), this, SLOT(removeAccount()));

       lab = new QLabel;
       QPixmap pTimePix(g_jsPath+g_nowId);
       lab->setPixmap(pTimePix);
       lab->setAlignment(Qt::AlignCenter);
       lab->setScaledContents(true);
       lab->setFixedSize(TX_SMALL,TX_SMALL);

       QHBoxLayout *main_layout = new QHBoxLayout();
       main_layout->addStretch();
       main_layout->addWidget(delede_button);
       main_layout->setContentsMargins(1, 0, 1, 0);
       main_layout->setSpacing(5);
       this->setLayout(main_layout);
}

void AccountItem::mouseMoveEvent(QMouseEvent *)
{
       static bool bFirst = false;
       static QString str;
       QString account_number_text = account_number->text();
       if(!bFirst)
       {
           bFirst = true;
           str = account_number_text;
       }
       if(str != account_number_text)
       {
           emit changeAccount(account_number_text);
           str = account_number_text;
           QString fileName=this->touxPath;

       }

}
void AccountItem::paintEvent(QPaintEvent *)
{
       QPainter painter1;
       painter1.begin(this);
       painter1.setPen(QColor(0,0,0,0));

       QSize nSize = this->size();
       QRectF target(0.0, 2.0, nSize.height()-4, nSize.height()-4);
       QSize szImage;
       szImage.setWidth(nSize.height() - 2);
       szImage.setHeight(nSize.height() - 2);
       QImageReader reader;                                     // 设置图片名
       reader.setFileName(this->touxPath);              // 读取图片大小
       QSize imageSize = reader.size();                     // 缩放图片尺寸以适应屏幕大小
       imageSize.scale(szImage, Qt::KeepAspectRatio); // 设置图片大小，size()为屏幕大小
       reader.setScaledSize(imageSize);                    // 读取图片
       QImage image = reader.read();                       // 转换成QPixmap
//       QPixmap pixmap = QPixmap::fromImage(image);

       QPainterPath path1;
       path1.addRoundedRect(target,3,3,Qt::AbsoluteSize);
   //    path1.addRoundRect(0, 2, nSize.height() - 4, nSize.height() - 4,10,10);
       QBrush brush(image);
       painter1.setBrush(brush);
       painter1.drawPath(path1);

       painter1.setPen(Qt::black);
       if(nSize.height() < 35)
           painter1.drawText(nSize.height() + 10,nSize.height()/2 + 5,this->name);
       else
       {
           painter1.drawText(nSize.height() + 10,nSize.height()/2 - 4,this->name);
           painter1.setPen(QColor(255,255,255));
           painter1.drawText(nSize.height() + 10,nSize.height()/2 +12,this->id);
       }
       painter1.end();




}
//_______________________________________________________________________________________________________________
logging::~logging()
{
    if(timer->isActive())
        {
            timer->stop();
            timer = NULL;
        }
    delete ui;
}
void logging::load(){
    using namespace std;
        int total;
        {
            std::ifstream in(g_totalCoursesNumPath.toStdString(), std::ios::in);
            if (!in) {
                QMessageBox::warning(this,"Warnning","can't open "+g_totalCoursesNumPath,QMessageBox::Yes);
                exit(-1);
            }

            in >> total;
            in.close();
        }
        g_courseNum=total;
        std::ifstream in(g_coursesPath.toStdString(), std::ios::in);
        if (!in) {
            QMessageBox::warning(this,"Warnning","can't open "+g_coursesPath,QMessageBox::Yes);
            exit(-1);
        }


        std::string line;
        string time;
        string name;
        string major;
        string type;
        string weekNum;
        string classRoom;
        string classesName;

        int index;
      //  QString major;
        string number;
      //  QString name;
        string sex;
        string classNum;
        string state;

        for (int i = 0; i < total; i++) {
            KeCheng k;
            std::ifstream sin(mingDanPath(i).toStdString(), std::ios::in);
            if (!sin) {
                QMessageBox::warning(this,"Warnning","can't open "+mingDanPath(i),QMessageBox::Yes);
                exit(-1);
            }
            Xuesheng x;
            k.index = i;

            std::getline(in, time);
            std::getline(in, name);
            std::getline(in, major);
            std::getline(in, type);
            std::getline(in, weekNum);
            std::getline(in, classRoom);
            std::getline(in, classesName);
            k.time=QString::fromStdString(time);
            k.name= QString::fromStdString(name);
            k.major= QString::fromStdString(major);
            k.type= QString::fromStdString(type);
            k.weekNum=QString::fromStdString( weekNum);
            k.classRoom =QString::fromStdString(classRoom);
            k.classesName =QString::fromStdString(classesName);
            bool startnew = false;
            bool startold = false;
            bool find = false;
            while (sin>>line) {
                if (strstr(line.c_str(), "入学年份")) {
                    startold = true;
                    sin>>line;
                }
                if (strstr(line.c_str(), "课程类型")) {
                    startnew = true;

                }
                if (startnew || startold) {
                    find = true;
                    break;
                }
            }
            if (!find) {
                exit(-1);
            }
            while (sin>> index >> major >> number >> name >> sex
                    >> classNum >> state >> state) {
                //TODO 这个地方显然有bug，重复输入了
                 x.index=index;
                 x.isLaiLe=true;
                 x.major=QString::fromStdString(major);
                 x.number=QString::fromStdString(number);
                 x.name=QString::fromStdString(name);
                 x.sex=QString::fromStdString(sex);
                 x.classNum=QString::fromStdString(classNum);
                 x.state=QString::fromStdString(state);
                 x.kuangdao=0;
                 k.xueshengs.push_back(x);

            }

            sin.clear();
            sin.close();

            g_kechengs.push_back(k);
        }

//        for (auto i : g_kechengs) {
//            qDebug()<<i.time<<i.classesName<<i.major<<i.type<<i.weekNum<<i.classRoom<<i.classesName<<endl;
//            for(auto x:i.xueshengs){
//                qDebug()<<x.index<<x.major <<x.number << x.name << x.sex<< x.classNum << x.state<< x.state<<endl;
//            }
//        }



}

void logging::on_commandLinkButton_clicked()
{
    QString id=ui->comboBox->lineEdit()->text().trimmed();
    if(id==""){
         ui->labelLogStat->setText("请输入教师号！");
        return ;
    }else if(id==QString("040317")){

    }else if(id.size()!=6){
        ui->labelLogStat->setText("长度应该是6位！");
        return ;
    }


    bool success =false;
    //下载该老师的课表和课表对应的学生名单
    g_teacherNum=id;

    QString s("正在下载您的课表，请稍后");
    for(int i=0;i<60;i++){
        if(i==0){
         QFile file(g_jsPath+g_teacherNum+"/"+"total"+g_teacherNum+".txt");
         if (file.open(QIODevice::ReadOnly)){
             success =true;
             break;
         }
        }else{
            QFile file(g_jsPath+g_teacherNum+"/"+"SUCCESS");
            if (file.open(QIODevice::ReadOnly )){
               if( file.size()>0){
                   QFile file2(g_jsPath+g_teacherNum+"/"+"total"+g_teacherNum+".txt");
                   if (file2.open(QIODevice::ReadOnly)){
                       success =file2.size()>0;
                       break;
                   }
               }
            }
        }
        if(i==0){
            QProcess::startDetached(QString("node ")+g_jsRunPath+" "+id);
        }
       ui->labelLogStat->setText(s);
       s+=".";
       QElapsedTimer t;
       t.start();
       while(t.elapsed()<500){
        QCoreApplication::processEvents();
       }

    }
    //如果失败

    if(!success){
        ui->labelLogStat->setText("下载课表失败,请检查网络或账号！");
        return ;
    }
    //如果成功则跳转到新的页面
    g_haveNextStep=true;
    g_totalCoursesNumPath=g_jsPath+g_teacherNum+"/"+"total"+g_teacherNum+".txt";
    g_coursesPath=g_jsPath+g_teacherNum+"/"+g_teacherNum+".txt";
    load();
    QFile f(g_jsPath+"logging.txt");
    f.open(QIODevice::ReadWrite|QIODevice::Text);
    QString nowId=ui->comboBox->lineEdit()->text();
    QString loggAll;
    QString logg=" ";
    bool have=false;
    while(!f.atEnd()&&logg.size()>0){
     logg=f.readLine();
     if(logg.contains(nowId)){
         loggAll=logg+loggAll;
         have=true;
     }else{
         loggAll+=logg;

     }
    }
    if(!have){
        loggAll=nowId+" 未命名\n"+loggAll;
    }
    f.resize(0);
    f.write(loggAll.toStdString().c_str(),(qint64)loggAll.toStdString().size());


    this->close();
    //这里会回到主函数
}

void logging::on_pushButton_clicked()
{
    QString id=ui->comboBox->lineEdit()->text().trimmed();
    if(id.size()!=6){
      ui->labelLogStat->setText("请使用正确教师账清除缓存！");
     return;
    }

    ui->labelLogStat->setText("根据教师账号删除本地缓存！");
    QFile file("tmp.vbs");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
         QMessageBox::warning(this,"Warnning","can't open tmp.vbs",QMessageBox::Yes);
        return;
    }
    QTextStream out(&file);
    out <<"Dim fso\n"
        <<"Set fso=CreateObject(\"scripting.filesystemobject\")\n"
        <<"fso.DeleteFolder \""<<g_jsPath<<id<<"\""<<",true";
    /*Dim fso
      Set fso=CreateObject("scripting.filesystemobject")
      fso.DeleteFolder "test",true
    */
    QProcess::startDetached("C:/windows/system32/wscript.exe "
    "tmp.vbs");
    ui->labelLogStat->setText("删除完毕，请登录！");
}


