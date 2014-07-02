#include "header.h"
#include "NetCluster.h"
#include "TimerTrigger.h"
#include "ClientSession.hpp"
#include "ServerSession.hpp"
#include "MessageThread.h"

Logger g_netLog;

namespace cpnet
{
	INetCluster* CreateNetCluster()
	{
		return NetCluster::GetInstance();
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
		return new TimerTrigger(m_ioService);
	}

	void NetCluster::SetLogConf(const char* pLogProp)
	{
		m_strLogProp = pLogProp;
	}

	bool NetCluster::Init()
	{
		PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(m_strLogProp.c_str()));
		Logger root = Logger::getRoot();

		g_netLog = Logger::getInstance(LOG4CPLUS_TEXT("NETWORK"));
		return true;
	}

	void NetCluster::Run()
	{
		for (uint32_t i=0; i<4; i++)
		{
			m_ioService.run();
		}
	}

	void NetCluster::Stop()
	{
		MessageThread::GetInstance()->Stop();		// 结束线程运行
		m_ioService.stop();
		if (m_pMsgThread)
		{
			delete m_pMsgThread;
		}
	}
}
