#ifndef NETWORK_LOGINPROTOCOL_H
#define NETWORK_LOGINPROTOCOL_H

/*
	0xA100 - 0xA200 GameServer和LoginServerAgent通信使用的协议
*/

enum 
{
	// ======================GameServer请求信息========================
	// 登录注册相关协议
	ID_SREQ_SRequestVerifyToken	= 0xA100,				// 请求验证Token

	// ======================服务器消息返回==========================
	// 进入游戏相关协议
	ID_SACK_SRequestVerifyToken	= 0xA100,				// 返回Token验证结果
};

#endif