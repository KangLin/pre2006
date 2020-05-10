#pragma once
#include "Sock.h"
#include "RecvData.h"
#include "SendData.h"
#include "Sock.h"

class CConnect
{
public:
	CConnect(CSocket * pSocket);
	virtual ~CConnect(void);

	//����IO�¼�
	virtual int OnHandleIOEvent(void * pPara = NULL);
	//��������¼�
	virtual int OnProcessRecvEvent();
	//�������¼�
	virtual int OnProcessWriteEvent();

	//������յ����������ݰ����û�Ҫ�̳в�ʵ���������
	virtual int OnRecv(void * pBuf, int nLen);
	//�������ݰ����û�Ҫ�̳в�ʵ���������
	virtual int OnSend(void * pBuf, int nLen);

	CSocket * m_pSocket;        //SOCKָ��

protected:
	CRecvData * m_pRecvData;    //���յ�����
	CSendData * m_pSendData;    //���͵�����
};
