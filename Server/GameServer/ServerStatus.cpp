#include "ServerStatus.h"
#include "PlayerMng.h"

void ServerStatus::StatusDump()
{
	TRACELOG("Server Status:");
	TRACELOG("Online Player Size=[" << gpPlayerMng->GetOnlinePlayerNum() << "]");
	TRACELOG("Server Status END!");
}