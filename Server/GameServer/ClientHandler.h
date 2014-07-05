#ifndef GAMESERVER_CLIENTHANDLER_H
#define GAMESERVER_CLIENTHANDLER_H

#include "../network/header.h"
#include "../network/IMsgParser.h"
#include "../network/IConnection.h"
#include "../network/IMsgHandler.h"
using namespace cpnet;
/*
	负责处理消息包头和包体的数据解析
*/
class ClientMsgParser : public IMsgParser
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
	处理从客户端(玩家)发送过来的请求
*/
class ClientHandler : public IMsgHandler
{
public:
	void HandleConnect(IConnection* pConn);

	void HandleDisconnect(IConnection* pConn, const BoostErrCode& error);

	void HandleWrite(const boost::system::error_code& error, size_t bytes_transferred);

	void HandleRecv(IConnection* pConn, const char* pBuf, uint32_t uLen);

private:
	void _RequestGMCommand(IConnection* pConn, MessageHeader* pMsgHeader);
	void _RequestEnterGate(IConnection* pConn, MessageHeader* pMsgHeader);
	void _RequestFinishGate(IConnection* pConn, MessageHeader* pMsgHeader);
	void _RequestHeroDressEquip(IConnection* pConn, MessageHeader* pMsgHeader);
	void _RequestHeroUpgrade(IConnection* pConn, MessageHeader* pMsgHeader);
	void _RequestCompoundEquip(IConnection* pConn, MessageHeader* pMsgHeader);
	void _RequestDrawPrizeList(IConnection* pConn, MessageHeader* pMsgHeader);
	void _RequestDrawPrize(IConnection* pConn, MessageHeader* pMsgHeader);
};

#endif