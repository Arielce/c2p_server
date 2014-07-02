#include <iostream>
#include "header.h"
#include "LobbyServer.h"


using namespace std;
IConnection* g_pGsConnection = NULL;

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
		cout << "lobbyServer init failed." << endl;
		return 1;
	}
	lobbyServer.Start();

	return 0;
}