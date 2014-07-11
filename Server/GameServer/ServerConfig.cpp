#include "header.h"
#include "ServerConfig.h"

bool ServerConfig::LoadServerConf(const char* pFilePath)
{
	if (!m_xmlDoc.LoadFile(pFilePath))
	{
		return false;
	}

	TiXmlElement* pRoot = m_xmlDoc.RootElement();
	if (!pRoot)
	{
		return false;
	}

	TiXmlElement* pHostServer = pRoot->FirstChildElement("HostServer");
	if (!pHostServer)
	{
		ERRORLOG("cannot find host server");
		return false;
	}

	const char* pServerId = pHostServer->Attribute("id");
	if (pServerId)
	{
		m_nServerId = boost::lexical_cast<int>(pServerId);
		cout << "ServerId=" << m_nServerId << endl;
		ERRORLOG("ServerId=" << m_nServerId);
	}

	TiXmlElement* pServer = pHostServer->FirstChildElement("bind");
	if (!pServer)
	{
		return false;
	}
	const char* pServerIp = pServer->Attribute("ip");
	const char* pServerPort = pServer->Attribute("port");
	if (pServerIp)
	{
		memcpy(m_szGsIp, pServerIp, strlen(pServerIp));
	}
	if (pServerPort)
	{
		m_nGsPort = boost::lexical_cast<int>(pServerPort);
	}

	// cmdlisten
	TiXmlElement* pCmdListen = pRoot->FirstChildElement("CmdListen");
	if (!pCmdListen)
	{
		return false;
	}
	TiXmlElement* pListen = pCmdListen->FirstChildElement("bind");
	if (!pListen)
	{
		return false;
	}
	const char* pCmdIp = pListen->Attribute("ip");
	const char* pCmdPort = pListen->Attribute("port");
	if (pCmdIp)
	{
		memcpy(m_szCmdIp, pCmdIp, strlen(pCmdIp));
	}
	if (pCmdPort)
	{
		m_uCmdPort = boost::lexical_cast<uint32_t>(pCmdPort);
	}

	// datasever
	TiXmlElement* pDataServer = pRoot->FirstChildElement("DataServer");
	if (!pDataServer)
	{
		ERRORLOG("cannot find DataServer");
		return false;
	}

	TiXmlElement* pDataServerConn = pDataServer->FirstChildElement("connect");
	if (!pDataServerConn)
	{
		return false;
	}
	const char* pDataServerIp = pDataServerConn->Attribute("ip");
	const char* pDataServerPort = pDataServerConn->Attribute("port");
	if (pDataServerIp)
	{
		memcpy(m_szDsIp, pDataServerIp, strlen(pDataServerIp));
	}
	if (pDataServerPort)
	{
		m_nDsPort = boost::lexical_cast<int>(pDataServerPort);
	}

	// lobbyserver
	TiXmlElement* pLobbyServer = pRoot->FirstChildElement("LobbyServer");
	if (!pLobbyServer)
	{
		ERRORLOG("cannot find LobbyServer");
		return false;
	}

	TiXmlElement* pLobbyServerConn = pLobbyServer->FirstChildElement("connect");
	if (!pLobbyServerConn)
	{
		return false;
	}
	const char* pLobbyServerIp = pLobbyServerConn->Attribute("ip");
	const char* pLobbyServerPort = pLobbyServerConn->Attribute("port");
	if (pLobbyServerIp)
	{
		memcpy(m_szLobbyIp, pLobbyServerIp, strlen(pLobbyServerIp));
	}
	if (pLobbyServerPort)
	{
		m_nLobbyPort = boost::lexical_cast<int>(pLobbyServerPort);
	}

	// loginserveragent
	TiXmlElement* pLoginAgent = pRoot->FirstChildElement("LoginServerAgent");
	if (!pLoginAgent)
	{
		ERRORLOG("cannot find LoginServerAgent");
		return false;
	}

	TiXmlElement* pLoginAgentConn = pLoginAgent->FirstChildElement("connect");
	if (!pLoginAgentConn)
	{
		return false;
	}
	const char* pLoginAgentIp = pLoginAgentConn->Attribute("ip");
	const char* pLoginAgentPort = pLoginAgentConn->Attribute("port");
	if (pLoginAgentIp)
	{
		memcpy(m_szLoginIp, pLoginAgentIp, strlen(pLoginAgentIp));
	}
	if (pLoginAgentPort)
	{
		m_nLoginPort = boost::lexical_cast<int>(pLoginAgentPort);
	}

	// redis
	TiXmlElement* pRedisServer = pRoot->FirstChildElement("Redis");
	if (!pRedisServer)
	{
		return false;
	}
	TiXmlElement* pRedisInfo = pRedisServer->FirstChildElement("connect");
	if (!pRedisInfo)
	{
		return false;
	}
	const char* pRedisIp = pRedisInfo->Attribute("ip");
	const char* pRedisPort = pRedisInfo->Attribute("port");
	const char* pRedisIndex = pRedisInfo->Attribute("index");
	if (!pRedisIp || !pRedisPort || !pRedisIndex)
	{
		return false;
	}
	m_strRedisIp = pRedisIp;
	m_nRedisPort = boost::lexical_cast<int>(pRedisPort);
	m_nRedisIndex = boost::lexical_cast<int>(pRedisIndex);

	return true;
}