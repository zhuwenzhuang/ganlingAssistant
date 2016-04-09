#ifndef DIANMING_H
#define DIANMING_H

#include <QDialog>

namespace Ui {
class Dianming;
}

class Dianming : public QDialog
{
    Q_OBJECT

public:
    explicit Dianming(QWidget *parent = 0);
    ~Dianming();

private:
    Ui::Dianming *ui;
};

#endif // DIANMING_H
