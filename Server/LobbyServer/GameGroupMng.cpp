#include "GameGroupMng.h"
#include "../network/IConnection.h"

GameGroupMng::GameGroupMng()
{

}

GameGroupMng::~GameGroupMng()
{
	m_groupMap.clear();
}

void GameGroupMng::GameServerDisconnect(IConnection* pGsConnection)
{
	map<IConnection*,int>::iterator connIt = m_groupConnMap.find(pGsConnection);
	if (connIt == m_groupConnMap.end())
	{
		return;
	}
	int nGroupId = connIt->second;
	m_groupConnMap.erase(connIt);
	m_groupMap.erase(nGroupId);

	return;
}

// gameserver注册
bool GameGroupMng::RegGameServer(IConnection* pGsConnection, int nGroupId)
{
	if (!pGsConnection)
	{
		return false;
	}
	map<int, GroupInfo>::iterator groupIt = m_groupMap.find(nGroupId);
	if (groupIt != m_groupMap.end())			// 已经存在
	{
		return false;
	}

	GroupInfo groupInfo(pGsConnection->GetRemoteIp(), pGsConnection->GetRemotePort());
	m_groupMap.insert(make_pair(nGroupId, groupInfo));
	m_groupConnMap.insert(make_pair(pGsConnection, nGroupId));

	return true;
}

// 获取gameserver区组列表
void GameGroupMng::GetGameGroups(vector<GroupInfo>& groupVec)
{
	map<int, GroupInfo>::iterator groupIt = m_groupMap.begin();
	map<int, GroupInfo>::iterator groupItEnd = m_groupMap.end();

	for (; groupIt!=groupItEnd; groupIt++)
	{
		groupVec.push_back(groupIt->second);
	}

	return;
}