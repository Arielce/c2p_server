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
	bool InitLog4cpp();								// ��ʼ��log4cplus
	bool InitServerConf(const char* pConfPath);		// ��ʼ��gameserverϵͳ����

	bool InitServerApp();							// ����GameServer����
	bool InitCmdListen();							// ��������ͨ������
	bool InitDataServer();							// ����DBServer
	bool InitLobbyServer();							// ����LobbyServer
	bool InitLoginServerAgent();					// ����LoginServerAgent 

	bool InitTimerTrigger();						// ������ʱ��ģ��
	bool InitLoadConf();							// ��ʼ������

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