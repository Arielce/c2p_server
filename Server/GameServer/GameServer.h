#ifndef GAMESERVER_GAMESERVER_H
#define GAMESERVER_GAMESERVER_H

#include "ServerConfig.h"
#include "../network/INetCluster.h"
#include "../network/ITimerTrigger.h"
#include "ServerStatus.h"

class GameServer
{
public:
	GameServer() : m_pServerSession(NULL), m_pDsSession(NULL), m_pLobbySession(NULL), m_pNetCluster(NULL), m_pTimerTrigger(NULL)
	{
		
	}

	bool Init(const char* pConfPath);

	void Start()
	{
		m_pNetCluster->Run();
	}
	void Stop();

private:
	bool InitLog4cpp();								// 初始化log4cplus
	bool InitServerConf(const char* pConfPath);		// 初始化gameserver系统配置

	bool InitServerApp();							// 启动GameServer监听
	bool InitCmdListen();							// 启动命令通道监听
	bool InitDataServer();							// 连接DBServer
	bool InitLobbyServer();							// 连接LobbyServer
	bool InitLoginServerAgent();					// 连接LoginServerAgent 

	bool InitTimerTrigger();						// 启动定时器模块
	bool InitLoadConf();							// 初始化配置

private:
	IServerSession* m_pServerSession;
	IServerSession* m_pCmdSession;
	IClientSession* m_pDsSession;
	IClientSession* m_pLobbySession;
	IClientSession* m_pLoginAgentSession;

	INetCluster*	m_pNetCluster;
	ITimerTrigger*	m_pTimerTrigger;

	ServerStatus m_serverStatus;
};

#endif