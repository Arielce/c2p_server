#include "header.h"
#include "NetCluster.h"
#include "TimerTrigger.h"
#include "ClientSession.hpp"
#include "ServerSession.hpp"

Logger g_netLog;

namespace cpnet
{
	INetCluster* CreateNetCluster()
	{
		return NetCluster::GetInstance();
	}

	void NetCluster::SetNetThreadNum(uint32_t uThreadNum)
	{
		m_uThreadNum = uThreadNum;
	}

	IClientSession* NetCluster::CreateClientSession()
	{
		ClientSession::pointer pClientSession = ClientSession::Create(m_ioService, m_strand);
		return pClientSession;
	}

	IServerSession* NetCluster::CreateServerSession()
	{
		ServerSession::pointer pServerSession = ServerSession::Create(m_ioService, m_strand);
		return pServerSession;
	}

	ITimerTrigger* NetCluster::CreateTimerTrigger()
	{
		return new TimerTrigger(m_ioService, m_strand);
	}

	bool NetCluster::Init()
	{
		g_netLog = Logger::getInstance(LOG4CPLUS_TEXT("NETWORK"));
		return true;
	}

	void NetCluster::Run()
	{
		for (uint32_t i=0; i<m_uThreadNum; i++)
		{
			boost::thread* pThread = new boost::thread(boost::bind(&BoostIoService::run, &m_ioService));
		}
		m_ioService.run();
	}

	void NetCluster::Stop()
	{
		m_ioService.stop();
	}
}
