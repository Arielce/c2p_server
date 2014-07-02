#include "ClientConnectionMng.h"
#include "Player.h"
#include "PlayerMng.h"

ClientConnectionMng::ClientConnectionMng()
{

}

ClientConnectionMng::~ClientConnectionMng()
{
	m_connToPlayerMap.clear();
	m_playerToConnMap.clear();
}

bool ClientConnectionMng::IsConnectionUsed(const string& strPtName, IConnection* pClientConn)
{
	map<IConnection*, string>::iterator connIt = m_connToPlayerMap.find(pClientConn);
	if (connIt == m_connToPlayerMap.end())
	{
		return false;
	}

	if (connIt->second != strPtName)			// ��ǰ��������Ѿ�ʹ�õĲ���ͬһ��
	{
		return true;
	}
	return false;
}

void ClientConnectionMng::SetPlayerConnection(Player* pPlayer, IConnection* pClientConn)
{
	if (!pPlayer || !pClientConn)
	{
		return;
	}

	m_playerToConnMap.insert(make_pair(pPlayer->PtName(), pClientConn));
	m_connToPlayerMap.insert(make_pair(pClientConn, pPlayer->PtName()));
	pPlayer->SetPlayerConnection(pClientConn);
	return;
}

void ClientConnectionMng::ClientDisconnect(IConnection* pClientConn)
{
	if (!pClientConn)
	{
		return;
	}

	map<IConnection*, string>::iterator connIt = m_connToPlayerMap.find(pClientConn);
	if (connIt == m_connToPlayerMap.end())
	{
		ERRORLOG("cannot find connection=[0x" << hex << pClientConn << "]");
		return;
	}

	Player* pPlayer = gpPlayerMng->GetPlayer(connIt->second);
	if (!pPlayer)
	{
		ERRORLOG("cannot find player ptname=[" << connIt->second << "]");
		return;
	}

	// ��մ�������ص�״̬
	pPlayer->ClientDisconnect();
	m_playerToConnMap.erase(connIt->second);
	m_connToPlayerMap.erase(connIt);
	return;
}