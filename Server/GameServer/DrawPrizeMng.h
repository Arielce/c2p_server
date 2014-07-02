#ifndef GAMESERVER_DRAWPRIZEMNG_H
#define GAMESERVER_DRAWPRIZEMNG_H

#include "header.h"
#include "DrawPrize.h"

typedef struct tagDrawPrizePool
{
	struct PrizeConf
	{
		uint32_t uPrizeId;
		uint32_t uPrizeNum;
		uint32_t uProbability;
		PrizeConf() : uPrizeId(0), uPrizeNum(0), uProbability(0) {}
	};

	vector<PrizeConf> prizeVec;
}DrawPrizePool;

typedef struct tagDrawConf
{
	EDrawType eDrawType;
	uint32_t uDrawId;
	EDrawCostType eCostType;
	uint32_t uCostNum;
	uint32_t uDrawTimes;
	int32_t nMaxDrawTimes;
	uint32_t uDeadline;
	uint32_t uPoolId;
}DrawConf;

class DrawPrizeMng
{
public:
	static DrawPrizeMng* GetInstance()
	{
		static DrawPrizeMng instance;
		return &instance;
	}

	~DrawPrizeMng();

	bool LoadDrawPrzieConf();
	bool GetDrawConf(uint32_t uDrawId, DrawConf& drawConf);
	bool GetPrizePool(uint32_t uPoolId, DrawPrizePool& prizePool);
	vector<uint32_t> GetDrawList();										// 获取能抽奖的列表

	void Draw(Player* pPlayer, uint32_t uDrawId);

private:
	DrawPrizeMng();

private:
	map<uint32_t, DrawPrizePool> m_drawPrizePoolMap;
	map<uint32_t, DrawConf> m_drawConfMap;
};

#define gpDrawPrizeMng DrawPrizeMng::GetInstance()

#endif