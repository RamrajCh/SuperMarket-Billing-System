#include <dbase.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

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
        qDebug() << "add user failed: " << qry.lastError();
    }else{
        success = true;
    }
    return success;
}



bool Dbase::removeUser(const QString& name){
    bool success = false;

    if (emailExists(name)){
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM Admin WHERE UserName = (:uname)");
        queryDelete.bindValue(":uname", name);
        success = queryDelete.exec();
        if(!success){
            qDebug() << "remove  failed: " << queryDelete.lastError();
        }
    }else{
        qDebug() << "remove user failed: user doesnt exist";
    }
    return success;
}

void Dbase::printAllUsers() const{
    qDebug() << "users in db:";
    QSqlQuery query("SELECT * FROM Admin");
    int idName = query.record().indexOf("UserName");
    while (query.next())
    {
        QString uname = query.value(idName).toString();
        qDebug() << "===" << uname;
    }
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

bool Dbase::removeAllUsers()
{
    bool success = false;

    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM Admin");

    if (removeQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "remove all users failed: " << removeQuery.lastError();
    }

    return success;
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

//QList<QString> dbase::getUserInfo(const QString& uname) const{
//    QList<QString> userList;

//    qDebug() << "users in db:";
//    QSqlQuery query;
//    query.prepare("SELECT * FROM user WHERE UserName = (:uname)");
//    query.bindValue(":uname", uname);

//    if(!query.exec()){
//        qDebug()<<"Query err"<<query.lastError();
//    }else{
//        //Query was sucessful :)
//        int email_id = query.record().indexOf("email");
//        int fname_id = query.record().indexOf("fname");
//        int lname_id = query.record().indexOf("lname");
//        int addr_id = query.record().indexOf("addr");
//        int phn_id = query.record().indexOf("phn");

//        if(query.next()){
//            QString email = query.value(email_id).toString();
//            QString fname = query.value(fname_id).toString();
//            QString lname = query.value(lname_id).toString();
//            QString addr = query.value(addr_id).toString();
//            QString phn = query.value(phn_id).toString();

//            userList.push_front(phn);
//            userList.push_front(addr);
//            userList.push_front(lname);
//            userList.push_front(fname);
//            userList.push_front(email);
//        }
//    }

//    return  userList;
//}

//QList<QString> dbase::getAllUsers(){
//    QList<QString> data;

//    qDebug() << "users in db:";
//    QSqlQuery query("SELECT * FROM user");
//    int idName = query.record().indexOf("email");
//    while (query.next()){
//        QString email = query.value(idName).toString();
//        data.push_front(email);
//    }
//    return data;
//}
