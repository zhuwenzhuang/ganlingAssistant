#include "dianming.h"
#include "ui_dianming.h"

Xuanke::Xuanke(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dianming)
{
    ui->setupUi(this);
}

Xuanke::~Xuanke()
{
    delete ui;
}
