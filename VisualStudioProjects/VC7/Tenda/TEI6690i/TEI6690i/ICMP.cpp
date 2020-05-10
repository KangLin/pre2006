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
��������ECHO
��  ������ʾ������԰�
��  ����
        LPICMPHeader lpHead        ��ICMPͷ
		unsigned short usIdentifier����־
		unsigned short usSequence  �����
		unsigned long ulTimstamp   ��ʱ���
		BOOL bReply                ����ʾ����ԡ�TRUE����ʾ��FALSE�����ԡ�
����ֵ������Ϊ BOOL ��
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��11��11�� 12:00:19
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
	unsigned char ucHeaderSize; //IP��ͷ����
	ucHeaderSize = ipHead.HeaderLength_Version & 15;
	ucHeaderSize *= 4;

	//Now check for total packet size
	unsigned short ucPacketSize;
	ucPacketSize = htons(ipHead.TotalLength);

	//Copy data to icmp
	memset(&icmpHead, 0, ICMPHeaderLength);

	//ICMP���ݰ��Ĵ�С
	unsigned short ucCopy;
	ucCopy = ucPacketSize - ucHeaderSize;

	if(ucCopy > ICMPHeaderLength)
		ucCopy = ICMPHeaderLength;

	memcpy(&icmpHead, buf + ucHeaderSize, ucCopy);
	memcpy(pICMPHead, buf + ucHeaderSize, ucCopy);

	return icmpHead.ICMPType;

}
