// TCPSocket.h: interface for the CTCPSocket class.
//
//////////////////////////////////////////////////////////////////////
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

#if !defined(AFX_TCPSOCKET_H__77DA7F21_291E_4C2A_B12B_535ABA1E829C__INCLUDED_)
#define AFX_TCPSOCKET_H__77DA7F21_291E_4C2A_B12B_535ABA1E829C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SpoofSocket.h"
#include "AsyncSocket.h"

/////////////////////////////////////////////////////////////////////////////
// CSpoofSocket command target
//////////////////////////////////////////////////////////////////
//																//
//							TCP Header							//
//				Implementation of RFC793 TCP Header				//
//																//
//////////////////////////////////////////////////////////////////

typedef struct _TCPHeader
{
	//TCPPseudoHeader	PseudoHeader;
	unsigned short	SourcePort;
	unsigned short	DestinationPort;
	unsigned int	SequenceNumber;
	unsigned int	AcknowledgeNumber;
	//unsigned int	DataOffset:4;
	//unsigned int	Reserved:6;				//Must be zeros
	//unsigned int	ControlFlags:6;			//URG/ACK/SYN
	unsigned char	DataOffset;		//Crappy MFC can't use bits
	unsigned char	Flags;
	unsigned short	Windows;
	unsigned short	Checksum;
	unsigned short	UrgentPointer;
} TCPHeader;

typedef TCPHeader FAR * LPTCPHeader;

#define TCPHeaderLength sizeof(TCPHeader)

//All of the TRP header flags
#define TCPFlag_URG 0
#define TCPFlag_ACK 2
#define TCPFlag_PSH 4
#define TCPFlag_RST 8
#define TCPFlag_SYN 16
#define TCPFlag_FYN 32

//TCP Options
#define TCPOptions_END 0
#define TCPOptions_NO_OPERATION 1
#define TCPOptions_MAX_Segment 2

//Max segment size
#define TCPOptions_MAX_Segment_Length 4

class CTCPOptions : protected CIPOptions
{
public:
	//Add options Segment size
	void AddOption_SegmentSize(unsigned short usMax);

	//Reset all the data in the options
	void Reset();

	//Do we auto pad to a 4 bytes limit
	void SetAutoPad(BOOL bAutoPAD);

	//List terminator
	virtual void AddOption_ENDLIST();

	//Get the length of the options buffer
	int GetBufferLength();

	//Get the buffer itself
	const char* GetBuffer();

	//Add option nothing
	virtual void AddOption_Nothing();

	//ctor and dtor
	CTCPOptions();
	virtual ~CTCPOptions();
};

class CTCPSocket : public CSpoofSocket
{
public:
	//Send data over the sockets
	BOOL Send(char* buf,int bufLen);

	//Accept a connection, supply an already made socket
	BOOL Accept(CTCPSocket* tSok);

	//Accept a connection, create the socket class
	CTCPSocket* Accept();

	//Listen to incoming connections
	virtual BOOL Listen(int iBackLog);

	//Create this socket as a regular socket
	virtual BOOL CreateRegular();

	//Get the class of the TCP options
	CTCPOptions* GetTCPOptions();

	//Connect to a remote system
	virtual BOOL Connect(int iSourcePort,LPCSTR lpDestinationAddress,int iDestinationPort);

	//Create as a raw socket
	virtual BOOL Create();

	//Supply the class of TCP options
	void SetTCPOptions(BOOL bOptions);

	//ctor and dtor
	CTCPSocket();
	virtual ~CTCPSocket();
private:
	//Initialize the class
	void InitializeTCP();

	//Attach to a socket
	CTCPSocket(SOCKET sok);
	
	//Set flags in the header
	void SetHeaderFlag(LPTCPHeader lpHead,int iFlag);

	//Create the TCP header
	LPTCPHeader ConstructTCPHeader(int iSourcePort,int iDestinationPort,int iHeaderLength);

	//The TCP options
	CTCPOptions* m_TCPOptions;

	//Do we have options
	BOOL m_Options;

	//Sequence in the TCP header
	static unsigned int m_Sequence;
protected:
	//When the socket is accepted, what to do
	virtual void Accepted();
};

#endif // !defined(AFX_TCPSOCKET_H__77DA7F21_291E_4C2A_B12B_535ABA1E829C__INCLUDED_)
