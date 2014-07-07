#ifndef LOBBYSERVER_CLIENTMSGHANDLER_H
#define LOBBYSERVER_CLIENTMSGHANDLER_H

#include "../network/Utility.h"
#include "../network/header.h"
#include "../network/IMsgParser.h"
#include "../network/IConnection.h"
#include "../network/IMsgHandler.h"
using namespace cpnet;
/*
	�����GameServer���͹���������
*/
class GameGroupMng;
class ClientMsgHandler : public IMsgHandler
{
public:
	ClientMsgHandler();

	void SetGroupMng(GameGroupMng* pGroupMng);

	void HandleConnect(IConnection* pConn);

	void HandleDisconnect(IConnection* pConn, const BoostErrCode& error);

	void HandleWrite(const boost::system::error_code& error, size_t bytes_transferred);

	void HandleRecv(IConnection* pConn, const char* pBuf, uint32_t nLen);

private:
	void _RequestGameGroup(IConnection* pConn, MessageHeader* pMsgHeader);

private:
	GameGroupMng* m_pGameGroupMng;
};

#endif
