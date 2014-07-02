#ifndef NETWORK_CONNECTION_H
#define NETWORK_CONNECTION_H

#include "header.h"
#include "IMsgParser.h"
#include "IConnection.h"

/*
	wrapper the ASIO connection
*/
namespace cpnet
{
	class MessageThread;
	class Connection : public IConnection, public boost::enable_shared_from_this<Connection>
	{
	public:
		friend class MessageThread;
		typedef boost::shared_ptr<Connection> pointer;

	public:
		static pointer Create(BoostIoService& ioService, BoostStrand& strand, size_t nHeadLength, size_t nBodyLength)
		{
			return pointer(boost::shared_ptr<Connection>(new Connection(ioService, strand, nHeadLength, nBodyLength)));
		}

		~Connection()
		{
			try 
			{
				m_sock.close();					// 关闭套接字对象
			}
			catch(boost::system::system_error& err)
			{
				ERROR_NET("reve message header exception, error=[" << err.what() << "]");
			}
			if (m_pBuff)
			{
				delete[] m_pBuff;
			}
		}
		virtual bool IsConnected();
		virtual const char* GetRemoteIp();
		virtual uint32_t GetRemotePort();
		virtual void SetRecvCallback(const recvFuncCallBack& _recvCallBack);
		virtual void SetSendCallback(const sendFuncCallBack& _sendCallBack);

		void SetConnected(bool bFlag);
		void SetConnCallback(const connFuncCallBack& _connCallback);
		void SetDisConnCallBack(const disConnFuncCallBack& _disConnCallback);
		void SetMsgParser(IMsgParser* pMsgParser);

		BoostSocket& socket();
		void GetRemoteInfo();
		void StartRead();
		void ShutDown();
		void SendMsg(const void* pData, uint32_t uLen);
	private:
		Connection(BoostIoService& ioService, BoostStrand& strand, size_t nHeadLength, size_t nBufLength) : 
			m_pStrand(NULL), m_sock(ioService), m_bConnect(false), m_pMsgParser(NULL), m_nHeadLength(nHeadLength), m_nBufLength(nBufLength), m_uRemotePort(0), m_bGetRemoteInfo(false)
		{
			m_pStrand = &strand;
			// to use memory pool later
			m_pBuff = new char[m_nBufLength];
			if (!m_pBuff)
			{
				exit(1);				// 程序退出
			}
		}

		// the async_write call back
		void HandleSend(const boost::system::error_code& error, std::size_t bytes_transferred);
		void HandleReadBody(const BoostErrCode& errCode, size_t nBytesTranfered);
		void HandleReadHeader(const BoostErrCode& errCode, size_t nBytesTranfered);
		void SetAsyncHandler();

		// 检查错误码，是否有错误
		bool CheckErrCode(const BoostErrCode& errCode);

	private:
		BoostStrand* m_pStrand;
		BoostSocket m_sock;								// the connection socket
		bool m_bConnect;								// 是否已经连接
		char* m_pBuff;
		recvFuncCallBack recvCallBack;
		sendFuncCallBack sendCallBack;
		connFuncCallBack connCallback;
		disConnFuncCallBack disConnCallback;
		IMsgParser* m_pMsgParser;
		deque<string> m_msgQueue;

		size_t m_nHeadLength;							// 消息头的大小
		size_t m_nBufLength;							// 接收缓冲区的大小

		string m_strRemoteIp;
		uint32_t m_uRemotePort;
		bool m_bGetRemoteInfo;

		boost::mutex m_mutex;
	};
}
#endif 