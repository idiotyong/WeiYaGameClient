#ifndef WEBSOCKETAPI_H
#define WEBSOCKETAPI_H

struct TLoginData
{
   char  m_sUserID[128];
   char  m_sPassWord[128];
};

union TStateType
{
   int m_iInt;
   double m_dfDouble;
};

struct TStateData
{
   int m_iStateID;
   TStateType m_State;
};

union TClientToServer
{
   TLoginData LoginData;
   int m_iGetStateID;
   TStateData m_sdGetStateIDRelpy;
   TStateData m_sdSetState;
   int m_iSetStateIDRelpy;
   int m_iUpdateEventID;
   int m_iUpdateEventIDRelpy;
};

union TServerToClient
{
   int m_iLoginReply;
   int m_iGetStateID;
   TStateData m_sdGetStateIDRelpy;
   TStateData m_sdSetState;
   int m_iSetStateIDRelpy;
   int m_iUpdateEventID;
   int m_iUpdateEventIDRelpy;
};

union TWeiYaWebSocketData
{
   TClientToServer ClientToServer;
   TServerToClient ServerToClient;
};

enum TWeiYaMsgType
{
   wym_Hello = 0,       // C->S
   wym_ImHere,          // S->C
   wym_Login,           // C->S
   wym_LoginBack,       // S->C
   wym_GetState,        // Both
   wym_GetStateBack,    // Both
   wym_SetState,        // Both
   wym_SetStateBack,    // Both
   wym_UpdateEvent,     // Both
   wym_UpdateEventBack, // Both
};

struct TWeiYaWebSocketMsg
{
   TWeiYaMsgType WeiYaMsgType;
   bool  m_bWaitRelpy;
   TWeiYaWebSocketData WeiYaWebSocketData;
};

#endif // WEBSOCKETAPI_H
