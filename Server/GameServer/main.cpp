#include <iostream>
#include "header.h"
#include "GameServer.h"
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;

Logger g_gsLog = Logger::getInstance(LOG4CPLUS_TEXT("ALL_MSGS"));
IClientSession* g_pDsSession = NULL;
IClientSession* g_pLobbySession = NULL;

int main(int argc, char* argv[])
{
	GameServer gameServer;
	const char* pInitConfPath = "./gs.xml";
	if (argc >= 2)
	{
		pInitConfPath = argv[1];		// ∂¡»°≈‰÷√
	}

	if (!gameServer.Init(pInitConfPath))
	{
		ERRORLOG("gameserver init failed.");
		return 1;
	}
	TRACELOG("SERVER Start");
	gameServer.Start();
	TRACELOG("SERVER Stop");

	return 0;
}