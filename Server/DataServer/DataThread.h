#ifndef DATASERVER_WORKTHREAD_H
#define DATASERVER_WORKTHREAD_H

#include "../network/header.h"
#include "PlayerDataMng.h"
using namespace cpnet;

class DataThread
{
public:
	DataThread();

	void Push(const char* pBuf, int nLen);
	bool Init();
	void Run();

private:
	deque<string> m_msgQueue;
	boost::mutex m_mutex;
	boost::condition m_cond;
	PlayerDataMng m_playerDataMng;
};

#endif