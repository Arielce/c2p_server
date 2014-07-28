#ifndef GAMESERVER_PRIZEMNG_H
#define GAMESERVER_PRIZEMNG_H

#include "header.h"

/*
	负责管理游戏中所有物品发放，奖励发放
	包括通关副本的奖励发放，抽奖的奖励发放
*/

class Player;

class PrizeMng
{
public:
	static PrizeMng* GetInstance()
	{
		static PrizeMng instance;
		return &instance;
	}

	~PrizeMng();

	void GiveGold(Player* pPlayer, uint32_t uGold);									// 给玩家金币
	void GiveExp(Player* pPlayer, uint32_t uExp);									// 给玩家经验
	void GiveHeroExp(Player* pPlayer, uint32_t uHeroId, uint32_t uHeroExp);			// 给英雄经验
	void GiveGoods(Player* pPlayer, uint32_t uGoodsId, uint32_t uGoodsNum=1);		// 给玩家物品
	void GiveHero(Player* pPlayer, uint32_t uHeroId);								// 给玩家英雄

private:
	PrizeMng();
};

#define gpPrizeMng PrizeMng::GetInstance()

#endif