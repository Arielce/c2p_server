#ifndef	GAMESERVER_HEROMNG_H
#define GAMESERVER_HEROMNG_H

#include "header.h"

typedef struct tagHeroRank
{
	uint32_t uRank;
	uint32_t uFragmentNum;
}HeroRank;

typedef struct tagHeroConf
{
	uint32_t uHeroId;
	uint32_t uInitRank;
	uint32_t uInitLevel;
}HeroConf;

typedef struct tagUpgradeEquip
{
	vector<uint32_t> equipList;
}UpgradeEquip;

typedef struct tagHeroUpgrades
{
	vector<uint32_t> upgradeList;
}HeroUpgrades;

class Player;
class HeroMng
{
public:
	static HeroMng* GetInstance()
	{
		static HeroMng instance;
		return &instance;
	}

	bool LoadHeroConf();
	bool LoadHeroUpgrade();

	bool GetHeroConf(uint32_t uHeroId, HeroConf& heroConf);						// ��ȡӢ������
	bool GetHeroUpgradeConf(uint32_t uHero, HeroUpgrades& heroUpgrade);			// Ӣ����������

	uint32_t GetExpNeed(uint32_t uOldLevel, uint32_t uNewLevel);				// ��ȡ�����ȼ�֮��ľ�������
	uint32_t GetNextLevelExp(uint32_t uCurLevel);								// ��ȡ�¸��ȼ���Ҫ�ľ���
	uint32_t GetFragmentNeed(uint32_t uOldRank, uint32_t uNewRank);				// ��ȡ����rank֮�����Ƭ����
	uint32_t GetNextRankFragment(uint32_t uCurRank);							// ��ȡ�¸�rank��Ҫ����Ƭ

	void AddHeroExp(uint32_t uExpAdd, uint32_t uCurLevel, uint32_t uCurExp, uint32_t& uNewLevel, uint32_t& uNewExp);		// ��Ӣ�����Ӿ���
	int32_t HeroDressEquip(Player* pPlayer, uint64_t uHeroUUID, uint32_t uEquipId);											// ��Ӣ�۴���װ��
	int32_t HeroUpgrade(Player* pPlayer, uint64_t uHeroUUID);																// Ӣ����Ʒ��

private:
	HeroMng();

private:
	map<uint32_t, uint32_t> m_heroRankMap;										// rank��Ӧ����Ƭ���ñ�
	map<uint32_t, uint32_t> m_heroExpMap;										// �ȼ���Ӧ��������ñ�
	map<uint32_t, HeroConf> m_heroConfMap;										// Ӣ��ID��Ӧ���Ե����ñ�
	map<uint32_t, UpgradeEquip> m_upgradeEquipMap;								// ����װ���б�
	map<uint32_t, HeroUpgrades> m_heroUpgradeMap;								// Ӣ�������б�
};

#define gpHeroMng HeroMng::GetInstance()

#endif