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

#if !defined(AFX_SPOOFSOCKET_H__5BAEA068_961A_4652_8BBD_90B78F6FBB09__INCLUDED_)
#define AFX_SPOOFSOCKET_H__5BAEA068_961A_4652_8BBD_90B78F6FBB09__INCLUDED_

#include "KTRACERT\StdAfx.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpoofSocket.h : header file
//

#include "SpoofBase.h"

/////////////////////////////////////////////////////////////////////////////
// CSpoofSocket command target
//////////////////////////////////////////////////////////////////
//																//
//							IP Header							//
//				Implementation of RFC791 IP Header				//
//																//
//////////////////////////////////////////////////////////////////

typedef struct _PseudoHeader
{
	unsigned int	SourceAddress;
	unsigned int	DestinationAddress;
	unsigned char	Zeros;
	unsigned char	PTCL;
	unsigned short	Length;
} PseudoHeader;

typedef PseudoHeader FAR * LPPseudoHeader;

#define PseudoHeaderLength sizeof(PseudoHeader)

#define tOptionType unsigned char

typedef struct _IPOption
{
	tOptionType		OptionType;
	unsigned char	OptionLength;
	unsigned char	OptionData;
} IPOption;

//IP Options flags (1bit)
#define IPOption_COPY 128
#define IPOption_DONT_COPY 0

//IP Options class (2 bits)
#define IPOption_CONTROL 0
#define IPOption_RESERVED 2
#define IPOption_DEBUGGING 64
#define IPOption_RESERVED2 6

//IP options type
/*The Type of Service provides an indication of the abstract
  parameters of the quality of service desired.  These parameters are
  to be used to guide the selection of the actual service parameters
  when transmitting a datagram through a particular network.  Several
  networks offer service precedence, which somehow treats high
  precedence traffic as more important than other traffic (generally
  by accepting only traffic above a certain precedence at time of high
  load).  The major choice is a three way tradeoff between low-delay,
  high-reliability, and high-throughput.

  The use of the Delay, Throughput, and Reliability indications may
  increase the cost (in some sense) of the service.  In many networks
  better performance for one of these parameters is coupled with worse
  performance on another.  Except for very unusual cases at most two
  of these three indications should be set.

  The type of service is used to specify the treatment of the datagram
  during its transmission through the internet system.  Example
  mappings of the internet type of service to the actual service
  provided on networks such as AUTODIN II, ARPANET, SATNET, and PRNET
  is given in "Service Mappings" [8].

  The Network Control precedence designation is intended to be used
  within a network only.  The actual use and control of that
  designation is up to each network. The Internetwork Control
  designation is intended for use by gateway control originators only.
  If the actual use of these precedence designations is of concern to
  a particular network, it is the responsibility of that network to
  control the access to, and use of, those precedence designations.*/

#define IPOption_END_OPTION 0 //End of option list
#define IPOption_NO_OPERATION 1 //Do nothing
#define IPOption_SECURITY 2 //Security information
#define IPOption_LOOSE_ROUTING 3 //Loose routing options
#define IPOption_STRICT_ROUTING 9 //Strict source routing
#define IPOption_RECORD_ROUTE 7 //Record route on datagram
#define IPOption_STREAM 8 //Used to carry stream identifier
#define IPOption_TIMESTAMP 4 //Internet timestamp

//IP options extensions - Security
/*Specifies one of 16 levels of security (eight of which are
  reserved for future use).
  Compartments (C field):  16 bits

  An all zero value is used when the information transmitted is
  not compartmented.  Other values for the compartments field
  may be obtained from the Defense Intelligence Agency.

  Handling Restrictions (H field):  16 bits

	The values for the control and release markings are
    alphanumeric digraphs and are defined in the Defense
    Intelligence Agency Manual DIAM 65-19, "Standard Security
    Markings".

  Transmission Control Code (TCC field):  24 bits

	Provides a means to segregate traffic and define controlled
    communities of interest among subscribers. The TCC values are
    trigraphs, and are available from HQ DCA Code 530.

    Must be copied on fragmentation.  This option appears at most
    once in a datagram.*/

#define IPOption_SECURITY_LENGTH 11

#define IPOption_SECURITY_UNCLASSIFIED 0
#define IPOption_SECURITY_CONFIDENTIAL 0x1111000100110101b
#define IPOption_SECURITY_EFTO 0x0111100010011010b
#define IPOption_SECURITY_MMMM 0x1011110001001101b
#define IPOption_SECURITY_PROG 0x0101111000100110b
#define IPOption_SECURITY_RESTRICTED 0x1010111100010011b
#define IPOption_SECURITY_SECRET 0x1101011110001000b
#define IPOption_SECURITY_TOPSECRET 0x0110101111000101b
#define IPOption_SECURITY_RESERVED1 0x0011010111100010b
#define IPOption_SECURITY_RESERVED2 0x1001101011110001b 
#define IPOption_SECURITY_RESERVED3 0x0100110101111000b
#define IPOption_SECURITY_RESERVED4 0x0010010010111101b
#define IPOption_SECURITY_RESERVED5 0x0001001101011110b
#define IPOption_SECURITY_RESERVED6 0x1000100110101111b
#define IPOption_SECURITY_RESERVED7 0x1100010011010110b
#define IPOption_SECURITY_RESERVED8 0x1110001001101011b

/*This option provides a way for the 16-bit SATNET stream
identifier to be carried through networks that do not support
the stream concept.

Must be copied on fragmentation.  Appears at most once in a
datagram.*/

//IP options extensions - Stream ID
#define IPOption_STREAM_LENGTH 4

/*The loose source and record route (LSRR) option provides a means
for the source of an internet datagram to supply routing
information to be used by the gateways in forwarding the
datagram to the destination, and to record the route
information.

The option begins with the option type code.  The second octet
is the option length which includes the option type code and the
length octet, the pointer octet, and length-3 octets of route
data.  The third octet is the pointer into the route data
indicating the octet which begins the next source address to be
processed.  The pointer is relative to this option, and the
smallest legal value for the pointer is 4.

A route data is composed of a series of internet addresses.
Each internet address is 32 bits or 4 octets.  If the pointer is
greater than the length, the source route is empty (and the
recorded route full) and the routing is to be based on the
destination address field.

If the address in destination address field has been reached and
the pointer is not greater than the length, the next address in
the source route replaces the address in the destination address
field, and the recorded route address replaces the source
address just used, and pointer is increased by four.

The recorded route address is the internet module's own internet
address as known in the environment into which this datagram is
being forwarded.

This procedure of replacing the source route with the recorded
route (though it is in the reverse of the order it must be in to
be used as a source route) means the option (and the IP header
as a whole) remains a constant length as the datagram progresses
through the internet.

This option is a loose source route because the gateway or host
IP is allowed to use any route of any number of other
intermediate gateways to reach the next address in the route.

Must be copied on fragmentation.  Appears at most once in a
datagram.*/

/*The strict source and record route (SSRR) option provides a
means for the source of an internet datagram to supply routing
information to be used by the gateways in forwarding the
datagram to the destination, and to record the route
information.

The option begins with the option type code.  The second octet
is the option length which includes the option type code and the
length octet, the pointer octet, and length-3 octets of route
data.  The third octet is the pointer into the route data
indicating the octet which begins the next source address to be
processed.  The pointer is relative to this option, and the
smallest legal value for the pointer is 4.

A route data is composed of a series of internet addresses.
Each internet address is 32 bits or 4 octets.  If the pointer is
greater than the length, the source route is empty (and the

recorded route full) and the routing is to be based on the
destination address field.

If the address in destination address field has been reached and
the pointer is not greater than the length, the next address in
the source route replaces the address in the destination address
field, and the recorded route address replaces the source
address just used, and pointer is increased by four.

The recorded route address is the internet module's own internet
address as known in the environment into which this datagram is
being forwarded.

This procedure of replacing the source route with the recorded
route (though it is in the reverse of the order it must be in to
be used as a source route) means the option (and the IP header
as a whole) remains a constant length as the datagram progresses
through the internet.

This option is a strict source route because the gateway or host
IP must send the datagram directly to the next address in the
source route through only the directly connected network
indicated in the next address to reach the next gateway or host
specified in the route.

Must be copied on fragmentation.  Appears at most once in a
datagram.*/

//IP options extensions - Strict routing
#define IPOption_STRICT_ROUTING_LENGTH 3
#define IPOption_STRICT_ROUTING_POINTER 4

/*The Timestamp is a right-justified, 32-bit timestamp in
milliseconds since midnight UT.  If the time is not available in
milliseconds or cannot be provided with respect to midnight UT
then any time may be inserted as a timestamp provided the high
order bit of the timestamp field is set to one to indicate the
use of a non-standard value.

The originating host must compose this option with a large
enough timestamp data area to hold all the timestamp information
expected.  The size of the option does not change due to adding

timestamps.  The intitial contents of the timestamp data area
must be zero or internet address/zero pairs.

If the timestamp data area is already full (the pointer exceeds
the length) the datagram is forwarded without inserting the
timestamp, but the overflow count is incremented by one.

If there is some room but not enough room for a full timestamp
to be inserted, or the overflow count itself overflows, the
original datagram is considered to be in error and is discarded.
In either case an ICMP parameter problem message may be sent to
the source host [3].

The timestamp option is not copied upon fragmentation.  It is
carried in the first fragment.  Appears at most once in a
datagram.*/

//IP options extensions - Time Stamp
#define IPOption_TIMESTAMP_LENGTH 5

#define IPOption_TIMESTAMP_ONLY 0
#define IPOption_TIMESTAMP_EACH 1
#define IPOption_TIMESTAMP_PRE 2

#define IPOption_TIMESTAMP_SIZE 8


typedef struct _IpHeader 
{
	unsigned char		HeaderLength_Version;
	unsigned char		TypeOfService;		// Type of service
	unsigned short		TotalLength;		// total length of the packet
	unsigned short		Identification;		// unique identifier
	unsigned short		FragmentationFlags; // flags
	unsigned char		TTL;				// Time To Live
	unsigned char		Protocol;           // protocol (TCP, UDP etc)
	unsigned short		CheckSum;			// IP Header checksum

	unsigned int		sourceIPAddress;	// Source address
	unsigned int		destIPAddress;		// Destination Address

} IpHeader;

typedef IpHeader FAR * LPIpHeader;

#define IpHeaderLength sizeof(IpHeader)

//Some IP constants
//Version
#define IpVersion 4

//Service types
#define IpService_NETWORK_CONTROL 111
#define IpService_INTERNETWORK_CONTROL 110
#define IpService_CRITIC_ECP 101
#define IpService_FLASH_OVERIDE 100
#define IpService_FLASH 011
#define IpService_IMMEDIATE 010
#define IpService_PRIORITY 001
#define IpService_ROUTINE 0

//Fragmetation flag
#define IpFragFlag_MAY_FRAG 0x0000
#define IpFragFlag_MORE_FRAG 0x2000
#define IpFragFlag_LAST_FRAG 0x5000
#define IpFragFlag_DONT_FRAG 0x4000
 
//Internet protocols
#define IpProtocol_ICMP 1
#define IpProtocol_TCP 6
#define IpProtocol_UDP 17

#define IP_DEF_TTL 128

#define IPOption_WRAPSIZE 4
#define IPOption_SIZE 40

#define IPOption_MAX_ROUTES 10

typedef struct _Routing
{
	int iRoutes;
	unsigned long ulRoutes[IPOption_MAX_ROUTES];
} tRouting;

class CBinaryTree;

class CIPOptions : protected CSpoofBase
{	
public:
	//ctor and dtor
	CIPOptions();
	virtual ~CIPOptions();
private:
	//Do we autopard
	BOOL m_AutoPAD;

	//Length of the buffer
	int m_BufferLength;

	//The buffer
	char* m_Buffer;
protected:
	//Add option route
	void AddOption_Route(tOptionType tRouteType,tRouting tRoute);

	//Add data to the buffer
	void AddToBuffer(char* buf,int BufLength);

	//Create an options prototype
	tOptionType GetOption(unsigned char CopyFlag,unsigned char ClassFlag,unsigned char TypeFlag);
public:
	//Add options (according to the method name)
	void AddOption_Timestamp(tOptionType tFlags,int iMaxStamps);
	void AddOption_LooseRoute(tRouting tRoute);
	void AddOption_RecordRoute(int iMaxRoutes);
	void AddOption_StrictRoute(tRouting tRoute);
	void AddOption_Stream(unsigned short usStreamID);
	virtual void AddOption_Security(unsigned short usType);
	virtual void AddOption_Nothing();

	//Delete all the options
	void Reset();

	//Set the autopad
	void SetAutoPad(BOOL bAutoPAD);

	//Add list terminator
	virtual void AddOption_ENDLIST();

	//Get the length of the buffer
	int GetBufferLength();

	//Get the buffer itself
	const char* GetBuffer();
};

//Value not specified within winsock2
//Thanks on this one goes to Bjorn Stickler author of Natas
#ifndef SIO_RCVALL
#define SIO_RCVALL  0x98000001
#endif

class CSpoofSocket : public CSpoofBase
{
public:
	typedef enum _SocketShutdown
	{
		ssReceive,
		ssSend,
		ssBoth
	} SocketShutdown;
public:
	//Close one way of the socket (receive,send,both)
	BOOL Shutdown(SocketShutdown eHow);

	//ctor and dtor
	CSpoofSocket();
	virtual ~CSpoofSocket();

	//Get the address of the remote connected system
	long GetPeerAddress();

	//Turn to be a sniffer socket
	virtual BOOL Sniff(BOOL bSniff);

	//Resolve a DNS entry
	long ResolveDNS(LPCSTR lpAddress);
	
	//Check if an address is valid
	BOOL ValidAddress(LPCSTR lpAddress);
	
	//Recieve data from remote socket
	virtual int Receive(char* buf,int bufLen);
	
	//Get the IP options
	CIPOptions* GetOptions();

	//Do we allow options on this socket ?
	void SetOptions(BOOL bOptions);

	//Are we a raw socket ?
	void SetRaw(BOOL bRaw);

	//Set the packet Time to live
	void SetTTL(unsigned char ucTTL);

	//Calculate the checksum for TCP and UDP
	unsigned short CalculatePseudoChecksum(char *buf, int BufLength,LPCSTR lpDestinationAddress,int iPacketLength);

	//Set source address for spoofing
	void SetSourceAddress(LPCSTR lpSourceAddress);

	//Close the socket
	virtual BOOL Close();

	//Bind to a specific address
	virtual BOOL Bind(LPCSTR lpSourceAddress,int iPort=0);

	//Send data to a socket
	virtual BOOL Send(LPCSTR lpDestinationAddress,char* buf,int bufLength,unsigned short usDestinationPort=0);

	//Create a socket
	BOOL Create(int iProtocol);
protected:
	//Attach to a socket
	void AssignSocket(SOCKET sok);

	//Attach to a socket by constructor
	CSpoofSocket(SOCKET sok);

	//Indication if we are a raw socket
	BOOL isRaw();

	//Set the protocol we are working on
	void SetProtocol(int iProtocol);

	//Check this socket is valid
	BOOL CheckSocketValid();

	//Calculate the data checksum
	unsigned short CalculateChecksum(unsigned short* usBuf,int iSize);

	//Is our socket valid ?
	BOOL ValidSocket();

	//Get the socket handle
	SOCKET getHandle();

	//initialize all the private memebers
	virtual void InitializeIP();

	//Set the address in the IP header
	virtual void SetIPHeaderAddress(LPIpHeader lpHead,LPCSTR lpSourceAddress,LPCSTR lpDestinationAddress);

	//Create an IP header
	virtual LPIpHeader ConstructIPHeader (unsigned char  ucProtocol,
										  unsigned short usFragmentationFlags,
										  unsigned char  ucTTL,
										  unsigned short usIdentification,
										  unsigned char  ucHeaderLength);

	//Remote address we are conencted to
	sockaddr_in m_ConnectedTo;
private:
	//Reseolve DNS
	sockaddr_in pResolveDNS(LPCSTR lpAddress);
	
	//Our options
	CIPOptions* m_IPOptions;

	//Do we have options
	BOOL m_Options;

	//Are we raw ?
	BOOL m_Raw;

	//Time to live
	unsigned char m_TTL;

	//The protocol
	unsigned char m_Protocol;

	//Our source address
	LPCSTR m_SourceAddress;
	
	//The actual socket handle
	SOCKET m_SpoofSocket;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPOOFSOCKET_H__5BAEA068_961A_4652_8BBD_90B78F6FBB09__INCLUDED_)
