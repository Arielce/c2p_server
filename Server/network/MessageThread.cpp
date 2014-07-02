#include "MessageThread.h"

namespace cpnet
{
	MessageThread::MessageThread() : m_bRun(true)
	{

	}

	// 线程停止运行
	void MessageThread::Stop()
	{
		m_bRun = false;
		boost::lock_guard<boost::mutex> lock(m_mutex);
		m_cond.notify_one();
	}
	void MessageThread::Push(const Package& package)
	{
		boost::lock_guard<boost::mutex> lock(m_mutex);
		m_msgQueue.push_back(package);	
		m_cond.notify_one();
	}

	void MessageThread::Run()
	{
		while (m_bRun)
		{
			Package package;
			{
				boost::lock_guard<boost::mutex> lock(m_mutex);
				if (m_msgQueue.empty())
				{
					m_cond.wait(m_mutex);
				}

				if (m_msgQueue.empty())					// 可能是被外部停止运行了
				{
					continue;
				}
				
				package = m_msgQueue.front();
				m_msgQueue.pop_front();
			}

			BoostErrCode errCode;
			switch (package.packageType)
			{
			case CONNECT_MSG:		
				package.pConn->connCallback(package.pConn.get(), errCode);
				break;
			case DISCONNECT_MSG:
				package.pConn->disConnCallback(package.pConn.get(), errCode);
				break;
			case RECV_MSG:
				package.pConn->recvCallBack(package.pConn.get(), package.strMessage.c_str(), package.strMessage.size());
				break;
			case TIMER_MSG:
				package.triggerCallback(errCode);
				break;
			default:
				break;
			}
		}
	}
}
