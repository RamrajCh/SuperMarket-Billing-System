#ifndef CASHIERWINDOW_H
#define CASHIERWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include <QFile>
#include<QDate>
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
     void showCompanyDetails();
     void showbillTable(const QString &id,const QString &particulars,const double &rate,const int &quantity,const double &amount);
     void showAmount();
     void setProductTable();
     void setTransactionTable();

public slots:
     void on_logoutButton_clicked();

     void on_productButton_clicked();

private slots:
    void on_saleButton_clicked();

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

    void on_saveChangeButton_clicked();

    void on_checkProduct_clicked();

    void on_addProduct_clicked();

    void on_printBillButton_clicked();

    void on_removeProduct_clicked();

    void on_additionMode_clicked();

    void on_deductionMode_clicked();

    void on_todayHistory_clicked();

    void on_gotodateHistory_clicked();

    void on_okButton_clicked();

    void on_invoiceButton_clicked();

    void on_profileButton_clicked();

private:
    Ui::CashierWindow *ui;
    enum Column{
        ID,Particulars,Rate,Quantity,Amount
    };
    int billno=0;
};

#endif // CASHIERWINDOW_H
