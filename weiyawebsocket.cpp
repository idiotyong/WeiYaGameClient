#include "weiyawebsocket.h"

WeiyaWebSocket::WeiyaWebSocket(const QUrl &url, QObject *parent)
   : QObject{parent}
{
   m_bIsConnect = false;
   connect(&m_webSocket, &QWebSocket::connected, this, &WeiyaWebSocket::onConnected);
   connect(&m_webSocket, &QWebSocket::binaryMessageReceived,
           this, &WeiyaWebSocket::onbinaryMessageReceived);
   m_webSocket.open(QUrl(url));
}

void WeiyaWebSocket::SendWeiyaWebSocketMesaage(const TWeiYaWebSocketMsg WeiYaWebSocketMsg)
{
   QByteArray l_baMsg;
   l_baMsg.clear();
   l_baMsg.append((char*)&WeiYaWebSocketMsg, sizeof(TWeiYaWebSocketMsg));
   m_webSocket.sendBinaryMessage(l_baMsg);
}

void WeiyaWebSocket::onConnected()
{
   m_bIsConnect = true;
}

void WeiyaWebSocket::onbinaryMessageReceived(const QByteArray &message)
{
   TWeiYaWebSocketMsg l_WeiYaWebSocketMsg;
   memcpy(&l_WeiYaWebSocketMsg, message.data(), sizeof(l_WeiYaWebSocketMsg));

   switch(l_WeiYaWebSocketMsg.WeiYaMsgType)
   {
      case wym_ImHere:
         HelloBack();
      break;
      case wym_LoginBack:
         LoginBack(!l_WeiYaWebSocketMsg.WeiYaWebSocketData.ServerToClient.m_iLoginReply);
      break;
      case wym_GetState:
      break;
      case wym_GetStateBack:
      break;
      case wym_SetState:
      break;
      case wym_SetStateBack:
      break;

   }
}

void WeiyaWebSocket::SendHelloMsg()
{
   TWeiYaWebSocketMsg l_WeiYaWebSocketMsg;
   l_WeiYaWebSocketMsg.WeiYaMsgType = wym_Hello;
   SendWeiyaWebSocketMesaage(l_WeiYaWebSocketMsg);
}

void WeiyaWebSocket::SendLoginMsg(QString _sUserName, QString _sPassword)
{
   TWeiYaWebSocketMsg l_WeiYaWebSocketMsg;
   l_WeiYaWebSocketMsg.WeiYaMsgType = wym_Login;
   strcpy( l_WeiYaWebSocketMsg.WeiYaWebSocketData.ClientToServer.LoginData.m_sUserID,
         _sUserName.toStdString().c_str());
   strcpy( l_WeiYaWebSocketMsg.WeiYaWebSocketData.ClientToServer.LoginData.m_sPassWord,
          _sPassword.toStdString().c_str());
   SendWeiyaWebSocketMesaage(l_WeiYaWebSocketMsg);
}

bool WeiyaWebSocket::IsConnect()
{
   return m_bIsConnect;
}

