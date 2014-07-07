#include "PlayerDataMng.h"
#include "header.h"
#include "../protocol/RoleData.pb.h"
#include "../protocol/DataServer.pb.h"
#include "../protocol/DataProtocol.h"
#include "../protocol/ErrorCodes.h"
#include <boost/lexical_cast.hpp>
#include "GsConnectionMng.h"
#include "ServerConfig.h"


void PlayerDataMng::SetMysqlInfo(const char* szHost, int nPort, const char* szUser, const char* szPasswd, const char* szDb)
{
	m_strHostIp = szHost;
	m_uPort = nPort;
	m_strUser= szUser;
	m_strPasswd = szPasswd;
	m_strDB = szDb;
}

bool PlayerDataMng::Init()
{
	if (!m_sqlConn.Init(m_strHostIp.c_str(), m_uPort, m_strUser.c_str(), m_strPasswd.c_str(), m_strDB.c_str()))
	{
		ERRORLOG("init mysql connection failed, mysql ip=[" << m_strHostIp << "], port=[" << m_uPort << "], user=[" << m_strUser << "], pwd=[" << m_strPasswd << "], db=[" << m_strDB.c_str() << "]");
		return false;
	}

	if (!InitTables())
	{
		ERRORLOG("init create tables failed.");
		return false;
	}
	m_strAreaId = boost::lexical_cast<string>(gpServerConfig->GetAreaId());
	return true;
}

bool PlayerDataMng::InitTables()
{
	if (!m_sqlTables.CreatePlayerInfo())
	{
		ERRORLOG("create table playerinfo failed.");
		return false;
	}

	return true;
}

// 创建角色
void PlayerDataMng::CreateRole(const string& strPtName, const string& strRoleName)
{
	gtod::SResponseCreateRole createRoleAck;
	createRoleAck.set_ptname(strPtName);

	// 先检查ptname是否在表中已经有数据了
	string strSql = "select ptname from playerinfo where ptname='" + strPtName + "' and areaid=" + m_strAreaId;
	CRecordSet record;
	if (!m_sqlConn.Execute(strSql.c_str(), record))
	{
		ERRORLOG("execute sql=[" << strSql << "] failed. error=[" << m_sqlConn.GetErrInfo() << "]");
		return;
	}
	MYSQL_ROW row;
	record.FetchRow(row);
	if (row)							// 此pt已经存在
	{
		createRoleAck.set_errcode(ERROR_PTNAME_HAS_CREATE_ROLE);
	}
	else
	{
		CRecordSet queryRecord;			// 两个查询语句不能用一个record对象，否则有查询结果没被释放掉
		// 检查rolename是否已经使用过了
		string strQueryRole = "select rolename from playerinfo where rolename='" + strRoleName + "' and areaid=" + m_strAreaId;
		if (!m_sqlConn.Execute(strSql.c_str(), queryRecord))
		{
			ERRORLOG("execute sql=[" << strSql << "] failed. error=[" << m_sqlConn.GetErrInfo() << "]");
			return;
		}
		MYSQL_ROW queryRow;
		queryRecord.FetchRow(queryRow);
		if (queryRow)						// 此角色名已经存在
		{
			createRoleAck.set_errcode(ERROR_ROLENAME_EXIST);
		}
		CreateNewPlayer(strPtName, strRoleName);
	}

	string strMessage;
	BuildRequestProto<gtod::SResponseCreateRole>(createRoleAck, strMessage, ID_SACK_SResponseCreateRole);
	gpGsConnMng->SendMsgToGS(strMessage.c_str(), strMessage.size());
	return;
}

// 获取玩家数据
void PlayerDataMng::GetPlayerData(const string& strPtName)
{
	string strSql = "select * from playerinfo where ptname='" + strPtName + "' and areaid=" + m_strAreaId;
	CRecordSet record;
	if (!m_sqlConn.Execute(strSql.c_str(), record))
	{
		ERRORLOG("execute sql=[" << strSql << "] failed. error=[" << m_sqlConn.GetErrInfo() << "]");
		return;
	}
	TRACELOG("pt ptname=[" << strPtName << "] request get playerdata");

	MYSQL_ROW row;
	record.FetchRow(row);

	roledata::PBRoleTotalInfo roleTotalInfo;
	roledata::PBRoleBaseInfo* pRoleBaseInfo = roleTotalInfo.mutable_baseinfo();
	roledata::PBRoleBag* pRoleBagInfo = roleTotalInfo.mutable_baginfo();

	if (!row)
	{
		//CreateNewPlayer(strPtName, *pRoleBaseInfo);
		ERRORLOG("cannot find ptname=[" << strPtName << "] in playerinfo table");
	}
	else
	{
		unsigned long *lengths = mysql_fetch_lengths(record.MysqlRes());
		uint32_t uUserId = boost::lexical_cast<uint32_t>(row[0]);
		string strRoleData(row[10], lengths[10]);
		pRoleBaseInfo->ParseFromString(strRoleData);
		pRoleBaseInfo->set_userid(uUserId);

		if (row[11])
		{
			pRoleBagInfo->ParseFromString(string(row[11], lengths[11]));
		}
		TRACELOG("Get Player Data id=[" << uUserId << "], ptname=[" << strPtName << "]");
	}
	
	gtod::SResponseRoleData roleDataResponse;
	roleDataResponse.mutable_roledata()->CopyFrom(roleTotalInfo);
	string strMessage;
	BuildRequestProto<gtod::SResponseRoleData>(roleDataResponse, strMessage, ID_SACK_SResponseGetRoleData);
	gpGsConnMng->SendMsgToGS(strMessage.c_str(), strMessage.size());

	string strPrint;
	google::protobuf::TextFormat::PrintToString(roleDataResponse, &strPrint);
	TRACELOG("get role proto:" << endl << strPrint);

	return;
}

bool PlayerDataMng::CreateNewPlayer(const string& strPtName, const string& strRoleName)
{
	try
	{
		roledata::PBRoleBaseInfo roleBaseInfo;
		roleBaseInfo.set_ptname(strPtName);
		roleBaseInfo.set_rolename(strRoleName);

		string strRoleData;
		roleBaseInfo.SerializeToString(&strRoleData);

		string strPrint;
		google::protobuf::TextFormat::PrintToString(roleBaseInfo, &strPrint);
		TRACELOG("create role proto:" << endl << strPrint);

		int nEscapeLen = mysql_real_escape_string(m_sqlConn.Mysql(), m_escapeBuf, strRoleData.c_str(), strRoleData.size());
		string strInsertSql = "insert into playerinfo(areaid, ptname, rolename, playerbase) values(" + m_strAreaId + ", '" + strPtName + "', '" + strRoleName + "', '" + string(m_escapeBuf, nEscapeLen) + "')";

		if (!m_sqlConn.Execute(strInsertSql.c_str()))
		{
			ERRORLOG("execute sql failed. error=[" << m_sqlConn.GetErrInfo() << "]");
			return false;
		}

		// 从mysql中查出玩家的ID
		CRecordSet record;
		string strQueryId = "select *from playerinfo where ptname='" + strPtName +  "' and areaid=" + m_strAreaId;
		if (!m_sqlConn.Execute(strQueryId.c_str(), record))
		{
			ERRORLOG("execute sql failed. error=[" << m_sqlConn.GetErrInfo() << "]");
			return false;
		}
		MYSQL_ROW row;
		record.FetchRow(row);
		if (!row)				// 没有记录
		{
			ERRORLOG("cannot find the player id in mysql, pt name=[" << strPtName << "]");
			return false;
		}

		uint32_t uUserId = boost::lexical_cast<uint32_t>(row[0]);
		roleBaseInfo.set_userid(uUserId);

		TRACELOG("Create Player data, id=[" << uUserId << "], pt name=[" << strPtName << "]");
	}
	catch (google::protobuf::FatalException fe)
	{
		ERRORLOG("protobuf excetpion error=[" << fe.message() << "]");
	}

	return true;
}

void PlayerDataMng::SavePlayerData(const string& strPtName, const roledata::PBRoleTotalInfo& roleTotalInfo)
{
	try
	{
		string strPrint;
		google::protobuf::TextFormat::PrintToString(roleTotalInfo, &strPrint);
		TRACELOG("save roledata proto:" << endl << strPrint);

		const roledata::PBRoleBaseInfo& roleBaseInfo = roleTotalInfo.baseinfo();
		string strRoleData;
		roleBaseInfo.SerializeToString(&strRoleData);

		const roledata::PBRoleBag& roleBag = roleTotalInfo.baginfo();
		string strRoleBag;
		roleBag.SerializeToString(&strRoleBag);

		int nEscapeLen = mysql_real_escape_string(m_sqlConn.Mysql(), m_escapeBuf, strRoleData.c_str(), strRoleData.size());
		string strPlayerBase = string(m_escapeBuf, nEscapeLen);

		nEscapeLen = mysql_real_escape_string(m_sqlConn.Mysql(), m_escapeBuf, strRoleBag.c_str(), strRoleBag.size());
		string strPlayerBag = string(m_escapeBuf, nEscapeLen);

		string strSaveDataSql = "update playerinfo set level=" + boost::lexical_cast<string>(roleBaseInfo.level()) 
			+ ", dataversion=" + boost::lexical_cast<string>(roleBaseInfo.dataversion())
			+ ", exp=" + boost::lexical_cast<string>(roleBaseInfo.exp())
			+ ", gold=" + boost::lexical_cast<string>(roleBaseInfo.gold())
			+ ", diamond=" + boost::lexical_cast<string>(roleBaseInfo.diamond())
			+ ", playerbase='" + strPlayerBase + "'"
			+ ", playerbag='" + strPlayerBag + "' where ptname='" + strPtName +  "' and areaid=" + m_strAreaId;

		TRACELOG("Save Player data, id=[" << roleBaseInfo.userid() << "], pt name=[" << strPtName << "]");

		//boost::timer timer;
		if (!m_sqlConn.Execute(strSaveDataSql.c_str()))
		{
			ERRORLOG("execute sql failed. error=[" << m_sqlConn.GetErrInfo() << "]");
			return;
		}
	}
	catch (google::protobuf::FatalException fe)
	{
		ERRORLOG("protobuf excetpion error=[" << fe.message() << "]");
	}

	//TRACELOG("save sql, time cost=[" << timer.elapsed() << "]");
	return;
}

void PlayerDataMng::GetDataVersion(const string& strPtName)
{
	string strQuerySql = "select dataversion from playerinfo where ptname='" + strPtName +  "' and areaid=" + m_strAreaId;
	CRecordSet record;
	if (!m_sqlConn.Execute(strQuerySql.c_str(), record))
	{
		ERRORLOG("execute sql=[" << strQuerySql << "] failed. error=[" << m_sqlConn.GetErrInfo() << "]");
		return;
	}

	gtod::SResponseRoleDataVersion dataVersionAck;
	dataVersionAck.set_ptname(strPtName);

	MYSQL_ROW row;
	record.FetchRow(row);
	if (!row)
	{
		dataVersionAck.set_errcode(ERROR_PLAYER_NOT_FOUND);
	}
	else
	{
		unsigned long *lengths = mysql_fetch_lengths(record.MysqlRes());
		uint32_t uDataVersion = boost::lexical_cast<uint32_t>(row[0]);
		dataVersionAck.set_dataversion(uDataVersion);
	}

	string strMessage;
	BuildRequestProto<gtod::SResponseRoleDataVersion>(dataVersionAck, strMessage, ID_SACK_SResponseRoleDataVersion);
	gpGsConnMng->SendMsgToGS(strMessage.c_str(), strMessage.size());
	return;
}