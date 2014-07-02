#include "CmdHandler.h"
#include "../protocol/ServerCmd.pb.h"
#include "../network/Utility.h"
#include "../protocol/CmdProtocol.h"
#include "GameServer.h"

void CmdHandler::HandleConnect(IConnection* pConn, const BoostErrCode& error)
{
	if (!error)
	{
		TRACELOG("command client " << pConn->GetRemoteIp() << " connect ");
	}
	else
	{
		TRACELOG("command client connect error, err=[" << error.message() << "]");
	}
}

void CmdHandler::HandleDisconnect(IConnection* pConn, const BoostErrCode& error)
{   
	TRACELOG("command client " << pConn->GetRemoteIp() << " disconnect ");
}

void CmdHandler::HandleWrite(const boost::system::error_code& error, size_t bytes_transferred) 
{
	if (error)
	{
		ERRORLOG("handle write error, error=[" << boost::system::system_error(error).what() << "]");
	}
}

void CmdHandler::HandleRecv(IConnection* pConn, const char* pBuf, uint32_t uLen)
{
	if (!pBuf || uLen == 0)
	{
		ERRORLOG("message error");
	}

	MessageHeader* pMsgHeader = (MessageHeader*)pBuf;
	switch (pMsgHeader->uMsgCmd)
	{
	case ID_REQ_RequestStop:
		{
			scmd::RequestStopServer stopServerReq;
			stopServerReq.ParseFromString(GetProtoData(pMsgHeader));

			if (m_pGameServer)
			{
				TRACELOG("gameserver recv command stop server, stop server start");
				m_pGameServer->Stop();
				TRACELOG("gameserver recv command stop server, stop server end");
			}
		}
		break;
	default:
		break;
	}
}

