#pragma once

#include "Property.h"
#include "Connection.h"

namespace FG
{
	class Server
	{
	public:
		FTL::Property<Server, boost::asio::io_service, false, true> IOService;

		Server();
		~Server();

		void Init(int port);
		void Listen();
		void Run();

		void Accept(Connection::Pointer& conn);

	private:
		boost::asio::ip::tcp::acceptor acc;
	};
}