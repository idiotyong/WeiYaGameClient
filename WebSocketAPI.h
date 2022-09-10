#ifndef WEBSOCKETAPI_H
#define WEBSOCKETAPI_H

struct TLoginData
{
   char  m_sUserID[128];
   char  m_sPassWord[128];
};

union TClientToServer
{
   TLoginData LoginData;
   int m_iGetStateID;
   int m_iGetStateIDRelpy;
   int m_iSetStateID;
   int m_iSetStateIDRelpy;
};

union TServerToClient
{
   int m_iLoginReply;
   int m_iGetStateID;
   int m_iGetStateIDRelpy;
   int m_iSetStateID;
   int m_iSetStateIDRelpy;
};

union TWeiYaWebSocketData
{
   TClientToServer ClientToServer;
   TServerToClient ServerToClient;
};

enum TWeiYaMsgType
{
   wym_Hello = 0,    // C->S
   wym_ImHere,       // S->C
   wym_Login,        // C->S
   wym_LoginBack,    // S->C
   wym_GetState,     // Both
   wym_GetStateBack, // Both
   wym_SetState,     // Both
   wym_SetStateBack, // Both
};

struct TWeiYaWebSocketMsg
{
   TWeiYaMsgType WeiYaMsgType;
   bool  m_bWaitRelpy;
   TWeiYaWebSocketData WeiYaWebSocketData;
};

#endif // WEBSOCKETAPI_H
