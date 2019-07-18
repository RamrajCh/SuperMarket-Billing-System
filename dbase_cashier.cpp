#include "dbase_cashier.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>



Dbase_Cashier::Dbase_Cashier(const QString &path)
{
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if(!db.open())
    {
        qDebug()<<"Error:Connection with database";
    }
    else
    {
        qDebug()<<"Sucess:Connection with database";
    }
}

Dbase_Cashier::~Dbase_Cashier()
{
    if(db.open())
    {
        db.close();
    }
}

bool Dbase_Cashier::isOpen() const
{
    return db.isOpen();
}
bool Dbase_Cashier::cashierAuth(const QString &uname, const QString &pass) const
{
bool exists = false;

QSqlQuery checkQuery;
checkQuery.prepare("SELECT UserName FROM Cashier WHERE UserName =:uname AND Password = :pass");
checkQuery.bindValue(":uname", uname);
checkQuery.bindValue(":pass", pass);
if (checkQuery.exec()){
    if (checkQuery.next()){
        qDebug()<<"cashier exists";
        exists = true;
    }
}else{
    qDebug()<<"cashier exists failed: " << checkQuery.lastError();
}
return exists;
}

void Dbase_Cashier::deleteCashier_Login()
{
    QSqlQuery qry;
    qry.prepare("DROP TABLE Cashier_Login");
    if(qry.exec())
    {
        qDebug()<<"cashier_Login Table deleted";
    }
    else
    {
        qDebug()<<"Couldn't delete table";
    }
}

QList<QString> Dbase_Cashier::getCashier_loginDetails()
{
    QList<QString> cashierdetails;
    QSqlQuery qry;
    qry.prepare(QString("SELECT * FROM Cashier_Login"));
    if(!qry.exec())
    {
        qDebug()<<"Error in retriving data"<<qry.lastError();
    }
    else
    {

       if(qry.next())
       {
           QString name=qry.value(0).toString();
           QString username=qry.value(1).toString();
           QString gender=qry.value(2).toString();
           QString mobileno=qry.value(3).toString();
           QString email=qry.value(4).toString();
           QString passwd=qry.value(5).toString();

           cashierdetails.push_front(name);
           cashierdetails.push_front(username);
           cashierdetails.push_front(gender);
           cashierdetails.push_front(mobileno);
           cashierdetails.push_front(email);
           cashierdetails.push_front(passwd);
       }
       else
       {
           qDebug()<<"not executing qyery";
       }

    }
      return cashierdetails;
}


QList<QString> Dbase_Cashier::getComDetails()
{
    QList<QString> companydetails;
    QSqlQuery qry;
    qry.prepare(QString("SELECT * FROM Company"));
    if(!qry.exec())
    {
        qDebug()<<"Error in retriving data"<<qry.lastError();
    }
    else
    {

       if(qry.next())
       {
           QString name=qry.value(0).toString();
           QString vat=qry.value(1).toString();
           QString phone=qry.value(2).toString();
           QString address=qry.value(3).toString();
           QString email=qry.value(4).toString();
           QString website=qry.value(5).toString();

           companydetails.push_front(name);
           companydetails.push_front(vat);
           companydetails.push_front(phone);
           companydetails.push_front(address);
           companydetails.push_front(email);
           companydetails.push_front(website);
       }
       else
       {
           qDebug()<<"not executing qyery";
       }

    }
      return companydetails;
}


 bool Dbase_Cashier::validProduct(QString &id)
 {
     QSqlQuery qry;
     qry.prepare("SELECT * FROM Product WHERE ID=:id");
     qry.bindValue(":id",id);
     if(qry.exec())
     {
         if(qry.next()){
        return true;}
     }
     else
     {
         return false;
     }
 }


bool Dbase_Cashier::validCashier(QString &username,QString &opassword)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM Cashier_Login WHERE UserName=:uname AND Password=:password");
    qry.bindValue(":uname",username);
    qry.bindValue(":password",opassword);
    if(qry.exec())
    {
       return true;
    }
    else
    {
        return false;
    }
}

void Dbase_Cashier::updateCashier(QString &username,QString &opassword)
{
    QSqlQuery qry;
    qry.prepare("UPDATE Cashier SET Password=:password WHERE UserName=:uname");
    qry.bindValue(":password",opassword);
    qry.bindValue(":uname",username);
    qry.exec();
}


////functions for invoice

void Dbase_Cashier::createBillTable()
{
    QSqlQuery qry;
    qry.prepare("CREATE TABLE Bill(ID TEXT,Name TEXT,Rate REAL,Quantity INT,Amount REAL)");
    if (!qry.exec())
    {
        qDebug() <<"Couldn't create Table,one might already exist";

    }
    else
    {
        qDebug()<<"Create table";
    }
}

QList<QString> Dbase_Cashier::getProductDetails(const QString &id)
{
    QList<QString> productdetails;
    QSqlQuery qry;
    qry.prepare(QString("SELECT * FROM Product WHERE ID=:id"));
    qry.bindValue(":id",id);
    if(!qry.exec())
    {
        qDebug()<<"Error in retriving data"<<qry.lastError();
    }
    else
    {

       if(qry.next())
       {
           QString id=qry.value(0).toString();
           QString name=qry.value(1).toString();
           QString category=qry.value(2).toString();
           QString price=qry.value(3).toString();

           productdetails.push_front(id);
           productdetails.push_front(name);
           productdetails.push_front(category);
           productdetails.push_front(price);
       }
       else
       {
           qDebug()<<"not executing qyery";
       }

    }
      return productdetails;
}

bool Dbase_Cashier::addProduct(const QString &id, const QString &name, const int &quantity, const double &rate, const double &amount)
{
    bool sucess=false;
    QSqlQuery qry;
    qry.prepare("INSERT INTO Bill(ID,Name,Quantity,Rate,Amount) VALUES (:id,:name,:quantity,:rate,:amount)");
    qry.bindValue(":id",id);
    qry.bindValue(":name",name);
    qry.bindValue(":quantity",quantity);
    qry.bindValue(":rate",rate);
    qry.bindValue(":amount",amount);

    if(!qry.exec())
    {
        qDebug()<<"Add Details Failed"<<qry.lastError();
        sucess=false;
    }
    else
    {
        qDebug()<<"Details added Sucessfully";
        sucess=true;
    }
    return sucess;

}

bool Dbase_Cashier::product_IdExists(const QString &id)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM Bill WHERE ID=:id");
    qry.bindValue(":id",id);
    if(qry.exec())
    {
        if(qry.next())
        {
            qDebug()<<"ID exists";
            return true;
        }

    }
    else
    {
        qDebug()<<"ID doesn't exist";
        return false;
    }
}

void Dbase_Cashier::deleteBillTable()
{
    QSqlQuery qry;
    qry.prepare("DROP TABLE Bill");
    qry.exec();
}

QList<QString> Dbase_Cashier::getAmount()
{
    QList<QString> amountdetails;
    QSqlQuery qry;
    qry.prepare(QString("SELECT Amount FROM Bill"));
    if(!qry.exec())
    {
        qDebug()<<"Error in retriving data"<<qry.lastError();
    }
    else
    {
       while(qry.next())
       {
           QString a=qry.value(0).toString();
           amountdetails.push_front(a);

       }
    }
      qDebug()<<amountdetails.count();
      return amountdetails;
}


void Dbase_Cashier::createHistoryTable()
{
    QSqlQuery qry;
    qry.prepare("CREATE TABLE `History` ( `Bill` INTEGER NOT NULL UNIQUE, `Date` TEXT, `Amount` REAL, `Cashier` TEXT, PRIMARY KEY(`Bill`) )");
    if (!qry.exec())
    {
        qDebug() <<"Couldn't create Table,one might already exist";

    }
    else
    {
        qDebug()<<"Create table";
    }
}

bool Dbase_Cashier::addHistory(const int &billno, const QString &date, const double &billamount, const QString &cashier)
{
    bool sucess=false;
    QSqlQuery qry;
    qry.prepare("INSERT INTO History(Bill,Date,Amount,Cashier) VALUES (:billno,:date,:billamount,:cashier)");
    qry.bindValue(":billno",billno);
    qry.bindValue(":date",date);
    qry.bindValue(":billamount",billamount);
    qry.bindValue(":cashier",cashier);
    if(!qry.exec())
    {
        qDebug()<<"Add Details Failed"<<qry.lastError();
        sucess=false;
    }
    else
    {
        qDebug()<<"Details added Sucessfully";
        sucess=true;
    }
    return sucess;

}
