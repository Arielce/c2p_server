#ifndef GAMESERVER_SERVERCONFIG_H
#define GAMESERVER_SERVERCONFIG_H

#include "../tinyxml/tinyxml.h"
#include <boost/lexical_cast.hpp>

class ServerConfig
{
public:
	static ServerConfig* GetInstance()
	{
		static ServerConfig instance;
		return &instance;
	}

	bool LoadServerConf(const char* pFilePath);
	uint32_t GetGsBindPort()
	{
		return m_nGsPort;
	}
	const char* GetGsBindIp()
	{
		return m_szGsIp;
	}

	uint32_t GetCmdPort()
	{
		return m_uCmdPort;
	}

	const char* GetCmdIp()
	{
		return m_szCmdIp;
	}

	uint32_t GetDsPort()
	{
		return m_nDsPort;
	}

	const char* GetDsIp()
	{
		return m_szDsIp;
	}

	uint32_t GetLobbyPort()
	{
		return m_nLobbyPort;
	}

	const char* GetLobbyIp()
	{
		return m_szLobbyIp;
	}

	uint32_t GetServerId()
	{
		return m_nServerId;
	}

	const char* GetRedisIp()
	{
		return m_strRedisIp.c_str();
	}

	uint32_t GetLoginPort()
	{
		return m_nLoginPort;
	}

	const char* GetLoginIp()
	{
		return m_szLoginIp;
	}

	uint32_t GetRedisPort()
	{
		return m_nRedisPort;
	}
	uint32_t GetRedisIndex()
	{
		return m_nRedisIndex;
	}

private:
	ServerConfig() : m_nServerId(0), m_nGsPort(0)
	{
		memset(m_szGsIp, 0, sizeof(m_szGsIp));
		memset(m_szDsIp, 0, sizeof(m_szDsIp));
	}

private:
	TiXmlDocument m_xmlDoc;
	uint32_t m_nServerId;
	uint32_t m_nGsPort;
	char m_szGsIp[32];
	uint32_t m_uCmdPort;
	char m_szCmdIp[32];
	uint32_t m_nDsPort;
	char m_szDsIp[32];
	uint32_t m_nLobbyPort;
	char m_szLobbyIp[32];
	uint32_t m_nLoginPort;
	char m_szLoginIp[32];

	string m_strRedisIp;
	uint32_t m_nRedisPort;
	uint32_t m_nRedisIndex;
};

#define gpServerConfig ServerConfig::GetInstance()

#endif