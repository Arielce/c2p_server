#ifndef NETWORK_MESSAGETHREAD_H
#define NETWORK_MESSAGETHREAD_H

#include "header.h"
#include "Connection.h"

namespace cpnet
{
	enum EPackageType
	{
		INVALID_MSG = -1,
		CONNECT_MSG = 0,
		DISCONNECT_MSG,
		RECV_MSG,
		SEND_MSG,
		TIMER_MSG,
	};

	typedef struct tagPackage
	{
		Connection::pointer pConn;					// �������Ӷ���
		TriggerCallback triggerCallback;			// ��ʱ�������ص�����(�������ص�������������ģ���ôpConn���ǲ���Ҫ�ģ�����ֻ��Ҫһ��)
		string strMessage;							
		EPackageType packageType;
		BoostErrCode errCode;
		tagPackage() : packageType(INVALID_MSG)
		{

		}
		tagPackage(const Connection::pointer& _pConn, const string& _strMessage, EPackageType type, const BoostErrCode& _errCode) : 
			pConn(_pConn), strMessage(_strMessage), packageType(type), errCode(_errCode)
		{

		}
		tagPackage(const TriggerCallback& _triggerCallback, EPackageType type, const BoostErrCode& _errCode) : 
			triggerCallback(_triggerCallback), packageType(type), errCode(_errCode)
		{

		}
	}Package;

	class MessageThread
	{
	public:
		static MessageThread* GetInstance()
		{
			static MessageThread instance;
			return &instance;
		}

		void Push(const Package& package);
		void Run();
		void Stop();
	private:
		MessageThread();

	private:
		deque<Package> m_msgQueue;				// ��Ϣ����
		boost::mutex m_mutex;
		boost::condition m_cond;
		bool m_bRun;
	};
}

#endif