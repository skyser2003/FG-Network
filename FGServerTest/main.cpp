#include "stdafx.h"

#include <iostream>
#include <functional>
#include <thread>
using namespace std;

#include "FGServer.h"
#include "FGClient.h"

int main()
{
	FG::Server server;

	thread serverThread([&server]()
	{
		FG::ConnectionPointer conn = nullptr;

		server.SetAcceptHandler([](auto& newConn)
		{
			cout << "boo" << endl;
		});

		server.Bind(80);
		server.Listen();

		while (true)
		{
			server.Run();
		}
	});

	serverThread.detach();

	FG::Client client1;
	FG::Client client2;

	client1.SetConnectHandler([](auto& conn)
	{
		cout << "client1 connected";
	});

	client2.SetConnectHandler([](auto& conn)
	{
		cout << "client2 connected";
	});

	client1.Connect("localhost", 80);
	client2.Connect("localhost", 80);

	while (true)
	{
		client1.Run();
		client2.Run();

		Sleep(1000);
		cout << "loop" << endl;
	}

	return 0;
}