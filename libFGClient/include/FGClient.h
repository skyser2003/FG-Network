#pragma once

#include <functional>

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "FGNetworkSharedHelper.h"

namespace FG
{
	class Client
	{
	public:
		using ConnectHandler = std::function<void(ConnectionPointer&)>;

		Client();

		void Run();

		void Connect(const std::string& ip, int port);

		void SetConnectHandler(ConnectHandler connectHandler);

	private:
		void OnConnect(ConnectionPointer conn, const boost::system::error_code& error, boost::asio::ip::tcp::resolver::iterator it);

		boost::asio::io_service ioService;

		ConnectHandler connectHandler;
	};
}