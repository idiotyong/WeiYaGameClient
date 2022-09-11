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

void WeiyaWebSocket::GetWeiyaWebSocketState(const int _iStateID)
{
   TWeiYaWebSocketMsg l_WeiYaWebSocketMsg;
   l_WeiYaWebSocketMsg.WeiYaMsgType = wym_GetState;
   l_WeiYaWebSocketMsg.WeiYaWebSocketData.ClientToServer.m_iGetStateID = _iStateID;
   SendWeiyaWebSocketMesaage(l_WeiYaWebSocketMsg);
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
         switch(l_WeiYaWebSocketMsg.WeiYaWebSocketData.ServerToClient.m_sdGetStateIDRelpy.m_iStateID)
         {
            case 100:
               OnGetCandidateNo(l_WeiYaWebSocketMsg.WeiYaWebSocketData.ServerToClient.m_sdGetStateIDRelpy.m_State.m_iInt);
            break;
         }
      break;
      case wym_SetState:
      break;
      case wym_SetStateBack:
      break;
      case wym_UpdateEvent:
         switch(l_WeiYaWebSocketMsg.WeiYaWebSocketData.ServerToClient.m_iUpdateEventID)
         {
            case 222://** Start/Reset to Vote
               StartToVote();
               GetWeiyaWebSocketState(100);
            break;

            case 777://** Rewarded!
               RewardedEvent();
            break;

         };
      break;
      case wym_UpdateEventBack:
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

void WeiyaWebSocket::SendVotedNumMsg(int _iNUm)
{
   TWeiYaWebSocketMsg l_WeiYaWebSocketMsg;
   l_WeiYaWebSocketMsg.WeiYaMsgType = wym_SetState;
   l_WeiYaWebSocketMsg.WeiYaWebSocketData.ClientToServer.m_sdSetState.m_iStateID = 1;
   l_WeiYaWebSocketMsg.WeiYaWebSocketData.ClientToServer.m_sdSetState.m_State.m_iInt = _iNUm;
   SendWeiyaWebSocketMesaage(l_WeiYaWebSocketMsg);

}
