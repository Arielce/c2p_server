#include "GateController.h"
#include "../protocol/GameProtocol.pb.h"
#include "../network/Utility.h"
#include "../protocol/GameProtocol.h"
#include "../protocol/ErrorCodes.h"
#include "../network/header.h"
#include "../tinyxml/tinyxml.h"
#include "HeroMng.h"
#include "PlayerMng.h"
#include "PrizeMng.h"


GateController::GateController() : m_pNormalGate(NULL)
{
	m_pNormalGate = new NormalGate();
}

GateController::~GateController()
{

}

bool GateController::LoadBattleGateConf()
{
	TiXmlDocument xmlDoc;
	if (!xmlDoc.LoadFile("./xml/BattleGate.xml"))
	{
		return false;
	}

	TiXmlElement* pRoot = xmlDoc.RootElement();
	if (!pRoot)
	{
		return false;
	}

	TiXmlElement* pBattleList = pRoot->FirstChildElement("Battles");
	if (!pBattleList)
	{
		return false;
	}
	TiXmlElement* pBattle = pBattleList->FirstChildElement("Battle");
	while (pBattle)
	{
		TiXmlElement* pGate = pBattle->FirstChildElement("gate");
		while (pGate)
		{
			GateConf gateConf;
			gateConf.uGateId		= boost::lexical_cast<uint32_t>(pGate->Attribute("ID"));
			gateConf.uNextGateId	= boost::lexical_cast<uint32_t>(pGate->Attribute("NextID"));
			gateConf.uGateType		= boost::lexical_cast<uint32_t>(pGate->Attribute("GateType"));
			gateConf.uExpGet		= boost::lexical_cast<uint32_t>(pGate->Attribute("ExpGet"));
			gateConf.uHeroExpGet	= boost::lexical_cast<uint32_t>(pGate->Attribute("HeroExpGet"));
			gateConf.uApCost		= boost::lexical_cast<uint32_t>(pGate->Attribute("ApCost"));
			gateConf.uTimeLimit		= boost::lexical_cast<uint32_t>(pGate->Attribute("TimeLimit"));
			gateConf.uPrizePool		= boost::lexical_cast<uint32_t>(pGate->Attribute("PrizePool"));

			m_gateGateConfMap.insert(make_pair(gateConf.uGateId, gateConf));
			pGate = pGate->NextSiblingElement();
		}
		pBattle = pBattle->NextSiblingElement();
	}
	
	return true;
}

bool GateController::LoadGatePrizePool()
{
	TiXmlDocument xmlDoc;
	if (!xmlDoc.LoadFile("./xml/GatePrizePool.xml"))
	{
		return false;
	}

	TiXmlElement* pRoot = xmlDoc.RootElement();
	if (!pRoot)
	{
		return false;
	}

	TiXmlElement* pPrizePool = pRoot->FirstChildElement("GatePrizePool");
	if (!pPrizePool)
	{
		return false;
	}
	TiXmlElement* pPool = pPrizePool->FirstChildElement("pool");
	while (pPool)
	{
		uint32_t uPoolId = boost::lexical_cast<uint32_t>(pPool->Attribute("id"));
		string strPrize = pPool->Attribute("prize");
		vector<string> prizeVec;
		boost::split(prizeVec, strPrize, boost::is_any_of(","));

		GatePrizePool prizePool;
		vector<string>::iterator prizeIt = prizeVec.begin();
		vector<string>::iterator prizeItEnd = prizeVec.end();
		for (; prizeIt != prizeItEnd; prizeIt++)
		{
			GatePrizePool::PrizeProp prizeProp;
			string& strTempPrizeInfo = *prizeIt;
			// 去除空格
			strTempPrizeInfo.erase(strTempPrizeInfo.begin(), std::find_if(strTempPrizeInfo.begin(), strTempPrizeInfo.end(), std::not1(std::ptr_fun<int, int>(std::isspace)))); 
			
			size_t uIndex = (*prizeIt).find(':');
			if (uIndex == string::npos)					// 没有冒号，说明100%掉落
			{
				prizeProp.uProbability = MAX_GATE_PRIZE_PROB;
				prizeProp.uPrizeId = boost::lexical_cast<uint32_t>(*prizeIt);
			}
			else
			{
				string strProb = (*prizeIt).substr(uIndex + 1);
				string strPrize = (*prizeIt).substr(0, uIndex);
				prizeProp.uProbability = boost::lexical_cast<uint32_t>(strProb);
				prizeProp.uPrizeId = boost::lexical_cast<uint32_t>(strPrize);
			}
			prizePool.m_prizeList.push_back(prizeProp);
		}

		m_gatePrizePoolMap.insert(make_pair(uPoolId, prizePool));
		pPool = pPool->NextSiblingElement();
	}

	return true;
}

bool GateController::IsPrizePoolExist(uint32_t uPoolId)
{
	map<uint32_t, GatePrizePool>::iterator poolIt = m_gatePrizePoolMap.find(uPoolId);
	if (poolIt == m_gatePrizePoolMap.end())
	{
		return false;
	}
	return true;
}

const GatePrizePool& GateController::GetGatePrizePool(uint32_t uPoolId)
{
	map<uint32_t, GatePrizePool>::iterator poolIt = m_gatePrizePoolMap.find(uPoolId);
	return poolIt->second;
}

// 检查关卡是否存在
bool GateController::IsGateExist(uint32_t uGateId)
{
	map<uint32_t, GateConf>::iterator gateIt = m_gateGateConfMap.find(uGateId);
	if (gateIt == m_gateGateConfMap.end())
	{
		return false;
	}
	return true;
}

// 获取关卡配置，如果不存在就返回false
bool GateController::GetGateConf(uint32_t uGateId, GateConf& gateConf)
{
	map<uint32_t, GateConf>::iterator gateIt = m_gateGateConfMap.find(uGateId);
	if (gateIt == m_gateGateConfMap.end())
	{
		return false;
	}
	gateConf = gateIt->second;
	return true;
}

// 进入关卡
void GateController::EnterGate(Player* pPlayer, uint32_t uGateId, const vector<uint32_t>& heroList)
{
	if (!IsGateExist(uGateId))
	{
		ERRORLOG("gate not exist, gate id=[" << uGateId << "]");
		return;
	}
	GateConf gateConf;
	if (!GetGateConf(uGateId, gateConf))
	{
		return;
	}
	if (gateConf.uGateType == NORMAL_GATE || gateConf.uGateType == BOSS_GATE)
	{
		m_pNormalGate->EnterGate(pPlayer, uGateId, heroList);
	}
	return;
}

// 结束关卡
void GateController::FinishGate(Player* pPlayer, uint32_t uGateId, int32_t nResult)
{
	if (!IsGateExist(uGateId))
	{
		ERRORLOG("gate not exist, gate id=[" << uGateId << "]");
		return;
	}
	GateConf gateConf;
	if (!GetGateConf(uGateId, gateConf))
	{
		return;
	}
	if (gateConf.uGateType == NORMAL_GATE || gateConf.uGateType == BOSS_GATE)
	{
		m_pNormalGate->FinishGate(pPlayer, uGateId, nResult);
	}
	return;
}

void GateController::SweepGate(Player* pPlayer, uint32_t uGateId)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GateChecker::GateChecker()
{

}

GateChecker::~GateChecker()
{

}

bool GateChecker::IsGateValid(Player* pPlayer, uint32_t uGateId)
{
	if (!pPlayer)
	{
		return false;
	}
	if (!pPlayer->CanEnterGate(uGateId))
	{
		ERRORLOG("player " << pPlayer->RoleName() << " cannot enter gate id=" << uGateId);
		return false;
	}
	return true;
}

bool GateChecker::IsHerosValid(Player* pPlayer, const vector<uint32_t>& heroList)
{
	vector<uint32_t>::const_iterator heroIt = heroList.begin();
	vector<uint32_t>::const_iterator heroItEnd = heroList.end();
	for (; heroIt != heroItEnd; heroIt++)
	{
		if (!pPlayer->HasHero(*heroIt))						// 这个英雄玩家没有拥有
		{
			return false;
		}
	}

	return true;
}

// 进入关卡
void GateChecker::EnterGate(Player* pPlayer, uint32_t uGateId, const vector<uint32_t>& heroList)
{
	_RecordEnterGate(pPlayer, uGateId, heroList);
}

// 判断是否有进入关卡记录
bool GateChecker::HasGateRecord(Player* pPlayer, uint32_t uGateId)
{
	map<string, GateRecord>::iterator gateIt = m_enterRecordMap.find(pPlayer->RoleName());
	if (gateIt == m_enterRecordMap.end())
	{
		return false;
	}

	if (gateIt->second.uGateId != uGateId)
	{
		return false;
	}

	return true;
}

// 获取英雄列表
const vector<uint32_t>& GateChecker::GetHeroList(Player* pPlayer)
{
	map<string, GateRecord>::iterator gateIt = m_enterRecordMap.find(pPlayer->RoleName());
	return gateIt->second.heroList;
}

// 记录进入关卡的信息
void GateChecker::_RecordEnterGate(Player* pPlayer, uint32_t uGateId, const vector<uint32_t>& heroList)
{
	GateRecord gateRecord;
	gateRecord.uGateId = uGateId;
	gateRecord.heroList = heroList;

	m_enterRecordMap.insert(make_pair(pPlayer->RoleName(), gateRecord));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GateAchieve::GateAchieve()
{

}

GateAchieve::~GateAchieve()
{

}

// 给玩家发通关奖励
void GateAchieve::GivePrize(Player* pPlayer, uint32_t uGateId, int32_t nResult, const vector<uint32_t>& heroList)
{
	if (!pPlayer)
	{
		return;
	}
	GateConf gateConf;
	if (!gpGateController->GetGateConf(uGateId, gateConf))
	{
		ERRORLOG("GateAchieve give prize, cannot find gate configure, id=[" << uGateId << "]");
		return;
	}

	// 给玩家发放经验
	gpPrizeMng->GiveExp(pPlayer, gateConf.uExpGet);

	// 给玩家英雄们发放经验
	vector<uint32_t>::const_iterator heroIt = heroList.begin();
	vector<uint32_t>::const_iterator heroItEnd = heroList.end();
	for (; heroIt != heroItEnd; heroIt++)
	{
		gpPrizeMng->GiveHeroExp(pPlayer, *heroIt, gateConf.uHeroExpGet);
	}

	// give prize in pool
	if (!gpGateController->IsPrizePoolExist(gateConf.uPrizePool))
	{
		ERRORLOG("Cannot find prize pool id=[" << gateConf.uPrizePool << "]");
		return;
	}

	// 给玩家发放奖励
	const GatePrizePool& prizePool = gpGateController->GetGatePrizePool(gateConf.uPrizePool);
	vector<GatePrizePool::PrizeProp>::const_iterator prizeIt = prizePool.m_prizeList.begin();
	vector<GatePrizePool::PrizeProp>::const_iterator prizeItEnd = prizePool.m_prizeList.end();
	for (; prizeIt != prizeItEnd; prizeIt++)
	{		
		const GatePrizePool::PrizeProp& prizeProp = *prizeIt;
		uint32_t uRand = GenRandom(0, MAX_GATE_PRIZE_PROB);
		if (uRand < prizeProp.uProbability)					// 触发概率
		{
			gpPrizeMng->GiveGoods(pPlayer, prizeProp.uPrizeId);
		}
	}

	return;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NormalGate::NormalGate()
{

}

NormalGate::~NormalGate()
{

}

void NormalGate::EnterGate(Player* pPlayer, uint32_t uGateId, const vector<uint32_t>& heroList)
{
	ctos::ResponseEnterGate enterGateAck;
	if (!m_gateChecker.IsGateValid(pPlayer, uGateId))
	{
		enterGateAck.set_errcode(ERROR_PLAYER_CAN_NOT_ENTER);
	}
	else if (!m_gateChecker.IsHerosValid(pPlayer, heroList))
	{
		enterGateAck.set_errcode(ERROR_HERO_NOT_EXIST);
	}
	else
	{
		m_gateChecker.EnterGate(pPlayer, uGateId, heroList);
	}

	IConnection* pClientConnection = pPlayer->GetPlayerConnection();
	if (!pClientConnection || !pClientConnection->IsConnected())
	{
		ERRORLOG("enter gate, ptname=[" << pPlayer->PtName() << "] client connection invalid");
		return;
	}

	string strMessage;
	BuildResponseProto<ctos::ResponseEnterGate>(enterGateAck, strMessage, ID_ACK_ResponseEnterGate);
	pClientConnection->SendMsg(strMessage.c_str(), strMessage.size());
	return;
}

void NormalGate::FinishGate(Player* pPlayer, uint32_t uGateId, int32_t nResult)
{
	ctos::ResponseFinishiGate finishGateAck;
	if (!m_gateChecker.HasGateRecord(pPlayer, uGateId))
	{
		TRACELOG("player rolename=[" << pPlayer->RoleName() << "] has no gate id=" << uGateId << " record");
		finishGateAck.set_errcode(ERROR_PLAYER_NEVER_ENTER);
	}
	else
	{
		pPlayer->AddGatePass(uGateId, nResult);
		if (nResult == BATTLE_FAILED)					// 战斗失败
		{
			return;
		}

		m_gateAchieve.GivePrize(pPlayer, uGateId, nResult, m_gateChecker.GetHeroList(pPlayer));
	}

	IConnection* pClientConnection = pPlayer->GetPlayerConnection();
	if (!pClientConnection || !pClientConnection->IsConnected())
	{
		ERRORLOG("enter gate, ptname=[" << pPlayer->PtName() << "] client connection invalid");
		return;
	}

	string strMessage;
	BuildResponseProto<ctos::ResponseFinishiGate>(finishGateAck, strMessage, ID_ACK_ResponseFinishGate);
	pClientConnection->SendMsg(strMessage.c_str(), strMessage.size());
	return;
}
