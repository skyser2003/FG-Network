#pragma once

#include <functional>

#include <boost/asio.hpp>

#include "FGNetworkSharedHelper.h"

namespace FG
{
	class Server
	{
	public:
		using AcceptHandler = std::function<void(ConnectionPointer&)>;

		Server();
		~Server();

		void Bind(int port);
		void Listen();
		void Run();

		void HandleAccept(ConnectionPointer& conn);

		void SetAcceptHandler(AcceptHandler acceptHandler);

	private:
		void NewAccept();

		boost::asio::io_service ioService;
		boost::asio::ip::tcp::acceptor acc;

		AcceptHandler acceptHandler;
	};
}