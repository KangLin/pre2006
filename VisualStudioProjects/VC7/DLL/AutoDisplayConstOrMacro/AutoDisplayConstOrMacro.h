/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����AutoDisplayConstOrMacro.h
��  �������������Զ���ʾ��ͷ�ļ�
��  ����1.0.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005-6-14
ʱ  �䣺14:43:10
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
*******************************************************************************************************/
// AutoDisplayConstOrMacro.h : AutoDisplayConstOrMacro DLL ����ͷ�ļ�
//
#if !defined(__KL_AUTODISPLAYMACROORCONST_H__521BE306_5FBC_4693_B266_92166DA83CD1__INCLUDED__1976121__)
#define __KL_AUTODISPLAYMACROORCONST_H__521BE306_5FBC_4693_B266_92166DA83CD1__INCLUDED__1976121__

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������
#include "Export.h"

// CAutoDisplayConstOrMacroApp
// �йش���ʵ�ֵ���Ϣ������� AutoDisplayConstOrMacro.cpp
//

class CAutoDisplayConstOrMacroApp : public CWinApp
{
public:
	CAutoDisplayConstOrMacroApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
    virtual int ExitInstance();
};

//������ʾ��ľ��
BOOL SetListHand();
//��ʾ\���ش���
void ShowTiShi(BOOL bShow = TRUE, BOOL bClear = TRUE);
//�ƶ���ʾ����
void MoveTiShi();
//���ǰ�������
void ClearInput(int iCount = 0);
//��������в���ָ�����ַ���
void FindString();
//��ʾTip
void ShowTip();
//��������е��ַ������Ƶ�IDE��
BOOL CopyString(TCHAR ch = NULL);
//���̿��Ƴ���
enum POSTION_ENUM
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    PAGEUP,
    PAGEDOWN,
    HOME,
    END
};
//�ƶ�������е�ѡ����
BOOL SetListPos(POSTION_ENUM pos);

//���̹��Ӵ�����
LRESULT CALLBACK KeyboardProc(int nCode, /*ָ���Ƿ���Ҫ�������Ϣ*/
    WPARAM wParam,
    LPARAM lParam
    );
//��Ϣ���Ӵ�����
LRESULT CALLBACK GetMsgProc(
  int nCode,      // hook code
  WPARAM wParam,  // removal flag
  LPARAM lParam   // address of structure with message
);

//�������Ϣ������
LRESULT CALLBACK WindowProc(HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
    );
//�û������������Ϣ������
LRESULT CALLBACK UserWindowProc(HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
);
//��ȨEdit��Ϣ������
LRESULT CALLBACK EditWndProc(HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
    );

#endif // ���� #if !defined(__KL_AUTODISPLAYMACROORCONST_H__521BE306_5FBC_4693_B266_92166DA83CD1__INCLUDED__1976121__)