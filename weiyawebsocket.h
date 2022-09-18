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
   void LoginBack(bool _bSuccess);

   void StartToVote();
   void RewardedEvent();

   void OnGetCandidateNo(int _iNUm);

   void OnSetRandomNoText(QString _sNum);

private:
   void SendWeiyaWebSocketMesaage(const TWeiYaWebSocketMsg WeiYaWebSocketMsg);
   void GetWeiyaWebSocketState(const int _iStateID);

private Q_SLOTS:
   void onConnected();
   void onbinaryMessageReceived(const QByteArray &message);

private:
   QWebSocket m_webSocket;
   QUrl m_url;
   bool m_debug;
   bool m_bIsConnect;
   bool m_bAuto;
   bool m_bRandom;

   int m_iPrevNum;

public slots:
   void SendHelloMsg();
   void SendLoginMsg(QString _sUserName, QString _sPassword);

   bool IsConnect();
   void SendVotedNumMsg(int _iNUm);

   void SetAuto(bool _bEnabled);
   void SetRandom(bool _bEnabled);
};

#endif // WEIYAWEBSOCKET_H
