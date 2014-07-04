#ifndef DATASERVER_GSHANDLER_H
#define DATASERVER_GSHANDLER_H

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
class DataServer;
class GsHandler : public IMsgHandler
{
public:
	GsHandler(DataServer* pDataServer);
	void HandleConnect(IConnection* pConn);

	void HandleDisconnect(IConnection* pConn, const BoostErrCode& error);

	void HandleWrite(const boost::system::error_code& error, size_t bytes_transferred);

	void HandleRecv(IConnection* pConn, const char* pBuf, uint32_t uLen);

private:
	void _RequestCreateRole(const char* pBuf, uint32_t uLen);
	void _RequestGetRoleData(const char* pBuf, uint32_t uLen);
	void _RequestSaveRoleData(const char* pBuf, uint32_t uLen);
	void _RequestDataVersion(const char * pBuf, uint32_t uLen);

private:
	boost::hash<string> m_stringHasher;
	DataServer* m_pDataServer;
};

#endif