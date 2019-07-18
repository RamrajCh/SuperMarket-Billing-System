#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDate>
#include <adminwindow.h>
#include <cashierwindow.h>
#include <dbase.h>
namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void showError(MainWindow *,QString); //function to give error messege


private slots:
   void on_registerButton_2_clicked();

   void on_loginButton_2_clicked();

   void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
    AdminWindow *adminwindow;
    CashierWindow *cashierwindow;
};

#endif // MAINWINDOW_H
