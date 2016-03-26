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

	void Server::Init(int port)
	{
		acc.bind(tcp::endpoint(tcp::v4(), port));
	}

	void Server::Listen()
	{
		Connection::Pointer conn = Connection::create(acc.get_io_service());

// 		acc.async_accept(
// 			conn->Socket.get(),
// 			boost::bind(&Server::Accept, this, conn)
// 			);
	}

	void Server::Run()
	{
		ioService.run();
	}

	void Server::Accept(Connection::Pointer& conn)
	{
		tcp::socket socket(ioService);
		acc.accept(socket);
	}
}