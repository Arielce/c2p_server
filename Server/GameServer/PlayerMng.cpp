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

	// ����������Ҫ��Token��֤
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
	pPlayer->SetHasVerifyFromServer();								// �����Ѿ��ӷ�������֤��Token
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

// ��ʱ�ж��Ƿ���Ҫ��������߼�
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
	m_clientConnMng.SetPlayerConnection(pPlayer, pConn);				// ������Ҷ�Ӧ����������
	m_playerInfoMap.insert(make_pair(strPtName, pPlayer));				// �������pt������ҵĶ�Ӧ��ϵ
	return pPlayer;
}

void PlayerMng::_SaveOnlinePlayer(uint32_t uFlag)
{
	bool bStopServer = false;
	if (uFlag & 0x1)													// �ж��Ƿ�Ϊͣ������
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

		if (pPlayer->PlayerLeaveTimes() < 1000 && !bStopServer)							// ���û���뿪̫��ʱ�䣬���Ҳ���ֹͣ������
		{
			playerIt++;
			continue;
		}

		m_playerIdMap.erase(playerIt++);
		m_playerInfoMap.erase(pPlayer->PtName());

		pPlayer->SetPlayerState(PLAYER_OFFLINE);
		// �����������
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

		// ��ȡ��ʼӢ���б�
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

// ��ȡ���������
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

// �������е��������ڲ����д���
void PlayerMng::ProcReq(IConnection* pConn, MessageHeader* pMsgHeader)
{
	if (!pConn || !pMsgHeader)
	{
		return;
	}
	switch (pMsgHeader->uMsgCmd)
	{
	case ID_REQ_RequestVerifyToken:			// ������֤token
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
	case ID_REQ_RequestCreateRole:			// ���󴴽���ɫ
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
	case ID_REQ_RequestRoleData:			// �����ɫ����
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
	case ID_SACK_SResponseVerifyToken:		// ��֤Token�������
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
	if (!pPlayer || !pPlayer->IsPlayerDataReady())				// ��ҽ�ɫ���ݻ�û���
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

// �ͻ��˶Ͽ�����
void PlayerMng::ClientDisconnect(IConnection* pConnection)
{
	m_clientConnMng.ClientDisconnect(pConnection);
	return;
}

/* 
	desc: ��ȡ��ɫ����
	��ɫ���ݿ��ܴ�����GameServer�Ļ���֮�У�
	������ڣ���ȥredis�����в��ң�
	���Ҳ���ڣ���ȥmysql���ݿ��в���
*/
void PlayerMng::GetPlayerData(IConnection* pConnection, const string& strPtName)
{
	Player* pPlayer = NULL;
	roledata::PBRoleTotalInfo roleData;

	// �жϴ������Ƿ��Ѿ����������ʹ���ˣ�ͬһ������ֻ֧��һ����ң�
	if (m_clientConnMng.IsConnectionUsed(strPtName, pConnection))
	{
		TRACELOG("the connection has already been used by other player, ptname=[" << strPtName << "]");
		return;
	}

	// ���������ߣ���ô��ֱ�Ӵ��ڴ��л�ȡ�������
	if (IsPlayerOnline(strPtName))
	{
		pPlayer = GetPlayer(strPtName);
		if (!pPlayer)
		{
			ERRORLOG("get player failed, pt name=[" << strPtName << "]");
			return;
		}
		
		// �����������֯��PB��ʽ
		pPlayer->SerializeToPB(roleData);
		
		pPlayer->SetPlayerConnection(pConnection);
		m_clientConnMng.SetPlayerConnection(pPlayer, pConnection);			// ����������Ҷ�Ӧ����������
		
		// �Ѿ���ȡ��������
		AchievePlayerData(roleData, "Player In mem");
		return;
	}

	pPlayer = GetPlayer(strPtName);
	if (!pPlayer)
	{
		// ������ݲ����ڴ���
		pPlayer = _InitPlayerInfo(strPtName, pConnection);
	}
	else 
	{
		// �����������
		m_clientConnMng.SetPlayerConnection(pPlayer, pConnection);
		m_playerInfoMap.insert(make_pair(strPtName, pPlayer));
	}
	
	if (pPlayer->State() == PLAYER_FETCHING_DATA)			// �������ȡ������
	{
		TRACELOG("player rolename=[" << strPtName << "] is in state PLAYER_FETCHING_DATA");
		return;
	}
	
	m_playerDataGetter.GetPlayerData(pPlayer);									// ������;����ȡ�������(redis, ����mysql)
	return;
}

// ��ȡ����ɫ����֮�󣬻ص��˺���
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

	// ������ݿ����Ѿ����޸���
	roledata::PBRoleTotalInfo newRoleTotalData;
	pPlayer->SerializeToPB(newRoleTotalData);

	// �����ݷ��ظ��ͻ���
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
	������֤token : ����ڵ�½֮�������Ϸ�����߶Ͽ����ӽ�����Ϸʱ��Ҫ����Token��֤
	PS�������ÿ���������ӶϿ���������ʱ�򣬶���Ҫ��֤token����Ҫ��2��ԭ��
	(1) ��֤����ҽ��в��������ܹ���ȫУ���
	(2) ��֤���ʹ�õ����µ���������
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
		// ������ݲ����ڴ���
		pPlayer = _InitPlayerInfo(verifyTokenReq.ptname(), pConn);
		m_tokenVerifyMng.VerifyToken(pPlayer, verifyTokenReq.token(), false);
		return;
	}
	if (!verifyTokenReq.reconnect())				// ��������������ӵ�Token��֤��˵�������ٴε�½��token��֤��
	{
		pPlayer->SetPlayerConnection(pConn);
		m_tokenVerifyMng.VerifyToken(pPlayer, verifyTokenReq.token(), false);
		return;
	}

	// ����������ӵ�Token��֤
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

// ���󴴽���ɫ
void PlayerMng::_RequestCreateRole(IConnection* pConn, MessageHeader* pMsgHeader)
{
	if (!g_pDsSession)
	{
		return;
	}

	ctos::RequestCreateRole createRoleReq;
	createRoleReq.ParseFromString(GetProtoData(pMsgHeader));

	// �жϴ������Ƿ��Ѿ����������ʹ���ˣ�ͬһ������ֻ֧��һ����ң�
	if (m_clientConnMng.IsConnectionUsed(createRoleReq.ptname(), pConn))
	{
		TRACELOG("the connection has already been used by other player.");
		return;
	}

	gtod::SRequestCreateRole sCreateRoleReq;
	sCreateRoleReq.set_ptname(createRoleReq.ptname());
	sCreateRoleReq.set_rolename(createRoleReq.rolename());

	// �������������Ϣ
	Player* pPlayer = GetPlayer(createRoleReq.ptname());
	if (!pPlayer)
	{
		// ������ݲ����ڴ���
		pPlayer = _InitPlayerInfo(createRoleReq.ptname(), pConn);
	}
	else
	{
		// �����������
		m_clientConnMng.SetPlayerConnection(pPlayer, pConn);
		m_playerInfoMap.insert(make_pair(createRoleReq.ptname(), pPlayer));
	}

	// ������Ϣ
	string strMessage;
	BuildRequestProto<gtod::SRequestCreateRole>(sCreateRoleReq, strMessage, ID_SREQ_SRequestCreateRole);
	g_pDsSession->SendMsg(strMessage.c_str(), strMessage.size());
	return;
}

/*
	��������ɫ����
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

	// ��ȡ��ɫ����
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
	if (verifyTokenResponse.errcode() != ERROR_OP_SUCCESS)				// ��֤Tokenʧ��
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

// �����������
void PlayerMng::_SaveRoleData(Player* pPlayer)
{
	if (!pPlayer)
	{
		return;
	}
	gtod::SRequestSaveRoleData saveRoleData;
	roledata::PBRoleTotalInfo* pRoleTotalInfo = saveRoleData.mutable_roledata();

	// ����������ݰ汾��
	pPlayer->IncreaseVersion();

	pPlayer->SerializeToPB(*pRoleTotalInfo);
	saveRoleData.set_ptname(pRoleTotalInfo->baseinfo().ptname());

	TRACELOG("save player data, ID=[" << pRoleTotalInfo->baseinfo().userid() << "], ptname=[" << pRoleTotalInfo->baseinfo().ptname() << "]");

#ifndef _MSC_VER
	// ���浽redis��
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

	// ���浽DataServer
	string strMessage;
	BuildRequestProto<gtod::SRequestSaveRoleData>(saveRoleData, strMessage, ID_SREQ_SRequestSaveRoleData);
	g_pDsSession->SendMsg(strMessage.c_str(), strMessage.size());

#ifdef DEBUG_SERVER
	string strPrint;
	google::protobuf::TextFormat::PrintToString(saveRoleData, &strPrint);
	TRACELOG("save roledata proto:" << endl << strPrint);
#endif

	// �ͷ�player
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
	����˵��:
	uExpAdd		���ӵľ���		IN
	uCurLevel	��ҵ�ǰ�ȼ�		IN
	uCurExp		��ҵ�ǰ����		IN
	uNewLevel	����µĵȼ�		OUT
	uNewExp		����µľ���		OUT
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
	while (uExpAdd + uCurExp >= uExpNeed)				// �����ܹ�����
	{
		uExpAdd -= (uExpNeed - uCurExp);				// �������
		uCurExp = 0;
		if (++curLevelIt != m_playerLevelMap.end())
		{
			uExpNeed = curLevelIt->second.uExpNeed;
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

