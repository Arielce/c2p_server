#ifndef GAMESERVER_GOODSMNG_H
#define GAMESERVER_GOODSMNG_H

#include "header.h"
#include "Goods.h"

typedef struct tagCompoundConf
{
	uint32_t uCompoundId;			// 合成Id
	uint32_t uGoldNeed;				// 需要的金币数量
	uint32_t uScrollId;				// 卷轴ID
	struct EquipNeed
	{
		uint32_t uEquipId;			// 装备ID
		uint32_t uEquipNum;			// 装备数量
	};
	vector<EquipNeed> equipNeedVec;	// 需要的装备列表
}CompoundConf;

class Player;
class GoodsMng
{
public:
	static GoodsMng* GetInstance()
	{
		static GoodsMng instance;
		return &instance;
	}

	bool LoadGoodsConf();
	bool LoadEquipCompound();
	bool GetEquipProp(uint32_t uEquipId, EquipProp& equipProp);

	int32_t CompoundEquip(Player* pPlayer, uint32_t uTargetEquipId);

private:
	GoodsMng();

private:
	map<uint32_t, bool> m_totalMap;											// 所有物品列表
	map<uint32_t, HeroExpMedicineProp> m_heroExpMedicineMap;				// 经验药水属性列表
	map<uint32_t, EquipProp> m_equipMap;									// 所有装备属性列表
	map<uint32_t, CompoundConf> m_compoundEquipMap;							// 装备合成列表
};

#define gpGoodsMng GoodsMng::GetInstance()

#endif