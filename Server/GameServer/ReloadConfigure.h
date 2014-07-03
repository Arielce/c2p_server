#ifndef GAMESERVER_RELOADCONFIGURE_H
#define GAMESERVER_RELOADCONFIGURE_H

#include "header.h"

// 主要负责配置文件的载入工作
class ConfigureReloador
{
public:
	// 如果目标配置是NULL，那么重载所有配置
	bool ReloadConf(const char* pFileName = NULL);
};

#endif