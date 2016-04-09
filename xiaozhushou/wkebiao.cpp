#include "wkebiao.h"
#include "ui_wkebiao.h"

WKebiao::WKebiao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WKebiao)
{
    ui->setupUi(this);
}

WKebiao::~WKebiao()
{
    delete ui;
}
