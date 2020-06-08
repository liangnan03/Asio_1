// asio_client.cpp : Defines the entry point for the console application.
//


#define BOOST_FILESYSTEM_NO_DEPRECATED
#define BOOST_FILESYSTEM_DYN_LINK
#define BOOST_FILESYSTEM_NO_LIB

#include "stdafx.h"


#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
using namespace boost::filesystem;


#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

enum { max_length = 1024 };

//int main()
//{
//    return 0;
//}

int main(int argc, char* argv[])
{
	try
	{
		//if (argc != 3)
		//{
		//	std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
		//	return 1;
		//}
		char buf[512] = { 0 };
		boost::filesystem::fstream rf("C:\\Users\\alex.liang\\Documents\\aws.pdf", (boost::filesystem::fstream::in | boost::filesystem::fstream::binary));

		boost::asio::io_context io_context;

		tcp::resolver resolver(io_context);
		tcp::resolver::results_type endpoints =
			resolver.resolve(tcp::v4(), "192.168.3.92", "63333");

		tcp::socket s(io_context);
		boost::asio::connect(s, endpoints);

		//using namespace std; // For strlen.
		//std::cout << "Enter message: ";
		//char request[max_length];
		//std::cin.getline(request, max_length);
		//size_t request_length = strlen(request);
		while (1)
		{
			if (rf.eof())
				break;
			rf.read(buf, 512);
			int nBytesRead = rf.gcount();
			if (nBytesRead <= 0)
				break;
			
			boost::asio::write(s, boost::asio::buffer(buf, nBytesRead));
		}
		
		

		//char reply[max_length];
		//size_t reply_length = boost::asio::read(s,
			//boost::asio::buffer(reply, request_length));
		//std::cout << "Reply is: ";
		//std::cout.write(reply, reply_length);
		//std::cout << "\n";

		//s.close();
		int abc;
		std::cin >> abc;
		rf.close();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}

