// Ping.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Ping1.h"

// Description:
//    Print usage information
//

int main(int argc, char* argv[])
{   
	/*
	char* temp = "127.0.0.1";
	argv = &temp;*/

	if (argc != 2)
	{
		printf("You must specify who you want to ping on the command line\n");
		return -1;
	}
	
	CPing ping;
	ping.ValidateArgs(argc, argv);

	ping.Ping();
	Sleep(1000);
	printf("Ping end!\n");
	ping.Cleanup();
    getchar();
	return 0;
	
}
