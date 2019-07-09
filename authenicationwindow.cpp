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
         QMessageBox::information(this,"Delete Cashier","Deletion Sucessful");
         this->close();
     }
     else
     {
        qDebug()<<"not removed cashier";
     }
  }

  else
  {
      QMessageBox::information(this,"Authenication","Incorrect UserName or Password");
      ui->authAdminPass->setText("");
  }

}
void Authenicationwindow::on_cancelButton_clicked()
{
  authenication=false;
  this->close();
}


//void Authenicationwindow::auth_to_remove_all_cashier()
//{
//    if(authenication)
//    {
//        qDebug()<<"returned true";
//        Dbase_admin db("SBS.db");
//        if(db.removeCashierTable())
//        {
//            qDebug()<<"removed cashiers";
//        }
//        else
//        {
//            qDebug()<<"not removed cashier";
//        }
//    }
//    else
//    {
//        qDebug()<<"returned false";
//    }
//}
