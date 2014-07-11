#ifndef GAMESERVER_LOGINAGENTHANDLER_H
#define GAMESERVER_LOGINAGENTHANDLER_H

#include "header.h"
#include "../network/IMsgHandler.h"

class LoginAgentHandler : public IMsgHandler
{
public:
public:
	void HandleConnect(IConnection* pConnection);

	void HandleDisconnect(IConnection* pConn, const BoostErrCode& error);

	void HandleWrite(const boost::system::error_code& error, size_t bytes_transferred);

	void HandleRecv(IConnection* pConn, const char* pBuf, uint32_t uLen);
};

#endif