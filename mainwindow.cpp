#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  Dbase db("SBS.db");
  if (db.isOpen())
  {
      if(!db.getAdminInfo())
      {
          //give information to register admin
          ui->mainStack->setCurrentIndex(0);
          ui->homeStack->setCurrentIndex(0);
      }
      else
      {
         ui->mainStack->setCurrentIndex(0);
         ui->homeStack->setCurrentIndex(1);
      }
  }

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_homeButton_clicked()
{
  //show home stack window
    Dbase db("SBS.db");
    if (db.isOpen())
    {
        if(!db.getAdminInfo())
        {
            //give information to register admin
            ui->mainStack->setCurrentIndex(0);
            ui->homeStack->setCurrentIndex(0);
        }
        else
        {
           ui->mainStack->setCurrentIndex(0);
           ui->homeStack->setCurrentIndex(1);
        }
    }
}

void MainWindow::on_registerButton_1_clicked()
{
    //show Register stack window
    Dbase db("SBS.db");
    if (db.isOpen())
    {
        if(!db.getAdminInfo())
        {
            //go to register admin
            ui->mainStack->setCurrentIndex(1);
            ui->registerStack->setCurrentIndex(1);
        }
        else
        {
           ui->mainStack->setCurrentIndex(1);
           ui->registerStack->setCurrentIndex(0);
        }
    }

}

void MainWindow::on_registerButton_3_clicked()
{
    //show Register stack window
    ui->mainStack->setCurrentIndex(1);
    ui->registerStack->setCurrentIndex(1);
}

void MainWindow::on_loginButton_1_clicked()
{
   ui->mainStack->setCurrentIndex(2);
   Dbase db("SBS.db");
    if (db.isOpen())
    {
        if(!db.getAdminInfo())
        {
           QMessageBox::StandardButton stdButton=QMessageBox::information(this,"No Admin","Click OK to register...",QMessageBox::Ok|QMessageBox::Cancel);
           if(stdButton==QMessageBox::Ok)
           {
               //go to register admin
               ui->mainStack->setCurrentIndex(1);
               ui->registerStack->setCurrentIndex(1);
           }
           else
           {
               //go to home
               ui->mainStack->setCurrentIndex(0);
               ui->homeStack->setCurrentIndex(0);
           }
        }
        else
        {
            //go to login stack
            ui->mainStack->setCurrentIndex(2);
        }
    }

}

bool isEmpty(QString obj)
{
  if(obj=="" || obj==" ") return true;
  else return false;
}

void MainWindow :: showError(MainWindow* window,QString error)
{
  QMessageBox::warning(window,"Error!!",error);
}

void MainWindow::on_registerButton_2_clicked()
{
  //Connect to database and register Admin user


      //extract text from ui
      QString fname=ui->firstName->text();
      QString lname=ui->lastName->text();
      QString username=ui->userName->text();
      QString mobileno=ui->mobileNum->text();
      QString email=ui->eMail->text();
      QString passwd=ui->getPass->text();
      QString confirm_passwd=ui->conPass->text();


      //check Data Validation
      if(isEmpty(fname)) showError(this,"Specify your First Name");
      else if(isEmpty(lname)) showError(this,"Specify your Last Name");
      else if(isEmpty(username)) showError(this,"Enter your Username");
      else if(isEmpty(mobileno)) showError(this,"Specify your Mobile Number");
      else if(isEmpty(email)) showError(this,"Specify your E-mail");
      else if(isEmpty(passwd)) showError(this,"Enter your Password");
      else if(isEmpty(confirm_passwd)) showError(this,"Confirm your Password");

      //if all data are valid, now confirm the password
      else if(!(passwd==confirm_passwd))
        {
          showError(this,"Password doesnot match");
        }
      else
        {

            //connect to database

            Dbase db("SBS.db");



            if(db.isOpen())
              {
                //Store Data to Database
                qDebug()<<"connected to database";
                db.createTable();
                if (db.unameExists(username))
                {
                    //username already exists
                    showError(this,"Username already taken");

                }
                else if(db.emailExists(email))
                {
                    //email already taken
                    showError(this,"Email Already taken");
                }
                else
                {
                    if(db.addAdmin(fname,lname,username,mobileno,email,passwd))
                    {
                        QMessageBox::information(this,"Registration","Registered Sucessful");
                        //clear all
                        ui->firstName->setText("");
                        ui->lastName->setText("");
                        ui->userName->setText("");
                        ui->mobileNum->setText("");
                        ui->eMail->setText("");
                        ui->getPass->setText("");
                        ui->conPass->setText("");

                        ui->mainStack->setCurrentIndex(2);
                    }
                    else
                    {
                        QMessageBox::information(this,"Registration","Registered Unsucessful");
                    }
                 }
               }
      }
}

void MainWindow::on_cancelButton_1_clicked()
{
    //show home stack window
      ui->mainStack->setCurrentIndex(0);
}



void MainWindow::on_loginButton_2_clicked()
{
    Dbase db("SBS.db");
    QString uname=ui->login_username->text();
    QString passwd=ui->login_password->text();

   if(db.userAuth(uname,passwd))
   {
       //Login
       QMessageBox::information(this,"Login","Login Sucessful");
       //create Admin_login table
       db.createAdmin_LoginTable();
       db.addAdmin_Login(uname);
       //clear login page password
       ui->login_password->setText("");
       //show admin window
       adminwindow=new AdminWindow(this);
       // mainwindow->hide();
       this->hide();
       adminwindow->show();
   }
   else if(db.cashierAuth(uname,passwd))
   {
       //Login
       QMessageBox::information(this,"Login","Login Sucessful");
       //create Cashier_Login table
       db.createCashier_LoginTable();
       db.addCashier_Login(uname);
       //clear login page password
       ui->login_password->setText("");
       //show cashier window
       cashierwindow=new CashierWindow(this);
       // mainwindow->hide();
       this->hide();
       cashierwindow->show();
   }
   else
   {
     QMessageBox::information(this,"Login","Incorrect UserName or Password");
     ui->login_password->setText("");
   }
}

void MainWindow::on_cancelButton_2_clicked()
{
    //show home stack window
      ui->login_username->setText("");
      ui->login_password->setText("");
      ui->mainStack->setCurrentIndex(0);
}

void MainWindow::on_exitButton_clicked()
{
    QApplication::exit();
}



void MainWindow::on_authButton_clicked()
{

    QString uname=ui->authAdminUserName->text();
    QString passwd=ui->authAdminPass->text();

   Dbase db("SBS.db");
   bool result=db.userAuth(uname,passwd);
   if(result)
   {
       //Login
       QMessageBox::information(this,"Authenication","Authenication Sucessful");
       //clear password
       ui->authAdminUserName->setText("");
       ui->authAdminPass->setText("");
       //go to register
      ui->registerStack->setCurrentIndex(1);
   }
   else
   {
     QMessageBox::information(this,"Authenication","Incorrect UserName or Password");
     ui->login_password->setText("");
   }
}

void MainWindow::on_cancelButton_3_clicked()
{
    //go to home stack
    ui->mainStack->setCurrentIndex(0);
    ui->homeStack->setCurrentIndex(1);
}
