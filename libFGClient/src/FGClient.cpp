#include "stdafx.h"
#include "FGClient.h"

#include "FGConnection.h"

using namespace std::placeholders;

using namespace boost::asio;
using namespace boost::asio::ip;

namespace FG
{
	Client::Client()
	{

	}

	void Client::Init(std::string ip, int port)
	{
		endpoint.address(boost::asio::ip::address::from_string(ip));
		endpoint.port(port);
	}

	void Client::Connect()
	{
		ConnectionPointer newConn = Connection::create(ioService);
		newConn->GetSocket().async_connect(endpoint, std::bind(&Client::OnConnect, this, _1, newConn));
	}

	void Client::SetConnectHandler(ConnectHandler connectHandler)
	{
		this->connectHandler = connectHandler;
	}

	void Client::OnConnect(const boost::system::error_code& error, ConnectionPointer conn)
	{
		if (connectHandler != nullptr)
		{
			connectHandler(conn);
			conn->BeginReceive();
		}
	}
}