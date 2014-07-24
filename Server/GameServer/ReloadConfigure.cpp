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

	try
	{
		if ((strFileName == "InitPlayerData.xml" || bLoadAll) && !gpPlayerMng->LoadPlayerInitConf())
		{
			ERRORLOG("load InitPlayerData.xml failed.");
			return false;
		}
		else if ((strFileName == "PlayerLevel.xml" || bLoadAll) && !gpPlayerMng->LoadPlayerLevelConf())
		{
			ERRORLOG("load PlayerLevel.xml failed.");
			return false;
		}
		else if ((strFileName == "Goods.xml" || bLoadAll) && !gpGoodsMng->LoadGoodsConf())
		{
			ERRORLOG("load Goods.xml failed.");
			return false;
		}
		else if ((strFileName == "EquipCompound.xml" || bLoadAll) && !gpGoodsMng->LoadEquipCompound())
		{
			ERRORLOG("load EquipCompound.xml failed.");
			return false;
		}
		else if ((strFileName == "BattleGate.xml" || bLoadAll) && !gpGateController->LoadGatePrizePool())
		{
			ERRORLOG("load BattleGate.xml failed.");
			return false;
		}
		else if ((strFileName == "GatePrizePool.xml" || bLoadAll) && !gpGateController->LoadGatePrizePool())
		{
			ERRORLOG("load GatePrizePool.xml failed.");
			return false;
		}
		else if ((strFileName == "Hero.xml" || bLoadAll) && !gpHeroMng->LoadHeroConf())
		{
			ERRORLOG("load Hero.xml failed.");
			return false;
		}
		else if ((strFileName == "HeroUpgrade.xml" || bLoadAll) && !gpHeroMng->LoadHeroUpgrade())
		{
			ERRORLOG("load HeroUpgrade.xml failed.");
			return false;
		}
		else if ((strFileName == "DrawPrize.xml" || bLoadAll) && !gpDrawPrizeMng->LoadDrawPrzieConf())
		{
			ERRORLOG("load DrawPrize.xml failed.");
			return false;
		}
		else
		{
			ERRORLOG("unknown file to be reloading, filename=[" << strFileName << "]");
		}

	}
	catch(boost::bad_lexical_cast& error)
	{
		ERRORLOG("reload configure failed, error=[" << error.what() << "], file name=[" << strFileName << "]");
		return false;
	}

	return true;
}