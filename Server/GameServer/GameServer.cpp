#include "header.h"
#include "GameServer.h"
#include "CmdHandler.h"
#include "ClientHandler.h"
#include "DsHandler.h"
#include "LobbyHandler.h"
#include "ReloadConfigure.h"
#include "PlayerMng.h"
#include "LoginAgentHandler.h"

GameServer::~GameServer()
{
	// 清理内存
	if (m_pClientHandler)
		delete m_pClientHandler;
	if (m_pClientMsgParser)
		delete m_pClientMsgParser;
	if (m_pCmdHandler)
		delete m_pCmdHandler;
	if (m_pDsHandler)
		delete m_pDsHandler;
	if (m_pLobbyHandler)
		delete m_pLobbyHandler;
	if (m_pLoginHandler)
		delete m_pLoginHandler;
}


bool GameServer::Init(const char* pConfPath)
{
	if (!_InitHandlers())
	{
		return false;
	}
	if (!_InitLog4cpp())
	{
		return false;
	}
	if (!_InitServerConf(pConfPath))
	{
		TRACELOG("init server conf failed.");
		return false;
	}
	if (!_InitServerApp())
	{
		TRACELOG("init server app failed.");
		return false;
	}
	if (!_InitCmdListen())
	{
		TRACELOG("init cmd listen failed.");
		return false;
	}
	if (!_InitDataServer())
	{
		TRACELOG("init data server failed.");
		return false;
	}
	if (!_InitLobbyServer())
	{
		TRACELOG("init lobby server failed.");
		return false;
	}
	if (!_InitLoginServerAgent())
	{
		TRACELOG("init login server agent failed.");
		return false;
	}
	if (!_InitTimerTrigger())
	{
		TRACELOG("init timer trigger failed.");
		return false;
	}
	if (!_InitLoadConf())
	{
		return false;
	}
	return true;
}

void GameServer::Stop()
{
	// 停止gameserver网络接收
	m_pServerSession->Stop();

	// 将需要停止的模块在这里逐一停止
	gpPlayerMng->Stop();

	// 停止网络模块
	m_pNetCluster->Stop();
}

bool GameServer::_InitHandlers()
{
	m_pClientHandler = new ClientHandler();
	if (!m_pClientHandler)
	{
		return false;
	}

	m_pClientMsgParser = new ClientMsgParser();
	if (!m_pClientMsgParser)
	{
		return false;
	}

	m_pCmdHandler = new CmdHandler();
	if (!m_pCmdHandler)
	{
		return false;
	}

	m_pDsHandler = new DsHandler();
	if (!m_pDsHandler)
	{
		return false;
	}

	m_pLobbyHandler = new LobbyHandler();
	if (!m_pLobbyHandler)
	{
		return false;
	}

	m_pLoginHandler = new LoginAgentHandler();
	if (!m_pLoginHandler)
	{
		return false;
	}

	return true;
}

bool GameServer::_InitLog4cpp()
{
	PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("./log.properties"));
	Logger root = Logger::getRoot();

	return true;
}

bool GameServer::_InitServerConf(const char* pConfPath)
{
	return gpServerConfig->LoadServerConf(pConfPath);
}

bool GameServer::_InitServerApp()
{
	m_pNetCluster = CreateNetCluster();
	if (!m_pNetCluster)
	{
		return false;
	}
	//m_pNetCluster->SetLogConf("./log.properties");
	m_pNetCluster->SetNetThreadNum(4);
	if (!m_pNetCluster->Init())
	{
		return false;
	}

	m_pServerSession = m_pNetCluster->CreateServerSession();
	if (!m_pServerSession)
	{
		return false;
	}

	m_pServerSession->SetMsgParser(m_pClientMsgParser);
	m_pServerSession->SetMsgHandler(m_pClientHandler);
	m_pServerSession->SetBufSize(12, 40960);
	m_pServerSession->Listen(gpServerConfig->GetGsBindIp(), gpServerConfig->GetGsBindPort());
	return true;
}

bool GameServer::_InitCmdListen()
{
	m_pCmdSession = m_pNetCluster->CreateServerSession();
	if (!m_pServerSession)
	{
		return false;
	}

	m_pCmdHandler->SetGameServer(this);
	m_pCmdSession->SetMsgParser(m_pClientMsgParser);
	m_pCmdSession->SetMsgHandler(m_pCmdHandler);
	m_pCmdSession->SetBufSize(12, 40960);
	m_pCmdSession->Listen(gpServerConfig->GetCmdIp(), gpServerConfig->GetCmdPort());
	return true;
}

bool GameServer::_InitDataServer()
{
	m_pDsSession = m_pNetCluster->CreateClientSession();
	if (!m_pDsSession)
	{
		return false;
	}

	m_pDsSession->SetMsgParser(m_pClientMsgParser);
	m_pDsSession->SetMsgHandler(m_pDsHandler);
	m_pDsSession->SetBufSize(12, 40960);

	m_pDsSession->Connect(gpServerConfig->GetDsIp(), gpServerConfig->GetDsPort());
	g_pDsSession = m_pDsSession;
	return true;
}

bool GameServer::_InitLobbyServer()
{
	m_pLobbySession = m_pNetCluster->CreateClientSession();
	if (!m_pLobbySession)
	{
		return false;
	}

	m_pLobbySession->SetMsgParser(m_pClientMsgParser);
	m_pLobbySession->SetMsgHandler(m_pLobbyHandler);
	m_pLobbySession->SetBufSize(12, 40960);

	m_pLobbySession->Connect(gpServerConfig->GetLobbyIp(), gpServerConfig->GetLobbyPort());
	g_pLobbySession = m_pLobbySession;
	return true;
}

bool GameServer::_InitLoginServerAgent()
{
	m_pLoginAgentSession = m_pNetCluster->CreateClientSession();
	if (!m_pLoginAgentSession)
	{
		return false;
	}

	m_pLoginAgentSession->SetMsgParser(m_pClientMsgParser);
	m_pLoginAgentSession->SetMsgHandler(m_pLoginHandler);
	m_pLoginAgentSession->SetBufSize(12, 40960);

	m_pLoginAgentSession->Connect(gpServerConfig->GetLoginIp(), gpServerConfig->GetLoginPort());
	g_pLoginAgentSession = m_pLoginAgentSession;
	return true;
}

bool GameServer::_InitTimerTrigger()
{
	m_pTimerTrigger = m_pNetCluster->CreateTimerTrigger();
	if (!m_pTimerTrigger)
	{
		return false;
	}
	m_pTimerTrigger->AddCircleTimer(boost::bind(&PlayerMng::OnTimer, gpPlayerMng, _1), 10);
	m_pTimerTrigger->AddCircleTimer(boost::bind(&ServerStatus::StatusDump, &m_serverStatus), 60);
	return true;
}

bool GameServer::_InitLoadConf()
{
	ConfigureReloador reloador;
	if (!reloador.ReloadConf())
	{
		return false;
	}
	return true;
}