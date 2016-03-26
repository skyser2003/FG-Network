#pragma once

namespace FG
{
	class Connection : public std::enable_shared_from_this<Connection>
	{
	public:
		typedef std::shared_ptr<Connection> Pointer;

		static Pointer create(boost::asio::io_service& ioService)
		{
			return Pointer(new Connection(ioService));
		}

//		FTL::Property<Connection, boost::asio::ip::tcp::socket, false, true> Socket;

		Connection(boost::asio::io_service& ioService);
		~Connection();

		void Start();
		void HandleWrite();

	private:
		std::string message;
	};
}