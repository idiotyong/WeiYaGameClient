#ifndef WEIYAWEBSOCKET_H
#define WEIYAWEBSOCKET_H

#include <QObject>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include "../../Include/WebSocketAPI.h"

class WeiyaWebSocket : public QObject
{
   Q_OBJECT
public:
   explicit WeiyaWebSocket(const QUrl &url, QObject *parent = nullptr);

signals:
   void closed();
   void HelloBack();

private:
   void SendWeiyaWebSocketMesaage(const TWeiYaWebSocketMsg WeiYaWebSocketMsg);

private Q_SLOTS:
   void onConnected();
   void onbinaryMessageReceived(const QByteArray &message);

private:
   QWebSocket m_webSocket;
   QUrl m_url;
   bool m_debug;

public slots:
   void SendHelloMsg();
};

#endif // WEIYAWEBSOCKET_H
