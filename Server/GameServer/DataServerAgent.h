#ifndef GAMESERVER_DATASERVER_AGENT_H
#define GAMESERVER_DATASERVER_AGENT_H

#include "header.h"


class DataServerAgent
{
public:
	void SendToDataServer(const char* pBuf, uint32_t uLen);

	void PlayerDataBack(const char* pBuf, uint32_t uLen);
private:
	IClientSession* m_pDataServer;
};

#endif