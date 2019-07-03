#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::AdminWindow)
{
  ui->setupUi(this);
  ui->adminStack->setCurrentIndex(3);
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
}


void AdminWindow::on_companyUpdateButton_clicked()
{
    //show update form
    ui->companyStack->setCurrentIndex(1);
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
                    }
                    else
                    {
                        QMessageBox::information(this,"Company Details","Failed to update");
                    }
                }
            }
        }
    }
    ui->companyStack->setCurrentIndex(2);
    showCompanyDetails();
}

void AdminWindow::on_cancelButton_1_clicked()
{
    ui->companyStack->setCurrentIndex(2);
}

void AdminWindow::on_editButton_1_clicked()
{
    ui->companyStack->setCurrentIndex(1);
}
