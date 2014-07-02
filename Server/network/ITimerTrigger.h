#ifndef NETWORK_ITIMERTRIGGER_H
#define NETWORK_ITIMERTRIGGER_H

#include "header.h"

namespace cpnet
{
	class ITimerTrigger
	{
	public:
		virtual void AddCircleTimer(TriggerCallback triggerCallback, size_t nIntervalTime) = 0;
		virtual void AddOnceTimer(TriggerCallback triggerOnceCallback, size_t nIntervalTime) = 0;
	};
}

#endif