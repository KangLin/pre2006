#include "stdafx.h"
#include "helper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CString IntToStr(int value)
{
	CString str;
	LPTSTR sz = str.GetBuffer(20);
#ifdef UNICODE
	_itow(value, sz, 10);
#else
	_itoa(value, sz, 10);
#endif
	str.ReleaseBuffer();
	return str;
}


CString UIntToStr(UINT value)
{
	CString str;
	LPTSTR sz = str.GetBuffer(20);
	wsprintf(sz, _T("%u"), value);
	str.ReleaseBuffer();
	return str;
}


CString BoolToStr(bool value)
{
	return (value) ? _T("True") : _T("False");
}

bool GetProperty(LPDISPATCH pDisp, LPCTSTR PropName, VARIANT * var)
{
	ASSERT(NULL != pDisp); 
	USES_CONVERSION;
	CComDispatchDriver dispdrv(pDisp);
	HRESULT hr = dispdrv.GetPropertyByName(T2CW(PropName), var); 
	if(SUCCEEDED(hr))
	{
		return TRUE; 
	} // ���� if(SUCCEEDED(hr))
    return FALSE;
}

int GetLongProperty(LPDISPATCH pDisp, LPCTSTR PropName)
{
	ASSERT(NULL != pDisp);
	USES_CONVERSION;
	int iRet;

	CComDispatchDriver dispdrv(pDisp);
	VARIANT var;
	VariantInit(&var);
	HRESULT hr = dispdrv.GetPropertyByName(T2CW(PropName), &var);
	if (SUCCEEDED(hr))
	{
		switch (var.vt)
		{
		case VT_I4:
			iRet = var.lVal;
			break;
		}
		VariantClear(&var);
	}
	return iRet;
}

/*******************************************************************************************************
��������GetStringProperty
��  �ܣ��õ��ӿڵ��ַ�������
��  ����
         LPDISPATCH pDisp���ӿ�
         LPCTSTR PropName��������
����ֵ������ֵ
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-7-7
ʱ  �䣺11:33:02
*******************************************************************************************************/
CString GetStringProperty(LPDISPATCH pDisp, LPCTSTR PropName)
{
	ASSERT(NULL != pDisp);
	USES_CONVERSION;
	CString str;

	CComDispatchDriver dispdrv(pDisp);
	VARIANT var;
	VariantInit(&var);
	HRESULT hr = dispdrv.GetPropertyByName(T2CW(PropName), &var);
	if (SUCCEEDED(hr))
	{
		switch (var.vt)
		{
		case VT_BSTR:
			str = var.bstrVal;
			break;
		case (VT_BSTR | VT_BYREF):
			str = *var.pbstrVal;
			break;
		}
		VariantClear(&var);
	}
	return str;
}


bool ExtensionIs(LPCTSTR FileName, LPCTSTR Ext)
{
	LPCTSTR szExt = _tcsrchr(FileName, _T('.'));
	if (!szExt) return false;
	if (lstrcmpi(szExt+1, Ext)==0)
		return true;
	else
		return false;
}


CString ChangeFileExt(LPCTSTR FileName, LPCTSTR Ext)
{
	CString str;
	LPTSTR lpsz = str.GetBuffer(_MAX_PATH);
	lstrcpy(lpsz, FileName);
	LPTSTR lpszExt = _tcsrchr(lpsz, _T('.'));
	if (lpszExt)
	{
		lstrcpy(lpszExt+1, Ext);
	}
	else
	{
		lstrcat(lpsz, _T("."));
		lstrcat(lpsz, Ext);
	}
	str.ReleaseBuffer();
	return str;
}


CString ComcatFileName(LPCTSTR Path, LPCTSTR FileName)
{
	CString str = Path;
	if (str.Right(1)!=_T("\\"))
		str += _T("\\");
	str += FileName;
	return str;
}

/*******************************************************************************************************
��������PutDispatchProperty
��  �ܣ����ýӿڵ�����ֵ
��  ����
         LPDISPATCH pDisp���ӿ�
         LPCTSTR PropName��������
         VARIANT var������ֵ
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-7-7
ʱ  �䣺11:34:21
*******************************************************************************************************/
HRESULT PutDispatchProperty(LPDISPATCH pDisp, LPCTSTR PropName, VARIANT var)
{
	USES_CONVERSION;
	CComDispatchDriver dispdrv(pDisp);
	HRESULT hr = dispdrv.PutPropertyByName(T2CW(PropName), &var);
    return hr;
}

/*******************************************************************************************************
��������PutDispatchProperty
��  �ܣ���������ֵΪ�ַ����Ľӿ� 
��  ����
         LPDISPATCH pDisp���ӿ� 
         LPCTSTR PropName��������
         LPCTSTR szVar���ַ���ֵ
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-7-7
ʱ  �䣺11:34:57
*******************************************************************************************************/
HRESULT PutDispatchProperty(LPDISPATCH pDisp, LPCTSTR PropName, LPCTSTR szVar)
{
	COleVariant var(szVar);	
	return PutDispatchProperty(pDisp, PropName, var);
}

/*******************************************************************************************************
��������InvokeMethod
��  �ܣ�����ָ���ӿڵķ���
��  ����
         LPDISPATCH pDisp���ӿ�
         LPCTSTR lpszMethodName��������
         VARIANT *var�����ú�ķ���ֵ
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-7-7
ʱ  �䣺11:58:56
*******************************************************************************************************/
bool InvokeMethod(LPDISPATCH pDisp, LPCTSTR lpszMethodName, VARIANT *var)
{
    USES_CONVERSION;
	CComDispatchDriver dispdrv(pDisp);
	dispdrv.Invoke0(T2CW(lpszMethodName), var);
	return TRUE;
}

bool InvokeMethod(LPDISPATCH pDisp, LPCTSTR lpszMethodName, LPCTSTR szVar)
{
	COleVariant var(szVar);
	return InvokeMethod(pDisp, lpszMethodName, var);
}

bool InvokeMethod1(LPDISPATCH pDisp, LPCTSTR lpszMethodName, VARIANT* pvarParam1, VARIANT* var)
{
	USES_CONVERSION;
	CComDispatchDriver dispdrv(pDisp);
	dispdrv.Invoke1(T2CW(lpszMethodName), pvarParam1, var);
	return TRUE;
}

bool InvokeMethod1(LPDISPATCH pDisp, LPCTSTR lpszMethodName, LPCTSTR szPara, VARIANT* var)
{
	COleVariant szVar(szPara);
	return InvokeMethod1(pDisp, lpszMethodName, szVar, var);
}

bool InvokeMethod2(LPDISPATCH pDisp, LPCTSTR lpszMethodName, VARIANT* pvarParam1, VARIANT* pvarParam2, VARIANT* var)
{
	USES_CONVERSION;
	CComDispatchDriver dispdrv(pDisp);
	dispdrv.Invoke2(T2CW(lpszMethodName), pvarParam1, pvarParam2, var);
	return TRUE;
}

bool InvokeMethod2(LPDISPATCH pDisp, LPCTSTR lpszMethodName, LPCTSTR szPara1, LPCTSTR szPara2, VARIANT* var)
{
	COleVariant szVar1(szPara1);
	COleVariant szVar2(szPara2);
	return InvokeMethod2(pDisp, lpszMethodName, szVar1, szVar2, var);
}

bool InvokeMethod3(LPDISPATCH pDisp, LPCTSTR lpszMethodName, LONG pvarParam1, LONG pvarParam2, VARIANT* pvar3, VARIANT* pvarRet)
{
	USES_CONVERSION;
	COleVariant vars[3];
	vars[0] = pvarParam1;
	vars[1] = pvarParam2;
	vars[2] = pvar3;
	CComDispatchDriver dispdrv(pDisp);
	dispdrv.InvokeN(T2CW(lpszMethodName), vars, 3, pvarRet);
	return TRUE;
}
