#include "Uuid.h"
#if !defined(_MSC_VER)
#include <sys/time.h>
#include <unistd.h>
#define EPOCHFILETIME 11644473600000000ULL
#else
#include <windows.h>
#include <time.h>
#define EPOCHFILETIME 11644473600000000Ui64
#endif

namespace cpnet
{
	int32_t GenUUID::sequence_ = 0;
	uint64_t get_time()
	{
#ifndef _MSC_VER
		struct timeval tv;
		gettimeofday(&tv, NULL);
		uint64_t time = tv.tv_usec;
		time /= 1000;
		time += (tv.tv_sec * 1000);
		return time;
#else
		FILETIME filetime;
		uint64_t time = 0;
		GetSystemTimeAsFileTime(&filetime);

		time |= filetime.dwHighDateTime;
		time <<= 32;
		time |= filetime.dwLowDateTime;

		time /= 10;
		time -= EPOCHFILETIME;
		return time / 1000;
#endif
	}

	GenUUID::GenUUID()
	{
		epoch_ = 0;
		time_ = 0;
		machine_ = 0;
	}

	GenUUID::~GenUUID()
	{

	}

	void GenUUID::set_epoch(uint64_t epoch)
	{
		epoch_ = epoch;
	}

	void GenUUID::set_machine(int32_t machine)
	{
		machine_ = machine;
	}

	int64_t GenUUID::generate()
	{
		int64_t value = 0;
		uint64_t time = get_time() - epoch_;

		// ������41λʱ��
		value = time << 22;

		// �м�10λ�ǻ���ID
		value |= (machine_ & 0x3FF) << 12;

		// ���12λ��sequenceID
		value |= sequence_++ & 0xFFF;
		if (sequence_ == 0x1000)
		{
			sequence_ = 0;
		}

		return value;
	}
}