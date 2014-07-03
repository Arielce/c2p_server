#ifndef NETWORK_CMDPROTOCOL_H
#define NETWORK_CMDPROTOCOL_H

/*
	0xA001 - 0xA100 命令
*/

enum 
{
	// ======================客户端请求信息========================
	// 登录注册相关协议
	ID_REQ_RequestStop = 0xA001,		// 请求停止服务器
	ID_REQ_RequestReloadConf,			// 热重载配置
};

#endif