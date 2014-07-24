#include "header.h"
#include "PlayerMng.h"
#include "../protocol/GameProtocol.pb.h"
#include "../protocol/DataServer.pb.h"
#include "../protocol/DataProtocol.h"
#include "../network/Utility.h"
#include "../protocol/GameProtocol.h"
#include "../protocol/ErrorCodes.h"
#include "../protocol/LoginProtocol.h"
#include "../protocol/LoginProtocol.pb.h"
#include "ServerConfig.h"
#include "KeyGen.h"


TokenVerifyMng::TokenVerifyMng()
{

}

TokenVerifyMng::~TokenVerifyMng()
{

}

bool TokenVerifyMng::VerifyToken(Player* pPlayer, uint32_t uToken, bool bReconnect/* =true */)
{
	if (!pPlayer)
	{
		return false;
	}

	// 不是重连需要的Token验证
	if (!bReconnect)
	{
		pPlayer->SetToken(uToken);
		_SendVerifyToken(pPlayer->PtName(), uToken);
		return true;
	}

	bool bRet = pPlayer->VerifyToken(uToken);
	return bRet;
}

void TokenVerifyMng::ServerVerifyBack(Player* pPlayer, uint32_t uErrorCode)
{
	pPlayer->SetHasVerifyFromServer();								// 设置已经从服务器验证过Token
}

void TokenVerifyMng::_SendVerifyToken(string strPtName, uint32_t uToken)
{
	if (!g_pLoginAgentSession)
	{
		return;
	}
	login::SRequestVerifyToken verifyTokenSreq;
	verifyTokenSreq.set_ptname(strPtName);
	verifyTokenSreq.set_token(boost::lexical_cast<string>(uToken));

	string strMessage;
	BuildResponseProto<login::SRequestVerifyToken>(verifyTokenSreq, strMessage, ID_SREQ_SRequestVerifyToken);
	g_pLoginAgentSession->SendMsg(strMessage.c_str(), strMessage.size());
	return;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PlayerMng::PlayerMng()
{
#ifndef _MSC_VER
	m_pRedisClient = NULL;
	m_pRedisClient = new redis::client(gpServerConfig->GetRedisIp(), gpServerConfig->GetRedisPort(), gpServerConfig->GetRedisIndex());
#endif
}

PlayerMng::~PlayerMng()
{
#ifndef _MSC_VER
	if (m_pRedisClient)
	{
		delete m_pRedisClient;
	}
#endif
	m_playerInfoMap.clear();
	m_playerIdMap.clear();
}

// 定时判断是否需要保存玩家逻辑
void PlayerMng::OnTimer(const BoostErrCode& errCode)
{
	if (errCode)
	{
		ERRORLOG("playermng ontimer error=[" << errCode.message() << "]");
		return;
	}
	
	_SaveOnlinePlayer();

	return;
}

Player* PlayerMng::_InitPlayerInfo(string strPtName, IConnection* pConn)
{
	Player* pPlayer = CreatePlayer();
	if (!pPlayer)
	{
		return NULL;
	}
	pPlayer->SetPtName(strPtName);
	m_clientConnMng.SetPlayerConnection(pPlayer, pConn);				// 保存玩家对应的网络连接
	m_playerInfoMap.insert(make_pair(strPtName, pPlayer));				// 保存玩家pt名和玩家的对应关系
	return pPlayer;
}

void PlayerMng::_SaveOnlinePlayer(uint32_t uFlag)
{
	bool bStopServer = false;
	if (uFlag & 0x1)													// 判断是否为停机保存
	{
		bStopServer = true;
	}
	map<uint32_t, Player*>::iterator playerIt = m_playerIdMap.begin();
	map<uint32_t, Player*>::iterator playerItEnd = m_playerIdMap.end();
	for (; playerIt!=playerItEnd; )
	{
		Player* pPlayer = playerIt->second;
		if (!pPlayer)
		{
			m_playerIdMap.erase(playerIt++);
			ERRORLOG("player point is NULL is playerIdMap, id=[" << playerIt->first << "]");
			continue;
		}

		if (pPlayer->PlayerLeaveTimes() < 1000 && !bStopServer)							// 玩家没有离开太长时间，并且不是停止服务器
		{
			playerIt++;
			continue;
		}

		m_playerIdMap.erase(playerIt++);
		m_playerInfoMap.erase(pPlayer->PtName());

		pPlayer->SetPlayerState(PLAYER_OFFLINE);
		// 保存玩家数据
		_SaveRoleData(pPlayer);
	}
}

void PlayerMng::Stop()
{
	_SaveOnlinePlayer(1);
}

bool PlayerMng::LoadPlayerInitConf()
{
	TiXmlDocument xmlDoc;
	if (!xmlDoc.LoadFile("./xml/InitPlayerData.xml"))
	{
		return false;
	}

	TiXmlElement* pRoot = xmlDoc.RootElement();
	if (!pRoot)
	{
		return false;
	}

	TiXmlElement* pInitPlayerData = pRoot->FirstChildElement("InitPlayerData");
	if (!pInitPlayerData)
	{
		return false;
	}
	TiXmlElement* pPlayerData = pInitPlayerData->FirstChildElement("PlayerData");
	if (!pInitPlayerData)
	{
		return false;
	}

	try
	{
		m_playerInitData.uLevel = boost::lexical_cast<uint32_t>(pPlayerData->Attribute("Level"));
		m_playerInitData.uExp = boost::lexical_cast<uint32_t>(pPlayerData->Attribute("Exp"));
		m_playerInitData.uAp = boost::lexical_cast<uint32_t>(pPlayerData->Attribute("Ap"));
		m_playerInitData.uGold = boost::lexical_cast<uint32_t>(pPlayerData->Attribute("Gold"));
		m_playerInitData.uDiamond = boost::lexical_cast<uint32_t>(pPlayerData->Attribute("Diamond"));
		m_playerInitData.uGateId = boost::lexical_cast<uint32_t>(pPlayerData->Attribute("GateId"));

		// 读取初始英雄列表
		TiXmlElement* pHeroList = pInitPlayerData->FirstChildElement("Hero");
		if (!pHeroList)
		{
			return false;
		}

		uint32_t uHeroId1 = boost::lexical_cast<uint32_t>(pHeroList->Attribute("Hero1"));
		uint32_t uHeroId2 = boost::lexical_cast<uint32_t>(pHeroList->Attribute("Hero2"));
		uint32_t uHeroId3 = boost::lexical_cast<uint32_t>(pHeroList->Attribute("Hero3"));
		m_playerInitData.heroList.push_back(uHeroId1);
		m_playerInitData.heroList.push_back(uHeroId2);
		m_playerInitData.heroList.push_back(uHeroId3);
	}
	catch (boost::bad_lexical_cast& err)
	{
		ERRORLOG("bad lexical cast, error=[" << err.what() << "]");
		return false;
	}
	
	return true;
}

// 读取玩家升级表
bool PlayerMng::LoadPlayerLevelConf()
{
	TiXmlDocument xmlDoc;
	if (!xmlDoc.LoadFile("./xml/PlayerLevel.xml"))
	{
		return false;
	}

	TiXmlElement* pRoot = xmlDoc.RootElement();
	if (!pRoot)
	{
		return false;
	}

	TiXmlElement* pLevelInfo = pRoot->FirstChildElement("levelInfo");
	if (!pLevelInfo)
	{
		return false;
	}

	TiXmlElement* pLevel = pLevelInfo->FirstChildElement("level");
	while (pLevel)
	{
		try 
		{
			PlayerLevelConf levelConf;
			levelConf.uLevel = boost::lexical_cast<uint32_t>(pLevel->Attribute("ID"));
			levelConf.uExpNeed = boost::lexical_cast<uint32_t>(pLevel->Attribute("ExpNeed"));
			levelConf.uMaxAp = boost::lexical_cast<uint32_t>(pLevel->Attribute("MaxAp"));
			m_playerLevelMap.insert(make_pair(levelConf.uLevel, levelConf));

			pLevel = pLevel->NextSiblingElement();
		}
		catch(boost::bad_lexical_cast& err)
		{
			ERRORLOG("bad lexical cast, error=[" << err.what() << "]");
			return false;
		}
	}

	return true;
}

// 处理所有的请求，在内部进行处理
void PlayerMng::ProcReq(IConnection* pConn, MessageHeader* pMsgHeader)
{
	if (!pConn || !pMsgHeader)
	{
		return;
	}
	switch (pMsgHeader->uMsgCmd)
	{
	case ID_REQ_RequestVerifyToken:			// 请求验证token
		{
			try
			{
				_RequestVerifyToken(pConn, pMsgHeader);
			}
			catch (google::protobuf::FatalException fe)
			{
				ERRORLOG("protobuf excetpion error=[" << fe.message() << "]");
			}
		}
		break;
	case ID_REQ_RequestCreateRole:			// 请求创建角色
		{
			try
			{
				_RequestCreateRole(pConn, pMsgHeader);
			}
			catch (google::protobuf::FatalException fe)
			{
				ERRORLOG("protobuf excetpion error=[" << fe.message() << "]");
			}
		}
		break;
	case ID_REQ_RequestRoleData:			// 请求角色数据
		{
			try
			{
				_RequestRoleData(pConn, pMsgHeader);
			}
			catch (google::protobuf::FatalException fe)
			{
				ERRORLOG("protobuf excetpion error=[" << fe.message() << "]");
			}	
		}
		break;
	case ID_SACK_SResponseVerifyToken:		// 验证Token结果返回
		{
			_SResponseVerifyToken(pConn, pMsgHeader);
		}
		break;
	default:
		break;
	}
}

Player* PlayerMng::GetValidPlayer(uint32_t uUserId, IConnection* pConnection)
{
	Player* pPlayer = gpPlayerMng->GetPlayer(uUserId);
	if (!pPlayer)
	{
		ERRORLOG("request enter gate, cannot find user id=[" << uUserId << "] in players");
		return NULL;
	}
	if (!pPlayer->HasVerified(pConnection))
	{
		ERRORLOG("this connection has never been verified");
		return NULL;
	}
	return pPlayer;
}

void PlayerMng::CreateRoleResult(const string& strPtName, int32_t nErrCode)
{
	Player* pPlayer = GetPlayer(strPtName);
	if (!pPlayer)
	{
		ERRORLOG("create role ptname=[" << strPtName << "] result, cannot find player");
		return;
	}
	IConnection* pClientConn = pPlayer->GetPlayerConnection();
	if (!pClientConn || !pClientConn->IsConnected())
	{
		ERRORLOG("create role ptname=[" << strPtName << "] result, client connection invalid");
		return;
	}

	ctos::ResponseCreateRole createRoleAck;
	createRoleAck.set_errcode(nErrCode);

	string strMessage;
	BuildResponseProto<ctos::ResponseCreateRole>(createRoleAck, strMessage, ID_ACK_ResponseCreateRole);
	pClientConn->SendMsg(strMessage.c_str(), strMessage.size());
	return;
}

uint32_t PlayerMng::GetOnlinePlayerNum()
{
	return m_playerIdMap.size();
}

Player* PlayerMng::CreatePlayer()
{
	return new Player;
}

void PlayerMng::ReleasePlayer(Player* pPlayer)
{
	if (pPlayer)
	{
		delete pPlayer;
	}
}

bool PlayerMng::IsPlayerOnline(const string& strPtName)
{
	map<string, Player*>::iterator playerIt = m_playerInfoMap.find(strPtName);
	if (playerIt == m_playerInfoMap.end())
	{
		return false;
	}

	Player* pPlayer = playerIt->second;
	if (!pPlayer || !pPlayer->IsPlayerDataReady())				// 玩家角色数据还没获得
	{
		return false;
	}
	return true;
}

Player* PlayerMng::GetPlayer(const string& strPtName)
{
	map<string, Player*>::iterator playerIt = m_playerInfoMap.find(strPtName);
	if (playerIt == m_playerInfoMap.end())
	{
		return NULL;
	}
	return playerIt->second;
}

Player* PlayerMng::GetPlayer(uint32_t nPlayerId)
{
	map<uint32_t, Player*>::iterator playerIt = m_playerIdMap.find(nPlayerId);
	if (playerIt == m_playerIdMap.end())
	{
		return NULL;
	}
	return playerIt->second;
}

// 客户端断开连接
void PlayerMng::ClientDisconnect(IConnection* pConnection)
{
	m_clientConnMng.ClientDisconnect(pConnection);
	return;
}

/* 
	desc: 获取角色数据
	角色数据可能存在于GameServer的缓存之中，
	如果不在，就去redis缓存中查找，
	如果也不在，就去mysql数据库中查找
*/
void PlayerMng::GetPlayerData(IConnection* pConnection, const string& strPtName)
{
	Player* pPlayer = NULL;
	roledata::PBRoleTotalInfo roleData;

	// 判断此链接是否已经被其他玩家使用了（同一个链接只支持一个玩家）
	if (m_clientConnMng.IsConnectionUsed(strPtName, pConnection))
	{
		TRACELOG("the connection has already been used by other player, ptname=[" << strPtName << "]");
		return;
	}

	// 如果玩家在线，那么就直接从内存中获取玩家数据
	if (IsPlayerOnline(strPtName))
	{
		pPlayer = GetPlayer(strPtName);
		if (!pPlayer)
		{
			ERRORLOG("get player failed, pt name=[" << strPtName << "]");
			return;
		}
		
		// 将玩家数据组织成PB格式
		pPlayer->SerializeToPB(roleData);
		
		pPlayer->SetPlayerConnection(pConnection);
		m_clientConnMng.SetPlayerConnection(pPlayer, pConnection);			// 重新设置玩家对应的网络连接
		
		// 已经获取到了数据
		AchievePlayerData(roleData, "Player In mem");
		return;
	}

	pPlayer = GetPlayer(strPtName);
	if (!pPlayer)
	{
		// 玩家数据不在内存中
		pPlayer = _InitPlayerInfo(strPtName, pConnection);
	}
	else 
	{
		// 更新玩家数据
		m_clientConnMng.SetPlayerConnection(pPlayer, pConnection);
		m_playerInfoMap.insert(make_pair(strPtName, pPlayer));
	}
	
	if (pPlayer->State() == PLAYER_FETCHING_DATA)			// 玩家正在取数据中
	{
		TRACELOG("player rolename=[" << strPtName << "] is in state PLAYER_FETCHING_DATA");
		return;
	}
	
	m_playerDataGetter.GetPlayerData(pPlayer);									// 从其他途径获取玩家数据(redis, 或者mysql)
	return;
}

// 获取到角色数据之后，回调此函数
void PlayerMng::AchievePlayerData(const roledata::PBRoleTotalInfo& roleData, const string& strDesc)
{
	map<string, Player*>::iterator playerIt = m_playerInfoMap.find(roleData.baseinfo().ptname());
	if (playerIt == m_playerInfoMap.end())
	{
		ERRORLOG("cannot find player, ptname=[" << roleData.baseinfo().ptname() << "],desc=[" << strDesc << "]");
		return;
	}
	Player* pPlayer = playerIt->second;
	if (!pPlayer)
	{
		ERRORLOG("player is NULL");
		return;
	}
	
	IConnection* pClientConn = pPlayer->GetPlayerConnection();
	if (!pClientConn)
	{
		ERRORLOG("player client connection is NULL.");
		return;
	}
	if (!pClientConn->IsConnected())
	{
		ERRORLOG("player client connection=[" << pClientConn <<"] is disconnect.");
		return;
	}
	pPlayer->GetRoleTotalInfo(roleData);
	pPlayer->SetPlayerState(PLAYER_ONLINE);

	uint32_t ID = pPlayer->GetPlayerID();
	m_playerIdMap.insert(make_pair(pPlayer->GetPlayerID(), pPlayer));

	TRACELOG("Achieve player data, ID=[" << ID << "], ptname=[" << pPlayer->PtName() << "] " << strDesc);

	// 玩家数据可能已经被修改了
	roledata::PBRoleTotalInfo newRoleTotalData;
	pPlayer->SerializeToPB(newRoleTotalData);

	// 将数据返回给客户端
	_SendPlayerDataToClient(pClientConn, newRoleTotalData);
}

void PlayerMng::_SendPlayerDataToClient(IConnection* pClientConn, const roledata::PBRoleTotalInfo& roleData)
{
	if (!pClientConn || !pClientConn->IsConnected())
	{
		return;
	}
	ctos::ResponseRoleData roleDataResponse;
	roleDataResponse.mutable_roledata()->CopyFrom(roleData);
	string strMessage;
	BuildRequestProto<ctos::ResponseRoleData>(roleDataResponse, strMessage, ID_ACK_ResponseRoleData);
	
	pClientConn->SendMsg(strMessage.c_str(), strMessage.size());
	return;
}

/* 
	请求验证token : 玩家在登陆之后进入游戏，或者断开连接进入游戏时需要进行Token验证
	PS：玩家在每次网络链接断开后，重连的时候，都需要验证token，主要有2个原因
	(1) 保证对玩家进行操作的是受过安全校验的
	(2) 保证玩家使用的是新的网络连接
*/
void PlayerMng::_RequestVerifyToken(IConnection* pConn, MessageHeader* pMsgHeader)
{
	if (!pConn || !pMsgHeader)
	{
		return;
	}

	ctos::RequestVerifyToken verifyTokenReq;
	verifyTokenReq.ParseFromString(GetProtoData(pMsgHeader));

	Player* pPlayer = GetPlayer(verifyTokenReq.ptname());
	if (!pPlayer)
	{
		// 玩家数据不在内存中
		pPlayer = _InitPlayerInfo(verifyTokenReq.ptname(), pConn);
		m_tokenVerifyMng.VerifyToken(pPlayer, verifyTokenReq.token(), false);
		return;
	}
	if (!verifyTokenReq.reconnect())				// 如果不是重新连接的Token验证（说明就是再次登陆的token验证）
	{
		pPlayer->SetPlayerConnection(pConn);
		m_tokenVerifyMng.VerifyToken(pPlayer, verifyTokenReq.token(), false);
		return;
	}

	// 玩家重新连接的Token验证
	ctos::ResponseVerifyToken verifyTokenAck;
	if (!m_tokenVerifyMng.VerifyToken(pPlayer, verifyTokenReq.token()))
	{
		TRACELOG("verify token failed, token=[" << verifyTokenReq.token());
		verifyTokenAck.set_errcode(ERROR_VERIFY_TOKEN_FAIL);
	}
	else
	{
		m_clientConnMng.SetPlayerConnection(pPlayer, pConn);
	}
	
	string strMessage;
	BuildResponseProto<ctos::ResponseVerifyToken>(verifyTokenAck, strMessage, ID_ACK_ResponseVerifyToken);

	pConn->SendMsg(strMessage.c_str(), strMessage.size());
	return;
}

// 请求创建角色
void PlayerMng::_RequestCreateRole(IConnection* pConn, MessageHeader* pMsgHeader)
{
	if (!g_pDsSession)
	{
		return;
	}

	ctos::RequestCreateRole createRoleReq;
	createRoleReq.ParseFromString(GetProtoData(pMsgHeader));

	// 判断此链接是否已经被其他玩家使用了（同一个链接只支持一个玩家）
	if (m_clientConnMng.IsConnectionUsed(createRoleReq.ptname(), pConn))
	{
		TRACELOG("the connection has already been used by other player.");
		return;
	}

	gtod::SRequestCreateRole sCreateRoleReq;
	sCreateRoleReq.set_ptname(createRoleReq.ptname());
	sCreateRoleReq.set_rolename(createRoleReq.rolename());

	// 保存玩家连接信息
	Player* pPlayer = GetPlayer(createRoleReq.ptname());
	if (!pPlayer)
	{
		// 玩家数据不在内存中
		pPlayer = _InitPlayerInfo(createRoleReq.ptname(), pConn);
	}
	else
	{
		// 更新玩家数据
		m_clientConnMng.SetPlayerConnection(pPlayer, pConn);
		m_playerInfoMap.insert(make_pair(createRoleReq.ptname(), pPlayer));
	}

	// 发送消息
	string strMessage;
	BuildRequestProto<gtod::SRequestCreateRole>(sCreateRoleReq, strMessage, ID_SREQ_SRequestCreateRole);
	g_pDsSession->SendMsg(strMessage.c_str(), strMessage.size());
	return;
}

/*
	玩家请求角色数据
*/
void PlayerMng::_RequestRoleData(IConnection* pConn, MessageHeader* pMsgHeader)
{
	ctos::RequestRoleData roleDataReq;
	roleDataReq.ParseFromString(GetProtoData(pMsgHeader));

	TRACELOG("ptname=[" << roleDataReq.ptname() << "] request role data.");

	if (roleDataReq.ptname() == "")
	{
		TRACELOG("request role data, pt name is NULL");
		return;
	}

	// 获取角色数据
	GetPlayerData(pConn, roleDataReq.ptname());
}

void PlayerMng::_SResponseVerifyToken(IConnection* pConn, MessageHeader* pMsgHeader)
{
	login::SResponseVerifyToken verifyTokenResponse;
	verifyTokenResponse.ParseFromString(GetProtoData(pMsgHeader));
	TRACELOG("verify token response, ptname=[" << verifyTokenResponse.ptname() << "], ret=[" << verifyTokenResponse.errcode() << "] request role data.");

	Player* pPlayer = GetPlayer(verifyTokenResponse.ptname());
	if (!pPlayer)
	{
		ERRORLOG("verify token response, cannot find player ptname=[" << verifyTokenResponse.ptname() << "]");
		return;
	}

	ctos::ResponseVerifyToken verifyTokenAck;
	if (verifyTokenResponse.errcode() != ERROR_OP_SUCCESS)				// 验证Token失败
	{
		verifyTokenAck.set_errcode(verifyTokenResponse.errcode());
	}
	else
	{
		m_tokenVerifyMng.ServerVerifyBack(pPlayer, verifyTokenResponse.errcode());
	}

	string strMessage;
	BuildRequestProto<ctos::ResponseVerifyToken>(verifyTokenAck, strMessage, ID_ACK_ResponseVerifyToken);
	pPlayer->SendMsg(strMessage.c_str(), strMessage.size());
	return;
}

// 保存玩家数据
void PlayerMng::_SaveRoleData(Player* pPlayer)
{
	if (!pPlayer)
	{
		return;
	}
	gtod::SRequestSaveRoleData saveRoleData;
	roledata::PBRoleTotalInfo* pRoleTotalInfo = saveRoleData.mutable_roledata();

	// 增加玩家数据版本号
	pPlayer->IncreaseVersion();

	pPlayer->SerializeToPB(*pRoleTotalInfo);
	saveRoleData.set_ptname(pRoleTotalInfo->baseinfo().ptname());

	TRACELOG("save player data, ID=[" << pRoleTotalInfo->baseinfo().userid() << "], ptname=[" << pRoleTotalInfo->baseinfo().ptname() << "]");

#ifndef _MSC_VER
	// 保存到redis中
	string strRoleData;
	pRoleTotalInfo->SerializeToString(&strRoleData);
	string strSaveKey = KeyGen::GenRoleDataKey(pRoleTotalInfo->baseinfo().ptname());
	try
	{
		m_pRedisClient->set(strSaveKey, strRoleData);
	}
	catch(redis::redis_error& err)
	{
		ERRORLOG("redis save role data error=[" << err.what() << "]");
	}
#endif

	// 保存到DataServer
	string strMessage;
	BuildRequestProto<gtod::SRequestSaveRoleData>(saveRoleData, strMessage, ID_SREQ_SRequestSaveRoleData);
	g_pDsSession->SendMsg(strMessage.c_str(), strMessage.size());

#ifdef DEBUG_SERVER
	string strPrint;
	google::protobuf::TextFormat::PrintToString(saveRoleData, &strPrint);
	TRACELOG("save roledata proto:" << endl << strPrint);
#endif

	// 释放player
	if (pPlayer)
	{
		ReleasePlayer(pPlayer);
	}
	return;
}

void PlayerMng::_DeletePlayer(Player* pPlayer)
{
	m_playerInfoMap.erase(pPlayer->PtName());
	m_playerIdMap.erase(pPlayer->GetPlayerID());
}

/*
	参数说明:
	uExpAdd		增加的经验		IN
	uCurLevel	玩家当前等级		IN
	uCurExp		玩家当前经验		IN
	uNewLevel	玩家新的等级		OUT
	uNewExp		玩家新的经验		OUT
*/
void PlayerMng::AddPlayerExp(uint32_t uExpAdd, uint32_t uCurLevel, uint32_t uCurExp, uint32_t& uNewLevel, uint32_t& uNewExp)
{
	map<uint32_t, PlayerLevelConf>::iterator curLevelIt = m_playerLevelMap.find(uCurLevel);
	if (curLevelIt == m_playerLevelMap.end())
	{
		ERRORLOG("cannot find player curlevel=[" << uCurLevel << "]");
		return;
	}

	uNewLevel = uCurLevel;

	uint32_t uExpNeed = curLevelIt->second.uExpNeed;
	while (uExpAdd + uCurExp >= uExpNeed)				// 经验能够升级
	{
		uExpAdd -= (uExpNeed - uCurExp);				// 经验减少
		uCurExp = 0;
		if (++curLevelIt != m_playerLevelMap.end())
		{
			uExpNeed = curLevelIt->second.uExpNeed;
		}
		else											// 已经是最高等级
		{
			break;
		}
		++uNewLevel;									// 等级增加1级
	} 
	uCurExp += uExpAdd;
	uNewExp = uCurExp;

	return;
}

