#include "stdafx.h"
#include "FGClient.h"

#include "FGConnection.h"

using namespace boost::asio;
using namespace boost::asio::ip;

using namespace std::placeholders;

namespace FG
{
	Client::Client()
	{

	}

	void Client::Run()
	{
		ioService.run();
	}

	void Client::Connect(const std::string& ip, int port)
	{
		tcp::resolver resolver(ioService);
		tcp::resolver::query query(ip, std::to_string(port));

		auto endpointIt = resolver.resolve(query);

		boost::system::error_code ec;

		auto newConn = Connection::create(ioService);
		boost::asio::async_connect(newConn->GetSocket(), endpointIt, std::bind(&Client::OnConnect, this, newConn, _1, _2));
	}

	void Client::SetConnectHandler(ConnectHandler connectHandler)
	{
		this->connectHandler = connectHandler;
	}

	void Client::OnConnect(ConnectionPointer conn, const boost::system::error_code& error, tcp::resolver::iterator it)
	{
		if (connectHandler != nullptr)
		{
			connectHandler(conn);
			conn->BeginReceive();
		}
	}
}