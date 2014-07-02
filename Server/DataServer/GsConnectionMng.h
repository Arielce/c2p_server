#ifndef DATASERVER_GSCONNECTIONMNG_H
#define DATASERVER_GSCONNECTIONMNG_H

#include "header.h"

/*
	����DataServer��GameServer֮������ӣ�����Ժ���Ҫ��GameServer�ܹ�������Ҳ������չ
*/
class GsConnectionMng
{
public:
	static GsConnectionMng* GetInstance()
	{
		static GsConnectionMng instance;
		return &instance;
	}

	void SetGsConnection(IConnection* pGsConnection, uint32_t uGsIndex=0);
	void SendMsgToGS(const char* pBuf, uint32_t uSize, uint32_t uGsIndex=0);

private:
	boost::mutex m_mutex;
	vector<IConnection*> m_gsConnectionList;
};

#define gpGsConnMng GsConnectionMng::GetInstance()

#endif