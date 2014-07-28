#include "PrizeMng.h"
#include "Player.h"
#include "GoodsMng.h"
#include "PlayerMng.h"
#include "HeroMng.h"

PrizeMng::PrizeMng()
{

}

PrizeMng::~PrizeMng()
{

}

/*
	����ҽ��
*/
void PrizeMng::GiveGold(Player* pPlayer, uint32_t uGold)
{
	if (!pPlayer)
	{
		return;
	}

	pPlayer->AddGold(uGold);
	return;
}

/*
	����Ҿ���
*/
void PrizeMng::GiveExp(Player* pPlayer, uint32_t uExp)
{
	if (!pPlayer)
	{
		return;
	}

	uint32_t uNewLevel = pPlayer->GetLevel();
	uint32_t uNewExp = pPlayer->GetExp();

	// ��������µľ���͵ȼ�
	gpPlayerMng->AddPlayerExp(uExp, pPlayer->GetLevel(), pPlayer->GetExp(), uNewLevel, uNewExp);
	pPlayer->SetLevel(uNewLevel);
	pPlayer->SetExp(uNewExp);
	return;
}

/*
	�����Ӣ�����Ӿ���
*/
void PrizeMng::GiveHeroExp(Player* pPlayer, uint32_t uHeroId, uint32_t uHeroExp)
{
	if (!pPlayer)
	{
		return;
	}

	Hero hero;
	if (!pPlayer->GetHero(uHeroId, hero))
	{
		ERRORLOG("player name=[" << pPlayer->PtName() << "]cannot find hero id=[" << uHeroId << "] in goods map");
		return;
	}

	uint32_t uNewLevel = hero.GetLevel();
	uint32_t uNewExp = hero.GetExp();
	gpHeroMng->AddHeroExp(uHeroExp, hero.GetLevel(), hero.GetExp(), uNewLevel, uNewExp);
	hero.SetLevel(uNewLevel);
	hero.SetExp(uNewExp);

	return;
}

/*
	�������Ʒ(װ��)
*/
void PrizeMng::GiveGoods(Player* pPlayer, uint32_t uGoodsId, uint32_t uGoodsNum/* =1 */)
{
	if (!pPlayer)
	{
		return;
	}

	// �����Ʒ�Ƿ����
	if (!gpGoodsMng->IsGoodsExist(uGoodsId))
	{
		ERRORLOG("player name=[" << pPlayer->PtName() << "]cannot find goods id=[" << uGoodsId << "] in goods map");
		return;
	}

	Goods goods(uGoodsId, uGoodsNum);
	pPlayer->AddGoodsIntoBag(goods);
	return;
}

/*
	�����Ӣ��
*/
void PrizeMng::GiveHero(Player* pPlayer, uint32_t uHeroId)
{
	if (!pPlayer)
	{
		return;
	}

	// ����Ӣ���Ƿ����
	HeroConf heroConf;
	if (!gpHeroMng->GetHeroConf(uHeroId, heroConf))
	{
		ERRORLOG("player name=[" << pPlayer->PtName() << "]cannot find hero id=[" << uHeroId << "] in goods map");
		return;
	}

	pPlayer->AddHero(uHeroId);
	return;
}