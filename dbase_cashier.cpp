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
    qry.prepare(QString("SELECT * FROM Admin_Login"));
    if(!qry.exec())
    {
        qDebug()<<"Error in retriving data"<<qry.lastError();
    }
    else
    {

       if(qry.next())
       {
           QString name=qry.value(1).toString();
           QString username=qry.value(2).toString();
           QString mobileno=qry.value(3).toString();
           QString email=qry.value(4).toString();
           QString passwd=qry.value(5).toString();

           cashierdetails.push_front(name);
           cashierdetails.push_front(username);
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

