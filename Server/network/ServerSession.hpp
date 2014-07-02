#ifndef	NETWORK_SERVERAPP_H
#define NETWORK_SERVERAPP_H

#include "header.h"
#include "IMsgParser.h"
#include "Connection.h"
#include "ITimerTrigger.h"
#include "TimerTrigger.h"
#include "INetCluster.h"
#include "IMsgHandler.h"

namespace cpnet
{
	class ServerSession : public IServerSession
	{
	public:
		typedef ServerSession* pointer;
		static pointer Create(BoostIoService& ioService, BoostStrand& strand)
		{
			return new ServerSession(ioService, strand);
		}

		virtual void Listen(const char* pHostIp, uint32_t nPort)
		{
			try 
			{
				BoostEndPoint endPoint(BoostAddress::from_string(pHostIp), nPort);
				m_acceptor.open(endPoint.protocol());
				m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
				m_acceptor.bind(endPoint);
				m_acceptor.listen();
			}
			catch(boost::system::system_error e)
			{
				TRACE_NET("server listen exception, err=[" << e.what() << "]");
			}

			Connection::pointer pNewConnection = Connection::Create(*m_pIoService, *m_pStrand, m_uHeadSize, m_uBufSize);
			m_acceptor.async_accept(pNewConnection->socket(), m_pStrand->wrap(boost::bind(&ServerSession::HandleAccept, this, pNewConnection, boost::asio::placeholders::error)));
			TRACE_NET("server listen start, ip=[" << pHostIp << "], port=[" << nPort << "]");

			return;
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

		virtual void Stop()
		{
			m_acceptor.close();
		}

	private:
		ServerSession(BoostIoService& ioService, BoostStrand& strand) : m_acceptor(ioService), m_uHeadSize(0), m_uBufSize(0)
		{
			m_pIoService = &ioService;
			m_pStrand = &strand;
		}
		virtual ~ServerSession()
		{
			m_pIoService->stop();
		}

		void HandleAccept(Connection::pointer pConnection, const boost::system::error_code& error)
		{
			if (error)
			{
				ERROR_NET("server app handle accept error=[" << error.message() << "]");
				return;
			}

			// 设置回调函数，以及消息处理接口
			pConnection->SetMsgParser(m_pMsgParser);
			pConnection->SetRecvCallback(boost::bind(&IMsgHandler::HandleRecv, m_pMsgHandler, _1, _2, _3));
			pConnection->SetSendCallback(boost::bind(&IMsgHandler::HandleWrite, m_pMsgHandler, _1, _2));
			pConnection->SetConnCallback(boost::bind(&IMsgHandler::HandleConnect, m_pMsgHandler, _1, _2));
			pConnection->SetDisConnCallBack(boost::bind(&IMsgHandler::HandleDisconnect, m_pMsgHandler, _1, _2));
			pConnection->GetRemoteInfo();
			pConnection->SetConnected(true);
			pConnection->StartRead();

			//MessageThread::GetInstance()->Push(Package(pConnection, string(""), CONNECT_MSG, error));
			m_pMsgHandler->HandleConnect(pConnection.get(), error);

			Connection::pointer pNewConnection = Connection::Create(*m_pIoService, *m_pStrand, m_uHeadSize, m_uBufSize);
			m_acceptor.async_accept(pNewConnection->socket(), m_pStrand->wrap(boost::bind(&ServerSession::HandleAccept, this, pNewConnection, boost::asio::placeholders::error)));
		}

	private:
		BoostIoService* m_pIoService;
		BoostStrand* m_pStrand;
		BoostAcceptor m_acceptor;
		IMsgParser* m_pMsgParser;
		IMsgHandler* m_pMsgHandler;

		uint32_t m_uHeadSize;
		uint32_t m_uBufSize;
	};
}

#endif