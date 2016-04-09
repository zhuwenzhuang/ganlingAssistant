#ifndef STRUCTS_H
#define STRUCTS_H
#include<vector>
#include<QString>
#include<map>
#include<QDebug>
#include<QCheckBox>
#include<QFile>
#include<QMessageBox>
#include<QProcess>
#include<stdio.h>
#include<string>
#include<fstream>
#include<QProcess>
#include<QElapsedTimer>
#include <QDialog>
#include<QCloseEvent>
#include <QtWidgets/QApplication>
#include <QtWebKitWidgets>
#include <qwebview.h>
struct Xuesheng{
    int index;
    QString major;
    QString number;
    QString name;
    QString sex;
    QString classNum;
    QString state;
    bool isLaiLe;
    int kuangdao;
    QString jiafenxiang;
};
struct KeCheng{
    int index;
    QString time;
    QString name;
    QString major;
    QString type;
    QString weekNum;
    QString classRoom;
    QString classesName;
    std::vector<Xuesheng> xueshengs;
};
void speak(QString str);
#endif // STRUCTS_H

