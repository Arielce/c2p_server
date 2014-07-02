#ifndef NETWORK_TIMERTRIGGER
#define NETWORK_TIMERTRIGGER

#include "header.h"
#include "ITimerTrigger.h"

namespace cpnet
{
	class TimerTrigger : public ITimerTrigger
	{
	public:
		typedef TimerTrigger* pointer;

		TimerTrigger(BoostIoService& ioService, BoostStrand& strand)
		{
			m_pIoService = &ioService;
			m_pStrand = &strand;
		}

		virtual void AddCircleTimer(TriggerCallback triggerCallback , size_t nIntervalTime)
		{
			BoostTimer* timer = new BoostTimer(*m_pIoService, boost::posix_time::seconds(nIntervalTime));
			m_timerList.push_back(timer);
			m_triggerCallbackMap.insert(make_pair(timer, triggerCallback));
			m_intervalTimeMap.insert(make_pair(timer, nIntervalTime));
			timer->async_wait(m_pStrand->wrap(boost::bind(&TimerTrigger::HandleCircleTimer, this, boost::asio::placeholders::error, timer)));
		}

		virtual void AddOnceTimer(TriggerCallback triggerOnceCallback, size_t nIntervalTime)
		{
			BoostTimer* timer = new BoostTimer(*m_pIoService, boost::posix_time::seconds(nIntervalTime));
			m_timerList.push_back(timer);
			m_triggerCallbackMap.insert(make_pair(timer, triggerOnceCallback));
			m_intervalTimeMap.insert(make_pair(timer, nIntervalTime));
			timer->async_wait(m_pStrand->wrap(boost::bind(&TimerTrigger::HandleOnceTimer, this, boost::asio::placeholders::error, timer)));
		}

	private:
		void HandleCircleTimer(const boost::system::error_code& errCode, BoostTimer* pTimer)
		{
			map<BoostTimer*, TriggerCallback>::iterator callbackIt = m_triggerCallbackMap.find(pTimer);
			if (callbackIt == m_triggerCallbackMap.end())
			{
				return;
			}
			map<BoostTimer*, size_t>::iterator timeIt = m_intervalTimeMap.find(pTimer);
			if (timeIt == m_intervalTimeMap.end())
			{
				return;
			}

			TriggerCallback& triggerCallback = callbackIt->second;
			triggerCallback(errCode);
			pTimer->expires_at(pTimer->expires_at() + boost::posix_time::seconds(timeIt->second));
			pTimer->async_wait(m_pStrand->wrap(boost::bind(&TimerTrigger::HandleCircleTimer, this, boost::asio::placeholders::error, pTimer)));
		}

		void HandleOnceTimer(const boost::system::error_code& errCode, BoostTimer* pTimer)
		{
			map<BoostTimer*, TriggerCallback>::iterator callbackIt = m_triggerCallbackMap.find(pTimer);
			if (callbackIt == m_triggerCallbackMap.end())
			{
				return;
			}
			map<BoostTimer*, size_t>::iterator timeIt = m_intervalTimeMap.find(pTimer);
			if (timeIt == m_intervalTimeMap.end())
			{
				return;
			}

			TriggerCallback& triggerCallback = callbackIt->second;
			triggerCallback(errCode);
			if (pTimer)
			{
				delete pTimer;
			}
			m_triggerCallbackMap.erase(callbackIt);
		}

	private:
		BoostIoService* m_pIoService;
		BoostStrand* m_pStrand;

		vector<BoostTimer*> m_timerList;
		map<BoostTimer*, TriggerCallback> m_triggerCallbackMap;
		map<BoostTimer*, size_t> m_intervalTimeMap;
	};
}

#endif