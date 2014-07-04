#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;

int total_conn = 0;

class session
	: public boost::enable_shared_from_this<session>
{
public:
	session(boost::asio::io_service& io_service)
		: socket_(io_service)
	{
	}

	tcp::socket& socket()
	{
		return socket_;
	}

	void start()
	{
		socket_.async_read_some(boost::asio::buffer(data_, max_length),
			boost::bind(&session::handle_read, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}

private:
	void handle_read(const boost::system::error_code& error,
		size_t bytes_transferred)
	{
		if (!error)
		{
			boost::asio::async_write(socket_,
				boost::asio::buffer(data_, bytes_transferred),
				boost::bind(&session::handle_write, shared_from_this(),
				boost::asio::placeholders::error));
		}
	}

	void handle_write(const boost::system::error_code& error)
	{
		if (!error)
		{
			socket_.async_read_some(boost::asio::buffer(data_, max_length),
				boost::bind(&session::handle_read, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}
	}

	tcp::socket socket_;
	enum { max_length = 1024 };
	char data_[max_length];
};

class server
{
public:
	server(boost::asio::io_service& io_service, short port)
		: io_service_(io_service),
		acceptor_(io_service)
		//acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
	{
		boost::asio::ip::tcp::endpoint endPoint(boost::asio::ip::address::from_string("192.168.1.34"), port);
		acceptor_.open(endPoint.protocol());
		acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
		acceptor_.bind(endPoint);
		acceptor_.listen();

		start_accept();
	}

private:
	void start_accept()
	{
		boost::shared_ptr<session> new_session(new session(io_service_));
		acceptor_.async_accept(new_session->socket(),
			boost::bind(&server::handle_accept, this, new_session,
			boost::asio::placeholders::error));
	}

	void handle_accept(boost::shared_ptr<session> new_session,
		const boost::system::error_code& error)
	{
		start_accept();

		if (!error)
		{
			//std::cout << "total connect =" << ++total_conn << std::endl;
			new_session->start();
		}
		else
		{
			std::cout << "accept error=" << error.message() << std::endl;
		}
	}

	boost::asio::io_service& io_service_;
	tcp::acceptor acceptor_;
};

int main(int argc, char* argv[])
{
	try
	{
		boost::asio::io_service io_service;

		using namespace std; // For atoi.
		server s(io_service, 8500);

		int thread_num = 4;

		boost::thread_group th_group; 
		for (int i=0; i<thread_num; ++i)
		{
			th_group.add_thread(new boost::thread(boost::bind(&boost::asio::io_service::run, &io_service)));
		}

		th_group.join_all();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
