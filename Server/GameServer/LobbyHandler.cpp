#include "LobbyHandler.h"
#include "ServerConfig.h"
#include "header.h"
#include "../protocol/LobbyProtocol.h"
#include "../protocol/LobbyProtocol.pb.h"
#include "../network/Utility.h"

void LobbyHandler::HandleConnect(IConnection* pConnection)
{
	cout << "connect LobbyServer success" << endl;
	lobby::RequestRegGameServer gameSeverReg;
	gameSeverReg.set_gsid(gpServerConfig->GetServerId());

	string strMessage;
	BuildRequestProto<lobby::RequestRegGameServer>(gameSeverReg, strMessage, ID_SREQ_SRequestGsReg);
	pConnection->SendMsg(strMessage.c_str(), strMessage.size());
}

void LobbyHandler::HandleDisconnect(IConnection* pConn, const BoostErrCode& error)
{
	cout << "LobbyServer disconnect " << endl;
}

void LobbyHandler::HandleWrite(const boost::system::error_code& error, size_t bytes_transferred) 
{
	if (error)
	{
		ERRORLOG("error");
		ERRORLOG("error:" << boost::system::system_error(error).what());
	}
}

void LobbyHandler::HandleRecv(IConnection* pConn, const char* pBuf, uint32_t uLen)
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
	case ID_SACK_SResponseGsReg:
		{
			lobby::ResponseRegGameServer regGameServerAck;
			regGameServerAck.ParseFromString(GetProtoData(pMsgHeader));
			TRACELOG("register gameserver to lobbyserver, errorCode=[" << regGameServerAck.errcode() << "]");
		}
		break;
	default:
		break;
	}
}
 