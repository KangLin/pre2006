// KIPConfig.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Interfaces.h"

void GeneralErrorMessage(CInterfaces* pInter,char* cError)
{
	printf("%s\n",cError);

	pInter->ShutdownSockets();

	delete pInter;
}

int main(int argc, char* argv[])
{

	//Our interfaces
	CInterfaces* pInter;
	pInter=new CInterfaces;

	//Initalize data
	if (!pInter->InitializeSockets())
	{
		GeneralErrorMessage(pInter,"Sockets couldn't be initialized");
		return 1;
	}
	
	//Get the interfaces
	if (!pInter->GetInterfaces())
	{
		GeneralErrorMessage(pInter,"Failed to get interfaces!");
		return 2;
	}

	//Print them
	BOOL bQuit=FALSE;

	while (!bQuit)
	{
		//Print the interface
		printf("Interface: %s\n",pInter->LongToString(pInter->GetAddress()));
		printf("Mask     : %s\n",pInter->LongToString(pInter->GetMask()));

		//Check if support broadcast
		if (pInter->IsBroadcast())
			printf("Broadcast: %s\n",pInter->LongToString(pInter->GetBroadcast()));

		//Check if running
		if (pInter->IsRunning())
			printf("Interface is running.\n");

		//Check if it's a PPP
		if (pInter->IsPPP())
			printf("Interface is a PPP connection.\n");

		//Check if it's a loopback
		if (pInter->IsLoopback())
			printf("Interface is a loopback interface.\n");

		//Check if it's support multicast
		if (pInter->IsMulticast())
			printf("Interface supports multicast.\n");

		bQuit=!pInter->MoveNext();
	}

	//Shutdown
	pInter->ShutdownSockets();

	//Dispose
	delete pInter;

	return 0;
}
