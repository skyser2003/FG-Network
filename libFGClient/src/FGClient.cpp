#include "stdafx.h"
#include "FGClient.h"

using namespace boost::asio;
using namespace boost::asio::ip;

namespace FG
{
	Client::Client() : socket(ioService)
	{

	}

	void Client::Init(std::string ip, int port)
	{
		tcp::resolver resolver(ioService);

		tcp::resolver::query query(ip, std::to_string(port));
		auto endpointIt = resolver.resolve(query);

		boost::asio::connect(socket, endpointIt);

		while (true)
		{
			boost::array<char, 128> buf;
			boost::system::error_code error;

			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			std::cout.write(buf.data(), len);
		}
	}
}