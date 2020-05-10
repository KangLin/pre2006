// TiShi.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TiShi.h"

// CTiShi

CTiShi::CTiShi()
{
    m_hInstance = NULL;  
}

CTiShi::CTiShi(HINSTANCE hInstance)
{
    m_hInstance = hInstance;
    Inital();
}

CTiShi::~CTiShi()
{
    DestroyWindow(m_hEditTip);
    DestroyWindow(m_hList);
    DestroyWindow(m_hEdit);
}

// ����ʵ�����
void CTiShi::SetInstance(HINSTANCE hInstance)
{
    ASSERT(hInstance != NULL);
    if(m_hInstance)
    {
        return;
    } //���� if(hInstance)
    m_hInstance = hInstance;
    Inital();
}

// ��ʼ��
BOOL CTiShi::Inital(void)
{
    m_hParent = NULL;
    m_iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
    m_iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
    m_iTop = 0;
    m_iLeft = 0;
    m_iListWidth = 200;
    m_iListHeight = 200;
    m_iEditWidth = m_iListWidth;
    m_iEditHeight = 55;    
    m_szFont = _T("����");

    m_hFont = CreateFont(12, 0, 0, 0, 0,
                         FALSE, FALSE, FALSE,
                         DEFAULT_CHARSET, DEFAULT_QUALITY,
                         DEFAULT_QUALITY, DEFAULT_QUALITY,
                         FIXED_PITCH + FF_SWISS, m_szFont);

    m_hList = CreateWindowEx(WS_EX_TOPMOST, _T("ListBox"),
                             _T(""),
                             WS_POPUP | WS_BORDER | WS_VSCROLL | LBS_SORT,
                             m_iTop, m_iLeft, m_iListWidth, m_iListHeight,
                             NULL, NULL,
                             m_hInstance, NULL);
    SendMessage(m_hList, WM_SETFONT, (WPARAM)m_hFont, 0);
    lpWndProc = (WNDPROC)SetWindowLong(m_hList, GWL_WNDPROC, (LONG)WindowProc);

    m_hEditTip = CreateWindowEx(WS_EX_TOPMOST, _T("Edit"),
                            _T(""),
                            WS_POPUP | WS_BORDER 
                            | ES_READONLY | ES_MULTILINE | ES_CENTER
                            | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                            0, 0, 0, 0,
                            m_hList, NULL,
                            m_hInstance, NULL);
    SendMessage(m_hEditTip, WM_SETFONT, (WPARAM)m_hFont, 0);

    m_hEdit = CreateWindowEx(WS_EX_TOPMOST, _T("Edit"),
                            _T(""),
                            WS_POPUP | WS_BORDER 
                            | ES_READONLY | ES_MULTILINE | ES_CENTER
                            | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                            m_iTop + m_iListHeight, m_iLeft, m_iEditWidth, m_iEditHeight,
                            NULL, NULL,
                            m_hInstance, NULL);
    SendMessage(m_hEdit, WM_SETFONT, (WPARAM)m_hFont, 0);

    SetCopyRightInfo(_T("���������Զ���ʾ��\r\n���ߣ�����\r\nʱ�䣺2005��06��13��\r\nE_Mail��kl222@126.com"));
    SetListText(_T("��ʾ��"));

    return TRUE;
}

// ����������
BOOL CTiShi::AddListItem(LPCTSTR lpszItem, BOOL bDirectness)
{
	ASSERT(lpszItem != NULL);
	//ֱ������
    if(bDirectness)
    {
        int iIndex = SendMessage(m_hList, LB_ADDSTRING, 0, (LPARAM)lpszItem);
        if(iIndex == LB_ERR)
        {
            return FALSE;
        }
        else
        {        
            return TRUE;
        } //���� if(iIndex == LB_ERR)
	} //���� if(bDirectness)
	//�����Ƿ����Ѵ���,�������,�򲻼�
    int iIndex = SendMessage(m_hList, LB_FINDSTRINGEXACT, 0, (LPARAM)lpszItem);
    if(iIndex == LB_ERR)
    {
        iIndex = SendMessage(m_hList, LB_ADDSTRING, 0, (LPARAM)lpszItem);
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

// ɾ��������
BOOL CTiShi::DeleteListItem(LPCTSTR lpszItem)
{
    ASSERT(lpszItem != NULL);
    int iIndex = SendMessage(m_hList, LB_FINDSTRINGEXACT, 0, (LPARAM)lpszItem);
    if(iIndex == LB_ERR)
    {
        return FALSE;
    } //���� if(iIndex == LB_ERR)
    if(SendMessage(m_hList, LB_DELETESTRING, iIndex, NULL) == LB_ERR)
    {
        return FALSE;
    } //���� if(iIndex == LB_ERR)

    return TRUE;
}

/*******************************************************************************************************
��������CopyString
��  ��������ʾ���е��ַ����Ƶ�IDE��
��  ����
         TCHAR ch��������ַ���Ĭ��Ϊ NULL�����ӡ�
����ֵ����
��  ����2005.6.0.0
��  �ߣ���  ��
ʱ  �䣺2005-6-14 10:34:04
*******************************************************************************************************/
BOOL CTiShi::CopyString(TCHAR ch)
{
    TCHAR szReceive[MAX_BUFFER];
    int iIndex;
    iIndex = SendMessage(m_hList, LB_GETCURSEL, NULL, NULL);
    if(iIndex != LB_ERR)
    {
        iIndex = SendMessage(m_hList, LB_GETTEXT, iIndex, (LPARAM)szReceive);
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
    } //���� if(SendMessage(m_hList, LB_GETCURSEL, NULL, NULL) != LB_ERR)
}

// ����ָ�����ַ���������ȫƥ�䣩
BOOL CTiShi::FindString(LPCTSTR lpszItem)
{
    ASSERT(lpszItem != NULL);
    if(!MoveTiShi())
    {
        return FALSE;
    }

    CString sztemp(lpszItem);
    int iIndex = SendMessage(m_hList, LB_FINDSTRING, -1, (LPARAM)(LPCTSTR)sztemp.MakeUpper());
    if(iIndex != LB_ERR)
    {
        if(SendMessage(m_hList, LB_SELECTSTRING, -1, (LPARAM)(LPCTSTR)sztemp) != LB_ERR)
        {
            ShowTip();
            return TRUE;
        }
    } //���� if(iIndex != LB_ERR)
    
    ShowTip();
    return FALSE;
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
void CTiShi::ShowTip()
{
    TCHAR szReceive[MAX_BUFFER];
    int iIndex, iCur;
    iCur = SendMessage(m_hList, LB_GETCURSEL, NULL, NULL);
    if(iCur != LB_ERR)
    {
        iIndex = SendMessage(m_hList, LB_GETTEXT, iCur, (LPARAM)szReceive);
        if(iIndex != LB_ERR)
        {
            CSize size;
            CString sztemp(szReceive);
            //sztemp.TrimRight();
            GetTextExtentPoint32(GetDC(m_hList), sztemp, sztemp.GetLength(), &size);
            if(size.cx > m_iListWidth)
            {
                CRect rect;
                iIndex = SendMessage(m_hList, LB_GETITEMRECT, iCur, (LPARAM)&rect);
                if(iIndex != LB_ERR)
                {
                    int x, y;
                    CPoint topleft, caret;
                    topleft = rect.TopLeft();
                    ::ClientToScreen(m_hList, &topleft);

                    y = topleft.y;

                    CSize chSize;
                    GetCaretPos(&caret);
                    ::ClientToScreen(m_hParent, &caret);
                    GetTextExtentPoint32(GetDC(m_hParent), _T("a"), 1, &chSize);
                    caret.Offset(chSize);

                    if(caret.x <= m_iLeft)
                    {
                        if(m_iLeft + m_iListWidth + size.cx <= m_iScreenWidth)
                        {
                            x = m_iLeft + m_iListWidth;
                        }
                        else
                        {
                            x = m_iLeft - size.cx;
                        }//���� if(m_iLeft + m_iListWidth + size.cx <= m_iScreenWidth)
                    }
                    else
                    {
                        if(m_iLeft - size.cx >= 0)
                        {
                            x = m_iLeft - size.cx;
                        }
                        else
                        {
                            x = m_iLeft + m_iListWidth;
                        } //���� if(m_iLeft - size.cx >= 0)
                    }

                    SetWindowText(m_hEditTip, sztemp);
                    MoveWindow(m_hEditTip, x, y, size.cx, size.cy + 1, TRUE);
                    ShowWindow(m_hEditTip, SW_SHOW);
                    SetFocus(m_hParent);
                    return;
                }
            }
        } //���� if(iIndex != LB_ERR)
    } //���� if(iCur != LB_ERR)

    ShowWindow(m_hEditTip, SW_HIDE);
}

// ���ð�Ȩ��Ϣ
BOOL CTiShi::SetCopyRightInfo(LPCTSTR lpszCopyRight)
{
    CString szTemp, szLeave;
    int iPos;
    CSize tmpsize, Size(150, 0);
    
    m_szEditText = lpszCopyRight;
    szTemp = m_szEditText;
    iPos = szTemp.Find("\r\n");
    do
    {
        if(iPos != -1)
        {
           //����: Right ִ�к��Ƿ�ı�ԭ���Ĵ洢��
            szLeave = szTemp.Right(szTemp.GetLength() - iPos + 1);
            szTemp = szTemp.Left(iPos - 1);
        }
        //����: �Ƿ��ܲ��Գ��������з��ַ����Ĵ�С
        if(GetTextExtentPoint32(GetDC(m_hEdit), szTemp, szTemp.GetLength(), &tmpsize))
        {
            if(tmpsize.cx > Size.cx)
            {
                Size.cx = tmpsize.cx;
            } // ���� if(tmpsize.cx > Size.cx)
            Size.cy += tmpsize.cy;
        } // ���� if(GetTextExtentPoint32(GetDC(m_hEdit), szTemp, szTemp.GetLength(), &tmpsize))
        iPos = szTemp.Find("\r\n");
    }  while(iPos != -1);

    m_iListWidth = Size.cx;
    m_iEditWidth = m_iListWidth;
    m_iEditHeight = Size.cy;
    
    SetWindowText(m_hEdit, m_szEditText);
    MoveTiShi();
    return 0;
}

// �������������
BOOL CTiShi::SetListText(LPCTSTR lpszText)
{
    SetWindowText(m_hList, lpszText);
    return 0;
}

// ��ʾ/������ʾ��
BOOL CTiShi::ShowTiShi(bool bShow,  HWND hParent)
{
    if(bShow)
    {
        m_bShow = TRUE;
        if(hParent)
        {
            m_hParent = hParent;
        }
        else
        {
            m_hParent = GetFocus();
        } //���� if(hParent)
        int iIndex;
        iIndex = SendMessage(m_hList, LB_GETCURSEL, NULL, NULL);
        if(iIndex == LB_ERR)
        {
            SendMessage(m_hList, LB_SETCURSEL, 0, NULL);
        }
        MoveTiShi();        
        ShowWindow(m_hList, SW_SHOW);
        ShowWindow(m_hEdit, SW_SHOW);
        SetFocus(m_hParent);
    }
    else
    {
        m_bShow = FALSE;
        ShowWindow(m_hList, SW_HIDE);
        ShowWindow(m_hEdit, SW_HIDE);
    }
    return 0;
}

/*******************************************************************************************************
��������Showed
��  �����õ���ʾ�����ʾ״̬��
��  ������
����ֵ������Ϊ BOOL ����ʾ����TRUE�����򷵻�FALSE��
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��8��28�� 9:36:56
*******************************************************************************************************/
BOOL CTiShi::Showed()
{
	retrun m_bShow;
}

// �ƶ���ʾ��
BOOL CTiShi::MoveTiShi(void)
{
    if(!m_bShow)
    {
        return FALSE;
    }

    CPoint caret;
    if(!GetCaretPos(&caret))
    {
        return FALSE;
    }
    ClientToScreen(m_hParent, &caret);

    CSize size;
    if(!GetTextExtentPoint32(GetDC(m_hParent), _T("a"), 1, &size))
    {
        return FALSE;
    }
    //�޸�:�ڱ�������Ҫ�ڲ������һ���ַ�����ʾ,��������.
    //     �������ֱ���ڲ������ʾ,ֻҪ��������پ���,�����겻Ҫ��
    caret.Offset(size);
	if(caret.x + m_iListWidth <= m_iScreenWidth)
    {
		m_iLeft = caret.x;
    }
    else
    {
		m_iLeft = caret.x - m_iListWidth;
    }
    if(size.cy + m_iListHeight + m_iEditHeight <= m_iScreenHeight)
    {
		m_iTop = caret.y;
    }
    else
    {
		m_iTop = caret.y - m_iListHeight - m_iEditHeight;
    }

    MoveWindow(m_hList, m_iLeft, m_iTop, m_iListWidth, m_iListHeight, TRUE);
    MoveWindow(m_hEdit, m_iLeft, m_iTop + m_iListHeight, m_iEditWidth, m_iEditHeight, TRUE);

    return 0;
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
BOOL CTiShi::SetListPos(POSTION_ENUM pos)
{
    int iCur, iNum, iCount;
    iNum = 8;

    //------------------------------------------------------------------------
    //��������� === �� BUG-4 λ�ò��ܵ��� === ���ܵ�����
    //

    if(!(0x80 && GetAsyncKeyState(VK_MENU)))
    {
        //ShowTiShi(FALSE, FALSE);
        //m_szInput = _T(""); //�� BUG-4
        return FALSE;
    } //���� if(!(0x80 && GetAsyncKeyState(VK_MENU)))
    
    if(!m_bShow)
    {
        return FALSE;
    } //���� if(!m_bShowTiShi)

    //
    //��������� === �� BUG-4 λ�ò��ܵ��� === ���ܵ�����
    //------------------------------------------------------------------------
           
    iCur = SendMessage(m_hList, LB_GETCURSEL, NULL, NULL);
    if(iCur == LB_ERR)
    {
        iCur = 0;
    } //���� if(iIndex == LB_ERR)
    iCount = SendMessage(m_hList, LB_GETCOUNT, NULL, NULL);
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
    if(SendMessage(m_hList, LB_SETCURSEL, iCur, NULL) != LB_ERR)
    {
        ShowTip();
        return TRUE;
    }
    else
    {
        return FALSE;
    }//���� if(SendMessage(m_hList, LB_SETCURSEL, iCur, NULL) != LB_ERR)
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
LRESULT CALLBACK CTiShi::WindowProc(HWND hWnd,
                                    UINT uMsg,
                                    WPARAM wParam,
                                    LPARAM lParam
                                    )
{
    //switch(uMsg)
    //{
    //case WM_LBUTTONDBLCLK:
    //    if(m_bShow)
    //    {
    //        ShowTiShi(FALSE);

    //        CopyString();
    //        break;
    //    } //���� if(m_bShowTiShi) 
    //case WM_LBUTTONUP:
    //    if(m_bShow)
    //    {
    //        ShowTip();
    //    }
    //    break;
    //} //���� switch(uMsg)
    //return CallWindowProc(lpWndProc, hWnd, uMsg, wParam, lParam);
    return 0;
}
