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

		void Connect(const std::string& ip, int port);

		void SetConnectHandler(ConnectHandler connectHandler);

	private:
		void OnConnect(const boost::system::error_code& error);

		boost::asio::io_service ioService;

		ConnectHandler connectHandler;
	};
}