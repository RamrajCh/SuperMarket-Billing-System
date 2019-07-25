#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include <QDate>
#include<QDebug>
#include <QFile>
#include <QFileDialog>
#include<dbase_admin.h>
#include <dbase.h>

namespace Ui {
  class AdminWindow;
}

class AdminWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit AdminWindow(QWidget *parent = 0);
  ~AdminWindow();
  void showError(AdminWindow* window,QString error);
  void showCompanyDetails();
  void showAdmin_LoginDetails();
  void hidePrivacy();
  void setProductTable();
  void setCashierTable();

public slots:
  void on_logoutButton_clicked();
  void on_viewCashierButton_clicked();
  void on_viewProductButton_clicked();
  void on_salesButton_clicked();



private slots:
    void on_companyButton_clicked();

    void on_cashierButton_clicked();

    void on_productButton_clicked();

    void on_privacyButton_clicked();

    void on_companyUpdateButton_clicked();

    void on_okButton_1_clicked();

    void on_editButton_1_clicked();

    void on_okButton_2_clicked();

    void on_addCashierButton_clicked();

    //void on_logoutButton_clicked();

    void on_editButton_2_clicked();

    void on_changePasswordButton_clicked();

    void on_removeButton_clicked();

    void on_removeCashierButton_clicked();

    void on_addButton_clicked();



    void on_addProductButton_2_clicked();

    void on_removeAllCashierButton_clicked();



    void on_deleteProductButton_clicked();

    void on_specificButton_clicked();

    void on_specificButton_2_clicked();

    void on_delete_product_clicked();

    void on_addAdminButton_clicked();

    void on_registerButton_2_clicked();

    void on_removeAccount_clicked();
    void on_cancelButton_clicked();

       void on_todayHistory_clicked();
    void on_gotodateHistory_clicked();

    void on_cashierHistory_clicked();

    void on_okButton_3_clicked();

    void on_goButton_2_clicked();

    void on_pushButton_clicked();

    void on_settingButton_clicked();

    void on_browseButton_clicked();

    void on_okButton_clicked();

private:
  Ui::AdminWindow *ui;

};

#endif // ADMINWINDOW_H
