#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::AdminWindow)
{
  ui->setupUi(this);
  ui->adminStack->setCurrentIndex(3);
  ui->privacyStack->setCurrentIndex(0);
  showAdmin_LoginDetails();
}

AdminWindow::~AdminWindow()
{
  delete ui;
}

bool isVacant(QString obj)
{
  if(obj=="" || obj==" ") return true;
  else return false;
}

void AdminWindow :: showError(AdminWindow* window,QString error)
{
  QMessageBox::warning(window,"Error!!",error);
}



void AdminWindow::on_companyButton_clicked()
{
    //show Company Stack
    ui->adminStack->setCurrentIndex(0);
    Dbase_admin db("SBS.db");
    if(db.isOpen())
    {
        //see if database have any table Company_Details and has any value
        if(!db.getCompanyDetails())
        {
            ui->companyStack->setCurrentIndex(0);
        }
        else
        {
            ui->companyStack->setCurrentIndex(2);
            showCompanyDetails();
        }
    }
    else
    {
        //show Error
        qDebug()<<"Database Connection Unsucessful";
    }

}

void AdminWindow::on_cashierButton_clicked()
{
    //show Cashier Stack
    ui->adminStack->setCurrentIndex(1);
    ui->cashierStack->setCurrentIndex(0);
}

void AdminWindow::on_productButton_clicked()
{
    //show Cashier Stack
    ui->adminStack->setCurrentIndex(2);
}

void AdminWindow::on_privacyButton_clicked()
{
    //show Privacy Stack
    ui->adminStack->setCurrentIndex(3);
    ui->privacyStack->setCurrentIndex(0);
    showAdmin_LoginDetails();
}


void AdminWindow::on_companyUpdateButton_clicked()
{
    //show update form
    ui->companyStack->setCurrentIndex(1);
}

////defining company functions

void AdminWindow:: showCompanyDetails()
{
    Dbase_admin db("SBS.db");
    if(!db.isOpen())
    {
        qDebug()<<"Not opening database";
    }
    else
    {
        //retriving data from database
        QString name,vat,phone,address,email,website;
        QList<QString> com_det=db.getComDetails();
        if(!com_det.isEmpty())
        {
           //retriving data from list
            website=com_det.takeAt(0);
            email=com_det.takeAt(0);
            address=com_det.takeAt(0);
            phone=com_det.takeAt(0);
            vat=com_det.takeAt(0);
            name=com_det.takeAt(0);

            //Showing results
            ui->nameLabel->setText(name);
            ui->vatLabel->setText(vat);
            ui->phoneLabel->setText(phone);
            ui->addressLabel->setText(address);
            ui->emailLabel->setText(email);
            ui->websiteLabel->setText(website);
        }
        else
        {
            qDebug()<<"Error in getting list";
        }
    }
}


void AdminWindow::on_okButton_1_clicked()
{
    //extract values from ui
    QString name=ui->companyName->text();
    QString vat=ui->companyVAT->text();
    QString phone=ui->companyPhone->text();
    QString address=ui->companyAddress->text();
    QString email=ui->companyEmail->text();
    QString website=ui->companyWebsite->text();

    //check data validation
    if(isVacant(name)) showError(this,"Specify Company Name");
    else if(isVacant(vat)) showError(this,"Specify Company VAT/PAN No.");
    else if(isVacant(phone)) showError(this,"Specify Company Phone");
    else if(isVacant(address)) showError(this,"Specify Company Address");
    else if(isVacant(email)) showError(this,"Specify Company Email");

    //check if there is table
    else
    {
        //connect to database
        Dbase_admin db("SBS.db");
        if(!db.isOpen())
        {
            qDebug()<<"Database Connection Unsucessful";
        }
        else
        {
            //check if there is Company Table
            if(!db.getCompanyDetails())
            {
                db.createCompanyTable();
                if(db.addCompanyDetails(name,vat,phone,address,email,website))
                {
                    QMessageBox::information(this,"Company Details","Added Sucessfully");
                    ui->companyStack->setCurrentIndex(2);
                    showCompanyDetails();
                }
                else
                {
                    QMessageBox::information(this,"Company Details","Failed to add");
                }

            }
            else
            {
                if(db.removeCompanyDetails())
                {
                    if(db.addCompanyDetails(name,vat,phone,address,email,website))
                    {
                        QMessageBox::information(this,"Company Details","Updated Sucessfully");
                        ui->companyStack->setCurrentIndex(2);
                        showCompanyDetails();
                    }
                    else
                    {
                        QMessageBox::information(this,"Company Details","Failed to update");
                    }
                }
            }
        }
    }
}

void AdminWindow::on_cancelButton_1_clicked()
{
    ui->companyStack->setCurrentIndex(2);
}

void AdminWindow::on_editButton_1_clicked()
{
    ui->companyStack->setCurrentIndex(1);
}

////Defining cashier functions

void AdminWindow::on_okButton_2_clicked()
{
    //extract values from ui
    QString name=ui->cashierName->text();
    QString uname=ui->cashierUsername->text();
    QString phone=ui->cashierPhone->text();
    QString email=ui->cashierEmail->text();
    QString passwd=ui->cashierPassword->text();

    //check data validation
    if(isVacant(name)) showError(this,"Specify Cashier Name");
    else if(isVacant(uname)) showError(this,"Specify Cashier UserName");
    else if(isVacant(phone)) showError(this,"Specify Cashier Phone");
    else if(isVacant(email)) showError(this,"Specify Cashier Email");
    else if(isVacant(passwd)) showError(this,"Specify Cashier Password");


    //check if there is table
    else
    {
        //connect to database
        Dbase_admin db("SBS.db");
        if(!db.isOpen())
        {
            qDebug()<<"Database Connection Unsucessful";
        }
        else
        {
                db.createCashierTable();
                if(db.addCashierDetails(name,uname,phone,email,passwd))
                {
                    QMessageBox::information(this,"Cashier Details","Added Sucessfully");

                    //vacant the line edits
                    ui->cashierName->setText("");
                    ui->cashierUsername->setText("");
                    ui->cashierPhone->setText("");
                    ui->cashierEmail->setText("");
                    ui->cashierPassword->setText("");

                    //got to cashier main stack
                    ui->cashierStack->setCurrentIndex(0);
                }
                else
                {
                    QMessageBox::information(this,"Cashier Details","Failed to add");
                }

            }
            }
    //ui->companyStack->setCurrentIndex(2);
    //showCompanyDetails();
}

void AdminWindow::on_addCashierButton_clicked()
{
    //go to add cashier stack
    ui->cashierStack->setCurrentIndex(1);
}


////Defining Privacy Functions

void AdminWindow::on_logoutButton_clicked()
{
    //delete Admin_Login Table
    Dbase_admin db("SBS.db");
    db.deleteAdmin_Login();

//    mainwindow=new QMainWindow(this);
    this->hide();
    QWidget *parent = this->parentWidget();
    parent->show();
//    mainwindow->show();
}

void AdminWindow:: showAdmin_LoginDetails()
{
    Dbase_admin db("SBS.db");
    if(!db.isOpen())
    {
        qDebug()<<"Not opening database";
    }
    else
    {
        qDebug()<<"Opening Database";
        QString fname,lname,username,mobileno,email,passwd;
        QList<QString> admin_details=db.getAdmin_LoginDetails();
        if(admin_details.isEmpty())
        {
            qDebug()<<"error in retriving admin details";
        }
        else
        {
            qDebug()<<"retriving data from admin";
            //retriving data from Admin
            passwd=admin_details.takeAt(0);
            email=admin_details.takeAt(0);
            mobileno=admin_details.takeAt(0);
            username=admin_details.takeAt(0);
            lname=admin_details.takeAt(0);
            fname=admin_details.takeAt(0);

           //Showing information
            ui->adminUsernameLabel->setText(username);
            ui->adminNameLabel->setText(fname+" "+lname);
            ui->adminPhoneLabel->setText(mobileno);
            ui->adminEmailLabel->setText(email);
        }

    }
}
