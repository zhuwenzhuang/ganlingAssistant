#ifndef KEBIAO_H
#define KEBIAO_H

#include <QDialog>

namespace Ui {
class Kebiao;
}

class Kebiao : public QDialog
{
    Q_OBJECT

public:
    explicit Kebiao(QWidget *parent = 0);
    ~Kebiao();
public :
    Ui::Kebiao* getUi(){return ui;}
private slots:


    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_listWidget_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Kebiao *ui;
};

#endif // KEBIAO_H
