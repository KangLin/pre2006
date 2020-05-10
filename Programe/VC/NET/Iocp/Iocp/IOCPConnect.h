#pragma once
#include "connect.h"
#include <queue>

using namespace std;

#define DATA_BUFFER_SIZE 4096

class CIOCPConnect : public CConnect
{
public:
	CIOCPConnect(CSocket * pSocket, HANDLE hCompletion);
	virtual ~CIOCPConnect(void);

#define IOCP_RECV  1
#define IOCP_WRITE 2
#define IOCP_CLOSE 3
	typedef struct
	{
		OVERLAPPED Overlapped;
		DWORD nLength;       //BUFFER长度
		DWORD nTransferred;  //传送的长度
		int nOption;
		WSABUF DataBuf;
		CHAR Buffer[DATA_BUFFER_SIZE];
	} PER_IO_OPERATION_DATA, * LPPER_IO_OPERATION_DATA;

	//处理接收到的完整数据包
	virtual int OnRecv(void * pBuf, int nLen);
	//发送数据包
	virtual int OnSend(void * pBuf, int nLen);

	virtual int OnHandleIOEvent(DWORD dwBytesTransferred, void * pPara = NULL);

private:
	queue<LPPER_IO_OPERATION_DATA> m_qIODataBuf;
	CRITICAL_SECTION m_csQueue;
	int Lock();
	int UnLock();

	//投递接收IO事件
	int PostIOCPRecvEvent();
	//投递发送事件
	int PostIOCPWriteEvent(LPPER_IO_OPERATION_DATA pData);
};
