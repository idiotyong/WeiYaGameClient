#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
   Q_OBJECT

public:
   explicit LoginDialog(QObject *WebSocketObj, QWidget *parent = nullptr);
   ~LoginDialog();

private:
   Ui::LoginDialog *ui;

signals:
   void SendLoginMsgSignal(QString _sUserName, QString _sPassword);

   bool GetConnectState();

private slots:
   void LoginOk();
   void LoginBack(bool _bSuccess);
};

#endif // LOGINDIALOG_H
