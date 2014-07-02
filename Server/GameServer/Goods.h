#ifndef GAMESERVER_GOODS_H
#define GAMESERVER_GOODS_H

#include "header.h"

/*
	物品，装备，卷轴以及相关类的定义
*/

enum EGoodsType
{
	GOODS_INVALID = 0,				// 无效物品类型
	GOODS_HERO_EXP = 1,				// 经验药水
	GOODS_SCROLL = 2,				// 合成卷轴
	GOODS_EQUIP = 3,				// 穿戴的装备
	GOODS_STONE = 4,				// 灵魂石
	GOODS_SWEEP = 5,				// 扫荡卷
};

/*
	物品总类，拥有物品一般的属性
	其他的卷轴类物品，经验消耗类物品，以及装备，都是通过type对应到不同的属性数据
	PS: 他们之间没有采用继承方式进行关系组织，是因为这些都是数据，没有什么能够统一的操作接口
*/
class Goods
{
public:
	uint32_t uId;				// 物品ID
	uint32_t uNum;				// 物品数量
	uint32_t uType;				// 物品类型
	Goods() : uId(0), uNum(1), uType(GOODS_INVALID)
	{
	}
};

// 目前扫荡卷，合成卷轴，以及灵魂石是没有额外属性的

// 英雄经验药水属性
class HeroExpMedicineProp
{
public:
	uint32_t uExpAdd;			// 能增加的英雄经验
	HeroExpMedicineProp() : uExpAdd(0)
	{
	}
};

// 装备属性
class EquipProp
{
public:
	uint32_t uLevelLimit;		// 等级限制
	uint32_t uStrength;			// 力量
	uint32_t uIntelligence;		// 智力
	uint32_t uAgility;			// 敏捷
	uint32_t uAttack;			// 物理攻击
	uint32_t uHP;				// 血量
	uint32_t uHPRecover;		// 血量回复
	uint32_t uMPRecover;		// 能量回复

	EquipProp() : uLevelLimit(0), uStrength(0), uIntelligence(0), uAgility(0), uAttack(0), uHP(0), uHPRecover(0), uMPRecover(0)
	{
	}
};

#endif