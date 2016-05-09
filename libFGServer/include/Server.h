#pragma once

#include "Connection.h"

#include <functional>

namespace FG
{
	class Server
	{
	public:
		using AcceptHandler = std::function<void(Connection::Pointer&)>;

		Server();
		~Server();

		void Bind(int port);
		void Listen();
		void Run();

		void HandleAccept(Connection::Pointer& conn);

		void SetAcceptHandler(AcceptHandler acceptHandler);

	private:
		void NewAccept();

		boost::asio::io_service ioService;
		boost::asio::ip::tcp::acceptor acc;

		AcceptHandler acceptHandler;
	};
}