/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����AutoDisplayConstOrMacro.cpp
��  �������������Զ���ʾ��ʵ���ļ�
��  ����2005.6.0.0
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005-6-14
ʱ  �䣺20:58:47
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
*******************************************************************************************************/
// AutoDisplayConstOrMacro.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "AutoDisplayConstOrMacro.h"
#include "..\..\..\..\Programe\VC\File\FileEx.h"
#include "..\..\..\..\Programe\VC\Clipboard\Clipboard.h"
#include "..\..\..\..\Programe\VC\Limit\Limit.h"
#include "TiShi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_BUFFER 1024

HINSTANCE g_hInstance;   //DLLʵ���ľ��
HHOOK g_hKeyHook;        //���̹��Ӿ��
HHOOK g_hMsgHook;        //��Ϣ����
HWND g_hWnd;             //�����д��ڵľ��(�ĵ� TextSelect)
HWND g_hList;            //��ʾ��ľ��
HWND g_hSysList;         //ϵͳ��ʾ��ľ��
HWND g_hUserList;        //�û�������ʾ��ľ��
HWND g_hEditTip;         //Tip Edit �ľ��
HWND g_hEdit;            //��Ȩ��Ϣ��ľ��
HFONT g_hFont;           //������
WNDPROC lpWndProc;       //���ڴ�����
WNDPROC lpUserWndProc;
WNDPROC lpEditWndProc;   //�༭���ڴ�����
BOOL g_bShowTiShi;       //��ʾ��ʾ��

INT g_iScreenWidth;      //��Ļ���
INT g_iScreenHeight;     //��Ļ�߶�
INT g_iListTop;          //�����Ķ���
INT g_iListLeft;         //���������
INT g_iListWidth;        //�����Ŀ��
INT g_iListHeight;       //�����ĸ߶�
INT g_iEditWidth;        //��Ȩ��Ŀ��
INT g_iEditHeight;       //��Ȩ��ĸ߶�

BOOL g_bESCFunction;     //ESCֵ�����á�TRUE�����ǰ������룻FALSE�������ǰ�������
CString g_szInput;       //�����ַ���
CString g_szPrompt;      //Ҫ��ʾ��ʾ����ַ���
CString g_szUserPrompt;  //Ҫ��ʾ�û�������ʾ����ַ���
CString g_szINIFile;     //�����ļ�
CString g_szListFile;    //�����ļ�
CString g_szTempFile;    //��ʱ�ļ�
CString g_szPath;        //��ǰDLL��·��
CString g_szCopyRight;   //��Ȩ

//
//	ע�⣡
//
//		����� DLL ��̬���ӵ� MFC
//		DLL���Ӵ� DLL ������
//		���� MFC ���κκ����ں�������ǰ��
//		��������� AFX_MANAGE_STATE �ꡣ
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CAutoDisplayConstOrMacroApp

BEGIN_MESSAGE_MAP(CAutoDisplayConstOrMacroApp, CWinApp)
END_MESSAGE_MAP()


// CAutoDisplayConstOrMacroApp ����

CAutoDisplayConstOrMacroApp::CAutoDisplayConstOrMacroApp()
{
	// TODO: �ڴ˴���ӹ�����룬
    // ��������Ҫ�ĳ�ʼ�������� InitInstance ��
    g_hList = NULL;
    g_hEdit = NULL;
    g_hKeyHook = NULL;
    g_hMsgHook = NULL;
}


// Ψһ��һ�� CAutoDisplayConstOrMacroApp ����

CAutoDisplayConstOrMacroApp theApp;


// CAutoDisplayConstOrMacroApp ��ʼ��

BOOL CAutoDisplayConstOrMacroApp::InitInstance()
{
	TRACE(_T("%s(%d) : CAutoDisplayConstOrMarcoApp::InitInstance()\n"), __FILE__, __LINE__); 
	CWinApp::InitInstance();

    g_hInstance = ::AfxGetInstanceHandle();
    g_szInput = _T("");
    g_bShowTiShi = FALSE;

    TCHAR szFile [MAX_PATH];
    ::GetModuleFileName(g_hInstance, szFile, MAX_PATH);

    CFileEx fe;
    CString szTemp;
    fe.GetFilePath(szTemp);
    g_szPath = szTemp;
    g_szINIFile = szTemp + _T("\\");
    fe.GetFileTitle(szTemp);
    g_szINIFile += szTemp + _T(".INI");

    TCHAR szPrompt[MAX_BUFFER];
    GetPrivateProfileString(_T("Settings"), _T("PromptString"), _T(".."), szPrompt, MAX_BUFFER, g_szINIFile);
    g_szPrompt = szPrompt;
    GetPrivateProfileString(_T("Settings"), _T("UserPromptString"), _T(".>"), szPrompt, MAX_BUFFER, g_szINIFile);
    g_szUserPrompt = szPrompt;
    GetPrivateProfileString(_T("Settings"), _T("ListFile"), _T("List.txt"), szPrompt, MAX_BUFFER, g_szINIFile);
    g_szListFile = szPrompt;
    GetPrivateProfileString(_T("Settings"), _T("TempFile"), _T("TempList.txt"), szPrompt, MAX_BUFFER, g_szINIFile);
    g_szTempFile = szPrompt;
    GetPrivateProfileString(_T("Settings"), _T("ESCFunction"), _T("TRUE"), szPrompt, MAX_BUFFER, g_szINIFile);
    if(!_tcsicmp(szPrompt, _T("true")))
    {
        g_bESCFunction = TRUE;
    }
    else
    {
        g_bESCFunction = FALSE;
    } //���� if(_tcscmp(szPrompt, _T("TRUE")))

    g_iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
    g_iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

    g_iListWidth = 200;
    g_iListHeight = 200;
    g_iEditWidth = g_iListWidth;
    g_iEditHeight = 55;

    g_hFont = CreateFont(12, 0, 0, 0, 0,
                         FALSE, FALSE, FALSE,
                         DEFAULT_CHARSET, DEFAULT_QUALITY,
                         DEFAULT_QUALITY, DEFAULT_QUALITY,
                         FIXED_PITCH + FF_SWISS, _T("����"));
    g_hSysList = CreateWindowEx(WS_EX_TOPMOST, _T("ListBox"),
                             _T("���������Զ���ʾ��"),
                             WS_POPUP | WS_BORDER | WS_VSCROLL | LBS_SORT,
                             0, 0, g_iListWidth, g_iListHeight,
                             NULL, NULL,
                             g_hInstance, NULL);
    SendMessage(g_hSysList, WM_SETFONT, (WPARAM)g_hFont, 0);
    lpWndProc = (WNDPROC)SetWindowLong(g_hSysList, GWL_WNDPROC, (LONG)WindowProc);

    if(g_szUserPrompt != g_szPrompt)
    {
        g_hUserList = CreateWindowEx(WS_EX_TOPMOST, _T("ListBox"),
                                         _T("���������Զ���ʾ�� - �û�����"),
                     WS_POPUP | WS_BORDER | WS_VSCROLL | LBS_SORT,
                     0, 0, g_iListWidth, g_iListHeight,
                     NULL, NULL,
                     g_hInstance, NULL);
        SendMessage(g_hUserList, WM_SETFONT, (WPARAM)g_hFont, 0);
        //lpUserWndProc = (WNDPROC)SetWindowLong(g_hUserList, GWL_WNDPROC, (LONG)UserWindowProc);
        lpWndProc = (WNDPROC)SetWindowLong(g_hUserList, GWL_WNDPROC, (LONG)WindowProc);
    }
    else
    {
        g_hUserList = NULL;
    }//���� if(m_szUserPrompt != m_szPrompt)

    g_hEditTip = CreateWindowEx(WS_EX_TOPMOST, _T("Edit"),
                            _T("��ʾ�����ַ���"),
                            WS_POPUP | WS_BORDER 
                            | ES_READONLY | ES_MULTILINE | ES_CENTER
                            | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                            0, 200, g_iEditWidth, g_iEditHeight,
                            NULL, NULL,
                            g_hInstance, NULL);
    SendMessage(g_hEditTip, WM_SETFONT, (WPARAM)g_hFont, 0);

    g_szCopyRight = _T("���������Զ���ʾ�� Ver:2005.6\r\n���ߣ�����\r\nʱ�䣺2005��06��13��\r\nE_Mail��kl222@126.com");
    g_hEdit = CreateWindowEx(WS_EX_TOPMOST, _T("Edit"),
                            g_szCopyRight,
                            WS_POPUP | WS_BORDER 
                            | ES_READONLY | ES_MULTILINE | ES_CENTER
                            | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                            0, 200, g_iEditWidth, g_iEditHeight,
                            NULL, NULL,
                            g_hInstance, NULL);
    SendMessage(g_hEdit, WM_SETFONT, (WPARAM)g_hFont, 0);
    //lpEditWndProc = (WNDPROC)SetWindowLong(g_hEdit, GWL_WNDPROC, (LONG)EditWndProc);

    TRY
    {
        CStdioFile sf(g_szPath + _T("\\") + g_szListFile, CFile::modeRead);
        while(sf.ReadString(szTemp))
        {
            SendMessage(g_hSysList, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)szTemp);
        }
        sf.Close();
    }
    CATCH(CFileException, e)
    {
        
        MessageBox(NULL, _T("��Ŀ¼�� ") + g_szPath + _T(" ���Ҳ����ļ���") + g_szListFile + _T(" ���Ѵ��ļ����Ƶ���λ�á�"), _T("�ļ�����"), NULL);
    }
    END_CATCH

    return TRUE;
}

int CAutoDisplayConstOrMacroApp::ExitInstance()
{
    // TODO: �ڴ����ר�ô����/����û���
	TRACE(_T("%s(%d) : CAutoDisplayConstOrMacroApp::ExitInstance()\n"), __FILE__, __LINE__); 
    TRY
    {
        DestroyWindow(g_hEditTip);
        DestroyWindow(g_hSysList);
        if(g_hUserList)
        {
            DestroyWindow(g_hUserList);
        }
        DestroyWindow(g_hEdit);
		UnHook();
    }
    CATCH(CException, e)
    {
        TRACE(_T("%s(%d) : �رվ������\n"), __FILE__, __LINE__);  
    }
    END_CATCH 
    return CWinApp::ExitInstance();
}

/*******************************************************************************************************
��������ClearInput
��  �������ǰ�������
��  ����
        int iCount��Ҫ����ĸ�����Ϊ0ʱ��ȫ�������Ĭ��Ϊ0��
����ֵ����
��  ����2005.6.0.0
��  �ߣ���  ��
ʱ  �䣺2005-6-13 18:21:02
*******************************************************************************************************/
void ClearInput(int iCount)
{
    int iEnd;

    if(iCount == 0)
    {
        iEnd = g_szInput.GetLength() + g_szPrompt.GetLength();
    }
    else
    {
        iEnd = iCount;
    } //���� if(iCount == 0)
    
    for(int i = 0; i < iEnd; i++)
    {
        keybd_event(VK_BACK, 0xFF, KEYEVENTF_EXTENDEDKEY, 0);
        keybd_event(VK_BACK, 0xFF, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    } //���� for(int i = 0; i < iEnd; i++)
}

/*******************************************************************************************************
��������ShowTiShi
��  ������ʾ/������ʾ��
��  ����
         BOOL bShow ����ʾ/������ʾ��Ĭ��Ϊ TRUE��
                      TRUE����ʾ��
                      FALSE�����ء�
         BOOL bClear���Ƿ����ǰ������롣Ĭ��Ϊ FALSE��
                      TRUE�������
                      FALSE���������
����ֵ����
��  ����2005.6.0.0
��  �ߣ���  ��
ʱ  �䣺2005-6-13 16:58:45
*******************************************************************************************************/
void ShowTiShi(BOOL bShow, BOOL bClear)
{
    if(bShow)
    {
        if(!g_bShowTiShi)
        {
            //����������
            if(g_szInput == g_szUserPrompt)
            {
                g_hList = g_hUserList;
            }
            if(g_szInput == g_szPrompt)
            {
                g_hList = g_hSysList;
            }
            int iIndex;
            iIndex = SendMessage(g_hList, LB_GETCURSEL, NULL, NULL);
            if(iIndex == LB_ERR)
            {
                SendMessage(g_hList, LB_SETCURSEL, 0, NULL);
            }
            g_bShowTiShi = TRUE;
            g_szInput = _T("");
            g_hWnd = GetFocus();
            //ע�⣺�����λ�ò��ܱ�
            MoveTiShi();
            ShowWindow(g_hList, SW_SHOW);
            ShowWindow(g_hEdit, SW_SHOW);
            SetFocus(g_hWnd);                    
        } //���� if(!g_bShowTiShi)
    }
    else
    {
       if(g_bShowTiShi)
       {
           ShowWindow(g_hList, SW_HIDE);
           ShowWindow(g_hEditTip, SW_HIDE);
           ShowWindow(g_hEdit, SW_HIDE);
           SetFocus(g_hWnd);
           if(bClear)
           {
               ClearInput();
           } //���� if(bClear)        
           g_bShowTiShi = FALSE;
       } //���� if(g_bShowTiShi)
    } //���� if(bShow)
}

/*******************************************************************************************************
��������MoveTiShi
��  �����ƶ���ʾ��
��  ������
����ֵ����
��  ����2005.6.0.0
��  �ߣ���  ��
ʱ  �䣺2005-6-13 16:58:03
*******************************************************************************************************/
void MoveTiShi()
{
    CPoint caret;
    CSize chSize;
    int top, left;

    //if(!IsWindowVisible(g_hList))
    //{
    //    return;
    //} //���� if(!IsWindowVisible(g_hList))

    if(!g_bShowTiShi)
    {
        return;
    } //���� if(g_bShowTiShi)
    //SetFocus(g_hWnd);
    GetCaretPos(&caret);
    ::ClientToScreen(g_hWnd, &caret);
    TRACE(_T("%s(%d) : %d,%d\n"), __FILE__, __LINE__, caret.x,caret.y);
    GetTextExtentPoint32(GetDC(g_hWnd), _T("a"), 1, &chSize);
    caret.Offset(chSize);
    if(caret.x + g_iListWidth > g_iScreenWidth)
    {
        left = caret.x - g_iListWidth;
    }
    else
    {
        left = caret.x;
    } //���� if(caret.x + g_iListWidth > g_iScreenWidth)
    if(caret.y + g_iListHeight + g_iEditHeight > g_iScreenHeight)
    {
        top = caret.y - g_iListHeight - g_iEditHeight - chSize.cy;
    }
    else
    {
        top = caret.y;
    } //���� if(caret.y + g_iListHeight + g_iEditHeight > g_iScreenHeight)

    g_iListLeft = left;
    g_iListTop = top;

    MoveWindow(g_hList, left, top, g_iListWidth, g_iListHeight, TRUE);
    MoveWindow(g_hEdit, left, top + g_iListHeight, g_iEditWidth, g_iEditHeight, TRUE);
    FindString();

}

/*******************************************************************************************************
��������FindString
��  ��������ʾ���в���ָ�����ַ�������ѡ������
��  ������
����ֵ����
��  ����2005.6.0.0
��  �ߣ���  ��
ʱ  �䣺2005-6-14 10:34:50
*******************************************************************************************************/
void FindString()
{
    /*g_szInput =*/ g_szInput.MakeUpper();
    int iIndex = SendMessage(g_hList, LB_FINDSTRING, 0, (LPARAM)(LPCTSTR)g_szInput);
    if(iIndex != LB_ERR)
    {
        SendMessage(g_hList, LB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)g_szInput);
    } //���� if(iIndex != LB_ERR)
    ShowTip();
}

/*******************************************************************************************************
��������ShowTip
��  ����������ѡ�������ȫ��ʾʱ,��ʾһ�� Edit ����ʾ���
��  ������
����ֵ����
��  ����2005.6.0.0
��  �ߣ���  ��
ʱ  �䣺2005-6-15 13:25:44
*******************************************************************************************************/
void ShowTip()
{
    TCHAR szReceive[MAX_BUFFER];
    int iIndex, iCur;
    iCur = SendMessage(g_hList, LB_GETCURSEL, NULL, NULL);
    if(iCur != LB_ERR)
    {
        iIndex = SendMessage(g_hList, LB_GETTEXT, iCur, (LPARAM)szReceive);
        if(iIndex != LB_ERR)
        {
            CSize size;
            CString sztemp(szReceive);
            //sztemp.TrimRight();
            GetTextExtentPoint32(GetDC(g_hList), sztemp, sztemp.GetLength(), &size);
            if(size.cx > g_iListWidth)
            {
                CRect rect;
                iIndex = SendMessage(g_hList, LB_GETITEMRECT, iCur, (LPARAM)&rect);
                if(iIndex != LB_ERR)
                {
                    int x, y;
                    CPoint topleft, caret;
                    topleft = rect.TopLeft();
                    ::ClientToScreen(g_hList, &topleft);

                    y = topleft.y;

                    CSize chSize;
                    GetCaretPos(&caret);
                    ::ClientToScreen(g_hWnd, &caret);
                    GetTextExtentPoint32(GetDC(g_hWnd), _T("a"), 1, &chSize);
                    caret.Offset(chSize);

                    if(caret.x <= g_iListLeft)
                    {
                        if(g_iListLeft + g_iListWidth + size.cx <= g_iScreenWidth)
                        {
                            x = g_iListLeft + g_iListWidth;
                        }
                        else
                        {
                            x = g_iListLeft - size.cx;
                        }//���� if(g_iListLeft + g_iListWidth + size.cx <= g_iScreenWidth)
                    }
                    else
                    {
                        if(g_iListLeft - size.cx >= 0)
                        {
                            x = g_iListLeft - size.cx;
                        }
                        else
                        {
                            x = g_iListLeft + g_iListWidth;
                        } //���� if(g_iListLeft - size.cx >= 0)
                    }

                    SetWindowText(g_hEditTip, sztemp);
                    MoveWindow(g_hEditTip, x, y, size.cx, size.cy + 1, TRUE);
                    ShowWindow(g_hEditTip, SW_SHOW);
                    SetFocus(g_hWnd);
                    return;
                }
            }
        } //���� if(iIndex != LB_ERR)
    } //���� if(iCur != LB_ERR)

    ShowWindow(g_hEditTip, SW_HIDE);
}

/*******************************************************************************************************
��������CopyString
��  ��������ʾ���е��ַ����Ƶ� IDE ��
��  ����
         TCHAR ch��������ַ���Ĭ��Ϊ NULL�����ӡ�
����ֵ��
��  ����2005.6.0.0
��  �ߣ���  ��
ʱ  �䣺2005-6-14 10:34:04
*******************************************************************************************************/
BOOL CopyString(TCHAR ch)
{
    TCHAR szReceive[MAX_BUFFER];
    int iIndex;
    iIndex = SendMessage(g_hList, LB_GETCURSEL, NULL, NULL);
    if(iIndex != LB_ERR)
    {
        iIndex = SendMessage(g_hList, LB_GETTEXT, iIndex, (LPARAM)szReceive);
        if(iIndex != LB_ERR)
        {
            CString sztemp(szReceive, iIndex);
            if(ch != NULL)
            {
                sztemp += ch;
            } //���� if(ch != NULL)

            if ( !OpenClipboard(NULL) )
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

            LPTSTR lpData;
            HGLOBAL hglbCopy;
            hglbCopy = ::GlobalAlloc(GMEM_MOVEABLE, sztemp.GetLength() + sizeof(TCHAR));
            if(hglbCopy == NULL)
            {
                ::CloseClipboard();
                TRACE(_T("%s(%d) : ȫ�ֶѷ���ʧ�ܡ�\n"), __FILE__, __LINE__);
                return FALSE;
            }
            lpData = (LPTSTR) ::GlobalLock(hglbCopy);
            memcpy(lpData, sztemp, sztemp.GetLength() + sizeof(TCHAR));

            // ���ü��а�����.
            if ( ::SetClipboardData( CF_TEXT, hglbCopy) == NULL )
            {
                TRACE(_T("%s(%d) : �������ü��а����ݡ�\n"), __FILE__, __LINE__);

                CloseClipboard();
                ::GlobalUnlock(hglbCopy);
                GlobalFree(hglbCopy);

                return FALSE;
            }
            // �رռ��а�
            CloseClipboard();
            ::GlobalUnlock(hglbCopy);
            GlobalFree(hglbCopy);

            /* CClipboard cb;
            if(cb.SetData((LPCTSTR)sztemp))
            {*/
            
            keybd_event(VK_SHIFT, 0xff, KEYEVENTF_EXTENDEDKEY, 0);
            keybd_event(VK_INSERT, 0xff, KEYEVENTF_EXTENDEDKEY, 0);
            keybd_event(VK_INSERT, 0xff, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
            keybd_event(VK_SHIFT, 0xff, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
            /*//��ΪCONTROL��SHIFT�г�ͻ,���Բ�������ķ���
            keybd_event(VK_CONTROL, 0xff, KEYEVENTF_EXTENDEDKEY, 0);
            keybd_event('V', 0xff, KEYEVENTF_EXTENDEDKEY, 0);
            keybd_event('V', 0xff, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
            keybd_event(VK_CONTROL, 0xff, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);//*/
            //} //���� if(cb.SetData((LPCTSTR)sztemp))
        } //���� if(iIndx != LB_ERR)
    } //���� if(SendMessage(g_hList, LB_GETCURSEL, NULL, NULL) != LB_ERR)

    return TRUE;
}

/*******************************************************************************************************
��������SetListPos
��  �����ƶ�������е�ѡ����Ŀ
��  ����
         POSTION_ENUM pos���ƶ���ʽ
����ֵ���ɹ���TRUE��ʧ�ܣ�FALSE��
��  ����2005.6.0.0
��  �ߣ���  ��
ʱ  �䣺2005-6-14 21:11:41
*******************************************************************************************************/
BOOL SetListPos(POSTION_ENUM pos)
{
    int iCur, iNum, iCount;
    iNum = 8;

    //------------------------------------------------------------------------
    //��������� === �� BUG-4 λ�ò��ܵ��� === ���ܵ�����
    //

    if(!(0x80 && GetAsyncKeyState(VK_MENU)))
    {
        //ShowTiShi(FALSE, FALSE);
        g_szInput = _T(""); //�� BUG-4
        return FALSE;
    } //���� if(!(0x80 && GetAsyncKeyState(VK_MENU)))
    
    if(!g_bShowTiShi)
    {
        return FALSE;
    } //���� if(!g_bShowTiShi)

    //
    //��������� === �� BUG-4 λ�ò��ܵ��� === ���ܵ�����
    //------------------------------------------------------------------------
           
    iCur = SendMessage(g_hList, LB_GETCURSEL, NULL, NULL);
    if(iCur == LB_ERR)
    {
        iCur = 0;
    } //���� if(iIndex == LB_ERR)
    iCount = SendMessage(g_hList, LB_GETCOUNT, NULL, NULL);
    if(iCount == LB_ERR)
    {
        return FALSE;
    } //���� if(iCount == LB_ERR)
    switch(pos)
    {
    case UP:
        iCur--;
        break;
    case DOWN:
        iCur++;
        break;
    case PAGEUP:
        iCur -= iNum;
        break;
    case PAGEDOWN:
        iCur += iNum;
        break;
    case HOME:
        iCur = 0;
        break;
    case END:
        iCur = iCount - 1;
        break;
    } //���� switch(pos)
    if(iCur < 0)
    {
        iCur = 0;
    } //���� if(iCur < 0)
    if(iCur >= iCount)
    {
        iCur = iCount - 1;
    } //���� if(iCur >= iCount)
    if(SendMessage(g_hList, LB_SETCURSEL, iCur, NULL) != LB_ERR)
    {
        ShowTip();
        return TRUE;
    }
    else
    {
        return FALSE;
    }//���� if(SendMessage(g_hList, LB_SETCURSEL, iCur, NULL) != LB_ERR)
}

/*******************************************************************************************************
��������AddTempList
��  ���������б��е���ʱ��
��  ����
        LPCTSTR lpszItem��Ҫ���ӵ���
����ֵ������Ϊ BOOL ���ɹ�����TRUE�����򷵻�FALSE��
��  ����2005.6.0.1
��  �ߣ���  ��
ʱ  �䣺2006��1��1�� 12:36:16
*******************************************************************************************************/
extern "C" BOOL WINAPI AddTempList(LPCTSTR lpszItem)
{
    if(AddListItem(lpszItem))
    {
        TRY
        {
            CStdioFile sf(g_szPath + _T("\\") + g_szTempFile, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);
            sf.SeekToEnd();
            sf.WriteString(lpszItem);
            sf.WriteString("\r\n");
            sf.Close();    
        }
        CATCH(CFileException, e)
        {
            TRACE(_T("%s(%d) : �ļ�����\n"), __FILE__, __LINE__);
        }
        END_CATCH
        return TRUE;
    }

    return FALSE;
}

/*******************************************************************************************************
��������AddListItem
��  ����������������һ��
��  ����
         LPCTSTR lpszItem��Ҫ���ӵ���
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  ����2005.6.0.0
��  �ߣ���  ��
ʱ  �䣺2005-6-15 21:01:31
*******************************************************************************************************/
extern "C" BOOL WINAPI AddListItem(LPCTSTR lpszItem)
{
    ASSERT(lpszItem != NULL);
    SetListHand();
    int iIndex = SendMessage(g_hList, LB_FINDSTRINGEXACT, 0, (LPARAM)lpszItem);
    if(iIndex == LB_ERR)
    {
        iIndex = SendMessage(g_hList, LB_ADDSTRING, 0, (LPARAM)lpszItem);
        if(iIndex == LB_ERR)
        {
            return FALSE;
        }
        else
        {        
            return TRUE;
        } //���� if(iIndex == LB_ERR)
    } //���� if(iIndex == LB_ERR)
    return FALSE;
}

/*******************************************************************************************************
��������DeleteTempList
��  ����ɾ�������е���ʱ��
��  ������
����ֵ��
��  ����2005.6.0.0
��  �ߣ���  ��
ʱ  �䣺2005-6-18 14:50:34
*******************************************************************************************************/
extern "C" BOOL WINAPI DeleteTempList()
{
    CString szTemp;
    TRY
    {
        CStdioFile sf(g_szPath + _T("\\") + g_szTempFile, CFile::modeRead);
        while(sf.ReadString(szTemp))
        {
            DeleteListItem(szTemp);
        } //���� while(sf.ReadString(szTemp))
        sf.Close();
        sf.Remove(g_szPath + _T("\\") + g_szTempFile);
    }
    CATCH(CFileException, e)
    {
        TRACE(_T("%s(%d) : �ļ�����\n"), __FILE__, __LINE__);
    }
    END_CATCH
    
    return FALSE;
}

/*******************************************************************************************************
��������DeleteListItem
��  ����ɾ��������ָ�����ַ���
��  ����
         LPCTSTR lpszItem��Ҫɾ�����ַ���
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  ����2005.6.0.0
��  �ߣ���  ��
ʱ  �䣺2005-6-15 21:02:18
*******************************************************************************************************/
extern "C" BOOL WINAPI DeleteListItem(LPCTSTR lpszItem)
{
    ASSERT(lpszItem != NULL);
    SetListHand();    
    int iIndex = SendMessage(g_hList, LB_FINDSTRINGEXACT, 0, (LPARAM)lpszItem);
    if(iIndex == LB_ERR)
    {
        return FALSE;
    } //���� if(iIndex == LB_ERR)
    if(SendMessage(g_hList, LB_DELETESTRING, iIndex, NULL) == LB_ERR)
    {
        return FALSE;
    } //���� if(iIndex == LB_ERR)

    return TRUE;
}

/*******************************************************************************************************
��������SetListHand
��  ������������ľ��
��  ������
����ֵ��
��  ����2005.6.0.0
��  �ߣ���  ��
ʱ  �䣺2005-6-16 22:47:07
*******************************************************************************************************/
BOOL SetListHand()
{
    if(NULL == g_hUserList)
    {
        g_hList = g_hSysList;
    }
    else
    {
        g_hList = g_hUserList;
    }
    return TRUE;
}

extern "C" BOOL WINAPI SetVCHook()
{
	return SetHook();
}

/*******************************************************************************************************
��������SetHook
��  �������ü��̹���
��  ������
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  ����2005.6.0.0
��  �ߣ���  ��
ʱ  �䣺2005-6-13 13:10:20
*******************************************************************************************************/
extern "C" BOOL WINAPI SetHook()
{
#ifdef __LIMIT__
#pragma message ("���� __LIMIT__")
    
     AFX_MANAGE_STATE(AfxGetStaticModuleState());
     if(!Regist(FALSE, _T("΢�����������߼�")))
     {
         return FALSE;
     } // ���� if(!Regist(FALSE, _T("΢�����������߼�")))
#endif // ���� #ifdef __LIMIT__
	
	if(g_hKeyHook || g_hMsgHook)
    {
        return FALSE;
    } // ���� if(g_hKeyHook || g_hMsgHook)
    g_hKeyHook = ::SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)KeyboardProc, g_hInstance, ::GetCurrentThreadId());
    g_hMsgHook = ::SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)GetMsgProc, g_hInstance, ::GetCurrentThreadId());
    if(g_hKeyHook && g_hMsgHook)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    } //���� if(g_hKeyHook)
}

/*******************************************************************************************************
��������UnHook
��  �����ͷż��̹���
��  ������
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  ����2005.6.0.0
��  �ߣ���  ��
ʱ  �䣺2005-6-13 13:10:58
*******************************************************************************************************/
extern"C" BOOL WINAPI UnHook()
{
#ifdef __LIMIT__
     AFX_MANAGE_STATE(AfxGetStaticModuleState());
     if(!Regist(FALSE, _T("΢�����������߼�")))
     {
         return FALSE;
     } // ���� if(!Regist(FALSE, _T("΢�����������߼�")))
#endif // ���� #ifdef __LIMIT__

    if(!(g_hMsgHook || g_hKeyHook))
    {
        return FALSE;
    } // ���� if(!(g_hMsgHook || g_hKeyHook))
    BOOL ir;
    ir = UnhookWindowsHookEx(g_hMsgHook);
    if(UnhookWindowsHookEx(g_hKeyHook)&& ir)
    {
		g_hMsgHook = NULL;
		g_hKeyHook = NULL;
        return TRUE;
    } //���� if(UnhookWindowsHookEx(g_hKeyHook))

    return FALSE;
}

/*******************************************************************************************************
��������KeyboardProc
��  �������̹��Ӵ�����
��  ����
         int nCode��ָ���Ƿ���Ҫ�������Ϣ
         WPARAM wParam�������ֵ
         LPARAM lParam��
����ֵ��
��  ����2005.6.0.0
��  �ߣ���  ��
ʱ  �䣺2005-6-13 13:11:26
*******************************************************************************************************/
LRESULT CALLBACK KeyboardProc(int nCode,   //ָ���Ƿ���Ҫ�������Ϣ
    WPARAM wParam,                         //�����ֵ
    LPARAM lParam
    )
{

    if(((DWORD)lParam & 0xC0000000) && (HC_ACTION == nCode))
    {
       switch(wParam) //���̰�����ʶ
       {
       case VK_BACK:
           if(g_szInput.GetLength() == 0 && g_bShowTiShi)
           {
               ShowTiShi(FALSE, FALSE);    
           }
           else
           {
               g_szInput.Delete(g_szInput.GetLength() - 1);
               MoveTiShi();
           }
           TRACE(_T("%s(%d) : BACK:g_szInput=%s\n"), __FILE__, __LINE__, g_szInput);
           break;
       case VK_ESCAPE:
           if(g_bESCFunction)
           {
               ShowTiShi(FALSE);
           }
           else
           {
               ShowTiShi(FALSE, FALSE);
               g_szInput = _T("");
           }//���� if(g_bESCFunction)           
           break;
#ifdef __VCNET__
       case VK_OEM_4:
           //keybd_event(VK_OEM_6, 0xff, KEYEVENTF_EXTENDEDKEY, 0);
           //keybd_event(VK_OEM_6, 0xff, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);

           //if(!(0x80 && GetAsyncKeyState(VK_SHIFT)))
           //{
           //    keybd_event(VK_SHIFT, 0xff, KEYEVENTF_EXTENDEDKEY, 0);
           //   keybd_event(VK_SHIFT, 0xff, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);    
           //} //���� if(!(0x80 && GetAsyncKeyState(VK_MENU)))       
           //keybd_event(VK_LEFT, 0xff, KEYEVENTF_EXTENDEDKEY, 0);
           //keybd_event(VK_LEFT, 0xff, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);    
           break;
#endif
       case VK_SPACE:
           //ShowTiShi(FALSE);
           break;
       case VK_DOWN: //����
           SetListPos(DOWN);
           break;
       case VK_UP: //����
           SetListPos(UP);
           break;
       case VK_PRIOR:
           SetListPos(PAGEUP);
           break;
       case VK_NEXT:
           SetListPos(PAGEDOWN);
           break;
       case VK_HOME:
           SetListPos(HOME);
           break;
       case VK_END:
           SetListPos(END);
           break;
       default:
           break;
       }
       //TRACE(_T("%s(%d) : g_szInput=%s\n"), __FILE__, __LINE__, g_szInput);

     }
    
    return CallNextHookEx(g_hKeyHook, nCode, wParam, lParam);
}

/*******************************************************************************************************
��������GetMsgProc
��  �ܣ�������Ϣ���Ӻ���
��  ����
		int code�����Ӵ���
		WPARAM wParam�� �Ƴ���־
		LPARAM lParam����Ϣ�ĵ�ַ
����ֵ��
��  �ߣ���  ��
��  ����2005.6.0.0
��  �ڣ�2004-12-5
ʱ  �䣺14:46:42
*******************************************************************************************************/
LRESULT CALLBACK GetMsgProc(int nCode,        // hook code
							WPARAM wParam,  // �Ƴ���־
							LPARAM lParam   // ��Ϣ�ĵ�ַ
							)
{
    MSG* pMsg = (MSG*) lParam;
    switch(pMsg->message)
    {		
    case WM_CHAR:
        {			
            if(PM_REMOVE == wParam)
            {
                switch(pMsg->wParam)
                {
                case 0x08:  // backspace 
                    break;
                case 0x1B:  // escape 
                    break;
                case '+':
                case '!':
                case '-':
                case '*':
                case '/':
                case '\\':
                case ';':
                case ':':
                case '(':                    
                case ')':                    
                case '[':
                case ']':
                case '{':
                case '}':
                case '&':
                case '%':
                case '>':
                case '<':
                case '=':
                case '.':
                case ',':
                case '?':
                case '~':
                case '|':
                case '^':
                case '\'':
                case '"':
                case 0x20:  // �ո�
                    if(g_bShowTiShi)
                    {
                        ShowTiShi(FALSE);
                        ClearInput(1);
                        CopyString((TCHAR)pMsg->wParam);
                        break;
                    } //���� if(g_bShowTiShi)
                default:
                    g_szInput += (TCHAR)pMsg->wParam;
                    MoveTiShi();
                    break;
                }

            }//if(PM_NOREMOVE == wParam)
        }

        if(g_szInput == g_szPrompt || g_szInput == g_szUserPrompt)
        {
            ShowTiShi();
        }
        else
        {
            if(g_szInput.GetLength() > g_szPrompt.GetLength() && !g_bShowTiShi)
            {
                g_szInput = g_szInput.Right(g_szInput.GetLength() - 1);
            } //���� if(g_szInput.GetLength() > g_szPrompt.GetLength())
            if(g_szInput == g_szPrompt || g_szInput == g_szUserPrompt)
            {   
                ShowTiShi();
            } //���� if(g_szInput == g_szPrompt)
        } //���� if(g_szInput == g_szPrompt)

        //TRACE(_T("%s(%d) : WS_CHAR:g_szInput=%s\n"), __FILE__, __LINE__, g_szInput);
        break;
    default:
        break;		
    }

    LRESULT lresult;

    lresult= ::CallNextHookEx(g_hMsgHook, nCode, wParam, lParam);

    return lresult;
}

/*******************************************************************************************************
��������WindowProc
��  ���������ܵ���Ϣ�������
��  ����
         HWND hWnd���������
         UINT uMsg����Ϣ
         WPARAM wParam������
         LPARAM lParam������
����ֵ��
��  ����2005.6.0.0
��  �ߣ���  ��
ʱ  �䣺2005-6-14 15:21:08
*******************************************************************************************************/
LRESULT CALLBACK WindowProc(HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
    )
{
    switch(uMsg)
    {
    case WM_LBUTTONDBLCLK:
        if(g_bShowTiShi)
        {
            SetFocus(g_hWnd);
            ShowTiShi(FALSE);
            CopyString();            
            break;
        } //���� if(g_bShowTiShi) 
    case WM_LBUTTONUP:
        if(g_bShowTiShi)
        {
            ShowTip();
        }
        break;
    } //���� switch(uMsg)
    return CallWindowProc(lpWndProc, hWnd, uMsg, wParam, lParam);
}

/*******************************************************************************************************
��������UserWindowProc
��  �����û����������ܵ���Ϣ�������
��  ����
         HWND hWnd���������
         UINT uMsg����Ϣ
         WPARAM wParam������
         LPARAM lParam������
����ֵ��
��  ����2005.6.0.0
��  �ߣ���  ��
ʱ  �䣺2005-6-14 15:21:08
*******************************************************************************************************/
LRESULT CALLBACK UserWindowProc(HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
    )
{
    switch(uMsg)
    {
    case WM_LBUTTONDBLCLK:
        if(g_bShowTiShi)
        {
            ShowTiShi(FALSE);

            CopyString();
            break;
        } //���� if(g_bShowTiShi) 
    case WM_LBUTTONUP:
        if(g_bShowTiShi)
        {
            ShowTip();
        }
        break;
    } //���� switch(uMsg)
    return CallWindowProc(lpWndProc, hWnd, uMsg, wParam, lParam);
}

/*******************************************************************************************************
��������EditWndProc
��  ������ȨEdit��Ϣ������
��  ����
         HWND hWnd��
         UINT uMsg��
         WPARAM wParam��
         LPARAM lParam��
����ֵ��
��  ����2005.6.0.0
��  �ߣ���  ��
ʱ  �䣺2005-6-14 21:13:50
*******************************************************************************************************/
LRESULT CALLBACK EditWndProc(HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
    )
{
    switch(uMsg)
    {
    case WM_PAINT:
        PAINTSTRUCT ps; 
        HDC hdc, hComDC;
        HBITMAP bmp;
        BITMAP bitmap;
  
        hdc = BeginPaint(hWnd, &ps);
        bmp = ::LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_KL));
        GetObject(bmp, sizeof(BITMAP), &bitmap);
        hComDC = ::CreateCompatibleDC(hdc);
        ::SelectObject(hComDC, bmp);

        BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hComDC, 0, 0,SRCCOPY);
        TextOut(hdc, 0, 0, g_szCopyRight, g_szCopyRight.GetLength());
        EndPaint(hWnd, &ps);        

        return 0L; 

        break;
    default:
        break;
    } //���� switch(uMsg)
    return CallWindowProc(lpEditWndProc, hWnd, uMsg, wParam, lParam);
}
