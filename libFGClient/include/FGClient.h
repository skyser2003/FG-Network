#pragma once

#include <functional>

#include <boost/asio.hpp>

#include "FGNetworkSharedHelper.h"

namespace FG
{
	class Client
	{
	public:
		using ConnectHandler = std::function<void(ConnectionPointer&)>;

		Client();

		void Init(std::string ip, int port);
		void Connect();

		void SetConnectHandler(ConnectHandler connectHandler);

	private:
		void OnConnect(const boost::system::error_code& error, ConnectionPointer conn);

		boost::asio::io_service ioService;
		boost::asio::ip::tcp::endpoint endpoint;

		ConnectHandler connectHandler;
	};
}