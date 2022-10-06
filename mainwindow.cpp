#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QObject *WebSocketObj, QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   ui->tbServerMsg->setVisible(false);

   for(int i = 0; i < ui->tabWidget->count(); i++)
   {
      ui->tabWidget->setTabVisible(i, false);
   }
   ui->tabWidget->setCurrentIndex(0);

   connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(GameOkClick()));

   connect(this, SIGNAL(SendLoginMsgSignal(QString, QString)), WebSocketObj, SLOT(SendLoginMsg(QString, QString)));
   connect(this, SIGNAL(GetConnectState()), WebSocketObj, SLOT(IsConnect()));
   connect(this, SIGNAL(SendVotedNumMsgSignal(int)), WebSocketObj, SLOT(SendVotedNumMsg(int)));
   connect(this, SIGNAL(GetIPAddress()), WebSocketObj, SLOT(SendIPAddress()));
   connect(ui->cbAuto , SIGNAL(clicked(bool)), WebSocketObj, SLOT(SetAuto(bool)));
   connect(ui->cbRandom , SIGNAL(clicked(bool)), WebSocketObj, SLOT(SetRandom(bool)));

   connect(WebSocketObj, SIGNAL(LoginBack(bool)), this, SLOT(LoginBack(bool)));
   connect(ui->btnLoginOK, SIGNAL(clicked()), this, SLOT(LoginOk()));
   connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(LoginCancel()));
   connect(ui->btnContinue , SIGNAL(clicked()), this, SLOT(ContinueAfterAward()));
   connect(WebSocketObj, SIGNAL(StartToVote()), this, SLOT(StartToVote()));
   connect(WebSocketObj, SIGNAL(RewardedEvent()), this, SLOT(OnRewarded()));
   connect(WebSocketObj, SIGNAL(OnGetCandidateNo(int)), ui->lcdRewardNumber, SLOT(display(int)));
   connect(WebSocketObj, SIGNAL(OnSetRandomNoText(QString)), ui->cbSelectNo, SLOT(setCurrentText(QString)));
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
      QString l_sIP = GetIPAddress();
      QMessageBox::information(NULL, "Error", "Fail to Connect Server! IP: " + l_sIP);
      return;
   }

   SendLoginMsgSignal(ui->ledtUserID->text(), ui->ledtPassword->text());
}

void MainWindow::LoginCancel()
{
   closed();
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

void MainWindow::GameOkClick()
{
   SendVotedNumMsgSignal(ui->cbSelectNo->currentIndex());
   ui->btnOk->setEnabled(false);
}

void MainWindow::StartToVote()
{
   ui->btnOk->setEnabled(true);
}

void MainWindow::OnRewarded()
{
   ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::ContinueAfterAward()
{
   ui->tabWidget->setCurrentIndex(1);
}

