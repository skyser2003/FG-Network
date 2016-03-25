#include "stdafx.h"

#include <iostream>
#include <functional>
using namespace std;

#include "Server.h"

int main()
{
	FG::Server server;
	server.Run();

	return 0;
}