#pragma once

#include <memory>

#include <boost/asio.hpp>

namespace FG
{
	class Connection : public std::enable_shared_from_this<Connection>
	{
	public:
		typedef std::shared_ptr<Connection> Pointer;
		typedef boost::asio::ip::tcp::socket Socket;

		using ReceiveHandler = std::function<void(int, char*)>;

		static Pointer create(boost::asio::io_service& ioService)
		{
			return Pointer(new Connection(ioService));
		}

		Connection(boost::asio::io_service& ioService);
		~Connection();

		void Send(int size, char* data);
		void BeginReceive(ReceiveHandler receiveHandler);

		void HandleWrite();
		void HandleReceive(const boost::system::error_code& error, std::size_t bytes_transferred);

		Socket& GetSocket();

	private:
		Socket socket;

		ReceiveHandler receiveHandler;
		char buffer[255];
	};
}