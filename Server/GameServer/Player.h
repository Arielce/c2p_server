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
	PLAYER_FETCHING_DATA = 1,	// 正在获取数据中
	PLAYER_ONLINE = 2,			// 在线
	PLAYER_AFK = 3,				// 睡眠
	PLAYER_OFFLINE = 4,			// 离线
};

// 关卡信息
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
	void IncreaseVersion();									// 增加玩家数据版本

	void SetPlayerActive();									// 玩家有新的操作
	uint32_t PlayerLeaveTimes();							// 玩家离开时间(没有操作的时间)
	bool IsPlayerDataReady();								// 玩家数据是否已经准备好

	IConnection* GetPlayerConnection();
	void SetPlayerConnection(IConnection* pConnection);
	void ClientDisconnect();								// 玩家断开了连接

	void SerializeToPB(roledata::PBRoleTotalInfo& roleTotalInfo);
	void GetRoleTotalInfo(const roledata::PBRoleTotalInfo& roleTotalInfo);
	
	void SetHasVerifyFromServer();													// 设置已经从服务器
	bool HasVerifyFromServer();														// 是否已经从Server验证过Token了
	bool HasVerified(IConnection* pConnection);										// 是否已经验证过
	void SetToken(uint32_t uToken);													// 设置Token
	bool VerifyToken(uint32_t uToken);												// 验证Token

	void SendMsg(const void* pData, uint32_t uLen);

public:
	// 玩家级别属性操作
	uint32_t GetPlayerID();
	const string& PtName();
	void SetPtName(const string& strPtName);
	const string& RoleName();
	void SetRoleName(const string& strRoleName);
	void AddGold(uint32_t uGold);									// 给玩家增加金币
	void SubGold(uint32_t uSubGold);
	void AddDiamond(uint32_t uDiamond);								// 给玩家增加钻石
	void SubDiamond(uint32_t uSubDiamond);
	void AddExp(uint32_t uExp);										// 给玩家增加经验
	uint32_t GetGold();												// 获取玩家当前金币
	uint32_t GetDiamond();											// 获取玩家当前钻石
	uint32_t GetExp();												// 获取玩家当前经验（和英雄不同）
	void SetExp(uint32_t uExp);										// 设置玩家当前经验（和英雄不同）
	uint32_t GetLevel();											// 获取玩家当前等级（和英雄不同）
	void SetLevel(uint32_t uLevel);									// 设置玩家当前等级（和英雄不同）

public:
	// 物品相关操作
	void AddGoodsIntoBag(const Goods& goods);						// 向玩家包裹增加物品
	bool HasGoods(uint32_t uGoodsId, uint32_t uGoodsNum=1);			// 玩家是否有某件物品
	void DelGoods(uint32_t uGoodsId, uint32_t uGoodsNum=1);			// 删除玩家包裹中物品

public:
	// 关卡相关操作
	bool CanEnterGate(uint32_t uGateId);							// 玩家是否可以进入某关卡
	void AddGatePass(uint32_t uGateId, uint32_t uGateStars);		// 添加玩家通过关卡信息

public:
	// 英雄相关操作
	bool GetHero(uint64_t uHeroUUID, Hero& hero);					// 获取英雄信息
	void AddHero(uint32_t uHeroId, uint32_t uHeroRank=1, uint32_t uHeroLevel=1, uint32_t uHeroExp=0);
	bool HasHero(uint64_t uHeroUUID);								// 是否有某个英雄

private:
	void _SetPlayerDataReady();

	void _InitPlayerData();											// 初始化玩家数据
	void _InitPlayerHero();											// 初始化玩家英雄数据

	void _ParseRoleBaseInfo(const roledata::PBRoleBaseInfo& roleBaseInfo);					// 解析玩家基础数据
	void _ParseRoleBagInfo(const roledata::PBRoleBag& roleBag);								// 解析玩家包裹数据
	void _SerializeRoleBaseInfo(roledata::PBRoleBaseInfo& roleBaseInfo);					// 序列化玩家基础数据
	void _SerializeRoleBagInfo(roledata::PBRoleBag& roleBag);								// 序列化玩家包裹信息

	void _AddNextGateAvailable(uint32_t nNextGateId);

private:
	PLAYER_STATE m_state;									// 默认是离线状态
	IConnection* m_pClientConn;								// 客户端连接

	uint32_t m_uDataVersion;								// 玩家数据版本
	uint32_t m_uSecureToken;								// 安全Token（玩家在每次重连服务器的时候，都需要验证一次token，防止有玩家使用其他玩家的数据）
	bool m_bHasVerifyFromServer;							// 是否已经从server验证过Token
	bool m_bHasVerifyToken;									// 是否已经验证了token，每次断开连接的时候，置为false
	uint32_t m_uID;											// 玩家ID
	string m_strRoleName;									// 角色名
	string m_strPtName;										// 账号名
	uint32_t m_uLevel;										// 等级
	uint32_t m_uExp;										// 经验
	uint32_t m_uGold;										// 金币
	uint32_t m_uDiamond;									// 钻石

	boost::timer::cpu_timer m_timer;						// 记录玩家非活跃时间间隔

	bool m_bDataReady;										// 数据是否已经准备好

private:
	map<uint32_t, Goods> m_roleBagMap;						// 玩家包裹信息[物品ID，物品信息]
	map<uint64_t, Hero> m_roleHeroMap;						// 玩家英雄信息[英雄UUID，英雄属性]
	map<uint32_t, GateInfo> m_gateMap;						// 玩家关卡信息[关卡ID, 关卡信息]
	map<uint32_t, BattleInfo> m_battleMap;					// 玩家大关卡信息[大关卡ID，大关卡信息]
};

#endif