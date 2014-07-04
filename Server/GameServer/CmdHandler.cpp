#include "CmdHandler.h"
#include "../protocol/ServerCmd.pb.h"
#include "../network/Utility.h"
#include "../protocol/CmdProtocol.h"
#include "../protocol/ErrorCodes.h"
#include "GameServer.h"
#include "ReloadConfigure.h"

void CmdHandler::HandleConnect(IConnection* pConn)
{
	TRACELOG("command client " << pConn->GetRemoteIp() << " connect ");
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
	case ID_REQ_RequestStop:									// 请求停止服务器
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
	case ID_REQ_RequestReloadConf:								// 热加载配置
		{
			scmd::RequestReloadConf reloadConfReq;
			reloadConfReq.ParseFromString(GetProtoData(pMsgHeader));
		
			_ReloadConfigure(pConn, reloadConfReq.conffile());			// 重载配置文件
		}
		break;
	default:
		break;
	}
}

void CmdHandler::_ReloadConfigure(IConnection* pConn, const string& strFileName)
{
	scmd::ResponseReloadConf reloadConfAck;
	ConfigureReloador reloader;
	const char* pFileName = NULL;
	if (strFileName != "")
	{
		pFileName = strFileName.c_str();
	}
	
	reloadConfAck.set_errcode(ERROR_OP_SUCCESS);
	if (!reloader.ReloadConf(pFileName))
	{
		reloadConfAck.set_errcode(ERROR_RELOAD_CONFIGURE_FAIL);
	}

	string strMessage;
	BuildResponseProto<scmd::ResponseReloadConf>(reloadConfAck, strMessage, ID_REQ_RequestReloadConf);

	pConn->SendMsg(strMessage.c_str(), strMessage.size());
	return;
}