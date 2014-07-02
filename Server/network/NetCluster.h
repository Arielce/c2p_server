#ifndef NETWORK_NETCLUSTER_H
#define NETWORK_NETCLUSTER_H

#include "INetCluster.h"
#include "header.h"

namespace cpnet
{
	class NetCluster : public INetCluster
	{
	public:
		static NetCluster* GetInstance()
		{
			static NetCluster instance;
			return &instance;
		}
		~NetCluster()
		{
			m_ioService.stop();
		}

	private:
		NetCluster() : m_strand(m_ioService)
		{
		}

	public:
		virtual IClientSession* CreateClientSession();
		virtual IServerSession* CreateServerSession();
		virtual ITimerTrigger* CreateTimerTrigger();
		virtual void SetLogConf(const char* pLogProp);
		virtual bool Init();
		virtual void Run();
		virtual void Stop();

	private:
		BoostIoService m_ioService;
		BoostStrand m_strand;
		string m_strLogProp;
	};
}
#endif