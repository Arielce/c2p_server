#ifndef GAMESERVER_GMCOMMAND_H
#define GAMESERVER_GMCOMMAND_H

#include "header.h"

/*
	GM÷∏¡Ó
*/

class Player;
class GMCommand
{
public:
	void ProcGMCommand(const string& strCommand);	

private:
	void _AddGoods(Player* pPlayer, uint32_t uGoodsId, uint32_t uGoodsNum=1);
};

#endif