#include "DrawPrize.h"
#include "DrawPrizeMng.h"
#include "Player.h"
#include "../network/Utility.h"
#include "../protocol/ErrorCodes.h"

DrawPrize::DrawPrize() : m_eCostType(DRAW_INVALID_COST), m_uCostNum(0), m_uDrawTimes(0), m_uPoolId(0)
{

}

DrawPrize::~DrawPrize()
{

}

bool DrawPrize::IsCostEnough(Player* pPlayer)
{
	if (!pPlayer)
	{
		return false;
	}

	switch (m_eCostType)
	{
	case DRAW_COST_GOLD:				// 金币
		{
			if (pPlayer->GetGold() < m_uCostNum)
			{
				return false;
			}
			return true;
		}
		break;
	case DRAW_COST_DIAMOND:				// 钻石
		{
			if (pPlayer->GetDiamond() < m_uCostNum)
			{
				return false;
			}
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}

bool DrawPrize::TakePlayerCost(Player* pPlayer)
{
	if (!pPlayer)
	{
		return false;
	}

	switch (m_eCostType)
	{
	case DRAW_COST_GOLD:				// 金币
		{
			if (pPlayer->GetGold() < m_uCostNum)
			{
				return false;
			}
			pPlayer->SubGold(m_uCostNum);
			return true;
		}
		break;
	case DRAW_COST_DIAMOND:				// 钻石
		{
			if (pPlayer->GetDiamond() < m_uCostNum)
			{
				return false;
			}
			pPlayer->SubDiamond(m_uCostNum);
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}

bool DrawPrize::IsDrawMaxTimes(Player* pPlayer)
{
	return false;
}

bool DrawPrize::IsDeadline()
{
	return false;
}

void DrawPrize::SetCostType(EDrawCostType eCostType)
{
	m_eCostType = eCostType;
}
void DrawPrize::SetCostNum(uint32_t uCostNum)
{
	m_uCostNum = uCostNum;
}
void DrawPrize::SetDrawTimes(uint32_t uDrawTimes)
{
	m_uDrawTimes = uDrawTimes;
}
void DrawPrize::SetPoolId(uint32_t uPoolId)
{
	m_uPoolId = uPoolId;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GoldDrawPrize::GoldDrawPrize()
{

}

GoldDrawPrize::~GoldDrawPrize()
{

}


// 进行抽奖
int32_t GoldDrawPrize::Draw(Player* pPlayer, vector<Goods>& prizeVec)
{
	DrawPrizePool prizePool;
	if (!gpDrawPrizeMng->GetPrizePool(m_uPoolId, prizePool))
	{
		ERRORLOG("cannot find draw pool id=[" << m_uPoolId << "]");
		return ERROR_DRAW_CONF_NOT_EXIST;
	}

	// 检查抽奖需要的消耗是否足够
	if (!IsCostEnough(pPlayer))
	{
		return ERROR_DRAW_COST_NOT_ENOUGH;
	}

	// 将消耗拿走
	if (!TakePlayerCost(pPlayer))
	{
		return ERROR_DRAW_COST_NOT_ENOUGH;
	}

	for (uint32_t i=0; i<m_uDrawTimes; i++)
	{
		vector<DrawPrizePool::PrizeConf>::iterator prizeIt = prizePool.prizeVec.begin();
		vector<DrawPrizePool::PrizeConf>::iterator prizeItEnd = prizePool.prizeVec.end();
		uint32_t uRand = GenRandom(0, 100000);
		for (; prizeIt!=prizeItEnd; prizeIt++)
		{
			const DrawPrizePool::PrizeConf& prizeConf = *prizeIt;
			if (uRand > prizeConf.uProbability)			// 没有获到此奖品
			{
				continue;
			}

			// 获到了奖品
			Goods goods;
			goods.uId = prizeConf.uPrizeId;
			goods.uNum = prizeConf.uPrizeNum;
			prizeVec.push_back(goods);
			pPlayer->AddGoodsIntoBag(goods);
			break;
		}
	}

	return ERROR_OP_SUCCESS;
}