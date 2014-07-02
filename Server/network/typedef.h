#ifndef NETWORK_TYPEDEF_H
#define NETWORK_TYPEDEF_H

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/function.hpp>

namespace cpnet
{
	typedef boost::asio::io_service BoostIoService;
	typedef boost::asio::ip::tcp BoostTcp;
	typedef boost::asio::ip::tcp::acceptor BoostAcceptor;
	typedef boost::asio::ip::address BoostAddress;
	typedef boost::asio::ip::tcp::endpoint BoostEndPoint;
	typedef boost::asio::ip::tcp::socket BoostSocket;
	typedef boost::system::error_code BoostErrCode;
	typedef boost::asio::deadline_timer BoostTimer;

	class IConnection;

	typedef boost::function<void(cpnet::IConnection*, const char*, int)> recvFuncCallBack;			// the recv call back 
	typedef boost::function<void(const BoostErrCode&, std::size_t)> sendFuncCallBack;				// the send call back 
	typedef boost::function<void(cpnet::IConnection*, const BoostErrCode&)> connFuncCallBack;		// connection call back
	typedef boost::function<void(cpnet::IConnection*, const BoostErrCode&)> disConnFuncCallBack;	// disconnection call back
	typedef boost::function<void(cpnet::IConnection*, const BoostErrCode&)> acceptFuncCallBack;		// accept call back
	typedef boost::function<void(const boost::system::error_code&)> TriggerCallback;
}


#endif