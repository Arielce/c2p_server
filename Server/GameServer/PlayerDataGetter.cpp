#include "PlayerDataGetter.h"
#include "../protocol/DataServer.pb.h"
#include "../network/Utility.h"
#include "PlayerMng.h"
#include "../protocol/DataProtocol.h"
#include "../protocol/ErrorCodes.h"
#include "ServerConfig.h"
#include "KeyGen.h"


void PlayerDataGetter::GetPlayerData(Player* pPlayer)
{
	// �������״̬Ϊ��ȡ������
	pPlayer->SetPlayerState(PLAYER_FETCHING_DATA);

	// ��redis�л�ȡ�����������, �����ȡ�����ʹ�mysql�л�ȡ����
	if (m_redisDataGetter.IsDataExistInRedis(pPlayer))
	{
		return;
	}
	m_mysqlDataGetter.GetDataFromMysql(pPlayer);
	return;
}

void PlayerDataGetter::DataBackFromDS(const roledata::PBRoleTotalInfo& roleTotalInfo)
{
	gpPlayerMng->AchievePlayerData(roleTotalInfo, "Player in Mysql");
}

void PlayerDataGetter::DataVersionBackFromDS(const gtod::SResponseRoleDataVersion& dataVersionAck)
{
	Player* pPlayer = gpPlayerMng->GetPlayer(dataVersionAck.ptname());
	if (!pPlayer)
	{
		ERRORLOG("cannot find ptname=[" << dataVersionAck.ptname() << "] in gameserver");
		return;
	}
	if (dataVersionAck.errcode() == ERROR_OP_SUCCESS 
		&& m_redisDataGetter.GetDataFromRedis(pPlayer, dataVersionAck.dataversion()))
	{
		return;
	}
	m_mysqlDataGetter.GetDataFromMysql(pPlayer);
	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RedisDataGetter::RedisDataGetter()
{
#ifndef _MSC_VER
	m_pRedisClient = new redis::client(gpServerConfig->GetRedisIp(), gpServerConfig->GetRedisPort(), gpServerConfig->GetRedisIndex());
#endif
}

bool RedisDataGetter::IsDataExistInRedis(Player* pPlayer)
{
#ifndef _MSC_VER				// windows�²���ʹ��redisclient
	if (!m_pRedisClient)
	{
		return false;
	}
	try
	{
		const string& strPtName = pPlayer->PtName();
		string strPtKey = KeyGen::GenRoleDataKey(strPtName);
		if (!m_pRedisClient->exists(strPtKey))
		{
			return false;
		}
		_GetDataVersionFromDS(strPtName);
		return true;
	}
	catch(redis::redis_error& error)
	{
		ERRORLOG("get data from redis exception, error=[" << error.what() << "]");
		return false;
	}
#else
	return false;
#endif
}

bool RedisDataGetter::GetDataFromRedis(Player* pPlayer, uint32_t uDataVersion)
{
#ifndef _MSC_VER				// windows�²���ʹ��redisclient
	if (!m_pRedisClient)
	{
		return false;
	}
	try
	{
		const string& strPtName = pPlayer->PtName();
		string strRoleKey = KeyGen::GenRoleDataKey(strPtName);
		if (!m_pRedisClient->exists(strRoleKey))
		{
			return false;
		}
		string strRoleData = m_pRedisClient->get(strRoleKey);
		roledata::PBRoleTotalInfo roleTotalInfo;
		roleTotalInfo.ParseFromString(strRoleData);

		// ��Ҵ�redis�л�ȡ������֮�󣬴�mysql�м����ҵ����ݰ汾�Ƿ�һ�£������һ�£���mysql������Ϊ׼
		if (!_CheckRoleDataVersion(roleTotalInfo.baseinfo().dataversion(), uDataVersion))
		{
			ERRORLOG("player pt name=[" << strPtName << "] dataversion error, redis version=[" << roleTotalInfo.baseinfo().dataversion() << "], DB version=[" << uDataVersion << "]");
			return false;
		}
		gpPlayerMng->AchievePlayerData(roleTotalInfo, "Player In Redis");
	}
	catch(redis::redis_error& error)
	{
		ERRORLOG("get data from redis exception, error=[" << error.what() << "]");
		return false;
	}
	
#else
	return false;
#endif
	return true;
}

bool RedisDataGetter::_CheckRoleDataVersion(uint32_t uRedisVersion, uint32_t uDBVersion)
{
	if (uRedisVersion == uDBVersion)
	{
		return true;
	}
	return false;
}

void RedisDataGetter::_GetDataVersionFromDS(const string& strPtName)
{
	gtod::SRequestRoleDataVersion dataVersionReq;
	dataVersionReq.set_ptname(strPtName);

	string strMessage;
	BuildRequestProto<gtod::SRequestRoleDataVersion>(dataVersionReq, strMessage, ID_SREQ_SRequestRoleDataVersion);
	g_pDsSession->SendMsg(strMessage.c_str(), strMessage.size());
	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MysqlDataGetter::GetDataFromMysql(Player* pPlayer)
{
	if (!g_pDsSession)
	{
		return;
	}

	gtod::SRequestRoleData roleDataReq;
	roleDataReq.set_ptname(pPlayer->PtName());

	string strMessage;
	BuildRequestProto<gtod::SRequestRoleData>(roleDataReq, strMessage, ID_SREQ_SRequestGetRoleData);
	g_pDsSession->SendMsg(strMessage.c_str(), strMessage.size());
	return;
}