#pragma once
#include "manage.h"
#include "ListenSock.h"
#include "ManageListen.h"
#include "ManageConnect.h"

//typedef struct _SOCKINFO
//{
//	CSocket * pSock;
//	CListenSocket * pListen;
//	CConnect * pConnect;
//	bool bIsListen;
//}SOCKINFO, *PSOCKINFO;

class CManageListen;

/*!
\class   CManageNet
\brief   ����������
\version 1.0
\author  ��  ��
\date    2007-9-24 11:43:08
*/
class CManageNet : public CManage
{
public:
	CManageNet(void);
	virtual ~CManageNet(void);

	//����һ���¼���
	virtual int AddListen(int nPort);
	//ɾ������
	virtual int RemoveListen(int nFd);
	//��������
	virtual int AddConncet(CSocket * pSocket);
	//ɾ������
	virtual int RemoveConnect(CSocket * pSock);

	virtual int Initalize(CManageConnect * pMngConnect = NULL, CManageListen * pMngListen = NULL);

private:
	CManageConnect * m_pConnect;
	CManageListen * m_pListen;
};
