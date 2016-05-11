#include "stdafx.h"
#include "FGClient.h"

#include "FGConnection.h"

#include <boost/bind.hpp>

using namespace std::placeholders;

using namespace boost::asio;
using namespace boost::asio::ip;

namespace FG
{
	Client::Client()
	{

	}

	void Client::Connect(const std::string& ip, int port)
	{
		tcp::resolver resolver(ioService);
		tcp::resolver::query query(ip, std::to_string(port));

		auto endpointIt = resolver.resolve(query);

		boost::system::error_code ec;

		auto newConn = Connection::create(ioService);
//		boost::asio::connect(newConn->GetSocket(), endpointIt, ec);
 		boost::asio::async_connect(newConn->GetSocket(), endpointIt, boost::bind(&Client::OnConnect, this, boost::placeholders::_1));
	}

	void Client::SetConnectHandler(ConnectHandler connectHandler)
	{
		this->connectHandler = connectHandler;
	}

	void Client::OnConnect(const boost::system::error_code& error)
	{
		if (connectHandler != nullptr)
		{
//			connectHandler(conn);
//			conn->BeginReceive();
		}
	}
}