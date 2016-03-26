#pragma once

#include "Connection.h"

namespace FG
{
	class Server
	{
	public:
		Server();
		~Server();

		void Init(int port);
		void Listen();
		void Run();

		void Accept(Connection::Pointer& conn);

	private:
		boost::asio::io_service ioService;
		boost::asio::ip::tcp::acceptor acc;
	};
}