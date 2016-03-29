#include "stdafx.h"
#include "Connection.h"

#include <ctime>

using namespace std;
using namespace boost::asio;

namespace FG
{
	std::string make_daytime_string()
	{
		time_t now = time(0);
		char buf[26];
		ctime_s(buf, sizeof(buf), &now);
		return buf;
	}

	Connection::Connection(boost::asio::io_service& ioService) : socket(ioService)
	{
	}

	Connection::~Connection()
	{

	}

	void Connection::Send(int size, char* data)
	{
		async_write(socket,
			boost::asio::buffer(data, size),
			boost::bind(&Connection::HandleWrite, shared_from_this())
			);
	}

	void Connection::BeginReceive(ReceiveHandler receiveHandler)
	{
		this->receiveHandler = receiveHandler;

		socket.async_receive(
			boost::asio::buffer(buffer),
			std::bind(&Connection::HandleReceive, shared_from_this(), std::placeholders::_1, std::placeholders::_2)
			);
	}

	void Connection::HandleWrite()
	{

	}

	void Connection::HandleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
	{
		if (receiveHandler != nullptr)
		{
			receiveHandler(bytes_transferred, buffer);
		}
	}

	Connection::Socket& Connection::GetSocket()
	{
		return socket;
	}
}