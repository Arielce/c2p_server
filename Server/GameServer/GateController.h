#ifndef GAMESERVER_GATECONTROLLER_H
#define GAMESERVER_GATECONTROLLER_H

#include "header.h"
#include "Player.h"
#include "../network/header.h"


typedef struct tagGateRecord
{
	tagGateRecord() : uGateId(0)
	{

	}
	uint32_t uGateId;					// 关卡ID
	boost::timer::cpu_timer m_timer;			// 关卡进入时间
	vector<uint64_t> heroList;		// 英雄列表
}GateRecord;

// 关卡配置信息
typedef struct tagGateConf
{
	uint32_t uGateId;
	uint32_t uNextGateId;
	uint32_t uGateType;
	uint32_t uExpGet;
	uint32_t uHeroExpGet;
	uint32_t uApCost;
	uint32_t uTimeLimit;
	uint32_t uPrizePool;
	tagGateConf()
	{
		// POD data
		memset(this, 0, sizeof(*this));
	}
}GateConf;

enum EBattleResult
{
	BATTLE_FAILED = 0,				// 战斗失败
	BATTLE_ONE_STAR,				// 胜利，获得一颗星
	BATTLE_TOW_STAR,				// 胜利，获得两颗星
	BATTLE_THREE_STAR,				// 胜利，获得三颗星
};

enum EGateType
{
	NORMAL_GATE = 0,
	BOSS_GATE = 1,
};

#define MAX_GATE_PRIZE_PROB 10000
typedef struct tagGatePrizePool
{
	struct PrizeProp
	{
		uint32_t uPrizeId;		// 奖品ID
		uint32_t uProbability;	// 奖品触发概率
		PrizeProp() : uPrizeId(0), uProbability(0)
		{

		}
	};
	vector<PrizeProp> m_prizeList;
}GatePrizePool;

/*
	控制玩家的关卡逻辑
*/
class NormalGate;
class GateController
{
public:
	static GateController* GetInstance()
	{
		static GateController instance;
		return &instance;
	}

	~GateController();

	bool LoadBattleGateConf();
	bool LoadGatePrizePool();

	bool IsPrizePoolExist(uint32_t uPoolId);
	const GatePrizePool& GetGatePrizePool(uint32_t uPoolId);

	bool IsGateExist(uint32_t uGateId);
	bool GetGateConf(uint32_t uGateId, GateConf& gateConf);

	// 玩家请求进入某个关卡
	void EnterGate(Player* pPlayer, uint32_t uGateId, const vector<uint64_t>& heroList);	
	// 玩家通知关卡结束
	void FinishGate(Player* pPlayer, uint32_t uGateId, int32_t nResult);
	// 玩家请求扫荡关卡
	void SweepGate(Player* pPlayer, uint32_t uGateId);

private:
	GateController();
	NormalGate* m_pNormalGate;

	map<uint32_t, GateConf> m_gateGateConfMap;
	map<uint32_t, GatePrizePool> m_gatePrizePoolMap;
};
#define gpGateController GateController::GetInstance()

/*
	玩家进入关卡时的逻辑判断类
*/
class GateChecker
{
public:
	GateChecker();
	~GateChecker();

	// 判断关卡是否合法
	bool IsGateValid(Player* pPlayer, uint32_t uGateId);
	// 判断关卡中的英雄是否合法
	bool IsHerosValid(Player* pPlayer, const vector<uint64_t>& heroList);
	// 玩家进入关卡
	void EnterGate(Player* pPlayer, uint32_t uGateId, const vector<uint64_t>& heroList);
	// 玩家是否有进入关卡记录
	bool HasGateRecord(Player* pPlayer, uint32_t uGateId);
	const vector<uint64_t>& GetHeroList(Player* pPlayer);
private:
	
	void _RecordEnterGate(Player* pPlayer, uint32_t uGateId, const vector<uint64_t>& heroList);

private:
	map<string, GateRecord> m_enterRecordMap;							// 玩家进入关卡的记录，使用角色名，玩家可能进入关卡之后，很长时间才完成关卡
};


/*
	玩家完成关卡是的控制类
*/
class GateAchieve
{
public:
	GateAchieve();
	~GateAchieve();

	// 判断是否合法完成了关卡
	bool IsAchieveValid(Player* pPlayer, uint32_t uGateId, int32_t nResult);
	// 给予玩家奖励
	void GivePrize(Player* pPlayer, uint32_t uGateId, int32_t nResult, const vector<uint64_t>& heroList);
};

/*
	普通关卡
*/
class NormalGate
{
public:
	NormalGate();
	~NormalGate();

	// 玩家请求进入某个关卡
	void EnterGate(Player* pPlayer, uint32_t uGateId, const vector<uint64_t>& heroList);	
	// 玩家通知关卡结束
	void FinishGate(Player* pPlayer, uint32_t uGateId, int32_t nResult);

private:
	GateChecker m_gateChecker;
	GateAchieve m_gateAchieve;
};

#endif