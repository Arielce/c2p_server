#include "ClientMsgHandler.h"
#include "../protocol/LobbyProtocol.h"
#include "../protocol/LobbyProtocol.pb.h"

ClientMsgHandler::ClientMsgHandler() 
{

}

void ClientMsgHandler::SetGroupMng(GameGroupMng* pGroupMng)
{
	m_pGameGroupMng = pGroupMng;
}


void ClientMsgHandler::HandleConnect(IConnection* pConn, const BoostErrCode& error)
{
	cout << "gs connect:" << pConn->GetRemoteIp() << ":" << pConn->GetRemotePort() << endl;
}

void ClientMsgHandler::HandleDisconnect(IConnection* pConn, const BoostErrCode& error)
{
	cout << "gs " << pConn->GetRemoteIp() << ":" << pConn->GetRemotePort() << " disconnect" << endl;
}

void ClientMsgHandler::HandleWrite(const boost::system::error_code& error, size_t bytes_transferred) 
{
	if (error)
	{
		cout << "error" << endl;
		cout << "error:" << boost::system::system_error(error).what() << endl;
	}
}

void ClientMsgHandler::HandleRecv(IConnection* pConn, const char* pBuf, uint32_t nLen)
{
	if (!pBuf || !nLen)
	{
		return;
	}

	MessageHeader* pMsgHeader = (MessageHeader*)pBuf;
	switch (pMsgHeader->uMsgCmd)
	{
	case ID_REQ_RequestGameGroup:
		{

		}
		break;
	default:
		break;
	}
}
