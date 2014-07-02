#ifndef NETWORK_CLIENTOBJ_H
#define NETWORK_CLIENTOBJ_H

#include "header.h"
#include "INetCluster.h"
#include "Connection.h"
#include "IMsgParser.h"
#include "IMsgHandler.h"
#include "NetCluster.h"

namespace cpnet
{
	class ClientSession : public IClientSession
	{
	public:
		typedef ClientSession* pointer;
		static pointer Create(BoostIoService& ioService, BoostStrand& strand)
		{
			return pointer(new ClientSession(ioService, strand));
		}

		virtual void Connect(const char* pServerIp, uint32_t uPort)
		{
			m_pConnection = Connection::Create(*m_pIoService, *m_pStrand, m_uHeadSize, m_uBufSize);
			m_strIp = pServerIp;
			m_uPort = uPort;
			m_pConnection->SetMsgParser(m_pMsgParser);

			// �����϶˵Ļص�����
			m_pConnection->SetRecvCallback(boost::bind(&IMsgHandler::HandleRecv, m_pMsgHandler, _1, _2, _3));
			m_pConnection->SetSendCallback(boost::bind(&IMsgHandler::HandleWrite, m_pMsgHandler, _1, _2));
			m_pConnection->SetConnCallback(boost::bind(&IMsgHandler::HandleConnect, m_pMsgHandler, _1, _2));
			m_pConnection->SetDisConnCallBack(boost::bind(&ClientSession::HandleDisconnect, this, _1, _2));
			// ��ʼ����
			DoReConnect();
		}

		virtual void SetMsgParser(IMsgParser* pMsgParser)
		{
			m_pMsgParser = pMsgParser;
		}

		virtual void SetMsgHandler(IMsgHandler* pMsgHandler)
		{
			m_pMsgHandler = pMsgHandler;
		}

		virtual void SetBufSize(uint32_t uHeadSize, uint32_t uBufSize)
		{
			m_uHeadSize = uHeadSize;
			m_uBufSize = uBufSize;
		}

		virtual void SendMsg(const char* pBuf, uint32_t uLen)
		{
			m_pConnection->SendMsg(pBuf, uLen);
		}

		virtual void Stop()
		{
			m_pConnection->ShutDown();
		}

	private:
		ClientSession(BoostIoService& ioService, BoostStrand& strand) : m_pTimerTrigger(NULL), m_pStrand(NULL), m_uHeadSize(0), m_uBufSize(0)
		{
			m_pIoService = &ioService;
			m_pStrand = &strand;
			InitReconnectTimer();
		}

		void DoReConnect()
		{
			BoostEndPoint endpoint(BoostAddress::from_string(m_strIp), m_uPort);
			BoostErrCode errCode;
			if (m_pConnection->socket().is_open())
			{
				m_pConnection->socket().close(errCode);						// �ȹرյ�ǰ���ӣ�Ȼ������
			}
			m_pConnection->socket().async_connect(endpoint, m_pStrand->wrap(boost::bind(&ClientSession::HandleConnect, this, boost::asio::placeholders::error)));
		}

		void HandleConnect(const BoostErrCode& err)
		{
			if (err)
			{
				ERROR_NET(err.message());
				OnTimerConnect();
				return;
			}
			m_pConnection->SetConnected(true);
			m_pConnection->StartRead();
			m_pMsgHandler->HandleConnect(m_pConnection.get(), err);
		}

		void HandleDisconnect(IConnection* pConnection, const BoostErrCode& err)
		{
			OnTimerConnect();	
		}

		void OnTimerConnect()
		{
			m_pTimerTrigger->AddOnceTimer(boost::bind(&ClientSession::DoReConnect, this), 3);			// ÿ��3������һ��
		}

		void InitReconnectTimer()
		{
			m_pTimerTrigger = NetCluster::GetInstance()->CreateTimerTrigger();
			if (!m_pTimerTrigger)
			{
				return;
			}
		}

	private:
		Connection::pointer m_pConnection;					// �������Ӷ���
		BoostIoService* m_pIoService;
		BoostStrand* m_pStrand;
		IMsgParser* m_pMsgParser;
		IMsgHandler* m_pMsgHandler;							// ��Ϣ�������
		ITimerTrigger* m_pTimerTrigger;						// ��ʱ������

		uint32_t m_uHeadSize;								// ��Ϣͷ����
		uint32_t m_uBufSize;								// ����������

		// �ص�����
		connFuncCallBack connCallback;
		disConnFuncCallBack disconnCallback;
		recvFuncCallBack recvCallback;
		sendFuncCallBack sendCallback;

		string m_strIp;										// ����Ŀ���IP
		uint32_t m_uPort;									// ����Ŀ��Ķ˿�
	};
}

#endif