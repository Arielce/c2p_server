#ifndef GAMESERVER_DRAWPRIZE_H
#define GAMESERVER_DRAWPRIZE_H

#include "header.h"
#include "Goods.h"

enum EDrawType
{
	DRAW_INVALID = 0,				// 非法值
	DRAW_GOLD_ONCE = 1,				// 金币一次抽奖
	DRAW_GOLD_TEN = 2,				// 金币10次抽奖
	DRAW_DIAMOND_ONCE = 3,			// 钻石一次抽奖
	DRAW_DIAMOND_TEN = 4,			// 钻石10次抽奖
};

enum EDrawCostType
{
	DRAW_INVALID_COST = 0,			// 非法值
	DRAW_COST_GOLD = 1,				// 消耗金币
	DRAW_COST_DIAMOND = 2,			// 消耗钻石
};

/*
	关于抽奖的模块功能都通过此基类进行实现
*/
class Player;
class DrawPrize
{
public:
	DrawPrize();
	virtual ~DrawPrize();
	virtual bool IsCostEnough(Player* pPlayer);					// 检查消耗是否够
	virtual bool TakePlayerCost(Player* pPlayer);				// 拿走玩家需要的消耗 
	virtual bool IsDrawMaxTimes(Player* pPlayer);				// 是否已经达到最多抽奖次数了
	virtual bool IsDeadline();									// 是否已经超过最后的抽奖时间了

	virtual int32_t Draw(Player* pPlayer, vector<Goods>& prizeVec) = 0;									// 进行抽奖

	void SetCostType(EDrawCostType eCostType);
	void SetCostNum(uint32_t uCostNum);
	void SetDrawTimes(uint32_t uDrawTimes);
	void SetPoolId(uint32_t uPoolId);

protected:
	EDrawCostType m_eCostType;
	uint32_t m_uCostNum;
	uint32_t m_uDrawTimes;
	uint32_t m_uPoolId;
};


// 使用金币抽奖
class GoldDrawPrize : public DrawPrize
{
public:
	GoldDrawPrize();
	virtual ~GoldDrawPrize();

	virtual int32_t Draw(Player* pPlayer, vector<Goods>& prizeVec);									// 进行抽奖	
};


#endif