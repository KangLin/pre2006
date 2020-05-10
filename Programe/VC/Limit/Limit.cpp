/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����Limit.cpp
��  ����
��  ����2005.6.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��7��12��
ʱ  �䣺19:05:47
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
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
        m_szRegKey = _T("SoftWare\\���ֹ�����\\") + m_szSoftName + _T("\\Register");        
    }
    else
    {
        m_szRegKey = _T("SoftWare\\���ֹ�����\\");
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
    } // ���� if(ERROR_SUCCESS != m_reg.Open(HKEY_CURRENT_USER, m_szRegKey))
    m_reg.QueryDWORDValue(_T("No"), m_dwRegVal);
    if(ERROR_SUCCESS != m_reg.QueryDWORDValue(_T("No1"), m_dwDay))
    {
        return FALSE; 
    }
    else
    {
        m_dwDay ^= m_dwXOR1;
    } // ���� if(ERROR_SUCCESS != m_reg.QueryDWORDValue(_T("No1"), m_dwDay))
    if(ERROR_SUCCESS != m_reg.QueryDWORDValue(_T("No2"), m_dwMonth))
    {
        return FALSE; 
    }
    else
    {
        m_dwMonth ^= m_dwXOR2;
    } // ���� if(ERROR_SUCCESS != m_reg.QueryDWORDValue(_T("No2"), m_dwMonth))
    if(ERROR_SUCCESS != m_reg.QueryDWORDValue(_T("No3"), m_dwYear))
    {
        return FALSE;
    }
    else
    {
        m_dwYear ^= m_dwXOR3;
    } // ���� if(ERROR_SUCCESS != m_reg.QueryDWORDValue(_T("No3"), m_dwYear))
    
    return TRUE;
}

/*******************************************************************************************************
��������WriteRegist
��  ������ע���д��ע���
��  ����
         DWORD dwRegistNo��ע���
����ֵ���ɹ����� TRUE�����򷵻� FALSE��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-23 11:14:16
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
    } // ���� if(dwRegistNo != 0)
    if(ERROR_SUCCESS != m_reg.Open(HKEY_CURRENT_USER, m_szRegKey ))
    {
        m_reg.Create(HKEY_CURRENT_USER, m_szRegKey);
    } // ���� if(ERROR_SUCCESS != m_reg.Open(HKEY_CURRENT_USER, m_szRegKey))
    if(ERROR_SUCCESS != m_reg.SetDWORDValue(_T("No"), dwRegist))
    {
        return FALSE;
    } // ���� if(ERROR_SUCCESS != m_reg.SetDWORDValue(_T("No"), dwRegist))
    return TRUE;
}

BOOL CLimit::WriteDate()
{
    if(ERROR_SUCCESS != m_reg.Open(HKEY_CURRENT_USER, m_szRegKey))
    {
        if(ERROR_SUCCESS != m_reg.Create(HKEY_CURRENT_USER, m_szRegKey))
        {
            return FALSE;
        } // ���� if(ERROR_SUCCESS != m_reg.Create(HKEY_CURRENT_USER, m_szRegKey))
    } // ���� if(ERROR_SUCCESS != m_reg.Open(HKEY_CURRENT_USER, m_szRegKey))
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

// �õ�Ӳ�����
DWORD CLimit::GetDiskNo(void)
{
	if(::GetVolumeInformation(_T("C:\\"), NULL, NULL, &m_dwDiskSerialNumber, NULL, NULL, NULL, NULL))
    {
       return m_dwDiskSerialNumber;
    } // ���� if(::GetVolumeInformation(_T("C:\\"), NULL, NULL, &m_dwDiskSerialNumber, NULL, NULL, NULL, NULL))
    TRACE(_T("%s(%d) : �õ�Ӳ�����ʧ��\n"), __FILE__, __LINE__);
    return 0;
}

/*******************************************************************************************************
��������GetRegistNoInRegedit
��  �����õ�������ע����е�ע����
��  ������
����ֵ������Ϊ DWORD ��������ע����е�ע����
��  ����2005.8.0.0
��  �ߣ���  ��
ʱ  �䣺2005��12��3�� 18:07:45
*******************************************************************************************************/
DWORD CLimit::GetRegistNoInRegedit()
{
	return m_dwRegVal;
}

/*******************************************************************************************************
��������GetMachineNo
��  �����õ�������
��  ������
����ֵ������Ϊ DWORD ��
��  ����2005.8.0.0
��  �ߣ���  ��
ʱ  �䣺2005��12��3�� 18:10:35
*******************************************************************************************************/
DWORD CLimit::GetMachineNo()
{
	m_dwMachineNo = GetDiskNo() ^ 807254913;
	return m_dwMachineNo;
}

/*******************************************************************************************************
��������ValidateRegistNo
��  ������֤ע����
��  ����
         DWORD dwRegistNo��ע����
����ֵ���ɹ�����TRUE,���򷵻�FALSE
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-22 11:54:58
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
	} // ���� if(GetRegistNo() == dwReg)
   
    return FALSE;
}

/*******************************************************************************************************
��������GetRegistNo
��  �����õ�ע���
��  ����
         DWORD dwMachine��������
����ֵ������ע���
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-23 11:13:27
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
	} // ���� if(dwMachine != 0)
	DWORD dwDate1, dwDate2, dwDate3;
	
	dwDate1 = m_dwXOR ^ dwData;
	dwDate2 = dwDate1 << 16;
	dwDate1 >>= 16;
    dwDate1 = dwDate2 | dwDate1;
	m_dwRegist = dwDate1;

    TRACE(_T("%s(%d) : ע���:%d\n"), __FILE__, __LINE__, m_dwRegist);
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
��������Regist
��  �������ע��
��  ����
        BOOL bShow     ���Ƿ���ʾע��Ի���TRUE����ʾ��FALSE������ʾ��
		LPCTSTR lpszKey��ע����ֵ
����ֵ������Ϊ BOOL ���ɹ����� TRUE�����򷵻� FALSE��
��  ����1.1.0.0
��  �ߣ���  ��
ʱ  �䣺2005��7��20�� 10:54:41
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
		} // ���� if(bTrueShow)
		return TRUE;
    } // ���� if(limit.ValidateRegistNo(limit.GetRegistNoInRegedit()))

    if(!bShow)
    {
        if(30 > limit.GetDays())
        {
            return TRUE;
        } // ���� if(30 > limit.GetDays())
        return FALSE;
    } // ���� if(!bShow)

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
            } // ���� if(30 > limit.GetDays())
            return FALSE;
        } // ���� if(reg.DoModal() == IDCANCEL)

        if(limit.ValidateRegistNo(reg.m_dwRegist))
        {
            limit.WriteRegist();
            ::MessageBox(NULL, _T("ע��ɹ�"), _T("ע��ɹ�"), MB_OK | MB_ICONINFORMATION);
        }
        else
        {
            ::MessageBox(NULL, _T("ע��Ŵ���"), _T("ע��ʧ��"), MB_OK | MB_ICONERROR);
        } // ���� if(reg.m_bRegisted)
    } while(!limit.ValidateRegistNo(reg.m_dwRegist));

    return limit.ValidateRegistNo(reg.m_dwRegist);
}