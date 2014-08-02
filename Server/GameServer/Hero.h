#ifndef GAMESERVER_HERO_H
#define GAMESERVER_HERO_H

#include "header.h"
#include "Goods.h"

#include <vector>
using namespace std;

// Ӣ��������Ϣ
typedef struct tagHeroLineup
{
	uint32_t uLineupId;				// ����ID
	vector<uint32_t> heroList;		// ����Ӣ���б�
	tagHeroLineup() : uLineupId(0)
	{
	}

	void AddHero(uint32_t uHeroId)
	{
		if (heroList.size() > 5)	// �������������������
		{
			ERRORLOG("hero line up is larger than the max num");
			return;
		}
		heroList.push_back(uHeroId);
		return;
	}

	// �������ݵ�Ӣ���б�
	void SetHeroList(vector<uint32_t>& _heroList)
	{
		heroList = _heroList;
	}
}HeroLineup;


// Ӣ����Ϣ
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
	uint32_t m_uHeroId;			// Ӣ��ID
	uint32_t m_uLevel;			// Ӣ�۵ȼ�
	uint32_t m_uExp;			// Ӣ�۾���
	uint32_t m_uHeroRank;		// Ӣ��Ʒ��
	uint32_t m_uUpgradeLevel;	// Ӣ������Ʒ������
	uint32_t m_uFragmentNum;	// ���ʯ����
	vector<Goods> m_equipList;	// װ���б�
};

#endif