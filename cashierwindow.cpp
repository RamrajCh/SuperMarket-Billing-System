#include "cashierwindow.h"
#include "ui_cashierwindow.h"

CashierWindow::CashierWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CashierWindow)
{
    ui->setupUi(this);
    ui->cashierStack->setCurrentIndex(0);
    ui->homeStack->setCurrentIndex(0);
    //showCashier_LoginDetails();
}

CashierWindow::~CashierWindow()
{
    delete ui;
}

void CashierWindow::on_homeButton_clicked()
{
    ui->cashierStack->setCurrentIndex(0);
    ui->homeStack->setCurrentIndex(0);
    //showCashier_LoginDetails();
}


void CashierWindow::on_productButton_clicked()
{
    ui->cashierStack->setCurrentIndex(1);
    Dbase_Cashier db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM Product");

    qry->exec();

    model->setQuery(*qry);
    ui->cashierStack->setCurrentIndex(1);
     ui->productTable->setModel(model);
}


void CashierWindow::on_saleButton_clicked()
{
    ui->cashierStack->setCurrentIndex(2);

}


void CashierWindow::on_logoutButton_clicked()
{
    //delete Cashier_Login Table
    Dbase_Cashier db("SBS.db");
    db.deleteCashier_Login();

//    mainwindow=new QMainWindow(this);
    this->hide();
    QWidget *parent = this->parentWidget();
    parent->show();
//    mainwindow->show();
}


void CashierWindow::on_allButton_clicked()
{
    Dbase_Cashier db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM Product");

    qry->exec();

    model->setQuery(*qry);
    ui->cashierStack->setCurrentIndex(1);
    ui->productTable->setModel(model);
}


void CashierWindow::on_groceryButton_clicked()
{
    Dbase_Cashier db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT ID,Name,Price FROM Product WHERE Category='Grocery'");

    qry->exec();

    model->setQuery(*qry);
    ui->cashierStack->setCurrentIndex(1);
    ui->productTable->setModel(model);
}

void CashierWindow::on_fashionButton_clicked()
{
    Dbase_Cashier db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT ID,Name,Price FROM Product WHERE Category='Fashion'");

    qry->exec();

    model->setQuery(*qry);
    ui->cashierStack->setCurrentIndex(1);
    ui->productTable->setModel(model);
}

void CashierWindow::on_homeappButton_clicked()
{
    Dbase_Cashier db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT ID,Name,Price FROM Product WHERE Category='Home Appliances'");

    qry->exec();

    model->setQuery(*qry);
    ui->cashierStack->setCurrentIndex(1);
    ui->productTable->setModel(model);
}

void CashierWindow::on_kidButton_clicked()
{
    Dbase_Cashier db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT ID,Name,Price FROM Product WHERE Category='Kids'");

    qry->exec();

    model->setQuery(*qry);
    ui->cashierStack->setCurrentIndex(1);
    ui->productTable->setModel(model);
}

void CashierWindow::on_liquorButton_clicked()
{
    Dbase_Cashier db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT ID,Name,Price FROM Product WHERE Category='Liquor'");

    qry->exec();

    model->setQuery(*qry);
    ui->cashierStack->setCurrentIndex(1);
    ui->productTable->setModel(model);
}

void CashierWindow::on_giftsButton_clicked()
{
    Dbase_Cashier db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT ID,Name,Price FROM Product WHERE Category='Games'");

    qry->exec();

    model->setQuery(*qry);
    ui->cashierStack->setCurrentIndex(1);
    ui->productTable->setModel(model);
}

void CashierWindow::on_otherButton_clicked()
{
    Dbase_Cashier db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT ID,Name,Price FROM Product WHERE Category='Other'");

    qry->exec();

    model->setQuery(*qry);
    ui->cashierStack->setCurrentIndex(1);
    ui->productTable->setModel(model);
}

void CashierWindow::on_editCashierButton_clicked()
{
    ui->homeStack->setCurrentIndex(1);
}

//void CashierWindow::showCashier_LoginDetails()
//{
//    Dbase_Cashier db("SBS.db");
//    if(!db.isOpen())
//    {
//        qDebug()<<"Not opening database";
//    }
//    else
//    {
//        qDebug()<<"Opening Database";
//        QString name,username,mobileno,email,passwd;
//        QList<QString> cashier_details=db.getCashier_loginDetails();
//        if(cashier_details.isEmpty())
//        {
//            qDebug()<<"error in retriving admin details";
//        }
//        else
//        {
//            qDebug()<<"retriving data from admin";
//            //retriving data from Admin
//            passwd=cashier_details.takeAt(0);
//            email=cashier_details.takeAt(0);
//            mobileno=cashier_details.takeAt(0);
//            username=cashier_details.takeAt(0);
//            name=cashier_details.takeAt(0);

//           //Showing information
//            ui->cashierUsernameLabel_2->setText(username);
//            ui->cashierUsernameLabel->setText(username);
//            ui->cashierNameLabel->setText(name);
//            ui->cashierMobileLabel->setText(mobileno);
//            ui->cashierEmailLabel->setText(email);
//        }

//    }
//}

