#pragma once
#include "manageConnect.h"
#include <vector>
using namespace std;

class CManageIOCPConnect : public CManageConnect
{
public:
	CManageIOCPConnect(void);
	virtual	~CManageIOCPConnect(void);

	//����һ������
	virtual int AddConnect(CSocket * pSocket);
	//ɾ��ָ��������
	//virtual int RemoveConnect(CSocket * pSocket);
	//�����������
	//virtual int ClearConnect();
	virtual int Initalize();

	//����ÿ������������ɶ˿ڵ��̸߳��������Ҫ���ã������� Initalize ǰ����
	int SetThreadNumber(int nNum = 1);
	int GetThreadNumber();

	BOOL * m_pExit;

private:
	static DWORD CompleteIOWorkThread(void * pPara);

	HANDLE m_hCompletion; //��ɶ˿ھ��
	vector < HANDLE > m_hThread;
	int m_nThread;

};
