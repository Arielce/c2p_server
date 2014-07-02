#ifndef DATASERVER_DATASERVER_H
#define DATASERVER_DATASERVER_H

#include "ServerConfig.h"
#include "../network/INetCluster.h"
#include "../network/header.h"
#include "DataThread.h"

class GsHandler;
class GsMsgParser;
class DataServer
{
public:
	DataServer() : m_pServerSession(NULL), m_pNetCluster(NULL), m_pGsHandler(NULL), m_pGsMsgParser(NULL)
	{

	}

	~DataServer()
	{
		//if (m_pServerSession)
		//{
		//	delete m_pServerSession;
		//}
	}

	bool Init(const char* pConfPath);

	void Start()
	{
		m_pNetCluster->Run();
	}

	DataThread* GetDataThread(int nIndex)
	{
		return m_pDataThread[nIndex];
	}

private:
	bool InitLog4cpp();
	bool InitServerConf(const char* pConfPath);
	bool InitServerApp();
	bool InitDataThread();

private:
	IServerSession* m_pServerSession;
	INetCluster* m_pNetCluster;
	DataThread** m_pDataThread;
	boost::thread** m_pThread;
	GsHandler* m_pGsHandler;
	GsMsgParser* m_pGsMsgParser;
};

#endif