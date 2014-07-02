#include "GsHandler.h"
#include "PlayerDataMng.h"
#include "header.h"
#include "../protocol/DataServer.pb.h"
#include "../protocol/DataProtocol.h"
#include "DataServer.h"
#include "DataThread.h"
#include "GsConnectionMng.h"


GsHandler::GsHandler(DataServer* pDataServer) : m_pDataServer(pDataServer)
{

}

void GsHandler::HandleConnect(IConnection* pConn, const BoostErrCode& error)
{
	cout << "gs connect:" << pConn->GetRemoteIp() << ":" << pConn->GetRemotePort() << endl;
	TRACELOG("gs connect:" << pConn->GetRemoteIp() << ":" << pConn->GetRemotePort());
	//g_pGsConnection = pConn;
	gpGsConnMng->SetGsConnection(pConn);
}

void GsHandler::HandleDisconnect(IConnection* pConn, const BoostErrCode& error)
{
	cout << "gs " << pConn->GetRemoteIp() << ":" << pConn->GetRemotePort() << " disconnect" << endl;
	TRACELOG("gs " << pConn->GetRemoteIp() << ":" << pConn->GetRemotePort() << " disconnect");
	//g_pGsConnection = NULL;
	gpGsConnMng->SetGsConnection(NULL);
}

void GsHandler::HandleWrite(const boost::system::error_code& error, size_t bytes_transferred) 
{
	if (error)
	{
		cout << "error" << endl;
		cout << "error:" << boost::system::system_error(error).what() << endl;
	}
}

void GsHandler::HandleRecv(IConnection* pConn, const char* pBuf, uint32_t uLen)
{
	if (!pBuf || !uLen)
	{
		return;
	}

	MessageHeader* pMsgHeader = (MessageHeader*)pBuf;
	switch (pMsgHeader->uMsgCmd)
	{
	case ID_SREQ_SRequestCreateRole:				// 请求创建角色
		{
			_RequestCreateRole(pBuf, uLen);
		}
		break;
	case ID_SREQ_SRequestGetRoleData:				// 请求角色数据
		{
			_RequestGetRoleData(pBuf, uLen);
		}
		break;
	case ID_SREQ_SRequestSaveRoleData:				// 请求保存角色数据
		{
			_RequestSaveRoleData(pBuf, uLen);
		}
		break;
	case ID_SREQ_SRequestRoleDataVersion:
		{
			_RequestDataVersion(pBuf, uLen);
		}
		break;
	default:
		break;
	}
}

void GsHandler::_RequestCreateRole(const char* pBuf, uint32_t uLen)
{
	MessageHeader* pMsgHeader = (MessageHeader*)pBuf;
	gtod::SRequestCreateRole createRoleReq;
	createRoleReq.ParseFromString(GetProtoData(pMsgHeader));

	size_t nHashIndex = m_stringHasher(createRoleReq.ptname()) % gpServerConfig->GetThreadNum();
	DataThread* pThread = m_pDataServer->GetDataThread(nHashIndex);
	pThread->Push(pBuf, uLen);

	return;
}

void GsHandler::_RequestGetRoleData(const char* pBuf, uint32_t uLen)
{
	MessageHeader* pMsgHeader = (MessageHeader*)pBuf;

	gtod::SRequestRoleData roleDataReq;
	roleDataReq.ParseFromString(GetProtoData(pMsgHeader));

	size_t nHashIndex = m_stringHasher(roleDataReq.ptname()) % gpServerConfig->GetThreadNum();
	DataThread* pThread = m_pDataServer->GetDataThread(nHashIndex);
	pThread->Push(pBuf, uLen);

	return;
}

void GsHandler::_RequestSaveRoleData(const char* pBuf, uint32_t uLen)
{
	MessageHeader* pMsgHeader = (MessageHeader*)pBuf;

	gtod::SRequestSaveRoleData saveRoleData;
	saveRoleData.ParseFromString(GetProtoData(pMsgHeader));

	size_t nHashIndex = m_stringHasher(saveRoleData.ptname()) % gpServerConfig->GetThreadNum();
	DataThread* pThread = m_pDataServer->GetDataThread(nHashIndex);
	pThread->Push(pBuf, uLen);

	return;
}

void GsHandler::_RequestDataVersion(const char * pBuf, uint32_t uLen)
{
	MessageHeader* pMsgHeader = (MessageHeader*)pBuf;

	gtod::SRequestRoleDataVersion dataVersionReq;
	dataVersionReq.ParseFromString(GetProtoData(pMsgHeader));

	size_t nHashIndex = m_stringHasher(dataVersionReq.ptname()) % gpServerConfig->GetThreadNum();
	DataThread* pThread = m_pDataServer->GetDataThread(nHashIndex);
	pThread->Push(pBuf, uLen);

	return;
}