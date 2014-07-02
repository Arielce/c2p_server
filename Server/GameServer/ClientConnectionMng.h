#ifndef GAMESERVER_CLIENTCONNECTION_H
#define GAMESERVER_CLIENTCONNECTION_H

#include "header.h"

/*
	专门用来管理玩家对象和玩家网络连接的类
*/

class Player;
class ClientConnectionMng
{
public:
	ClientConnectionMng();
	~ClientConnectionMng();

	bool IsConnectionUsed(const string& strPtName, IConnection* pClientConn);				// 判断此链接是否已经被其他玩家使用过
	void SetPlayerConnection(Player* pPlayer, IConnection* pClientConn);					// 设置玩家和链接的对应关系
	void ClientDisconnect(IConnection* pClientConn);										// 有客户端链接端开

private:
	map<string, IConnection*> m_playerToConnMap;					// 玩家pt对应网络链接
	map<IConnection*, string> m_connToPlayerMap;					// 网络链接对应玩家pt
};

#endif