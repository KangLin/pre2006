// sendarp.cpp : Defines the entry point for the console application.
//

//
// Link with ws2_32.lib and iphlpapi.lib
//
#include "stdafx.h"

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <iphlpapi.h>
#include <Winsock2.h>
#include <string>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

using namespace std;

int __cdecl _tmain(int argc, TCHAR * argv[])
{
	HRESULT hr;
	IPAddr  ipAddr;
	ULONG   pulMac[2];
	ULONG   ulLen;
	int i = 0;
	string szIP = "192.168.164.";
	string szTmp = szIP;
	char szDes[10];

	for(i = 0; i <= 255; i++)
	{
		sprintf(szDes, "%d", i);
		szTmp = szIP + szDes;
		printf("IP address:%s\n", szTmp.c_str());
		ipAddr = inet_addr(szTmp.c_str());
		memset (pulMac, 0xff, sizeof (pulMac));
		ulLen = 6;

		hr = SendARP (ipAddr, 0, pulMac, &ulLen);
		printf ("Return %08x, length %8d\n", hr, ulLen);
		if(hr == NO_ERROR)
		{
			size_t i, j;
			char * szMac = new char[ulLen*3];
			PBYTE pbHexMac = (PBYTE) pulMac;

			//
			// Convert the binary MAC address into human-readable
			//
			for (i = 0, j = 0; i < ulLen - 1; ++i) {
				j += sprintf (szMac + j, "%02X:", pbHexMac[i]);
			}
			
			sprintf (szMac + j, "%02X", pbHexMac[i]);
			printf ("MAC address %s\n", szMac);

			delete [] szMac;
		} // ½áÊø if(hr != NO_ERROR)
	}// ½áÊø for(i = 0; i <= 255; i++)

    return 0;
}
