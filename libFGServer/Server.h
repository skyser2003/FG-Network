#pragma once

#include "Connection.h"

namespace FG
{
	class Server
	{
	public:
		Server();
		~Server();

		void Bind(int port);
		void Listen();
		void Run();

		void HandleAccept(Connection::Pointer& conn);

	private:
		void NewAccept();

		boost::asio::io_service ioService;
		boost::asio::ip::tcp::acceptor acc;
	};
}