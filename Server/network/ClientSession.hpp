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

			// 设置上端的回调函数
			m_pConnection->SetRecvCallback(boost::bind(&IMsgHandler::HandleRecv, m_pMsgHandler, _1, _2, _3));
			m_pConnection->SetSendCallback(boost::bind(&IMsgHandler::HandleWrite, m_pMsgHandler, _1, _2));
			m_pConnection->SetConnCallback(boost::bind(&IMsgHandler::HandleConnect, m_pMsgHandler, _1, _2));
			m_pConnection->SetDisConnCallBack(boost::bind(&ClientSession::HandleDisconnect, this, _1, _2));
			// 开始连接
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
				m_pConnection->socket().close(errCode);						// 先关闭当前连接，然后重连
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
			m_pTimerTrigger->AddOnceTimer(boost::bind(&ClientSession::DoReConnect, this), 3);			// 每隔3秒重连一次
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
		Connection::pointer m_pConnection;					// 网络连接对象
		BoostIoService* m_pIoService;
		BoostStrand* m_pStrand;
		IMsgParser* m_pMsgParser;
		IMsgHandler* m_pMsgHandler;							// 消息处理对象
		ITimerTrigger* m_pTimerTrigger;						// 定时器对象

		uint32_t m_uHeadSize;								// 消息头长度
		uint32_t m_uBufSize;								// 缓冲区长度

		// 回调函数
		connFuncCallBack connCallback;
		disConnFuncCallBack disconnCallback;
		recvFuncCallBack recvCallback;
		sendFuncCallBack sendCallback;

		string m_strIp;										// 连接目标的IP
		uint32_t m_uPort;									// 连接目标的端口
	};
}

#endif