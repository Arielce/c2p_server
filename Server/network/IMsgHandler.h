#ifndef DATASERVER_IMSGHANDLER_H
#define DATASERVER_IMSGHANDLER_H

#include "header.h"

namespace cpnet
{
	class IConnection;
	class IMsgHandler
	{
	public:
		virtual void HandleConnect(IConnection* pConn, const BoostErrCode& error) = 0;

		virtual void HandleDisconnect(IConnection* pConn, const BoostErrCode& error) = 0;

		virtual void HandleWrite(const boost::system::error_code& error, size_t bytes_transferred) = 0;

		virtual void HandleRecv(IConnection* pConn, const char* pBuf, uint32_t uLen) = 0;
	};
}

#endif