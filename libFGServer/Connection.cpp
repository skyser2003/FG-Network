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
		char buf[25];
		ctime_s(buf, sizeof(buf), &now);
		return buf;
	}

	Connection::Connection(boost::asio::io_service& ioService) : socket(ioService)
	{
	}

	Connection::~Connection()
	{

	}

	void Connection::Start()
	{
		message = make_daytime_string();

		async_write(socket,
			boost::asio::buffer(message),
			boost::bind(&Connection::HandleWrite, shared_from_this())
			);
	}

	void Connection::HandleWrite()
	{

	}

	Connection::Socket& Connection::GetSocket()
	{
		return socket;
	}
}