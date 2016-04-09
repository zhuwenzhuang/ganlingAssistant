#ifndef KEJIAN_H
#define KEJIAN_H

#include <QDialog>

namespace Ui {
class kejian;
}

class kejian : public QDialog
{
    Q_OBJECT

public:
    explicit kejian(QWidget *parent = 0);
    ~kejian();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    //void on_horizontalSlider_sliderMoved(int position);

    //void on_dial_sliderMoved(int position);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_4_clicked();

private:
    Ui::kejian *ui;
};

#endif // KEJIAN_H
