#include "LoginAgentHandler.h"

#include "ServerConfig.h"
#include "header.h"
#include "../protocol/LobbyProtocol.h"
#include "../protocol/LobbyProtocol.pb.h"
#include "../protocol/LoginProtocol.h"
#include "../network/IConnection.h"
#include "../network/Utility.h"
#include "PlayerMng.h"

void LoginAgentHandler::HandleConnect(IConnection* pConnection)
{
	cout << "connect LoginServerAgent success" << endl;
}

void LoginAgentHandler::HandleDisconnect(IConnection* pConn, const BoostErrCode& error)
{
	cout << "LoginServerAgent disconnect " << endl;
}

void LoginAgentHandler::HandleWrite(const boost::system::error_code& error, size_t bytes_transferred) 
{
	if (error)
	{
		ERRORLOG("error");
		ERRORLOG("error:" << boost::system::system_error(error).what());
	}
}

void LoginAgentHandler::HandleRecv(IConnection* pConn, const char* pBuf, uint32_t uLen)
{
	if (!pBuf || !uLen)
	{
		return;
	}
	MessageHeader* pMsgHeader = (MessageHeader*)pBuf;
	if (!pMsgHeader)
	{
		return;
	}
	switch (pMsgHeader->uMsgCmd)
	{
	case ID_SACK_SRequestVerifyToken:
		{
			gpPlayerMng->ProcReq(pConn, pMsgHeader);
		}
		break;
	default:
		break;
	}
}
