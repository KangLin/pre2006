#include "StdAfx.h"
#include ".\icmp.h"

CICMP::CICMP(void)
{
}

CICMP::~CICMP(void)
{
}

BOOL CICMP::ConstructICMP(LPICMPHeader lpHead)
{
	try
	{				
		//Set all as zeros
		memset(lpHead, 0, ICMPHeaderLength);

		//Set the timestamp
		lpHead->ICMP_Originate_Timestamp = GetTickCount();

		//Return it
		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}
}

/*******************************************************************************************************
函数名：ECHO
描  述：显示包或回显包
参  数：
        LPICMPHeader lpHead        ：ICMP头
		unsigned short usIdentifier：标志
		unsigned short usSequence  ：序号
		unsigned long ulTimstamp   ：时间戳
		BOOL bReply                ：显示或回显。TRUE：显示；FALSE：回显。
返回值：类型为 BOOL 。
版  本：1.0
作  者：康  林
时  间：2005年11月11日 12:00:19
*******************************************************************************************************/
BOOL CICMP::ECHO(LPICMPHeader lpHead, unsigned short usIdentifier, unsigned short usSequence, unsigned long ulTimstamp, BOOL bReply)
{
	try
	{
		if(!ConstructICMP(lpHead))
		{
			return FALSE;
		}

		//Check if echo or reply
		if (bReply)
			lpHead->ICMPType=ICMP_Echo_Reply;
		else
			lpHead->ICMPType=ICMP_Echo;

		lpHead->ICMPCode=0;
		lpHead->sICMP.sUS.us1=htons(usIdentifier);
		lpHead->sICMP.sUS.us2=htons(usSequence);
		lpHead->ICMP_Originate_Timestamp = htonl(ulTimstamp);

		//And the checksum
		lpHead->ICMPChecksum=CalculateChecksum((unsigned short*)lpHead,ICMPHeaderLength);

		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}

}

unsigned short CICMP::CalculateChecksum(unsigned short *usBuf, int iSize)
{
	try
	{
		unsigned long usChksum=0;

		//Calculate the checksum
		while (iSize>1)
		{
			usChksum+=*usBuf++;
			iSize-=sizeof(unsigned short);
		}

		//If we have one char left
		if (iSize)
			usChksum+=*(unsigned char*)usBuf;

		//Complete the calculations
		usChksum=(usChksum >> 16) + (usChksum & 0xffff);
		usChksum+=(usChksum >> 16);

		//Return the value (inversed)
		return (unsigned short)(~usChksum);
	}
	catch(...)
	{
		return FALSE;
	}

}

DWORD CICMP::ProccessICMP(char * buf, ICMPHeader * pICMPHead)
{
	IpHeader ipHead;
	ICMPHeader icmpHead;

	//Copy to buffer
	memcpy(&ipHead, buf, IpHeaderLength);

	//Let's check for options
	unsigned char ucHeaderSize; //IP的头长度
	ucHeaderSize = ipHead.HeaderLength_Version & 15;
	ucHeaderSize *= 4;

	//Now check for total packet size
	unsigned short ucPacketSize;
	ucPacketSize = htons(ipHead.TotalLength);

	//Copy data to icmp
	memset(&icmpHead, 0, ICMPHeaderLength);

	//ICMP数据包的大小
	unsigned short ucCopy;
	ucCopy = ucPacketSize - ucHeaderSize;

	if(ucCopy > ICMPHeaderLength)
		ucCopy = ICMPHeaderLength;

	memcpy(&icmpHead, buf + ucHeaderSize, ucCopy);
	memcpy(pICMPHead, buf + ucHeaderSize, ucCopy);

	return icmpHead.ICMPType;

}
