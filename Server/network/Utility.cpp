#include "Utility.h"

namespace cpnet
{
	string GetProtoData(MessageHeader* pMsgHeader)
	{
		char* pBuf = (char*)pMsgHeader + sizeof(MessageHeader);
		int uDataSize = pMsgHeader->uMsgSize - sizeof(MessageHeader);
		return string(pBuf, uDataSize);
	}

	uint32_t GenRandom(uint32_t uMin, uint32_t uMax)
	{
		boost::random::mt19937 rng((uint32_t)std::time(0)); 
		boost::random::uniform_int_distribution<> randGen(uMin, uMax);
		return randGen(rng);
	}
}
