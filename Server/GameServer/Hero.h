#ifndef GAMESERVER_HERO_H
#define GAMESERVER_HERO_H

#include "header.h"
#include "Goods.h"

#include <vector>
using namespace std;

// 英雄阵容信息
typedef struct tagHeroLineup
{
	uint32_t uLineupId;				// 阵容ID
	vector<uint32_t> heroList;		// 阵容英雄列表
	tagHeroLineup() : uLineupId(0)
	{
	}

	void AddHero(uint32_t uHeroId)
	{
		if (heroList.size() > 5)	// 超过阵容人数最高上限
		{
			ERRORLOG("hero line up is larger than the max num");
			return;
		}
		heroList.push_back(uHeroId);
		return;
	}

	// 重设阵容的英雄列表
	void SetHeroList(vector<uint32_t>& _heroList)
	{
		heroList = _heroList;
	}
}HeroLineup;


// 英雄信息
class Hero
{
public:
	Hero() : m_uHeroId(0), m_uLevel(0), m_uExp(0), m_uHeroRank(0), m_uUpgradeLevel(0), m_uFragmentNum(0)
	{
	}

	inline uint32_t GetHeroId()
	{
		return m_uHeroId;
	}

	inline void SetHeroId(uint32_t uHeroId)
	{
		m_uHeroId = uHeroId;
	}

	inline uint32_t GetLevel()
	{
		return m_uLevel;
	}

	inline void SetLevel(uint32_t uLevel)
	{
		m_uLevel = uLevel;
	}

	inline uint32_t GetExp()
	{
		return m_uExp;
	}

	inline void SetExp(uint32_t uExp)
	{
		m_uExp = uExp;
	}

	inline uint32_t GetHeroRank()
	{
		return m_uHeroRank;
	}

	inline void SetHeroRank(uint32_t uHeroRank)
	{
		m_uHeroRank = uHeroRank;
	}

	inline uint32_t GetUpgradeLevel()
	{
		return m_uUpgradeLevel;
	}

	inline void SetUpgradeLevel(uint32_t uUpgradeLevel)
	{
		m_uUpgradeLevel = uUpgradeLevel;
	}

	inline uint32_t GetFragmentNum()
	{
		return m_uFragmentNum;
	}

	inline void SetFragmentNum(uint32_t uFragmentNum)
	{
		m_uFragmentNum = uFragmentNum;
	}

	inline const vector<Goods>& GetEquipList()
	{
		return m_equipList;
	}

	inline vector<Goods>& GetMutableEquipList()
	{
		return m_equipList;
	}

	void DressEquip(uint32_t uEquipId);

private:
	uint32_t m_uHeroId;			// 英雄ID
	uint32_t m_uLevel;			// 英雄等级
	uint32_t m_uExp;			// 英雄经验
	uint32_t m_uHeroRank;		// 英雄品级
	uint32_t m_uUpgradeLevel;	// 英雄提升品级次数
	uint32_t m_uFragmentNum;	// 灵魂石数量
	vector<Goods> m_equipList;	// 装备列表
};

#endif