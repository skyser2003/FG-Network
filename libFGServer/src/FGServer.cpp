#include "stdafx.h"
#include "FGServer.h"

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
		boost::system::error_code ec;

		auto endpoint = tcp::endpoint(tcp::v6(), port);

		acc.set_option(ip::v6_only(false), ec);

		if (ec.value() != 0)
		{
			// TODO
		}

		acc.open(endpoint.protocol());
		acc.bind(endpoint, ec);
		
		if (ec == error::address_in_use)
		{
			// TODO
		}
	}

	void Server::Listen()
	{
		acc.listen();

		NewAccept();
	}

	void Server::Run()
	{
		ioService.poll();
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