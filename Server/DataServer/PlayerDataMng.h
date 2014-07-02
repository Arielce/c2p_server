#ifndef	DATASERVER_PLAYERDATAMNG_H
#define DATASERVER_PLAYERDATAMNG_H

#include "../network/Utility.h"
#include <string>
#include "SqlTables.h"
#include "Mysql.h"
#include "../network/IConnection.h"
#include "../protocol/RoleData.pb.h"
using namespace std;

#define MAX_BLOB_SIZE 65*1024

class PlayerDataMng
{
public:
	PlayerDataMng() : m_sqlTables(m_sqlConn)
	{

	}

	static PlayerDataMng* GetInstance()
	{
		static PlayerDataMng instance;
		return &instance;
	}

	void SetMysqlInfo(const char* szHost, int nPort, const char* szUser, const char* szPasswd, const char* szDb);
	bool Init();

	void CreateRole(const string& strPtName, const string& strRoleName);
	void GetPlayerData(const string& strPtName);
	void SavePlayerData(const string& strPtName, const roledata::PBRoleTotalInfo& roleTotalInfo);
	void GetDataVersion(const string& strPtName);

private:
	bool InitTables(); 
	bool CreateNewPlayer(const string& strPtName, const string& strRoleName);

private:
	CMysqlConnection m_sqlConn;
	SqlTables m_sqlTables;

	string m_strHostIp;
	uint32_t m_uPort;
	string m_strUser;
	string m_strPasswd;
	string m_strDB;
	string m_strAreaId;

	char m_escapeBuf[MAX_BLOB_SIZE];
};

#define gpPlayerDataMng PlayerDataMng::GetInstance()

#endif