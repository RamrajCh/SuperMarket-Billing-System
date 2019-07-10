#ifndef CASHIERWINDOW_H
#define CASHIERWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include <QDebug>
#include<dbase_cashier.h>

namespace Ui {
class CashierWindow;
}

class CashierWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CashierWindow(QWidget *parent = 0);
    ~CashierWindow();
    void showCashier_LoginDetails();

private slots:
    void on_productButton_clicked();

    void on_saleButton_clicked();

    void on_logoutButton_clicked();

    void on_allButton_clicked();

    void on_homeButton_clicked();

    void on_groceryButton_clicked();

    void on_fashionButton_clicked();

    void on_homeappButton_clicked();

    void on_kidButton_clicked();

    void on_liquorButton_clicked();

    void on_giftsButton_clicked();

    void on_otherButton_clicked();

    void on_editCashierButton_clicked();

private:
    Ui::CashierWindow *ui;
};

#endif // CASHIERWINDOW_H
