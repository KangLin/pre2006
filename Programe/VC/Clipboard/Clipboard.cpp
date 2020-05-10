#include "StdAfx.h"
#include "clipboard.h"

CClipboard::CClipboard(void)
{
}

CClipboard::~CClipboard(void)
{
}

// 清空当前剪切板
BOOL CClipboard::Empty(void)
{
    return EmptyClipboard();
}

BOOL CClipboard::Open()
{
    return ::OpenClipboard(NULL);
}

BOOL CClipboard::Close()
{
    return CloseClipboard();
}

BOOL CClipboard::SetData(LPVOID lpData, int iLen, UINT uFormat)
{
    if(!OpenClipboard(NULL))
    {
        TRACE(_T("%s(%d) : 不能打开剪切板\n"), __FILE__, __LINE__);
        return FALSE;
    }
    // 清空当前剪切板
    if( !EmptyClipboard() )
    {
        TRACE(_T("%s(%d) : 剪切板清空失败。\n"), __FILE__, __LINE__);
        return FALSE;
    }
    LPVOID lp;
    HGLOBAL hglbCopy;
    hglbCopy = ::GlobalAlloc(GMEM_MOVEABLE, iLen);
    if(hglbCopy == NULL)
    {
        ::CloseClipboard();
        TRACE(_T("%s(%d) : 全局堆分配失败。\n"), __FILE__, __LINE__);
        return FALSE;
    }
    lp = (LPVOID)::GlobalLock(hglbCopy);
    memcpy(lp, lpData, iLen);
    

    if(::SetClipboardData(uFormat, lp))
    {
        ::GlobalUnlock(hglbCopy);
        GlobalFree(hglbCopy);
        CloseClipboard();
        return TRUE;
    } //结束 if(SetClipboardData(uFormat, lp))
    
    ::GlobalUnlock(hglbCopy);
    GlobalFree(hglbCopy);        
    CloseClipboard();

    return FALSE;
}

BOOL CClipboard::SetData(LPCTSTR lpszData)
{
    if(SetData((LPVOID)lpszData, _tcslen(lpszData) + sizeof(TCHAR), CF_TEXT))
    {
        return TRUE;
    } //结束 if(SetData((LPVOID)lpszData, _tcslen(lpszData) + sizeof(TCHAR), CF_TEXT))
    return FALSE;
}