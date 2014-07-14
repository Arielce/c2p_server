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

// 玩家初始化配置数据
typedef struct tagPlayerInitData
{
	uint32_t uLevel;			// 等级
	uint32_t uExp;				// 经验
	uint32_t uAp;				// 体力
	uint32_t uGold;				// 金币
	uint32_t uDiamond;			// 钻石
	uint32_t uGateId;			// 初始关卡ID
	tagPlayerInitData() : uLevel(0), uExp(0), uAp(0), uGold(0), uDiamond(0), uGateId(0)
	{

	}
	vector<uint32_t> heroList;
}PlayerInitData;

// 玩家等级配置信息
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

	uint32_t GetOnlinePlayerNum();													// 获取在线人数

	void CreateRoleResult(const string& strPtName, int32_t nErrCode);
	void AddPlayerExp(uint32_t uExpAdd, uint32_t uCurLevel, uint32_t uCurExp, uint32_t& uNewLevel, uint32_t& uNewExp);		// 给玩家增加指定经验
	Player* CreatePlayer();															// 创建Player对象
	void ReleasePlayer(Player* pPlayer);											// 释放Player对象
	bool IsPlayerOnline(const string& strPtName);									// 判断玩家是否在线
	Player* GetPlayer(const string& strPtName);										// 通过角色名获取角色对象
	Player* GetPlayer(uint32_t nPlayerId);
	void GetPlayerData(IConnection* pConnection, const string& strPtName);			// 获取角色数据
	void AchievePlayerData(const roledata::PBRoleTotalInfo& roleData, const string& strDesc);				// 获取到了角色数据
	void ClientDisconnect(IConnection* pConnection);								// 有客户端断开连接

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

	Player* _InitPlayerInfo(string strPtName, IConnection* pConn);											// 初始化玩家在内存中的数据
	void _SaveOnlinePlayer(uint32_t uFlag=0);																// 保存在线玩家
	void _SendPlayerDataToClient(IConnection* pConn, const roledata::PBRoleTotalInfo& roleData);			// 将角色数据发送给客户端
	void _SaveRoleData(Player* pPlayer);																	// 保存玩家数据
	void _DeletePlayer(Player* pPlayer);
	void _SendVerifyToken(string strPtName, uint32_t uToken);

private:
	map<string, Player*> m_playerInfoMap;									// PTName对应内存对象
	map<uint32_t, Player*> m_playerIdMap;									// ID对应内存对象

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