#include "Connection.h"

namespace cpnet
{
	void Connection::Start()
	{
		GetRemoteInfo();
		SetConnected(true);
		StartRead();

		m_pStrand->dispatch(boost::bind(&IMsgHandler::HandleConnect, m_pMsgHandler, this));

	}
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

	void Connection::SetConnected(bool bFlag)
	{
		m_bConnect = bFlag;
	}

	void Connection::SetMsgParser(IMsgParser* pMsgParser)
	{
		m_pMsgParser = pMsgParser;
	}

	void Connection::SetMsgHandler(IMsgHandler* pMsgHandler)
	{
		m_pMsgHandler = pMsgHandler;
	}

	void Connection::SetDisconnCallback(const disConnFuncCallBack& _disConnCallback)
	{
		disconnCallback = _disConnCallback;
		m_bForClientSession = true;
	}

	BoostSocket& Connection::socket()
	{
		return m_sock;
	}

	void Connection::SendMsg(const void* pData, uint32_t uLen)
	{
		//boost::lock_guard<boost::mutex> lock(m_mutex);
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
		//boost::lock_guard<boost::mutex> lock(m_mutex);		// 为了保证发送功能是线程安全的
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

	void Connection::HandleRead(const BoostErrCode& errCode, size_t nBytesTranfered)
	{
		if (errCode)
		{
			CheckErrCode(errCode);
			return;
		}
		
		// 主要针对半包和粘包进行处理
		m_nHasTransffered += nBytesTranfered;											// 算出当前已经传输了的数据量
		if (m_nHasTransffered < m_nHeadLength)											// 没有数据包头大, 继续接收数据
		{
			StartRead();
			return;
		}

		// 计算出整个数据包的大小
		size_t nBodySize = m_pMsgParser->CheckMsgHeader(m_pBuff, m_nHasTransffered);

		if (nBodySize > m_nBufLength)														// 数据包头比整个buf还要大
		{
			ERROR_NET("message size is too large, message size =[" << nBodySize << "]");
			m_sock.close();
			return;
		}

		size_t nHasUsedBuf = 0;							// 已经使用了的数据长度
		while (m_nHasTransffered >= nBodySize)											// 必须确保数据包长度的完整性
		{
			m_pMsgHandler->HandleRecv(this, m_pBuff + nHasUsedBuf, nBodySize);
			m_nHasTransffered -= nBodySize;												// 减少已经收到的数据量
			nHasUsedBuf += nBodySize;													// 计算缓冲区中已经被使用的buf长度

			// 如果一次收到了多个数据包
			if (m_nHasTransffered >= m_nHeadLength)										// 如果剩下的数据长度够一个包头的大小，
			{
				nBodySize = m_pMsgParser->CheckMsgHeader(m_pBuff + nHasUsedBuf, m_nHasTransffered);
			}
			else
			{
				break;
			}
		}

		if (m_nHasTransffered && nHasUsedBuf)					// 还有剩余的数据，进行buf的移动
		{
			memmove(m_pBuff, m_pBuff + nHasUsedBuf, m_nHasTransffered);
		}

		StartRead();
	}

	void Connection::StartRead()
	{
		// set read call back function
		try
		{
			m_sock.async_read_some(boost::asio::buffer(m_pBuff + m_nHasTransffered, m_nBufLength - m_nHasTransffered),
				m_pStrand->wrap(
				boost::bind(&Connection::HandleRead, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred)));
		}
		catch(boost::system::system_error& err)
		{
			ERROR_NET("reve message header exception, error=[" << err.what() << "]");
		}
	}

	// 检查错误码，是否有错误
	bool Connection::CheckErrCode(const BoostErrCode& errCode)
	{
		if (!errCode)
		{
			return true;
		}
		if (boost::asio::error::eof == errCode || boost::asio::error::connection_reset == errCode || boost::asio::error::connection_aborted == errCode)
		{
			SetConnected(false);
			m_sock.close();						// 先关闭连接
			if (m_bForClientSession)
			{
				disconnCallback(this, errCode);
			}
			else
			{
				m_pMsgHandler->HandleDisconnect(this, errCode);
			}
			
			return false;
		}
		else if (boost::asio::error::connection_refused == errCode)			// 连接被拒绝
		{
			ERROR_NET("connect refused.");
			return false;
		}
		else if (boost::asio::error::bad_descriptor == errCode)
		{
			ERROR_NET("bad descriptor");
			return false;
		}
		else
		{
			ERROR_NET("error code=[" << errCode << "]");
			return false;
		}

		return true;
	}
}
