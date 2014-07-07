#ifndef NETWORK_LOBBYPROTOCOL_H
#define NETWORK_LOBBYPROTOCOL_H

/*
	0x9000 - 0xA000 GameServer和DataServer通信使用的协议
*/

enum 
{
	// ======================客户端请求信息========================
	// 登录注册相关协议
	ID_REQ_RequestGameGroup	= 0x0100,			// 客户端请求游戏区组

	// ======================服务器消息返回==========================
	// 进入游戏相关协议
	ID_ACK_ResponseGameGroup = 0x0100,			// 返回区组信息


	// ======================GameServer请求信息========================
	// 登录注册相关协议
	ID_SREQ_SRequestGsReg	= 0xA000,				// GameServer注册

	// ======================服务器消息返回==========================
	// 进入游戏相关协议
	ID_SACK_SResponseGsReg	= 0xA000,				// 返回角色数据
};

#endif