#include "DsHandler.h"
#include "../protocol/RoleData.pb.h"
#include "../protocol/DataServer.pb.h"
#include "../protocol/DataProtocol.h"
#include "../network/Utility.h"
#include "PlayerMng.h"


void DsHandler::HandleConnect(IConnection* pConnection, const boost::system::error_code& error)
{
	cout << "connect datasever success" << endl;
	TRACELOG("connect datasever success");
}

void DsHandler::HandleDisconnect(IConnection* pConn, const BoostErrCode& error)
{
	cout << "dataserver disconnect" << endl;
	TRACELOG("dataserver disconnect");
}

void DsHandler::HandleWrite(const boost::system::error_code& error, size_t bytes_transferred) 
{
	if (error)
	{
		TRACELOG("error:" << boost::system::system_error(error).what());
	}
}

void DsHandler::HandleRecv(IConnection* pConn, const char* pBuf, uint32_t uLen)
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
	case ID_SACK_SResponseCreateRole:
		{
			gtod::SResponseCreateRole sCreateRoleAck;
			sCreateRoleAck.ParseFromString(GetProtoData(pMsgHeader));
			gpPlayerMng->CreateRoleResult(sCreateRoleAck.ptname(), sCreateRoleAck.errcode());
		}
		break;
	case ID_SACK_SResponseGetRoleData:
		{
			gtod::SResponseRoleData roleDataResponse;
			roleDataResponse.ParseFromString(GetProtoData(pMsgHeader));
			m_dataGetter.DataBackFromDS(roleDataResponse.roledata());

#ifdef DEBUG_SERVER
			string strPrint;
			google::protobuf::TextFormat::PrintToString(roleDataResponse, &strPrint);
			TRACELOG("proto:" << endl << strPrint);
#endif
		}
		break;
	case ID_SACK_SResponseRoleDataVersion:
		{
			gtod::SResponseRoleDataVersion roleDataVersionAck;
			roleDataVersionAck.ParseFromString(GetProtoData(pMsgHeader));
			m_dataGetter.DataVersionBackFromDS(roleDataVersionAck);
		}
		break;
	default:
		break;
	}
}
