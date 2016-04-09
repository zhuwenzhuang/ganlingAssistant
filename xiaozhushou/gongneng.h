#ifndef GONGNENG_H
#define GONGNENG_H

#include <QDialog>

namespace Ui {
class gongneng;
}

class gongneng : public QDialog
{
    Q_OBJECT

public:
    explicit gongneng(QWidget *parent = 0);
    void update2();
    ~gongneng();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_label_4_linkActivated(const QString &link);

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::gongneng *ui;
};

#endif // GONGNENG_H
