#ifndef GAMESERVER_GOODS_H
#define GAMESERVER_GOODS_H

#include "header.h"

/*
	��Ʒ��װ���������Լ������Ķ���
*/

enum EGoodsType
{
	GOODS_INVALID = 0,				// ��Ч��Ʒ����
	GOODS_HERO_EXP = 1,				// ����ҩˮ
	GOODS_SCROLL = 2,				// �ϳɾ���
	GOODS_EQUIP = 3,				// ������װ��
	GOODS_STONE = 4,				// ���ʯ
	GOODS_SWEEP = 5,				// ɨ����
};

/*
	��Ʒ���࣬ӵ����Ʒһ�������
	�����ľ�������Ʒ��������������Ʒ���Լ�װ��������ͨ��type��Ӧ����ͬ����������
	PS: ����֮��û�в��ü̳з�ʽ���й�ϵ��֯������Ϊ��Щ�������ݣ�û��ʲô�ܹ�ͳһ�Ĳ����ӿ�
*/
class Goods
{
public:
	uint32_t uId;				// ��ƷID
	uint32_t uNum;				// ��Ʒ����
	uint32_t uType;				// ��Ʒ����
	Goods() : uId(0), uNum(1), uType(GOODS_INVALID)
	{
	}
};

// Ŀǰɨ�����ϳɾ��ᣬ�Լ����ʯ��û�ж������Ե�

// Ӣ�۾���ҩˮ����
class HeroExpMedicineProp
{
public:
	uint32_t uExpAdd;			// �����ӵ�Ӣ�۾���
	HeroExpMedicineProp() : uExpAdd(0)
	{
	}
};

// װ������
class EquipProp
{
public:
	uint32_t uLevelLimit;		// �ȼ�����
	uint32_t uStrength;			// ����
	uint32_t uIntelligence;		// ����
	uint32_t uAgility;			// ����
	uint32_t uAttack;			// ������
	uint32_t uHP;				// Ѫ��
	uint32_t uHPRecover;		// Ѫ���ظ�
	uint32_t uMPRecover;		// �����ظ�

	EquipProp() : uLevelLimit(0), uStrength(0), uIntelligence(0), uAgility(0), uAttack(0), uHP(0), uHPRecover(0), uMPRecover(0)
	{
	}
};

#endif