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
	bool _InitLog4cpp();								// ��ʼ��log4cplus
	bool _InitServerConf(const char* pConfPath);		// ��ʼ��gameserverϵͳ����

	bool _InitServerApp();								// ����GameServer����
	bool _InitCmdListen();								// ��������ͨ������
	bool _InitDataServer();								// ����DBServer
	bool _InitLobbyServer();							// ����LobbyServer
	bool _InitLoginServerAgent();						// ����LoginServerAgent 

	bool _InitTimerTrigger();							// ������ʱ��ģ��
	bool _InitLoadConf();								// ��ʼ������

private:
	IServerSession* m_pServerSession;					// GameServer�Ϳͻ���ֱ�ӽ�����session
	IServerSession* m_pCmdSession;						// ������ͨ��֮�佻��
	IClientSession* m_pDsSession;						// ��DataServer֮�佻��
	IClientSession* m_pLobbySession;					// ��LobbyServer֮�佻��
	IClientSession* m_pLoginAgentSession;				// ��LoginAgent֮�佻��

	INetCluster*	m_pNetCluster;
	ITimerTrigger*	m_pTimerTrigger;

	ServerStatus m_serverStatus;

private:
	// handler ����
	ClientHandler* m_pClientHandler;					// �ͻ��˴�����
	ClientMsgParser* m_pClientMsgParser;				// ��Ϣ����������
	CmdHandler* m_pCmdHandler;							// ����ͨ��������
	DsHandler* m_pDsHandler;							// DataServer������
	LobbyHandler* m_pLobbyHandler;						// LobbyServer������
	LoginAgentHandler* m_pLoginHandler;					// LoginAgent������
};

#endif