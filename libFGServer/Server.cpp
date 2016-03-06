#include "stdafx.h"
#include "Server.h"

using namespace boost::asio;
using namespace boost::asio::ip;

namespace FG
{
	Server::Server() : acc(IOService.get())
	{
	}

	Server::~Server()
	{
	}

	void Server::Init(int port)
	{
		acc.bind(tcp::endpoint(tcp::v4(), port));
		acc.listen();
	}

	void Server::OnConnect()
	{
		io_service serv;
		tcp::socket socket(IOService.get());
		acc.accept(socket);
	}
}