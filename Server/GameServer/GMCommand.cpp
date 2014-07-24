#include "GMCommand.h"
#include "Player.h"
#include "PlayerMng.h"

void GMCommand::ProcGMCommand(const string& strCommand)
{
	vector<string> cmdVec;
	boost::split(cmdVec, strCommand, boost::is_any_of(" "));

	if (cmdVec[0] == "@addgoods")					// 增加物品 @addgoods rolename goodsid goodsnum
	{
		if (cmdVec.size() < 3)
		{
			return;
		}
		Player* pPlayer = gpPlayerMng->GetPlayer(cmdVec[1]);
		if (!pPlayer)
		{
			return;
		}

		uint32_t uGoodsNum = 1;				// 默认添加一个
		if (cmdVec.size() == 4)
		{
			uGoodsNum = boost::lexical_cast<uint32_t>(cmdVec[3]);
		}
		_AddGoods(pPlayer, boost::lexical_cast<uint32_t>(cmdVec[2]), uGoodsNum);
	}
	else if (cmdVec[0] == "@addexp")				// 增加玩家经验 @addexp rolename expadd
	{
		if (cmdVec.size() < 3)
		{
			return;
		}
		Player* pPlayer = gpPlayerMng->GetPlayer(cmdVec[1]);
		if (!pPlayer)
		{
			return;
		}
		uint32_t uExpAdd = boost::lexical_cast<uint32_t>(cmdVec[2]);
		pPlayer->AddExp(uExpAdd);
		TRACELOG("player ptname=[" << pPlayer->PtName() << "] add gold=[" << uExpAdd << "]");
	}
	else if (cmdVec[0] == "@addgold")				// 增加玩家金币 @addgold rolename goldadd
	{
		if (cmdVec.size() < 3)
		{
			return;
		}
		Player* pPlayer = gpPlayerMng->GetPlayer(cmdVec[1]);
		if (!pPlayer)
		{
			return;
		}
		uint32_t uGoldAdd = boost::lexical_cast<uint32_t>(cmdVec[2]);
		pPlayer->AddGold(uGoldAdd);
		TRACELOG("player ptname=[" << pPlayer->PtName() << "] add gold=[" << uGoldAdd << "]");
	}
	else if (cmdVec[0] == "@adddiamond")			// 增加玩家钻石 @adddiamond rolename diamondadd
	{
		if (cmdVec.size() < 3)
		{
			return;
		}
		Player* pPlayer = gpPlayerMng->GetPlayer(cmdVec[1]);
		if (!pPlayer)
		{
			return;
		}
		uint32_t uDiamondAdd = boost::lexical_cast<uint32_t>(cmdVec[2]);
		pPlayer->AddDiamond(uDiamondAdd);
		TRACELOG("player ptname=[" << pPlayer->PtName() << "] add diamond=[" << uDiamondAdd << "]");
	}
}

void GMCommand::_AddGoods(Player* pPlayer, uint32_t uGoodsId, uint32_t uGoodsNum/* =1 */)
{
	if (!pPlayer)
	{
		return;
	}

	Goods goods;
	goods.uId = uGoodsId;
	goods.uNum = uGoodsNum;
	pPlayer->AddGoodsIntoBag(goods);

	return;
}