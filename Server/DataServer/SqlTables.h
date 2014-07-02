#ifndef	DATASEVER_SQLTABLES_H
#define DATASEVER_SQLTABLES_H

#include "header.h"
#include "Mysql.h"
#include <iostream>
using namespace std;

class SqlTables
{
public:
	SqlTables(CMysqlConnection& sqlConn) : m_pSqlConn(&sqlConn)
	{

	}
	bool CreatePlayerInfo()
	{
		const char* pPlayerInfoTable = " \
								 CREATE TABLE IF NOT EXISTS playerinfo( \
								 id			int(16)		NOT NULL primary key auto_increment, \
								 areaid		int(4)		NOT NULL default 0, \
								 ptname		varchar(24) NOT NULL default '', \
								 rolename	varchar(23) NOT NULL default '', \
								 dataversion int(16)	NOT NULL default 0, \
								 level		int(16)		NOT NULL default 0, \
								 exp		int(16)		NOT NULL default 0, \
								 gold		int(16)		NOT NULL default 0,	\
								 diamond	int(16)		NOT NULL default 0,	\
								 ap			int(16)		NOT NULL default 0, \
								 playerbase blob,		\
								 playerbag	blob,		\
								 INDEX rolename_index (rolename), \
								 INDEX ptname_index (ptname) \
								 )";

		if (!m_pSqlConn->Execute(pPlayerInfoTable))
		{
			ERRORLOG("create table ptinfo failed. error msg:" << m_pSqlConn->GetErrInfo());
			return false; 
		}
		return true;
	}

private:
	CMysqlConnection* m_pSqlConn;
};

#endif