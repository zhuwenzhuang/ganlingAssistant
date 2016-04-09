#include "xuanke.h"
#include "ui_xuanke.h"

Xuanke::Xuanke(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Xuanke)
{
    ui->setupUi(this);
}

Xuanke::~Xuanke()
{
    delete ui;
}
