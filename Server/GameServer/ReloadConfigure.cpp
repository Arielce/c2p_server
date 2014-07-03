#include "ReloadConfigure.h"
#include "GameServer.h"
#include "PlayerMng.h"
#include "LobbyHandler.h"
#include "GateController.h"
#include "HeroMng.h"
#include "GoodsMng.h"
#include "DrawPrizeMng.h"

// 重载所有游戏配置文件，不包括gs.xml这种系统启动配置
bool ConfigureReloador::ReloadConf(const char* pFileName)
{
	string strFileName;
	bool bLoadAll = false;
	if (pFileName)
	{
		strFileName = pFileName;
	}
	else
	{
		bLoadAll = true;
	}

	if ((strFileName == "InitPlayerData.xml" || bLoadAll) && !gpPlayerMng->LoadPlayerInitConf())
	{
		return false;
	}
	else if ((strFileName == "PlayerLevel.xml" || bLoadAll) && !gpPlayerMng->LoadPlayerLevelConf())
	{
		return false;
	}
	else if ((strFileName == "Goods.xml" || bLoadAll) && !gpGoodsMng->LoadGoodsConf())
	{
		return false;
	}
	else if ((strFileName == "EquipCompound.xml" || bLoadAll) && !gpGoodsMng->LoadEquipCompound())
	{
		return false;
	}
	else if ((strFileName == "BattleGate.xml" || bLoadAll) && !gpGateController->LoadGatePrizePool())
	{
		return false;
	}
	else if ((strFileName == "GatePrizePool.xml" || bLoadAll) && !gpGateController->LoadGatePrizePool())
	{
		return false;
	}
	else if ((strFileName == "Hero.xml" || bLoadAll) && !gpHeroMng->LoadHeroConf())
	{
		return false;
	}
	else if ((strFileName == "HeroUpgrade.xml" || bLoadAll) && !gpHeroMng->LoadHeroUpgrade())
	{
		return false;
	}
	else if ((strFileName == "DrawPrize.xml" || bLoadAll) && !gpDrawPrizeMng->LoadDrawPrzieConf())
	{
		return false;
	}
	

	return true;
}