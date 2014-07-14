#include "Player.h"
#include "PlayerMng.h"
#include "GateController.h"
#include "../network/Uuid.h"
#include "HeroMng.h"

Player::Player() : m_state(PLAYER_OFFLINE), m_pClientConn(NULL), m_uSecureToken(0), m_bHasVerifyFromServer(false), m_bHasVerifyToken(false), m_uID(0), m_uLevel(0), m_uExp(0), m_uGold(0), m_uDiamond(0), m_bDataReady(false)
{

}

Player::~Player()
{

}

PLAYER_STATE Player::State()
{
	return m_state;
}

void Player::SetPlayerState(PLAYER_STATE eState)
{
	m_state = eState;
}

void Player::IncreaseVersion()
{
	++m_uDataVersion;
}

void Player::SetPlayerActive()
{
	m_timer.resume();
}

uint32_t Player::PlayerLeaveTimes()
{
	return uint32_t(m_timer.elapsed().wall / 1000000000.0L);
}

bool Player::IsPlayerDataReady()
{
	return m_bDataReady;
}

uint32_t Player::GetPlayerID()
{
	return m_uID;
}

const string& Player::PtName()
{
	return m_strPtName;
}
void Player::SetPtName(const string& strPtName)
{
	m_strPtName = strPtName;
}
const string& Player::RoleName()
{
	return m_strRoleName;
}
void Player::SetRoleName(const string& strRoleName)
{
	m_strRoleName = strRoleName;
}

IConnection* Player::GetPlayerConnection()
{
	return m_pClientConn;
}

void Player::SetPlayerConnection(IConnection* pClientConn)
{
	if (pClientConn == NULL)
	{
		ClientDisconnect();
		return;
	}
	if (m_pClientConn != pClientConn)
	{
		m_pClientConn = pClientConn;
	}
}

void Player::ClientDisconnect()
{
	m_pClientConn = NULL;
	m_bHasVerifyToken = false;
}

void Player::SerializeToPB(roledata::PBRoleTotalInfo& roleTotalInfo)
{
	roledata::PBRoleBaseInfo* pBaseInfo = roleTotalInfo.mutable_baseinfo();
	roledata::PBRoleBag* pRoleBag = roleTotalInfo.mutable_baginfo();
	// 序列化玩家基本信息
	_SerializeRoleBaseInfo(*pBaseInfo);
	// 序列化玩家包裹信息
	_SerializeRoleBagInfo(*pRoleBag);

#ifdef DEBUG_SERVER
	string strOutput;
	google::protobuf::TextFormat::PrintToString(roleTotalInfo, &strOutput);
	TRACELOG("roleTotalInfo:" << endl << strOutput);
#endif
}

// 序列化玩家基本信息
void Player::_SerializeRoleBaseInfo(roledata::PBRoleBaseInfo& roleBaseInfo)
{
	roleBaseInfo.set_dataversion(m_uDataVersion);
	roleBaseInfo.set_userid(m_uID);
	roleBaseInfo.set_ptname(m_strPtName);
	roleBaseInfo.set_rolename(m_strRoleName);
	roleBaseInfo.set_level(m_uLevel);
	roleBaseInfo.set_exp(m_uExp);
	roleBaseInfo.set_gold(m_uGold);
	roleBaseInfo.set_diamond(m_uDiamond);

	TRACELOG("serialize role base info, id=[" << m_uID << "], ptname=[" << m_strPtName << "]");

	// 玩家英雄信息
	roledata::PBHeroList* pHeroList = roleBaseInfo.mutable_herolist();
	map<uint64_t, Hero>::iterator heroIt = m_roleHeroMap.begin();
	map<uint64_t, Hero>::iterator heroItEnd = m_roleHeroMap.end();
	for (; heroIt!=heroItEnd; heroIt++)
	{
		Hero& hero = heroIt->second;
		roledata::PBHero* pPBHero = pHeroList->add_heros();
		pPBHero->set_heroid(hero.GetHeroId());
		pPBHero->set_herouuid(hero.GetHeroUUID());
		pPBHero->set_level(hero.GetLevel());
		pPBHero->set_exp(hero.GetExp());
		pPBHero->set_herorank(hero.GetHeroRank());
		pPBHero->set_upgradelevel(hero.GetUpgradeLevel());
		pPBHero->set_fragmentnum(hero.GetFragmentNum());

		const vector<Goods> equipList = hero.GetEquipList();
		size_t nEquipNum = equipList.size();
		for (size_t i=0; i<nEquipNum; i++)
		{
			pPBHero->add_equips()->set_equipid(equipList[i].uId);
			pPBHero->add_equips()->set_equipnum(equipList[i].uNum);
		}
	}

	// 玩家关卡信息
	roledata::PBBattleGateList* pBattleGateList = roleBaseInfo.mutable_battlegatelist();
	map<uint32_t, BattleInfo>::iterator battleIt = m_battleMap.begin();
	map<uint32_t, BattleInfo>::iterator battleItEnd = m_battleMap.end();
	for (; battleIt!=battleItEnd; battleIt++)
	{
		BattleInfo& battle = battleIt->second;
		roledata::PBBattleInfo* pPBBattle = pBattleGateList->add_battlegates();
		pPBBattle->set_battleid(battle.uBattleId);

		vector<uint32_t>& gateList = battle.gateList;
		vector<uint32_t>::iterator gateIt = gateList.begin();
		vector<uint32_t>::iterator gateItEnd = gateList.end();
		for (; gateIt!=gateItEnd; gateIt++)
		{
			map<uint32_t, GateInfo>::iterator findGateIt = m_gateMap.find(*gateIt);
			if (findGateIt == m_gateMap.end())
			{
				ERRORLOG("cannot find gate id=" << *gateIt << "in map");
				continue;
			}
			GateInfo& gate = findGateIt->second;
			roledata::PBGateInfo* pPBGateInfo = pPBBattle->add_gates();
			pPBGateInfo->set_gateid(gate.uGateId);
			pPBGateInfo->set_gatestar(gate.uGateStar);
			pPBGateInfo->set_hasfight(gate.bHasFight);
		}
	}
}

// 序列化玩家包裹信息
void Player::_SerializeRoleBagInfo(roledata::PBRoleBag& roleBag)
{
	map<uint32_t, Goods>::iterator goodsIt = m_roleBagMap.begin();
	map<uint32_t, Goods>::iterator goodsItEnd = m_roleBagMap.end();
	for (; goodsIt != goodsItEnd; goodsIt++)
	{
		const Goods& goods = goodsIt->second;
		roledata::PBEquip* pPBEquip = roleBag.add_equips();
		pPBEquip->set_equipid(goods.uId);
		pPBEquip->set_equipnum(goods.uNum);
	}
}

void Player::SetHasVerifyFromServer()
{
	m_bHasVerifyFromServer = true;
}

bool Player::HasVerifyFromServer()
{
	return m_bHasVerifyFromServer;
}

bool Player::HasVerified(IConnection* pConnection)
{
	if (!m_bHasVerifyToken || m_pClientConn != pConnection)
	{
		return false;
	}
	return true;
}

void Player::SetToken(uint32_t uToken)
{
	m_uSecureToken = uToken;
}

bool Player::VerifyToken(uint32_t uToken)
{
	if (uToken != m_uSecureToken || !HasVerifyFromServer())
	{
		return false;
	}
	m_bHasVerifyToken = true;
	return true;
}

void Player::SendMsg(const void* pData, uint32_t uLen)
{
	if (!m_pClientConn || !m_pClientConn->IsConnected())
	{
		return;
	}
	m_pClientConn->SendMsg(pData, uLen);
	return;
}

void Player::GetRoleTotalInfo(const roledata::PBRoleTotalInfo& roleTotalInfo)
{
	const roledata::PBRoleBaseInfo& roleBaseInfo = roleTotalInfo.baseinfo();
	const roledata::PBRoleBag& pbRoleBag = roleTotalInfo.baginfo();

	// 解析玩家基础数据
	_ParseRoleBaseInfo(roleBaseInfo);
	// 解析玩家包裹数据
	_ParseRoleBagInfo(pbRoleBag);

	// 设置玩家数据已经准备好
	_SetPlayerDataReady();
}

void Player::_ParseRoleBaseInfo(const roledata::PBRoleBaseInfo& roleBaseInfo)
{
	m_uDataVersion	= roleBaseInfo.dataversion();
	m_uID			= roleBaseInfo.userid();
	m_strPtName		= roleBaseInfo.ptname();
	m_strRoleName	= roleBaseInfo.rolename();
	m_uLevel		= roleBaseInfo.level();
	m_uExp			= roleBaseInfo.exp();
	m_uGold			= roleBaseInfo.gold();
	m_uDiamond		= roleBaseInfo.diamond();

	TRACELOG("Parse role base info, id=[" << m_uID << "], rolename=[" << m_strRoleName << "]");

	if (m_uLevel == 0)					// 玩家是第一次进入游戏, 对角色进行初始化操作
	{
		_InitPlayerData();
	}

	// 解析玩家英雄列表
	const roledata::PBHeroList& heroList = roleBaseInfo.herolist();
	uint32_t uSize = heroList.heros_size();
	for (uint32_t i=0; i<uSize; i++)
	{
		Hero hero;
		const roledata::PBHero& pbHero = heroList.heros(i);
		hero.SetHeroId(pbHero.heroid());
		hero.SetHeroUUID(pbHero.herouuid());
		hero.SetLevel(pbHero.level());
		hero.SetExp(pbHero.exp());
		hero.SetHeroRank(pbHero.herorank());
		hero.SetUpgradeLevel(pbHero.upgradelevel());
		hero.SetFragmentNum(pbHero.fragmentnum());
		
		uint32_t uEquipNum = pbHero.equips_size();
		for (uint32_t n=0; n<uEquipNum; n++)
		{
			const roledata::PBEquip pbEquip = pbHero.equips(n);
			Goods equip;
			equip.uId = pbEquip.equipid();
			equip.uNum = pbEquip.equipnum();
			hero.GetMutableEquipList().push_back(equip);
		}
		m_roleHeroMap.insert(make_pair(hero.GetHeroUUID(), hero));
	}

	// 解析玩家关卡信息
	const roledata::PBBattleGateList& battleGateList = roleBaseInfo.battlegatelist();
	uint32_t uBattleSize = battleGateList.battlegates_size();
	for (size_t i=0; i<uBattleSize; i++)
	{
		const roledata::PBBattleInfo& battleInfo = battleGateList.battlegates(i);
		BattleInfo battle;
		battle.uBattleId = battleInfo.battleid();

		uint32_t uGateSize = battleInfo.gates_size();
		for (uint32_t n=0; n<uGateSize; n++)
		{
			GateInfo gateInfo;
			gateInfo.uGateId = battleInfo.gates(n).gateid();
			gateInfo.uGateStar = battleInfo.gates(n).gatestar();
			gateInfo.bHasFight = battleInfo.gates(n).hasfight();
			m_gateMap.insert(make_pair(gateInfo.uGateId, gateInfo));

			battle.gateList.push_back(gateInfo.uGateId);
		}

		m_battleMap.insert(make_pair(battleInfo.battleid(), battle));
	}
}

void Player::_ParseRoleBagInfo(const roledata::PBRoleBag& roleBag)
{
	uint32_t uEquipNum = roleBag.equips_size();
	for (uint32_t i=0; i<uEquipNum; i++)
	{
		const roledata::PBEquip pbEquip = roleBag.equips(i);
		Goods goods;
		goods.uId = pbEquip.equipid();
		goods.uNum = pbEquip.equipnum();

		m_roleBagMap.insert(make_pair(goods.uId, goods));
	}
}

void Player::_SetPlayerDataReady()
{
	m_bDataReady = true;
}

// 初始化角色数据
void Player::_InitPlayerData()
{
	const PlayerInitData& playerInitData = gpPlayerMng->GetPlayerInitData();
	m_uLevel	= playerInitData.uLevel;	
	m_uExp		= playerInitData.uExp;		
	m_uGold		= playerInitData.uGold;	
	m_uDiamond	= playerInitData.uDiamond;

	// 添加关卡信息
	uint32_t nBattleId = playerInitData.uGateId / 1000;
	BattleInfo battleInfo;
	battleInfo.uBattleId = nBattleId;
	battleInfo.gateList.push_back(playerInitData.uGateId);
	m_battleMap.insert(make_pair(battleInfo.uBattleId, battleInfo));

	GateInfo gateInfo;
	gateInfo.uGateId = playerInitData.uGateId;
	m_gateMap.insert(make_pair(gateInfo.uGateId, gateInfo));

	// 初始化英雄信息
	_InitPlayerHero();
}

// 初始化玩家英雄信息
void Player::_InitPlayerHero()
{
	const PlayerInitData& playerInitData = gpPlayerMng->GetPlayerInitData();

	uint32_t uHeroNum = playerInitData.heroList.size();
	for (uint32_t i=0; i<uHeroNum; i++)
	{
		HeroConf heroConf;
		if (!gpHeroMng->GetHeroConf(playerInitData.heroList[i], heroConf))
		{
			ERRORLOG("cannot get hero configure id=[" << playerInitData.heroList[i] << "]");
			break;
		}
		AddHero(heroConf.uHeroId, heroConf.uInitRank, heroConf.uInitLevel);
	}
}

void Player::AddGold(uint32_t uGold)
{
	m_uGold += uGold;
}

void Player::SubGold(uint32_t uSubGold)
{
	if (m_uGold < uSubGold)
	{
		m_uGold = 0;
		return;
	}
	m_uGold -= uSubGold;
	return;
}

void Player::AddDiamond(uint32_t uDiamond)
{
	m_uDiamond += uDiamond;
}

void Player::SubDiamond(uint32_t uSubDiamond)
{
	if (m_uDiamond < uSubDiamond)
	{
		m_uDiamond = 0;
		return;
	}
	m_uDiamond -= uSubDiamond;
	return;
}

void Player::AddExp(uint32_t uExp)
{
	m_uExp += uExp;
}

uint32_t Player::GetGold()
{
	return m_uGold;
}

uint32_t Player::GetDiamond()
{
	return m_uDiamond;
}

uint32_t Player::GetExp()
{
	return m_uExp;
}

void Player::SetExp(uint32_t uExp)
{
	m_uExp = uExp;
}

uint32_t Player::GetLevel()
{
	return m_uLevel;
}

void Player::SetLevel(uint32_t uLevel)
{
	m_uLevel = uLevel;
}

bool Player::GetHero(uint64_t uHeroUUID, Hero& hero)
{
	map<uint64_t, Hero>::iterator heroIt = m_roleHeroMap.find(uHeroUUID);
	if (heroIt == m_roleHeroMap.end())
	{
		return false;
	}
	hero = heroIt->second;
	return true;
}

// 给玩家的包裹中增加物品
void Player::AddGoodsIntoBag(const Goods& goods)
{
	m_roleBagMap.insert(make_pair(goods.uId, goods));
}

// 检查玩家的包裹中是否有足够的某种物品
bool Player::HasGoods(uint32_t uGoodsId, uint32_t uGoodsNum/* =1 */)
{
	map<uint32_t, Goods>::iterator goodsIt = m_roleBagMap.find(uGoodsId);
	if (goodsIt == m_roleBagMap.end())
	{
		return false;
	}
	if (goodsIt->second.uNum < uGoodsNum)
	{
		return false;
	}
	return true;
}

// 删除玩家包裹中的物品
void Player::DelGoods(uint32_t uGoodsId, uint32_t uGoodsNum/* =1 */)
{
	map<uint32_t, Goods>::iterator goodsIt = m_roleBagMap.find(uGoodsId);
	if (goodsIt == m_roleBagMap.end())
	{
		return;
	}
	if (goodsIt->second.uNum <= uGoodsNum)			// 如果物品数量刚好够，则从表中删除，否则只是减少数量
	{
		m_roleBagMap.erase(goodsIt);
	}
	else
	{
		goodsIt->second.uNum -= uGoodsNum;
	}
	return;
}

bool Player::CanEnterGate(uint32_t uGateId)
{
	map<uint32_t, GateInfo>::iterator gateIt = m_gateMap.find(uGateId);
	if (gateIt == m_gateMap.end())
	{
		return false;
	}
	return true;
}

// 增加玩家通过关卡信息
void Player::AddGatePass(uint32_t uGateId, uint32_t uGateStars)
{
	GateInfo gateInfo;
	gateInfo.uGateId = uGateId;
	gateInfo.uGateStar = uGateStars;
	gateInfo.bHasFight = true;

	GateConf gateConf;
	if (!gpGateController->GetGateConf(uGateId, gateConf))
	{
		ERRORLOG("cannot find gate id=[" << uGateId << "] configure");
		return;
	}

	if (uGateStars && gateConf.uNextGateId)		// 通关了，而且有下一个关卡
	{
		_AddNextGateAvailable(uGateStars);
	}

	map<uint32_t, GateInfo>::iterator gateIt = m_gateMap.find(uGateId);
	if (gateIt != m_gateMap.end())				// 玩家数据已经存在
	{
		gateIt->second = gateInfo;
		return;
	}
	return;
}

void Player::_AddNextGateAvailable(uint32_t nNextGateId)
{
	map<uint32_t, GateInfo>::iterator gateIt = m_gateMap.find(nNextGateId);
	if (gateIt != m_gateMap.end())				// 玩家关卡数据已经存在
	{
		return;
	}

	GateInfo gateInfo;
	gateInfo.uGateId = nNextGateId;

	// 玩家还没有有此关卡信息
	m_gateMap.insert(make_pair(nNextGateId, gateInfo));

	map<uint32_t, BattleInfo>::iterator battleIt = m_battleMap.find(nNextGateId/1000);
	if (battleIt == m_battleMap.end())
	{
		BattleInfo battle;
		battle.uBattleId = nNextGateId/1000;
		battle.gateList.push_back(nNextGateId);
		return;
	}
	BattleInfo& battle = battleIt->second;
	battle.gateList.push_back(nNextGateId);
	return;
}

void Player::AddHero(uint32_t uHeroId, uint32_t uHeroRank/* =1 */, uint32_t uHeroLevel/* =1 */, uint32_t uHeroExp/* =0 */)
{
	GenUUID uuidGen;

	Hero hero;
	hero.SetHeroId(uHeroId);
	hero.SetHeroUUID(uuidGen.generate());
	hero.SetLevel(uHeroLevel);
	hero.SetHeroRank(uHeroRank);

	m_roleHeroMap.insert(make_pair(hero.GetHeroUUID(), hero));
	return;
}

bool Player::HasHero(uint64_t uHeroUUID)
{
	map<uint64_t, Hero>::iterator heroIt = m_roleHeroMap.find(uHeroUUID);
	if (heroIt == m_roleHeroMap.end())
	{
		return false;
	}
	return true;
}