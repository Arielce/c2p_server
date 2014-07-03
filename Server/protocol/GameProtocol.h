#ifndef NETWORK_GAMEPROTOCOL_H
#define NETWORK_GAMEPROTOCOL_H

/*
	0x0000 - 0x8000 客户端和LobbyCenter，GameServer之间通信使用的协议号范围
*/

enum 
{
	// ======================客户端请求信息========================
	// 测试使用的ping-pong协议
	ID_REQ_Test_PingPong			= 0x0001,

	// 登录注册相关协议
	ID_REQ_Lobby_RequestGameGroups	= 0x0100,		// 用户请求区组列表

	ID_REQ_Lobby_RequestLogin		= 0x0200,		// 用户登录请求
	ID_REQ_Lobby_RequestRegister,					// 用户请求注册
	ID_REQ_Lobby_RequestBindEmail,					// 用户请求绑定邮箱
	ID_REQ_Lobby_RequestChangePwd,					// 用户请求修改密码
	ID_REQ_Lobby_RequestFindPasswd,					// 用户请求密码找回

	// 请求执行GM指令
	ID_REQ_RequestProcGMCommand		= 0x0900,		// 请求执行GM指令
	ID_REQ_RequestVerifyToken,						// 验证token

	// 进入游戏相关协议
	ID_REQ_RequestLoginGame			= 0x1000,		// 客户端请求进入游戏
	ID_REQ_RequestCreateRole,						// 请求创建角色
	ID_REQ_RequestRoleData,							// 请求角色数据

	// 关卡相关操作
	ID_REQ_RequestEnterGate			= 0x1100,		// 玩家请求进入关卡
	ID_REQ_RequestFinishGate,						// 请求结束关卡

	// 装备相关操作
	ID_REQ_RequestHeroDressEquip	= 0x1200,		// 玩家请求英雄穿装备
	ID_REQ_RequestUpgradeHero,						// 玩家请求英雄升级
	ID_REQ_RequestCompoundEquip,					// 玩家请求合成装备

	// 抽奖相关操作
	ID_REQ_RequestDrawPrizeList		= 0x1300,		// 请求抽奖列表
	ID_REQ_RequestDrawPrize,						// 请求抽奖

	// ======================服务器消息返回==========================
	// 请求执行GM指令
	ID_ACK_ResponseProcGMCommand	= 0x0900,		// 请求执行GM指令
	ID_ACK_ResponseVerifyToken,						// 验证token

	// 进入游戏相关协议
	ID_ACK_ResponseLoginGame		= 0x1000,		// 返回客户端进入游戏结果
	ID_ACK_ResponseCreateRole,
	ID_ACK_ResponseRoleData,						// 返回角色数据 

	ID_ACK_ResponseEnterGate		= 0x1100,		// 玩家请求进入关卡
	ID_ACK_ResponseFinishGate,						// 请求结束关卡

	// 装备相关操作
	ID_ACK_ResponseHeroDressEquip	= 0x1200,		// 玩家请求英雄穿装备
	ID_ACK_ResponseUpgradeHero,						// 玩家请求英雄升级
	ID_ACK_ResponseCompoundEquip,					// 玩家请求合成装备

	// 抽奖相关操作
	ID_ACK_ResponseDrawPrizeList	= 0x1300,		// 请求抽奖列表
	ID_ACK_ReponseDrawPrize,						// 请求抽奖


	// ======================服务器通知消息==========================
	// 广播专用协议
	ID_NTY_NotifyBroadcast			= 0x8000,		// 用于广播消息的协议

	// 角色属性相关
	ID_NTY_NotifyRoleLevelUp		= 0x9000,		// 通知玩家升级
};

#endif