#ifndef GAMESERVER_RELOADCONFIGURE_H
#define GAMESERVER_RELOADCONFIGURE_H

#include "header.h"

// ��Ҫ���������ļ������빤��
class ConfigureReloador
{
public:
	// ���Ŀ��������NULL����ô������������
	bool ReloadConf(const char* pFileName = NULL);
};

#endif