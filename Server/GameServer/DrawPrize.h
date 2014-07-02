#ifndef GAMESERVER_DRAWPRIZE_H
#define GAMESERVER_DRAWPRIZE_H

#include "header.h"
#include "Goods.h"

enum EDrawType
{
	DRAW_INVALID = 0,				// �Ƿ�ֵ
	DRAW_GOLD_ONCE = 1,				// ���һ�γ齱
	DRAW_GOLD_TEN = 2,				// ���10�γ齱
	DRAW_DIAMOND_ONCE = 3,			// ��ʯһ�γ齱
	DRAW_DIAMOND_TEN = 4,			// ��ʯ10�γ齱
};

enum EDrawCostType
{
	DRAW_INVALID_COST = 0,			// �Ƿ�ֵ
	DRAW_COST_GOLD = 1,				// ���Ľ��
	DRAW_COST_DIAMOND = 2,			// ������ʯ
};

/*
	���ڳ齱��ģ�鹦�ܶ�ͨ���˻������ʵ��
*/
class Player;
class DrawPrize
{
public:
	DrawPrize();
	virtual ~DrawPrize();
	virtual bool IsCostEnough(Player* pPlayer);					// ��������Ƿ�
	virtual bool TakePlayerCost(Player* pPlayer);				// ���������Ҫ������ 
	virtual bool IsDrawMaxTimes(Player* pPlayer);				// �Ƿ��Ѿ��ﵽ���齱������
	virtual bool IsDeadline();									// �Ƿ��Ѿ��������ĳ齱ʱ����

	virtual int32_t Draw(Player* pPlayer, vector<Goods>& prizeVec) = 0;									// ���г齱

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


// ʹ�ý�ҳ齱
class GoldDrawPrize : public DrawPrize
{
public:
	GoldDrawPrize();
	virtual ~GoldDrawPrize();

	virtual int32_t Draw(Player* pPlayer, vector<Goods>& prizeVec);									// ���г齱	
};


#endif