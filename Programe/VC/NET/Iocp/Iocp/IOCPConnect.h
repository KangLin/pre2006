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
		DWORD nLength;       //BUFFER����
		DWORD nTransferred;  //���͵ĳ���
		int nOption;
		WSABUF DataBuf;
		CHAR Buffer[DATA_BUFFER_SIZE];
	} PER_IO_OPERATION_DATA, * LPPER_IO_OPERATION_DATA;

	//������յ����������ݰ�
	virtual int OnRecv(void * pBuf, int nLen);
	//�������ݰ�
	virtual int OnSend(void * pBuf, int nLen);

	virtual int OnHandleIOEvent(DWORD dwBytesTransferred, void * pPara = NULL);

private:
	queue<LPPER_IO_OPERATION_DATA> m_qIODataBuf;
	CRITICAL_SECTION m_csQueue;
	int Lock();
	int UnLock();

	//Ͷ�ݽ���IO�¼�
	int PostIOCPRecvEvent();
	//Ͷ�ݷ����¼�
	int PostIOCPWriteEvent(LPPER_IO_OPERATION_DATA pData);
};
