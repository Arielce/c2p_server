#ifndef LOBBYSERVER_GAMEGROUPMNG_H
#define LOBBYSERVER_GAMEGROUPMNG_H

#include "header.h"
using namespace cpnet;

typedef struct tagGroupInfo
{
	string strIp;
	int nPort;
	tagGroupInfo() : nPort(0)
	{

	}
	tagGroupInfo(const string& _strIp, int _nPort) : strIp(_strIp), nPort(_nPort)
	{

	}
}GroupInfo;

class GameGroupMng
{
public:
	GameGroupMng();
	~GameGroupMng();

	void GameServerDisconnect(IConnection* pGsConnection);
	bool RegGameServer(IConnection* pGsConnection, int nGroupId);
	void GetGameGroups(vector<GroupInfo>& groupVec);

private:
	map<int, GroupInfo> m_groupMap;
	map<IConnection*, int> m_groupConnMap;
};

#endif