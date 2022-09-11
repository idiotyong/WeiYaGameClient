#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QObject *WebSocketObj, QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   for(int i = 0; i < ui->tabWidget->count(); i++)
   {
      ui->tabWidget->setTabVisible(i, false);
   }
   ui->tabWidget->setCurrentIndex(0);

   connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(GameOkClick()));

   connect(this, SIGNAL(SendLoginMsgSignal(QString, QString)), WebSocketObj, SLOT(SendLoginMsg(QString, QString)));
   connect(this, SIGNAL(GetConnectState()), WebSocketObj, SLOT(IsConnect()));
   connect(this, SIGNAL(SendVotedNumMsgSignal(int)), WebSocketObj, SLOT(SendVotedNumMsg(int)));

   connect(WebSocketObj, SIGNAL(LoginBack(bool)), this, SLOT(LoginBack(bool)));
   connect(ui->btnLoginOK, SIGNAL(clicked()), this, SLOT(LoginOk()));
   connect(WebSocketObj, SIGNAL(StartToVote()), this, SLOT(StartToVote()));
   connect(WebSocketObj, SIGNAL(RewardedEvent()), this, SLOT(OnRewarded()));
   connect(WebSocketObj, SIGNAL(OnGetCandidateNo(int)), ui->lcdRewardNumber, SLOT(display(int)));

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

   SendLoginMsgSignal(ui->cbUserName->currentText(), "");
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

