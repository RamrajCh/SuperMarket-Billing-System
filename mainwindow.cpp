#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
   ui->mainStack->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_homeButton_clicked()
{
  //show home stack window
    ui->mainStack->setCurrentIndex(0);
}

void MainWindow::on_registerButton_1_clicked()
{
    //show Register stack window
    ui->mainStack->setCurrentIndex(1);
}

void MainWindow::on_loginButton_1_clicked()
{
    //show login stack window
    ui->mainStack->setCurrentIndex(2);
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
                QMessageBox::information(this,"Connection","Connection Sucessful");
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
                    if(db.addUser(fname,lname,username,mobileno,email,passwd))
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
    QString uname=ui->login_username->text();
    QString passwd=ui->login_password->text();

   Dbase db("SBS.db");
   bool result=db.userAuth(uname,passwd);
   if(result)
   {
       //Login
       QMessageBox::information(this,"Login","Login Sucessful");
       //clear login page password
       ui->login_password->setText("");
       //show admin window
       adminwindow=new AdminWindow(this);
       // mainwindow->hide();
       this->hide();
       adminwindow->show();
   }
   else
   {
     QMessageBox::information(this,"Login","Login Unsucessful");
   }
}

void MainWindow::on_cancelButton_2_clicked()
{
    //show home stack window
      ui->mainStack->setCurrentIndex(0);
}
