#pragma once

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
  unsigned long			ICMP_Originate_Timestamp; // Ê±¼ä´Á Not standard field in header, but reserved nonetheless
  unsigned long			ICMP_Receive_Timestamp;
  unsigned long			ICMP_Transmit_Timestamp;
} ICMPHeader;

typedef ICMPHeader FAR * LPICMPHeader;

#define ICMPHeaderLength sizeof(ICMPHeader)

// ICMP Echo
#define ICMP_Echo 8
#define ICMP_Echo_Reply 0

class CICMP
{
public:
	CICMP(void);
	~CICMP(void);
	BOOL ConstructICMP(LPICMPHeader lpHead);
	BOOL ECHO(LPICMPHeader lpHead, unsigned short usIdentifier, unsigned short usSequence, unsigned long ulTimstamp, BOOL bReply = FALSE);

	unsigned short CalculateChecksum(unsigned short * usBuf, int iSize);
	DWORD ProccessICMP(char * buf, ICMPHeader * pICMPHead = NULL);
};
