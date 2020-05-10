// UserInfo.cpp : implementation file
//

#include "stdafx.h"
#include "..\中国象棋.h"
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
    //设置扩展风格
    //m_UserInfo.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT /*| LVS_EX_CHECKBOXES */);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*******************************************************************************************************
函数名：SetListHead
功  能：设置列表头
参  数：
        CCommand* pCmd：表头内容
返回值：成功返回TRUE,否则返回FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-30
时  间：15:51:00
*******************************************************************************************************/
BOOL CUserInfo::SetListHead(CCommand* pCmd)
{
    if(m_bSetListHead)
    {
        TRACE(_T("%s(%d) : 表头已设置,消除表项目.\n"), __FILE__, __LINE__);
        m_UserInfo.DeleteAllItems();//消除表项目
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
函数名：AddUserInfo
功  能：向表中增加用户的信息
参  数：
         CCommant* pCmd：用户信息串
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-30
时  间：15:38:43
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
        
        if(i == 0) //插入项目
        {
            iPos = HadUser(sztmp);
            if(iPos != -1)
            {
                TRACE(_T("%s(%d) : 用户 %s 已存在 %d, 修改用户信息\n"), __FILE__, __LINE__, sztmp, iPos);
                lvi.iItem = iPos;
                m_UserInfo.SetItem(&lvi);
            }
            else
            {
                m_pUserName->AddString(sztmp);  //在用用户名列表中加入用户名
                m_pVideoUser->AddString(sztmp); //在视频中列表用户中加入用户名
                iPos = m_UserInfo.InsertItem(&lvi);
            }
        }
        else       //插入子项目
        {       
            lvi.iItem = iPos;
            m_UserInfo.SetItem(&lvi);
        }
        i++;
        TRACE(_T("%s(%d) : CUserInfo::AddUserInfo:%s\n"), __FILE__, __LINE__, sztmp);
    }
}

/*******************************************************************************************************
函数名：HadUser
功  能：判断指定的用户是否已存在
参  数：
         LPCSTR lpszUserName：用户名
返回值：用户信息已存在返回它在表中的索引号，否则返回 -1。
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-31
时  间：11:07:51
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
函数名：FindUser
描  述：查找用户,如果查到并选择它
参  数：
        LPCSTR lpszUserName：用户名
返回值：找到返回 TREU
版  本：1.0.0.1
作  者：康  林
时  间：2005-7-2 7:36:51
*******************************************************************************************************/
BOOL CUserInfo::FindUser(LPCSTR lpszUserName)
{
    int i = HadUser(lpszUserName);
    if(i == -1)
    {
       return FALSE;
    } // 结束 if(i == -1)
    m_UserInfo.SetHotItem(i);
    return TRUE;
}

/*******************************************************************************************************
函数名：FindValue
功  能：查找指定用户的指定值
参  数：
         LPCSTR lpszUserName：用户名
         LPCSTR lpszField：要查找的值
返回值：返回找到的值
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-31
时  间：19:21:55
*******************************************************************************************************/
CString CUserInfo::FindValue(LPCSTR lpszUserName, LPCSTR lpszField)
{
    ASSERT(lpszUserName && lpszField);
    int i;
    i = HadUser(lpszUserName);
    if(i == -1)
    {
        TRACE(_T("%s(%d) : 没找到指定的用户的值\n"), __FILE__, __LINE__);
        return _T("");
    }

    CString sztmp(lpszField);
    if(sztmp ==_T("用户名"))
    {
        return m_UserInfo.GetItemText(i, 0);
    }
    if(sztmp ==_T("下棋总盘数"))
    {
        return m_UserInfo.GetItemText(i, 1);
    }
    if(sztmp ==_T("赢的盘数"))
    {
        return m_UserInfo.GetItemText(i, 2);
    }
    if(sztmp ==_T("输的盘数"))
    {
        return m_UserInfo.GetItemText(i, 3);
    }
    if(sztmp ==_T("和的盘数"))
    {
        return m_UserInfo.GetItemText(i, 4);
    }
    if(sztmp ==_T("积分"))
    {
        return m_UserInfo.GetItemText(i, 5);
    }
    if(sztmp ==_T("性别"))
    {
        return m_UserInfo.GetItemText(i, 6);
    }
    if(sztmp ==_T("状态"))
    {
        return m_UserInfo.GetItemText(i, 7);
    }
    if(sztmp ==_T("头像"))
    {
        return m_UserInfo.GetItemText(i, 8);
    }
    return _T("");
}

/*******************************************************************************************************
函数名：DeleteUser
功  能：删除指定用户的信息
参  数：
         LPCSTR lpszUserName：要删除的用户名
返回值：成功返回 TRUE，否则返回 FALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-31
时  间：12:03:42
*******************************************************************************************************/
BOOL CUserInfo::DeleteUser(LPCSTR lpszUserName)
{
    int i;
    i = HadUser(lpszUserName);
    if(i != -1)
    {
        m_UserInfo.DeleteItem(i);
        m_pUserName->DeleteString(i); //文本信息中的列表中的用户名
        m_pVideoUser->DeleteString(i);//视频中的列表中的用户名
        return TRUE;
    }
    return FALSE;
}

/*******************************************************************************************************
函数名：DeleteUserInfo
功  能：删除用户信息
参  数：
         CCommand *pCmd：
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-31
时  间：12:14:05
*******************************************************************************************************/
void CUserInfo::DeleteUserInfo(CCommand *pCmd)
{
    CString szUser;
    szUser = pCmd->GetPara();
    DeleteUser(szUser);
}

