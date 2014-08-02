#ifndef GAMESERVER_GAMESERVER_H
#define GAMESERVER_GAMESERVER_H

#include "ServerConfig.h"
#include "../network/INetCluster.h"
#include "../network/ITimerTrigger.h"
#include "ServerStatus.h"

class ClientHandler;
class ClientMsgParser;
class CmdHandler;
class DsHandler;
class LobbyHandler;
class LoginAgentHandler;

class GameServer
{
public:
	GameServer() : m_pServerSession(NULL), m_pDsSession(NULL), m_pLobbySession(NULL), m_pNetCluster(NULL), m_pTimerTrigger(NULL),
		m_pClientHandler(NULL), m_pClientMsgParser(NULL), m_pCmdHandler(NULL), m_pDsHandler(NULL), m_pLobbyHandler(NULL), m_pLoginHandler(NULL)
	{
		
	}

	~GameServer();

	bool Init(const char* pConfPath);

	void Start()
	{
		m_pNetCluster->Run();
	}
	void Stop();

private:
	bool _InitHandlers();
	bool _InitLog4cpp();								// 初始化log4cplus
	bool _InitServerConf(const char* pConfPath);		// 初始化gameserver系统配置

	bool _InitServerApp();								// 启动GameServer监听
	bool _InitCmdListen();								// 启动命令通道监听
	bool _InitDataServer();								// 连接DBServer
	bool _InitLobbyServer();							// 连接LobbyServer
	bool _InitLoginServerAgent();						// 连接LoginServerAgent 

	bool _InitTimerTrigger();							// 启动定时器模块
	bool _InitLoadConf();								// 初始化配置

private:
	IServerSession* m_pServerSession;					// GameServer和客户端直接交互的session
	IServerSession* m_pCmdSession;						// 和命令通道之间交互
	IClientSession* m_pDsSession;						// 和DataServer之间交互
	IClientSession* m_pLobbySession;					// 和LobbyServer之间交互
	IClientSession* m_pLoginAgentSession;				// 和LoginAgent之间交互

	INetCluster*	m_pNetCluster;
	ITimerTrigger*	m_pTimerTrigger;

	ServerStatus m_serverStatus;

private:
	// handler 对象
	ClientHandler* m_pClientHandler;					// 客户端处理类
	ClientMsgParser* m_pClientMsgParser;				// 消息解析处理类
	CmdHandler* m_pCmdHandler;							// 命令通过处理类
	DsHandler* m_pDsHandler;							// DataServer处理类
	LobbyHandler* m_pLobbyHandler;						// LobbyServer处理类
	LoginAgentHandler* m_pLoginHandler;					// LoginAgent处理类
};

#endif