/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：Export.h
描  述：导出函数头文件
版  本：2005.6.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年7月28日
时  间：7:54:59
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/
#pragma once

//增加加临时例表项
extern "C" BOOL WINAPI AddTempList(LPCTSTR lpszItem);
//删除临时例表项
extern "C" BOOL WINAPI DeleteTempList();
//在例表框中增加一项
extern "C" BOOL WINAPI AddListItem(LPCTSTR lpszItem);
//在例表框中删除指定的字符串
extern "C" BOOL WINAPI DeleteListItem(LPCTSTR lpszItem);

//设置钩子
extern "C" BOOL WINAPI SetHook();
extern "C" BOOL WINAPI SetVCHook();
//卸载钩子
extern "C" BOOL WINAPI UnHook();