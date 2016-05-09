#include "stdafx.h"
#include "Server.h"

#include "FGConnection.h"

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

		NewAccept();
	}

	void Server::Run()
	{
		ioService.run();
	}

	void Server::HandleAccept(ConnectionPointer& conn)
	{
		if (acceptHandler != nullptr)
		{
			acceptHandler(conn);
		}

		conn->BeginReceive();

		NewAccept();
	}

	void Server::SetAcceptHandler(AcceptHandler acceptHandler)
	{
		this->acceptHandler = acceptHandler;
	}

	void Server::NewAccept()
	{
		ConnectionPointer newConn = Connection::create(acc.get_io_service());

		acc.async_accept(
			newConn->GetSocket(),
			boost::bind(&Server::HandleAccept, this, newConn)
			);
	}
}