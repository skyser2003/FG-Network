#pragma once

namespace FG
{
	class Client
	{
	public:
		Client();

		void Init(std::string ip, int port);
		void Connect();

	private:
		boost::asio::io_service ioService;
		boost::asio::ip::tcp::socket socket;
	};
}