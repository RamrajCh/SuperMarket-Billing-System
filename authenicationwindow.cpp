#include "authenicationwindow.h"
#include "ui_authenicationwindow.h"

Authenicationwindow::Authenicationwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Authenicationwindow)
{
    ui->setupUi(this);
}

Authenicationwindow::~Authenicationwindow()
{
    delete ui;
}

void Authenicationwindow::on_authButton_clicked()
{

    QString uname=ui->authAdminUserName->text();
    QString passwd=ui->authAdminPass->text();

   Dbase_admin db("SBS.db");
    bool result=db.userAuth(uname,passwd);
    if(result)
    {
        //Login
        QMessageBox::information(this,"Authenication","Authenication Sucessful");
             if(db.removeCashierTable())
             {
                 qDebug()<<"removing table";
                 QMessageBox::information(this,"Remove","All Cashier removed");

             }
             else
             {
                 QMessageBox::information(this,"Remove","All Cashier not removed");

             }
         }
    else
    {
      QMessageBox::information(this,"Authenication","Incorrect UserName or Password");
   }
}
void Authenicationwindow::on_cancelButton_clicked()
{
    this->close();
}
