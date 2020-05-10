/*******************************************************************************************************
��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
�ļ�����Events.h
��  �������������¼��Ĵ���
��  ����1.0.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2007��5��5��
ʱ  �䣺14:25:53
��������Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*******************************************************************************************************/
#ifndef __ADDINSINPUT_EVENTS_H__
#define __ADDINSINPUT_EVENTS_H__

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif // ���� #ifdef __cplusplus

BOOL __stdcall BeforeKeyPress(BSTR bstrKey);
LONG __stdcall AfterKeyPress(BSTR bstrKey);

LONG __stdcall Sol_Open();
LONG __stdcall Sol_AfterClosing();
LONG __stdcall Sol_BeforeClosing();
LONG __stdcall Sol_Renamed(BSTR oldName);
LONG __stdcall Sol_ProjectAdded(EnvDTE::Project * pProject);
LONG __stdcall Sol_ProjectRemoved(EnvDTE::Project * pProject);
LONG __stdcall Sol_ProjectRenamed(EnvDTE::Project * pProject);
LONG __stdcall Pro_ItemAdded(EnvDTE::ProjectItem * pItem);
LONG __stdcall Pro_ItemRemoved(EnvDTE::ProjectItem * pItem);
LONG __stdcall Pro_ItemRenamed(EnvDTE::ProjectItem * pItem);

#ifdef __cplusplus
}
#endif

#endif //__ADDINSINPUT_EVENTS_H__
