#ifndef GAMESERVER_CLIENTCONNECTION_H
#define GAMESERVER_CLIENTCONNECTION_H

#include "header.h"

/*
	ר������������Ҷ��������������ӵ���
*/

class Player;
class ClientConnectionMng
{
public:
	ClientConnectionMng();
	~ClientConnectionMng();

	bool IsConnectionUsed(const string& strPtName, IConnection* pClientConn);				// �жϴ������Ƿ��Ѿ����������ʹ�ù�
	void SetPlayerConnection(Player* pPlayer, IConnection* pClientConn);					// ������Һ����ӵĶ�Ӧ��ϵ
	void ClientDisconnect(IConnection* pClientConn);										// �пͻ������Ӷ˿�

private:
	map<string, IConnection*> m_playerToConnMap;					// ���pt��Ӧ��������
	map<IConnection*, string> m_connToPlayerMap;					// �������Ӷ�Ӧ���pt
};

#endif