#ifndef NETWORK_DATAPROTOCOL_H
#define NETWORK_DATAPROTOCOL_H

/*
	0x9000 - 0xA000 GameServer和DataServer通信使用的协议
*/

enum 
{
	// ======================客户端请求信息========================
	// 登录注册相关协议
	ID_SREQ_SRequestCreateRole = 0x9000,		// 请求创建角色
	ID_SREQ_SRequestGetRoleData	,				// 请求角色数据
	ID_SREQ_SRequestSaveRoleData,				// 请求保存角色数据
	ID_SREQ_SRequestRoleDataVersion,			// 请求数据版本

	// ======================服务器消息返回==========================
	// 进入游戏相关协议
	ID_SACK_SResponseCreateRole = 0x9000,		// 返回创建角色结果
	ID_SACK_SResponseGetRoleData,				// 返回角色数据
	ID_SACK_SResponseSaveRoleData,				// 返回保存数据结果
	ID_SACK_SResponseRoleDataVersion,			// 返回数据版本
};

#endif