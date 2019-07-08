#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include <QDebug>
#include <authenicationwindow.h>
#include<dbase_admin.h>
#include <dbase.h>

namespace Ui {
  class AdminWindow;
}

class AdminWindow : public QMainWindow
{
  Q_OBJECT

public:
  void showError(AdminWindow* window,QString error);
  void showCompanyDetails();
  void showAdmin_LoginDetails();

  explicit AdminWindow(QWidget *parent = 0);
  ~AdminWindow();

private slots:
    void on_companyButton_clicked();

    void on_cashierButton_clicked();

    void on_productButton_clicked();

    void on_privacyButton_clicked();

    void on_companyUpdateButton_clicked();

    void on_okButton_1_clicked();

    void on_cancelButton_1_clicked();

    void on_editButton_1_clicked();

    void on_okButton_2_clicked();

    void on_addCashierButton_clicked();

    void on_logoutButton_clicked();

    void on_editButton_2_clicked();

    void on_changePasswordButton_clicked();

    void on_cancelButton_2_clicked();

    void on_removeButton_clicked();

    void on_removeCashierButton_clicked();

    void on_addButton_clicked();

    void on_addProductButton_2_clicked();

    void on_cancelButton_3_clicked();

    void on_addCategoryButton_clicked();

    void on_addCategoryButton_2_clicked();

    void on_addProductButton_clicked();

    void on_removeAllCashierButton_clicked();

    void on_viewProductButton_clicked();

    void on_deleteProductButton_clicked();

    void on_viewCashierButton_clicked();

    void on_specificButton_clicked();

private:
  Ui::AdminWindow *ui;
  Authenicationwindow *adminauth;
};

#endif // ADMINWINDOW_H
