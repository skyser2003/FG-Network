#include "stdafx.h"
#include "Server.h"

#include "Connection.h"

using namespace boost::asio;
using namespace boost::asio::ip;

namespace FG
{
	Server::Server() : acc(ioService)
	{
	}

	Server::~Server()
	{
	}

	void Server::Bind(int port)
	{
		auto endpoint = tcp::endpoint(tcp::v4(), port);

		acc.open(endpoint.protocol());
		acc.bind(endpoint);
	}

	void Server::Listen()
	{
		acc.listen();

		Connection::Pointer conn = Connection::create(acc.get_io_service());

		acc.async_accept(
			conn->GetSocket(),
			boost::bind(&Server::Accept, this, conn)
			);
	}

	void Server::Run()
	{
		ioService.run();
	}

	void Server::Accept(Connection::Pointer& conn)
	{
		conn->Start();
	}
}