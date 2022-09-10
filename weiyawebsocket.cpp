#include "weiyawebsocket.h"

WeiyaWebSocket::WeiyaWebSocket(const QUrl &url, QObject *parent)
   : QObject{parent}
{
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

