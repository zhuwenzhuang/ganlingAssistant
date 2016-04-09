#ifndef MINGDAN_H
#define MINGDAN_H
#include <QDialog>

namespace Ui {
class Mingdan;
}

class Mingdan : public QDialog
{
    Q_OBJECT

public:
    explicit Mingdan(QWidget *parent = 0);
    ~Mingdan();
    void closeEvent(QCloseEvent *event);
    void update();
private slots:
    void on_tableWidget_cellClicked(int row, int column);
    void changeTest(int row, int col);

    void on_pushButton_clicked();

    void on_tableWidget_activated(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Mingdan *ui;
    bool isDm;
    int startx=-1;
};

#endif // MINGDAN_H
