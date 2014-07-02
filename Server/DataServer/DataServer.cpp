#include "header.h"
#include "DataServer.h"
#include "GsHandler.h"
#include "PlayerDataMng.h"

bool DataServer::Init(const char* pConfPath)
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
	if (!InitDataThread())
	{
		return false;
	}
	return true;
}


bool DataServer::InitLog4cpp()
{
	PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("./log.properties"));
	Logger root = Logger::getRoot();
	return true;
}

bool DataServer::InitServerConf(const char* pConfPath)
{
	return gpServerConfig->LoadServerConf(pConfPath);
}

bool DataServer::InitServerApp()
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

	m_pGsHandler = new GsHandler(this);
	m_pGsMsgParser = new GsMsgParser;
	m_pServerSession->SetMsgHandler(m_pGsHandler);	
	m_pServerSession->SetMsgParser(m_pGsMsgParser);
	m_pServerSession->SetBufSize(12, 4096);

	m_pServerSession->Listen(gpServerConfig->GetBindIp(), gpServerConfig->GetListenPort());
	return true;
}

bool DataServer::InitDataThread()
{
	int nThreadNum = gpServerConfig->GetThreadNum();
	m_pDataThread = new DataThread*[nThreadNum];
	m_pThread = new boost::thread*[nThreadNum];
	for (int i=0; i<nThreadNum; i++)
	{
		m_pDataThread[i] = new DataThread;
		if (!m_pDataThread[i] || !m_pDataThread[i]->Init())
		{
			return false;
		}
		m_pThread[i] = new boost::thread(boost::bind(&DataThread::Run, m_pDataThread[i]));
		if (!m_pThread[i])
		{
			return false;
		}
	}
	return true;
}