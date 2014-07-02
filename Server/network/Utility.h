#ifndef NETWORK_UTILITY_HPP
#define NETWORK_UTILITY_HPP

#include "header.h"
#include "MessageHeader.h"

namespace cpnet
{
	string GetProtoData(MessageHeader* pMsgHeader);

	// ����protobuf��request��Ϣ
	template <typename T>
	void BuildRequestProto(const T& requestData, string& strBuffer, uint32_t uMsgCmd)
	{
		string strOutput;
		requestData.SerializeToString(&strOutput);

		MessageHeader msgHeader; 
		msgHeader.uMsgSize = sizeof(MessageHeader) + strOutput.size();
		msgHeader.uMsgCmd = uMsgCmd;
		strBuffer.append((char*)&msgHeader, sizeof(MessageHeader));
		strBuffer.append(strOutput);
		return;
	}


	// ����protobuf��response��Ϣ
	template <typename T>
	void BuildResponseProto(const T& responseData, string& strBuffer, uint32_t uMsgCmd)
	{
		string strOutput;
		responseData.SerializeToString(&strOutput);

		MessageHeader msgHeader; 
		msgHeader.uMsgSize = sizeof(MessageHeader) + strOutput.size();
		msgHeader.uMsgCmd = uMsgCmd;
		strBuffer.append((char*)&msgHeader, sizeof(MessageHeader));
		strBuffer.append(strOutput);
		return;
	}

	// range in [uMin, uMax], not [uMin, uMax)
	uint32_t GenRandom(uint32_t uMin, uint32_t uMax);
}



#endif