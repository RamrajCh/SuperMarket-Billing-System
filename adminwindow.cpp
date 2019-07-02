#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::AdminWindow)
{
  ui->setupUi(this);
}

AdminWindow::~AdminWindow()
{
  delete ui;
}

void AdminWindow::on_companyButton_clicked()
{
    //show Company Stack
    ui->adminStack->setCurrentIndex(0);
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
