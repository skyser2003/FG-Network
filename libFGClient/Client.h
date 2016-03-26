#pragma once

namespace FG
{
	class Client
	{
	public:
		void Init(std::string ip, int port);

	private:
		boost::asio::io_service ioService;
	};
}