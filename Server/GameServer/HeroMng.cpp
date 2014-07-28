#include "HeroMng.h"
#include "Player.h"
#include "Hero.h"
#include "GoodsMng.h"
#include "../network/Utility.h"
#include "../protocol/ErrorCodes.h"
#include "../protocol/GameProtocol.pb.h"
#include "../protocol/GameProtocol.h"
#include "../protocol/ErrorCodes.h"
#include "../tinyxml/tinyxml.h"


HeroMng::HeroMng()
{

}

// ��ȡӢ��������Ϣ
bool HeroMng::LoadHeroConf()
{
	TiXmlDocument xmlDoc;
	if (!xmlDoc.LoadFile("./xml/Hero.xml"))
	{
		return false;
	}

	TiXmlElement* pRoot = xmlDoc.RootElement();
	if (!pRoot)
	{
		return false;
	}

	TiXmlElement* pHeroRank = pRoot->FirstChildElement("HeroRank");
	if (!pHeroRank)
	{
		return false;
	}

	TiXmlElement* pRank = pHeroRank->FirstChildElement("rank");
	while (pRank)
	{
		uint32_t uRank = boost::lexical_cast<uint32_t>(pRank->Attribute("Rank"));
		uint32_t uFragmentNum = boost::lexical_cast<uint32_t>(pRank->Attribute("FragmentNum"));
		m_heroRankMap.insert(make_pair(uRank, uFragmentNum));
		pRank = pRank->NextSiblingElement();
	}

	TiXmlElement* pHeroExp = pRoot->FirstChildElement("HeroExp");
	if (!pHeroExp)
	{
		return false;
	}
	TiXmlElement* pExp = pHeroExp->FirstChildElement("exp");
	while (pExp)
	{
		uint32_t uLevel = boost::lexical_cast<uint32_t>(pExp->Attribute("level"));
		uint32_t uExp = boost::lexical_cast<uint32_t>(pExp->Attribute("exp"));
		m_heroExpMap.insert(make_pair(uLevel, uExp));

		pExp = pExp->NextSiblingElement();
	}

	TiXmlElement* pHeroList = pRoot->FirstChildElement("Heros");
	if (!pHeroList)
	{
		return false;
	}
	TiXmlElement* pHero = pHeroList->FirstChildElement("Hero");
	while (pHero)
	{
		HeroConf heroConf;
		heroConf.uHeroId = boost::lexical_cast<uint32_t>(pHero->Attribute("Id"));
		heroConf.uInitRank = boost::lexical_cast<uint32_t>(pHero->Attribute("InitRank"));
		heroConf.uInitLevel = boost::lexical_cast<uint32_t>(pHero->Attribute("InitLevel"));
		m_heroConfMap.insert(make_pair(heroConf.uHeroId, heroConf));
		
		pHero = pHero->NextSiblingElement();
	}

	return true;
}

bool HeroMng::LoadHeroUpgrade()
{
	TiXmlDocument xmlDoc;
	if (!xmlDoc.LoadFile("./xml/HeroUpgrade.xml"))
	{
		return false;
	}

	TiXmlElement* pRoot = xmlDoc.RootElement();
	if (!pRoot)
	{
		return false;
	}


	// ��ȡ������Ҫ��װ���б�
	TiXmlElement* pUpgradeEquips = pRoot->FirstChildElement("UpgradeEquips");
	if (!pUpgradeEquips)
	{
		return false;
	}
	TiXmlElement* pEquips = pUpgradeEquips->FirstChildElement("upgrade");
	while (pEquips)
	{
		UpgradeEquip upgradeEquip;

		uint32_t uUpgradeId = boost::lexical_cast<uint32_t>(pEquips->Attribute("id"));
		string strEquips = pEquips->Attribute("equips");
		vector<string> equipVec;
		boost::split(equipVec, strEquips, boost::is_any_of(","));

		vector<string>::iterator equipIt = equipVec.begin();
		vector<string>::iterator equipItEnd = equipVec.end();
		for (; equipIt != equipItEnd; equipIt++)
		{
			// ȥ���ո�
			string& strTempPrizeInfo = *equipIt;
			strTempPrizeInfo.erase(strTempPrizeInfo.begin(), std::find_if(strTempPrizeInfo.begin(), strTempPrizeInfo.end(), std::not1(std::ptr_fun<int, int>(std::isspace)))); 

			upgradeEquip.equipList.push_back(boost::lexical_cast<uint32_t>(*equipIt));
		}

		m_upgradeEquipMap.insert(make_pair(uUpgradeId, upgradeEquip));
		pEquips = pEquips->NextSiblingElement();
	}

	// ��ȡӢ��������Ҫ��װ���б�
	TiXmlElement* pHeroUpgrades = pRoot->FirstChildElement("HeroUpgrade");
	if (!pHeroUpgrades)
	{
		return false;
	}

	TiXmlElement* pHero = pHeroUpgrades->FirstChildElement("hero");
	while (pHero)
	{
		HeroUpgrades heroUpgrades;

		uint32_t uHeroId = boost::lexical_cast<uint32_t>(pHero->Attribute("id"));
		string strUpgrades = pHero->Attribute("upgrades");
		vector<string> upgradeVec;
		boost::split(upgradeVec, strUpgrades, boost::is_any_of(","));

		vector<string>::iterator upgradeIt = upgradeVec.begin();
		vector<string>::iterator upgradeItEnd = upgradeVec.end();
		for (; upgradeIt != upgradeItEnd; upgradeIt++)
		{
			// ȥ���ո�
			string& strTempPrizeInfo = *upgradeIt;
			strTempPrizeInfo.erase(strTempPrizeInfo.begin(), std::find_if(strTempPrizeInfo.begin(), strTempPrizeInfo.end(), std::not1(std::ptr_fun<int, int>(std::isspace)))); 
			heroUpgrades.upgradeList.push_back(boost::lexical_cast<uint32_t>(*upgradeIt));
		}

		m_heroUpgradeMap.insert(make_pair(uHeroId, heroUpgrades));
		pHero = pHero->NextSiblingElement();
	}

	return true;
}

bool HeroMng::GetHeroConf(uint32_t uHeroId, HeroConf& heroConf)
{
	map<uint32_t, HeroConf>::iterator heroIt = m_heroConfMap.find(uHeroId);
	if (heroIt == m_heroConfMap.end())
	{
		ERRORLOG("cannot find hero configure, id=[" << uHeroId << "]");
		return false;
	}

	if (heroIt->second.uHeroId != uHeroId)				// ��һ�ζ��μ��
	{
		return false;
	}

 	heroConf = heroIt->second;
	return true;
}

bool HeroMng::GetHeroUpgradeConf(uint32_t uHero, HeroUpgrades& heroUpgrade)
{
	map<uint32_t, HeroUpgrades>::iterator upgradeIt = m_heroUpgradeMap.find(uHero);
	if (upgradeIt == m_heroUpgradeMap.end())
	{
		return false;
	}

	heroUpgrade = upgradeIt->second;
	return true;
}

uint32_t HeroMng::GetExpNeed(uint32_t uOldLevel, uint32_t uNewLevel)
{
	map<uint32_t, uint32_t>::iterator oldExpIt = m_heroExpMap.find(uOldLevel);
	map<uint32_t, uint32_t>::iterator newExpIt = m_heroExpMap.find(uNewLevel);
	if (oldExpIt == m_heroExpMap.end() || newExpIt == m_heroExpMap.end())				// �в����ڵĵȼ�
	{
		ERRORLOG("error level, oldlevel=[" << uOldLevel << "], newlevel=[" << uNewLevel << "]");
		return 0;
	}

	uint32_t uTotalExpNeed = 0;
	for (; oldExpIt != newExpIt; oldExpIt++)					// map�Ǻ��������������һ��Ԫ�ؾ������̽ڵ�
	{
		uTotalExpNeed += oldExpIt->second;
	}

	return uTotalExpNeed;
}

uint32_t HeroMng::GetNextLevelExp(uint32_t uCurLevel)
{
	return GetExpNeed(uCurLevel, uCurLevel+1);
}

uint32_t HeroMng::GetFragmentNeed(uint32_t uOldRank, uint32_t uNewRank)
{
	map<uint32_t, uint32_t>::iterator oldRankIt = m_heroRankMap.find(uOldRank);
	map<uint32_t, uint32_t>::iterator newRankIt = m_heroRankMap.find(uNewRank);
	if (oldRankIt == m_heroRankMap.end() || newRankIt == m_heroRankMap.end())
	{
		ERRORLOG("error rank, oldrank=[" << uOldRank << "], newrank=[" << uNewRank << "]");
		return 0;
	}

	uint32_t uTotalFragmentNeed = 0;
	for (; oldRankIt != newRankIt; oldRankIt++)
	{
		uTotalFragmentNeed += oldRankIt->second;
	}

	return uTotalFragmentNeed;
}

uint32_t HeroMng::GetNextRankFragment(uint32_t uCurRank)
{
	return GetFragmentNeed(uCurRank, uCurRank+1);
}


/*
	����˵��:
	uExpAdd		���ӵľ���		IN
	uCurLevel	��ҵ�ǰ�ȼ�		IN
	uCurExp		��ҵ�ǰ����		IN
	uNewLevel	����µĵȼ�		OUT
	uNewExp		����µľ���		OUT
*/
void HeroMng::AddHeroExp(uint32_t uExpAdd, uint32_t uCurLevel, uint32_t uCurExp, uint32_t& uNewLevel, uint32_t& uNewExp)
{
	map<uint32_t, uint32_t>::iterator curExpIt = m_heroExpMap.find(uCurLevel);
	if (curExpIt == m_heroExpMap.end())
	{
		ERRORLOG("cannot find player curlevel=[" << uCurLevel << "]");
		return;
	}

	uNewLevel = uCurLevel;

	uint32_t uExpNeed = curExpIt->second;
	while (uExpAdd + uCurExp >= uExpNeed)				// �����ܹ�����
	{
		uExpAdd -= (uExpNeed - uCurExp);				// �������
		uCurExp = 0;
		if (++curExpIt != m_heroExpMap.end())
		{
			uExpNeed = curExpIt->second;
		}
		else											// �Ѿ�����ߵȼ�
		{
			break;
		}
		++uNewLevel;									// �ȼ�����1��
	} 
	uCurExp += uExpAdd;
	uNewExp = uCurExp;

	return;
}

int32_t HeroMng::HeroDressEquip(Player* pPlayer, uint32_t uHeroID, uint32_t uEquipId)
{
	if (!pPlayer->HasGoods(uEquipId))
	{
		return ERROR_EQUIP_NOT_EXIST;
	}

	EquipProp equipProp;
	if (!gpGoodsMng->GetEquipProp(uEquipId, equipProp))
	{
		return ERROR_EQUIP_NOT_EXIST;
	}

	// ���Ӣ���Ƿ����
	Hero hero;
	if (!pPlayer->GetHero(uHeroID, hero))
	{
		return ERROR_HERO_NOT_EXIST;
	}

	if (hero.GetLevel() < equipProp.uLevelLimit)
	{
		return ERROR_HERO_LEVEL_NOT_ENOUGH;
	}

	// �������ȫ�����㣬��ô����Ʒ�Ӱ�����ɾ����Ӣ�۴���װ��
	pPlayer->DelGoods(uEquipId);
	hero.DressEquip(uEquipId);

	return ERROR_OP_SUCCESS;
}

int32_t HeroMng::HeroUpgrade(Player* pPlayer, uint32_t uHeroID)
{
	// ���Ӣ���Ƿ����
	Hero hero;
	if (!pPlayer->GetHero(uHeroID, hero))
	{
		return ERROR_HERO_NOT_EXIST;
	}

	// ���Ӣ�۵�ǰ����������Ҫ��װ���Ƿ���ȫ
	HeroUpgrades heroUpgrade;
	if (!GetHeroUpgradeConf(hero.GetHeroId(), heroUpgrade))
	{
		return ERROR_HERO_NOT_EXIST;
	}

	vector<uint32_t>::iterator upgradeEquipIt = heroUpgrade.upgradeList.begin();
	vector<uint32_t>::iterator upgradeEquipItEnd = heroUpgrade.upgradeList.end();
	for (; upgradeEquipIt != upgradeEquipItEnd; upgradeEquipIt++)
	{
		vector<Goods>::const_iterator heroEquipIt = hero.GetEquipList().begin();
		vector<Goods>::const_iterator heroEquipItEnd = hero.GetEquipList().end();
		bool bFind = false;
		for (; heroEquipIt != heroEquipItEnd; heroEquipIt++)
		{
			if (heroEquipIt->uId == *upgradeEquipIt)
			{
				bFind = true;
				break;
			}
		}
		if (!bFind)								// ��Ӣ��װ������û���Ҹ���Ҫ��װ����˵��װ������
		{
			return ERROR_EQUIP_NOT_ENOUGHT;
		}
	}

	return ERROR_OP_SUCCESS;
}