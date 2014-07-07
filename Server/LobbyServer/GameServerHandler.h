#ifndef LOBBYSERVER_GAMESERVERHANDLER_H
#define LOBBYSERVER_GAMESERVERHANDLER_H

#include "../network/Utility.h"
#include "../network/header.h"
#include "../network/IMsgParser.h"
#include "../network/IConnection.h"
#include "../network/IMsgHandler.h"
using namespace cpnet;
/*
	负责处理消息包头和包体的数据解析
*/
class GsMsgParser : public IMsgParser
{
public:
	virtual size_t CheckMsgHeader(void* pMsg, size_t nBytesTransfered)
	{
		uint16_t* pMsgSize = (uint16_t*)pMsg;
		uint32_t* pMagicCode = (uint32_t*)((char*)pMsg + 8);
		if (*pMagicCode != 0xA1B2C3D4)
		{
			return 0;
		}
		return *pMsgSize;
	}
	virtual size_t CheckMsgBody(void* pMsg, size_t nBytesTransfered)
	{
		uint16_t* pMsgSize = (uint16_t*)pMsg;
		if (*pMsgSize >= nBytesTransfered)
		{
			return *pMsgSize;
		}
		return 0;
	}
};

/*
	处理从GameServer发送过来的请求
*/
class LobbyServer;
class GameGroupMng;
class GameServerHandler : public IMsgHandler
{
public:
	GameServerHandler(LobbyServer* pDataServer);
	virtual ~GameServerHandler();

	void SetGroupMng(GameGroupMng* pGroupMng);

	void HandleConnect(IConnection* pConn);

	void HandleDisconnect(IConnection* pConn, const BoostErrCode& error);

	void HandleWrite(const boost::system::error_code& error, size_t bytes_transferred);

	void HandleRecv(IConnection* pConn, const char* pBuf, uint32_t nLen);

private:
	LobbyServer* m_pLobbyServer;
	GameGroupMng* m_pGameGroupMng;
};

#endif