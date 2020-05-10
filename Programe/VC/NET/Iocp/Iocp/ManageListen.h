#pragma once
#include "manage.h"
#include "ListenSock.h"
#include "ManageNet.h"
#include <vector>
using namespace std;

#define MAX_Listen_NUMBER 64      //����SOCKET�����

class CManageNet;
class CManageListen : public CManage
{
public:
	CManageListen(CManageNet * pMngNet);
	virtual ~CManageListen(void);

	virtual int Initalize();

	//���Ӽ���
	virtual int AddListen(int nPort);
	//ɾ������
	virtual int RemoveListen(int nFD);
	//������м���
	virtual int ClearListen();

	//�õ���ǰ������
	virtual LONG GetListenNumber();
	//�õ��ܵļ�����
	virtual LONG GetTotalListenNumber();

	//����IO
	virtual int HandleIO(int nPos);

	//�¼�����
	HANDLE m_hEvent[MAX_Listen_NUMBER];
	//�����¼�����
	int RebuildArray();

protected:
	vector<CListenSocket *> m_Listen;

	CManageNet * m_ManageNet;
	HANDLE m_hThreadListen;       //�����߳̾��
	LONG m_nLiseterNumber;        //������
	LONG m_nTotalNumber;          //��������

	CRITICAL_SECTION m_csListen;  //����m_Listen�����
	int Lock();
	int UnLock();

	static DWORD ListenWorkThread(void * pPara);
};
