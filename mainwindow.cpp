#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
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
            QSqlDatabase db;
            db=QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName("/home/ramraj/SBS/SBS.db");


            if(db.open())
              {
                //Store Data to Database
                QMessageBox::information(this,"Connection","Connection Sucessful");
                QSqlQuery qry;

                qry.prepare("INSERT INTO Admin(FirstName,LastName,UserName,MobileNo,Email,Password)"" values(:Fname,:Lname,:Uname,:Mobile,:Email,:Password)");
                qry.bindValue(0,fname);
                qry.bindValue(1,lname);
                qry.bindValue(2,username);
                qry.bindValue(3,mobileno);
                qry.bindValue(4,email);
                qry.bindValue(5,passwd);

                if(qry.exec())
                    {
                      QMessageBox::information(this,"Registration","Registered Sucessful");
                      //show login stack window
                      ui->mainStack->setCurrentIndex(2);
                    }
                else QMessageBox::information(this,"Registration","Registered Unsucessful");
              }
            else
              {
                //Show unsucessful Message
                QMessageBox::information(this,"Connection","Connection Unsucessful");

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
    //connect to database
    QSqlDatabase db;
    db=QSqlDatabase::addDatabase("QSQLITE","MyConnection");
    db.setDatabaseName("/home/ramraj/SBS/SBS.db");

    QString uname=ui->login_username->text();
    QString passwd=ui->login_password->text();

    if(db.open())
    {
        //executing query
        QMessageBox::information(this,"Login","Database Connected");
        QSqlQuery qry(QSqlDatabase::database("MyConnection"));

        qry.prepare(QString("SELECT * FROM Admin WHERE UserName=:Uname AND Password=:Password"));
        qry.bindValue(":Uname",uname);
        qry.bindValue(":Password",passwd);

        if(qry.exec())
        {
            //show AdminWindow
            QMessageBox::information(this,"Login","Login Sucessful");
            adminwindow=new AdminWindow(this);
           // mainwindow->hide();
            this->hide();
            adminwindow->show();
        }
        else
        {
            //Show error
            QMessageBox::information(this,"Login","Incorrect Username or Password");
        }

    }

    else
    {
        //show error
        QMessageBox::information(this,"Login","Login Unsucessful");
    }

}

void MainWindow::on_cancelButton_2_clicked()
{
    //show home stack window
      ui->mainStack->setCurrentIndex(0);
}
