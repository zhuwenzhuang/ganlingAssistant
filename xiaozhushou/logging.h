#ifndef LOGGING_H
#define LOGGING_H

#include <QApplication>
#include <QDialog>
#include <QWidget>
#include <QMainWindow>
#include <QLayout>
#include <QTreeWidget>
#include <QLineEdit>
#include <QLayout>
#include <QLabel>
#include <QTreeWidgetItem>
#include <QTreeView>
#include <QEvent>
#include <QMouseEvent>
#include <QItemDelegate>
#include <QStyledItemDelegate>
#include <QCommonStyle>
#include <QTableWidget>
#include <QItemDelegate>
#include <QTabWidget>
#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QListWidget>
#include <QTimer>

#include "kebiao.h"
#include "ui_kebiao.h"

#define TX_SMALL 32
#define TX_BIG 42

extern QApplication *app;

class AccountItem:public QWidget
{
    Q_OBJECT
public:
    explicit AccountItem(QWidget *parent = 0);
    ~AccountItem(){}
signals:
    void changeAccount(QString account);
    void showAccount(QString account);
    void removeAccount(QString account);
public slots:
    void setAccountNumber(QString account_text)
    {
        account_number->setText(account_text);
    }

    QString getAccountNumber()
    {
        QString account_number_text = account_number->text();
        return account_number_text;
    }
    void removeAccount()
    {
        QString account_number_text = account_number->text();
        emit removeAccount(account_number_text);
    }
    void mousePressEvent(QMouseEvent *event)
    {
         if(event->button() == Qt::LeftButton)
         {
          mouse_press = true;
         }
    }
    void mouseReleaseEvent(QMouseEvent *event)
    {
        if(mouse_press)
        {
            emit showAccount(account_number->text());
            mouse_press = false;
        }
    }
    void mouseMoveEvent(QMouseEvent *);
public:
    QString id;
    QString name;
    QString touxPath;
private:
    bool mouse_press;
    QLabel* account_number;
    QPushButton* delede_button;
    QLabel* lab;
private slots:
    void paintEvent(QPaintEvent *);
};


namespace Ui {
class logging;
}

class logging : public QDialog
{
    Q_OBJECT

public:
    explicit logging(QWidget *parent = 0);
    ~logging();
    void load();
public slots:
    void showAccount(QString account);
    void removeAccount(QString account);
    void proxyChange(int index);
    void changeAccount(QString account);

private slots:
    void on_commandLinkButton_clicked();

    void on_pushButton_clicked();

    void mousePressEvent(QMouseEvent *);
    void slotTime();
public:
    Ui::logging *ui;
private:
    QListWidget *list_widget;
    QComboBox *account_combo_box;
    int m_nTimerCount;
    int m_nNow,m_nLast;
    QTimer *timer;

};

#endif // LOGGING_H
