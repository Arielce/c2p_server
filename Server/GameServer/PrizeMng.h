#ifndef GAMESERVER_PRIZEMNG_H
#define GAMESERVER_PRIZEMNG_H

#include "header.h"

/*
	���������Ϸ��������Ʒ���ţ���������
	����ͨ�ظ����Ľ������ţ��齱�Ľ�������
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

	void GiveGold(Player* pPlayer, uint32_t uGold);									// ����ҽ��
	void GiveExp(Player* pPlayer, uint32_t uExp);									// ����Ҿ���
	void GiveHeroExp(Player* pPlayer, uint32_t uHeroId, uint32_t uHeroExp);			// ��Ӣ�۾���
	void GiveGoods(Player* pPlayer, uint32_t uGoodsId, uint32_t uGoodsNum=1);		// �������Ʒ
	void GiveHero(Player* pPlayer, uint32_t uHeroId);								// �����Ӣ��

private:
	PrizeMng();
};

#define gpPrizeMng PrizeMng::GetInstance()

#endif