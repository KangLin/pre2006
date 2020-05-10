/*******************************************************************************************************
版权所有 (C) 2007 康林工作室；保留所有权利。
文件名：Events.h
描  述：键盘输入事件的处理
版  本：1.0.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2007年5月5日
时  间：14:25:53
编译器：Microsoft Visual Studio 8.0 —— C/C++ 8.0
*******************************************************************************************************/
#ifndef __ADDINSINPUT_EVENTS_H__
#define __ADDINSINPUT_EVENTS_H__

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif // 结束 #ifdef __cplusplus

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
