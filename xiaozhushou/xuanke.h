#ifndef XUANKE_H
#define XUANKE_H

#include <QDialog>

namespace Ui {
class Xuanke;
}

class Xuanke : public QDialog
{
    Q_OBJECT

public:
    explicit Xuanke(QWidget *parent = 0);
    ~Xuanke();

private:
    Ui::Xuanke *ui;
};

#endif // XUANKE_H
