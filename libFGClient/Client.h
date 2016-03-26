#pragma once

#include "Property.h"

namespace FG
{
	class Client
	{
	public:
		FTL::Property<Client, boost::asio::io_service, false, true> IOService;

		void Init(std::string ip, int port);

	private:
	};
}