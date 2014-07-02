#include "Connection.h"

namespace cpnet
{
	bool Connection::IsConnected()
	{
		return m_bConnect;
	}
	void Connection::GetRemoteInfo()
	{
		if (!m_bGetRemoteInfo)
		{
			try 
			{
				m_strRemoteIp = m_sock.remote_endpoint().address().to_string();
				m_uRemotePort = m_sock.remote_endpoint().port();
				m_bGetRemoteInfo = true;
			}
			catch(boost::system::system_error& err)
			{
				ERROR_NET("get remote info exception, error=[" << err.what() << "]");
			}
		}
	}

	void Connection::StartRead()
	{
		SetAsyncHandler();
	}

	void Connection::ShutDown()
	{
		m_sock.shutdown(boost::asio::socket_base::shutdown_both);
	}

	const char* Connection::GetRemoteIp()
	{
		return m_strRemoteIp.c_str();
	}

	uint32_t Connection::GetRemotePort()
	{
		return m_uRemotePort;
	}

	void Connection::SetRecvCallback(const recvFuncCallBack& _recvCallBack)
	{
		recvCallBack = _recvCallBack;
	}
	void Connection::SetSendCallback(const sendFuncCallBack& _sendCallBack)
	{
		sendCallBack = _sendCallBack;
	}

	void Connection::SetConnected(bool bFlag)
	{
		m_bConnect = bFlag;
	}

	void Connection::SetConnCallback(const connFuncCallBack& _connCallback)
	{
		connCallback = _connCallback;
	}
	void Connection::SetDisConnCallBack(const disConnFuncCallBack& _disConnCallback)
	{
		disConnCallback = _disConnCallback;
	}

	void Connection::SetMsgParser(IMsgParser* pMsgParser)
	{
		m_pMsgParser = pMsgParser;
	}

	BoostSocket& Connection::socket()
	{
		return m_sock;
	}

	void Connection::SendMsg(const void* pData, uint32_t uLen)
	{
		boost::lock_guard<boost::mutex> lock(m_mutex);
		bool bWriteInProcess = !m_msgQueue.empty();		
		m_msgQueue.push_back(string((char*)pData, uLen));
		if (!bWriteInProcess)								// 如果当前发送队列没有消息正在发送，就直接调用异步发送接口，否则只是将发送消息加入队列
		{
			try
			{
				boost::asio::async_write(m_sock, boost::asio::buffer(m_msgQueue.front().data(), m_msgQueue.front().length()),
					m_pStrand->wrap(
						boost::bind(
							&Connection::HandleSend,
							shared_from_this(),
							boost::asio::placeholders::error,
							boost::asio::placeholders::bytes_transferred)
						)
					);
			}
			catch(boost::system::system_error& err)
			{
				ERROR_NET("send message exception, error=[" << err.what() << "]");
			}
		}
	}

	// the async_write call back
	void Connection::HandleSend(const boost::system::error_code& error, std::size_t bytes_transferred) 
	{
		boost::lock_guard<boost::mutex> lock(m_mutex);		// 为了保证发送功能是线程安全的
		m_msgQueue.pop_front();
		if (!m_msgQueue.empty())
		{
			try 
			{
				boost::asio::async_write(m_sock, boost::asio::buffer(m_msgQueue.front().data(), m_msgQueue.front().length()),
					m_pStrand->wrap(
						boost::bind(
							&Connection::HandleSend,
							shared_from_this(),
							boost::asio::placeholders::error,
							boost::asio::placeholders::bytes_transferred)
						)
					);
			}
			catch(boost::system::system_error& err)
			{
				ERROR_NET("send message exception, error=[" << err.what() << "]");
			}
		}
	}

	void Connection::HandleReadBody(const BoostErrCode& errCode, size_t nBytesTranfered)
	{
		if (!CheckErrCode(errCode))
		{
			return;
		}

		size_t nMsgSize = m_pMsgParser->CheckMsgBody(m_pBuff, nBytesTranfered + m_nHeadLength);
		if (nMsgSize < m_nHeadLength)
		{
			ERROR_NET("message size is too small, message size =[" << nMsgSize << "]");
			m_sock.close();
			return;
		}
		nMsgSize -= m_nHeadLength;

		if (nMsgSize != nBytesTranfered)
		{
			cout << "the message is lager than the buf capacity" << endl;
			return;
		}

		recvCallBack(this, m_pBuff, nBytesTranfered + m_nHeadLength);

		// reset recv handle
		SetAsyncHandler();
	}

	void Connection::HandleReadHeader(const BoostErrCode& errCode, size_t nBytesTranfered)
	{
		if (!CheckErrCode(errCode))
		{
			return;
		}
		if (nBytesTranfered < m_nHeadLength)
		{
			return;
		}

		GetRemoteInfo();

		size_t nBodySize = m_pMsgParser->CheckMsgHeader(m_pBuff, nBytesTranfered);
		if (nBodySize + m_nHeadLength >= m_nBufLength || nBodySize < m_nHeadLength)
		{
			ERROR_NET("body size is too large or too small, body size =[" << nBodySize << "]");
			m_sock.close();
			return;
		}
		try
		{
			boost::asio::async_read(
				m_sock, 
				boost::asio::buffer(m_pBuff + m_nHeadLength, nBodySize - m_nHeadLength), 
				m_pStrand->wrap(boost::bind(&Connection::HandleReadBody, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)));
		}
		catch(boost::system::system_error& err)
		{
			ERROR_NET("reve message body exception, error=" << err.what());
		}
	}

	void Connection::SetAsyncHandler()
	{
		// set read call back function
		try
		{
			boost::asio::async_read(
				m_sock, 
				boost::asio::buffer(m_pBuff, m_nHeadLength), 
				m_pStrand->wrap(boost::bind(&Connection::HandleReadHeader, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)));
		}
		catch(boost::system::system_error& err)
		{
			ERROR_NET("reve message header exception, error=[" << err.what() << "]");
		}
	}

	// 检查错误码，是否有错误
	bool Connection::CheckErrCode(const BoostErrCode& errCode)
	{
		if (boost::asio::error::eof == errCode || boost::asio::error::connection_reset == errCode)
		{
			SetConnected(false);
			m_sock.close();						// 先关闭连接
			disConnCallback(this, errCode);
			return false;
		}
		if (boost::asio::error::connection_refused == errCode)
		{
			ERROR_NET("connect refused.");
			return false;
		}
		if (boost::asio::error::bad_descriptor == errCode)
		{
			ERROR_NET("bad descriptor");
			return false;
		}
		if (boost::asio::error::connection_aborted == errCode)
		{
			SetConnected(false);
			disConnCallback(this, errCode);
			return false;
		}
		if (errCode)
		{
			ERROR_NET("error code=[" << errCode << "]");
			return false;
		}

		return true;
	}
}
