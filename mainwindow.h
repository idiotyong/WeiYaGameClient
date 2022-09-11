#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   MainWindow(QObject *WebSocketObj, QWidget *parent = nullptr);
   ~MainWindow();

public slots:
   void ShowHelloBack();

private:
   Ui::MainWindow *ui;
signals:
   void SendLoginMsgSignal(QString _sUserName, QString _sPassword);

   bool GetConnectState();

private slots:
   void LoginOk();
   void LoginBack(bool _bSuccess);

};
#endif // MAINWINDOW_H
