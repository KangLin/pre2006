// UserInfo.cpp : implementation file
//

#include "stdafx.h"
#include "..\�й�����.h"
#include "UserInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserInfo dialog
IMPLEMENT_DYNCREATE(CUserInfo, CDialog)

CUserInfo::CUserInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CUserInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserInfo)
	//}}AFX_DATA_INIT
}


void CUserInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserInfo)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserInfo, CDialog)
	//{{AFX_MSG_MAP(CUserInfo)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserInfo message handlers

void CUserInfo::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	if(m_UserInfo.GetSafeHwnd())
	{
		m_UserInfo.MoveWindow(0, 0, cx, cy);
	}
}

BOOL CUserInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();

    // TODO: Add extra initialization here	
	m_lstWidth = 100;
    m_bSetListHead = FALSE;
    m_UserInfo.Create(LVS_REPORT | WS_CHILD | WS_VISIBLE | LVS_SORTASCENDING
                      | LVS_ALIGNLEFT | LVS_SHOWSELALWAYS | LVS_SINGLESEL
                      | WS_BORDER | WS_TABSTOP, 
                      CRect(0, 0, 100, 100), this, NULL);
    //������չ���
    //m_UserInfo.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT /*| LVS_EX_CHECKBOXES */);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*******************************************************************************************************
��������SetListHead
��  �ܣ������б�ͷ
��  ����
        CCommand* pCmd����ͷ����
����ֵ���ɹ�����TRUE,���򷵻�FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-30
ʱ  �䣺15:51:00
*******************************************************************************************************/
BOOL CUserInfo::SetListHead(CCommand* pCmd)
{
    if(m_bSetListHead)
    {
        TRACE(_T("%s(%d) : ��ͷ������,��������Ŀ.\n"), __FILE__, __LINE__);
        m_UserInfo.DeleteAllItems();//��������Ŀ
        return FALSE;
    }
    int i = 0;
	CString sztmp;
    while(pCmd->GetLength())
	{
        sztmp = pCmd->GetPara();
		m_UserInfo.InsertColumn(i++, sztmp, LVCFMT_CENTER, m_lstWidth);
	}
    m_bSetListHead = TRUE;
	return TRUE;
}

/*******************************************************************************************************
��������AddUserInfo
��  �ܣ�����������û�����Ϣ
��  ����
         CCommant* pCmd���û���Ϣ��
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-30
ʱ  �䣺15:38:43
*******************************************************************************************************/
void CUserInfo::AddUserInfo(CCommand* pCmd)
{
    CString sztmp;
    int i;
    int iPos;
    int iCount;
    
    i = 0;
    iCount = m_UserInfo.GetItemCount();

    LV_ITEM lvi;
    memset(&lvi, 0, sizeof(lvi));
    lvi.mask = LVIF_TEXT;
    lvi.iItem = iCount;    
    
    while(pCmd->GetLength())
    {
        sztmp = pCmd->GetPara();

        lvi.iSubItem = i;
        lvi.pszText = (LPSTR)(LPCSTR)sztmp;
        
        if(i == 0) //������Ŀ
        {
            iPos = HadUser(sztmp);
            if(iPos != -1)
            {
                TRACE(_T("%s(%d) : �û� %s �Ѵ��� %d, �޸��û���Ϣ\n"), __FILE__, __LINE__, sztmp, iPos);
                lvi.iItem = iPos;
                m_UserInfo.SetItem(&lvi);
            }
            else
            {
                m_pUserName->AddString(sztmp);  //�����û����б��м����û���
                m_pVideoUser->AddString(sztmp); //����Ƶ���б��û��м����û���
                iPos = m_UserInfo.InsertItem(&lvi);
            }
        }
        else       //��������Ŀ
        {       
            lvi.iItem = iPos;
            m_UserInfo.SetItem(&lvi);
        }
        i++;
        TRACE(_T("%s(%d) : CUserInfo::AddUserInfo:%s\n"), __FILE__, __LINE__, sztmp);
    }
}

/*******************************************************************************************************
��������HadUser
��  �ܣ��ж�ָ�����û��Ƿ��Ѵ���
��  ����
         LPCSTR lpszUserName���û���
����ֵ���û���Ϣ�Ѵ��ڷ������ڱ��е������ţ����򷵻� -1��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-31
ʱ  �䣺11:07:51
*******************************************************************************************************/
INT CUserInfo::HadUser(LPCSTR lpszUserName)
{
    int iLow;
    int iHight;
    int iMid;
    iLow = 0;
    iHight = m_UserInfo.GetItemCount();
    iMid = (iLow + iHight) / 2;
    while(iLow <= iHight)
    {
        if(m_UserInfo.GetItemText(iMid, 0) == lpszUserName)
        {
            return iMid;
        }
        if(m_UserInfo.GetItemText(iMid, 0) > lpszUserName)
        {
            iHight = iMid - 1;
        }
        if(m_UserInfo.GetItemText(iMid, 0) < lpszUserName)
        {
            iLow = iMid + 1;
        }
        iMid = (iLow + iHight) / 2;
    }
    return -1;
}

/*******************************************************************************************************
��������FindUser
��  ���������û�,����鵽��ѡ����
��  ����
        LPCSTR lpszUserName���û���
����ֵ���ҵ����� TREU
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-7-2 7:36:51
*******************************************************************************************************/
BOOL CUserInfo::FindUser(LPCSTR lpszUserName)
{
    int i = HadUser(lpszUserName);
    if(i == -1)
    {
       return FALSE;
    } // ���� if(i == -1)
    m_UserInfo.SetHotItem(i);
    return TRUE;
}

/*******************************************************************************************************
��������FindValue
��  �ܣ�����ָ���û���ָ��ֵ
��  ����
         LPCSTR lpszUserName���û���
         LPCSTR lpszField��Ҫ���ҵ�ֵ
����ֵ�������ҵ���ֵ
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-31
ʱ  �䣺19:21:55
*******************************************************************************************************/
CString CUserInfo::FindValue(LPCSTR lpszUserName, LPCSTR lpszField)
{
    ASSERT(lpszUserName && lpszField);
    int i;
    i = HadUser(lpszUserName);
    if(i == -1)
    {
        TRACE(_T("%s(%d) : û�ҵ�ָ�����û���ֵ\n"), __FILE__, __LINE__);
        return _T("");
    }

    CString sztmp(lpszField);
    if(sztmp ==_T("�û���"))
    {
        return m_UserInfo.GetItemText(i, 0);
    }
    if(sztmp ==_T("����������"))
    {
        return m_UserInfo.GetItemText(i, 1);
    }
    if(sztmp ==_T("Ӯ������"))
    {
        return m_UserInfo.GetItemText(i, 2);
    }
    if(sztmp ==_T("�������"))
    {
        return m_UserInfo.GetItemText(i, 3);
    }
    if(sztmp ==_T("�͵�����"))
    {
        return m_UserInfo.GetItemText(i, 4);
    }
    if(sztmp ==_T("����"))
    {
        return m_UserInfo.GetItemText(i, 5);
    }
    if(sztmp ==_T("�Ա�"))
    {
        return m_UserInfo.GetItemText(i, 6);
    }
    if(sztmp ==_T("״̬"))
    {
        return m_UserInfo.GetItemText(i, 7);
    }
    if(sztmp ==_T("ͷ��"))
    {
        return m_UserInfo.GetItemText(i, 8);
    }
    return _T("");
}

/*******************************************************************************************************
��������DeleteUser
��  �ܣ�ɾ��ָ���û�����Ϣ
��  ����
         LPCSTR lpszUserName��Ҫɾ�����û���
����ֵ���ɹ����� TRUE�����򷵻� FALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-31
ʱ  �䣺12:03:42
*******************************************************************************************************/
BOOL CUserInfo::DeleteUser(LPCSTR lpszUserName)
{
    int i;
    i = HadUser(lpszUserName);
    if(i != -1)
    {
        m_UserInfo.DeleteItem(i);
        m_pUserName->DeleteString(i); //�ı���Ϣ�е��б��е��û���
        m_pVideoUser->DeleteString(i);//��Ƶ�е��б��е��û���
        return TRUE;
    }
    return FALSE;
}

/*******************************************************************************************************
��������DeleteUserInfo
��  �ܣ�ɾ���û���Ϣ
��  ����
         CCommand *pCmd��
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-31
ʱ  �䣺12:14:05
*******************************************************************************************************/
void CUserInfo::DeleteUserInfo(CCommand *pCmd)
{
    CString szUser;
    szUser = pCmd->GetPara();
    DeleteUser(szUser);
}

