#ifndef NETWORK_ERRORCODES_H
#define NETWORK_ERRORCODES_H

/*
	0x0000 - 0x8000 客户端和LobbyCenter，GameServer之间通信使用的协议号范围
*/

enum 
{
	ERROR_OP_SUCCESS			= 0,		// 成功

	// 系统类错误
	ERROR_RELOAD_CONFIGURE_FAIL,			// 重载配置失败

	// 角色类错误
	ERROR_PTNAME_HAS_CREATE_ROLE,			// 已经创建过角色了
	ERROR_ROLENAME_EXIST,					// 角色名已经存在
	ERROR_PLAYER_NOT_FOUND,					// 玩家不在线
	ERROR_VERIFY_TOKEN_FAIL,				// 验证token失败

	// 金钱类错误
	ERROR_GOLD_NOT_ENOUGH,					// 金币不够
	ERROR_DIAMOND_NOT_ENOUGH,				// 钻石不够
	
	// 装备类错误
	ERROR_HERO_LEVEL_NOT_ENOUGH,			// 等级不够
	ERROR_EQUIP_NOT_EXIST,					// 装备不存在
	ERROR_EQUIP_NOT_ENOUGHT,				// 装备不够
	ERROR_COMPOUND_TARGET_NOT_EXIST,		// 合成装备目标不存在

	// 英雄类错误
	ERROR_HERO_NOT_EXIST,					// 英雄不存在

	// 关卡类错误
	ERROR_PLAYER_CAN_NOT_ENTER,				// 玩家不能进入指定关卡
	ERROR_PLAYER_NEVER_ENTER,				// 玩家没有进入过次关卡

	// 抽奖类错误
	ERROR_DRAW_CONF_NOT_EXIST,				// 此抽奖信息不存在
	ERROR_DRAW_COST_NOT_ENOUGH,				// 抽奖消耗不够
	ERROR_DRAW_DEADLINE,					// 抽奖信息过期
	ERROR_DRAW_MAX_TIMES,					// 已经达到最大抽奖次数
};

#endif