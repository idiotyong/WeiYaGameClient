#include "mainwindow.h"
#include "weiyawebsocket.h"
#include <QtWebSockets/QtWebSockets>
#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   WeiyaWebSocket wws(QUrl(QStringLiteral("ws://192.168.1.129:8000")));
   MainWindow w(&wws);

   QObject::connect(&wws, &WeiyaWebSocket::HelloBack, &w, &MainWindow::ShowHelloBack);
   QObject::connect(&wws, &WeiyaWebSocket::closed, &a, &QCoreApplication::quit);
   w.show();
   return a.exec();
}
