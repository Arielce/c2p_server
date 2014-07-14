#ifndef GAMESERVER_PLAYERMNG_H
#define GAMESERVER_PLAYERMNG_H

#include "../network/IConnection.h"
#include "header.h"
#include "Player.h"
#include "PlayerDataGetter.h"
#include "../protocol/RoleData.pb.h"
#include "redis/redisclient.h"
#include "ClientConnectionMng.h"
using namespace cpnet;

// ��ҳ�ʼ����������
typedef struct tagPlayerInitData
{
	uint32_t uLevel;			// �ȼ�
	uint32_t uExp;				// ����
	uint32_t uAp;				// ����
	uint32_t uGold;				// ���
	uint32_t uDiamond;			// ��ʯ
	uint32_t uGateId;			// ��ʼ�ؿ�ID
	tagPlayerInitData() : uLevel(0), uExp(0), uAp(0), uGold(0), uDiamond(0), uGateId(0)
	{

	}
	vector<uint32_t> heroList;
}PlayerInitData;

// ��ҵȼ�������Ϣ
typedef struct tagPlayerLevelConf
{
	uint32_t uLevel;
	uint32_t uExpNeed;
	uint32_t uMaxAp;
	tagPlayerLevelConf() : uLevel(0), uExpNeed(0), uMaxAp(0)
	{

	}
}PlayerLevelConf;

class PlayerMng
{
public:
	static PlayerMng* GetInstance()
	{
		static PlayerMng instance;
		return &instance;
	}

	~PlayerMng();

	void OnTimer(const BoostErrCode& errCode);
	void Stop();
	void ProcReq(IConnection* pConn, MessageHeader* pMsgHeader);

	bool LoadPlayerInitConf();
	bool LoadPlayerLevelConf();

	uint32_t GetOnlinePlayerNum();													// ��ȡ��������

	void CreateRoleResult(const string& strPtName, int32_t nErrCode);
	void AddPlayerExp(uint32_t uExpAdd, uint32_t uCurLevel, uint32_t uCurExp, uint32_t& uNewLevel, uint32_t& uNewExp);		// ���������ָ������
	Player* CreatePlayer();															// ����Player����
	void ReleasePlayer(Player* pPlayer);											// �ͷ�Player����
	bool IsPlayerOnline(const string& strPtName);									// �ж�����Ƿ�����
	Player* GetPlayer(const string& strPtName);										// ͨ����ɫ����ȡ��ɫ����
	Player* GetPlayer(uint32_t nPlayerId);
	void GetPlayerData(IConnection* pConnection, const string& strPtName);			// ��ȡ��ɫ����
	void AchievePlayerData(const roledata::PBRoleTotalInfo& roleData, const string& strDesc);				// ��ȡ���˽�ɫ����
	void ClientDisconnect(IConnection* pConnection);								// �пͻ��˶Ͽ�����

	const PlayerInitData& GetPlayerInitData()
	{
		return m_playerInitData;
	}

private:
	void _RequestVerifyToken(IConnection* pConn, MessageHeader* pMsgHeader);
	void _RequestCreateRole(IConnection* pConn, MessageHeader* pMsgHeader);
	void _RequestRoleData(IConnection* pConn, MessageHeader* pMsgHeader);
	void _SResponseVerifyToken(IConnection* pConn, MessageHeader* pMsgHeader);

private:
	PlayerMng();

	Player* _InitPlayerInfo(string strPtName, IConnection* pConn);											// ��ʼ��������ڴ��е�����
	void _SaveOnlinePlayer(uint32_t uFlag=0);																// �����������
	void _SendPlayerDataToClient(IConnection* pConn, const roledata::PBRoleTotalInfo& roleData);			// ����ɫ���ݷ��͸��ͻ���
	void _SaveRoleData(Player* pPlayer);																	// �����������
	void _DeletePlayer(Player* pPlayer);
	void _SendVerifyToken(string strPtName, uint32_t uToken);

private:
	map<string, Player*> m_playerInfoMap;									// PTName��Ӧ�ڴ����
	map<uint32_t, Player*> m_playerIdMap;									// ID��Ӧ�ڴ����

#ifndef _MSC_VER
	redis::client* m_pRedisClient;
#endif

private:
	PlayerDataGetter m_playerDataGetter;
	PlayerInitData m_playerInitData;
	ClientConnectionMng m_clientConnMng;
	map<uint32_t, PlayerLevelConf> m_playerLevelMap;
};

#define gpPlayerMng PlayerMng::GetInstance()

#endif