#ifndef __UTIL_UUID_H__
#define __UTIL_UUID_H__

#include <stdint.h>

namespace cpnet
{
	// twitter snowflake�㷨
	// 64       63--------------22---------12---------0
	// ����λ   |     41λʱ��   |10λ������|12λ������|
	extern uint64_t get_time();

	class GenUUID
	{
	public:
		GenUUID();
		~GenUUID();

		void set_epoch(uint64_t epoch);
		void set_machine(int32_t machine);
		int64_t generate();

	private:
		uint64_t epoch_;
		uint64_t time_;
		int32_t machine_;
		static int32_t sequence_;
	};

}

#endif // !__UTIL_UUID_H__