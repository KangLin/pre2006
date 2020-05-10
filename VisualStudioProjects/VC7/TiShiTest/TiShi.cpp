/*******************************************************************************************************
��Ȩ���� (C) 2006 ���ֹ����ң���������Ȩ����
�ļ�����TiShi.cpp
��  ���������ʾ�����ʾ���ַ����ҡ�ToolTip�����й��ܡ�
ʹ  �ã�
        1������һ������
		2����ʼ��
		   a�����ļ��м�����Ŀ������LoadString
		   b����AddStringһ�����ļ�
		   c����������LoadString���Զ���������ݡ�
		3�������Ҫ��ע��ص�������
		4��Ҫ������ʾ��λ��ʱ������Show����
		   Ҳ����ѡ����Show���ٵ�����Ӧ��Move
	    5����������OnEnter������EnterFun��������ȷ�������º���¼���
��  ����1.0.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2006��1��2��
ʱ  �䣺10:48:34
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
*******************************************************************************************************/

#include "stdafx.h"
#include "TiShiTest.h"
#include "TiShi.h"
#include ".\tishi.h"


// CTiShi

IMPLEMENT_DYNAMIC(CTiShi, CListBox)
CTiShi::CTiShi()
{
	m_iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
    m_iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
    m_iTop = 0;
    m_iLeft = 0;
	m_iListWidth = 200;
	m_iListHeight = 200;
    m_iEditWidth = m_iListWidth;
	m_iEditHeight = 55;
	m_bShow = FALSE;
	m_szInput = _T("");

	m_bVerTiShi = TRUE;
	m_hParent = NULL;

	m_EnterFun = NULL;
	m_KeyPressFun = NULL;
	m_ShowTipFun = NULL;

}

CTiShi::~CTiShi()
{
}


BEGIN_MESSAGE_MAP(CTiShi, CListBox)
	ON_WM_CREATE()
	ON_WM_LBUTTONUP()
    ON_WM_KEYUP()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CTiShi ��Ϣ�������
void CTiShi::OnLButtonUp(UINT nFlags, CPoint point)
{
	OnLeftButtonEvents(GetString());

	CListBox::OnLButtonUp(nFlags, point);
	GetString();
}

void CTiShi::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if(m_EnterFun)
	{
		m_EnterFun(GetString());
	}// ���� if(m_EnterFun)
	OnEnter(GetString());

	CListBox::OnLButtonDblClk(nFlags, point);
}

/*******************************************************************************************************
��������OnLeftButton
��  �������ڴ����������¼�������һ�����⺯�����û����������������Զ����Լ����¼���
��  ����
		LPCTSTR lpszText���б�ѡ����ı�
����ֵ������Ϊ void ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��8��29�� 8:07:45
*******************************************************************************************************/
void CTiShi::OnLeftButtonEvents(LPCTSTR lpszText)
{
	TRACE(_T("CTiShi::OnLeftButton"));
	return;
}

//�޸�:�������뻹û�����
void CTiShi::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int nIndex = GetCurSel();
	if(nIndex != -1)
	{
		switch(nChar)
		{
		case VK_UP:
			TRACE("UP\n");
		case VK_DOWN:
			TRACE("Down\n");
		case VK_PRIOR:
			TRACE("PageUP\n");
		case VK_NEXT:
			TRACE("PageDown\n");
			break;
		case VK_RETURN:
			TRACE("RETURN\n");
			if(m_EnterFun)
			{
				m_EnterFun(GetString());
			}// ���� if(m_EnterFun)
			OnEnter(GetString());
			break;
		default:
			TRACE("Other\n");
			::SetFocus(m_hParent); //���ý���Ϊ������
		}// ���� switch(nChar)

		OnKeyEvents(nChar, GetString());
		m_KeyPressFun(nChar, nRepCnt, nFlags);
	}	

error_exit:
	CListBox::OnKeyUp(nChar, nRepCnt, nFlags);
	GetString();
}

/*******************************************************************************************************
��������OnKeyEvents
��  �������ڴ�������¼�������һ�����⺯�����û����������������Զ����Լ����¼���
��  ����
        UINT nChar      �������
		LPCTSTR lpszText���б�ѡ����ı�
����ֵ������Ϊ void ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��1��2�� 11:03:39
*******************************************************************************************************/
void CTiShi::OnKeyEvents(UINT nChar, LPCTSTR lpszText)
{
	TRACE(_T("GetText:%s\n"), lpszText);
	TRACE(_T("CTiShi::OnKeyEvents\n"));
	return;
}

/*******************************************************************************************************
��������OnEnter
��  ����Enter ���¼�������һ�����⺯�����û����������������Զ����Լ����¼���
��  ����
        LPCTSTR lpszText����ǰѡ�����Ŀ���ݡ�
����ֵ������Ϊ void ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��9��4�� 13:56:32
*******************************************************************************************************/
void CTiShi::OnEnter(LPCTSTR lpszText)
{
	::SetFocus(m_hParent);
	Show(m_hParent, FALSE);
	return;
}

/*******************************************************************************************************
��������RegisterKeyPress
��  ����ע�ᴦ�������Ϣ�Ļص�����
��  ����
        KeyPressFun fun��������Ϣ����ص�������
����ֵ������Ϊ BOOL ��
*******************************************************************************************************/
BOOL CTiShi::RegisterKeyPress(KeyPressFun fun)
{
	if(fun == NULL)
	{
		return FALSE;
	}// ���� if(fun == NULL)
	m_KeyPressFun = fun;
	return TRUE;
}

/*******************************************************************************************************
��������RegisterEnterFun
��  ��������ȷ�����Ļص�����
��  ����
        EnterFun fun���ص�����ָ��
����ֵ������Ϊ BOOL ���ɹ�����TURE�����򷵻�FALSE��
*******************************************************************************************************/
BOOL CTiShi::RegisterEnterFun(EnterFun fun)
{
	if(fun == NULL)
	{
		return FALSE;
	} // ���� if(fun == NULL)
	m_EnterFun = fun;
	return TRUE;
}

/*******************************************************************************************************
��������RegisterShowTip
��  ����ע����Ŀ������ʾ��Ļص�������
��  ����
        ShowTipFun fun����Ŀ������ʾ��Ļص����������Ķ��壺
		typedef int(*ShowTipFun)(UINT nIndex, LPCTSTR lpcszText)
		������
		     UINT nIndex����ѡ����Ŀ������
			 LPCTSTR lpcszText����ѡ����Ŀ������
����ֵ������Ϊ BOOL ��
*******************************************************************************************************/
BOOL CTiShi::RegisterShowTip(ShowTipFun fun)
{
	if(fun == NULL)
	{
		return FALSE;
	}// ���� if(fun == NULL)
	m_ShowTipFun = fun;
	return TRUE;
}

// ���ð�Ȩ��Ϣ
int CTiShi::SetCopyRight(LPCTSTR lpszCopyRight)
{
	CString szTemp, szLeave, m_szEditText;
    int iPos;
	CSize tmpsize, Size(m_iEditWidth, 0);
    
    m_szEditText = lpszCopyRight;
	GetFontSize(GetSafeHwnd(), m_szEditText, &Size);

    m_iListWidth = Size.cx;
    m_iEditWidth = m_iListWidth;
    m_iEditHeight = Size.cy;
    
	m_Edit.SetWindowText(m_szEditText);
    Move();
    
	return 1;
}

int CTiShi::ShowCopyRight(BOOL bShow)
{
	return m_bVerTiShi = bShow;
}

// �õ�ָ������Ĵ�С
int CTiShi::GetFontSize(HWND hWnd, LPCTSTR lpszText, LPSIZE lpSize)
{
	CString szTemp = lpszText;
	CString szLeave;
	int iPos = szTemp.Find("\r\n");
	CSize Size(0, 0), tmpsize;
	while(1)
	{
		if(iPos != -1)
		{
			// Right ִ�к�û�иı�ԭ���Ĵ洢��
			szLeave = szTemp.Right(szTemp.GetLength() - iPos - 2);
			szTemp = szTemp.Left(iPos);
		}
		//���ܲ��Գ��������з��ַ����Ĵ�С
		if(GetTextExtentPoint32(::GetDC(hWnd), szTemp, szTemp.GetLength(), &tmpsize))
		{
			if(tmpsize.cx > Size.cx)
			{
				Size.cx = tmpsize.cx;
			} // ���� if(tmpsize.cx > Size.cx)
			Size.cy += tmpsize.cy; 
		}
		else
		{
			return FALSE;
		} // ���� if(GetTextExtentPoint32(::GetDC(hWnd), szTemp, szTemp.GetLength(), &tmpsize))

		if(iPos == -1)
		{
			break;
		} // ���� if(iPos == -1)
		szTemp = szLeave;
		iPos = szTemp.Find("\r\n");
	} // ���� (1)
	lpSize->cx = Size.cx;
	lpSize->cy = Size.cy;
	return TRUE;
}

// ��������
int CTiShi::SetFont(LPCTSTR lpszFacename,
					int nHeight,
					int nWidth,
					int nEscapement,
					int nOrientation,
					int nWeight,
					BYTE bItalic,
					BYTE bUnderline,
					BYTE cStrikeOut,
					BYTE nCharSet,
					BYTE nOutPrecision,
					BYTE nClipPrecision,
					BYTE nQuality,
					BYTE nPitchAndFamily
					)
{
	CString szFont = lpszFacename;

	m_Font.Detach();
	m_Font.CreateFont(nHeight, nWidth, nEscapement, nOrientation, nWeight, bItalic, bUnderline, cStrikeOut, nCharSet, nOutPrecision,
		nClipPrecision, nQuality, nPitchAndFamily, lpszFacename);
	return SetFont(&m_Font);
}

int CTiShi::SetFont(CFont * pFont)
{
	CListBox::SetFont(pFont);
	m_Edit.SetFont(pFont);
	m_edTip.SetFont(pFont);
	return 1;
}

/*******************************************************************************************************
��������CreateEx
��  ����������ʾ��
��  ����
        HWND hParent�������ھ����
����ֵ������Ϊ BOOL ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��8��29�� 10:33:42
*******************************************************************************************************/
BOOL CTiShi::CreateEx(HWND hParent)
{
	if(m_hParent)
	{
		return FALSE;
	} // ���� if(m_hParent)

	m_hParent = hParent;
	
	return CListBox::CreateEx(WS_EX_TOPMOST,
		_T("ListBox"), NULL, WS_POPUP | WS_BORDER | WS_VSCROLL | LBS_SORT,
		m_iLeft, m_iTop, m_iListWidth, m_iListHeight,
		NULL, NULL, NULL);
}

int CTiShi::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_Edit.CreateEx(WS_EX_TOPMOST, _T("Edit"), NULL,
					WS_POPUP | WS_BORDER
					| ES_READONLY | ES_MULTILINE | ES_CENTER
					| ES_AUTOVSCROLL | ES_AUTOHSCROLL,
					m_iLeft, m_iTop + m_iListHeight, m_iEditWidth, m_iEditHeight,
					this->GetSafeHwnd(), NULL);
	SetCopyRight(_T("���ߣ�����\r\nʱ�䣺2005��06��13��\r\nE_Mail��kl222@126.com"));
	m_edTip.CreateEx(WS_EX_TOPMOST, _T("Edit"), NULL,
					WS_POPUP | WS_BORDER | ES_READONLY | ES_MULTILINE //| ES_CENTER 
					| ES_AUTOVSCROLL | ES_AUTOHSCROLL,
					0, 0, 0, 0,
					this->GetSafeHwnd(), NULL);
	SetFont();
	InitToolTip();
	return 0;
}

/*******************************************************************************************************
��������Move
��  �����ƶ���ʾ��
��  ������
����ֵ������Ϊ BOOL ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��1��2�� 11:16:37
*******************************************************************************************************/
BOOL CTiShi::Move()
{
	if(!(m_hParent && m_bShow))
    {
        return FALSE;
    } // ���� if(!(m_hParent && m_bShow))

    CPoint caret;
	if(!::GetCaretPos(&caret))
    {
        return FALSE;
    }
	::ClientToScreen(m_hParent, &caret);

    CSize size;
	if(!GetTextExtentPoint32(::GetDC(m_hParent), _T("a"), 1, &size))
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
	if(caret.y + m_iListHeight + m_iEditHeight <= m_iScreenHeight)
    {
		m_iTop = caret.y;
    }
    else
    {
		m_iTop = caret.y - m_iListHeight - m_iEditHeight - size.cy;
    }

	MoveWindow(m_iLeft, m_iTop, m_iListWidth, m_iListHeight, TRUE);
	m_Edit.MoveWindow(m_iLeft, m_iTop + m_iListHeight, m_iEditWidth, m_iEditHeight, TRUE);

	FindText();

	//����:�ƶ���Ŀ������ʾ���λ��

	::SetFocus(m_hParent);

	return TRUE;
}

/*******************************************************************************************************
��������Move
��  ����
��  ����
        UINT nCh��������ַ�
����ֵ������Ϊ BOOL ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��1��2�� 11:15:58
*******************************************************************************************************/
BOOL CTiShi::Move(UINT nCh)
{
	switch(nCh)
	{
	case VK_BACK:
		m_szInput.Delete(m_szInput.GetLength() - 1);
		break;
	default:
		m_szInput += (TCHAR)nCh;
	} // ���� (m_szInput.GetLength() - 1)
	return Move();
}

/*******************************************************************************************************
��������Move
��  ����
��  ����
        TCHAR ch��������ַ�
����ֵ������Ϊ BOOL ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��1��2�� 11:16:13
*******************************************************************************************************/
BOOL CTiShi::Move(TCHAR ch)
{
	return Move((UINT)ch);
}

/*******************************************************************************************************
��������Move
��  ����
��  ����
        LPCTSTR lpszText��������ַ���
����ֵ������Ϊ BOOL ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��1��2�� 11:16:23
*******************************************************************************************************/
BOOL CTiShi::Move(LPCTSTR lpszText)
{
	m_szInput = lpszText;
	return Move();
}

/*******************************************************************************************************
��������Show
��  ������ʾ��ʾ��
��  ����
        HWND hParent�������ھ������Ϊ��ʾ����ʾ�����Ժ�Ҫ�ѽ��������õ��������ڡ�
		BOOL bShow  ��TRUE����ʾ��FALSE�����ء�
����ֵ������Ϊ BOOL ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��8��29�� 10:41:08
*******************************************************************************************************/
BOOL CTiShi::Show(HWND hParent, BOOL bShow, LPCTSTR lpcszInput)
{
	ASSERT(hParent != NULL);
	m_hParent = hParent;
	BOOL bOld = m_bShow;
	m_bShow = bShow;
	if(m_bShow)
	{
		/*LONG lnStyle = ::GetWindowLong(this->GetSafeHwnd(), GWL_STYLE);
		lnStyle = lnStyle & ~WS_POPUP | WS_CHILD;
		::SetWindowLong(this->GetSafeHwnd(), GWL_STYLE, lnStyle);
		::SetParent(this->GetSafeHwnd(), m_hParent);*/
		Move();
		//::SetWindowPos(this->GetSafeHwnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		if(lpcszInput)
		{
			m_szInput = lpcszInput;
		} // ���� if(lpcszInput)
		ShowWindow(SW_SHOW);
		if(m_bVerTiShi)
		{
			m_Edit.ShowWindow(SW_SHOW);
		}
		else
		{
			m_Edit.ShowWindow(SW_HIDE);
		} // ���� if(m_bVerTiShi)
		::SetFocus(m_hParent); //���ý���Ϊ��������
	}
	else
	{
		m_edTip.ShowWindow(SW_HIDE);
		m_Edit.ShowWindow(SW_HIDE);
		ShowWindow(SW_HIDE);
		m_szInput = _T("");
	} // ���� if(m_bShow)
	return bOld;
}

/*******************************************************************************************************
��������ShowTip
��  ������ʾѡ����İ�����ʾ�� Tip��
        1�������Ŀ��ʾ��û��ʾ���������ʾ��Ҳ������ʾ��
		2�����ûص��������õ��������ݡ�
		3���ٵ���������ʾ���λ�á�
��  ����
        LPCTSTR lpszText��ѡ��������ݡ�
����ֵ������Ϊ int ��
*******************************************************************************************************/
int CTiShi::ShowTip(LPCTSTR lpszText)
{
	CString szInText(lpszText);
	LPTSTR pStr;
	BOOL bShowTip = FALSE;
	if(!m_bShow)
	{
		m_edTip.ShowWindow(SW_HIDE);
		return FALSE;
	} // ���� if(!m_bShow)

	if(m_ShowTipFun)
	{
		if(!m_ShowTipFun(GetCurSel(), lpszText, &pStr))
		{
			if(pStr)
			{
				szInText = pStr;
				bShowTip = TRUE;
			}// ���� if(pStr)
		}// ���� if(!m_ShowTipFun(GetCurSel(), lpszText, &pStr))
		if(pStr)
		{
			delete []pStr;
		} // ���� if(pStr)
	}// ���� if(m_ShowTipFun)
	
	//������Ŀ�������ʾ���λ��
	int nCur;
	nCur = GetCurSel();
	if(nCur != LB_ERR)
    {
		CRect rect;
		CSize size;
		int nTop, nLeft;
		if(LB_ERR != GetItemRect(nCur, &rect))
		{
			ClientToScreen(&rect);
			
			if(FALSE == bShowTip)
			{
				//Ĭ�ϴ���ʱ����������ʾ��������ʱ������ʾ������ʾ��
				GetFontSize(GetSafeHwnd(), szInText, &size);
				if(size.cx < rect.Width())
				{
					m_edTip.ShowWindow(SW_HIDE);
					return FALSE;
				}
				else
				{
					bShowTip = TRUE;
				}// ���� if(size.cx < rect.Width())
			}
			else
			{
				GetFontSize(m_edTip.GetSafeHwnd(), szInText, &size);
			} // ���� if(FALSE == bShowTip)

			//����λ��
			if(size.cx < m_iScreenWidth - rect.left - rect.Width())
			{
				nLeft = rect.left + m_iListWidth;
				nTop = rect.top;
			}
			else if(size.cx < rect.left)
			{
				nLeft = rect.left - size.cx;
				nTop = rect.top;
			}
			else 
			{
				nLeft = (m_iScreenWidth - size.cx) / 2;
				nTop = rect.top + rect.Height();
			} // ���� if(size.cx < m_iScreenWidth - rect.left - rect.Width())
			m_edTip.MoveWindow(nLeft, nTop, size.cx, size.cy);
		} // ���� if(LB_ERR != GetItemRect(iCur, &rect))
	}// ���� if(nCur != LB_ERR)

	if(bShowTip)
	{
		m_edTip.SetWindowText(szInText);
		m_edTip.ShowWindow(SW_SHOWNOACTIVATE);//SW_SHOW);
	} // ���� if(bShowTip)

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//��������� ===ToolTip=== ���ܵĺ�����
//

/*******************************************************************************************************
��������InitToolTip
��  �ܣ���ʼ�� ToolTip
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-17
ʱ  �䣺19:54:35
*******************************************************************************************************/
void CTiShi::InitToolTip()
{
	if (m_ToolTip.m_hWnd == NULL)
	{
		// Create ToolTip control
		m_ToolTip.Create(this);
		// Create inactive
		m_ToolTip.Activate(FALSE);
		// Enable multiline
		m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 100 /*��󴰿ڿ��*/);
	} // if
}

/*******************************************************************************************************
��������SetToolTipText
��  �ܣ�����ToolTip�ı�
��  ����
         LPCSTR lpszText��Ҫ��ʾ���ı�
         BOOL bActivate���Ƿ񼤻�
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-17
ʱ  �䣺20:23:36
*******************************************************************************************************/
BOOL CTiShi::SetToolTipText(LPCSTR lpszText, BOOL bActivate)
{
	// We cannot accept NULL pointer
	if (lpszText == NULL) return FALSE;

	// Initialize ToolTip
	InitToolTip();

	// If there is no tooltip defined then add it
	if (m_ToolTip.GetToolCount() == 0)
	{
		CRect rect; 
		GetClientRect(rect);
		m_ToolTip.AddTool(this, lpszText, rect, 1);
	} // ���� if(m_ToolTip.GetToolCount() == 0)

	// Set text for tooltip
	m_ToolTip.UpdateTipText(lpszText, this, 1);
	m_ToolTip.Activate(bActivate);
	return TRUE;
}

/*******************************************************************************************************
��������SetToolTipText
��  �ܣ�����ToolTip�ı�
��  ����
         int nText��Ҫ��ʾ���ı�����Դ��
         BOOL bActivate���Ƿ񼤻�
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-17
ʱ  �䣺20:24:10
*******************************************************************************************************/
BOOL CTiShi::SetToolTipText(int nText, BOOL bActivate)
{
	CString sText;

	// Load string resource
	sText.LoadString(nText);
	// If string resource is not empty
	if (sText.IsEmpty() == FALSE) 
	{
		SetToolTipText((LPCTSTR)sText, bActivate);
	}
	return TRUE;
}

BOOL CTiShi::PreTranslateMessage(MSG* pMsg)
{
	m_ToolTip.RelayEvent(pMsg);
	return CListBox::PreTranslateMessage(pMsg);
}

//
//��������� ===ToolTip=== ���ܵĺ�����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


// ���ļ��м�������
int CTiShi::LoadString(LPCTSTR lpszFileName)
{
	TRY
	{
		CStdioFile stdf(lpszFileName, CFile::modeRead);
		CString szText;
		while(stdf.ReadString(szText))
		{
			AddString(szText);
		} // ���� (stdf.ReadString(szText))
	}
	CATCH(CFileException, e)
	{
		e->ReportError();
		return 0;
	}
	END_CATCH
	return 1;
}

/*******************************************************************************************************
��������FindText
��  ��������Ŀ��ʾ���в����ַ�����������ַ������ڳ�Ա���� m_szInput �С�
��  ������
����ֵ������Ϊ int ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��8��29�� 11:43:50
*******************************************************************************************************/
int CTiShi::FindText()
{
	return FindText(m_szInput);
}

int CTiShi::FindText(LPCTSTR lpcszText)
{
	int nRet = 0;
	int nIndex = FindString(-1, lpcszText);
	TRACE(_T("%s(%d) : %s:%d\n"), __FILE__, __LINE__,  m_szInput, nIndex);
	if(LB_ERR != nIndex)
	{
		SetCurSel(nIndex);
		nRet = 1;
	}// ���� if(LB_ERR != nIndex)
	GetString();	
	
	return nRet;
}

/*******************************************************************************************************
��������GetString
��  ����Ĭ�ϵõ���Ŀ��ʾ����ѡ����ı���
        �˺���Ϊ���غ������û��������أ��õ��Լ���Ҫ�����ݡ�
		�����ش˺�������ʾ�Դ����ע�Ϳ� Tip
��  ����void����
����ֵ������Ϊ CString ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��8��29�� 11:44:51
*******************************************************************************************************/
CString CTiShi::GetString(void)
{
	CString szText;
	int nIndex = GetCurSel();
	if(LB_ERR != nIndex)
	{
		GetText(nIndex, szText);
		
		// �Ƿ���ʾע�Ϳ� Tip
		ShowTip(szText);
	} // ���� if(LB_ERR != nIndex)
	return szText;
}