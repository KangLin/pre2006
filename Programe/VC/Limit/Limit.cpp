/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：Limit.cpp
描  述：
版  本：2005.6.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年7月12日
时  间：19:05:47
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/
#include "StdAfx.h"
#include ".\limit.h"
#include ".\Regist.h"

CLimit::CLimit(void)
{
    m_dwXOR = 561257923;
    m_dwXOR1 = 0x81976214;
    m_dwXOR2 = 0x19760121;
    m_dwXOR3 = 0xf1a5c4b1;
    m_dwDiskSerialNumber = 19760121;
	GetMachineNo();
    m_dwRegVal = 0;
    m_dwDay = 0;
    m_dwMonth = 0;
    m_dwYear = 0;
}

CLimit::CLimit(LPCTSTR lpszKey)
{
    m_dwXOR = 561257923;
    m_dwXOR1 = 0x81976214;
    m_dwXOR2 = 0x19760121;
    m_dwXOR3 = 0xf1a5c4b1;
    m_dwDiskSerialNumber = 19760121;
	GetMachineNo();
    m_dwRegVal = 0;
    m_dwDay = 0;
    m_dwMonth = 0;
    m_dwYear = 0;
    GetRegist(lpszKey);
}

BOOL CLimit::GetRegist(LPCTSTR lpszKey)
{
    if(lpszKey == NULL)
    {
        m_szSoftName = AfxGetApp()->m_pszProfileName;
        m_szRegKey = _T("SoftWare\\康林工作室\\") + m_szSoftName + _T("\\Register");        
    }
    else
    {
        m_szRegKey = _T("SoftWare\\康林工作室\\");
        m_szRegKey += lpszKey;
        m_szRegKey += _T("\\Register");
    }
    
    if(ERROR_SUCCESS != m_reg.Open(HKEY_CURRENT_USER, m_szRegKey))
    {
        if(ERROR_SUCCESS ==m_reg.Create(HKEY_CURRENT_USER, m_szRegKey))
        {
            return this->WriteDate();
        }            
        return FALSE;
    } // 结束 if(ERROR_SUCCESS != m_reg.Open(HKEY_CURRENT_USER, m_szRegKey))
    m_reg.QueryDWORDValue(_T("No"), m_dwRegVal);
    if(ERROR_SUCCESS != m_reg.QueryDWORDValue(_T("No1"), m_dwDay))
    {
        return FALSE; 
    }
    else
    {
        m_dwDay ^= m_dwXOR1;
    } // 结束 if(ERROR_SUCCESS != m_reg.QueryDWORDValue(_T("No1"), m_dwDay))
    if(ERROR_SUCCESS != m_reg.QueryDWORDValue(_T("No2"), m_dwMonth))
    {
        return FALSE; 
    }
    else
    {
        m_dwMonth ^= m_dwXOR2;
    } // 结束 if(ERROR_SUCCESS != m_reg.QueryDWORDValue(_T("No2"), m_dwMonth))
    if(ERROR_SUCCESS != m_reg.QueryDWORDValue(_T("No3"), m_dwYear))
    {
        return FALSE;
    }
    else
    {
        m_dwYear ^= m_dwXOR3;
    } // 结束 if(ERROR_SUCCESS != m_reg.QueryDWORDValue(_T("No3"), m_dwYear))
    
    return TRUE;
}

/*******************************************************************************************************
函数名：WriteRegist
描  述：把注册号写入注册表
参  数：
         DWORD dwRegistNo：注册号
返回值：成功返回 TRUE，否则返回 FALSE。
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-23 11:14:16
*******************************************************************************************************/
BOOL CLimit::WriteRegist(DWORD dwRegistNo)
{
    DWORD dwRegist;
    if(dwRegistNo != 0)
    {
        dwRegist = dwRegistNo; 
    }
    else
    {
        dwRegist = m_dwRegist;
    } // 结束 if(dwRegistNo != 0)
    if(ERROR_SUCCESS != m_reg.Open(HKEY_CURRENT_USER, m_szRegKey ))
    {
        m_reg.Create(HKEY_CURRENT_USER, m_szRegKey);
    } // 结束 if(ERROR_SUCCESS != m_reg.Open(HKEY_CURRENT_USER, m_szRegKey))
    if(ERROR_SUCCESS != m_reg.SetDWORDValue(_T("No"), dwRegist))
    {
        return FALSE;
    } // 结束 if(ERROR_SUCCESS != m_reg.SetDWORDValue(_T("No"), dwRegist))
    return TRUE;
}

BOOL CLimit::WriteDate()
{
    if(ERROR_SUCCESS != m_reg.Open(HKEY_CURRENT_USER, m_szRegKey))
    {
        if(ERROR_SUCCESS != m_reg.Create(HKEY_CURRENT_USER, m_szRegKey))
        {
            return FALSE;
        } // 结束 if(ERROR_SUCCESS != m_reg.Create(HKEY_CURRENT_USER, m_szRegKey))
    } // 结束 if(ERROR_SUCCESS != m_reg.Open(HKEY_CURRENT_USER, m_szRegKey))
    DWORD dwDay, dwMonth, dwYear;
    CTime t = CTime::GetCurrentTime();
    dwDay = t.GetDay();
    dwMonth = t.GetMonth();
    dwYear = t.GetYear();
    m_reg.SetDWORDValue(_T("No1"), (dwDay ^ m_dwXOR1));
    m_reg.SetDWORDValue(_T("No2"), (dwMonth ^ m_dwXOR2));
    m_reg.SetDWORDValue(_T("No3"), (dwYear ^ m_dwXOR3));
    m_dwDay = dwDay;
    m_dwMonth = dwMonth;
    m_dwYear = dwYear;
    return TRUE;
}

CLimit::~CLimit(void)
{
    m_reg.Close();
}

// 得到硬盘序号
DWORD CLimit::GetDiskNo(void)
{
	if(::GetVolumeInformation(_T("C:\\"), NULL, NULL, &m_dwDiskSerialNumber, NULL, NULL, NULL, NULL))
    {
       return m_dwDiskSerialNumber;
    } // 结束 if(::GetVolumeInformation(_T("C:\\"), NULL, NULL, &m_dwDiskSerialNumber, NULL, NULL, NULL, NULL))
    TRACE(_T("%s(%d) : 得到硬盘序号失败\n"), __FILE__, __LINE__);
    return 0;
}

/*******************************************************************************************************
函数名：GetRegistNoInRegedit
描  述：得到保存在注册表中的注册码
参  数：无
返回值：类型为 DWORD 。保存在注册表中的注册码
版  本：2005.8.0.0
作  者：康  林
时  间：2005年12月3日 18:07:45
*******************************************************************************************************/
DWORD CLimit::GetRegistNoInRegedit()
{
	return m_dwRegVal;
}

/*******************************************************************************************************
函数名：GetMachineNo
描  述：得到机器码
参  数：无
返回值：类型为 DWORD 。
版  本：2005.8.0.0
作  者：康  林
时  间：2005年12月3日 18:10:35
*******************************************************************************************************/
DWORD CLimit::GetMachineNo()
{
	m_dwMachineNo = GetDiskNo() ^ 807254913;
	return m_dwMachineNo;
}

/*******************************************************************************************************
函数名：ValidateRegistNo
描  述：验证注册码
参  数：
         DWORD dwRegistNo：注册码
返回值：成功返回TRUE,否则返回FALSE
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-22 11:54:58
*******************************************************************************************************/
BOOL CLimit::ValidateRegistNo(DWORD dwRegistNo)
{
    DWORD dwReg;
   
    dwReg = dwRegistNo;

	if(GetRegistNo() == dwReg)
	{
		return TRUE; 
	}
    else
	{
		return FALSE;
	} // 结束 if(GetRegistNo() == dwReg)
   
    return FALSE;
}

/*******************************************************************************************************
函数名：GetRegistNo
描  述：得到注册号
参  数：
         DWORD dwMachine：机器码
返回值：返回注册号
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-23 11:13:27
*******************************************************************************************************/
DWORD CLimit::GetRegistNo(DWORD dwMachine)
{
	DWORD dwData;
    if(dwMachine != 0)
	{
		dwData = dwMachine;
    }
    else
	{
		dwData = m_dwMachineNo;
	} // 结束 if(dwMachine != 0)
	DWORD dwDate1, dwDate2, dwDate3;
	
	dwDate1 = m_dwXOR ^ dwData;
	dwDate2 = dwDate1 << 16;
	dwDate1 >>= 16;
    dwDate1 = dwDate2 | dwDate1;
	m_dwRegist = dwDate1;

    TRACE(_T("%s(%d) : 注册号:%d\n"), __FILE__, __LINE__, m_dwRegist);
    return m_dwRegist;
}

DWORD CLimit::GetDays()
{
    CTime curt;
    CTime t(m_dwYear, m_dwMonth, m_dwDay, 0, 0, 0);
    curt = CTime::GetCurrentTime();
    CTimeSpan span;
    span = curt - t;
    int ir;
    ir = span.GetDays();
    return ir;    
}

/*******************************************************************************************************
函数名：Regist
描  述：检查注册
参  数：
        BOOL bShow     ：是否显示注册对话框，TRUE：显示，FALSE：不显示。
		LPCTSTR lpszKey：注册表键值
返回值：类型为 BOOL 。成功返回 TRUE，否则返回 FALSE。
版  本：1.1.0.0
作  者：康  林
时  间：2005年7月20日 10:54:41
*******************************************************************************************************/
extern "C" BOOL Regist(BOOL bShow, LPCTSTR lpszKey, BOOL bTrueShow)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CLimit limit(lpszKey);
    
	if(limit.ValidateRegistNo(limit.GetRegistNoInRegedit()))
	{
		if(bTrueShow)
		{
			CRegist reg;
			reg.m_szTitle = lpszKey;			
			reg.m_dwMachinNo = limit.GetMachineNo();
			reg.DoModal();
		} // 结束 if(bTrueShow)
		return TRUE;
    } // 结束 if(limit.ValidateRegistNo(limit.GetRegistNoInRegedit()))

    if(!bShow)
    {
        if(30 > limit.GetDays())
        {
            return TRUE;
        } // 结束 if(30 > limit.GetDays())
        return FALSE;
    } // 结束 if(!bShow)

    CRegist reg;
    reg.m_szTitle = lpszKey;
	reg.m_dwMachinNo = limit.GetMachineNo();
   
    do
    {
        if(reg.DoModal() == IDCANCEL)
        {
            if(30 > limit.GetDays())
            {
                return TRUE;
            } // 结束 if(30 > limit.GetDays())
            return FALSE;
        } // 结束 if(reg.DoModal() == IDCANCEL)

        if(limit.ValidateRegistNo(reg.m_dwRegist))
        {
            limit.WriteRegist();
            ::MessageBox(NULL, _T("注册成功"), _T("注册成功"), MB_OK | MB_ICONINFORMATION);
        }
        else
        {
            ::MessageBox(NULL, _T("注册号错误！"), _T("注册失败"), MB_OK | MB_ICONERROR);
        } // 结束 if(reg.m_bRegisted)
    } while(!limit.ValidateRegistNo(reg.m_dwRegist));

    return limit.ValidateRegistNo(reg.m_dwRegist);
}