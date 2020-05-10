#include "StdAfx.h"
#include "clipboard.h"

CClipboard::CClipboard(void)
{
}

CClipboard::~CClipboard(void)
{
}

// ��յ�ǰ���а�
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
        TRACE(_T("%s(%d) : ���ܴ򿪼��а�\n"), __FILE__, __LINE__);
        return FALSE;
    }
    // ��յ�ǰ���а�
    if( !EmptyClipboard() )
    {
        TRACE(_T("%s(%d) : ���а����ʧ�ܡ�\n"), __FILE__, __LINE__);
        return FALSE;
    }
    LPVOID lp;
    HGLOBAL hglbCopy;
    hglbCopy = ::GlobalAlloc(GMEM_MOVEABLE, iLen);
    if(hglbCopy == NULL)
    {
        ::CloseClipboard();
        TRACE(_T("%s(%d) : ȫ�ֶѷ���ʧ�ܡ�\n"), __FILE__, __LINE__);
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
    } //���� if(SetClipboardData(uFormat, lp))
    
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
    } //���� if(SetData((LPVOID)lpszData, _tcslen(lpszData) + sizeof(TCHAR), CF_TEXT))
    return FALSE;
}