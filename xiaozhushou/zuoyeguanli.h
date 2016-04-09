#ifndef ZUOYEGUANLI_H
#define ZUOYEGUANLI_H

#include <QDialog>

namespace Ui {
class zuoyeguanli;
}

class zuoyeguanli : public QDialog
{
    Q_OBJECT

public:
    explicit zuoyeguanli(QWidget *parent = 0);
    ~zuoyeguanli();

private slots:
    void on_webView_destroyed();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::zuoyeguanli *ui;
};

#endif // ZUOYEGUANLI_H
