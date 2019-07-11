#include "cashierwindow.h"
#include "ui_cashierwindow.h"

CashierWindow::CashierWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CashierWindow)
{
    ui->setupUi(this);
    ui->cashierStack->setCurrentIndex(0);
    ui->homeStack->setCurrentIndex(0);
    ui->billStack->setCurrentIndex(2);
    showCashier_LoginDetails();
    showCompanyDetails();
}

CashierWindow::~CashierWindow()
{
    delete ui;
}


void CashierWindow::showCashier_LoginDetails()
{
    Dbase_Cashier db("SBS.db");
    if(!db.isOpen())
    {
        qDebug()<<"Not opening database";
    }
    else
    {
        qDebug()<<"Opening Database";
        QString name,username,mobileno,email,passwd;
        QList<QString> cashier_details=db.getCashier_loginDetails();
        if(cashier_details.isEmpty())
        {
            qDebug()<<"error in retriving cashier details";
        }
        else
        {
            qDebug()<<"retriving data from cashier";
            //retriving data from Cashier
            passwd=cashier_details.takeAt(0);
            email=cashier_details.takeAt(0);
            mobileno=cashier_details.takeAt(0);
            username=cashier_details.takeAt(0);
            name=cashier_details.takeAt(0);

           //Showing information
            ui->cashierUsernameLabel_2->setText(username);
            ui->cashierUsernameLabel->setText(username);
            ui->cashierNameLabel->setText(name);
            ui->cashierMobileLabel->setText(mobileno);
            ui->cashierEmailLabel->setText(email);
        }

    }
}

void CashierWindow:: showCompanyDetails()
{
    Dbase_Cashier db("SBS.db");
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
            ui->nameLabel_2->setText(name);
            ui->vatLabel_2->setText(vat);
            ui->phoneLabel_2->setText(phone);
            ui->addressLabel_2->setText(address);
            ui->emailLabel_2->setText(email);
            ui->websiteLabel_2->setText(website);
        }
        else
        {
            qDebug()<<"Error in getting list";
        }
    }
}



void CashierWindow::on_homeButton_clicked()
{
    ui->cashierStack->setCurrentIndex(0);
    ui->homeStack->setCurrentIndex(0);
    showCashier_LoginDetails();
    showCompanyDetails();
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
    QMessageBox::StandardButton stdbutton=QMessageBox::question(this,"Change Password","Do you want to change password?",QMessageBox::Yes|QMessageBox::No);
    if(stdbutton==QMessageBox::Yes)
    {
        ui->homeStack->setCurrentIndex(1);
    }
}

void CashierWindow::on_saveChangeButton_clicked()
{
    QString username=ui->userName->text();
    QString opasswd=ui->oldPassword->text();
    QString npasswd=ui->newPassword->text();
    QString conpasswd=ui->confirmPassword->text();

    Dbase_Cashier db("SBS.db");
    if(db.validCashier(username,opasswd))
    {
        if(!(npasswd==conpasswd)){QMessageBox::warning(this,"Confirm Password","Confirm password doennot match");}
        else
        {
            db.updateCashier(username,npasswd);
            QMessageBox::information(this,"Change Password","Password Changed Sucessfully");
            {
              on_logoutButton_clicked();
            }
        }
    }
    else
    {
        QMessageBox::information(this,"Change Password","Incorrect UserName or Password");
    }
}


void CashierWindow::on_checkProduct_clicked()
{
    QString id=ui->productID->text();
    Dbase_Cashier db("SBS.db");
    //check product validation
    if(!db.validProduct(id)){QMessageBox::information(this,"Check Product","Invalid Product"); ui->productID->setText("");}
    else
    {
        QMessageBox::information(this,"Check Product","Product Found");
        if(!db.product_IdExists(id)){ui->billStack->setCurrentIndex(0);}
        else{ui->billStack->setCurrentIndex(1);}
    }
    //if true check product in bill
    //if not contained goto index 0
    //if contained goto index 1
}

void CashierWindow::on_addProduct_clicked()
{
    QString id,name;
    int quantity;
    double amount;

    id=ui->productID->text();
    quantity=ui->quantityBox->value();

    Dbase_Cashier db("SBS.db");
    QList<QString>pro = db.getProductDetails(id);
    double temp;
    temp = pro[0].toDouble();
    name=pro[2];
    amount=quantity*temp;
    qDebug()<<amount;
    db.createBillTable();
    db.addProduct(id,name,quantity,temp,amount);
}
