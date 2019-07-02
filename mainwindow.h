#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <adminwindow.h>
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
   void on_homeButton_clicked();

   void on_registerButton_1_clicked();

   void on_loginButton_1_clicked();

   void on_registerButton_2_clicked();

   void on_cancelButton_1_clicked();

   void on_loginButton_2_clicked();

   void on_cancelButton_2_clicked();

private:
    Ui::MainWindow *ui;
    AdminWindow *adminwindow;
};

#endif // MAINWINDOW_H
