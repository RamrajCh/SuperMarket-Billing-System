#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include <QDebug>
#include<dbase_admin.h>

namespace Ui {
  class AdminWindow;
}

class AdminWindow : public QMainWindow
{
  Q_OBJECT

public:
  void showError(AdminWindow* window,QString error);
  void showCompanyDetails();

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

private:
  Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
