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

	bool GetHeroConf(uint32_t uHeroId, HeroConf& heroConf);						// 获取英雄配置
	bool GetHeroUpgradeConf(uint32_t uHero, HeroUpgrades& heroUpgrade);			// 英雄升级配置

	uint32_t GetExpNeed(uint32_t uOldLevel, uint32_t uNewLevel);				// 获取两个等级之间的经验配置
	uint32_t GetNextLevelExp(uint32_t uCurLevel);								// 获取下个等级需要的经验
	uint32_t GetFragmentNeed(uint32_t uOldRank, uint32_t uNewRank);				// 获取两个rank之间的碎片需求
	uint32_t GetNextRankFragment(uint32_t uCurRank);							// 获取下个rank需要的碎片

	void AddHeroExp(uint32_t uExpAdd, uint32_t uCurLevel, uint32_t uCurExp, uint32_t& uNewLevel, uint32_t& uNewExp);		// 给英雄增加经验
	int32_t HeroDressEquip(Player* pPlayer, uint64_t uHeroUUID, uint32_t uEquipId);											// 给英雄穿戴装备
	int32_t HeroUpgrade(Player* pPlayer, uint64_t uHeroUUID);																// 英雄升品级

private:
	HeroMng();

private:
	map<uint32_t, uint32_t> m_heroRankMap;										// rank对应的碎片配置表
	map<uint32_t, uint32_t> m_heroExpMap;										// 等级对应经验的配置表
	map<uint32_t, HeroConf> m_heroConfMap;										// 英雄ID对应属性的配置表
	map<uint32_t, UpgradeEquip> m_upgradeEquipMap;								// 升级装备列表
	map<uint32_t, HeroUpgrades> m_heroUpgradeMap;								// 英雄升级列表
};

#define gpHeroMng HeroMng::GetInstance()

#endif