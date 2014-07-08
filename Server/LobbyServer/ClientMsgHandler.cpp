#include "ClientMsgHandler.h"
#include "../protocol/LobbyProtocol.h"
#include "../protocol/LobbyProtocol.pb.h"
#include "../protocol/GameProtocol.pb.h"
#include "../protocol/GameProtocol.h"
#include "GameGroupMng.h"

ClientMsgHandler::ClientMsgHandler() 
{

}

void ClientMsgHandler::SetGroupMng(GameGroupMng* pGroupMng)
{
	m_pGameGroupMng = pGroupMng;
}


void ClientMsgHandler::HandleConnect(IConnection* pConn)
{
	cout << "gs connect:" << pConn->GetRemoteIp() << ":" << pConn->GetRemotePort() << endl;
	TRACELOG("gs connect:" << pConn->GetRemoteIp() << ":" << pConn->GetRemotePort());
}

void ClientMsgHandler::HandleDisconnect(IConnection* pConn, const BoostErrCode& error)
{
	cout << "gs " << pConn->GetRemoteIp() << ":" << pConn->GetRemotePort() << " disconnect" << endl;
	TRACELOG("gs " << pConn->GetRemoteIp() << ":" << pConn->GetRemotePort() << " disconnect");
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
	case ID_REQ_RequestGameGroup:				// 请求游戏区组
		{
			_RequestGameGroup(pConn, pMsgHeader);
		}
		break;
	default:
		break;
	}
}

// 请求区组列表
void ClientMsgHandler::_RequestGameGroup(IConnection* pConn, MessageHeader* pMsgHeader)
{
	if (!pConn || !pMsgHeader)
	{
		return;
	}

	ctos::ResponseGameGroups gameGroupAck;
	vector<GroupInfo> groupVec;

	m_pGameGroupMng->GetGameGroups(groupVec);

	vector<GroupInfo>::iterator groupIt = groupVec.begin();
	vector<GroupInfo>::iterator groupItEnd = groupVec.end();
	for (; groupIt != groupItEnd; groupIt++)
	{
		const GroupInfo& groupInfo = *groupIt;
		ctos::PBGameGroup* pGameGroup = gameGroupAck.add_groups();
		pGameGroup->set_ip(groupInfo.strIp);
		pGameGroup->set_port(groupInfo.nPort);
	}

	string strMessage;
	BuildResponseProto<ctos::ResponseGameGroups>(gameGroupAck, strMessage, ID_ACK_Lobby_ResponseGameGroups);
	pConn->SendMsg(strMessage.c_str(), strMessage.size());

	return;
}
