/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    Thread.h
\brief   �̵߳ķ�װ��
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��9��4��  15:46:37
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/

#ifndef __THREAD_H_KL_2008_09_04__
#define __THREAD_H_KL_2008_09_04__

#pragma once

class CThread
{
public:
	CThread(void * pPara = NULL);
	virtual ~CThread(void);

	//�õ��̵߳�ID
	DWORD GetID();
	//�����߳�
	virtual int Start();
	//�ر��߳�
	virtual int Stop();

	//���º��������̺߳���workʹ��,�û����ܵ��ô˹��к���
	void * GetPara();

	//�̵߳Ĺ�������������������ʵ�֡�
	virtual int Run(void * pPara) = 0;

private:
	void * m_pPara;    //���ݸ��̵߳Ĳ���
	HANDLE m_hThread;  //�߳̾��
	DWORD m_dwID;      //�߳�ID

	//�̺߳���
	static int Work(void * pThis);
};

#endif //__THREAD_H_KL_2008_09_04__
