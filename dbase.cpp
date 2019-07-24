#include <dbase.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include<QMessageBox>

Dbase::Dbase(const QString &path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (!db.open()){
        qDebug() << "Error: connection with dbase fail";
    }else{
        qDebug() << "dbase: connection ok";
    }
}

Dbase::~Dbase()
{
    if (db.isOpen())
    {
        db.close();
    }
}

bool Dbase::isOpen() const
{
    return db.isOpen();
}

void Dbase::createTable()
{
   // bool success = false;

    QSqlQuery query;
    query.prepare("CREATE TABLE Admin ( FirstName TEXT NOT NULL, LastName TEXT NOT NULL, UserName TEXT NOT NULL UNIQUE, MobileNo TEXT NOT NULL, Email TEXT NOT NULL UNIQUE, Password TEXT NOT NULL )");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'Admin': one might already exist.";
        //success = false;
    }

    //return success;
}

bool Dbase::addAdmin(const QString &fname, const QString &lname, const QString &username, const QString &mobileno, const QString &email, const QString &passwd){
    bool success = false;
    QSqlQuery qry;
    qry.prepare("INSERT INTO Admin(FirstName,LastName,UserName,MobileNo,Email,Password)"" VALUES(:FirstName,:LastName,:UserName,:MobileNo,:Email,:Password)");
    qry.bindValue(":FirstName",fname);
    qry.bindValue(":LastName",lname);
    qry.bindValue(":UserName",username);
    qry.bindValue(":MobileNo",mobileno);
    qry.bindValue(":Email",email);
    qry.bindValue(":Password",passwd);

    if(!qry.exec()){
        qDebug() << "add admin failed: " << qry.lastError();
    }else{
        success = true;
    }
    return success;
}

bool Dbase::unameExists(const QString &uname){
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT UserName FROM Admin WHERE UserName = (:uname)");
    checkQuery.bindValue(":uname",uname);
    if(checkQuery.exec()){
        if(checkQuery.next()){
            return true;
        }
    }else{
        qDebug()<<"does email exist query failed "<<checkQuery.lastError();
    }
    return false;
}

bool Dbase::emailExists(const QString &email){
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT Email FROM Admin WHERE Email = (:email)");
    checkQuery.bindValue(":email",email);
    if(checkQuery.exec()){
        if(checkQuery.next()){
            return true;
        }
    }else{
        qDebug()<<"does email exist query failed "<<checkQuery.lastError();
    }
    return false;
}

bool Dbase::userAuth(const QString &uname, const QString &pass)const{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT UserName FROM Admin WHERE UserName =:uname AND Password = :pass");
    checkQuery.bindValue(":uname", uname);
    checkQuery.bindValue(":pass", pass);
    if (checkQuery.exec()){
        if (checkQuery.next()){
            exists = true;
        }
    }else{
        qDebug() << "user exists failed: " << checkQuery.lastError();
    }
    return exists;
}

QList<QString> Dbase::getAdminInfo(const QString& uname)
{
    QList<QString> adminList;

    qDebug() << "admin in db:";
    QSqlQuery query;
    query.prepare("SELECT * FROM Admin WHERE UserName =:uname");
    query.bindValue(":uname",uname);

    if(!query.exec()){
        qDebug()<<"Query err"<<query.lastError();
    }else{

        if(query.next()){
            qDebug()<<"Sent data";
            QString fname = query.value(0).toString();
            QString lname = query.value(1).toString();
            QString username = query.value(2).toString();
            QString mobileno = query.value(3).toString();
            QString email = query.value(4).toString();
            QString passwd=query.value(5).toString();

            adminList.push_front(fname);
            adminList.push_front(lname);
            adminList.push_front(username);
            adminList.push_front(mobileno);
            adminList.push_front(email);
            adminList.push_front(passwd);
        }
        else
        {
            qDebug()<<"Couldn't sent data";
        }
    }
    return  adminList;
}

bool Dbase::getAdminInfo()
{
    QList<QString> adminList;
    QSqlQuery qry;
    qry.prepare("SELECT * FROM Admin");
    if(qry.exec())
    {
        if(qry.next())
        {
            QString fname = qry.value(0).toString();
            QString lname = qry.value(1).toString();
            QString username = qry.value(2).toString();
            QString mobileno = qry.value(3).toString();
            QString email = qry.value(4).toString();
            QString passwd=qry.value(5).toString();

            adminList.push_front(fname);
            adminList.push_front(lname);
            adminList.push_front(username);
            adminList.push_front(mobileno);
            adminList.push_front(email);
            adminList.push_front(passwd);
        }
        if(adminList.count()==0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

void Dbase::createAdmin_LoginTable()
{
    QSqlQuery query;
    query.prepare("CREATE TABLE Admin_Login ( FirstName TEXT, LastName TEXT, UserName TEXT UNIQUE, MobileNo TEXT , Email TEXT UNIQUE, Password TEXT)");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'Admin_Login': one might already exist.";
    }
    else
    {
        qDebug()<<"created Admin_LoginTable";
    }
}

void Dbase::addAdmin_Login(QString &uname)
{
    QSqlQuery qry;
    //retrive data from Admin table
    QString fname,lname,username,mobileno,email,passwd;
    QList <QString> adminlist=getAdminInfo(uname);
    if(adminlist.isEmpty())
    {
        qDebug()<<"error in retriving admin details";
    }
    else
    {
        qDebug()<<"retrived data from admin";
        //retriving data from Admin
        passwd=adminlist.takeAt(0);
        email=adminlist.takeAt(0);
        mobileno=adminlist.takeAt(0);
        username=adminlist.takeAt(0);
        lname=adminlist.takeAt(0);
        fname=adminlist.takeAt(0);

        //Add value to Admin_Login table

        qry.prepare("INSERT INTO Admin_Login(FirstName,LastName,UserName,MobileNo,Email,Password) VALUES(:fname,:lname,:uname,:mobileno,:email,:passwd)");
        qry.bindValue(":fname",fname);
        qry.bindValue(":lname",lname);
        qry.bindValue(":uname",username);
        qry.bindValue(":mobileno",mobileno);
        qry.bindValue(":email",email);
        qry.bindValue(":passwd",passwd);

    if(!qry.exec())
    {
        qDebug() << "add admin failed: " << qry.lastError();
    }else
    {
        //QMessageBox::information(this,"Admin_Login Table","Created");
        qDebug()<<"add admin sucess";
    }
}
}

bool Dbase::cashierAuth(const QString &uname, const QString &pass)const{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT UserName FROM Cashier WHERE UserName =:uname AND Password = :pass");
    checkQuery.bindValue(":uname", uname);
    checkQuery.bindValue(":pass", pass);
    if (checkQuery.exec()){
        if (checkQuery.next()){
            exists = true;
        }
    }else{
        qDebug() << "user exists failed: " << checkQuery.lastError();
    }
    return exists;
}

void Dbase::createCashier_LoginTable()
{
    QSqlQuery query;
    query.prepare("CREATE TABLE Cashier_Login ( Name TEXT, UserName TEXT,Gender TEXT, Phone TEXT , Email TEXT, Password TEXT)");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'Admin_Login': one might already exist.";
    }
    else
    {
        qDebug()<<"created Admin_LoginTable";
    }
}

QList<QString> Dbase::getCashierInfo(const QString &uname)
{
    QList<QString> cashierList;

    qDebug() << "cashier in db:";
    QSqlQuery query;
    query.prepare("SELECT * FROM Cashier WHERE UserName =:uname");
    query.bindValue(":uname",uname);

    if(!query.exec()){
        qDebug()<<"Query err"<<query.lastError();
    }else{

        if(query.next()){
            qDebug()<<"Sent data";
            QString name = query.value(0).toString();
            QString username = query.value(1).toString();
            QString gender=query.value(2).toString();
            QString phone = query.value(3).toString();
            QString email = query.value(4).toString();
            QString passwd=query.value(5).toString();

            cashierList.push_front(name);
            cashierList.push_front(username);
            cashierList.push_front(gender);
            cashierList.push_front(phone);
            cashierList.push_front(email);
            cashierList.push_front(passwd);
        }
        else
        {
            qDebug()<<"Couldn't sent data";
        }
    }
    return  cashierList;
}

void Dbase::addCashier_Login(QString &uname)
{
    QSqlQuery qry;
    //retrive data from Cashier table
    QString name,username,gender,phone,email,passwd;
    QList <QString> cashierlist=getCashierInfo(uname);
    if(cashierlist.isEmpty())
    {
        qDebug()<<"error in retriving cashier details";
    }
    else
    {
        qDebug()<<"retrived data from cashier";
        //retriving data from Cashier
        passwd=cashierlist.takeAt(0);
        email=cashierlist.takeAt(0);
        phone=cashierlist.takeAt(0);
        gender=cashierlist.takeAt(0);
        username=cashierlist.takeAt(0);
        name=cashierlist.takeAt(0);

        //Add value to Cashier_Login table

        qry.prepare("INSERT INTO Cashier_Login(Name,UserName,Gender,Phone,Email,Password) VALUES(:name,:uname,:gender,:phone,:email,:passwd)");
        qry.bindValue(":name",name);
        qry.bindValue(":uname",username);
        qry.bindValue(":gender",gender);
        qry.bindValue(":phone",phone);
        qry.bindValue(":email",email);
        qry.bindValue(":passwd",passwd);
    }
    if(!qry.exec())
    {
        qDebug() << "add cashier failed: " << qry.lastError();
    }else
    {
        //QMessageBox::information(this,"Cashier_Login Table","Created");
        qDebug()<<"add cashier sucess";
    }
}
