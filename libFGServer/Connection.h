#pragma once

namespace FG
{
	class Connection : public std::enable_shared_from_this<Connection>
	{
	public:
		typedef std::shared_ptr<Connection> Pointer;
		typedef boost::asio::ip::tcp::socket Socket;

		static Pointer create(boost::asio::io_service& ioService)
		{
			return Pointer(new Connection(ioService));
		}

		Connection(boost::asio::io_service& ioService);
		~Connection();

		void Start();
		void HandleWrite();

		Socket& GetSocket();

	private:
		Socket socket;

		std::string message;
	};
}