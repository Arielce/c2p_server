#ifndef GAMESERVER_GOODSMNG_H
#define GAMESERVER_GOODSMNG_H

#include "header.h"
#include "Goods.h"

typedef struct tagCompoundConf
{
	uint32_t uCompoundId;			// �ϳ�Id
	uint32_t uGoldNeed;				// ��Ҫ�Ľ������
	uint32_t uScrollId;				// ����ID
	struct EquipNeed
	{
		uint32_t uEquipId;			// װ��ID
		uint32_t uEquipNum;			// װ������
	};
	vector<EquipNeed> equipNeedVec;	// ��Ҫ��װ���б�
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
	map<uint32_t, bool> m_totalMap;											// ������Ʒ�б�
	map<uint32_t, HeroExpMedicineProp> m_heroExpMedicineMap;				// ����ҩˮ�����б�
	map<uint32_t, EquipProp> m_equipMap;									// ����װ�������б�
	map<uint32_t, CompoundConf> m_compoundEquipMap;							// װ���ϳ��б�
};

#define gpGoodsMng GoodsMng::GetInstance()

#endif