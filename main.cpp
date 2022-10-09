#include "mainwindow.h"
#include "weiyawebsocket.h"
#include <QtWebSockets/QtWebSockets>
#include <QApplication>
#include <QSettings>
#include <QTranslator>


int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   QSettings m_stIniFile( QCoreApplication::applicationDirPath() + "/Config.ini", QSettings::IniFormat);
   QString l_sIP = m_stIniFile.value("WebSocket/IPAddress", "192.168.1.151").toString();
   int l_iPort = m_stIniFile.value("WebSocket/Port", 8000).toInt();
   QString l_sWsDNS = QStringLiteral("ws://") + l_sIP + QStringLiteral(":") + QString::number(l_iPort);
   WeiyaWebSocket wws(QUrl::fromUserInput(l_sWsDNS)) ;

   QTranslator translator;
   translator.load(":/file/translang/CHT.qm");
   a.installTranslator(&translator);
   MainWindow w(&wws);

   QObject::connect(&wws, &WeiyaWebSocket::HelloBack, &w, &MainWindow::ShowHelloBack);
   QObject::connect(&wws, &WeiyaWebSocket::closed, &a, &QCoreApplication::quit);
   QObject::connect(&w, &MainWindow::closed, &a, &QCoreApplication::quit);

   w.show();
   return a.exec();
}
