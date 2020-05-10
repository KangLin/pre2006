#pragma once

#include "..\..\TestItem.h"
#include "..\SetTestSock.h"

#define TFTP_RRQ        01  /* read request */
#define TFTP_WRQ        02  /* write request */
#define TFTP_DATA       03  /* data packet */
#define TFTP_ACK        04  /* acknowledgement */
#define TFTP_ERROR      05  /* error code */
#define TFTP_OACK       06  /* option acknowledgement */

#define TFTP_NETASCII   "netascii"
#define TFTP_OCTET      "octet"

#define TFTP_PORT       69

#define BLK_SIZE        512
#define DATA_BUFFER     BLK_SIZE + 4

class CTFTP : public CTestItem
{
public:
	CTFTP(void);
	~CTFTP(void);
	int SetFileName(LPCTSTR lpszFileName);
	int SetFileMode(LPCTSTR lpszFileMode = TFTP_NETASCII);

	struct TFTP_HEAD
	{
		unsigned short OperateCode;
		union
		{
			unsigned short BlockNo;
			char Stuff[2];
		}th_u;
		char data[1];
	};

	struct TFTP_HEAD *m_Send, *m_Recv;

protected:
	CString m_szFileName;
	CString m_szFileMode;
	char m_SendBuf[DATA_BUFFER];
	char m_RecvBuf[DATA_BUFFER];
	CString m_szIP;
	UINT m_nPort;
	int m_nTimeOut;
	CTestSocket m_Sock;
	int m_nMaxRepeat;

};
