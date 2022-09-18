#include "mainwindow.h"
#include "weiyawebsocket.h"
#include <QtWebSockets/QtWebSockets>
#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
   qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

   QApplication a(argc, argv);
   QSettings m_stIniFile( QCoreApplication::applicationDirPath() + "\\Config.ini", QSettings::IniFormat);
   QString l_sIP = m_stIniFile.value("WebSocket/IPAddress", "localhost").toString();
   int l_iPort = m_stIniFile.value("WebSocket/Port", 8000).toInt();
   QString l_sWsDNS = QStringLiteral("ws://") + l_sIP + QStringLiteral(":") + QString::number(l_iPort);
   WeiyaWebSocket wws(QUrl::fromUserInput(l_sWsDNS)) ;
   MainWindow w(&wws);

   QObject::connect(&wws, &WeiyaWebSocket::HelloBack, &w, &MainWindow::ShowHelloBack);
   QObject::connect(&wws, &WeiyaWebSocket::closed, &a, &QCoreApplication::quit);
   QObject::connect(&w, &MainWindow::closed, &a, &QCoreApplication::quit);

   w.show();
   return a.exec();
}
