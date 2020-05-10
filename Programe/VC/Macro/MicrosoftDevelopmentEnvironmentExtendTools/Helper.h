#ifndef __HELPER_H__
#define __HELPER_H__

#include "stdafx.h"
#pragma once


CString    IntToStr(int value);
CString    UIntToStr(UINT value);
CString    BoolToStr(bool value);
CString    GetStringProperty(LPDISPATCH pDisp, LPCTSTR PropName);
int        GetLongProperty(LPDISPATCH pDisp, LPCTSTR PropName); 
bool       GetProperty(LPDISPATCH pDisp, LPCTSTR PropName, VARIANT* var);
bool       ExtensionIs(LPCTSTR FileName, LPCTSTR Ext);
CString    ChangeFileExt(LPCTSTR FileName, LPCTSTR Ext);
CString    ComcatFileName(LPCTSTR Path, LPCTSTR FileName);
bool       InvokeMethod(LPDISPATCH pDisp, LPCTSTR lpszMethodName, VARIANT* var  = NULL);
bool       InvokeMethod(LPDISPATCH pDisp, LPCTSTR lpszMethodName, LPCTSTR szVar);
bool       InvokeMethod1(LPDISPATCH pDisp, LPCTSTR lpszMethodName, VARIANT* pvarParam1, VARIANT* var  = NULL);
bool       InvokeMethod1(LPDISPATCH pDisp, LPCTSTR lpszMethodName, LPCTSTR szPara, VARIANT* var  = NULL);
bool       InvokeMethod2(LPDISPATCH pDisp, LPCTSTR lpszMethodName, VARIANT* pvarParam1, VARIANT* pvarParam2, VARIANT* var  = NULL);
bool       InvokeMethod2(LPDISPATCH pDisp, LPCTSTR lpszMethodName, LPCTSTR szPara1, LPCTSTR szPara2, VARIANT* var  = NULL);
bool       InvokeMethod3(LPDISPATCH pDisp, LPCTSTR lpszMethodName, LONG pvarParam1, LONG pvarParam2,  VARIANT* pvar3, VARIANT* pvarRet = NULL);

HRESULT PutDispatchProperty(LPDISPATCH pDisp, LPCTSTR PropName, LPCTSTR szVar);
HRESULT PutDispatchProperty(LPDISPATCH pDisp, LPCTSTR PropName, VARIANT var);

/*******************************************************************************************************
函数名：GetDispatchProperty
功  能：得到接口的指针
参  数：
         LPDISPATCH pDisp：接口
         LPCTSTR PropName：属性名
         REFIID riid：属性的ID
返回值：指定的接口
作  者：康  林
版  本：1.0.0.1
日  期：2005-7-7
时  间：11:44:32
*******************************************************************************************************/
template<class T>
T GetDispatchProperty(LPDISPATCH pDisp, LPCTSTR PropName, REFIID riid)
{
	USES_CONVERSION;
	CComDispatchDriver dispdrv(pDisp);
	VARIANT var;
	VariantInit(&var);

	HRESULT hr = dispdrv.GetPropertyByName(T2CW(PropName), &var);
	if (FAILED(hr)) return NULL;
	switch (var.vt)
	{
	case VT_DISPATCH:
		{
			if (var.pdispVal == NULL)
			{
				VariantClear(&var);
				return NULL;
			}
			T ret = NULL;
			hr = var.pdispVal->QueryInterface(riid, (LPVOID*)&ret);
			VariantClear(&var);
			return (SUCCEEDED(hr)) ? ret : NULL;
		}
		break;
	case (VT_DISPATCH | VT_BYREF):
		{
			if ((*var.ppdispVal) == NULL)
			{
				VariantClear(&var);
				return NULL;
			}
			T ret = NULL;
			hr = (*var.ppdispVal)->QueryInterface(riid, (LPVOID*)&ret);
			VariantClear(&var);
			return (SUCCEEDED(hr)) ? ret : NULL;
		}
		break;
	default:
		VariantClear(&var);
		return NULL;
		break;
	}
}

/*******************************************************************************************************
函数名：InterfaceIs
功  能：得到指定的ID的接口
参  数：
         IDispatch* pDisp：接口
         REFIID riid：要得到的接口
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2005-7-7
时  间：11:48:01
*******************************************************************************************************/
template<class T>
bool InterfaceIs(IDispatch* pDisp, REFIID riid)
{
	T* t = NULL;
	HRESULT hr = pDisp->QueryInterface(riid, (LPVOID*)&t);
	if (SUCCEEDED(hr) && t!=NULL)
	{
		t->Release();
		return true;
	}
	else
	{
		return false;
	}
}


/*******************************************************************************************************
函数名：InterfaceAs
功  能：得到指定IID的接口
参  数：
         IDispatch* pDisp：接口
         REFIID riid：要得到接口的IID
返回值：成功返回 接口指针,否则返回 NULL
作  者：康  林
版  本：1.0.0.1
日  期：2005-7-7
时  间：11:49:13
*******************************************************************************************************/
template<class T>
T* InterfaceAs(IDispatch* pDisp, REFIID riid)
{
	T* t = NULL;
	HRESULT hr = pDisp->QueryInterface(riid, (LPVOID*)&t);
	if (SUCCEEDED(hr) && t!=NULL)
	{
		return t;
	}
	else
	{
		return NULL;
	}
}


template<class T>
long GetEnumCount(T* t)
{
	long lCount = 0;
	HRESULT hr = t->get_Count(&lCount);
	if (SUCCEEDED(hr))
		return lCount;
	else
		return 0;
}


template<class TEnum, class TItem>
TItem* GetEnumItem(TEnum* t, long index, REFIID riid)
{
	_variant_t varIndex(index);
	IDispatch* pDisp = NULL;
	HRESULT hr = t->Item(varIndex, &pDisp);
	if (FAILED(hr) || pDisp==NULL)
		return NULL;
	TItem* pItem = NULL;
	hr = pDisp->QueryInterface(riid, (LPVOID*)&pItem);
	pDisp->Release();
	if (SUCCEEDED(hr) && pItem!=NULL)
		return pItem;
	else
		return NULL;
}


template<class TEnum, class TItem>
TItem* GetEnumItem2(TEnum* t, long index, REFIID riid)
{
	_variant_t varIndex(index);
	TItem* pItem = NULL;
	HRESULT hr = t->Item(varIndex, &pItem);
	if (FAILED(hr) || pItem==NULL)
		return NULL;
	else
		return pItem;
}


#endif
