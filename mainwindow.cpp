#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QObject *WebSocketObj, QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   ui->tabWidget->setTabVisible(0, false);
   ui->tabWidget->setTabVisible(1, false);
   ui->tabWidget->setCurrentIndex(0);

   connect(ui->btnOk, SIGNAL(clicked()), WebSocketObj, SLOT(SendHelloMsg()));

   connect(this, SIGNAL(SendLoginMsgSignal(QString, QString)), WebSocketObj, SLOT(SendLoginMsg(QString, QString)));
   connect(this, SIGNAL(GetConnectState()), WebSocketObj, SLOT(IsConnect()));

   connect(WebSocketObj, SIGNAL(LoginBack(bool)), this, SLOT(LoginBack(bool)));
   connect(ui->btnLoginOK, SIGNAL(clicked()), this, SLOT(LoginOk()));
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::ShowHelloBack()
{
   ui->tbServerMsg->append("I'm Here!");
}

void MainWindow::LoginOk()
{
   if(!GetConnectState())
   {
      QMessageBox::information(NULL, "Error", "Fail to Connect Server!");
      return;
   }

   SendLoginMsgSignal(ui->ledtUserName->text(), "");
}

void MainWindow::LoginBack(bool _bSuccess)
{
   if(_bSuccess)
   {
      ui->tabWidget->setCurrentIndex(1);
   }
   else
   {
      QMessageBox::information(NULL, "Error", "Fail to Login !");
   }
}

