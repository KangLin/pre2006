/*
 *
 *
 *  Copyright (c) 2000 Barak Weichselbaum <barak@komodia.com>
 *  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *
 * Contact info:
 * Site: http://www.komodia.com
 * Email: barak@komodia.com
 */

// ICMPSocket.h: interface for the CICMPSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ICMPSOCKET_H__543E6F8C_42FA_4317_B799_0056E8B44467__INCLUDED_)
#define AFX_ICMPSOCKET_H__543E6F8C_42FA_4317_B799_0056E8B44467__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SpoofSocket.h"

// Regular ICMP Header
typedef struct _ICMPHeader
{
  unsigned char			ICMPType;
  unsigned char			ICMPCode;			// Type sub code 
  unsigned short		ICMPChecksum;
  union
  {
	  struct {unsigned char uc1,uc2,uc3,uc4;} sUC;
	  struct {unsigned short us1,us2;} sUS;
	  unsigned long sUL;
  } sICMP;
  unsigned long			ICMP_Originate_Timestamp; // Not standard field in header, but reserved nonetheless
  unsigned long			ICMP_Receive_Timestamp;
  unsigned long			ICMP_Transmit_Timestamp;
} ICMPHeader;

typedef ICMPHeader FAR * LPICMPHeader;

#define ICMPHeaderLength sizeof(ICMPHeader)


// ICMP data size
#define ICMP_DATA_SIZE 8

// ICMP Message unreachable
#define ICMP_Unreachable 3
#define ICMP_Unreachable_SIZE 8

#define ICMP_Unreachable_NET 0
#define ICMP_Unreachable_HOST 1
#define ICMP_Unreachable_PROTOCOL 2
#define ICMP_Unreachable_PORT 3
#define ICMP_Unreachable_FRAGMENTATION 4
#define ICMP_Unreachable_SOURCE 5

// ICMP Time exceeded
#define ICMP_Time 11

#define ICMP_Time_TRANSIT 0
#define ICMP_Time_FRAGMENT 1

// ICMP Parameter problem
#define ICMP_Parameter 12

#define ICMP_Parameter_ERROR 0

// ICMP Source quench
#define ICMP_Quench 4

// ICMP Redirect
#define ICMP_Redirect 5

#define ICMP_Redirect_NETWORK 0
#define ICMP_Redirect_HOST 1
#define ICMP_Redirect_SERVICE_NETWORK 2
#define ICMP_Redirect_SERVICE_HOST 3

// ICMP Echo
#define ICMP_Echo 8
#define ICMP_Echo_Reply 0

// ICMP Timestamp
#define ICMP_Timestamp 13
#define ICMP_Timestamp_Reply 14

// ICMP Information request
#define ICMP_Information 15
#define ICMP_Information_Reply 16

#define ICMP_Information_SIZE 8

//Max buf
#define ICMP_BUF 100

class CICMPSocket : public CSpoofSocket  
{
public:
	//Get the last ICMP data
	const char* GetLastICMPData();

	//Get the last ICMP - IP header
	const LPIpHeader GetLastICMPIPHeader();

	//Get the last ICMP header size
	unsigned long GetLastDataSize();

	//The the last IP header
	const LPIpHeader GetLastIPHeader();

	//Get the last ICMP header
	const LPICMPHeader GetLastICMPHeader();

	//Send ICMP messages according to the name
	BOOL SendInformation(LPCSTR lpDestinationAddress,BOOL bReply,unsigned short usIdentifier,unsigned short usSequence);
	BOOL SendTimestamp(LPCSTR lpDestinationAddress,BOOL bReply,unsigned short usIdentifier,unsigned short usSequence,unsigned long ulOriginateTimestamp,unsigned long ulReceiveTimestamp,unsigned long ulTransmitTimestamp);
	BOOL SendEcho(LPCSTR lpDestinationAddress,BOOL bReply,unsigned short usIdentifier,unsigned short usSequence,unsigned long ulData);
	BOOL SendRedirect(LPCSTR lpDestinationAddress, unsigned char cType,LPCSTR lpGatewayAddress);
	BOOL SendQuench(LPCSTR lpDestinationAddress);
	BOOL SendParameter(LPCSTR lpDestinationAddress, unsigned char cError);
	BOOL SendTime(LPCSTR lpDestinationAddress,unsigned char cType);
	BOOL SendUnreachable(LPCSTR lpDestinationAddress,unsigned char cType);

	//Create an ICMP socket
	virtual BOOL Create();

	//ctor and dtor
	CICMPSocket();
	virtual ~CICMPSocket();
private:
	//The data
	char* m_Data;

	//The ICMP IP header
	LPIpHeader m_ICMPIPHeader;

	//Reverse the header (big little endian)
	void ReverseHeader();

	//The data size
	unsigned short m_DataSize;

	//The IP header
	LPIpHeader m_IPHeader;

	//The ICMP header
	LPICMPHeader m_ICMPHeader;

	//Send the data
	BOOL Send(LPCSTR lpDestinationAddress,unsigned char cICMP,unsigned char cType);
protected:
	//Construct an ICMP header
	virtual LPICMPHeader ConstructICMP();

	//Proccess incoming ICMP data
	virtual BOOL ProccessICMP(char* buf);
};

#endif // !defined(AFX_ICMPSOCKET_H__543E6F8C_42FA_4317_B799_0056E8B44467__INCLUDED_)
