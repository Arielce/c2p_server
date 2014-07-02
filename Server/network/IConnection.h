#ifndef NETWORK_ICONNECTION_H
#define NETWORK_ICONNECTION_H

#include "header.h"
#include "IMsgParser.h"

namespace cpnet
{
	class IConnection
	{
	public:
		virtual const char* GetRemoteIp() = 0;
		virtual uint32_t GetRemotePort() = 0;
		virtual bool IsConnected() = 0;
		virtual void SetRecvCallback(const recvFuncCallBack& _recvCallBack) = 0;
		virtual void SetSendCallback(const sendFuncCallBack& _sendCallBack) = 0;
		virtual void SetMsgParser(IMsgParser* pMsgParser) = 0;
		virtual void SendMsg(const void* pData, uint32_t nLen) = 0;
	};
}

#endif