#pragma once
#include "manage.h"
#include "Connect.h"
#include "Sock.h"
#include <vector>
using namespace std;

class CManageConnect : public CManage
{
public:
	CManageConnect(void);
	virtual ~CManageConnect(void);

	//����һ������
	virtual int AddConnect(CSocket * pSocket);
	//ɾ��ָ��������
	virtual int RemoveConnect(CSocket * pSocket);
	//�����������
	virtual int ClearConnect();

	virtual int Initalize();

	//�õ���ǰ������
	virtual LONG GetConnectNumber();
	//�õ��ܵ�������
	virtual LONG GetTotalConnectNumber();

protected:
	LONG m_ConnectNumber;       //��ǰ������
	LONG m_TotalConnectNumber;  //��������

	vector < CConnect * > m_Connect;
	CRITICAL_SECTION m_csConnect;

	int Lock();
	int UnLock();

	static DWORD WorkThread(void * pPara);
};
