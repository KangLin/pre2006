/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    ProcessInfoView.h
\brief   ���н�����Ϣ�Ĵ��ڣ���������������������н�����Ϣ��
\version 1.0.0.1
\author  ��  �� (kl222@126.com)
\date    2007��8��21��  9:03:32
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/

#ifndef __PROCESSINFOVIEW_H_KL_2007_08_24__
#define __PROCESSINFOVIEW_H_KL_2007_08_24__

#pragma once


// CProcessInfoView

class CProcessInfoView : public CWnd
{
	DECLARE_DYNAMIC(CProcessInfoView)

public:
	CProcessInfoView();
	virtual ~CProcessInfoView();

protected:
	DECLARE_MESSAGE_MAP()

public:
	CBCGPListCtrl m_lstProcess;

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	int OnInitialUpdate(CNetManageViewDoc * pDocument);

	virtual int ProcessCommand(CCommand & cmd);

private:
	CNetManageViewDoc * m_pDocument; //��ǰ�ĵ�
};

#endif //__PROCESSINFOVIEW_H_KL_2007_08_24__
