#pragma once

#include <memory>
#include <atomic>

#include <boost/asio.hpp>

#include "FGNetworkSharedHelper.h"

namespace FG
{
	class Connection : public std::enable_shared_from_this<Connection>
	{
	public:
		typedef boost::asio::ip::tcp::socket Socket;

		using ReceiveHandler = std::function<void(int, char*)>;
		using DisconnectHandler = std::function<void(void)>;

		static ConnectionPointer create(boost::asio::io_service& ioService)
		{
			return ConnectionPointer(new Connection(ioService));
		}

		explicit Connection(boost::asio::io_service& ioService);
		~Connection();

		void Send(int size, const char* data);
		void BeginReceive();

		void HandleWrite();
		void HandleReceive(const boost::system::error_code& error, std::size_t bytes_transferred);

		void SetReceiveHandler(ReceiveHandler receiveHandler);
		void SetDisconnectHandler(DisconnectHandler disconnectHandler);

		Socket& GetSocket();
		int GetID() const;

	private:
		void HandleDisconnect();

		static std::atomic<int> nextID;

		int id;
		Socket socket;

		ReceiveHandler receiveHandler;
		char buffer[255];

		DisconnectHandler disconnectHandler;
	};
}