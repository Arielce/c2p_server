#include "GoodsMng.h"
#include "Player.h"
#include "../tinyxml/tinyxml.h"
#include "../protocol/ErrorCodes.h"

GoodsMng::GoodsMng()
{

}

bool GoodsMng::LoadGoodsConf()
{
	TiXmlDocument xmlDoc;
	if (!xmlDoc.LoadFile("./xml/Goods.xml"))
	{
		return false;
	}

	TiXmlElement* pRoot = xmlDoc.RootElement();
	if (!pRoot)
	{
		return false;
	}

	// 读取消耗类物品配置
	TiXmlElement* pHeroExpMedicine = pRoot->FirstChildElement("HeroExpMedicine");
	if (!pHeroExpMedicine)
	{
		return false;
	}
	TiXmlElement* pMedicine = pHeroExpMedicine->FirstChildElement("Goods");
	while (pMedicine)
	{
		uint32_t uGoodsId = boost::lexical_cast<uint32_t>(pMedicine->Attribute("id"));
		uint32_t uGoodsType = boost::lexical_cast<uint32_t>(pMedicine->Attribute("type"));
		uint32_t uGoodsValue = boost::lexical_cast<uint32_t>(pMedicine->Attribute("value"));
		
		m_totalMap.insert(make_pair(uGoodsId, true));
		if (uGoodsType == GOODS_HERO_EXP)
		{
			HeroExpMedicineProp heroExpProp;
			heroExpProp.uExpAdd = uGoodsValue;
			m_heroExpMedicineMap.insert(make_pair(uGoodsId, heroExpProp));
		}

		pMedicine = pMedicine->NextSiblingElement();
	}


	// 扫荡卷配置
	TiXmlElement* pSweepTicket = pRoot->FirstChildElement("SweepTicket");
	if (!pSweepTicket)
	{
		return false;
	}
	TiXmlElement* pTicket = pSweepTicket->FirstChildElement("ticket");
	while (pTicket)
	{
		uint32_t uTicketId = boost::lexical_cast<uint32_t>(pTicket->Attribute("id"));
		m_totalMap.insert(make_pair(uTicketId, true));

		pTicket = pTicket->NextSiblingElement();
	}

	// 合成卷轴配置
	TiXmlElement* pScrollBook = pRoot->FirstChildElement("ScrollBook");
	if (!pScrollBook)
	{
		return false;
	}
	TiXmlElement* pScroll = pScrollBook->FirstChildElement("scroll");
	while (pScroll)
	{
		uint32_t uScrollId = boost::lexical_cast<uint32_t>(pScroll->Attribute("id"));
		uint32_t uScrollType = boost::lexical_cast<uint32_t>(pScroll->Attribute("type"));
		m_totalMap.insert(make_pair(uScrollId, true));

		pScroll = pScroll->NextSiblingElement();
	}

	// 装备配置
	TiXmlElement* pEquips = pRoot->FirstChildElement("Equips");
	if (!pEquips)
	{
		return false;
	}
	TiXmlElement* pEquip = pEquips->FirstChildElement("Equip");
	while (pEquip)
	{
		EquipProp equipProp;
		uint32_t uEquipId		= boost::lexical_cast<uint32_t>(pEquip->Attribute("id"));
		uint32_t uEquipType		= boost::lexical_cast<uint32_t>(pEquip->Attribute("type"));
		equipProp.uLevelLimit	= boost::lexical_cast<uint32_t>(pEquip->Attribute("levelLimit"));
		equipProp.uStrength		= boost::lexical_cast<uint32_t>(pEquip->Attribute("strength"));
		equipProp.uIntelligence = boost::lexical_cast<uint32_t>(pEquip->Attribute("intelligence"));
		equipProp.uAgility		= boost::lexical_cast<uint32_t>(pEquip->Attribute("agility"));
		equipProp.uAttack		= boost::lexical_cast<uint32_t>(pEquip->Attribute("attack"));
		equipProp.uHP			= boost::lexical_cast<uint32_t>(pEquip->Attribute("hp"));	
		equipProp.uHPRecover	= boost::lexical_cast<uint32_t>(pEquip->Attribute("hpRecover"));	
		equipProp.uMPRecover	= boost::lexical_cast<uint32_t>(pEquip->Attribute("mpRecover"));

		m_totalMap.insert(make_pair(uEquipId, true));
		if (uEquipType == GOODS_EQUIP)
		{
			m_equipMap.insert(make_pair(uEquipId, equipProp));
		}

		pEquip = pEquip->NextSiblingElement();
	}

	return true;
}

bool GoodsMng::LoadEquipCompound()
{
	TiXmlDocument xmlDoc;
	if (!xmlDoc.LoadFile("./xml/EquipCompound.xml"))
	{
		return false;
	}

	TiXmlElement* pRoot = xmlDoc.RootElement();
	if (!pRoot)
	{
		return false;
	}

	// 读取消耗类物品配置
	TiXmlElement* pEquipCompound = pRoot->FirstChildElement("Equips");
	if (!pEquipCompound)
	{
		return false;
	}

	TiXmlElement* pCompound = pEquipCompound->FirstChildElement("Equip");
	while (pCompound)
	{
		CompoundConf compoundConf;
		compoundConf.uCompoundId = boost::lexical_cast<uint32_t>(pCompound->Attribute("id"));
		compoundConf.uGoldNeed = boost::lexical_cast<uint32_t>(pCompound->Attribute("goldNeed"));
		compoundConf.uScrollId = boost::lexical_cast<uint32_t>(pCompound->Attribute("srollId"));

		string strEquips = pCompound->Attribute("EquipList");

		vector<string> equipVec;
		boost::split(equipVec, strEquips, boost::is_any_of(","));

		vector<string>::iterator equipIt = equipVec.begin();
		vector<string>::iterator equipItEnd = equipVec.end();
		for (; equipIt != equipItEnd; equipIt++)
		{
			CompoundConf::EquipNeed equipNeed;
			string& strTempPrizeInfo = *equipIt;
			// 去除空格
			strTempPrizeInfo.erase(strTempPrizeInfo.begin(), std::find_if(strTempPrizeInfo.begin(), strTempPrizeInfo.end(), std::not1(std::ptr_fun<int, int>(std::isspace)))); 

			size_t uIndex = (*equipIt).find(':');
			if (uIndex == string::npos)					// 没有冒号，说明100%掉落
			{
				equipNeed.uEquipNum = 1;
				equipNeed.uEquipId = boost::lexical_cast<uint32_t>(*equipIt);
			}
			else
			{
				string strEquipNum = (*equipIt).substr(uIndex + 1);
				string strEquipId = (*equipIt).substr(0, uIndex);
				equipNeed.uEquipNum = boost::lexical_cast<uint32_t>(strEquipNum);
				equipNeed.uEquipId = boost::lexical_cast<uint32_t>(strEquipId);
			}
			compoundConf.equipNeedVec.push_back(equipNeed);
		}

		m_compoundEquipMap.insert(make_pair(compoundConf.uCompoundId, compoundConf));
		pCompound = pCompound->NextSiblingElement();
	}

	return true;
}

bool GoodsMng::GetEquipProp(uint32_t uEquipId, EquipProp& equipProp)
{
	map<uint32_t, EquipProp>::iterator equipIt = m_equipMap.find(uEquipId);
	if (equipIt == m_equipMap.end())
	{
		return false;
	}

	equipProp = equipIt->second;
	return true;
}

bool GoodsMng::IsGoodsExist(uint32_t uGoodsId)
{
	map<uint32_t, bool>::iterator findGoodsIt = m_totalMap.find(uGoodsId);
	if (findGoodsIt == m_totalMap.end())
	{
		return false;
	}
	return true;
}

int32_t GoodsMng::CompoundEquip(Player* pPlayer, uint32_t uTargetEquipId)
{
	if (!pPlayer)
	{
		return ERROR_PLAYER_NOT_FOUND;
	}

	map<uint32_t, CompoundConf>::iterator compoundIt = m_compoundEquipMap.find(uTargetEquipId);
	if (compoundIt == m_compoundEquipMap.end())
	{
		return ERROR_COMPOUND_TARGET_NOT_EXIST;
	}

	const CompoundConf& compoundConf = compoundIt->second;

	// 检查玩家金币是否足够
	if (pPlayer->GetGold() < compoundConf.uGoldNeed)
	{
		return ERROR_GOLD_NOT_ENOUGH;
	}

	// 检查制作书是否存在
	if (!pPlayer->HasGoods(compoundConf.uScrollId))
	{
		return ERROR_EQUIP_NOT_EXIST;
	}

	// 依次检查所有合成需要的装备是否存在
	vector<CompoundConf::EquipNeed>::const_iterator equipIt = compoundConf.equipNeedVec.begin();
	vector<CompoundConf::EquipNeed>::const_iterator equipItEnd = compoundConf.equipNeedVec.end();
	for (; equipIt != equipItEnd; equipIt++)
	{
		const CompoundConf::EquipNeed& equipNeed = *equipIt;
		if (!pPlayer->HasGoods(equipNeed.uEquipId, equipNeed.uEquipNum))
		{
			return ERROR_EQUIP_NOT_ENOUGHT;
		}
	}

	// 检查完之后就是扣除玩家的道具，同时将新合成的物品添加到玩家包裹
	pPlayer->DelGoods(compoundConf.uScrollId);
	equipIt = compoundConf.equipNeedVec.begin();
	equipItEnd = compoundConf.equipNeedVec.end();
	for (; equipIt != equipItEnd; equipIt++)
	{
		const CompoundConf::EquipNeed& equipNeed = *equipIt;
		pPlayer->DelGoods(equipNeed.uEquipId, equipNeed.uEquipNum);
	}

	Goods goods;
	goods.uId = compoundConf.uCompoundId;
	pPlayer->AddGoodsIntoBag(goods);

	return ERROR_OP_SUCCESS;
}