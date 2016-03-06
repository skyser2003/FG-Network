#include "stdafx.h"
#include "Client.h"

using namespace boost::asio;
using namespace boost::asio::ip;

namespace FG
{
	void Client::Init(std::string ip, int port)
	{
		tcp::resolver resolver(ioService);
	}
}