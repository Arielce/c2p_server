#include "header.h"
#include "GameServer.h"
#include "CmdHandler.h"
#include "ClientHandler.h"
#include "DsHandler.h"
#include "PlayerMng.h"
#include "LobbyHandler.h"
#include "GateController.h"
#include "HeroMng.h"
#include "GoodsMng.h"
#include "DrawPrizeMng.h"

bool GameServer::Init(const char* pConfPath)
{
	if (!InitLog4cpp())
	{
		return false;
	}
	if (!InitServerConf(pConfPath))
	{
		TRACELOG("init server conf failed.");
		return false;
	}
	if (!InitServerApp())
	{
		TRACELOG("init server app failed.");
		return false;
	}
	if (!InitCmdListen())
	{
		TRACELOG("init cmd listen failed.");
		return false;
	}
	if (!InitDataServer())
	{
		TRACELOG("init data server failed.");
		return false;
	}
	if (!InitLobbyServer())
	{
		TRACELOG("init lobby server failed.");
		return false;
	}
	if (!InitTimerTrigger())
	{
		TRACELOG("init timer trigger failed.");
		return false;
	}
	if (!InitLoadConf())
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


bool GameServer::InitLog4cpp()
{
	PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("./log.properties"));
	Logger root = Logger::getRoot();

	return true;
}

bool GameServer::InitServerConf(const char* pConfPath)
{
	return gpServerConfig->LoadServerConf(pConfPath);
}

bool GameServer::InitServerApp()
{
	m_pNetCluster = CreateNetCluster();
	if (!m_pNetCluster)
	{
		return false;
	}
	m_pNetCluster->SetLogConf("./log.properties");
	if (!m_pNetCluster->Init())
	{
		return false;
	}

	m_pServerSession = m_pNetCluster->CreateServerSession();
	if (!m_pServerSession)
	{
		return false;
	}

	ClientHandler* clientHandler = new ClientHandler;
	ClientMsgParser* clientMsgParser = new ClientMsgParser;
	m_pServerSession->SetMsgParser(clientMsgParser);
	m_pServerSession->SetMsgHandler(clientHandler);
	m_pServerSession->SetBufSize(12, 4096);
	m_pServerSession->Listen(gpServerConfig->GetGsBindIp(), gpServerConfig->GetGsBindPort());
	return true;
}

bool GameServer::InitCmdListen()
{
	m_pCmdSession = m_pNetCluster->CreateServerSession();
	if (!m_pServerSession)
	{
		return false;
	}
	CmdHandler* pCmdHandler = new CmdHandler();
	pCmdHandler->SetGameServer(this);
	ClientMsgParser* pClientMsgParser = new ClientMsgParser();
	m_pCmdSession->SetMsgParser(pClientMsgParser);
	m_pCmdSession->SetMsgHandler(pCmdHandler);
	m_pCmdSession->SetBufSize(12, 4096);
	m_pCmdSession->Listen(gpServerConfig->GetCmdIp(), gpServerConfig->GetCmdPort());
	return true;
}

bool GameServer::InitDataServer()
{
	m_pDsSession = m_pNetCluster->CreateClientSession();
	if (!m_pDsSession)
	{
		return false;
	}

	DsHandler* pDsHandler = new DsHandler;
	ClientMsgParser* clientMsgParser = new ClientMsgParser;
	m_pDsSession->SetMsgParser(clientMsgParser);
	m_pDsSession->SetMsgHandler(pDsHandler);
	m_pDsSession->SetBufSize(12, 4096);

	m_pDsSession->Connect(gpServerConfig->GetDsIp(), gpServerConfig->GetDsPort());
	g_pDsSession = m_pDsSession;
	return true;
}

bool GameServer::InitLobbyServer()
{
	m_pLobbySession = m_pNetCluster->CreateClientSession();
	if (!m_pLobbySession)
	{
		return false;
	}

	LobbyHandler* pLobbyHandler = new LobbyHandler;
	ClientMsgParser* clientMsgParser = new ClientMsgParser;
	m_pLobbySession->SetMsgParser(clientMsgParser);
	m_pLobbySession->SetMsgHandler(pLobbyHandler);
	m_pLobbySession->SetBufSize(12, 4096);

	m_pLobbySession->Connect(gpServerConfig->GetLobbyIp(), gpServerConfig->GetLobbyPort());
	g_pLobbySession = m_pLobbySession;
	return true;
}

bool GameServer::InitTimerTrigger()
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

bool GameServer::InitLoadConf()
{
	if (!gpPlayerMng->LoadPlayerInitConf())				// InitPlayerData.xml
	{
		return false;
	}
	if (!gpPlayerMng->LoadPlayerLevelConf())			// PlayerLevel.xml
	{
		return false;
	}
	if (!gpGoodsMng->LoadGoodsConf())					// Goods.xml
	{
		return false;
	}
	if (!gpGoodsMng->LoadEquipCompound())				// EquipCompound.xml
	{
		return false;
	}
	if (!gpGateController->LoadBattleGateConf())		// BattleGate.xml
	{
		return false;
	}
	if (!gpGateController->LoadGatePrizePool())			// GatePrizePool.xml
	{
		return false;
	}
	if (!gpHeroMng->LoadHeroConf())						// Hero.xml
	{
		return false;
	}
	if (!gpHeroMng->LoadHeroUpgrade())					// HeroUpgrade.xml
	{
		return false;
	}
	if (!gpDrawPrizeMng->LoadDrawPrzieConf())			// DrawPrize.xml
	{
		return false;
	}

	return true;
}