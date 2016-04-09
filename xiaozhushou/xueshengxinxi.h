#ifndef XUESHENGXINXI_H
#define XUESHENGXINXI_H

#include <QDialog>

namespace Ui {
class xueshengxinxi;
}

class xueshengxinxi : public QDialog
{
    Q_OBJECT

public:
    explicit xueshengxinxi(QWidget *parent = 0);
    ~xueshengxinxi();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::xueshengxinxi *ui;
};

#endif // XUESHENGXINXI_H
