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
		if (!bWriteInProcess)								// �����ǰ���Ͷ���û����Ϣ���ڷ��ͣ���ֱ�ӵ����첽���ͽӿڣ�����ֻ�ǽ�������Ϣ�������
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
		//boost::lock_guard<boost::mutex> lock(m_mutex);		// Ϊ�˱�֤���͹������̰߳�ȫ��
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
		
		// ��Ҫ��԰����ճ�����д���
		m_nHasTransffered += nBytesTranfered;											// �����ǰ�Ѿ������˵�������
		if (m_nHasTransffered < m_nHeadLength)											// û�����ݰ�ͷ��, ������������
		{
			StartRead();
			return;
		}

		// ������������ݰ��Ĵ�С
		size_t nBodySize = m_pMsgParser->CheckMsgHeader(m_pBuff, m_nHasTransffered);

		if (nBodySize > m_nBufLength)														// ���ݰ�ͷ������buf��Ҫ��
		{
			ERROR_NET("message size is too large, message size =[" << nBodySize << "]");
			m_sock.close();
			return;
		}

		size_t nHasUsedBuf = 0;							// �Ѿ�ʹ���˵����ݳ���
		while (m_nHasTransffered >= nBodySize)											// ����ȷ�����ݰ����ȵ�������
		{
			m_pMsgHandler->HandleRecv(this, m_pBuff + nHasUsedBuf, nBodySize);
			m_nHasTransffered -= nBodySize;												// �����Ѿ��յ���������
			nHasUsedBuf += nBodySize;													// ���㻺�������Ѿ���ʹ�õ�buf����

			// ���һ���յ��˶�����ݰ�
			if (m_nHasTransffered >= m_nHeadLength)										// ���ʣ�µ����ݳ��ȹ�һ����ͷ�Ĵ�С��
			{
				nBodySize = m_pMsgParser->CheckMsgHeader(m_pBuff + nHasUsedBuf, m_nHasTransffered);
			}
			else
			{
				break;
			}
		}

		if (m_nHasTransffered && nHasUsedBuf)					// ����ʣ������ݣ�����buf���ƶ�
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

	// �������룬�Ƿ��д���
	bool Connection::CheckErrCode(const BoostErrCode& errCode)
	{
		if (!errCode)
		{
			return true;
		}
		if (boost::asio::error::eof == errCode || boost::asio::error::connection_reset == errCode || boost::asio::error::connection_aborted == errCode)
		{
			SetConnected(false);
			m_sock.close();						// �ȹر�����
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
		else if (boost::asio::error::connection_refused == errCode)			// ���ӱ��ܾ�
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
