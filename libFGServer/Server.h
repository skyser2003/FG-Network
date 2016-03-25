#pragma once

#include "Property.h"

namespace FG
{
	class Server
	{
	public:
		FTL::Property<Server, boost::asio::io_service, false, true> IOService;

		Server();
		~Server();

		void Init(int port);
		void Run();

		void OnConnect();

	private:
		boost::asio::ip::tcp::acceptor acc;
	};
}