#ifndef AUTHENICATIONWINDOW_H
#define AUTHENICATIONWINDOW_H

#include <QMainWindow>
#include<dbase_admin.h>
#include<QMessageBox>
#include<QDebug>

namespace Ui {
class Authenicationwindow;
}

class Authenicationwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Authenicationwindow(QWidget *parent = 0);
    ~Authenicationwindow();
   void auth_to_remove_all_cashier();
     bool authenication;

private slots:
    void on_authButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::Authenicationwindow *ui;

};

#endif // AUTHENICATIONWINDOW_H
