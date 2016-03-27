#include "stdafx.h"

#include <iostream>
#include <functional>
#include <thread>
using namespace std;

#include "Server.h"
#include "Client.h"

int main()
{
	FG::Server server;
	server.Bind(80);
	server.Listen();

	thread serverThread([&server]()
	{
		while (true)
		{
			server.Run();
		}
	});
	serverThread.detach();

	FG::Client client;
	client.Init("localhost", 80);

	FG::Client client2;
	client2.Init("localhost", 80);

	system("pause");
	return 0;
}