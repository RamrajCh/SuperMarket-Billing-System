#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::AdminWindow)
{
  ui->setupUi(this);
  QDate date;
  QString currentDate=date.currentDate().toString();
  ui->currentDate->setText(currentDate);
  ui->privacyStack_2->setCurrentIndex(0);
  ui->adminStack_2->setCurrentIndex(1);
  on_salesButton_clicked();
  showAdmin_LoginDetails();
  showCompanyDetails();
  ui->transactionTable->setColumnWidth(0,150);
  ui->transactionTable->setColumnWidth(1,200);
  ui->transactionTable->setColumnWidth(2,200);
  ui->transactionTable->setColumnWidth(3,250);
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

void AdminWindow :: hidePrivacy()
{
    ui->privacyStack_2->setCurrentIndex(0);
}

void AdminWindow::on_companyButton_clicked()
{
    hidePrivacy();
    //show Company Stack
    ui->adminStack_2->setCurrentIndex(2);
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
    hidePrivacy();
    Dbase_admin db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM Cashier");

    qry->exec();

    model->setQuery(*qry);
    ui->adminStack_2->setCurrentIndex(2);
    ui->adminStack->setCurrentIndex(1);
    ui->cashierStack->setCurrentIndex(2);
    ui->cashierTable->setModel(model);
    setCashierTable();
}

void AdminWindow::on_productButton_clicked()
{
    hidePrivacy();
    ui->adminStack_2->setCurrentIndex(2);
    ui->adminStack->setCurrentIndex(2);
    ui->productStack->setCurrentIndex(1);
    on_viewProductButton_clicked();
}

void AdminWindow::on_privacyButton_clicked()
{
    int curind=ui->privacyStack_2->currentIndex();
    if(curind==0)
    {
     ui->privacyStack_2->setCurrentIndex(1);
    }
    else
    {
      hidePrivacy();
    }
}

void AdminWindow::on_companyUpdateButton_clicked()
{
    //show update form
    ui->companyStack->setCurrentIndex(1);
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
            ui->company->setText(name);
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

void AdminWindow::on_editButton_1_clicked()
{
    ui->companyStack->setCurrentIndex(1);
}

void AdminWindow::on_okButton_2_clicked()
{
    //extract values from ui
    QString name=ui->cashierName->text();
    QString uname=ui->cashierUsername->text();
    QString gender=ui->genderBox->currentText();
    QString phone=ui->cashierPhone->text();
    QString email=ui->cashierEmail->text();
    QString passwd=ui->cashierPassword->text();

    //check data validation
    if(isVacant(name)) showError(this,"Specify Cashier Name");
    else if(isVacant(uname)) showError(this,"Specify Cashier UserName");
    else if(gender=="Choose Gender") showError(this,"Specify Gender of Cashier");
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
                if(db.cashier_unameExists(uname))
                {
                     QMessageBox::information(this,"Cashier Registration","Username already taken");
                }
                else
                {
                     if(db.cashier_emailExists(email))
                     {
                          QMessageBox::information(this,"Cashier Registration","Email already taken");
                     }
                     else
                     {
                         if(db.addCashierDetails(name,uname,gender,phone,email,passwd))
                         {
                             //vacant the line edits
                             ui->cashierName->setText("");
                             ui->cashierUsername->setText("");
                             ui->cashierPhone->setText("");
                             ui->cashierEmail->setText("");
                             ui->cashierPassword->setText("");
                             QMessageBox::StandardButton stdButton=QMessageBox::question(this,"Added Sucessfully","Want to add more?",QMessageBox::Yes|QMessageBox::No);
                             if(stdButton==QMessageBox::Yes)
                             {
                                 //got to cashier main stack
                                 ui->cashierStack->setCurrentIndex(1);
                             }
                             else
                             {
                                 //got to cashier main stack
                                 on_viewCashierButton_clicked();
                              }
                         }
                         else
                         {
                             QMessageBox::information(this,"Cashier Details","Failed to add");
                         }
                     }

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

void AdminWindow::setCashierTable()
{
    ui->cashierTable->setColumnWidth(0,200);
    ui->cashierTable->setColumnWidth(1,200);
    ui->cashierTable->setColumnWidth(2,150);
    ui->cashierTable->setColumnWidth(3,200);
    ui->cashierTable->setColumnWidth(4,250);
    ui->cashierTable->setColumnWidth(5,100);
}

void AdminWindow::on_viewCashierButton_clicked()
{
    Dbase_admin db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM Cashier");

    qry->exec();

    model->setQuery(*qry);
    ui->adminStack->setCurrentIndex(1);
    ui->cashierStack->setCurrentIndex(2);
    ui->cashierTable->setModel(model);
    setCashierTable();

}

void AdminWindow::on_specificButton_clicked()
{
    Dbase_admin db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();

    QString uname=ui->cashierUsername_2->text();
    QString name=ui->cashierName_2->text();

    if((uname=="" && name!="")||(name=="" && uname!=""))
    {
         qDebug()<<"only one specification";
         qry->prepare("SELECT * FROM Cashier WHERE UserName=:uname OR Name=:name");
         qry->bindValue(":uname",uname);
         qry->bindValue(":name",name);

         qry->exec();

         model->setQuery(*qry);
         ui->adminStack->setCurrentIndex(1);
         ui->cashierStack->setCurrentIndex(2);
         ui->cashierTable->setModel(model);

    }

    else if(uname!="" && name!="")
    {
        qDebug()<<"both specification";
        qry->prepare("SELECT * FROM Cashier WHERE UserName=:uname AND Name=:name");
        qry->bindValue(":uname",uname);
        qry->bindValue(":name",name);

        qry->exec();

        model->setQuery(*qry);
        ui->adminStack->setCurrentIndex(1);
        ui->cashierStack->setCurrentIndex(2);
        ui->cashierTable->setModel(model);

    }

    else if(uname=="" && name=="")
    {
        QMessageBox::information(this,"Specific Cashier","Please Specify any one");
        qry->prepare("SELECT * FROM Cashier");

        qry->exec();

        model->setQuery(*qry);
        ui->adminStack->setCurrentIndex(1);
        ui->cashierStack->setCurrentIndex(2);
        ui->cashierTable->setModel(model);

    }
    setCashierTable();
    ui->cashierUsername_2->setText("");
    ui->cashierName_2->setText("");
}

void AdminWindow::on_removeButton_clicked()
{
    //remove a cashier

    //extract values from ui
    QString uname=ui->cashierUsername_3->text();
    QString email=ui->cashierEmail_3->text();

    Dbase_admin db("SBS.db");
    if(!db.isOpen())
    {
        qDebug()<<"No connection to database";
    }
    else
    {
        if(!db.validCashier(uname,email))
        {
            QMessageBox::warning(this,"Remove Cashier","Do not match any cashier..");
        }

        else
        {
            QMessageBox::StandardButton stdbut=QMessageBox::warning(this,"Remove Cashier","You want to delete cashier",QMessageBox::Yes|QMessageBox::No);
            if(stdbut=QMessageBox::Yes){
            db.removeCashier(uname,email);
            QMessageBox::information(this,"Remove Cashier","Sucessful");
            ui->cashierStack->setCurrentIndex(2);
            on_viewCashierButton_clicked();
            //clear username and email
            ui->cashierUsername_3->setText("");
            ui->cashierEmail_3->setText("");
        }
        }
    }
}

void AdminWindow::on_cancelButton_clicked()
{
    ui->cashierStack->setCurrentIndex(2);
}

void AdminWindow::on_removeCashierButton_clicked()
{
    ui->cashierStack->setCurrentIndex(3);
}

void AdminWindow::on_removeAllCashierButton_clicked()
{
    QMessageBox::StandardButton stdButton=QMessageBox::question(this,"Remove all Cashier","Do you really want to delete all cashier?",QMessageBox::Yes|QMessageBox::No);
    if(stdButton==QMessageBox::Yes)
    {
        Dbase_admin db("SBS.db");
        if(db.removeCashierTable())
           {
               QMessageBox::information(this,"Delete Cashier","Deletion Sucessful");
           }
        }
}

void AdminWindow::on_logoutButton_clicked()
{
    qDebug()<<"hwkjdh";
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

void AdminWindow::on_editButton_2_clicked()
{
        hidePrivacy();
        //go to edit admin stack
        ui->adminStack_2->setCurrentIndex(2);
        ui->adminStack->setCurrentIndex(3);
        ui->privacyStack->setCurrentIndex(1);

        //show placeholder text
        ui->userName->setPlaceholderText("Give your User Name");
        ui->oldPassword->setPlaceholderText("Give your old Password");
        ui->newPassword->setPlaceholderText("Give New Password");
        ui->confirmNewPassword->setPlaceholderText("Confirm your Password");
}

void AdminWindow::on_changePasswordButton_clicked()
{
   //change text in line edit to string
    QString username=ui->userName->text();
    QString oPassword=ui->oldPassword->text();
    QString nPassword=ui->newPassword->text();
    QString cnPasswod=ui->confirmNewPassword->text();

    qDebug()<<username;
    qDebug()<<oPassword;
    qDebug()<<nPassword;

    //check password validation
    Dbase_admin db("SBS.db");
    if(!db.uNameExists(username))
    {
        QMessageBox::critical(this,"Username Validation","Your Username doesnot match");
    }
    else
    {
        if(!db.passwordValid(oPassword))
        {
            QMessageBox::critical(this,"Password Validation","Your Password doesnot match");
        }
        else
        {
            if(!(nPassword==cnPasswod))
            {
                QMessageBox::warning(this,"Confirm Password","Your Confirm Password Doesnot match with New Password");
            }
            else
            {
                //change the password
                db.changeAdminPassword(username,nPassword);
                db.changeAdmin_LoginPassword(username,nPassword);
                QMessageBox::information(this,"Change Password","Sucessful!");
                //clear the screen
                ui->userName->setText("");
                ui->oldPassword->setText("");
                ui->newPassword->setText("");
                ui->confirmNewPassword->setText("");
                //go to privacy stack
                ui->privacyStack->setCurrentIndex(0);
               showAdmin_LoginDetails();
            }
        }
    }
}

void AdminWindow::on_addButton_clicked()
{
    ui->adminStack->setCurrentIndex(2);
    ui->productStack->setCurrentIndex(0);
    ui->addStack->setCurrentIndex(0);
}

void AdminWindow::on_addProductButton_2_clicked()
{
    QString productid=ui->productID->text();
    QString productname=ui->productName->text();
    QString productprice=ui->productPrice->text();
    QString productcategory=ui->categoryCombo->currentText();

    //check if all fields are filled
    //check data validation
    if(isVacant(productid)) showError(this,"Specify Product ID");
    else if(isVacant(productname)) showError(this,"Specify Product Name");
    else if(isVacant(productprice)) showError(this,"Specify Product Price");
    else if(productcategory=="Uncategorized")
    {
        QMessageBox::information(this,"Category","You don't categorized the product.");
    }
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
           db.createProductTable();
           if(db.product_IdExists(productid))
           {
               QMessageBox::information(this,"Product","Product ID already used");
           }
           else
           {
               if(db.product_NameExists(productname))
               {
                 QMessageBox::information(this,"Product","Name already taken");
               }
               else
               {
                  if(db.addProduct(productid,productname,productcategory,productprice))
                  {
                    //vacant the line edits
                     ui->productID->setText("");
                     ui->productName->setText("");
                     ui->productPrice->setText("");
                     ui->categoryCombo->setCurrentIndex(0);
                     QMessageBox::StandardButton stdButton=QMessageBox::question(this,"Added Sucessfully","Want to add more?",QMessageBox::Yes|QMessageBox::No);
                     if(stdButton==QMessageBox::Yes)
                     {
                        //got to add product main stack
                        ui->addStack->setCurrentIndex(0);
                     }
                     else
                     {
                        //got to privacy stack
                        ui->adminStack->setCurrentIndex(2);
                        ui->productStack->setCurrentIndex(1);
                        on_viewProductButton_clicked();
                     }
                  }
               }
            }
        }
    }
}

void AdminWindow::setProductTable()
{
    ui->productTable->setColumnWidth(0,100);
    ui->productTable->setColumnWidth(1,250);
    ui->productTable->setColumnWidth(2,200);
    ui->productTable->setColumnWidth(3,150);
}

void AdminWindow::on_viewProductButton_clicked()
{

    Dbase_admin db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM Product");

    qry->exec();

    model->setQuery(*qry);
    ui->adminStack->setCurrentIndex(2);
    ui->productStack->setCurrentIndex(1);
    ui->productTable->setModel(model);
        setProductTable();
}

void AdminWindow::on_specificButton_2_clicked()
{

    Dbase_admin db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();

    QString id=ui->product_id->text();
    QString category=ui->product_category->currentText();

    if((id=="" && category!="Search By Category")||(category=="Search By Category" && id!=""))
    {
         qDebug()<<"only one specification";
         qry->prepare("SELECT * FROM Product WHERE ID=:id OR Category=:category");
         qry->bindValue(":id",id);
         qry->bindValue(":category",category);

         qry->exec();

         model->setQuery(*qry);
         ui->adminStack->setCurrentIndex(2);
         ui->productStack->setCurrentIndex(1);
         ui->productTable->setModel(model);
             setProductTable();

    }

    else if(id!="" && category!="")
    {
        qDebug()<<"both specification";
        qry->prepare("SELECT * FROM Product WHERE ID=:id AND Category=:category");
        qry->bindValue(":id",id);
        qry->bindValue(":category",category);

        qry->exec();

        model->setQuery(*qry);
        ui->adminStack->setCurrentIndex(2);
        ui->productStack->setCurrentIndex(1);
        ui->productTable->setModel(model);
            setProductTable();

    }

    else if(id=="" && category=="")
    {
        QMessageBox::information(this,"Specific Cashier","Please Specify any one");
        qry->prepare("SELECT * FROM Product");

        qry->exec();

        model->setQuery(*qry);
        ui->adminStack->setCurrentIndex(2);
        ui->productStack->setCurrentIndex(1);
        ui->productTable->setModel(model);
            setProductTable();
    }
    ui->product_id->setText("");
}

void AdminWindow::on_deleteProductButton_clicked()
{
    ui->adminStack->setCurrentIndex(2);
    ui->productStack->setCurrentIndex(2);
}

void AdminWindow::on_delete_product_clicked()
{
    QString id=ui->product_id_2->text();
    QString category=ui->product_category_2->text();

    Dbase_admin db("SBS.db");
    if(db.isOpen())
    {
       if(db.validProduct(id,category))
       {
          QMessageBox::StandardButton stdbut=QMessageBox::warning(this,"Delete","You want to delete product.",QMessageBox::Yes|QMessageBox::No);
          if(stdbut==QMessageBox::Yes)
          {
             db.deleteProducts(id,category);
             QMessageBox::information(this,"Remove Cashier","Sucessful");
             ui->product_id->setText("");
             ui->product_category_2->setText("");
          }
        }
        else
        {
           QMessageBox::information(this,"Remove Cashier","Do not match any cashier..");
        }
    }
}

void AdminWindow::on_addAdminButton_clicked()
{
   hidePrivacy();
    ui->adminStack_2->setCurrentIndex(0);

}

void AdminWindow::on_salesButton_clicked()
{
    hidePrivacy();
    ui->adminStack_2->setCurrentIndex(1);
    Dbase_admin db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM History");

    qry->exec();

    model->setQuery(*qry);
    ui->historyStack->setCurrentIndex(0);
    ui->transactionTable->setModel(model);
}

void AdminWindow::on_registerButton_2_clicked()
{
    //Connect to database and register Admin user


        //extract text from ui
        QString fname=ui->firstName->text();
        QString lname=ui->lastName->text();
        QString username=ui->userName_2->text();
        QString mobileno=ui->mobileNum->text();
        QString email=ui->eMail->text();
        QString passwd=ui->getPass->text();
        QString confirm_passwd=ui->conPass->text();


        //check Data Validation
        if(isVacant(fname)) showError(this,"Specify your First Name");
        else if(isVacant(lname)) showError(this,"Specify your Last Name");
        else if(isVacant(username)) showError(this,"Enter your Username");
        else if(isVacant(mobileno)) showError(this,"Specify your Mobile Number");
        else if(isVacant(email)) showError(this,"Specify your E-mail");
        else if(isVacant(passwd)) showError(this,"Enter your Password");
        else if(isVacant(confirm_passwd)) showError(this,"Confirm your Password");

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
                  qDebug()<<"connected to database";
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
                      if(db.addAdmin(fname,lname,username,mobileno,email,passwd))
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
                      }
                      else
                      {
                          QMessageBox::information(this,"Registration","Registered Unsucessful");
                      }
                   }
                 }
        }
}

void AdminWindow::on_removeAccount_clicked()
{
    QMessageBox::StandardButton stdbutton=QMessageBox::critical(this,"Remove Account","Do you want to remove your account?",QMessageBox::Yes|QMessageBox::No);
    if(stdbutton==QMessageBox::Yes)
    {
            Dbase_admin db("SBS.db");
            if(db.isOpen())
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

                QSqlQuery qry;
                qry.prepare("DELETE FROM Admin WHERE UserName=:username");
                qry.bindValue(":username",username);

                if(qry.exec())
                {
                   QApplication::quit();
                }

            }
        }
    }
}

void AdminWindow::on_todayHistory_clicked()
{
    ui->historyStack->setCurrentIndex(0);
    QDate Date;
    QString currentDate=Date.currentDate().toString("dd/MM/yyyy");
    Dbase_admin db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT *FROM History WHERE Date=:date");
    qry->bindValue(":date",currentDate);
    qry->exec();

    model->setQuery(*qry);
   ui->transactionTable->setModel(model);
}

void AdminWindow::on_gotodateHistory_clicked()
{
    ui->historyStack->setCurrentIndex(1);
}

void AdminWindow::on_cashierHistory_clicked()
{
     ui->historyStack->setCurrentIndex(2);
}

void AdminWindow::on_okButton_3_clicked()
{
    QString day=ui->dCombo->currentText();
    QString month=ui->mCombo->currentText();
    QString year=ui->yCombo->currentText();
    if(day=="Day"||month=="Month"||year=="Year")
    {
        QMessageBox::information(this,"GoTo Date","Please Specify Correct Date");
    }
    else
    {
        QString date=day+'/'+month+'/'+year;
        Dbase_admin db("SBS.db");
        QSqlQueryModel *model= new QSqlQueryModel();

        QSqlQuery *qry=new QSqlQuery();
        qry->prepare("SELECT *FROM History WHERE Date=:date");
        qry->bindValue(":date",date);
        qry->exec();

        model->setQuery(*qry);
       ui->transactionTable->setModel(model);
    }
}

void AdminWindow::on_goButton_2_clicked()
{
    QString uname=ui->userName_History->text();
    Dbase_admin db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM History WHERE Cashier=:cashier");
    qry->bindValue(":cashier",uname);
    qry->exec();

    model->setQuery(*qry);
   ui->transactionTable->setModel(model);
}

void AdminWindow::on_pushButton_clicked()
{
    ui->adminStack->setCurrentIndex(3);
    ui->privacyStack->setCurrentIndex(0);
    showAdmin_LoginDetails();
}
