#ifndef GAMESERVER_PLAYERDATAGETTER_H
#define GAMESERVER_PLAYERDATAGETTER_H

#include "header.h"
#include "../protocol/RoleData.pb.h"
#include "../protocol/DataServer.pb.h"
#ifndef _MSC_VER
#include "redis/redisclient.h"
#endif // !1


class Player;
// 从redis获取角色数据
class RedisDataGetter
{
public:
	RedisDataGetter();
	bool IsDataExistInRedis(Player* pPlayer);
	bool GetDataFromRedis(Player* pPlayer, uint32_t uVersion);

private:
	bool _CheckRoleDataVersion(uint32_t uRedisVersion, uint32_t uDBVersion);
	void _GetDataVersionFromDS(const string& strPtName);

private:
#ifndef _MSC_VER
	redis::client* m_pRedisClient;
#endif
};

// 从mysql获取角色数据
class MysqlDataGetter
{
public:
	void GetDataFromMysql(Player* pPlayer);
	
};

class PlayerDataGetter
{
public:
	void GetPlayerData(Player* pPlayer);
	void DataBackFromDS(const roledata::PBRoleTotalInfo& roleTotalInfo);
	void DataVersionBackFromDS(const gtod::SResponseRoleDataVersion& dataVersionAck);
private:

	RedisDataGetter m_redisDataGetter;
	MysqlDataGetter m_mysqlDataGetter;
};

#endif