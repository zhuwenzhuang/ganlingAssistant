#ifndef WKEBIAO_H
#define WKEBIAO_H

#include <QDialog>

namespace Ui {
class WKebiao;
}

class WKebiao : public QDialog
{
    Q_OBJECT

public:
    explicit WKebiao(QWidget *parent = 0);
    ~WKebiao();
    Ui::WKebiao *getUi(){return ui;}
private:
    Ui::WKebiao *ui;
};

#endif // WKEBIAO_H
