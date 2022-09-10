#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QObject *WebSocketObj, QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
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

