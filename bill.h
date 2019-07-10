#ifndef BILL_H
#define BILL_H

#include <QMainWindow>

namespace Ui {
class Bill;
}

class Bill : public QMainWindow
{
    Q_OBJECT

public:
    explicit Bill(QWidget *parent = 0);
    ~Bill();

private:
    Ui::Bill *ui;
};

#endif // BILL_H
