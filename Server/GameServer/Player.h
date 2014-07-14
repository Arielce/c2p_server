#ifndef GAMESERVER_PLAYER_H
#define GAMESERVER_PLAYER_H

#include "header.h"
#include "../protocol/RoleData.pb.h"
#include "../network/IConnection.h"
#include "Goods.h"
#include "Hero.h"
using namespace cpnet;

enum PLAYER_STATE 
{
	PLAYER_FETCHING_DATA = 1,	// ���ڻ�ȡ������
	PLAYER_ONLINE = 2,			// ����
	PLAYER_AFK = 3,				// ˯��
	PLAYER_OFFLINE = 4,			// ����
};

// �ؿ���Ϣ
typedef struct tagGateInfo
{
	uint32_t uGateId;
	uint32_t uGateStar;
	bool bHasFight;
	tagGateInfo() : uGateId(0), uGateStar(0), bHasFight(false)
	{

	}
}GateInfo;

typedef struct tagBattleInfo
{
	int uBattleId;
	tagBattleInfo() : uBattleId(0)
	{
	}
	vector<uint32_t> gateList;
}BattleInfo;

class Player
{
public:
	Player();
	~Player();

	PLAYER_STATE State();
	void SetPlayerState(PLAYER_STATE eState);
	void IncreaseVersion();									// ����������ݰ汾

	void SetPlayerActive();									// ������µĲ���
	uint32_t PlayerLeaveTimes();							// ����뿪ʱ��(û�в�����ʱ��)
	bool IsPlayerDataReady();								// ��������Ƿ��Ѿ�׼����

	IConnection* GetPlayerConnection();
	void SetPlayerConnection(IConnection* pConnection);
	void ClientDisconnect();								// ��ҶϿ�������

	void SerializeToPB(roledata::PBRoleTotalInfo& roleTotalInfo);
	void GetRoleTotalInfo(const roledata::PBRoleTotalInfo& roleTotalInfo);
	
	void SetHasVerifyFromServer();													// �����Ѿ��ӷ�����
	bool HasVerifyFromServer();														// �Ƿ��Ѿ���Server��֤��Token��
	bool HasVerified(IConnection* pConnection);										// �Ƿ��Ѿ���֤��
	void SetToken(uint32_t uToken);													// ����Token
	bool VerifyToken(uint32_t uToken);												// ��֤Token

	void SendMsg(const void* pData, uint32_t uLen);

public:
	// ��Ҽ������Բ���
	uint32_t GetPlayerID();
	const string& PtName();
	void SetPtName(const string& strPtName);
	const string& RoleName();
	void SetRoleName(const string& strRoleName);
	void AddGold(uint32_t uGold);									// ��������ӽ��
	void SubGold(uint32_t uSubGold);
	void AddDiamond(uint32_t uDiamond);								// �����������ʯ
	void SubDiamond(uint32_t uSubDiamond);
	void AddExp(uint32_t uExp);										// ��������Ӿ���
	uint32_t GetGold();												// ��ȡ��ҵ�ǰ���
	uint32_t GetDiamond();											// ��ȡ��ҵ�ǰ��ʯ
	uint32_t GetExp();												// ��ȡ��ҵ�ǰ���飨��Ӣ�۲�ͬ��
	void SetExp(uint32_t uExp);										// ������ҵ�ǰ���飨��Ӣ�۲�ͬ��
	uint32_t GetLevel();											// ��ȡ��ҵ�ǰ�ȼ�����Ӣ�۲�ͬ��
	void SetLevel(uint32_t uLevel);									// ������ҵ�ǰ�ȼ�����Ӣ�۲�ͬ��

public:
	// ��Ʒ��ز���
	void AddGoodsIntoBag(const Goods& goods);						// ����Ұ���������Ʒ
	bool HasGoods(uint32_t uGoodsId, uint32_t uGoodsNum=1);			// ����Ƿ���ĳ����Ʒ
	void DelGoods(uint32_t uGoodsId, uint32_t uGoodsNum=1);			// ɾ����Ұ�������Ʒ

public:
	// �ؿ���ز���
	bool CanEnterGate(uint32_t uGateId);							// ����Ƿ���Խ���ĳ�ؿ�
	void AddGatePass(uint32_t uGateId, uint32_t uGateStars);		// ������ͨ���ؿ���Ϣ

public:
	// Ӣ����ز���
	bool GetHero(uint64_t uHeroUUID, Hero& hero);					// ��ȡӢ����Ϣ
	void AddHero(uint32_t uHeroId, uint32_t uHeroRank=1, uint32_t uHeroLevel=1, uint32_t uHeroExp=0);
	bool HasHero(uint64_t uHeroUUID);								// �Ƿ���ĳ��Ӣ��

private:
	void _SetPlayerDataReady();

	void _InitPlayerData();											// ��ʼ���������
	void _InitPlayerHero();											// ��ʼ�����Ӣ������

	void _ParseRoleBaseInfo(const roledata::PBRoleBaseInfo& roleBaseInfo);					// ������һ�������
	void _ParseRoleBagInfo(const roledata::PBRoleBag& roleBag);								// ������Ұ�������
	void _SerializeRoleBaseInfo(roledata::PBRoleBaseInfo& roleBaseInfo);					// ���л���һ�������
	void _SerializeRoleBagInfo(roledata::PBRoleBag& roleBag);								// ���л���Ұ�����Ϣ

	void _AddNextGateAvailable(uint32_t nNextGateId);

private:
	PLAYER_STATE m_state;									// Ĭ��������״̬
	IConnection* m_pClientConn;								// �ͻ�������

	uint32_t m_uDataVersion;								// ������ݰ汾
	uint32_t m_uSecureToken;								// ��ȫToken�������ÿ��������������ʱ�򣬶���Ҫ��֤һ��token����ֹ�����ʹ��������ҵ����ݣ�
	bool m_bHasVerifyFromServer;							// �Ƿ��Ѿ���server��֤��Token
	bool m_bHasVerifyToken;									// �Ƿ��Ѿ���֤��token��ÿ�ζϿ����ӵ�ʱ����Ϊfalse
	uint32_t m_uID;											// ���ID
	string m_strRoleName;									// ��ɫ��
	string m_strPtName;										// �˺���
	uint32_t m_uLevel;										// �ȼ�
	uint32_t m_uExp;										// ����
	uint32_t m_uGold;										// ���
	uint32_t m_uDiamond;									// ��ʯ

	boost::timer::cpu_timer m_timer;						// ��¼��ҷǻ�Ծʱ����

	bool m_bDataReady;										// �����Ƿ��Ѿ�׼����

private:
	map<uint32_t, Goods> m_roleBagMap;						// ��Ұ�����Ϣ[��ƷID����Ʒ��Ϣ]
	map<uint64_t, Hero> m_roleHeroMap;						// ���Ӣ����Ϣ[Ӣ��UUID��Ӣ������]
	map<uint32_t, GateInfo> m_gateMap;						// ��ҹؿ���Ϣ[�ؿ�ID, �ؿ���Ϣ]
	map<uint32_t, BattleInfo> m_battleMap;					// ��Ҵ�ؿ���Ϣ[��ؿ�ID����ؿ���Ϣ]
};

#endif