// asio.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "iostream"
#include <boost/filesystem.hpp>

using boost::asio::ip::tcp;

const int max_length = 1024;

typedef boost::shared_ptr<tcp::socket> socket_ptr;

void session(socket_ptr sock)
{
	try
	{
		boost::filesystem::fstream wf("C:\\Users\\alex.liang\\Documents\\aws_copy_1.pdf", (boost::filesystem::fstream::out | boost::filesystem::fstream::binary));
		for (;;)
		{
			char data[max_length];

			boost::system::error_code error;
			size_t length = sock->read_some(boost::asio::buffer(data), error);
			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			//boost::asio::write(*sock, boost::asio::buffer(data, length));

			wf.write(data, length);
		}

		wf.close();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception in thread: " << e.what() << "\n";
	}
}

void server(boost::asio::io_context& io_context, unsigned short port)
{
	tcp::acceptor a(io_context, tcp::endpoint(tcp::v4(), port));
	for (;;)
	{
		socket_ptr sock(new tcp::socket(io_context));
		a.accept(*sock);
		boost::thread t(boost::bind(session, sock));
	}
}

int main(int argc, char* argv[])
{
	try
	{
		

		//unsigned short port;
		//std::cin >> port;

		boost::asio::io_context io_context;

		using namespace std; // For atoi.
		server(io_context, 63333);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}