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
	uint32_t uGateId;					// �ؿ�ID
	boost::timer::cpu_timer m_timer;			// �ؿ�����ʱ��
	vector<uint64_t> heroList;		// Ӣ���б�
}GateRecord;

// �ؿ�������Ϣ
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
	BATTLE_FAILED = 0,				// ս��ʧ��
	BATTLE_ONE_STAR,				// ʤ�������һ����
	BATTLE_TOW_STAR,				// ʤ�������������
	BATTLE_THREE_STAR,				// ʤ�������������
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
		uint32_t uPrizeId;		// ��ƷID
		uint32_t uProbability;	// ��Ʒ��������
		PrizeProp() : uPrizeId(0), uProbability(0)
		{

		}
	};
	vector<PrizeProp> m_prizeList;
}GatePrizePool;

/*
	������ҵĹؿ��߼�
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

	// ����������ĳ���ؿ�
	void EnterGate(Player* pPlayer, uint32_t uGateId, const vector<uint64_t>& heroList);	
	// ���֪ͨ�ؿ�����
	void FinishGate(Player* pPlayer, uint32_t uGateId, int32_t nResult);
	// �������ɨ���ؿ�
	void SweepGate(Player* pPlayer, uint32_t uGateId);

private:
	GateController();
	NormalGate* m_pNormalGate;

	map<uint32_t, GateConf> m_gateGateConfMap;
	map<uint32_t, GatePrizePool> m_gatePrizePoolMap;
};
#define gpGateController GateController::GetInstance()

/*
	��ҽ���ؿ�ʱ���߼��ж���
*/
class GateChecker
{
public:
	GateChecker();
	~GateChecker();

	// �жϹؿ��Ƿ�Ϸ�
	bool IsGateValid(Player* pPlayer, uint32_t uGateId);
	// �жϹؿ��е�Ӣ���Ƿ�Ϸ�
	bool IsHerosValid(Player* pPlayer, const vector<uint64_t>& heroList);
	// ��ҽ���ؿ�
	void EnterGate(Player* pPlayer, uint32_t uGateId, const vector<uint64_t>& heroList);
	// ����Ƿ��н���ؿ���¼
	bool HasGateRecord(Player* pPlayer, uint32_t uGateId);
	const vector<uint64_t>& GetHeroList(Player* pPlayer);
private:
	
	void _RecordEnterGate(Player* pPlayer, uint32_t uGateId, const vector<uint64_t>& heroList);

private:
	map<string, GateRecord> m_enterRecordMap;							// ��ҽ���ؿ��ļ�¼��ʹ�ý�ɫ������ҿ��ܽ���ؿ�֮�󣬺ܳ�ʱ�����ɹؿ�
};


/*
	�����ɹؿ��ǵĿ�����
*/
class GateAchieve
{
public:
	GateAchieve();
	~GateAchieve();

	// �ж��Ƿ�Ϸ�����˹ؿ�
	bool IsAchieveValid(Player* pPlayer, uint32_t uGateId, int32_t nResult);
	// ������ҽ���
	void GivePrize(Player* pPlayer, uint32_t uGateId, int32_t nResult, const vector<uint64_t>& heroList);
};

/*
	��ͨ�ؿ�
*/
class NormalGate
{
public:
	NormalGate();
	~NormalGate();

	// ����������ĳ���ؿ�
	void EnterGate(Player* pPlayer, uint32_t uGateId, const vector<uint64_t>& heroList);	
	// ���֪ͨ�ؿ�����
	void FinishGate(Player* pPlayer, uint32_t uGateId, int32_t nResult);

private:
	GateChecker m_gateChecker;
	GateAchieve m_gateAchieve;
};

#endif