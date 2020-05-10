/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����SetMAC.cpp
��  ����д��MAC��ַ
��  ����1.0
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��11��8��
ʱ  �䣺15:31:56
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
*******************************************************************************************************/

#include "StdAfx.h"
#include "setmac.h"
#include "..\CommonFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CString g_INIFile;

CSetMAC::CSetMAC(void)
{
	SetName(_T("д��MAC��ַ"));
	m_szMAC = _T("");

	CString szPath = GetCurrentDir();
	szPath += _T("\\") + g_INIFile;
	TCHAR szRe [1024];
	if(::GetPrivateProfileString(_T("WRITEMAC"), _T("PACKNUM"), _T("5"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("��ȡдMAC��ַ�Ĵ���ʧ��"));
		return;
	} // ���� if(::GetPrivateProfileString(_T("WRITEMAC"), _T("PACKNUM"), _T("5"), szRe, 1024, szPath) == 0)
	m_Num = _ttoi(szRe);
	if(::GetPrivateProfileString(_T("WRITEMAC"), _T("MACADDRESSINCREATE"), _T("1"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("��ȡMAC��ַ��������ʧ��"));
		return;
	} // ���� if(::GetPrivateProfileString(_T("WRITEMAC"), _T("MACADDRESSINCREATE"), _T("1"), szRe, 1024, szPath) == 0)
	m_Increate = _ttoi(szRe);
}

CSetMAC::~CSetMAC(void)
{

}

int CSetMAC::DoPrepare(void)
{
	//m_plog->Message(_T("��ʼд��MAC��ַ......"));

	//�������ļ��ж���Ҫд��MAC��ַ
	CString szPath = GetCurrentDir();
	szPath += _T("\\") + g_INIFile; // _T("Setup.Ini");
	int nLen = 7;

	TCHAR szReturnedString[7];
	if(::GetPrivateProfileString(_T("MACADDR"), _T("MAC_OUI"), _T("00037F"), szReturnedString, nLen, szPath) != 6)
	{
		m_plog->Message(_T("�������ļ��ж���MAC��ַ����"));
		return 1;
	} // ���� if(::GetPrivateProfileString(_T("MACADDR"), _T("MAC_OUI"), _T("00037F"), szReturnedString, nLen, szPath) != 6)
	szReturnedString[6] = _T('\0');
	m_szMAC = szReturnedString;
	if(::GetPrivateProfileString(_T("MACADDR"), _T("MAC_CURR_ADDR"), _T("-1"), szReturnedString, nLen, szPath) != 6)
	{
		m_plog->Message(_T("�������ļ��ж���MAC��ַ����"));
		return 1;
	} // ���� if(::GetPrivateProfileString(_T("MACADDR"), _T("MAC_CURR_ADDR"), _T("-1"), szReturnedString, nLen, szPath) != 6)
	m_szMAC += szReturnedString;
	m_szMAC.MakeLower();
	m_plog->Message(_T("д���MAC��ַΪ��"), FALSE);
	m_plog->Message(m_szMAC);

	if(WriteMAC())
	{
		//д��MAC��ַʧ��
		return 2;
	} // ���� if(WriteMAC())

	//�������ļ���д���´ε�MAC��ַ
	DWORD nextAddr = HexStrToDWORD(szReturnedString, 6);
	nextAddr += m_Increate;
	_stprintf(szReturnedString, "%06X", nextAddr);
	if(!::WritePrivateProfileString(_T("MACADDR"), _T("MAC_CURR_ADDR"), szReturnedString, szPath))
	{
		m_plog->Message(_T("MAC��ַд�������ļ�ʧ�ܣ�����"));
		return 2;
	} // ���� if(!::WritePrivateProfileString(_T("MACADDR"), _T("MAC_CURR_ADDR"), szReturnedString, szPath))
	//_tprintf(_T("�´�д���MAC��ַΪ��%s\n"), szReturnedString);
	
	return 0;
}


/*******************************************************************************************************
��������WriteMAC
��  ����д��MAC��ַ
��  ����void����
����ֵ������Ϊ int ���ɹ������㣬ʧ�ܷ��ط��㡣
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��11��8�� 15:30:59
*******************************************************************************************************/
int CSetMAC::WriteMAC(void)
{
	return 0;
}

/*******************************************************************************************************
��������HexStrToDWORD
��  ���������ַ�����ʾ��ʮ������ת��ΪDWORD
��  ����
        char * str��ʮ�����Ƶ������ַ���
		int nSize ��Ҫת���ĳ���
����ֵ������Ϊ DWORD ��
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��11��4�� 21:28:34
*******************************************************************************************************/
DWORD CSetMAC::HexStrToDWORD(char * str, int nSize)
{
    DWORD value=0;

	for(int i = 0; i < nSize; ++i)
    {
		if(str[i] >= '0' && str[i] <= '9')
        {
    	    value <<= 4;
    	    value += (str[i] - '0');
        }
        else
        {
			value <<= 4;
			if(str[i] >= _T('a') && str[i] <= _T('f'))
			{
				value += (str[i] - _T('a') + 10);
			}				
			else
			{
				if(str[i] >= _T('A') && str[i] <= _T('F'))
				{
					value += (str[i] - _T('A') + 10);
				} // ���� if(str[i] >= _T('A') && str[i] <= _T('F'))
			} // ���� if(str[i] >= _T('a') && str[i] <= _T('f'))
        }
    }

    return value;
}

/*******************************************************************************************************
��������MACStrToHex
��  �������ַ�����MAC��ַת��ΪHex��MAC��ַ
��  ����
        char * pstrMAC���ַ���MAC��ַ
		char * pHex   ��Hex�͵�MAC��ַ
����ֵ������Ϊ int ���ɹ�ת������ 0�����򷵻ط��㡣
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��11��30�� 8:50:53
*******************************************************************************************************/
int CSetMAC::MACStrToHex(char * pstrMAC, char * pHex)
{
	for(int i = 0; i < 6; i++)
	{
		*(pHex + i) = (char)HexStrToDWORD(pstrMAC + i * 2, 2);
	} // ���� for(int i = 0; i < 6; i++)
	return 0;
}
