/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����Export.h
��  ������������ͷ�ļ�
��  ����2005.6.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��7��28��
ʱ  �䣺7:54:59
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
*******************************************************************************************************/
#pragma once

//���Ӽ���ʱ������
extern "C" BOOL WINAPI AddTempList(LPCTSTR lpszItem);
//ɾ����ʱ������
extern "C" BOOL WINAPI DeleteTempList();
//�������������һ��
extern "C" BOOL WINAPI AddListItem(LPCTSTR lpszItem);
//���������ɾ��ָ�����ַ���
extern "C" BOOL WINAPI DeleteListItem(LPCTSTR lpszItem);

//���ù���
extern "C" BOOL WINAPI SetHook();
extern "C" BOOL WINAPI SetVCHook();
//ж�ع���
extern "C" BOOL WINAPI UnHook();