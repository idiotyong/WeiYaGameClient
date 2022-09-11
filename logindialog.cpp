#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QObject *WebSocketObj, QWidget *parent) :
   QDialog(parent),
   ui(new Ui::LoginDialog)
{
   ui->setupUi(this);
   connect(this, SIGNAL(SendLoginMsgSignal(QString, QString)), WebSocketObj, SLOT(SendLoginMsg(QString, QString)));
   connect(this, SIGNAL(GetConnectState()), WebSocketObj, SLOT(IsConnect()));

   connect(WebSocketObj, SIGNAL(LoginBack(bool)), this, SLOT(LoginBack(bool)));
   connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(LoginOk()));   
}

LoginDialog::~LoginDialog()
{
   delete ui;
}

void LoginDialog::LoginOk()
{
   if(!GetConnectState())
   {
      QMessageBox::information(NULL, "Error", "Fail to Connect Server!");
      return;
   }

   SendLoginMsgSignal(ui->ledtUserName->text(), "");
}

void LoginDialog::LoginBack(bool _bSuccess)
{
   if(_bSuccess)
   {
      close();
   }
   else
   {
      QMessageBox::information(NULL, "Error", "Fail to Login !");
   }
}
