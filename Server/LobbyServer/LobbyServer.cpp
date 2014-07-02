#include "LobbyServer.h"
#include "GameServerHandler.h"
#include "GameGroupMng.h"
#include "ClientMsgHandler.h"

bool LobbyServer::Init(const char* pConfPath)
{
	if (!InitLog4cpp())
	{
		return false;
	}
	if (!InitServerConf(pConfPath))
	{
		return false;
	}
	if (!InitServerApp())
	{
		return false;
	}
	return true;
}


bool LobbyServer::InitLog4cpp()
{
	//PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("./log.properties"));
	//Logger root = Logger::getRoot();

	return true;
}

bool LobbyServer::InitServerConf(const char* pConfPath)
{
	return gpServerConfig->LoadServerConf(pConfPath);
}

bool LobbyServer::InitServerApp()
{
	m_pNetCluster = CreateNetCluster();
	if (!m_pNetCluster)
	{
		return false;
	}
	if (!m_pNetCluster->Init())
	{
		return false;
	}
	m_pServerSession = m_pNetCluster->CreateServerSession();
	if (!m_pServerSession)
	{
		return false;
	}

	GameServerHandler* pGsHandler = new GameServerHandler(this);
	GsMsgParser* gsMsgParser = new GsMsgParser;
	GameGroupMng* pGameGroupMng = new GameGroupMng;
	pGsHandler->SetGroupMng(pGameGroupMng);
	m_pServerSession->SetMsgParser(gsMsgParser);
	m_pServerSession->SetMsgHandler(pGsHandler);	
	m_pServerSession->SetBufSize(12, 4096);

	m_pServerSession->Listen(gpServerConfig->GetBindIp(), gpServerConfig->GetListenPort());



	m_pClientSession = m_pNetCluster->CreateServerSession();
	if (!m_pClientSession)
	{
		return false;
	}

	ClientMsgHandler* pClientHandler = new ClientMsgHandler();
	pClientHandler->SetGroupMng(pGameGroupMng);
	m_pClientSession->SetMsgParser(gsMsgParser);
	m_pClientSession->SetMsgHandler(pClientHandler);	

	m_pClientSession->Listen(gpServerConfig->GetClientBindIp(), gpServerConfig->GetClientListenPort());

	return true;
}