#include <iostream>
#include "header.h"
#include "LobbyServer.h"

using namespace std;
IConnection* g_pGsConnection = NULL;
Logger g_lobbyLog = Logger::getInstance(LOG4CPLUS_TEXT("ALL_MSGS"));
Logger g_clientLog = Logger::getInstance(LOG4CPLUS_TEXT("client"));

int main(int argc, char* argv[])
{
	LobbyServer lobbyServer;
	const char* pInitConfPath = "./lobby.xml";
	if (argc >= 2)
	{
		pInitConfPath = argv[1];		// ∂¡»°≈‰÷√
	}

	if (!lobbyServer.Init(pInitConfPath))
	{
		ERRORLOG("lobbyServer init failed.");
		return 1;
	}
	TRACE_CLIENT("test client");
	lobbyServer.Start();

	return 0;
}