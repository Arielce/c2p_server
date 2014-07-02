#include "LobbyHandler.h"
#include "ServerConfig.h"
#include "../protocol/LobbyProtocol.h"
#include "../protocol/LobbyProtocol.pb.h"
#include "../network/Utility.h"

void LobbyHandler::HandleConnect(IConnection* pConnection, const boost::system::error_code& error)
{
	cout << "connect LobbyServer success" << endl;
	//cout << pConnection->GetRemoteIp() << endl;
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
		cout << "error" << endl;
		cout << "error:" << boost::system::system_error(error).what() << endl;
	}
}

void LobbyHandler::HandleRecv(IConnection* pConn, const char* pBuf, uint32_t nLen)
{
	
}
 