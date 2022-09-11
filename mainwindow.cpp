#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"

MainWindow::MainWindow(QObject *WebSocketObj, QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
   , m_WebSocketObj(WebSocketObj)
{
   ui->setupUi(this);
   connect(ui->btnOk, SIGNAL(clicked()), WebSocketObj, SLOT(SendHelloMsg()));
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::ShowHelloBack()
{
   ui->tbServerMsg->append("I'm Here!");
}

void MainWindow::showEvent(QShowEvent *ev)
{
   QMainWindow::showEvent(ev);
   ShowLoginDialog();
}

void MainWindow::ShowLoginDialog()
{
   LoginDialog *l_ldDialog = new LoginDialog(m_WebSocketObj);

   l_ldDialog->exec();
   delete l_ldDialog;
}
