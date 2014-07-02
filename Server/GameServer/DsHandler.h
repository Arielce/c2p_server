#ifndef GAMESERVER_DSHANDLER_H
#define GAMESERVER_DSHANDLER_H

#include "../network/header.h"
#include "../network/IMsgParser.h"
#include "../network/IConnection.h"
#include "../network/IMsgHandler.h"

#include "DataServerAgent.h"
#include "PlayerDataGetter.h"



/*
	�����DataServer���ص���Ϣ
*/
class DsHandler : public IMsgHandler
{
public:
	void HandleConnect(IConnection* pConnection, const boost::system::error_code& error);

	void HandleDisconnect(IConnection* pConn, const BoostErrCode& error);

	void HandleWrite(const boost::system::error_code& error, size_t bytes_transferred);

	void HandleRecv(IConnection* pConn, const char* pBuf, uint32_t uLen);

private:
	DataServerAgent* m_pAgent;
	PlayerDataGetter m_dataGetter;
};


#endif